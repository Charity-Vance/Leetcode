/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     SecurityModule.c
Version:       V1
Author:        jiangzs
Date:          2014-3-31
Description:   ��ȫ�ļ�
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:   20211021
   	   Author: lx
       Modification:
	   ---------------------------------------------------------------------------
����2. Date:
   	   Author:
       Modification:
----------------------------------------------------------------------------------
History2:      ��2���޸�
����1. Date:
   	   Author:
       Modification:
	   ---------------------------------------------------------------------------
����2. Date:
   	   Author:
       Modification:
******************************************************************************/

#include    "SecurityModule.h"

Str7816HeaderSW		GV_7816CMD;

MoneyClient_Type	MoneyClient_Table;			/*�ݴ���Ҫд���ݲ����*/

uchar8 GV_ESAMAction9_SIDP1P2;



const Str_EsamTable	C_EsamNatureToAction[]=
{
/*698����DI1DI0		esam������P2		ƫ��	����*/
	{0x0200,			0x02,			0,		8},		/*ESAM���к�*/
	{0x0300,			0x01,			0,		5},		/*ESAM�汾��*/
	{0x0400,			0x04,			0,		16},	/*�Գ���Կ�汾*/
	{0x0500,			0x05,			0,		4},		/*�ỰʱЧ���� + ʣ��ʱ��*/
	{0x0600,			0x05,			4,		4},		/*�ỰʱЧʣ��ʱ��*/
	{0x0700,			0x06,			0,		12},	/*��ǰ������*/
	{0x1100,			0x08,			0,		1},		/*�����֤Ȩ��*/
	{0x1200,			0x11,			0,		8},		/*�ն˵�ַ*/
	{0x1300,			0x12,			0,		4},		/*�ն˹㲥������*/
	{0x1400,			0x13,			0,		4},		/*�ն�����Ự������*/
	{0x1500,			0x14,			0,		8},		/*�ն˻ỰʱЧ���� +ʣ��ʱ��*/
	{0x1501,			0x14,			0,		4},		/*�ն˻ỰʱЧ����*/
	{0x1502,			0x14,			4,		4},		/*�ն˻Ựʣ��ʱ��*/

/*	{C_Remain_termal_Item,	0x14}*//*�ն˻Ựʣ��ʱ��(������������ڲ���)*/

};


#define	CL_EsamNature	(sizeof (C_EsamNatureToAction) / sizeof (Str_EsamTable) )

/*******************************************************************************
����ԭ�ͣ�	uchar8 InF_Get_SafeModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
����������	����ȫģ��ӿں�����֧�ֶ�esam����
���������	V_ulOAD����ȡ�����ݵ�OAD��ʶ��
���������	pV_ucDataBuf�����������׵�ַ
			pV_usDataLen���������ݳ���
			pV_usDataEncode���������ݱ���
���ز�����	C_OK:��ʾ�ɹ�;Ӧ�����:C_Error;
����λ�ã�
��    ע��	�������������
			�������ݶ���С�˸�ʽ
*******************************************************************************/
uchar8 InF_Get_SafeModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
{
	uchar8		V_ucReturn = C_Error, V_ucLen;
	ushort16	V_usActionID, V_usLen;
	uchar8		V_ucBuffer[C_Max_EsamLen];

	V_usLen = C_Max_EsamLen;
	V_ucLen = C_Max_EsamLen;

	if( (V_ulOAD & 0xFFFF0000) == 0xF1000000) 	/*ESAM����*/
	{
		if( (V_ulOAD == C_IRAuth_Timer)					/*������֤ʱЧ����*/
			|| (V_ulOAD == CID_Auth_T_Remain_Time)		/*�ն������֤ʣ��ʱ��*/
			|| (V_ulOAD == CInfra_Auth_Remain_Time) )	/*������֤ʣ��ʱ��*/

		{
			V_ucReturn = InF_Read_Data(V_ulOAD, &V_ucBuffer[0], &V_usLen, pV_usDataEncode);	/*�����ݲ�*/
		}
		else
		{
			V_usActionID = (ushort16)(V_ulOAD);
			V_ucReturn = S_ReadEsam_698(&V_ucBuffer[0], &V_usLen, V_usActionID);	/*��ESAM*/

			/*���ݷ�ת*/
			PF_OneDataReversed(V_ucBuffer, V_ucBuffer,V_usLen);
		}
	}
	else if(V_ulOAD == CPurchasePowTime)	/*Ǯ���ļ��Ĺ������*/
	{
		V_ucReturn = ReadRecordFile(&V_ucBuffer[0], &V_ucLen, C_PurchasingE_Num_Mac);
		V_usLen = V_ucLen;
	}
	else
	{
		V_ucReturn = C_IDError;
	}


	/*********����Ϊ�÷��ز��� ******************************/
	if(V_ucReturn == C_OK)
	{
		if(*pV_usDataLen < V_usLen)
		{
			V_ucReturn =  C_DataLenError;	/*���ݳ��ȴ�*/
		}
		else
		{
			/*��������*/
			*pV_usDataLen = V_usLen;
			memcpy( pV_ucDataBuf, V_ucBuffer, *pV_usDataLen);
		}
	}


	return(V_ucReturn);

};



/*******************************************************************************
����ԭ�ͣ�uchar8 InF_JudgeKeyStatus(void)
�����������жϵ�ǰ��Կ״̬
�����������
�����������
���ز�����C_StateOfTestKey/C_StateOfOfficialKey
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 InF_JudgeKeyStatus(void)
{
	uchar8		V_ucKeyStatus[30], i, j;
	uchar8		V_uctemp, V_ucNum = 0;
	ushort16	V_usBufRemainLen, V_usActionID;
	uchar8		V_ucResult;

	V_usActionID = (ushort16)CKey_State ;

	V_usBufRemainLen = 30;
	V_ucResult = S_ReadEsam_698(V_ucKeyStatus, &V_usBufRemainLen, V_usActionID);
	if(V_ucResult != C_OK)
	{
		V_ucResult = S_ReadEsam_698(V_ucKeyStatus, &V_usBufRemainLen, V_usActionID);
	}

	if(V_ucResult != C_OK)
	{
		return C_StateOfTestKey;
	}
	else
	{
		for(i = 0; i < V_usBufRemainLen; i++)
		{
			V_uctemp = V_ucKeyStatus[i];
			for(j = 0; j < 8; j++)
			{
				if( (V_uctemp & 0x80) == 0x80)
				{
					V_ucNum++;
				}
				V_uctemp <<= 1;
			}
		}
		if(V_ucNum >= 35)
		{
			return C_StateOfOfficialKey;
		}
		else
		{
			return C_StateOfTestKey;
		}
	}
}


/*******************************************************************************
����ԭ�ͣ�	uchar8 InF_S_Authentication_698(uchar8 *pV_ucData, ushort16* pV_usLen,uchar8 V_ClientAddr)
����������	�����֤�ӿں���
���������	pV_ucData:   	���ݵ���ʼָ�� ע�⣺�������ݳ���(�̶�:32�ֽ�+4�ֽ�MAC)
			V_ucClientAddr:��վ/�ն˵�ַ
���������	pV_ucData:		���ص�����
			pV_usLen:	�������ݳ���(�̶�:48�ֽ�+4�ֽ�MAC)
���ز�����	C_OK:��ʾ�ɹ�;Ӧ�����:C_Error;
����λ�ã�
��    ע��	1:����52�ֽ�
			���յ����ݸ�ʽ:XX(���ĳ���)+XX...XX(��������)+XX(MAC����)+XX...XX(MAC����)
			����ESAM���ݸ�ʽ:8102000000+24+XX...XX(��������)+XX...XX(MAC����)
*******************************************************************************/
uchar8 InF_S_Authentication_698(uchar8 *pV_ucData, ushort16 *pV_usLen, uchar8 V_ucClientAddr)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	ushort16	V_usReceiveLen, V_usReturnData16, V_usSendLen;
	uchar8		V_ucAuthSessionLen, V_ucMACLen;

	if(V_ucClientAddr == Termal_Address)		/*�ն������֤*/
	{
		PF_CopyDataBytes((uchar8 * )TB_Authentication_698_termal, V_ucDataBuffer, CLen_TB_ESAM_Lc_698);
	}
	else	/*��վ�����֤*/
	{
		PF_CopyDataBytes((uchar8 * )TB_Authentication_698, V_ucDataBuffer, CLen_TB_ESAM_Lc_698);
	}

	V_ucDataBuffer[CLen_TB_ESAM_Lc_698] = AuthSessionData1Len_698 + C_MAC_Length_698;

	/*�����������ݳ���*/
	V_ucAuthSessionLen = *pV_ucData;
	PF_CopyDataBytes(&pV_ucData[C_len_698], &V_ucDataBuffer[CLen_TB_ESAM_Lc_698 + C_len_698], V_ucAuthSessionLen);

	/*�����������ݳ���*/
	V_ucMACLen = *(pV_ucData + C_len_698 + V_ucAuthSessionLen);
	PF_CopyDataBytes((pV_ucData + C_len_698 * 2 + V_ucAuthSessionLen), &V_ucDataBuffer[CLen_TB_ESAM_Lc_698 + C_len_698 + V_ucAuthSessionLen], V_ucMACLen);

	/********* ���·���esam���� *********************************************************/
	V_usSendLen =CLen_TB_ESAM_Lc + C_len_698 + AuthSessionData1Len_698 + C_MAC_Length_698;		/*�������ݳ���*/

	V_usReceiveLen = MaxLength_698;		/*����������󳤶�*/
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		if(V_usReturnData16 == C_Security_OverTime)
		{
			return(C_RequestTimeOut_DAR);
		}
		else
		{
			return(C_SCErr_DAR);
		}
	}

	/*********����Ϊ�÷��ز��� *********************************************************/
	*pV_usLen = V_usReceiveLen;

	if(V_ucClientAddr == Master_Address)
	{
		if(*pV_usLen != (AuthSessionData2Len_698 + C_MAC_Length_698) )	/*����48���ֽ�+4MAC*/
		{
			return(C_SCErr_DAR);
		}

		*pV_usLen = *pV_usLen + C_len_698 + C_len_698;
		pV_ucData[0] = AuthSessionData2Len_698;
		PF_CopyDataBytes(V_ucDataBuffer, &pV_ucData[1], pV_ucData[0]);	/*Ӧ��APDU*/
		pV_ucData[AuthSessionData2Len_698 + C_len_698] = C_MAC_Length_698;
		PF_CopyDataBytes(&V_ucDataBuffer[AuthSessionData2Len_698], &pV_ucData[C_len_698 + C_len_698 + AuthSessionData2Len_698], C_MAC_Length_698);	/*Ӧ��APDU*/

	}
	else
	{
		if(*pV_usLen != (AuthSessionData2Len_698_termal + C_MAC_Length_698) )		/*����48���ֽ�+4MAC*/
		{
			return(C_SCErr_DAR);
		}

		*pV_usLen = *pV_usLen + C_len_698 + C_len_698;
		pV_ucData[0] = AuthSessionData2Len_698_termal;
		PF_CopyDataBytes(V_ucDataBuffer, &pV_ucData[1], pV_ucData[0]);	/*Ӧ��APDU*/
		pV_ucData[AuthSessionData2Len_698_termal + C_len_698] = C_MAC_Length_698;
		PF_CopyDataBytes(&V_ucDataBuffer[AuthSessionData2Len_698_termal], &pV_ucData[C_len_698 + C_len_698 + AuthSessionData2Len_698_termal], C_MAC_Length_698);	/*Ӧ��APDU*/

	}

	return(C_OK);
}

/*
const uchar8 C_Test[227]=
{0x07, 0x01, 0x04,
0xF1, 0x00, 0x07, 0x00, 0x02, 0x02, 0x09, 0x81, 0xC0, 0x87, 0x51, 0x19, 0x12, 0xF3, 0x2C, 0xB6,
0xE0, 0xE1, 0xFC, 0x31, 0x68, 0x25, 0xB0, 0xD5, 0xD4, 0x53, 0xE3, 0x51, 0xC2, 0xCE, 0xCC, 0xDE,
0xF5, 0x16, 0x5F, 0x1F, 0x63, 0x25, 0x47, 0x8B, 0xAF, 0x22, 0x12, 0x59, 0xD1, 0x30, 0x37, 0xED,
0x83, 0xD1, 0x29, 0xD9, 0x17, 0x33, 0xCE, 0xB9, 0xE6, 0x52, 0xB8, 0xC4, 0x42, 0xFD, 0x1F, 0xB4,
0xEB, 0xC9, 0xBC, 0x5F, 0x76, 0x25, 0xD2, 0x5E, 0xC0, 0xFD, 0x41, 0x50, 0x1C, 0x13, 0x7B, 0x61,
0x88, 0x77, 0x1B, 0xF8, 0x9D, 0x3F, 0x1E, 0xA4, 0xAE, 0x66, 0xE4, 0x30, 0x52, 0x2D, 0x36, 0xDD,
0x69, 0x0D, 0x8A, 0x3D, 0xA2, 0x8A, 0xDA, 0xDA, 0x91, 0xE0, 0x80, 0x28, 0xC4, 0xCB, 0x4F, 0x80,
0xF0, 0x87, 0x1C, 0x8B, 0x80, 0x19, 0x70, 0x52, 0x50, 0x9C, 0xB2, 0x7F, 0x27, 0xB7, 0x5F, 0x28,
0xC8, 0x25, 0xBB, 0xC5, 0xE2, 0x8F, 0x10, 0x61, 0x62, 0x1D, 0x98, 0x29, 0x59, 0x22, 0x78, 0x5B,
0xD5, 0xE8, 0x2E, 0x88, 0x6A, 0x71, 0xBD, 0xBB, 0xDC, 0xF1, 0xFF, 0xB9, 0x34, 0x52, 0xBC, 0x03,
0x2A, 0x93, 0xA1, 0x7B, 0xBD, 0x4E, 0x73, 0xD4, 0x7C, 0x89, 0xFD, 0xC4, 0x89, 0x5B, 0xC9, 0x34,
0xB9, 0xAC, 0x87, 0x45, 0x4C, 0xF7, 0xE8, 0xBD, 0xCF, 0x41, 0xCB, 0x5C, 0x54, 0xE6, 0xF2, 0xEB,
0x2D, 0xC3, 0xCE, 0xEF, 0xC9, 0x25, 0xD7, 0x0A, 0xB6, 0x5E, 0x81, 0x2E, 0x00, 0x00, 0x0B, 0x00,
0xCD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x04, 0xB7, 0x14, 0x98, 0x43, 0x00};
*/

/*******************************************************************************
����ԭ�ͣ�		uchar8  INF_S_Decrypt_698(uchar8 *pV_ucAPDU,ushort16 *Len,uchar8 V_ucSecurityMode,uchar8 *SID_Data)
����������		����APDU
��������� 		pV_ucAPDU:		����ܵ�APDU�׵�ַ
			pV_usLen:		����֤���ݳ���
			V_ucSecurityMode:2��������֤ģʽ:SID_698;SID_MAC_698
			pV_ucSID_Data:	������֤��Ϣ�׵�ַ
���������		pV_ucAPDU:		���ܺ��APDU�׵�ַ
			pV_usLen:		���ܺ�����ݳ���
���ز�����		Ӧ��ɹ�:C_OK;
	   		Ӧ���������¼���:
   			�Գƽ��ܴ���:C_SymmetryDecodeErr_DAR;ǩ������:C_SignatureErr_DAR;��������:C_Error;
����λ�ã�
��    ע��		P_ APDU��512�ֽ�
		 	ͨ�ŷ��͵����ݸ�ʽ: SID_Data(SID_MAC_698):	XXXXXXXX(��ʶ)+xx(�������ݳ���)+XX...XX(��������)+xx(MAC����)+XX...XX(MAC)
		 	ͨ�ŷ��͵����ݸ�ʽ: SID_Data(SID_698):		XXXXXXXX(��ʶ)+xx(�������ݳ���)+XX...XX(��������)
		 	���͸�ESAM�ĸ�ʽ:	SID_MAC_698:	XXXXXXXX(��ʶ)+XX...XX(��������)+XX...XX(����)+XX...XX(MAC)
		 	���͸�ESAM�ĸ�ʽ:	SID_698:		XXXXXXXX(��ʶ)+XX...XX(��������)+XX...XX(����)
*******************************************************************************/
uchar8  INF_S_Decrypt_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucSecurityMode, uchar8 *pV_ucSID_Data)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	uchar8		V_ucAttachLength,V_ucAttachOffset;
	uchar8		V_ucDataOffset;
	uchar8		V_ucMACLength = 0,V_ucMACOffset;
	ushort16	V_usReturnData16,V_usSendLen,V_usDataLength,V_usReceiveLen;


	/*ƫ�ƺͳ���*/
	/*����*/
	V_ucDataOffset = 0;
	V_usDataLength = *pV_usLen;

	/*��������*/
	V_ucAttachLength = *(pV_ucSID_Data + C_DataID_Length_698);	/*�������ݳ���*/
	V_ucAttachOffset = C_DataID_Length_698 + C_len_698;


	if( (V_ucSecurityMode != SID_MAC_698) && (V_ucSecurityMode != SID_698) )	/*SID_MAC,SID*/
	{
		return(C_OK);
	}

	/*��������*/
	/*��ʶ*/
	PF_CopyDataBytes_698(pV_ucSID_Data,V_ucDataBuffer, C_DataID_Length_698);	/*��ʶ*/

	/*��������*/
	PF_CopyDataBytes_698(pV_ucSID_Data+V_ucAttachOffset,V_ucDataBuffer + C_DataID_Length_698, V_ucAttachLength);

	/*��ʶ����*/
	PF_CopyDataBytes_698(pV_ucAPDU+V_ucDataOffset,V_ucDataBuffer + C_DataID_Length_698 + V_ucAttachLength, V_usDataLength);

	if(V_ucSecurityMode == SID_MAC_698)
	{
		/*MAC*/
		V_ucMACLength = *(pV_ucSID_Data + C_DataID_Length_698 + C_len_698 + V_ucAttachLength);
		V_ucMACOffset = C_DataID_Length_698 + C_len_698 + V_ucAttachLength + C_len_698;

		PF_CopyDataBytes(pV_ucSID_Data + V_ucMACOffset, V_ucDataBuffer + C_DataID_Length_698 + V_ucAttachLength + V_usDataLength, V_ucMACLength);	/*MAC*/
	}

	/********* ���·���esam���� *********************************************************/
	V_usSendLen = C_DataID_Length_698 + V_ucAttachLength + V_usDataLength + V_ucMACLength;
	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		if( (V_usReturnData16 == C_Security_SafetyDataIncorrect) || (V_usReturnData16 == C_Security_MacErr) )
		{
		/*	if(V_ucDataBuffer[0] != 0x05)*/		/*�����������ۼ�mac��*/

			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}

		return(C_SymmetryDecodeErr_DAR);
	/*	return(C_ESAMErr_DAR);*/
	}

	/*********����Ϊ�÷��ز���*********************************************************/
	*pV_usLen = V_usReceiveLen;
	PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucAPDU, *pV_usLen);		/*Ӧ��APDU*/

	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�	uchar8  S_Encrypt_RN_698(uchar8 *pV_ucAPDU,ushort16 *pV_usLen,uchar8 V_ucEncryptMode,uchar8 *pV_ucRN_Data,uchar8 *pV_ucMAC)
����������	�����ݼ���
��������� 	pV_ucAPDU:		����ܵ�APDU�׵�ַ
			pV_usLen:		��������ݳ���
 			pV_ucRN_Data:		��֤�����׵�ַ
			V_ucEncryptMode:�������ݼ��ܷ�ʽ:����+MAC;����;����+MAC
���������	pV_ucAPDU:		���ܺ������
			pV_usLen:		���ܺ�����ݳ���
���ز�����	Ӧ��ɹ�:C_OK;
			Ӧ���������¼���:
			��ȫ��֤ʧ��:C_SCErr_DAR;��������:C_Error;
����λ�ã�
��    ע��	���͸�ESAM�ĸ�ʽ:	XXXXXXXX(����ͷ)+LC+XX...XX(RN)+XX...XX(����)
*******************************************************************************/
uchar8  S_Encrypt_RN_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucEncryptMode, uchar8 *pV_ucRN_Data, uchar8 *pV_ucMAC)
{
	uchar8		V_ucDataBuffer[MaxLength_698], V_ucRD_Len;
	ushort16	V_usReturnData16,V_usReceiveLen, V_usSendLen;

	if(V_ucEncryptMode == RN_698)
	{
		PF_CopyDataBytes( (uchar8 * )TB_Encrypt_RN_PlainData_MAC_698, V_ucDataBuffer, CLen_TB_ESAM_4_698);
	}
	else if(V_ucEncryptMode == CodedData_698)
	{
		PF_CopyDataBytes((uchar8 * )TB_Encrypt_RN_EncodedData_698, V_ucDataBuffer, CLen_TB_ESAM_4_698);
	}
	else if(V_ucEncryptMode == CodedData_MAC_698)
	{
		PF_CopyDataBytes((uchar8 * )TB_Encrypt_RN_EncodedData_MAC_698, V_ucDataBuffer, CLen_TB_ESAM_4_698);
	}
	else
	{
		return(C_OtherErr_DAR);
	}

	V_ucRD_Len = *(pV_ucRN_Data + C_len_698);	/*RN���ݳ���*/

	PF_CopyDataBytes_698(pV_ucRN_Data + 2, &V_ucDataBuffer[CLen_TB_ESAM_4_698 + CLen_LC_Len_698], V_ucRD_Len);	/*����RN*/
	PF_CopyDataBytes_698(pV_ucAPDU, &V_ucDataBuffer[CLen_TB_ESAM_4_698 + CLen_LC_Len_698 + V_ucRD_Len], *pV_usLen);	/*������������*/

	/********* ���·���esam���� *********************************************************/
	V_usSendLen = CLen_TB_ESAM_4_698 + CLen_LC_Len_698 + V_ucRD_Len + (*pV_usLen);
	V_usReceiveLen = V_usSendLen - CLen_TB_ESAM_4_698 - CLen_LC_Len_698;

	PF_Ushort16ToBuffer2_698(&V_ucDataBuffer[4],&V_usReceiveLen);

	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		if(V_usReturnData16 == C_Security_OverTime)
		{
			return(C_RequestTimeOut_DAR);
		}
		else
		{
			if( (V_usReturnData16 == C_Security_SafetyDataIncorrect) || (V_usReturnData16 == C_Security_MacErr) )
			{
				Comm_DealwithSPTVariable(C_SPTNumAdd);
			}

			return(C_ESAMErr_DAR);
		}
	}


/*********����Ϊ�÷��ز��� *********************************************************/
	*pV_usLen = V_usReceiveLen;
	if(V_ucEncryptMode == RN_698)
	{
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucRN_Data, *pV_usLen);		/*Ӧ��APDU*/
	}
	else
	{
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucAPDU, *pV_usLen);			/*Ӧ��APDU*/
	}

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�	uchar8  S_Encrypt_698(uchar8 *pV_ucAPDU,ushort16 *pV_usLen,uchar8 V_ucEncryptMode,uchar8 *pV_ucMAC)
����������	���ݼ���
���������	pV_ucAPDU:		����ܵ�APDU�׵�ַ
			pV_usLen:		��������ݳ���
			V_ucEncryptMode:�������ݼ��ܷ�ʽ:����+MAC;����;����+MAC
���������	pV_ucAPDU:		���ܺ������
			pV_usLen:		���ܺ�����ݳ���
			pV_uc_MAC:		MAC������
���ز����� 	Ӧ����ȷ:C_OK;		Ӧ�����:C_Error;
����λ�ã�
��    ע��	���͸�ESAM�ĸ�ʽ:	811C00P2(��ʶ)+XX(P2)+XXXX(LC)+XX...XX(����)
*******************************************************************************/
uchar8  S_Encrypt_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucEncryptMode, uchar8 *pV_ucMAC)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	ushort16	V_usReturnData16, V_usReceiveLen, V_usSendLen;

	PF_CopyDataBytes( (uchar8 * )TB_Encrypt_EncodedData_MAC_698, V_ucDataBuffer, CLen_TB_ESAM_4_698);
	V_ucDataBuffer[3] = V_ucEncryptMode;	/*P2*/

	PF_CopyDataBytes_698(pV_ucAPDU, &V_ucDataBuffer[CLen_TB_ESAM_4_698+CLen_LC_Len_698], *pV_usLen);	/*������������*/

	/********* ���·���esam���� *********************************************************/
	V_usSendLen = CLen_TB_ESAM_4_698 + CLen_LC_Len_698 + (*pV_usLen);

	PF_Ushort16ToBuffer2_698(&V_ucDataBuffer[4], pV_usLen);

	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_ESAMErr_DAR);
	}

	/*********����Ϊ�÷��ز��� *********************************************************/
	*pV_usLen = V_usReceiveLen;
	if(V_ucEncryptMode == CodedData_698)
	{
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucAPDU, *pV_usLen);	/*Ӧ��APDU*/
	}
	else
	{
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucAPDU, V_usReceiveLen - 4);		/*Ӧ��APDU*/
		*pV_usLen -= 4;
		PF_CopyDataBytes_698(&V_ucDataBuffer[V_usReceiveLen - 4], pV_ucMAC, 4);	/*Ӧ��APDU*/
	}

	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�	uchar8  S_Encrypt_698_terminal(uchar8 *pV_ucAPDU,ushort16 *pV_usLen,uchar8 V_ucEncryptMode,uchar8 *pV_ucMAC)
����������	���ݼ���
���������	 pV_ucAPDU:		����ܵ�APDU�׵�ַ
			pV_usLen:		��������ݳ���
			V_ucEncryptMode:�������ݼ��ܷ�ʽ:����+MAC;����;����+MAC
���������	pV_ucAPDU:		���ܺ������
			Len:		���ܺ�����ݳ���
			pV_uc_MAC:		MAC������
���ز�����	Ӧ����ȷ:C_OK;		Ӧ�����:C_Error;
����λ�ã�
��    ע��	���͸�ESAM�ĸ�ʽ:	811C00P2(��ʶ)+XX(P2)+XXXX(LC)+XX...XX(����)
*******************************************************************************/
uchar8  S_Encrypt_698_terminal(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucEncryptMode, uchar8 *pV_uc_MAC)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	ushort16	V_usReturnData16,V_usReceiveLen, V_usSendLen;
	ushort16	V_usOffset;
	ushort16	V_usLC, V_usLC1;

	if(V_ucEncryptMode == Plain_MAC)	/*����+MAC*/
	{
		PF_CopyDataBytes( (uchar8 * )TB_Encrypt_EncodedData_Plain_MAC_698_terminal, V_ucDataBuffer, CLen_TB_ESAM_4_698);

		PF_CopyDataBytes_698(pV_ucAPDU, &V_ucDataBuffer[CLen_TB_ESAM_4_698 + CLen_LC_Len_698], *pV_usLen);	/*������������*/

		V_usOffset = CLen_TB_ESAM_4_698 + CLen_LC_Len_698 + (*pV_usLen);

		PF_CopyDataBytes((uchar8 * )TB_Encrypt_EncodedData_Plain_MAC_698_terminal_back, &V_ucDataBuffer[V_usOffset], CLen_TB_ESAM_4_698);
		V_usOffset += 4;

		V_usLC1 = *pV_usLen + 4;
		PF_Ushort16ToBuffer2_698( &V_ucDataBuffer[V_usOffset], &V_usLC1);
		V_usOffset += 2;

		V_usLC = *pV_usLen + 4 + 2;		/*LC����*/
		V_usSendLen = V_usOffset;	/*��ֵ�������ݳ���*/

	}
	else if(V_ucEncryptMode == Secret)/*����*/
	{
		PF_CopyDataBytes((uchar8 * )TB_Encrypt_EncodedData_698_terminal, V_ucDataBuffer, CLen_TB_ESAM_4_698);
		PF_CopyDataBytes_698(pV_ucAPDU, &V_ucDataBuffer[CLen_TB_ESAM_4_698 + CLen_LC_Len_698], *pV_usLen);	/*������������*/

		V_usLC = *pV_usLen;
		V_usSendLen = CLen_TB_ESAM_4_698 + CLen_LC_Len_698 + (*pV_usLen);

	}
	else if(V_ucEncryptMode == Secret_MAC)	/*����+SID_MAC*/
	{
		PF_CopyDataBytes((uchar8 * )TB_Encrypt_EncodedData_MAC_698_terminal, V_ucDataBuffer, CLen_TB_ESAM_4_698);

		PF_CopyDataBytes_698(pV_ucAPDU, &V_ucDataBuffer[CLen_TB_ESAM_4_698 + CLen_LC_Len_698], *pV_usLen);		/*������������*/

		V_usOffset = CLen_TB_ESAM_4_698 + CLen_LC_Len_698 + (*pV_usLen);

		PF_CopyDataBytes((uchar8 * )TB_Encrypt_EncodedData_MAC_698_terminal_back, &V_ucDataBuffer[V_usOffset], CLen_TB_ESAM_4_698);
		V_usOffset += 4;

		V_usLC1 = *pV_usLen + 3;	/*LC1���ȼ�����������+3����16�ֽڵ�������+4*/
		V_usLC1 += (16 - (V_usLC1%16) ) + 4;	/*esam���·�����ܳ������ĳ�����6���ֽ�*/

		PF_Ushort16ToBuffer2_698( &V_ucDataBuffer[V_usOffset], &V_usLC1);
		V_usOffset += 2;

		V_usLC = *pV_usLen + 4 + 2;	/*LC���ȼ���*/


		V_usSendLen = V_usOffset;	/*��ֵ�������ݳ���*/
	}
	else
	{
		return(C_OtherErr_DAR);
	}


	PF_Ushort16ToBuffer2_698(&V_ucDataBuffer[4],&V_usLC);

	/********* ���·���esam���� *********************************************************/
	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 !=C_Security_CommandOk)
	{
		return(C_ESAMErr_DAR);
	}

	/*********����Ϊ�÷��ز��� *********************************************************/
	*pV_usLen = V_usReceiveLen;
	if(V_ucEncryptMode == CodedData_698)
	{
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucAPDU, *pV_usLen);		/*Ӧ��APDU*/
	}
	else
	{
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucAPDU, V_usReceiveLen - 4);	/*Ӧ��APDU*/
		*pV_usLen -= 4;
		PF_CopyDataBytes_698(&V_ucDataBuffer[V_usReceiveLen - 4], pV_uc_MAC, 4);		/*Ӧ��APDU*/
	}

	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�	uchar8 S_Encrypt_RN_MAC_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucEncryptMode, uchar8 *pV_ucRN_Data, uchar8 *pV_ucMAC_Data)
����������	���ݼ���(�����ϱ�)
��������� 	pV_ucAPDU:		����ܵ�APDU�׵�ַ
			pV_usLen:		��������ݳ���
			V_ucEncryptMode:�������ݼ��ܷ�ʽ:����+MAC;����;����+MAC
���������	pV_ucAPDU:		���ܺ������
			pV_usLen:		���ܺ�����ݳ���
���ز�����	Ӧ����ȷ:C_OK;		Ӧ�����:C_Error;
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 S_Encrypt_RN_MAC_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucEncryptMode, uchar8 *pV_ucRN_Data, uchar8 *pV_ucMAC_Data)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	ushort16	V_usSendLen = 0;
	uchar8		V_ucReturnStatus = C_OK;
	ushort16	V_usReturnData;
	ushort16	V_usReceiveDataLen;

	memcpy(&V_ucDataBuffer[V_usSendLen], TB_Encrypt_Report_RN_MAC_698, CLen_TB_ESAM_4_698);
	V_usSendLen += CLen_TB_ESAM_4_698;

	PF_Ushort16ToBuffer2_698(&V_ucDataBuffer[V_usSendLen], pV_usLen);
	V_usSendLen += 2;

	memcpy(&V_ucDataBuffer[V_usSendLen], pV_ucAPDU, *pV_usLen);
	V_usSendLen += *pV_usLen;

	V_usReceiveDataLen = MaxLength_698;
	V_usReturnData = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveDataLen);
	if(V_usReturnData != C_Security_CommandOk)
	{
		if(V_usReturnData == C_Security_OverTime)
		{
			V_ucReturnStatus = C_RequestTimeOut_DAR;
		}
		else
		{
			V_ucReturnStatus = C_ESAMErr_DAR;
		}
	}
	else
	{
		memcpy( pV_ucRN_Data, &V_ucDataBuffer[0], C_RNLen);
		memcpy( pV_ucMAC_Data, &V_ucDataBuffer[C_RNLen], C_MACLen);

		*pV_usLen = V_usReceiveDataLen;
	}

	return V_ucReturnStatus;
}

/*******************************************************************************
����ԭ�ͣ�	uchar8 S_Encrypt_MAC_698(uchar8 *pV_ucAPDU,ushort16 *Len,uchar8 V_ucEncryptMode,uchar8 *pV_ucRN_Data,uchar8 *pV_ucMAC_Data)
����������	���ݼ���(�����ϱ�)
���������	 pV_ucAPDU:		����ܵ�APDU�׵�ַ
			pV_usLen:		��������ݳ���
			V_ucEncryptMode:�������ݼ��ܷ�ʽ:����+MAC;����;����+MAC
���������	pV_ucAPDU:		���ܺ������
			Len:		���ܺ�����ݳ���
���ز�����	Ӧ����ȷ:C_OK;		Ӧ�����:C_Error;
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 S_Encrypt_MAC_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucEncryptMode, uchar8 *pV_ucRN_Data, uchar8 *pV_ucMAC_Data)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	ushort16	V_usSendLen= 0;
	uchar8		V_ucReturnStatus = C_OK;
	ushort16	V_usReturnData;
	ushort16	V_usReceiveDataLen;

	memcpy(&V_ucDataBuffer[V_usSendLen], TB_Encrypt_Report_MAC_698, CLen_TB_ESAM_4_698);
	V_usSendLen += CLen_TB_ESAM_4_698;

	PF_Ushort16ToBuffer2_698(&V_ucDataBuffer[V_usSendLen], pV_usLen);
	V_usSendLen += 2;

	memcpy(&V_ucDataBuffer[V_usSendLen], pV_ucAPDU, *pV_usLen);
	V_usSendLen += *pV_usLen;


	V_usReceiveDataLen = MaxLength_698;
	V_usReturnData = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveDataLen);
	if(V_usReturnData != C_Security_CommandOk)
	{
		if(V_usReturnData == C_Security_OverTime)
		{
			V_ucReturnStatus = C_RequestTimeOut_DAR;
		}
		else
		{
			V_ucReturnStatus = C_ESAMErr_DAR;
		}
	}
	else
	{
/*      memcpy( pV_ucRN_Data,&V_ucDataBuffer[0], C_RNLen);
        memcpy( pV_ucMAC_Data,&V_ucDataBuffer[C_RNLen], C_MACLen);
        *Len = V_usReceiveDataLen;*/
    }

	return V_ucReturnStatus;
}


/*******************************************************************************
����ԭ�ͣ�	ushort16	S_InitMoney_698(uchar8 *pV_ucData,ushort16 *pV_usLen)
����������	Զ�̳�ʼ��Ǯ����ȫģ��ӿں���
���������	*pV_ucData				:Զ�̳�ʼ��Ǯ���ļ�������:��ʽ4�ֽ�Ԥ�ý��+SID_MAC(���ݳ��Ȳ��̶�)
			pV_usLen				:���ݳ���
���������	��
���ز�����	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
����λ�ã�
��    ע��	���ݽṹ Ԥ�ý��+SID_MAC
			ͨ�ŷ��͵����ݸ�ʽ: 	XXXXXXXX(Ԥ�ý��)+XXXXXXXX(��ʶ)+xx(�������ݳ���)+XX...XX(��������)+xx(MAC����)+XX...XX(MAC)
			02 (�ṹ��)
			02
			06
			00 00 30 39 (Ԥ�ý��)
			5E ��SID-MAC��
			81 3E 00 00 (��ʶ)
			03
			00 09 10 ���������ݣ�
			04
			64 5B 4C 97 ��MAC��
			���͸�ESAM�ĸ�ʽ:		XXXXXXXX(��ʶ)+XX...XX(��������)+XXXXXXXX(Ԥ�ý��)+XX...XX(MAC)
*******************************************************************************/
ushort16	S_InitMoney_698(uchar8 *pV_ucData, ushort16 *pV_usLen)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	uchar8		V_ucMoneyLen,V_ucMoneyOffset;
	uchar8		V_ucAttachDataLen,V_ucAttachDataOffset;
	uchar8		V_ucMACLen,V_ucMACOffset;
	uchar8		V_ucSIDLen,V_ucSIDOffset;
	ushort16	V_usSendLen,V_usReceiveLen;
	ushort16	V_usReturnData16;

	/*Ԥ�ý��*/
	V_ucMoneyOffset = 3;
	V_ucMoneyLen = C_PreSetMoney_len_698;
	PF_OneDataReversed(pV_ucData + V_ucMoneyOffset, (uchar8 *)&(MoneyClient_Table.V_ulMoney), V_ucMoneyLen);

	if(MoneyClient_Table.V_ulMoney > C_MoneyLimit)
	{
		return C_RechargeHoarding_DAR;
	}

	/*�ж��Ƿ���˽Կ״̬*/
	if(InF_JudgeKeyStatus() == C_StateOfOfficialKey)
	{
		return(C_OtherErr_DAR);
	}

	/*(��ʶ)*/
	V_ucSIDOffset = 3 + V_ucMoneyLen + C_len_698;
	V_ucSIDLen = C_DataID_Length_698;

	/*������Ϣ*/
	V_ucAttachDataLen = pV_ucData[V_ucSIDOffset + V_ucSIDLen];
	V_ucAttachDataOffset = V_ucSIDOffset + V_ucSIDLen + C_len_698;

	/*MAC*/
	V_ucMACLen = pV_ucData[V_ucAttachDataOffset + V_ucAttachDataLen];
	V_ucMACOffset = V_ucAttachDataOffset + V_ucAttachDataLen + C_len_698;

	/*��ֵ����*/
	/*��ʶ*/
	PF_CopyDataBytes(pV_ucData + V_ucSIDOffset, V_ucDataBuffer, V_ucSIDLen);

	/*��������*/
	PF_CopyDataBytes(pV_ucData + V_ucAttachDataOffset, V_ucDataBuffer + C_DataID_Length_698, V_ucAttachDataLen);/*��������*/

	/*Ԥ�ý��*/
	PF_CopyDataBytes(pV_ucData + V_ucMoneyOffset, V_ucDataBuffer + C_DataID_Length_698 + V_ucAttachDataLen, V_ucMoneyLen);

	/*MAC*/
	PF_CopyDataBytes(pV_ucData + V_ucMACOffset, V_ucDataBuffer + C_DataID_Length_698+V_ucAttachDataLen + C_PreSetMoney_len_698, V_ucMACLen);

	/*���㷢�����ݳ���*/
	V_usSendLen = C_DataID_Length_698 + V_ucAttachDataLen + C_PreSetMoney_len_698 + V_ucMACLen;

	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		if( (V_usReturnData16 == C_Security_SafetyDataIncorrect) || (V_usReturnData16 == C_Security_MacErr) )
		{
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		return(C_ESAMErr_DAR);
	}


	/*********����Ϊ�÷��ز��� *********************************************************/
	*pV_usLen = V_usReceiveLen;
	PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucData, *pV_usLen);	/*Ӧ��APDU*/

	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�	ushort16  S_DataExcerption_698(uchar8 *pV_ucData,ushort16 *pV_ucLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen)
����������	��ȡESAM�ļ�(���ݻس�)
���������	*pV_ucData:				�س���ʶ���̶�8�ֽ�
			*pV_ucLen				���ٵĻ������ĳ���
���������	*pV_ucDataOutBuf:		�س�����(�س���ʶ8+�س�����Ld+Mac 4
			*pV_usDataOutLen		��������ʵ�ʳ���
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��	������ע	����ǰ��֤p_Dataָ�����ݹ̶�8�ֽ�
			ͨ�ŷ��͵����ݸ�ʽ: 	XXXXXXXX(��ʶ)+xx(�������ݳ���)+XX...XX(��������)
			���͸�ESAM�ĸ�ʽ:		XXXXXXXX(��ʶ)+XX...XX(��������)
*******************************************************************************/
ushort16  S_DataExcerption_698(uchar8 *pV_ucData, ushort16 *pV_usLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	uchar8		V_ucAttachDataLen,V_ucAttachDataOffset;
	ushort16	V_usSendLen,V_usReceiveLen;
	ushort16	V_usReturnData16,V_usDataOff;

	/*��ʶ*/
	PF_CopyDataBytes(&pV_ucData[C_len_698], V_ucDataBuffer, C_DataID_Length_698);

	/*��������*/
	V_ucAttachDataLen = *( pV_ucData + C_len_698 + C_DataID_Length_698);	/*�������ݳ���*/
	V_ucAttachDataOffset = C_DataID_Length_698 + C_len_698 + C_len_698;
	PF_CopyDataBytes(pV_ucData + V_ucAttachDataOffset, V_ucDataBuffer + C_DataID_Length_698, V_ucAttachDataLen);	/*��������*/


	/*���㷢�����ݳ���*/
	V_usSendLen = C_DataID_Length_698 + V_ucAttachDataLen;

	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		if((V_usReturnData16 == C_Security_SafetyDataIncorrect) || (V_usReturnData16 == C_Security_MacErr) )
		{
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}

		return(C_ESAMErr_DAR);
	}

/*********����Ϊ�÷��ز��� *********************************************************/
	pV_ucDataOutBuf[0] = C_octet_string;
	V_usDataOff = 1;

	if(V_usReceiveLen > 255)
	{
		if( (V_usReceiveLen + 4) > *pV_usDataOutLen)
		{
			return C_DataLenError;
		}
		else
		{
			pV_ucDataOutBuf[V_usDataOff] = 0x82;
			PF_Ushort16ToBuffer2_698(&pV_ucDataOutBuf[V_usDataOff + 1], &V_usReceiveLen);
			V_usDataOff = V_usDataOff + 3;
		}
	}
	else if(V_usReceiveLen > 127)
	{
		if( (V_usReceiveLen + 3) > *pV_usDataOutLen)
		{
			return C_DataLenError;
		}
		else
		{
			pV_ucDataOutBuf[V_usDataOff + 0] = 0x81;
			pV_ucDataOutBuf[V_usDataOff + 1] = (uchar8)V_usReceiveLen;
			V_usDataOff = V_usDataOff + 2;
		}
	}
	else
	{
		if( (V_usReceiveLen + 2) > *pV_usDataOutLen)
		{
			return C_DataLenError;
		}
		else
		{
			pV_ucDataOutBuf[V_usDataOff] = (uchar8)V_usReceiveLen;
			V_usDataOff++;
		}
	}

	PF_CopyDataBytes_698(V_ucDataBuffer, &pV_ucDataOutBuf[V_usDataOff], V_usReceiveLen);	/*Ӧ��APDU*/
	V_usDataOff += V_usReceiveLen;

	*pV_usDataOutLen = V_usDataOff;

	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�	ushort16  S_WritePara_PlainTextMAC_698(uchar8 *pV_ucData, ushort16 *pV_usLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen)
����������	1�����Mac��֤��ESAM��Ӧ����д
���������	*pV_ucData:	�������(���ݸ�����Ϣ+��������D1+SID_MAC) ע:���ݳ��Ȳ��̶�
			pV_usLen		�������ݵĳ���(����Mac)
			--------------------------------
			���ñ��
			0D
			40 02 02 00 08 00 00 00 00 00 00 00 00
			04
			80 2A 00 01
			06
			00 15 40 01 00 00
			04
			63 2A 1E A3
			00
			���û��������
			08
			40 1C 02 00 03 00 00 10
			04
			81 2A 00 04
			05
			00 0A 40 00 18
			04
			BC 70 41 33
			00
���������	pV_ucDataOutBuf���������
			pV_usDataOutLen��������ݳ���
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��	P_Data�������е�����ʱ�����ġ�
			ͨ�ŷ��͵����ݸ�ʽ: 	xx(��������)+XX...XX(��������)+XXXXXXXX(��ʶ)+xx(�������ݳ���)+XX...XX(��������)+xx(MAC����)+XX...XX(MAC)
			���͸�ESAM�ĸ�ʽ:		XXXXXXXX(��ʶ)+XX...XX(��������)+XX...XX(��������)+XX...XX(MAC)
*******************************************************************************/
ushort16  S_WritePara_PlainTextMAC_698(uchar8 *pV_ucData, ushort16 *pV_usLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	uchar8		V_ucParaOffset;
	ushort16	V_usParaLen;
	uchar8		V_ucAttachDataLen,V_ucAttachDataOffset;
	uchar8		V_ucMACLen,V_ucMACOffset;
	uchar8		V_ucSIDLen,V_ucSIDOffset;
	ushort16	V_usSendLen,V_usReceiveLen;
	ushort16	V_usReturnData16;
	uchar8		V_ucOID[4];
	ulong32		V_ulOID;
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucReturnData,DataLen;
	uchar8		V_ucOffsetInOP;
	uchar8		V_ucParmPlainText_O;
	ulong32		V_ulDataTemp;
	uchar8		V_ucNum,i,V_ucTime[7];

	/*ƫ�ƺͳ���*/
	/*����*/
	if(pV_ucData[0] & 0x80)
	{
		if( (pV_ucData[0] & 0x7F) == 2)
		{
			V_ucParaOffset = 3;
			V_usParaLen = PF_Buffer2ToLong16_698(&pV_ucData[V_ucParaOffset - 2]);
		}
		else	/*���ʱ����*/
		{
			V_ucParaOffset = 2;
			V_usParaLen = pV_ucData[V_ucParaOffset - 1];
		}
	}
	else
	{
		V_ucParaOffset = 1;
		V_usParaLen = pV_ucData[V_ucParaOffset - 1];
	}
	PF_CopyDataBytes(pV_ucData + V_ucParaOffset, V_ucOID, 4);
	V_ulOID = PF_Buffer4ToUlong32_698(V_ucOID);

	#if 0
	/*���ر���������÷��ʺͽ��ݱ�*/
	if(C_Meter_Type != C_L_SmartMeter)
	{
		switch(V_ulOID &0xFFFFFF00)
		{
				case		0x401e0200:				/*�������*/
				case		CChange_Rate:			/*���׷��ʵ���л�ʱ��*/
				case		CChange_Ladder:			/*���׽��ݵ���л�ʱ��*/
				case		CCurrent_RateFF_Price:	/*��ǰ�׷��ʱ�*/
				case		CBackUp_RateFF_Price:	/*�����׷��ʱ�*/
				case		CCurrent_Ladder_Table: 	/*��ǰ�׽��ݱ�*/
				case		CBackUp_Ladder_Table: 	/*�����׽��ݱ�*/
					return(C_ObjectNotExist_DAR);
				default:
					break;					/*ע��������break������һ���ж�*/
		}
	}
	if(InF_JudgeKeyStatus() == C_StateOfOfficialKey)	/*˽Կ�²��������ñ�š��ͻ����*/
	{
		if( (V_ulOID == CCustomer_Num) || (V_ulOID == CMeter_Num) )
		{
			return(C_RWForbid_DAR);
		}
	}
	#endif

	if( (V_ucOID[0] == 0x40) && (V_ucOID[1] == 0x02) )		/*���ñ��*/
	{
		/*����*/
		V_ucParaOffset = C_len_698;
		V_usParaLen = pV_ucData[V_ucParaOffset - C_len_698];
		/*SID���ȼ�ƫ��*/
		V_ucSIDOffset = C_len_698 + V_usParaLen + V_ucParaOffset;
		V_ucSIDLen = pV_ucData[V_usParaLen + V_ucParaOffset];
		/*������Ϣ*/
		V_ucAttachDataLen = pV_ucData[V_ucSIDLen + V_ucSIDOffset];
		V_ucAttachDataOffset = C_len_698 + V_ucSIDOffset + V_ucSIDLen;
		/*MAC*/
		V_ucMACLen = pV_ucData[V_ucAttachDataOffset + V_ucAttachDataLen];
		V_ucMACOffset = C_len_698 + V_ucAttachDataOffset + V_ucAttachDataLen;
	}
	else
	{
		/*����*/
		V_ucParaOffset += 5;
		V_usParaLen = pV_ucData[V_ucParaOffset - C_len_698];
		/*SID���ȼ�ƫ��*/
		V_ucSIDOffset = C_len_698 + V_usParaLen + V_ucParaOffset;
		V_ucSIDLen = pV_ucData[V_usParaLen + V_ucParaOffset];
		/*������Ϣ*/
		V_ucAttachDataLen = pV_ucData[V_ucSIDLen + V_ucSIDOffset];
		V_ucAttachDataOffset = C_len_698 + V_ucSIDOffset + V_ucSIDLen;
		/*MAC*/
		V_ucMACLen = pV_ucData[V_ucAttachDataOffset + V_ucAttachDataLen];
		V_ucMACOffset = C_len_698 + V_ucAttachDataOffset + V_ucAttachDataLen;
	}
	/*��ʶ*/
	PF_CopyDataBytes(pV_ucData + V_ucSIDOffset, V_ucDataBuffer, V_ucSIDLen);
	/*��������*/
	PF_CopyDataBytes(pV_ucData + V_ucAttachDataOffset, V_ucDataBuffer + V_ucSIDLen, V_ucAttachDataLen);	/*��������*/
	/*����*/
	PF_CopyDataBytes_698(pV_ucData + V_ucParaOffset, V_ucDataBuffer + V_ucSIDLen + V_ucAttachDataLen, V_usParaLen);	/*��������*/
	/*MAC*/
	PF_CopyDataBytes(pV_ucData + V_ucMACOffset, V_ucDataBuffer + V_ucSIDLen + V_ucAttachDataLen + V_usParaLen, V_ucMACLen);

	/*���㷢�����ݳ���*/
	V_usSendLen = V_ucSIDLen + V_ucAttachDataLen + V_usParaLen + V_ucMACLen;

	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		if( (V_usReturnData16 == C_Security_SafetyDataIncorrect) || (V_usReturnData16 == C_Security_MacErr) )
		{
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		return(C_ESAMErr_DAR);
	}



	/*********����д������Ϣ�ļ�*********************************************************/

	/*���Ȳ��ȷ���ڱ��TB_ParmPlainText��ƫ��,�Ҳ������������˳�*/
	if(LookForStr_ParmPlainText(V_ulOID,&V_ucParmPlainText_O) == C_OK)
	{
		V_ucOffsetInOP = TB_ParmPlainText[V_ucParmPlainText_O].OffsetInOP;
		/*�����Ҫд�����ļ�����д�����ļ�*/
		if(V_ucOffsetInOP != C_Invalid_Offset)
		{
			if(V_ulOID == CMeter_Num)
			{
				DataLen = V_usParaLen - 5 - 2;
				PF_CopyDataBytes_698(pV_ucData + V_ucParaOffset + 5 + 2, V_ucbuf, DataLen);	/*������Ϣ�ļ���ų���6�ֽڣ�ƫ��2�ֽڣ�ȥ�����λ*/
			}
			else
			{
				DataLen = V_usParaLen;
				PF_CopyDataBytes_698(pV_ucData + V_ucParaOffset, V_ucbuf, DataLen);	/*����*/
			}
			V_ucReturnData = WriteBinFile(C_ESAM, V_ucbuf, C_F_OpInfo, V_ucOffsetInOP, DataLen);
			if(V_ucReturnData != C_OK)
			{
				return(C_SERR_OtherErr);
			}
		}
	}


	/*********����Ϊ�÷��ز��� *********************************************************/
	if(V_ulOID == CMeter_Num)	/*�������*/
	{
		*pV_usDataOutLen = V_usParaLen - 5;
		PF_OneDataReversed(pV_ucData + V_ucParaOffset + 5, pV_ucDataOutBuf, *pV_usDataOutLen);
	}
	else if(V_ulOID == CCustomer_Num) 	/*�ͻ����*/
	{
		*pV_usDataOutLen = V_usParaLen;
		PF_OneDataReversed(pV_ucData + V_ucParaOffset, pV_ucDataOutBuf, *pV_usDataOutLen);
	}
	else if( (V_ulOID == CRatio_Curr_Tran) || (V_ulOID == CRatio_Vol_Tran) )	/*���������*/
	{
		/*3�ֽ�BCDת4�ֽڵ�hex*/
		*pV_usDataOutLen = 4;

		PF_OneDataReversed(pV_ucData + V_ucParaOffset, pV_ucDataOutBuf, V_usParaLen);
		PF_BCDtoHexBytes(pV_ucDataOutBuf, &V_ulDataTemp, V_usParaLen);
		PF_Ulong32ToBuffer4(pV_ucDataOutBuf, &V_ulDataTemp, 4);

	}
	else if(V_ulOID == CAlam_Money) 	/*��������*/
	{
		/*4�ֽ�BCDת4�ֽ�hex��2�Σ�*/
		*pV_usDataOutLen = 8;

		PF_OneDataReversed(pV_ucData + V_ucParaOffset, pV_ucDataOutBuf, 4);
		PF_BCDtoHexBytes(pV_ucDataOutBuf, &V_ulDataTemp, 4);
		PF_Ulong32ToBuffer4(pV_ucDataOutBuf, &V_ulDataTemp, 4);

		PF_OneDataReversed(pV_ucData + V_ucParaOffset + 4, pV_ucDataOutBuf + 4, 4);
		PF_BCDtoHexBytes(pV_ucDataOutBuf + 4, &V_ulDataTemp, 4);
		PF_Ulong32ToBuffer4(pV_ucDataOutBuf + 4, &V_ulDataTemp, 4);

	}
	else if( (V_ulOID == CChange_Rate) || (V_ulOID == CChange_Ladder) )		/*�л�ʱ��*/
	{
		*pV_usDataOutLen = 7;

		memcpy(&V_ucTime[1], pV_ucData + V_ucParaOffset, 5);

		if(PF_Is_Buf_AllFixedData(&V_ucTime[1],0x00,5) == C_OK)	/*ȫ0*/
		{
			*pV_ucDataOutBuf = 0xFF;	/*��Ĭ��FF*/
			memset(pV_ucDataOutBuf + 1, 0x00, 6);
		}
		else if(PF_Is_Buf_AllFixedData(&V_ucTime[1],0xFF,5) == C_OK)	/*ȫFF*/
		{
			*pV_ucDataOutBuf = 0xFF;	/*��Ĭ��FF*/
			memset(pV_ucDataOutBuf + 1, 0xFF, 6);
		}
		else if(PF_Is_Buf_AllFixedData(&V_ucTime[1],0x99,5) == C_OK)	/*ȫ99*/
		{
			*pV_ucDataOutBuf = 0xFF;	/*��Ĭ��FF*/
			memset(pV_ucDataOutBuf + 1, 0x63, 6);	/*99ת����0x63д�����ݲ�*/
		}
		else	/*�Ϸ�����ʱ��*/
		{
			/*5�ֽ�BCD���ת����7�ֽ�data_time_s*/
			PF_OneDataReversed(pV_ucData + V_ucParaOffset, &V_ucTime[1], 5);
			V_ucTime[0] = 0xFF;	/*��Ĭ��FF*/
			V_ucTime[6] = 0x20;

			*pV_ucDataOutBuf = V_ucTime[0];
			*(pV_ucDataOutBuf + 1) = PF_BCDtoHexOneByte(V_ucTime[1]);
			*(pV_ucDataOutBuf + 2) = PF_BCDtoHexOneByte(V_ucTime[2]);
			*(pV_ucDataOutBuf + 3) = PF_BCDtoHexOneByte(V_ucTime[3]);
			*(pV_ucDataOutBuf + 4) = PF_BCDtoHexOneByte(V_ucTime[4]);

			PF_BCDtoHexBytes(&V_ucTime[5], &V_ulDataTemp, 2);
			PF_Ulong32ToBuffer4(pV_ucDataOutBuf + 5, &V_ulDataTemp, 2);
		}
	}
	else if(V_ulOID == CBackUp_RateFF_Price)	/*�����׷��ʵ�����ݿ�*/
	{

		*pV_usDataOutLen = V_usParaLen;

		V_ucNum = V_usParaLen / 4;	/*�����˼�������*/

		for(i = 0; i < V_ucNum; i++)
		{
			PF_OneDataReversed(pV_ucData + V_ucParaOffset + 4 * i, pV_ucDataOutBuf + 4 * i, 4);
			PF_BCDtoHexBytes(pV_ucDataOutBuf  + 4 * i, &V_ulDataTemp, 4);
			PF_Ulong32ToBuffer4(pV_ucDataOutBuf + 4 * i, &V_ulDataTemp, 4);

		}
		if(*pV_usDataOutLen > CLBackUp_RateFF_Price)
		{
			*pV_usDataOutLen = CLBackUp_RateFF_Price;
		}
	}
	else if(V_ulOID == CBackUp_Ladder_Table)	/*�����׽��ݵ�����ݿ飨55�ֽڣ�*/
	{

		*pV_usDataOutLen = V_usParaLen;

		V_ucNum = 6 + 7;	/*6�����ݺ�7�����ݵ��*/
		for(i = 0; i < V_ucNum; i++)
		{
			PF_OneDataReversed(pV_ucData + V_ucParaOffset + 4 * i, pV_ucDataOutBuf + 4 * i, 4);
			PF_BCDtoHexBytes(pV_ucDataOutBuf + 4 * i, &V_ulDataTemp, 4);
			PF_Ulong32ToBuffer4(pV_ucDataOutBuf + 4 * i, &V_ulDataTemp, 4);
		}

		/*�¡��ա�ʱת����*/
		V_ucNum = 4;	/*4��������*/

		for(i = 0; i < V_ucNum; i++)
		{
			if(*(pV_ucData + V_ucParaOffset+ 4 * 13 + i * 3) != 0xFF)
			{
				*(pV_ucDataOutBuf + 4 * 13 + i * 3) = PF_BCDtoHexOneByte(*(pV_ucData + V_ucParaOffset+ 4 * 13 + i * 3) );
			}
			else
			{
				*(pV_ucDataOutBuf + 4 * 13 + i * 3) = 0xFF;
			}

			if(*(pV_ucData + V_ucParaOffset + 4 * 13 + i * 3 + 1) != 0xFF)
			{
				*(pV_ucDataOutBuf + 4 * 13 + i * 3 + 1) = PF_BCDtoHexOneByte(*(pV_ucData + V_ucParaOffset + 4 * 13 + i * 3 + 1) );
			}
			else
			{
				*(pV_ucDataOutBuf + 4 * 13 + i * 3 + 1) = 0xFF;
			}

			if(*(pV_ucData + V_ucParaOffset + 4 * 13 + i * 3 + 2) != 0xFF)
			{
				*(pV_ucDataOutBuf + 4 * 13 + i * 3 + 2) = PF_BCDtoHexOneByte(*(pV_ucData + V_ucParaOffset + 4 * 13 + i * 3 + 2) );
			}
			else
			{
				*(pV_ucDataOutBuf + 4 * 13 + i * 3 + 2) = 0xFF;
			}
		}

	}
	else	/*�������ᵽ��������*/
	{
		*pV_usDataOutLen = V_usReceiveLen;
		PF_CopyDataBytes_698(pV_ucDataOutBuf, pV_ucData, *pV_usDataOutLen);	/*Ӧ��APDU*/

	}


	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�	ushort16  S_Key_Update_698(uchar8 *pV_ucData,ushort16 *pV_ucLen)
����������	�����Կ���£���Կ״̬����ˢ��
���������	pV_ucData:	���������׵�ַ����ʽ(����+SID_MAC) ���Ȳ��̶�
���������	pV_ucData��	�������
			pV_ucLen��	������ݳ���
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��	P_Data�������ޱ仯���жϱ�ʶ��Ϊ812E0000
			ͨ�ŷ��͵����ݸ�ʽ: 	xx(��Կ���ĳ���)+XX...XX(��Կ��������)+XXXXXXXX(��ʶ)+xx(�������ݳ���)+XX...XX(��������)+xx(MAC����)+XX...XX(MAC)
			���͸�ESAM�ĸ�ʽ:		XXXXXXXX(��ʶ)+XX...XX(��������)+XX...XX(��������)+XX...XX(MAC)
*******************************************************************************/
ushort16  S_Key_Update_698(uchar8 *pV_ucData, ushort16 *pV_usLen)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	ushort16	V_usParaLen,V_usParaOffset;
	ushort16	V_usAttachDataLen,V_usAttachDataOffset;
	ushort16	V_usMACLen,V_usMACOffset;
	ushort16	V_usSIDOffset,V_usSIDLen;
	ushort16	V_usSendLen,V_usReceiveLen;
	ushort16	V_usReturnData16;
	ulong32		V_ulDataID;

	/*ƫ�ƺͳ���*/
	/*����*/
	if(pV_ucData[0] & 0x80)
	{
		if((pV_ucData[0] & 0x7F) == 2)
		{
			V_usParaOffset = 3;
			V_usParaLen = PF_Buffer2ToLong16_698(&pV_ucData[V_usParaOffset - 2]);
		}
		else
		{
			V_usParaOffset = 2;
			V_usParaLen = pV_ucData[V_usParaOffset - 1];
		}
	}
	else
	{
		V_usParaOffset = 1;
		V_usParaLen = pV_ucData[V_usParaOffset - 1];
	}
	/*SID���ȼ�ƫ��*/
	V_usSIDOffset = C_len_698 + V_usParaLen + V_usParaOffset;
	V_usSIDLen = pV_ucData[V_usParaLen + V_usParaOffset];
	/*������Ϣ*/
	V_usAttachDataLen = pV_ucData[V_usSIDLen + V_usSIDOffset];
	V_usAttachDataOffset = C_len_698 + V_usSIDOffset + V_usSIDLen;
	/*MAC*/
	V_usMACLen = pV_ucData[V_usAttachDataOffset + V_usAttachDataLen];
	V_usMACOffset = C_len_698 + V_usAttachDataOffset + V_usAttachDataLen;

	/*��������*/
	/*��ʶ*/
	PF_CopyDataBytes_698(pV_ucData + V_usSIDOffset, V_ucDataBuffer, V_usSIDLen);
	PF_CopyDataBytes_698(pV_ucData + V_usSIDOffset, (uchar8 *)&V_ulDataID, C_DataID_Length_698);

	if(V_ulDataID != 0x00002E81)	/*0x812E0000�ߵ�*/
	{
		return(C_OtherErr_DAR);
	}

	/*��������*/
	PF_CopyDataBytes_698(pV_ucData + V_usAttachDataOffset, V_ucDataBuffer + C_DataID_Length_698, V_usAttachDataLen);	/*��������*/
	/*����*/
	PF_CopyDataBytes_698(pV_ucData + V_usParaOffset, V_ucDataBuffer + C_DataID_Length_698 + V_usAttachDataLen, V_usParaLen);
	/*MAC*/
	PF_CopyDataBytes_698(pV_ucData + V_usMACOffset, V_ucDataBuffer + C_DataID_Length_698 + V_usAttachDataLen + V_usParaLen, V_usMACLen);

	/*���㷢�����ݳ���*/
	V_usSendLen = C_DataID_Length_698 + V_usAttachDataLen + V_usParaLen + V_usMACLen;

	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		if( (V_usReturnData16 == C_Security_SafetyDataIncorrect) || (V_usReturnData16 == C_Security_MacErr) )
		{
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		return(C_ESAMErr_DAR);
	}


	/*********����Ϊ�÷��ز��� *********************************************************/
	*pV_usLen = V_usReceiveLen;
	PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucData, *pV_usLen);	/*Ӧ��APDU*/

	return(C_OK);
}



/*******************************************************************************
����ԭ�ͣ�	ushort16  S_IR_ID_Request(uchar8 *pV_ucData, ushort16 *pV_ucLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen, uchar8 V_ucClientAddr)
����������	������֤����
���������	pV_ucData:		���������׵�ַ����ʽ(����+SID_MAC) ���Ȳ��̶�
			pV_usLen���������ݳ���
			V_ucClientAddr���ն˵�ַ������վ��ַ
���������	pV_ucDataOutBuf���������
			pV_usDataOutLen��������ݳ���
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��	P_Data�������ޱ仯���жϱ�ʶ��Ϊ812E0000
			ͨ�ŷ��͵����ݸ�ʽ: 	RN(����)+XX...XX(��Կ��������)
			���͸�ESAM�ĸ�ʽ:		800808030010+���+RN1
			����:		0X10+ENDATA1+0X08+RN2
*******************************************************************************/
ushort16  S_IR_ID_Request(uchar8 *pV_ucData, ushort16 *pV_usLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen, uchar8 V_ucClientAddr)
{
	uchar8		V_ucDataBuffer[MaxLength_698], V_ucReturnData, V_ucbuf[16], V_ucoffset;
	ushort16	V_usReceiveLen, V_usReturnData16, V_usSendLen;
	uchar8 		V_ucAuthSessionLen;
	uchar8		V_ucMeterNo[8], V_ucEsamno[8], V_ucRN1Encode[16], V_ucRN2[16];
	uchar8		V_ucReturnData8;
	ushort16	V_usDataEnCode, V_usDataLen;

	if(V_ucClientAddr == Termal_Address)	/*�ն������֤*/
	{
		PF_CopyDataBytes((uchar8 * )TB_IR_ID_Request_698_Termal, V_ucDataBuffer, CLen_TB_ESAM_6_698);

		/*�������*/
		V_usDataLen = CLMeter_Num;
		V_ucReturnData = InF_Read_Data(CMeter_Num, &V_ucbuf[0], &V_usDataLen, &V_usDataEnCode);		/*�����*/
		if(V_ucReturnData != C_OK)
		{
			return(C_OtherErr_DAR);
		}
		PF_OneDataReversed(&V_ucbuf[0], &V_ucMeterNo[0], CLMeter_Num);				/*�������ı����Ҫ�ߵ�ʹ��*/


		/*����RN*/
		V_ucAuthSessionLen = *(pV_ucData + 1);
		PF_CopyDataBytes(&pV_ucData[C_len_698 + 1], &V_ucDataBuffer[CLen_TB_ESAM_6_698 ], V_ucAuthSessionLen);
		/********* ���·���esam���� *********************************************************/
		V_usSendLen = CLen_TB_ESAM_6_698 + V_ucAuthSessionLen;		/*�������ݳ���*/
	}
	else
	{
		PF_CopyDataBytes( (uchar8 * )TB_IR_ID_Request_698, V_ucDataBuffer, CLen_TB_ESAM_6_698);
		/*�������*/
		V_usDataLen = CLMeter_Num;
		V_ucReturnData = InF_Read_Data(CMeter_Num, &V_ucbuf[0], &V_usDataLen, &V_usDataEnCode);		/*�����*/
		if(V_ucReturnData != C_OK)
		{
			return(C_OtherErr_DAR);
		}
		PF_OneDataReversed(&V_ucbuf[0], &V_ucMeterNo[0], CLMeter_Num);				/*�������ı����Ҫ�ߵ�ʹ��*/
		PF_CopyDataBytes(&V_ucMeterNo[0], &V_ucDataBuffer[CLen_TB_ESAM_6_698], CLMeter_Num);

		/*����RN*/
		V_ucAuthSessionLen = *(pV_ucData + 1);
		PF_CopyDataBytes(&pV_ucData[C_len_698 + 1], &V_ucDataBuffer[CLen_TB_ESAM_6_698 + CLMeter_Num], V_ucAuthSessionLen);

		/********* ���·���esam���� *********************************************************/
		V_usSendLen = CLen_TB_ESAM_6_698 + CLMeter_Num + V_ucAuthSessionLen;	/*�������ݳ���*/
	}
	V_usReceiveLen = MaxLength_698;	/*����������󳤶�*/
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SCErr_DAR);
	}
	if(V_usReceiveLen != (IRidRequestData1Len_698) )	/*����8���ֽ�����*/
	{
		return(C_SCErr_DAR);
	}
	PF_CopyDataBytes(V_ucDataBuffer, &V_ucRN1Encode[0], IRidRequestData1Len_698);	/*Ӧ��APDU*/

	/********* ���·���esam���� *********************************************************/
	PF_CopyDataBytes((uchar8 * )TB_IR_ID_Request2_698, V_ucDataBuffer, CLen_TB_ESAM_6_698);
	V_usSendLen = CLen_TB_ESAM_6_698;	/*�������ݳ���	*/
	V_usReceiveLen = MaxLength_698;		/*����������󳤶�*/
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SCErr_DAR);
	}
	if(V_usReceiveLen != (IRidRequestData2Len_698) )	/*����8���ֽ�RN*/
	{
		return(C_SCErr_DAR);
	}
	PF_CopyDataBytes(V_ucDataBuffer, &V_ucRN2[0], IRidRequestData2Len_698);	/*Ӧ��APDU*/
	V_ucReturnData8 = S_ReadEsam_698(V_ucEsamno, &V_usReceiveLen, 0x0200);	/*��esam���к�*/
	if(V_ucReturnData8 != C_OK)
	{
		return(C_OtherErr_DAR);
	}

	/*********����Ϊ�÷��ز��� *********************************************************/
	V_ucDataBuffer[0] = C_structure;
	V_ucDataBuffer[1] = 4;
	/*���*/
	V_ucDataBuffer[2] = C_octet_string;
	V_ucDataBuffer[3] = CLMeter_Num;
	V_ucoffset = 4;
	PF_CopyDataBytes(&V_ucMeterNo[0], &V_ucDataBuffer[V_ucoffset] , CLMeter_Num);
	V_ucoffset += CLMeter_Num;
	/*esam���к�*/
	V_ucDataBuffer[V_ucoffset] = C_octet_string;
	V_ucoffset += 1;
	V_ucDataBuffer[V_ucoffset] = 8;
	V_ucoffset += 1;
	PF_CopyDataBytes(&V_ucEsamno[0], &V_ucDataBuffer[V_ucoffset], 8);
	V_ucoffset += 8;
	/*RN1����*/
	V_ucDataBuffer[V_ucoffset] = C_octet_string;
	V_ucoffset +=1;
	V_ucDataBuffer[V_ucoffset]= IRidRequestData1Len_698;
	V_ucoffset += 1;
	PF_CopyDataBytes(&V_ucRN1Encode[0], &V_ucDataBuffer[V_ucoffset], IRidRequestData1Len_698);
	V_ucoffset += IRidRequestData1Len_698;
	/*RN2*/
	V_ucDataBuffer[V_ucoffset] = C_RN;
	V_ucoffset += 1;
	V_ucDataBuffer[V_ucoffset] = IRidRequestData2Len_698;
	V_ucoffset += 1;
	PF_CopyDataBytes(&V_ucRN2[0], &V_ucDataBuffer[V_ucoffset], IRidRequestData2Len_698);
	V_ucoffset += IRidRequestData2Len_698;


	if(*pV_usDataOutLen < V_ucoffset)
	{
		return(C_DataLenError);		/*��ʾ���ݳ��ȴ�*/
	}
	else
	{
		*pV_usDataOutLen = V_ucoffset;
		memcpy(pV_ucDataOutBuf, V_ucDataBuffer, *pV_usDataOutLen);
	}

	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�	ushort16  S_IR_ID(uchar8 *pV_ucData,ushort16 *pV_ucLen)
����������	������֤
���������	pV_ucData:	���������׵�ַ����ʽ(����+SID_MAC) ���Ȳ��̶�
���������	pV_usLen��	�������ݳ���
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��	pV_ucData�������ޱ仯���жϱ�ʶ��Ϊ812E0000
			ͨ�ŷ��͵����ݸ�ʽ: 	RN(����)+XX...XX(��Կ��������)
			���͸�ESAM�ĸ�ʽ:		800808030010+���+RN1
			����:		0X10+ENDATA1+0X08+RN2
*******************************************************************************/
ushort16  S_IR_ID(uchar8 *pV_ucData, ushort16 *pV_usLen)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	ushort16	V_usReceiveLen, V_usReturnData16, V_usSendLen;
	uchar8		V_ucAuthSessionLen;

	PF_CopyDataBytes((uchar8 * )TB_IR_ID_698, V_ucDataBuffer, CLen_TB_ESAM_6_698);
	/*����RN*/
	V_ucAuthSessionLen = *(pV_ucData + 1);
	PF_CopyDataBytes(&pV_ucData[C_len_698 + 1], &V_ucDataBuffer[CLen_TB_ESAM_6_698], V_ucAuthSessionLen);

	/********* ���·���esam���� *********************************************************/
	V_usSendLen = CLen_TB_ESAM_6_698 + V_ucAuthSessionLen;	/*�������ݳ���*/
	V_usReceiveLen = MaxLength_698;		/*����������󳤶�*/
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		*pV_usLen = 0;
		return(C_SCErr_DAR);
	}

	*pV_usLen = 0;

	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�	ushort16	Comm_OpenChgBL_698()
����������	Զ�̿�������ֵ����Ľ���
���������	��
���������	��
���ز�����	��
����λ�ã�
��    ע��	�ڽ��뱾����֮ǰ�����ж�200�ι��������֤��ЧȨ��
			����������ͨ��Զ�̿����ͳ�ֵ2������Ľ�������
*******************************************************************************/
ushort16	Comm_OpenChgBL_698()
{
	ulong32		V_ulChargeBal_Hex_Cent;			/*��ֵ���*/
	ulong32		V_ulPC_Num;						/*�������*/
	ushort16	V_usReturn16 = C_OK;

	/*�ж��Ƿ���˽Կ״̬*/
	if(InF_JudgeKeyStatus() == C_StateOfTestKey)	/*����ȫ������˽Կ״̬	*/
	{
		return C_OtherErr_DAR;
	}

	/*����������͹�����ת����32λ16������*/
	V_ulChargeBal_Hex_Cent = MoneyClient_Table.V_ulMoney;
	V_ulPC_Num = MoneyClient_Table.V_ulBuyMoneyTime;

	/*�ж��Ƿ��ѿ���(Զ�̻򱾵�)*/
	if( (InF_DealWith_L_R_OAAFlag(C_Judge_Method_R, C_HaveOpenAnAccount) == C_HaveOpenAnAccount)
		|| (InF_DealWith_L_R_OAAFlag(C_Judge_Method_L, C_HaveOpenAnAccount) == C_HaveOpenAnAccount) )	/*Զ�̻򱾵��ѿ�����,�ȶԿͻ�����Ƿ�һ��*/
	{
		if(InF_Compare_CustomerNum(&MoneyClient_Table.V_ucClientNum[0]) != C_OK)
		{
			return C_CNMismatch_DAR;
		}
	}
	else	/*δ����*/
	{
		if(MoneyClient_Table.V_ucOpenFlag == 1)	/*δ����������Զ�̳�ֵ��Ӧ���ֵ������(����΢Ҳ�����)*/
		{
			return C_RechargeNumErr_DAR;
		}
	}
	/*����ǿ�������򹺵����ֻ����0��1*/
	if(MoneyClient_Table.V_ucOpenFlag == 0)
	{
		if(MoneyClient_Table.V_ulBuyMoneyTime > 1)	/*�������������0��1*/
		{
			return C_RechargeNumErr_DAR;
		}
	}

	/*�жϹ�������͹������Ƿ����㹺��������
	ֻ������������²Ž���Ǯ����ֵ����*/
	V_usReturn16 = InF_Judge_ChgBal_PC_Num(V_ulChargeBal_Hex_Cent, V_ulPC_Num);
	MoneyClient_Table.V_CanRecharge = V_usReturn16;

	switch(V_usReturn16)
	{
		case		C_Can_EPurchase:			/*���Գ�ֵ*/
			return C_OK;

		case		C_PC_Num_Equal:			/*����������*/
			if(MoneyClient_Table.V_ucOpenFlag == 0)	/*����ǿ�������򲻽��г�ֵ�жϣ�ֱ���˳�*/
			{
				return C_OK;
			}
			else	/*����Ϊ��ֵ���Ӧ���ظ���ֵ*/
			{
				return C_ReRecharge_DAR;
			}

		case		C_MeterPC_Num_Large:		/*���ڹ��������*/
			return C_ReRecharge_DAR;

		case		C_SERR_RechargeNumErr:		/*��ֵ������*/
			return C_RechargeNumErr_DAR;

		case		C_SERR_RechargeHoarding:		/*���糬�ڻ�*/
			return C_RechargeHoarding_DAR;

		default:	/*Զ�̳�ֵ�����˲�������ʾ��ʾ��*/

			return C_OtherErr_DAR;

	}

}


/*******************************************************************************
����ԭ�ͣ�uchar8		DV_Return_Money_698(uchar8 *pV_ucReturnMoney)
�����������˷ѽ����Ч���ж�
���������*pV_ucReturnMoney				:���յ�������֡
���������
���ز�����C_OK/C_OtherErr
����λ�ã�
��    ע��hex�����ұ���С��Ǯ�����
*******************************************************************************/
uchar8		DV_Return_Money_698(uchar8 *pV_ucReturnMoney)
{
	uchar8		V_ucReturnData;
	uchar8		V_ucChargeBal_Hex_Cent[CLChargeBal_Hex_Cent];
	ushort16	V_usDataLen;
	ushort16	V_usdataCode;

	/*ͬ�����ٶ����ݲ�ʣ�����Ϊͬ���У����ܻ���ESAMΪ׼���ۼ����ݲ�*/
	V_usDataLen = CLChargeBal_Hex_Cent;
	InF_GetData_ObjectManage(CChargeBal_Hex_Cent, V_ucChargeBal_Hex_Cent, &V_usDataLen, &V_usdataCode);
	/*�Ƚ�*/
	V_ucReturnData = PF_Campare_Data(&pV_ucReturnMoney[0], V_ucChargeBal_Hex_Cent, CLChargeBal_Hex_Cent);
	if( (V_ucReturnData == C_GreaterThan) || (Is_Buf_AllZero(V_ucChargeBal_Hex_Cent, CLChargeBal_Hex_Cent) == C_OK) )	/*C_GreaterThan��ʾ����1��������2*/
	{
		return(C_OtherErr_DAR);
	}
	else
	{
		return(C_OK);
	}
}

/*******************************************************************************
����ԭ�ͣ�	ushort16	S_Purchase_ReturnFile_698(uchar8 *pV_ucData,ushort16 *pV_ucLen)
����������	��ESAMǮ���ļ����г�ֵSID_MAC��֤����ֵ������Ǯ���˷�
���������	*pV_ucData		:��ֵ���ġ���ʽ:Ǯ��������ϢD1+���
			pV_ucLen		:����
���������	C_OK/C_SERR_ESAM_VF
���ز�����
����λ�ã�
��    ע��	pData�������ǲ���仯��;ͨ���ж��Ƿ���Ҫ����Ǯ����ֵ;
			��ֵ��ʶ:80420000 ���ݱ�ʶ80420000(��ֵ) 81440000(�˷�)
			02
			06
			0F ��integer��
			00 0-���� 1-��ֵ 2-�˷�
			06
			00 00 0B B8 ��������3000Ԫ��
			06
			00 00 00 64 ���������100�Σ�
			09
			06
			00 00 00 00 00 01 �����ţ�
			5E ��SID_MAC��
			81 42 00 00 (SID)
			03
			00 13 10 (��������)
			04
			55 B0 0C 0D ��MAC��
			09 (OCTET STRING)
			08
			00 00 00 00 00 00 00 00 (���)
			ͨ�ŷ��͵����ݸ�ʽ: 	XX(��������)+XXXXXXXX(������)+XXXXXXXX(�������)+XX(���ų���)+XX...XX(����)+XXXXXXXX(��ʶ)+xx(�������ݳ���)+XX...XX(��������)+xx(MAC����)+XX...XX(MAC)+xx(��ų���)+XX...XX(���)
			���͸�ESAM�ĸ�ʽ:		XXXXXXXX(��ʶ)+XX...XX(��������)+XX...XX(������+�������+�ͻ����)+XX...XX(MAC)
*******************************************************************************/
ushort16	S_Purchase_ReturnFile_698(uchar8 *pV_ucData, ushort16 *pV_usLen)
{
	uchar8 		V_ucDataBuffer[MaxLength_698];
	uchar8 		V_ucMoneyLen, V_ucMoneyOffset, V_ucBuyNumOffset, V_ucBuyNumLen;
	uchar8 		V_ucAttachDataLen,V_ucAttachDataOffset;
	uchar8 		V_ucMACLen,V_ucMACOffset;
	uchar8 		V_ucSIDLen,V_ucSIDOffset;
	ushort16	V_usSendLen, V_usReceiveLen;
	ushort16	V_usReturnData16;
	uchar8 		V_ucClientNumLen, V_ucClientNumOffset;
	uchar8 		V_ucTemp[6];

	/*��ֵ������ʶ*/
	MoneyClient_Table.V_ucOpenFlag = *(pV_ucData + 3);
	MoneyClient_Table.V_CanRecharge = 0;	/*�������ֵ*/

	/*ƫ�ƺͳ���*/
	/*������*/
	V_ucMoneyOffset = 5;
	V_ucMoneyLen = C_BuyMoney_len_698;
	PF_OneDataReversed(pV_ucData + V_ucMoneyOffset, (uchar8 *)&(MoneyClient_Table.V_ulMoney), V_ucMoneyLen);

	/*�������*/
	V_ucBuyNumOffset = V_ucMoneyOffset + C_BuyMoney_len_698 + C_len_698;
	V_ucBuyNumLen = C_BuyMoneyNum_len_698;
	PF_OneDataReversed(pV_ucData + V_ucBuyNumOffset, (uchar8 *)&(MoneyClient_Table.V_ulBuyMoneyTime), V_ucBuyNumLen);

	/*�ͻ����*/
	V_ucClientNumOffset = V_ucBuyNumOffset + V_ucBuyNumLen + 2;
	V_ucClientNumLen = C_ClientNum_len_698;
	PF_OneDataReversed(pV_ucData + V_ucClientNumOffset, (uchar8 *)&(MoneyClient_Table.V_ucClientNum), V_ucClientNumLen);

	/*������ֵ�������ж��Ƿ���Գ�ֵ*/
	if( (MoneyClient_Table.V_ucOpenFlag == 0) || (MoneyClient_Table.V_ucOpenFlag == 1) )
	{
		V_usReturnData16 = Comm_OpenChgBL_698();
		if(V_usReturnData16 != C_OK)
		{
			return V_usReturnData16;	/*���ش���*/
		}
	}
	else if(MoneyClient_Table.V_ucOpenFlag == 2)	/*�˷�*/
	{
		V_usReturnData16 = DV_Return_Money_698( (uchar8 *)&MoneyClient_Table.V_ulMoney);
		if(V_usReturnData16 != C_OK)
		{
			return V_usReturnData16;	/*���ش���*/
		}
	}
	else
	{
		return(C_OtherErr_DAR);		/*������������*/
	}


	/*(��ʶ)*/
	V_ucSIDOffset = V_ucClientNumOffset + C_ClientNum_len_698 + C_len_698;
	V_ucSIDLen = C_DataID_Length_698;
	/*��������*/
	V_ucAttachDataLen = pV_ucData[V_ucSIDOffset + V_ucSIDLen];
	V_ucAttachDataOffset = V_ucSIDOffset + V_ucSIDLen + C_len_698;
	/*MAC*/
	V_ucMACLen = pV_ucData[V_ucAttachDataOffset + V_ucAttachDataLen];
	V_ucMACOffset = V_ucAttachDataOffset + V_ucAttachDataLen + C_len_698;

	/*�жϱ���Ƿ���ȡ�*/
	if(InF_SC_Meter_Num_OK(pV_ucData + V_ucMACOffset + V_ucMACLen + 2) != C_OK)
	{
		return(C_OtherErr_DAR);	/*������������*/
	}

	/*��������*/
	/*��ʶ*/
	PF_CopyDataBytes(pV_ucData + V_ucSIDOffset, V_ucDataBuffer, V_ucSIDLen);

	/*��������*/
	PF_CopyDataBytes(pV_ucData + V_ucAttachDataOffset, V_ucDataBuffer + V_ucSIDLen, V_ucAttachDataLen);	/*��������*/

	/*������*/
	PF_CopyDataBytes(pV_ucData + V_ucMoneyOffset, V_ucDataBuffer + V_ucSIDLen + V_ucAttachDataLen, V_ucMoneyLen);


	/*�������*/
	PF_CopyDataBytes(pV_ucData + V_ucBuyNumOffset, V_ucDataBuffer + V_ucSIDLen + V_ucAttachDataLen + V_ucMoneyLen, V_ucBuyNumLen);

	/*�ͻ����*/
	PF_CopyDataBytes(pV_ucData + V_ucClientNumOffset, V_ucDataBuffer + V_ucSIDLen + V_ucAttachDataLen + V_ucMoneyLen + V_ucBuyNumLen, V_ucClientNumLen);

	/*MAC*/
	PF_CopyDataBytes(pV_ucData + V_ucMACOffset,V_ucDataBuffer + V_ucSIDLen + V_ucAttachDataLen + V_ucMoneyLen+V_ucBuyNumLen+V_ucClientNumLen, V_ucMACLen);


	/*���㷢�����ݳ���*/
	V_usSendLen = V_ucSIDLen + V_ucAttachDataLen + V_ucMoneyLen + V_ucBuyNumLen + V_ucClientNumLen + V_ucMACLen;

	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		if( (V_usReturnData16 == C_Security_SafetyDataIncorrect) || (V_usReturnData16 == C_Security_MacErr) )
		{
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		return(C_ESAMErr_DAR);
	}

	/*********����Ϊ�÷��ز��� *********************************************************/
	*pV_usLen = V_usReceiveLen;
	PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucData, *pV_usLen);	/*Ӧ��APDU*/

	if(MoneyClient_Table.V_ucOpenFlag == 0)
	{
		PF_OneDataReversed(&(MoneyClient_Table.V_ucClientNum[0]), V_ucTemp, CLCustomer_Num);
		/*д������Ϣ�ļ��Ŀͻ����*/
		WriteBinFile(C_ESAM, V_ucTemp, C_F_OpInfo, CF_O_CNumInOP, CLCustomer_Num);
	}

	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�	ushort16  S_Action_Esam_698(uchar8 *pV_ucData,ushort16 *pV_ucLen)
����������	esam��action����
���������	pV_ucData:		���������׵�ַ����ʽ��������  octet-string����ȫ��ʶ+SID���Ȳ��̶�
			pV_usLen���������ݳ���

���������	pV_ucData:		��������׵�ַ����ʽ��������  octet-string����ȫ��ʶ+SID���Ȳ��̶�
			pV_usLen��������ݳ���
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��	�ỰʱЧ����
			ͨ�ŷ��͵����ݸ�ʽ: 	xx(��Կ���ĳ���)+XX...XX(��Կ��������)+XX(sid����04)+XXXXXXXX(��ʶ)+xx(�������ݳ���02)+XX...XX(��������)
			���͸�ESAM�ĸ�ʽ:		XXXXXXXX(��ʶ)+XX...XX(��������)+XX...XX(��������)+XX...XX(MAC)
*******************************************************************************/
ushort16  S_Action_Esam_698(uchar8 *pV_ucData, ushort16 *pV_usLen)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	ushort16	V_usParaLen,V_usParaOffset;
	ushort16	V_usAttachDataLen,V_usAttachDataOffset;
	ushort16	V_usSIDOffset,V_usSIDLen;
	ushort16	V_usSendLen,V_usReceiveLen;
	ushort16	V_usReturnData16;
	ulong32		V_ulDataID;

	/*ƫ�ƺͳ���*/
	/*����*/
	if(pV_ucData[0] & 0x80)
	{
		if((pV_ucData[0] & 0x7F) == 2)
		{
			V_usParaOffset = 3;
			V_usParaLen = PF_Buffer2ToLong16_698(&pV_ucData[V_usParaOffset - 2]);
		}
		else
		{
			V_usParaOffset = 2;
			V_usParaLen = pV_ucData[V_usParaOffset - 1];
		}
	}
	else
	{
		V_usParaOffset = 1;
		V_usParaLen = pV_ucData[V_usParaOffset - 1];
	}

	/*SID���ȼ�ƫ��*/
	V_usSIDOffset = C_len_698 + V_usParaLen + V_usParaOffset;
	V_usSIDLen = pV_ucData[V_usParaLen + V_usParaOffset];

	/*����SID�ĵ�3�ֽ�P1���ж���ʲô��������*/
	GV_ESAMAction9_SIDP1P2 = pV_ucData[V_usSIDOffset + 2];


	/*������Ϣ*/
	V_usAttachDataLen = pV_ucData[V_usSIDLen + V_usSIDOffset];
	V_usAttachDataOffset = C_len_698 + V_usSIDOffset + V_usSIDLen;

	/*��������*/
	/*��ʶ*/
	PF_CopyDataBytes_698(pV_ucData + V_usSIDOffset, V_ucDataBuffer, V_usSIDLen);
	PF_CopyDataBytes_698(pV_ucData + V_usSIDOffset, (uchar8 *)&V_ulDataID, C_DataID_Length_698);

	#if 0
	if(V_ulDataID != 0x00002E81)	/*0x812E0000�ߵ�*/
	{
		return(C_OtherErr_DAR);
	}
	#endif

	/*��������*/
	PF_CopyDataBytes_698(pV_ucData + V_usAttachDataOffset, V_ucDataBuffer + C_DataID_Length_698, V_usAttachDataLen);		/*��������*/
	/*����*/
	PF_CopyDataBytes_698(pV_ucData + V_usParaOffset, V_ucDataBuffer + C_DataID_Length_698 + V_usAttachDataLen, V_usParaLen);

	/*���㷢�����ݳ���*/
	V_usSendLen = C_DataID_Length_698 + V_usAttachDataLen + V_usParaLen;

	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		if( (V_usReturnData16 == C_Security_SafetyDataIncorrect) || (V_usReturnData16 ==  C_Security_MacErr) )
		{
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		*pV_usLen = 0;

		return(C_ESAMErr_DAR);
	}


	/*********����Ϊ�÷��ز��� *********************************************************/
	*pV_usLen = V_usReceiveLen;
	PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucData, *pV_usLen);		/*Ӧ��APDU*/

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	S_ReadEsam_698(uchar8 *pV_ucData, ushort16 *pV_usLen, ushort16 V_usItem)
����������	��esam�ڲ�����
���������	V_usItem������DI1DI0
���������	*pV_ucData			:��������
			pV_usLen���������ݳ���
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	S_ReadEsam_698(uchar8 *pV_ucData, ushort16 *pV_usLen, ushort16 V_usItem)
{
	uchar8 		V_ucDataBuffer[MaxLength_698], V_ucActionID = 0, i;
	ushort16	V_usSendLen,V_usReceiveLen;
	ushort16	V_usReturnData16;

	for(i = 0; i < CL_EsamNature; i++)
	{
		if(V_usItem == C_EsamNatureToAction[i].V_usDI1DI0   )
		{
			V_ucActionID = C_EsamNatureToAction[i].V_ucP2 ;
			break;
		}
	}
	if(V_usItem == 0x00ff)
	{
		PF_CopyDataBytes( (uchar8 *)&TB_ReadEsamInfoAll_698, V_ucDataBuffer, CLen_TB_ESAM_4_698);
	}
	else if(V_usItem == 0x00fe)		/*�ն˼�������*/
	{
		PF_CopyDataBytes( (uchar8 *)&TB_ReadEsamInfoAll_698_termal, V_ucDataBuffer, CLen_TB_ESAM_4_698);
	}
	else if(i <= CL_EsamNature)
	{
		PF_CopyDataBytes( (uchar8 *)&TB_ReadEsamInfo_698, V_ucDataBuffer, CLen_TB_ESAM_4_698);
		V_ucDataBuffer[3] = V_ucActionID;
	}
	else
	{
		return(C_Error);
	}

	V_ucDataBuffer[4] = 0;
	V_ucDataBuffer[5] = 0;

	/*���㷢�����ݳ���*/
	V_usSendLen = CLen_TB_ESAM_4_698 + 2;

	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_Error);
	}

	/*********����Ϊ�÷��ز��� ******************************/
	if(*pV_usLen < C_EsamNatureToAction[i].V_ucLen)
	{
		return(C_DataLenError);
	}
	else
	{
		*pV_usLen = C_EsamNatureToAction[i].V_ucLen;
		PF_CopyDataBytes_698(&V_ucDataBuffer[C_EsamNatureToAction[i].V_ucOffset], pV_ucData, *pV_usLen); 	/*Ӧ��APDU*/
	}

#if 0
	/*********����Ϊ�÷��ز��� ******************************/
    if( (Item == 6) || (Item == C_Remain_termal_Item) )		/*�ն˻ỰʱЧʣ��ʱ��*/
	{

		/*��վʣ��Ựʱ�����⴦��*/
		if(Item == 6)
		{
			if(Com_Conect.ConectOverTime == 0)
			{
				V_ucDataBuffer[4] = 0;
				V_ucDataBuffer[5] = 0;
				V_ucDataBuffer[6] = 0;
				V_ucDataBuffer[7] = 0;
			}
		}
		else if(Item == C_Remain_termal_Item)
		{
			if(Com_Conect.ConectOverTime_termal == 0)
			{
				V_ucDataBuffer[4]	= 0;
				V_ucDataBuffer[5]	= 0;
				V_ucDataBuffer[6]	= 0;
				V_ucDataBuffer[7]	= 0;
			}

		}

		*pV_ucLen = 4;
		PF_CopyDataBytes_698(&V_ucDataBuffer[4], pV_ucData, *pV_ucLen);		/*Ӧ��APDU*/
	}
	else
	{
	    if(Item == 5)
		{
			*pV_ucLen = 4;
		}
		else if(Item == 21)
		{
			if(Com_Conect.ConectOverTime_termal == 0)
			{
				V_ucDataBuffer[4] = 0;
				V_ucDataBuffer[5] = 0;
				V_ucDataBuffer[6] = 0;
				V_ucDataBuffer[7] = 0;
			}
            *pV_ucLen = V_usReceiveLen;

		}
		else
		{
			*pV_ucLen = V_usReceiveLen;
		}
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucData, *pV_ucLen);	/*Ӧ��APDU*/
	}
#endif

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�	uchar8  INF_S_Encrypt_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucSecurityMode, uchar8 V_ucEncryptMode, uchar8 *pV_ucRN_Data, uchar8 *pV_ucMAC_Data, uchar8 V_ucClientAddr)
����������	����APDU
���������	pV_ucAPDU:		����ܵ�APDU�׵�ַ
			pV_usLen:		��������ݳ���
			V_ucSecurityMode:����������֤ģʽ:RN_698;RN_MAC_698;SID_698;SID_MAC_698
			V_ucEncryptMode:�������ݼ��ܷ�ʽ:����+MAC;����;����+MAC;
			pV_ucRN_Data:	����RN�׵�ַ(RN_698��Ч)
			V_ucClientAddr��	�ͻ��˵�ַ
���������	pV_ucAPDU:		���ܺ��APDU�׵�ַ(���Ļ���������)
			Len:		���ܺ�(��������)���ݳ���
			pV_ucRN_Data:	��������RN�׵�ַ(RN_MAC_698��Ч)
			pV_ucMAC_Data	MAC���ݷ����׵�ַ(����+MAC;����+MAC��Ч;RN_MAC_698��Ч)
���ز�����	Ӧ��ɹ�:C_OK;
			Ӧ���������¼���:
		    ��ȫ��֤ʧ��:C_SCErr_DAR;��������:C_Error;
����λ�ã�
��    ע��	SecurityMode��	�����RN_698ģʽ��p_RN_Data������Ч��
							�����RN_MAC_698ģʽ��p_RN_Data��p_MAC_Data�����Ч��
							���������ģʽ��p_RN_Data��Ч��
		 	p_APDU��buffer 512�ֽڣ�p_RN_Data��20���ֽڣ�p_MAC_Data��4�ֽ�
		 	p_RN_Data��p_MAC_DataӦ�����octet-string��ʽ
*******************************************************************************/
uchar8  INF_S_Encrypt_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucSecurityMode, uchar8 V_ucEncryptMode, uchar8 *pV_ucRN_Data, uchar8 *pV_ucMAC_Data, uchar8 V_ucClientAddr)
{
	uchar8 V_ucReturnFlag;

	if(V_ucSecurityMode == RN_698)	/*RN �������������*/
	{
		V_ucReturnFlag = S_Encrypt_RN_698(pV_ucAPDU, pV_usLen, V_ucEncryptMode, pV_ucRN_Data, pV_ucMAC_Data);
	}
	else if(V_ucSecurityMode == RN_MAC_698)	/*RN_MAC �����ϱ�����*/
	{
		V_ucReturnFlag = S_Encrypt_RN_MAC_698(pV_ucAPDU, pV_usLen, V_ucEncryptMode, pV_ucRN_Data, pV_ucMAC_Data);
	}
	else if(V_ucSecurityMode == MAC_698)
	{
		V_ucReturnFlag = S_Encrypt_MAC_698(pV_ucAPDU, pV_usLen, V_ucEncryptMode, pV_ucRN_Data, pV_ucMAC_Data);
	}
	else
	{
		if(V_ucClientAddr == Termal_Address)
		{
			V_ucReturnFlag = S_Encrypt_698_terminal(pV_ucAPDU, pV_usLen, V_ucEncryptMode, pV_ucMAC_Data);	/*�ն˼���	*/
		}
		else
		{
			V_ucReturnFlag = S_Encrypt_698(pV_ucAPDU, pV_usLen, V_ucEncryptMode, pV_ucMAC_Data);	/*��ս����*/
		}
	}

	return(V_ucReturnFlag);
}


/*******************************************************************************
����ԭ�ͣ�	uchar8  INF_S_ActionEsam_698(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen,uchar8 V_ucClientAddr)
����������	����ESAM
���������	V_ulOAD:			action��OAD
			pV_ucDataBuf:		���������׵�ַ
			pV_usDataLen:		�������ݳ���
���������	pV_ucDataOutBuf:	���ص������׵�ַ
			pV_usDataOutLen:	���ص����ݳ���
			V_ucClientAddr��	�ͻ��˵�ַ
���ز�����	C_OK;
			Ӧ���������¼���:
		    ��ȫ��֤ʧ��:C_SCErr_DAR;��������:C_Error;
����λ�ã�
��    ע��
*******************************************************************************/
uchar8  INF_S_ActionEsam_698(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen,uchar8 V_ucClientAddr)
{
	ushort16	V_ucActionID, V_usReturnData16 = C_OtherErr_DAR;
	uchar8		V_ucbuf[10];
	ushort16	V_usDataLen,V_usCodeData;
	ushort16	V_usDataEnCode;

	V_ucActionID = (uchar8)(V_ulOAD>>8);

	if(C_Meter_Type != C_L_SmartMeter)
	{
		if( (V_ucActionID == C_EsamAction_MoneyInit) || (V_ucActionID == C_EsamAction_MoneyAction) )
		{
			return(C_Unauthorized_DAR);
		}
	}

  	switch( V_ucActionID)
	{
		case C_EsamAction_MoneyInit:	/*Ǯ����ʼ��*/
			V_usReturnData16 = S_InitMoney_698(pV_ucDataBuf,pV_usDataLen);
			*pV_usDataOutLen = 0;
			break;
		case C_EsamAction_ReadData:		/*��ESAM�ļ�,��ҪӦ��*/
			V_usReturnData16 = S_DataExcerption_698(pV_ucDataBuf, pV_usDataLen, pV_ucDataOutBuf, pV_usDataOutLen);
			break;
		case C_EsamAction_DataUpdate:	/*���ݸ��¡���Ҫ��������*/
			V_usReturnData16 = S_WritePara_PlainTextMAC_698(pV_ucDataBuf, pV_usDataLen, pV_ucDataOutBuf, pV_usDataOutLen);
			break;
		case C_EsamAction_KetUpdate:	/*��Կ����*/
			V_usReturnData16 = S_Key_Update_698(pV_ucDataBuf, pV_usDataLen);
			*pV_usDataOutLen = 0;
			break;
		case C_EsamAction_MoneyAction:	/*Ǯ������:��������ֵ���˷�*/
			/*����esam����ǰ�Ƚ���Ǯ������ͬ��*/
			V_usCodeData = CLChargeBal_Hex_Cent;
			if(InF_GetData_ObjectManage(CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, &V_usCodeData) == C_OK)
			{
				InF_S_UpdataChargeBalInESAM(V_ucbuf);
			}

			V_usReturnData16 = S_Purchase_ReturnFile_698(pV_ucDataBuf, pV_usDataLen);
			*pV_usDataOutLen = 0;
			break;
		case C_EsamAction_Auth_Time:	/*Э��ʱЧ����+�ն˵�ַ+�ն˹㲥������+�����֤���ò���+*/
			V_usReturnData16 = S_Action_Esam_698(pV_ucDataBuf, pV_usDataLen);
			*pV_usDataOutLen = 0;
			break;
		case C_EsamAction_Unvalid:		/*Э��ʧЧ,��ҪӦ��*/
			if(*pV_usDataOutLen < (CLDate_Time + 1) )
			{
				return(C_DataLenError); 	/*��ʾ���ݳ��ȴ�*/
			}
			else
			{
				*pV_usDataOutLen = CLDate_Time;
				V_usReturnData16 = InF_Read_Data(CDate_Time, &pV_ucDataOutBuf[1], pV_usDataOutLen, &V_usDataEnCode);
				pV_ucDataOutBuf[0] = C_date_time_s;
				*pV_usDataOutLen += 1;
			}
			break;
		case C_EsamAction_IRRequest:	/*������֤����,��ҪӦ��*/
			V_usReturnData16 = S_IR_ID_Request(pV_ucDataBuf, pV_usDataLen,  pV_ucDataOutBuf, pV_usDataOutLen, V_ucClientAddr);
			break;
		case C_EsamAction_IRID:		/*������֤*/
			V_usReturnData16 = S_IR_ID(pV_ucDataBuf, pV_usDataLen);
			/*���ⶨʱ������*/
			if(V_usReturnData16 != C_OK)
			{
				/****************������֤ʧ�ܽ���������֤��Ч***********************/
				memset(V_ucbuf,0,CL_IRAuth_Timer);

				if(V_ucClientAddr == Termal_Address)
				{
					DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, &V_ucbuf[0]);
				}
				else
				{
					DealWith_IR_Auth_Timer(C_Set_TimerExceed10min, &V_ucbuf[0]);
				}
			}
			else	/*��ȷ��Ӧ�𲢸�ֵ������֤��ʱ��	*/
			{
				V_usDataLen = CL_IRAuth_Timer;	/*���ݳ���4�ֽ�*/
				if(InF_Read_Data(C_IRAuth_Timer, V_ucbuf, &V_usDataLen, &V_usDataEnCode) != C_OK)
				{
					V_ucbuf[0] = C_IRAuthTime_L;		/*���ݲ���������ݣ���Ĭ��Ϊ30����*/
					V_ucbuf[1] = C_IRAuthTime_H;
					V_ucbuf[2] = 0;
					V_ucbuf[3] = 0;
				}

				if(V_ucClientAddr == Termal_Address)
				{
					DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, &V_ucbuf[0]);
				}
				else
				{
					DealWith_IR_Auth_Timer(C_Set_TimerExceed10min, &V_ucbuf[0]);
				}
			}

			*pV_usDataOutLen = 0;
			break;
		default:
			V_usReturnData16 = C_OtherErr_DAR;
			break;
	}


	return(V_usReturnData16);
}

/*******************************************************************************
����ԭ�ͣ�	void DataReversed(ulong32 V_ulReversedMethod,uchar8 *pV_ucData,uchar8 V_ucR_ItemNum)
����������	���ָ����������������ĵߵ�
���������	V_ulReversedMethod:    	�ߵ��ķ���������������Ա�ʶ������
		 	pV_ucData:			��Ҫ�ߵ����ݵĻ������׵�ַ
		 	V_ucR_ItemNum:		��Ҫ�ߵ�����Ŀ��
���������	pV_ucData:�ߵ������ݴ��λ�á����������ͬ
���ز�����
����λ�ã�
��    ע��	����ߵ�ǰ���ֽ������ǲ���ġ�
			����˵��:
			1������ReversedMethod�������1�����ݣ������R_Lenֱ�ӵߵ������˳�
			2������ReversedMethod��ȷ�ϵߵ������з������ݱ���׵�ַ
			3�����ȷ������ߵ����ݵĳ��ȣ�����ѭ���ߵ���ѭ������ΪR_ItemNum
			4���ߵ�������������copy�����ڻ������˳�
*******************************************************************************/
void DataReversed(ulong32 V_ulReversedMethod, uchar8 *pV_ucData, uchar8 V_ucR_ItemNum)
{
	uchar8	*pV_ucTB_DataReversed;		/*��ߵ����ݻ�������ÿ�����������ݳ��ȱ�*/
	uchar8	i;
	uchar8	*pV_ucSdata;
	uchar8	*pV_ucDdata;

	switch(V_ulReversedMethod)
	{
		case		CDI_Auth:				/*��������case��Ҳ���Խ�һ�ű������׶಻�ࡣ*/
			pV_ucTB_DataReversed = (uchar8 *)TB_RItem_Len_Auth;
			break;
		case		CDI_Auth_R:
			pV_ucTB_DataReversed = (uchar8 *)TB_RItem_Len_AuthR;
			break;
		case		CDI_CPTime:
			pV_ucTB_DataReversed = (uchar8 *)TB_RITem_Len_CPTime;
			break;
		case		CBackUp_RateFF_Price:
			pV_ucTB_DataReversed = (uchar8 *)TB_RITem_Len_RateBak;
			break;
		case		CBackUp_Ladder_Table:
			pV_ucTB_DataReversed = (uchar8 *)TB_RITem_Len_LadderBak;
			break;
		case		CMeter_Position:
			pV_ucTB_DataReversed = (uchar8 *)TB_RITem_Len_MeterPosition;
			break;
		case		CDI_TZone_Data:
			pV_ucTB_DataReversed = (uchar8 *)TB_RITem_Len_TZone_Data;
			break;
		case		CDI_TZone_PT_Data:
			pV_ucTB_DataReversed = (uchar8 *)TB_RITem_Len_TZone_PT_Data;
			break;
		case		CDI_Init_Money:
			pV_ucTB_DataReversed = (uchar8 *)TB_RITem_Len_InitMoney;
			break;
		default:
			return;
	}

	/*��ʼѭ���ߵ�*/
	pV_ucSdata = pV_ucData;
	pV_ucDdata = pV_ucData;
	for(i = 0; i < V_ucR_ItemNum; i++)
	{
		PF_OneDataReversed(pV_ucSdata, pV_ucDdata, pV_ucTB_DataReversed[i]);
		pV_ucSdata = pV_ucSdata + pV_ucTB_DataReversed[i];
		pV_ucDdata = pV_ucDdata + pV_ucTB_DataReversed[i];
	}
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	ReadRecordFile(uchar8 * pV_ucData, uchar8 * pV_ucLen, uchar8 V_ucRecordNo)
����������	���Ǯ���ļ��м�¼��Ķ�ȡ
���������	V_ucRecordNo:	��ȡ�ļ�¼�ż�����ȡֵΪ:
							C_ChargeBal(���)
							C_PurchasingE_Num(�������)
							C_Custormer_Num(�ͻ����)
���������	*pV_ucData:	ESAM�м�¼�ļ��Ĺ��������ʣ����Ϳͻ����
			*pV_ucLen:	������󳤶�
���ز�����	C_OK/C_Error
����λ�ã�
��    ע��	�������ص������Ѿ��ߵ���!
*******************************************************************************/
uchar8	ReadRecordFile(uchar8 *pV_ucData, uchar8 * pV_ucLen, uchar8 V_ucRecordNo)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	ushort16	V_usDataLen;
	ushort16	V_usReturnData16;

	PF_CopyDataBytes( (uchar8 *)TB_ReadRecord_698, &V_ucbuf[0], CLen_TB_ReadRecord_698);					/*��ȡ������*/
	V_usDataLen = CLen_S_BufMaxLen;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucbuf, CLen_TB_ReadRecord_698, V_ucbuf, &V_usDataLen);
	if( (V_usReturnData16 != C_Security_CommandOk) && ( (V_usReturnData16 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_Error);
	}

	/*��������*/
	if(V_ucRecordNo == C_ChargeBal_Mac)
	{
		if(*pV_ucLen < CLChargeBal_Hex_Cent)
		{
			return(C_DataLenError);
		}
		else
		{
			*pV_ucLen = CLChargeBal_Hex_Cent;
			PF_OneDataReversed(V_ucbuf, pV_ucData, CLChargeBal_Hex_Cent);	/*4�ֽڹ�����		*/
		}
	}
	else if(V_ucRecordNo == C_PurchasingE_Num_Mac)
	{
		if(*pV_ucLen < CL_PurchasingE_Num)
		{
			return(C_DataLenError);
		}
		else
		{
			*pV_ucLen = CL_PurchasingE_Num;

			PF_OneDataReversed(V_ucbuf + CLChargeBal_Hex_Cent, pV_ucData, CL_PurchasingE_Num);	/*4�ֽڹ������	*/
		}
	}
	else if(V_ucRecordNo == C_Custormer_Num)
	{
		if(*pV_ucLen < CLCustomer_Num)
		{
			return(C_DataLenError);
		}
		else
		{
			*pV_ucLen = CLCustomer_Num;
			PF_OneDataReversed(V_ucbuf + CLChargeBal_Hex_Cent + CL_PurchasingE_Num, pV_ucData, CLCustomer_Num);	/*�ͻ����	*/
		}
	}
	else
	{
		return(C_Error);
	}


	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�	ReadRecordFile_1(uchar8 * pV_ucData, uchar8 *pV_ucLen)
����������	��ɼ�¼�ļ��м�¼��Ķ�ȡ(�����Mac��)
���������
���������	*pV_ucData:		ESAM�м�¼�ļ��Ĺ��������ʣ����+mac
			pV_ucLen:		*pV_ucDataʵ�ʳ���

���ز�����	C_OK/C_Error
����λ�ã�
��    ע��	������ע	�������ص������Ѿ��ߵ���!
			������ע	645��ӦԶ�̽�������״̬��ѯר��
*******************************************************************************/
uchar8	ReadRecordFile_1(uchar8 * pV_ucData, uchar8 *pV_ucLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucReturnData;
	uchar8		V_ucResponseLen;
	ushort16	V_usDataLen1;
	ushort16	V_usReturnData16;
	ushort16	V_usDataEnCode, V_usDataLen;

	/*�ж���ڲ���* pDataLen�Ƿ���ȷ*/

	if(*pV_ucLen < (C_MacLen + CLChargeBal_Hex_Cent + CL_PurchasingE_Num + CLCustomer_Num + 4) )
	{

		return(C_Error);
	}
	V_ucResponseLen = C_MacLen + CLChargeBal_Hex_Cent + CL_PurchasingE_Num + CLCustomer_Num + 4;


	/*��Mac����¼�ļ�������80 48 00 00 00 0d 48 + 00 00 +���+4�ֽ��������*/
	/*����P1Ϊ��¼��*/
	V_usDataLen = CLMeter_Num;
	PF_CopyDataBytes( (uchar8 *)TB_ReadRecord, &V_ucbuf[0], CLen_TB_ReadRecord);			/*��ȡ������*/
	V_ucReturnData = InF_Read_Data(CMeter_Num, &V_ucbuf[C_O_MeterNum], &V_usDataLen, &V_usDataEnCode);			/*�����*/
	if(V_ucReturnData != C_OK)
	{
		return(C_Error);
	}
	PF_OneDataReversed(&V_ucbuf[C_O_MeterNum], &V_ucbuf[C_O_MeterNum], CLMeter_Num);				/*�������ı����Ҫ�ߵ�ʹ��*/
	PF_CopyDataBytes(SV_Rand1_4, &V_ucbuf[CLen_TB_ReadRecord + CLMeter_Num], 4);				/*ȡ����������ڼ���Mac*/
	V_usDataLen1 = CLen_S_BufMaxLen;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucbuf, (CLen_TB_ReadRecord + CLMeter_Num + 4), V_ucbuf, &V_usDataLen1);
	if( (V_usReturnData16 != C_Security_CommandOk) && ( (V_usReturnData16 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_Error);
	}

	/*��������Ϊ0012+ʣ����+�������+�ͻ����+MAC	*/
	PF_CopyDataBytes(V_ucbuf, pV_ucData, V_ucResponseLen);

	/*�ֱ�ߵ�*/
	PF_OneDataReversed(pV_ucData, pV_ucData, CLChargeBal_Hex_Cent);
	PF_OneDataReversed(&pV_ucData[CLChargeBal_Hex_Cent], &pV_ucData[CLChargeBal_Hex_Cent], C_BuyMoneyNum_len_698);
	PF_OneDataReversed(&pV_ucData[CLChargeBal_Hex_Cent + C_BuyMoneyNum_len_698], &pV_ucData[CLChargeBal_Hex_Cent + C_BuyMoneyNum_len_698], CLCustomer_Num);
	PF_OneDataReversed(&pV_ucData[CLChargeBal_Hex_Cent + C_BuyMoneyNum_len_698 + CLCustomer_Num], &pV_ucData[CLChargeBal_Hex_Cent+C_BuyMoneyNum_len_698 + CLCustomer_Num], C_MacLen);

	*pV_ucLen = CLChargeBal_Hex_Cent + C_BuyMoneyNum_len_698 + CLCustomer_Num + C_MacLen;

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�	ushort16	WriteRecordFile(uchar8 * pV_ucData, uchar8 V_ucLen)
����������	дESAM��¼�ļ�(Ǯ���ļ�)
���������	pV_ucData				:��д�����׵�ַ
			V_ucLen				:��д���ݵĳ���
���������	��
���ز�����	C_OK/C_Error/C_SERR_ESAM_VF/C_SERR_OtherErr
����λ�ã�
��    ע��	1����¼�ļ�ָ�ľ���Ǯ���ļ�
			2�����ݷ���ESAM���ģʽ�����ñ�����ʱ����ߵ���!
			3��ʵ��*pData�̶���8�ֽڵġ�
*******************************************************************************/
ushort16	WriteRecordFile(uchar8 * pV_ucData, uchar8 V_ucLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	ushort16	V_usDataLen;

	/*��7816ָ��*/
	PF_CopyDataBytes( (uchar8 * )TB_WriteRecord_698, V_ucbuf, CLen_TB_ESAM_Lc_698_Esam);
	if(V_ucLen != 8)
	{
		return(C_SERR_OtherErr);
	}
	PF_CopyDataBytes(pV_ucData, &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], V_ucLen);

	PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*����֮ǰ��������ͷ*/
	/*дESAM*/
	V_usDataLen = CLen_S_BufMaxLen;
	GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucbuf, (CLen_TB_ESAM_Lc_698_Esam + V_ucLen), V_ucbuf, &V_usDataLen);
	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		if((GV_7816CMD.SW1_2 == C_Security_SafetyDataIncorrect) || (GV_7816CMD.SW1_2 == C_Security_MacErr) )
		{
			return(C_SERR_ESAM_VF);
		}
		else
		{
			return(C_SERR_OtherErr);
		}
	}
	else
	{
		return(C_OK);
	}
}

/*******************************************************************************
����ԭ�ͣ�	uchar8	ReadBinFileMac(uchar8 * pV_ucData, uchar8 *V_ucFileNo,uchar8 *V_ucParmOffset,uchar8 *V_ucParmLen)
����������	��Mac ��ȡ�������ļ��е�һ���������������ݻس���
���������	V_ucFileNo:		��ȡ�Ķ������ļ��̱�ʶ�롣���궨��
			V_ucParmOffset	���Ĳ���ƫ�ơ����궨��
			V_ucParmLen		��Ҫ���Ĳ������ȡ�
���������	*pV_ucData:		���ز������䳤��Ϊ�������ݳ���+4�ֽ�Mac
���ز�����	C_OK/C_Error
����λ�ã�
��    ע��	��������ֵû�еߵ���!���������¼�ļ���ͬ!!
			������Ӧ�ð����������ݳ���+4�ֽ�Mac����
			���ñ����Ϊ��ɢ���ӡ�LC1=��ȡ���ݳ���+4(Mac)+8(��ɢ����)
*******************************************************************************/
uchar8	ReadBinFileMac(uchar8 *pV_ucData, uchar8 *pV_ucFileNo, uchar8 *pV_ucParmOffset, uchar8 *pV_ucParmLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucReturnData;
	ushort16	V_usShort16Buufer;
	ushort16	V_usReturnData16;
	ushort16	V_usDataEnCode, V_usDataLen;

	if(*pV_ucParmLen > CLen_S_BufMaxLen -2)
	{
		return(C_Error);
	}

	/*��֯����֡������*/
	PF_CopyDataBytes( (uchar8 *)TB_ReadBinFile_Mac, V_ucbuf, CLen_TB_ReadBinFileMac);
	PF_CopyDataBytes(pV_ucFileNo, &V_ucbuf[C_O_P1], 2);

	PF_CopyDataBytes(SV_Rand1_4, &V_ucbuf[C_O_Rand4], 4);		/*ȡ����������ڼ���Mac*/
	PF_CopyDataBytes(pV_ucParmOffset, &V_ucbuf[C_O_P2BinFile], 2);	/*P2*/
	PF_CopyDataBytes(pV_ucParmLen, &V_ucbuf[C_O_lenBinFile], 2);		/*len*/

	PF_Buffer2ToUshort16(pV_ucParmLen, &V_usShort16Buufer);
	V_usShort16Buufer = V_usShort16Buufer + 4;
	PF_Ushort16ToBuffer2(&V_ucbuf[C_O_Lc2], &V_usShort16Buufer);	/*lc2=len+4*/
	/*���*/
	V_usDataLen = CLMeter_Num;
	V_ucReturnData = InF_Read_Data(CMeter_Num, &V_ucbuf[C_O_MeterNumBinFile], &V_usDataLen, &V_usDataEnCode);	/*�����*/
	if(V_ucReturnData != C_OK)
	{
		return(C_Error);
	}
	PF_OneDataReversed(&V_ucbuf[C_O_MeterNumBinFile], &V_ucbuf[C_O_MeterNumBinFile], CLMeter_Num);	/*�������ı����Ҫ�ߵ�ʹ��*/
	/*��������	*/
	V_usDataLen = CLen_S_BufMaxLen;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucbuf, CLen_TB_ReadBinFileMac, V_ucbuf, &V_usDataLen);
	if( (V_usReturnData16 != C_Security_CommandOk) && ( (V_usReturnData16 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_Error);
	}

	PF_CopyDataBytes_698(&V_ucbuf[2], pV_ucData, V_usShort16Buufer);

	return(C_OK);

}




/*******************************************************************************
����ԭ�ͣ�	uchar8	WriteBinFile(uchar8 V_ucCH,uchar8 * pV_ucData, uchar8 V_ucFileNo,uchar8 V_ucParmOffset,uchar8 V_ucParmLen)
����������	����Mac д�������ļ��е�һ������
���������	pV_ucData:		��Ҫд�����ݻ�����
			V_ucFileNo:		�������ļ��̱�ʶ�롣���궨��
			V_ucParmOffset	����ƫ�ơ����궨��
			V_ucParmLen		��Ҫд�Ĳ������ȡ�
			V_ucCH			ͨ��C_ESAM/C_Card
���������	��
���ز�����	C_OK/C_Error
����λ�ã�
��    ע��	��ڲ����Ѿ�����ESAM�Ĵ��ģʽ
			ע:ֻ����дesam�ķ�д��Ϣ�ļ�(esam�����ļ���֧��д)�����ļ�����֧������д
*******************************************************************************/
uchar8	WriteBinFile(uchar8 V_ucCH, uchar8 *pV_ucData, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, uchar8 V_ucParmLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucDataLen1;
    ushort16	V_usDataLen2;
	uchar8		V_ucDataLen;

	if(V_ucParmLen > C_F_Pam_Max-9)
	{
		return(C_Error);
	}

	if(V_ucCH == C_ESAM)
	{
		V_ucbuf[0] = 0x80;			/*����Macд�������ļ�*/
		V_ucbuf[1] = 0x2A;
		V_ucbuf[2] = 0x00;			/*FileNoΪ�ļ��̱�ʶ�룬���÷�ʽ1, 100x xxxx xxxxxΪ�̱�ʶ��*/
		V_ucbuf[3] = 0x07;			/*P2*/
		V_ucbuf[4] = 0x00;			/*Lc*/
		V_ucbuf[5] = V_ucParmLen + 3;		/*Lc*/
		V_ucbuf[6] = 0x00;			/*Lc*/
		V_ucbuf[7] = 0x00;			/*Lc*/
		V_ucbuf[8] = V_ucParmOffset;	/*Lc*/

		PF_CopyDataBytes(pV_ucData, &V_ucbuf[9], V_ucParmLen);

		PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*�ݴ�7816����ͷ*/

		V_ucDataLen = 9 + V_ucParmLen;

		V_usDataLen2 = CLen_S_BufMaxLen;


		GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucbuf, V_ucDataLen, V_ucbuf, &V_usDataLen2);
	}
	else	/*ʵ���ϲ������ߵ������֧����Ϊ���������¿��ļ�*/
	{
		V_ucbuf[0] = 0x00;					/*����Macд�������ļ�*/
		V_ucbuf[1] = 0xD6;
		V_ucbuf[2] = 0x80 | V_ucFileNo;			/*FileNoΪ�ļ��̱�ʶ�룬���÷�ʽ1, 100x xxxx xxxxxΪ�̱�ʶ��*/
	/*	V_ucbuf[2] = 0xC0 & V_ucbuf[2] ;*/
		V_ucbuf[3] = V_ucParmOffset;			/*P2*/
		V_ucbuf[4] = V_ucParmLen;				/*Lc*/

		PF_CopyDataBytes(pV_ucData, &V_ucbuf[5], V_ucParmLen);

		PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*�ݴ�7816����ͷ*/

		V_ucDataLen = CLen_TB_ESAM_Lc + V_ucParmLen;

		V_ucDataLen1 = CLen_S_BufMaxLen;

		GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucbuf, V_ucDataLen, V_ucbuf, &V_ucDataLen1);
	}

	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_Error);
	}
	else
	{
		return(C_OK);
	}
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	WriteBinFileMac(uchar8 V_ucCH, uchar8 * pV_ucData, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, ushort16 V_ucParmLen)
����������	��Mac д�������ļ��е�һ������
���������	pV_ucData:		��Ҫд�����ݻ�����
			V_ucFileNo:		�������ļ��̱�ʶ�롣���궨��
			V_ucParmOffset	����ƫ�ơ����궨��
			V_ucParmLen		��Ҫд�Ĳ������ȡ�����Mac����
			V_ucCH			ͨ���ţ�ȡֵC_ESAM/C_Card
���������	��
���ز�����	C_OK/C_IC_MAC_ERR/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR/C_Error
����λ�ã�
��    ע��	��ڲ����Ѿ�����ESAM�Ĵ��ģʽ
*******************************************************************************/
uchar8	WriteBinFileMac(uchar8 V_ucCH, uchar8 * pV_ucData, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, ushort16 V_usParmLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucReturnData;
	ushort16	V_usDataLen2;
	uchar8		V_ucDataLen1;
	ushort16	V_usDataLen;

	if(V_usParmLen > (C_F_Pam_Max-CLen_TB_ESAM_Lc_698_Esam))
	{
		return(C_Error);
	}


	if(V_ucCH == C_ESAM)
	{
		V_ucbuf[0] = 0x83;							/*����Mac���������ļ�����Ϊ00B0*/
		V_ucbuf[1] = 0x2a;
		V_ucbuf[2] = 0x80 | V_ucFileNo;					/*FileNoΪ�ļ��̱�ʶ�룬���÷�ʽ1, 100x xxxx xxxxxΪ�̱�ʶ��*/
		V_ucbuf[3] = V_ucParmOffset;					/*P2*/
		V_ucbuf[4] = (uchar8)(V_usParmLen >> 8);		/*Lc*/
		V_ucbuf[5] = (uchar8)V_usParmLen;				/*Lc*/

		PF_CopyDataBytes_698(pV_ucData, &V_ucbuf[6], V_usParmLen);

		PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*7816����ͷ�ݴ�*/

		V_usDataLen = CLen_TB_ESAM_Lc_698_Esam + V_usParmLen;

		V_usDataLen2 = CLen_S_BufMaxLen;


		GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucbuf, V_usDataLen, V_ucbuf, &V_usDataLen2);
		V_ucReturnData = C_IC_ESAM_RDWR_ERR;
	}
	else
	{
		V_ucbuf[0] = 0x04;					/*����Mac���������ļ�����Ϊ00B0*/
		V_ucbuf[1] = 0xD6;
		V_ucbuf[2] = 0x80 | V_ucFileNo;			/*FileNoΪ�ļ��̱�ʶ�룬���÷�ʽ1, 100x xxxx xxxxxΪ�̱�ʶ��*/
		V_ucbuf[3] = V_ucParmOffset;			/*P2*/
		V_ucbuf[4] = (uchar8)V_usParmLen;		/*Lc*/

		PF_CopyDataBytes_698(pV_ucData, &V_ucbuf[5], V_usParmLen);

		PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*7816����ͷ�ݴ�*/

		V_usDataLen = CLen_TB_ESAM_Lc + V_usParmLen;

		V_ucDataLen1 = CLen_S_BufMaxLen;

		GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucbuf, V_usDataLen, V_ucbuf, &V_ucDataLen1);
		V_ucReturnData = C_IC_NOIN_ERR;
	}

	if( (GV_7816CMD.SW1_2 !=C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		if((GV_7816CMD.SW1_2 == C_Security_SafetyDataIncorrect) || (GV_7816CMD.SW1_2 == C_Security_MacErr) )
		{
			return(C_IC_MAC_ERR);
		}
		else
		{
			return(V_ucReturnData);
		}
	}
	else
	{
		return(C_OK);
	}
}

/*******************************************************************************
����ԭ�ͣ�	uchar8	WriteBinFileMac_1(uchar8 V_ucCH,uchar8 * pV_ucData, uchar8 V_ucFileNo,uchar8 V_ucParmLen)
����������	��Macд�������ļ�
���������	V_ucCH			ͨ���ţ�ȡֵC_ESAM/C_Card
			pV_ucData:		��Ҫд�����ݻ�����
			V_ucFileNo:		�������ļ��̱�ʶ�롣���궨��
			V_ucParmLen		��Ҫд�Ĳ������ȡ�����Mac����
���������	��
���ز�����	C_OK/C_IC_MAC_ERR/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR/C_Error
����λ�ã�	645Э���Զ�̿�������������㡢�¼�/��������
��    ע��	����8012C08X+LC
*******************************************************************************/
uchar8	WriteBinFileMac_1(uchar8 V_ucCH, uchar8 *pV_ucData, uchar8 V_ucFileNo, uchar8 V_ucParmLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucReturnData;
	ushort16	V_usDataLen,V_usDataLen1;

	if(V_ucParmLen > C_F_Pam_Max - CLen_TB_ESAM_Lc)
	{
		return(C_Error);
	}
	V_ucbuf[0] = 0x80;				/*����Mac���������ļ�����Ϊ00B0*/
	V_ucbuf[1] = 0x12;
	V_ucbuf[2] = 0xC0;
	V_ucbuf[3] = V_ucFileNo;			/*FileNoΪ�ļ��̱�ʶ�룬���÷�ʽ1, 100x xxxx xxxxxΪ�̱�ʶ��*/
	V_ucbuf[4] = 0x00;				/*Lc*/
	V_ucbuf[5] = V_ucParmLen;

	PF_CopyDataBytes(pV_ucData, &V_ucbuf[6], V_ucParmLen);

	PF_OneDataReversed(V_ucbuf,GV_7816CMD.Header, CL_7816Header);		/*7816����ͷ�ݴ�*/

	V_usDataLen = 6 + V_ucParmLen;

	V_usDataLen1 = CLen_S_BufMaxLen;


	GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucbuf, V_usDataLen, pV_ucData, &V_usDataLen1);
	V_ucReturnData = C_IC_ESAM_RDWR_ERR;


	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		if( (GV_7816CMD.SW1_2 == C_Security_SafetyDataIncorrect) || (GV_7816CMD.SW1_2 == C_Security_MacErr) )
		{
			return(C_IC_MAC_ERR);
		}
		else
		{
			return(V_ucReturnData);
		}
	}
	else
	{
		return(C_OK);
	}
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	WriteBinFileMac_2(uchar8 V_ucCH, uchar8 * pV_ucData, uchar8 V_ucParmOffsetL, uchar8 V_ucParmOffsetH, uchar8 V_ucParmLen)
����������	��Mac д�������ļ�
���������	pV_ucData:		��Ҫд�����ݻ�����
			V_ucParmOffsetL:		ƫ�Ƶ�ַ���ֽ�
			V_ucParmOffsetH	ƫ�Ƶ�ַ���ֽ�
			V_ucParmLen		��Ҫд�Ĳ������ȡ�����Mac����
			V_ucCH			ͨ���ţ�ȡֵC_ESAM/C_Card
���������	��
���ز�����	C_OK/C_IC_MAC_ERR/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR/C_Error
����λ�ã�	645Э������Ĵ�macдesam��645Э������Ĵ�macдesam
��    ע��	��ڲ����Ѿ�����ESAM�Ĵ��ģʽ
			�ͺ���WriteBinFileMac����Ϊ��
			1��WriteBinFileMac���÷�ʽһ����P1P2 = 1	0	0	5λ�̵��ļ���ʶ��	8λ�ļ���ƫ����
			2��WriteBinFileMac_2���÷�ʽ������P1P2 = 0 15λƫ�ơ�д֮ǰ��������ѡ���ļ�
*******************************************************************************/
uchar8	WriteBinFileMac_2(uchar8 V_ucCH, uchar8 * pV_ucData, uchar8 V_ucParmOffsetL, uchar8 V_ucParmOffsetH, uchar8 V_ucParmLen)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;
	uchar8	V_ucDataLen1;
	uchar8	V_ucDataLen;

	if(V_ucParmLen > C_F_Pam_Max-CLen_TB_ESAM_Lc)
	{
		return(C_Error);
	}
	V_ucbuf[0] = 0x04;					/*����Mac���������ļ�����Ϊ00B0*/
	V_ucbuf[1] = 0xD6;
	V_ucbuf[2] = V_ucParmOffsetH;			/*FileNoΪ�ļ��̱�ʶ�룬���÷�ʽ1, 100x xxxx xxxxxΪ�̱�ʶ��*/
	V_ucbuf[3] = V_ucParmOffsetL;			/*P2*/
	V_ucbuf[4] = V_ucParmLen;				/*Lc*/

	PF_CopyDataBytes(pV_ucData, &V_ucbuf[5], V_ucParmLen);

	PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*7816����ͷ�ݴ�*/

	V_ucDataLen = CLen_TB_ESAM_Lc + V_ucParmLen;

	V_ucDataLen1 = CLen_S_BufMaxLen;

	if(V_ucCH == C_ESAM)
	{
		GV_7816CMD.SW1_2 = INF_SendData_7816_Esam(V_ucbuf, V_ucDataLen, V_ucbuf, &V_ucDataLen1);
		V_ucReturnData = C_IC_ESAM_RDWR_ERR;
	}
	else
	{
		GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucbuf, V_ucDataLen, V_ucbuf, &V_ucDataLen1);
		V_ucReturnData = C_IC_NOIN_ERR;
	}

	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		if( (GV_7816CMD.SW1_2 == C_Security_SafetyDataIncorrect) || (GV_7816CMD.SW1_2 == C_Security_MacErr) )
		{
			return(C_IC_MAC_ERR);
		}
		else
		{
			return(V_ucReturnData);
		}
	}
	else
	{
		return(C_OK);
	}
}


/*******************************************************************************
����ԭ�ͣ�	void	InF_S_UpdataChargeBalInESAM(uchar8 *pV_ucChargeBal_Hex_Cent)
����������	ˢ��ESAM�е�ʣ����
���������	*pV_ucChargeBal_Hex_Cent:	���ݲ�洢��ʣ����(009002F9)��Hex����λΪ��
								���ȹ̶�Ϊ4�ֽ�,С��
���������	ESAM�е�ʣ��������ݲ�ͬ��
���ز�����	��
����λ�ã�	��
��    ע��	20140820���ݸ���΢�������޸�����:
			1�����ESAM���С�����ݲ�ʣ��������ݲ�����˷Ѳ�����
			2����֮�������ݲ���и���ֵ
*******************************************************************************/
void	InF_S_UpdataChargeBalInESAM(uchar8 *pV_ucChargeBal_Hex_Cent)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	ulong32		V_ulChargeBal_DataLayer;
	ulong32		V_ulChargeBal_ESAM;
	ulong32		V_ulDecrease_ChargeBal;
	uchar8		V_ucDataLen;
	ushort16	V_usDataLen1;
	uchar8		V_ucReturnData;
	uchar8		V_ucSendDataLen = 0;

	SV_SafeByte = 0x00;

	PF_Buffer4ToUlong32(pV_ucChargeBal_Hex_Cent, &V_ulChargeBal_DataLayer, 4);

	SV_SafeByte = SV_SafeByte |C_W_SafeFlag_1;

	/*��ȡESAM�е�ʣ����*/
	V_ucDataLen = CLen_S_BufMaxLen;
	V_ucReturnData = ReadRecordFile(V_ucbuf, &V_ucDataLen, C_ChargeBal_Mac);
	if(V_ucReturnData != C_OK)
	{
		SV_SafeByte = 0x00;
		return;
	}
	PF_Buffer4ToUlong32(V_ucbuf, &V_ulChargeBal_ESAM, CLChargeBal_Hex_Cent);

	SV_SafeByte = SV_SafeByte | C_W_SafeFlag_2;

	/*�Ƚ�ESAM��ʣ��������ݲ��ʣ���
	���ESAM�еĴ������ݲ㣬���пۼ�
	��֮�������ݲ���и���ֵ��*/
	if(V_ulChargeBal_ESAM > V_ulChargeBal_DataLayer)	/*ESAM�ۼ�*/
	{
		/*�ۼ�����80 46 00 00 00 04 +4�ֽڿۼ����*/
		V_ucDataLen = CLen_S_BufMaxLen;
		/*��ȡ����ͷ����������*/
		PF_CopyDataBytes((uchar8 *)TB_Decrease_698, &V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam);		/*��ȡ������*/
		V_ucSendDataLen = CLen_TB_ESAM_Lc_698_Esam;

		/*��ȡ�ۼ�����������*/
		V_ulDecrease_ChargeBal = V_ulChargeBal_ESAM - V_ulChargeBal_DataLayer;							/*�ۼ��Ľ��*/
		PF_Ulong32ToBuffer4(&V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], &V_ulDecrease_ChargeBal, CLChargeBal_Hex_Cent);
		PF_OneDataReversed(&V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], CLChargeBal_Hex_Cent);
		V_ucSendDataLen = V_ucSendDataLen + CLChargeBal_Hex_Cent;

		SV_SafeByte = SV_SafeByte | C_W_SafeFlag_3;

		V_usDataLen1 = CLen_S_BufMaxLen;
		if(SV_SafeByte == C_W_SafeFlag)
		{
			GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucbuf, V_ucSendDataLen, V_ucbuf, &V_usDataLen1);
			if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
			{
				SV_SafeByte = 0x00;
				return;
			}
		}
		SV_SafeByte = 0x00;

	}
	else if(V_ulChargeBal_ESAM < V_ulChargeBal_DataLayer)	/*����ֵ����ESAMΪ׼��д���ݲ㡣*/
	{
		SV_SafeByte = SV_SafeByte | C_W_SafeFlag_3;

		V_ulDecrease_ChargeBal = V_ulChargeBal_DataLayer - V_ulChargeBal_ESAM;

		InF_ReturnMoneyFromPurchase(V_ulDecrease_ChargeBal, SV_SafeByte);

		SV_SafeByte = 0;
	}
	else	/*��ȣ��������в���*/
	{
		SV_SafeByte = 0;
	}
}



/*******************************************************************************
����ԭ�ͣ�	void		Updata_ESAM_OpParm(uchar8	V_ucMsgNum)
����������	ˢ��ESAM�����в���
���������	MsgNum:��Ϣ�ţ�ȡֵC_Msg_Communication/C_Msg_Card
���������
���ز�����	��
����λ�ã�
��    ע��	I������ڸ���ʱ��ֱ��ˢ�������ļ��ˣ��������ﲻ��
*******************************************************************************/
void		Updata_ESAM_OpParm(uchar8	V_ucMsgNum)
{
	uchar8		V_ucReturnData;
	uchar8		V_ucbuf1[60];
	uchar8		V_ucbuf2[60];
	uchar8		V_ucReponseBuf[CL_Response_InIC];
	uchar8		V_ucDataLen;
	uchar8		i;
	ushort16	V_usDataLen, V_usCodeData;
	ulong32		V_ulhexData;

	/*�ݴ������ļ�*/
	InF_SC_RDBinFileNoMac(C_ESAM, C_F_OpInfo, CF_O_OPI_Start, CL_OPI, V_ucbuf1);
	PF_CopyDataBytes(V_ucbuf1, V_ucbuf2, CL_OPI);
	/*��������ֻ�б��ر�Ż��б仯*/
	if(C_Meter_Type == C_L_SmartMeter)
	{
		/*��Ǯ���ļ���ʣ����*/
		V_ucDataLen = CL_Response_InIC;
		V_ucReturnData = ReadRecordFile(V_ucReponseBuf, &V_ucDataLen, C_ChargeBal_Mac);
		if(V_ucReturnData != C_OK)
		{
			return;
		}
		PF_OneDataReversed(V_ucReponseBuf, &V_ucbuf1[CF_O_OPI_ChBal_H_C], CLChargeBal_Hex_Cent);		/*����¼�ļ�������ʱ�ѷ���С������ĳɴ��	*/
		/*��Ǯ���ļ��й������*/
		V_ucDataLen = CL_Response_InIC;
		V_ucReturnData = ReadRecordFile(V_ucReponseBuf, &V_ucDataLen, C_PurchasingE_Num_Mac);
		if(V_ucReturnData != C_OK)
		{
			return;
		}
		PF_OneDataReversed(V_ucReponseBuf, &V_ucbuf1[CF_O_OPI_PEN], CL_PurchasingE_Num);		/*����¼�ļ�������ʱ�ѷ���С������ĳɴ��*/

		/*��͸֧���	hex��ʽת����BCD��ʽ*/
		V_usDataLen = CLOverDraft_Hex_Cent;
		V_ucReturnData = InF_GetData_ObjectManage(COverDraft_Hex_Cent, V_ucReponseBuf, &V_usDataLen, &V_usCodeData);
		if(V_ucReturnData != C_OK)
		{
			return;
		}
		PF_Buffer4ToUlong32(V_ucReponseBuf, &V_ulhexData, CLOverDraft_Hex_Cent);
		V_ucDataLen = CLOverDraft_Hex_Cent;
		PF_HextoBCDBytes(&V_ulhexData, V_ucReponseBuf, &V_ucDataLen);
		PF_OneDataReversed(V_ucReponseBuf, &V_ucbuf1[CF_O_OPI_OD_B], CLOverDraft_BCD);	/*���дesam*/

		/*���Ƿ��忨����*/
		V_usDataLen = CLLawlessC_Degree;
		InF_Read_Data(CLawlessC_Degree, V_ucReponseBuf, &V_usDataLen, &V_usCodeData);
		if(V_ucReturnData != C_OK)
		{
			return;
		}
		PF_OneDataReversed(V_ucReponseBuf, &V_ucbuf1[CF_O_OPI_LawLessIC], (CLLawlessC_Degree - 1) );
		/*����дʱ��*/
		if(V_ucMsgNum == C_Msg_Card)
		{
			V_usDataLen = CL_Response_InIC;
			InF_Read_Data(CDate_Time, V_ucReponseBuf, &V_usDataLen, &V_usCodeData);
			PF_OneDataReversed(&V_ucReponseBuf[1], &V_ucbuf1[CF_O_OPI_RWRClock], (CLDate_Time - 1) );
		}
	}

	/*�ù̶�ֵ����CS��16*/
	V_ucbuf1[CF_O_OPI_Start] = 0x68;
	V_ucbuf1[CF_O_OPI_CMD] = 0x11;
	V_ucbuf1[CF_O_OPI_Len] = 0x00;
	V_ucbuf1[CF_O_OPI_Len+1] = CL_OPI-6;		/*49-(68 11 00 2b cs 16)*/

	/*����CS*/
	V_ucbuf1[CF_O_OPI_CS] = 0;
	for(i = 1; i < (CL_OPI - 2); i++)				/*ȥ��68 cs 16*/
	{
		V_ucbuf1[CF_O_OPI_CS] = V_ucbuf1[CF_O_OPI_CS] + V_ucbuf1[i];
	}
	V_ucbuf1[CF_O_OPI_End] = 0x16;

	/*�Ƚ��ļ�ǰ���Ƿ���ͬ����ͬ��ˢ��*/
	if(PF_Campare_Data(V_ucbuf1, V_ucbuf2, CL_OPI) != C_Equal)
	{
		WriteBinFile(C_ESAM, V_ucbuf1, C_F_OpInfo, CF_O_OPI_Start, CL_OPI);
	}
}


/*******************************************************************************
����ԭ�ͣ�	ushort16 InF_S_Authentication(uchar8 *pV_ucData, uchar8 *pV_ucLen)
����������	�����֤�ӿں���
���������	pV_ucData:     ���ݵ���ʼָ�루���ġ�������ͷ�ɢ���ӣ�
			*pV_ucLen:   ���ݳ���(�̶���3*8=24 �ֽ�)
���������	*P_DataPtr: ����(�����2��ESAM���кš������֤��Чʱ��������������ص���վ��)
			*pV_ucLen:   �������ݳ���(�̶����س�4+8+2 = 14)
���ز�����	C_OK        ��ʾ�ɹ�
			������ʾ����: C_SERR_AF/  C_SERR_OtherErr

����λ�ã�
��    ע��
*******************************************************************************/
ushort16 InF_S_Authentication(uchar8 *pV_ucData, uchar8 *pV_ucLen)
{
	uchar8 		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucReturnData;
	ushort16	V_usReturnData16, V_usDataLen16;
	ushort16	V_usDataEnCode;

	/*�жϳ����Ƿ���ȷ*/
	if(*pV_ucLen != C_Authentication_Len)
	{
		return(C_SERR_OtherErr);
	}

	/*�����ݲ��ţ��жϺ��յ��ķ�ɢ�����Ƿ�һ��*/
	V_usDataLen16 = CLMeter_Num;
	V_ucReturnData = InF_Read_Data(CMeter_Num, &V_ucbuf[0], &V_usDataLen16, &V_usDataEnCode);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);		/*��Ŷ�����*/
	}

	V_ucReturnData = PF_Campare_Data(&V_ucbuf[0], &pV_ucData[C_Auth_O_Dis_factor], CLMeter_Num_645); /*6�ֽ�*/
	if(V_ucReturnData != C_Equal)		/*��ɢ���Ӹ�2λӦ��Ϊ0   ǰ2�ֽڲ���*/
	{
		return(C_SERR_OtherErr);
	}

	/*�Խ��յ����Ľ��еߵ����Ա��������ʹ�á�*/
	DataReversed(CDI_Auth, pV_ucData, C_RItem_Len_Auth);

	SF_ColdReset_7816_Esam_No();

	InF_Clear698ConectTimer();

	/*��ŷ�ɢ�õ���ʱ��Կ���������R1���м��ܣ���ȡ����K2*/
	V_usDataLen16 = CLen_S_BufMaxLen;
	PF_CopyDataBytes((uchar8 *)TB_AuthDistributedkey_645, &V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam);
	PF_CopyDataBytes(&pV_ucData[C_Auth_O_Dis_factor], &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], CL_Auth_Dis_factor);		/*�����ɢ���ӡ���û�����ݵߵ�����*/
	PF_CopyDataBytes(&pV_ucData[C_Auth_O_Rand1], &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam + CL_Auth_Dis_factor], CL_Auth_Rand1);	/*����RAND1����û�����ݵߵ�����*/
	V_usReturnData16 = INF_SendData_698_Esam(&V_ucbuf[0], (CLen_TB_ESAM_Lc_698_Esam + CL_Auth_Dis_factor + CL_Auth_Rand1), &V_ucbuf[0], &V_usDataLen16);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SERR_AF);
	}

	/*�ȶ��յ�������K1�������1���ܺ�����K2����������֤ͨ��!*/
	V_ucReturnData = PF_Campare_Data(&V_ucbuf[CLen_Respond_Auth], &pV_ucData[C_Auth_O_CiphertextK1], CL_Auth_CiphertextK1);
	if(V_ucReturnData != C_Equal)
	{
		return(C_SERR_AF);
	}

	/*********   ����Ϊ�÷��ز��� *********************************************************/
	/*��ȡ�����2������Ϊ4�����ڷ�����վ��*/
	V_usDataLen16 = CLen_S_BufMaxLen;
	PF_CopyDataBytes((uchar8 *)TB_GetChallenge_645_Esam, &V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam);
	V_usReturnData16 = INF_SendData_698_Esam(&V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam, &V_ucbuf[0], &V_usDataLen16);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SERR_AF);
	}
	PF_CopyDataBytes(&V_ucbuf[CLen_Respond_Auth], pV_ucData, CLen_Rand2);
	*pV_ucLen = CLen_Rand2;

	/*��ȡESAM���кţ�����Ϊ8�����ڷ�����վ��*/
	V_usDataLen16 = CLen_S_BufMaxLen;
	PF_CopyDataBytes((uchar8 *)TB_RdESAMNo_645,&V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam);
	V_usReturnData16 = INF_SendData_698_Esam(&V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam, &V_ucbuf[0], &V_usDataLen16);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SERR_AF);
	}
	PF_CopyDataBytes(&V_ucbuf[CLen_Respond_Auth], &pV_ucData[CLen_Rand2], CLen_ESAMNo);
	*pV_ucLen = CLen_Rand2 + CLen_ESAMNo;



	/*��ȡ�����֤��Чʱ����*/
	V_usDataLen16 = CLen_S_BufMaxLen;						/*�����֤��Чʱ���ĳ���Ϊ4*/
	V_ucReturnData = S_ReadEsam_698(V_ucbuf, &V_usDataLen16, 0x0500);

	/*DataLen =  (uchar8)V_usDataLen16;*/
	PF_OneDataReversed(V_ucbuf, V_ucbuf, V_usDataLen16);
	PF_OneDataReversed(V_ucbuf, V_ucbuf, CLen_AuthPTime);

	if( (V_ucReturnData != C_OK ) || ( (V_ucbuf[0] == 0x00) && (V_ucbuf[1] == 0x00) ) )
	{
		V_ucbuf[1] = C_AuthPTime_LByte;
		V_ucbuf[0] = C_AuthPTime_HByte;				/*����ע��ESAM���ص��Ǵ��ģʽ������Ҫͳһ�ߵ�*/
	}
	PF_CopyDataBytes(&V_ucbuf[0], &pV_ucData[C_R_Auth_O_AuthPTime], CLen_AuthPTime);
	*pV_ucLen = *pV_ucLen + CLen_AuthPTime;

	/*��Ӧ������Ҫ�ߵ���645��ʽ!*/
	DataReversed(CDI_Auth_R, pV_ucData, C_RItem_Len_AuthR);

	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_Certification_Invaliad(uchar8 *pV_ucData,uchar8 *pV_ucLen)
����������	��������֤ʧЧ������ʵ������֯Ӧ��֡
���������	pV_ucData:		�������ݻ�����
			*pV_ucLen:	��������󳤶�
���������	*pV_ucData:	ESAM��6�ֽڿͻ���ţ�4�ֽ�ʣ���
			4�ֽڹ��������4�ֽ���Կ��Ϣ
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��
*******************************************************************************/
ushort16  InF_S_Certification_Invaliad(uchar8 *pV_ucData,uchar8 *pV_ucLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen], V_ucDataLen;
	uchar8		V_ucReturnData;
	uchar8  	V_ucActionID;
	ushort16 	V_usDataLen;
	ushort16	V_usDataEnCode;

	if(*pV_ucLen < (CLCustomer_Num + CLChargeBal_Hex_Cent + CL_PurchasingE_Num + CLKey_State) )
	{
		return(C_SERR_OtherErr);
	}

#if 0
	/*����Ǳ��ر�ˢ��ESAM�е�ʣ���
	�������ǲ���Ҫ�ܱ�����͡�����Զ�̱�����ݲ�ʣ�����Ƕ���������*/
 	V_ReturnData = InF_ReadEnergy_Protocol(CChargeBal_Hex_Cent, V_ucbuf, CLChargeBal_Hex_Cent);
 	if(V_ReturnData == C_OK)
	{
		InF_S_UpdataChargeBalInESAM(V_ucbuf);
	}							/*�������ɹ�����ˢ��ESAM*/


#endif

	/*ͬ��ESAM��ʣ���15min����*/
	UpdataChargeBalInESAMWithSwitch();

	/*���ͻ���š�
	�����ݲ�*/
	V_usDataLen = CLCustomer_Num;
	V_ucReturnData = InF_Read_Data(CCustomer_Num, &V_ucbuf[C_AInvR_O_CustomerNo], &V_usDataLen, &V_usDataEnCode);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}

#if 0
	/*��ESAM �ڲ�����Ϣ�ļ���*/
	V_ReturnData = ReadBinFileNoMac(&V_ucbuf[C_AInvR_O_CustomerNo], C_F_ParmInf, CF_O_CNumInParm,CLCustomer_Num);
	if(V_ReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}
	PF_OneDataReversed(&V_ucbuf[C_AInvR_O_CustomerNo], &V_ucbuf[C_AInvR_O_CustomerNo], CLCustomer_Num);
#endif


	/*��ʣ����,����¼�ļ����ѽ����ݵߵ�*/
	V_ucDataLen = CLen_S_BufMaxLen - CLCustomer_Num;
	V_ucReturnData = ReadRecordFile(&V_ucbuf[C_AInvR_O_ChargeB_B], &V_ucDataLen, C_ChargeBal_Mac);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}

	/*���������,����¼�ļ����ѽ����ݵߵ�*/
	V_ucDataLen = CLen_S_BufMaxLen - CLCustomer_Num - CLChargeBal_Hex_Cent;
	V_ucReturnData = ReadRecordFile(&V_ucbuf[C_AInvR_O_PE_Num], &V_ucDataLen, C_PurchasingE_Num_Mac);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}

#if 0
	/*����Կ״̬�������ݲ�*/
	V_usDataLen = CLKey_State;
	V_ReturnData = InF_Read_Data(CKey_State, &V_ucbuf[C_AInvR_O_Key_State], &V_usDataLen, &V_usDataEnCode);
	if(V_ReturnData != C_OK)
	{
		return(C_Error);
	}

	V_ReturnData = ReadBinFileNoMac(&V_ucbuf[C_AInvR_O_Key_State], C_F_LKeyState, CF_O_KeyState,CLKey_State);
	if(V_ReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}
	PF_OneDataReversed(&V_ucbuf[C_AInvR_O_Key_State], &V_ucbuf[C_AInvR_O_Key_State], CLKey_State);
#endif


	/*����Կ״̬����ESAM*/
	V_ucActionID = (uchar8)(CKey_State >> 8);

	V_usDataLen = 30;
	V_ucReturnData = S_ReadEsam_698(&V_ucbuf[C_AInvR_O_Key_State], &V_usDataLen, V_ucActionID);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}
	PF_OneDataReversed(&V_ucbuf[C_AInvR_O_Key_State], &V_ucbuf[C_AInvR_O_Key_State], CLKey_State);


	*pV_ucLen = CLCustomer_Num + CLChargeBal_Hex_Cent + CL_PurchasingE_Num + CLKey_State;
	PF_CopyDataBytes(V_ucbuf, pV_ucData, *pV_ucLen);

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�void	InF_S_PowerOn(void)
������������ȫģ���ϵ��ʼ��
�����������
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void	InF_S_PowerOn(void)
{
	SV_SafeByte = 0x00;
	SV_UpdateMInEsamTimer = 0;
}


/*******************************************************************************
����ԭ�ͣ�ushort16	InF_S_WriteCertificationTime(uchar8	*pV_ucData)
������������������֤ʱ������
���������P_Data:		���������׵�ַ���̶�2+4 �ֽڣ�����645��С��ģʽ
�����������
���ز�����C_OK/C_SERR_ESAM_VF/C_SERR_OtherErr
����λ�ã���
��    ע����
*******************************************************************************/
ushort16	InF_S_WriteCertificationTime(uchar8	*pV_ucData)
{
	uchar8	V_ucReturnData;

	/*�ж������Ƿ�Ϊ�Ϸ�*/
	V_ucReturnData = PF_Judge_BCD(CLen_AuthPTime, pV_ucData);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}

	/*�����ݽ��������ݽ��еߵ�*/
	DataReversed(CDI_CPTime, pV_ucData, C_RITem_Len_CPTime);

	V_ucReturnData = WriteBinFileMac(C_ESAM, pV_ucData, C_F_ParmInf, CF_O_AuthPTime, (CLen_AuthPTime + C_MacLen) );

	if(V_ucReturnData != C_OK)
	{
		if(V_ucReturnData == C_IC_MAC_ERR)
		{
			return(C_SERR_ESAM_VF);
		}
		else
		{
			return(C_SERR_OtherErr);
		}
	}
	else
	{
		return(C_OK);
	}

}


/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_IRCertification_Request(uchar8 *pV_ucData,uchar8 *pV_ucLen,uchar8 V_ucBufMaxLen)
����������	��ɺ�����֤����
���������	pV_ucData:		���������׵�ַ��
			*pV_ucLen:		����*P_Data���ȡ�ʵ�ʹ̶�8 �ֽ�
���������	*pV_ucData:		����������ݡ����ձ�ţ����кţ�K1��Rand2����
			*pV_ucLen:		���ز�������6+8+8+8
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��
*******************************************************************************/
ushort16  InF_S_IRCertification_Request(uchar8 *pV_ucData,uchar8 *pV_ucLen,uchar8 V_ucBufMaxLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucReturnData;
	ushort16	V_usReturnData16;
	uchar8		V_ucReponseBuf[CL_IRReq_Response+2];		/*��Ӧ���ݣ��ײ�Ӧ���ǲ���Ҫ����2�ֽ�SW������������2�ֽ�*/
	uchar8		V_ucReponseLen = 0;							/*��Ӧ���ݳ�����ʱ����*/
	ushort16 	V_usDataLen16;
	ushort16	V_usDataEnCode;

	/*�жϻ������Ƿ�С��Ӧ���ص����ݳ���*/
	if((V_ucBufMaxLen < CL_IRReq_Response) || (*pV_ucLen !=CL_Auth_Rand1) )
	{
		return(C_SERR_OtherErr);
	}

	/*����ţ���ΪӦ�����ݵ� 1 ��*/
	V_usDataLen16 = CLMeter_Num;
	V_ucReturnData = InF_Read_Data(CMeter_Num, &V_ucReponseBuf[C_RIRCReq_O_M_Num_645], &V_usDataLen16, &V_usDataEnCode);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}
	V_ucReponseLen = V_ucReponseLen + CLMeter_Num_645;

	/*��ȡESAM���к�,��ΪӦ�����ݵĵ�2��*/
	V_usDataLen16 = CL_IRReq_Response - V_ucReponseLen;
	V_usReturnData16 = INF_SendData_698_Esam
				((uchar8 *)TB_RdESAMNo_645, CLen_TB_ESAM_Lc_698_Esam, &V_ucReponseBuf[C_RIRCReq_O_ESAMNo_645], &V_usDataLen16); /*2�ֽڣ�698���8�ֽڣ�645���6�ֽڣ�*/
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SERR_OtherErr);
	}
	PF_OneDataReversed(&V_ucReponseBuf[C_RIRCReq_O_ESAMNo_645], &V_ucReponseBuf[C_RIRCReq_O_ESAMNo_645], CLen_ESAMNo);
	V_ucReponseLen = V_ucReponseLen + CLen_ESAMNo;
	/*ȡ�����1�ļ��ܺ�����K1,��ΪӦ�����ݵĵ�3�*/
	PF_CopyDataBytes((uchar8 *)TB_AuthDistributedkey_645, &V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam);		/*��ȡ����ͷ*/
	PF_CopyDataBytes(&V_ucReponseBuf[C_RIRCReq_O_M_Num_645], &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], CLMeter_Num_645);	/*��ȡ���*/
	V_ucbuf[CLen_TB_ESAM_Lc_698_Esam + CLMeter_Num_645] = 0x00;
	V_ucbuf[CLen_TB_ESAM_Lc_698_Esam + CLMeter_Num_645+1] = 0x00;
	PF_OneDataReversed(&V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], (CLMeter_Num_645 + 2));	/*���+0000�ߵ���ɷ�ɢ����*/
	PF_CopyDataBytes(pV_ucData,&V_ucbuf[CLen_TB_ESAM_Lc_698_Esam + CLMeter_Num_645 + 2], CL_Auth_Rand1);				/*ȡRand1*/
	PF_OneDataReversed(&V_ucbuf[C_RIRCReq_O_RandK1_645], &V_ucbuf[C_RIRCReq_O_RandK1_645], CL_Auth_Rand1);				/*�����1�ߵ���ʹ��*/
	V_usDataLen16 = CL_Auth_CiphertextK1;
	V_usReturnData16 = INF_SendData_698_Esam(&V_ucbuf[0], (CLen_TB_ESAM_Lc_698_Esam + CLMeter_Num_645 + 2 + CL_Auth_Rand1), &V_ucbuf[0], &V_usDataLen16);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SERR_OtherErr);
	}
	PF_CopyDataBytes(V_ucbuf,&V_ucReponseBuf[C_RIRCReq_O_RandK1_645], CL_Auth_CiphertextK1);	/*ȡK1*/
	PF_OneDataReversed(&V_ucReponseBuf[C_RIRCReq_O_RandK1_645], &V_ucReponseBuf[C_RIRCReq_O_RandK1_645], CL_Auth_CiphertextK1);
	V_ucReponseLen = V_ucReponseLen + CL_Auth_CiphertextK1;

	/*��ȡ�����2,Rand2,��ΪӦ�����ݵĵ�4��*/
	V_usDataLen16 = CLen_S_BufMaxLen;
	PF_CopyDataBytes((uchar8 *)TB_IR_ID_Request2_698, &V_ucbuf[0], CLen_TB_ESAM_Le_698_Esam);
	V_usReturnData16 = INF_SendData_698_Esam(&V_ucbuf[0], CLen_TB_ESAM_Le_698_Esam, &V_ucbuf[0], &V_usDataLen16);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SERR_OtherErr);
	}
	PF_OneDataReversed(&V_ucbuf[0], &V_ucReponseBuf[C_RIRCReq_O_Rand2_645], CL_RIRCReq_Rand2);
	V_ucReponseLen = V_ucReponseLen + CL_RIRCReq_Rand2;

	/*��ֵ���ڲ���*/
	PF_CopyDataBytes(V_ucReponseBuf, pV_ucData, V_ucReponseLen);
	*pV_ucLen = V_ucReponseLen;

	return(C_OK);

}


/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_IRCertification_Instruction(uchar8 *pV_ucData)
����������	��ɺ�����֤
���������	pV_ucData:		���������׵�ַ �̶�8 �ֽ�
���������	��
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��
*******************************************************************************/
ushort16  InF_S_IRCertification_Instruction(uchar8 *pV_ucData)
{
	uchar8 V_ucDataBuffer[MaxLength_698];
	ushort16 V_usReceiveLen,V_usReturnData16,V_usSendLen;
	uchar8 V_ucAuthSessionLen;

	PF_CopyDataBytes((uchar8 * )TB_IR_ID_698, V_ucDataBuffer, CLen_TB_ESAM_6_698);
	/*����RN*/
	V_ucAuthSessionLen = CL_Auth_CiphertextK2;
	PF_OneDataReversed(pV_ucData, &V_ucDataBuffer[CLen_TB_ESAM_6_698], V_ucAuthSessionLen);

	/********* ���·���esam���� *********************************************************/
	V_usSendLen =CLen_TB_ESAM_6_698 + V_ucAuthSessionLen;		/*�������ݳ���*/
	V_usReceiveLen = MaxLength_698;		/*����������󳤶�*/
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SCErr_DAR);
	}

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	JudgeS_Key_V_Mac_InP(uchar8 *pV_ucData, uchar8 V_ucDataLen, uchar8 *pV_ucMsgReupdataKey, uchar8 *pV_ucKeyNum)
����������	�����Կ����Mac��֤�����������ȷ�Ե��жϡ�
���������	pV_ucData:				���������׵�ַ������ΪV_ucKeyNum*36
			V_ucDataLen:			��������ĳ��ȡ�
			pV_ucMsgReupdataKey:	���ز�����ַ
			pV_ucKeyNum:			������Կ������ַ
���������	*pV_ucMsgReupdataKey:	�����Ƿ���Ҫ���¸��µı�־
			*pV_ucKeyNum:			������Կ��Ŀ��(1-4)
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	JudgeS_Key_V_Mac_InP(uchar8 *pV_ucData, uchar8 V_ucDataLen, uchar8 *pV_ucMsgReupdataKey, uchar8 *pV_ucKeyNum)
{
	uchar8	i;
	uchar8	V_ucoffset;
	uchar8	V_ucKeyNumTemp;
	uchar8	V_ucKeyNum;

	*pV_ucMsgReupdataKey = CMsg_Null;							/*Ĭ�ϲ����¸���*/

	/*��ڲ����Ϸ����ж�,���ݳ��ȵ��ж�*/

	switch(V_ucDataLen)
	{
		case		(CL_KeyWithInfo_1 + C_MacLen):
			V_ucKeyNum = 1;
			break;
		case		(CL_KeyWithInfo_2 + C_MacLen):
			V_ucKeyNum = 2;
			break;
		case		(CL_KeyWithInfo_3 + C_MacLen):
			V_ucKeyNum = 3;
			break;
		case		(CL_KeyWithInfo_4 + C_MacLen):
			V_ucKeyNum = 4;
			break;
		default:
			return(C_SERR_OtherErr);
	}

	/*��Կ�������ж�*/

	V_ucKeyNumTemp = InF_Get_Key_Tol_Num();
	V_ucoffset = C_UpKey_O_KeyNum_1;

	for(i=0; i < V_ucKeyNum; i++)
	{
		if(pV_ucData[V_ucoffset] != V_ucKeyNumTemp)
		{
			*pV_ucMsgReupdataKey = CMsg_ReUpdataKey;		/* �յ�����Կ��Ϣ����Կ���������������ݲ�*/
			return(C_SERR_OtherErr);					/*����������*/
		}
		V_ucoffset = V_ucoffset + CL_KeyWithInfo_1;
	}

	/*��Կ��Ϣ��������Կ��ű���С�����ݲ���Կ������*/
	V_ucoffset = C_UpKey_O_KeyNo_1;
	for(i=0;i<V_ucKeyNum;i++)
	{
		if(pV_ucData[V_ucoffset] >= V_ucKeyNumTemp)					/*��Կ��Ŵ�0��ʼ��*/
		{
			*pV_ucMsgReupdataKey = CMsg_ReUpdataKey;		/* �յ�����Կ��Ϣ����Կ��Ŵ�����Կ������*/
			return(C_SERR_OtherErr);					/*����������*/
		}
		V_ucoffset = V_ucoffset + CL_KeyWithInfo_1;
	}

	/*��Կ��Ϣ����Կ״̬������ȣ��ҵ���00��01*/
	if( (pV_ucData[C_UpKey_O_KeyState_1] != CInfo_TestKey)
		&&(pV_ucData[C_UpKey_O_KeyState_1] != CInfo_OfficialKey) )
	{
		*pV_ucMsgReupdataKey = CMsg_ReUpdataKey;		/* �յ�����Կ��Ϣ����Կ״̬�Ȳ��ǹ�Կ�ֲ���˽Կ*/
		return(C_SERR_OtherErr);					/*����������*/
	}
	V_ucoffset = C_UpKey_O_KeyState_1;
	for(i = 0; i < V_ucKeyNum; i++)
	{
		if(pV_ucData[V_ucoffset] !=pV_ucData[C_UpKey_O_KeyState_1])
		{
			*pV_ucMsgReupdataKey = CMsg_ReUpdataKey;		/* �յ�����Կ��Ϣ����Կ״̬�Ȳ��ǹ�Կ�ֲ���˽Կ*/

			return(C_SERR_OtherErr);					/*����������*/
		}
		V_ucoffset = V_ucoffset + CL_KeyWithInfo_1;
	}

	*pV_ucKeyNum = V_ucKeyNum;						/*ȡ��Կ��Ϣ*/

	return(C_OK);

}



/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_Key_Update (uchar8 *pV_ucData, uchar8 V_ucKeyNO)
����������	�����Կ���£���Կ״̬����ˢ��
���������	pV_ucData:		���������׵�ַ������Ϊ32�ֽ�
			V_ucKeyNO:		��Կ���,00Ϊ������Կֵ
���������
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��	pV_ucData�������ޱ仯
*******************************************************************************/
ushort16  InF_S_Key_Update (uchar8 *pV_ucData, uchar8 V_ucKeyNO)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucDataLen;
	ushort16	V_usReturnData16;
	uchar8		V_ucKeyNum;

	/*�ж���Կ����Ƿ������Կ������*/
	V_ucKeyNum = InF_Get_Key_Tol_Num();
	if(V_ucKeyNO > V_ucKeyNum)
	{
		return(C_SERR_OtherErr);
	}

	/*������Կ��ESAM������Ϊ0x84,0xD4,0x01,0xFF,0x20  ���Ϊ���أ�P2=00*/
	PF_CopyDataBytes( (uchar8 *)TB_UpdateKey, V_ucbuf, CLen_TB_ESAM_Lc);
	if(V_ucKeyNO == 0x00)
	{
		V_ucbuf[3] = 0x00;			/*P2=00 �������أ�=0xFF����������Կ*/
	}
	V_ucDataLen = CLen_S_BufMaxLen;
	PF_OneDataReversed(pV_ucData, &V_ucbuf[CLen_TB_ESAM_Lc], CL_Key);		/*��Կ�ߵ���д��ESAM*/
	V_usReturnData16 = INF_SendData_7816_Esam(&V_ucbuf[0], (CLen_TB_ESAM_Lc + CL_Key), &V_ucbuf[0], &V_ucDataLen);
	if( (V_usReturnData16 == C_Security_CommandOk)
		|| ( (V_usReturnData16 & C_Resp_61XXType) == C_Security_ProcessOk) )
	{
		return(C_OK);
	}
	else
	{
		return(C_SERR_OtherErr);
	}
}


/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_ReadKeyStateInESAM(uchar8 *pV_ucData,uchar8 *pV_ucDataLen)
����������	��ȡESAM�е���Կ״̬
���������	pV_ucData:		�������ָ��
			*pV_ucDataLen	���ٵĻ������ĳ���
���������	*pV_ucData:		��Կ״̬
			*pV_ucDataLen	��������ʵ�ʳ���
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��	���ڲ�����Կ״̬����645С��ģʽ��
*******************************************************************************/
ushort16  InF_S_ReadKeyStateInESAM(uchar8 *pV_ucData, uchar8 *pV_ucDataLen)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;

	/*���ȺϷ����ж�*/
	if(*pV_ucDataLen < CLKey_State)
	{
		return(C_SERR_OtherErr);
	}

/*��ȡ����*/
	V_ucReturnData = InF_SC_RDBinFileNoMac(C_ESAM, C_F_LKeyState, CF_O_KeyState, CLKey_State, V_ucbuf);
	if(V_ucReturnData == C_OK)
	{
		PF_OneDataReversed(V_ucbuf, pV_ucData, CLKey_State);
		*pV_ucDataLen = CLKey_State;

		return(C_OK);
	}
	else
	{
		return(C_SERR_OtherErr);
	}

}


/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_GetStatus(uchar8 *pV_ucData,uchar8 *pV_ucLen)
����������	״̬��ѯ
���������	pV_ucData:		�������ָ��
			*pV_ucLen		���ٵĻ������ĳ���
���������	*pV_ucData:		״̬��ѯ���ݡ���ʣ����+Mac���������+Mac���ͻ���ţ���Կ״̬��
			*pV_ucLen		��������ʵ�ʳ���
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��
*******************************************************************************/
ushort16  InF_S_GetStatus(uchar8 *pV_ucData, uchar8 *pV_ucLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucReturnData;
	uchar8		V_ucDataLen;
	uchar8		V_ucEnRecMaxLen = CLen_S_BufMaxLen;
	uchar8		V_ucMAC[4]={0,0,0,0};
	ushort16  	V_usActionID;
	ushort16 	V_usDataLen;

	if(*pV_ucLen < CL_GetStatusR)
	{
		return(C_SERR_OtherErr);
	}

	/*����Ǳ��ر�ˢ��ESAM�е�ʣ���
	�������ǲ���Ҫ�ܱ�����͡�����Զ�̱�����ݲ�ʣ�����Ƕ���������*/


	/*ͬ��ESAM��ʣ���15min����*/
	UpdataChargeBalInESAMWithSwitch();

	/*��ʣ����,�������,���ͻ����,����¼�ļ����ѽ����ݵߵ�*/
	V_ucDataLen = V_ucEnRecMaxLen;
	V_ucReturnData = ReadRecordFile_1(&V_ucbuf[C_GetS_O_ChgBlHC], &V_ucDataLen);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}
	PF_CopyDataBytes(V_ucbuf, pV_ucData, CLChargeBal_BCD);
	PF_CopyDataBytes(V_ucMAC, &pV_ucData[CLChargeBal_BCD], C_MacLen);
	PF_CopyDataBytes(&V_ucbuf[C_PPNumOff], &pV_ucData[CLChargeBal_BCD + C_MacLen], CL_PurchasingE_Num);
	PF_CopyDataBytes(&V_ucbuf[C_MacOff], &pV_ucData[CLChargeBal_BCD + C_MacLen + CL_PurchasingE_Num], C_MacLen);
	PF_CopyDataBytes(&V_ucbuf[C_CustomerNumOff], &pV_ucData[CLChargeBal_BCD + C_MacLen + CL_PurchasingE_Num + C_MacLen], CLCustomer_Num);

#if 0
	/*����Կ״̬�������ݲ�*/
	pDataLen = CLKey_State;
	V_ReturnData = InF_Read_Data(CKey_State, &V_ucbuf[C_GetS_O_Key_State], &pDataLen);
	if(V_ReturnData != C_OK)
	{
		return(C_Error);
	}

	PF_CopyDataBytes(V_ucbuf, &pV_ucData[CLChargeBal_BCD + C_MacLen + CL_PurchasingE_Num + C_MacLen + CLCustomer_Num], CLKey_State);
#endif

	/*����Կ״̬����ESAM*/
	V_usActionID = (uchar8)CKey_State ;

	V_usDataLen = 30;
	V_ucReturnData = S_ReadEsam_698(&V_ucbuf[C_GetS_O_Key_State], &V_usDataLen, V_usActionID);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}
	PF_OneDataReversed(&V_ucbuf[C_GetS_O_Key_State], &V_ucbuf[C_GetS_O_Key_State], CLKey_State);

	*pV_ucLen = C_GetS_O_Key_State + CLKey_State;

	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�	ushort16      InF_S_DataExcerption(uchar8 *pV_ucData,uchar8 *pV_ucLen)
����������	���ݻس�
���������	*pV_ucData:		�س���ʶ���̶�8�ֽ�
			*pV_ucLen		���ٵĻ������ĳ���
���������	*pV_ucData:		�س�����(�س���ʶ8+�س�����Ld+Mac 4
			*pV_ucLen		��������ʵ�ʳ���
���ز�����	C_OK/C_SERR_OtherErr
����λ�ã�
��    ע��	����ǰ��֤p_Dataָ�����ݹ̶�8�ֽ�
*******************************************************************************/
ushort16  InF_S_DataExcerption(uchar8 *pV_ucData,uchar8 *pV_ucLen)
{
	uchar8		V_ucReturnData,V_ucFile_Ld_8;
	uchar8		V_ucDataLen;
	ushort16	V_usFile_Ld;
	ushort16	V_usFile_Offset;
	ushort16	V_usFile_No;
	ushort16	V_usFile_Dir;
	ushort16	V_usResponseLen = CL_FileDataCode;


	/*���ļ���ʶ���н�����*/
	PF_Buffer2ToUshort16(&pV_ucData[C_DExc_O_Dir], &V_usFile_Dir);
	PF_Buffer2ToUshort16(&pV_ucData[C_DExc_O_FileNo], &V_usFile_No);
	PF_Buffer2ToUshort16(&pV_ucData[C_DExc_O_Offset], &V_usFile_Offset);
	PF_Buffer2ToUshort16(&pV_ucData[C_DExc_O_Ld], &V_usFile_Ld);
	V_ucFile_Ld_8 = pV_ucData[C_DExc_O_Ld];

	/*�ж���ڲ����Ƿ���ȷ,�ļ�Ŀ¼����жϱ�����DF01*/
	if(V_usFile_Dir != C_F_MainDir)
	{
		return(C_SERR_OtherErr);
	}
	/*�����������ļ�����Կ�ļ�*/
	if( (V_usFile_No == C_F_MF) || (V_usFile_No == C_F_MasterKey) )
	{
		return(C_SERR_OtherErr);
	}

	/*�����ж��Ƿ���ȷ*/
	if(V_usFile_No == C_F_Purse)
	{
		/*�س�Ǯ���ļ�����������������Ӧ��ʣ����+Mac�͹������+mac*/
		V_usResponseLen = V_usResponseLen + CLChargeBal_Hex_Cent + CL_PurchasingE_Num + CLCustomer_Num + C_MacLen;
	}
	else
	{
		V_usResponseLen = V_usResponseLen + V_usFile_Ld + C_MacLen;
	}
	if( (*pV_ucLen < V_usResponseLen) || (V_usResponseLen > (C_F_Pam_Max - 2) ) )		/*��������С�ˣ����ȡ���ݳ���100*/
	{
		return(C_SERR_OtherErr);
	}

	/*ˢ��ESAM��Ǯ���ļ��������ļ��еĸ������*/
	if( (V_usFile_No == C_F_Purse) || (V_usFile_No == C_F_OpInfo) )
	{
		/*���ڻس�Ǯ���ļ��������ļ�ʱ������Ǯ���ļ���������Ϣ�ļ���ʣ����
		�Ȳ��������ݲ�ͬ������15min����
		ͬ��ESAM��ʣ���15min����*/
		UpdataChargeBalInESAMWithSwitch();
	}
	if(V_usFile_No == C_F_OpInfo)	/*ͬ�������ļ���ע�����������ļ����κ���һ�β�ͬ�Ÿ��¡�*/
	{
		Updata_ESAM_OpParm(C_Msg_Communication);
	}

	/*����ǻس�Ǯ���ļ��������ļ�ƫ�ƣ����ȶ�����Ӧ��ʣ����+Mac,�������+Mac*/
	if(V_usFile_No == C_F_Purse)
	{
		/*��Mac��ʣ����+�������+�ͻ����+MAC*/
		V_ucDataLen = V_usResponseLen - CL_FileDataCode;
		V_ucReturnData = ReadRecordFile_1(&pV_ucData[C_DExcR_O_ChgBlHC], &V_ucDataLen);
		if(V_ucReturnData != C_OK)
		{
			return(C_SERR_OtherErr);
		}
	}
	/*����ǻس������ļ�*/
	else
	{
		/*���������ļ�*/
		V_ucReturnData = ReadBinFileMac(&pV_ucData[C_DExcR_O_Data], &pV_ucData[C_DExc_O_FileNo], &pV_ucData[C_DExc_O_Offset], &pV_ucData[C_DExc_O_Ld]);
		/*���ݺ�Mac�ֱ�ߵ���*/
		PF_OneDataReversed(&pV_ucData[C_DExcR_O_Data], &pV_ucData[C_DExcR_O_Data], V_ucFile_Ld_8);
		PF_OneDataReversed(&pV_ucData[C_DExcR_O_Data + V_ucFile_Ld_8], &pV_ucData[C_DExcR_O_Data + V_ucFile_Ld_8], C_MacLen);
		if(V_ucReturnData != C_OK)
		{
			return(C_SERR_OtherErr);
		}
	}

	*pV_ucLen = V_usResponseLen;

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	InF_S_Is_ParmPlainTextMAC(ulong32	V_ulDI,	uchar8 	*pV_ucDataLen)
����������	�ж��Ƿ�Ϊ1����������򷵻ظò�������
���������	pV_ucDataLen:	����ָ��
			V_ulDI		���ݱ�ʶ
���������	*pV_ucDataLen	1��������ȣ�����Mac
���ز�����	C_OK/C_Error
����λ�ã�
��    ע��	������֧��ͨ��ģ��֧�ֵı�ʶ�룬�������ֱ���Զ�̱�
*******************************************************************************/
uchar8	InF_S_Is_ParmPlainTextMAC(ulong32	V_ulDI,	uchar8 	*pV_ucDataLen)
{
	uchar8	i;

	for(i = 0;i < C_ParmPlainText_MaxNum; i++)
	{
		if(V_ulDI == TB_ParmPlainText[i].DI)
		{
			*pV_ucDataLen = TB_ParmPlainText[i].Len;

			return(C_OK);
		}
	}

	return(C_Error);
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	LookForStr_ParmPlainText(ulong32	V_ulDI,	uchar8 	*pV_ucParmPlainText_O)
����������	���������ʶ�룬����Str_ParmPlainText�ͱ���
���������	pV_ucParmPlainText_O:	����������±�ָ��
			V_ulDI			���ݱ�ʶ
���������	*pV_ucParmPlainText_O	����������±�
���ز�����	C_OK/C_Error
����λ�ã�
��    ע��	������֧��ͨ��ģ��֧�ֵı�ʶ�룬�������ֱ���Զ�̱�
*******************************************************************************/
uchar8	LookForStr_ParmPlainText(ulong32	V_ulDI,	uchar8 	*pV_ucParmPlainText_O)
{
	uchar8	i;

	for(i=0; i < C_ParmPlainText_MaxNum; i++)
	{
		if(V_ulDI == TB_ParmPlainText[i].DI)
		{
			*pV_ucParmPlainText_O = i;

			return(C_OK);
		}
	}

	return(C_Error);
}


/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_WriteCustermerNumMAC(ulong32 V_ulDI,uchar8 *pV_ucData,uchar8 V_ucDataLen)
����������	�ͻ����дesam
���������	V_ulDI			���ݱ�ʶ
			*pV_ucData:		�������
			V_ucDataLen		�������ĳ���(����Mac)

���������	��
���ز�����	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
����λ�ã�
��    ע��	P_Data�������е�����ʱ������
*******************************************************************************/
ushort16  InF_S_WriteCustermerNumMAC(ulong32 V_ulDI, uchar8 *pV_ucData, uchar8 V_ucDataLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen],V_ucTemp[6];
	uchar8		V_ucReturnData;
	ushort16	V_usDataLen1;

	V_ucbuf[0] = 0x83;			/*����Mac���������ļ�����Ϊ00B0*/
	V_ucbuf[1] = 0x2A;
	V_ucbuf[2] = 0x8F;			/*FileNoΪ�ļ��̱�ʶ�룬���÷�ʽ1, 100x xxxx xxxxxΪ�̱�ʶ��*/
	V_ucbuf[3] = 0x06;			/*P2*/
	V_ucbuf[4] = 0x00;			/*Lc*/
	V_ucbuf[5] = 0x0A;			/*Lc*/

	/*��������+Mac���ֱ�ߵ�*/
	PF_OneDataReversed(pV_ucData, &V_ucbuf[6], (V_ucDataLen - C_MacLen));

	PF_OneDataReversed(&pV_ucData[(V_ucDataLen - C_MacLen)], &V_ucbuf[(6 + V_ucDataLen - C_MacLen)], C_MacLen);

	PF_OneDataReversed(V_ucbuf,GV_7816CMD.Header,CL_7816Header);		/*7816����ͷ�ݴ�*/

	V_usDataLen1 = CLen_S_BufMaxLen;

	GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucbuf,(6 + V_ucDataLen), V_ucbuf, &V_usDataLen1);
	V_ucReturnData = C_IC_ESAM_RDWR_ERR;

	if( (GV_7816CMD.SW1_2 !=C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		if( (GV_7816CMD.SW1_2 == C_Security_SafetyDataIncorrect) || (GV_7816CMD.SW1_2 == C_Security_MacErr) )
		{
			return(C_IC_MAC_ERR);
		}
		else
		{
			return(V_ucReturnData);
		}
	}



	/*�ͻ���Ų���macд�����ļ�*/
	PF_OneDataReversed(pV_ucData, V_ucTemp, (V_ucDataLen - C_MacLen) );

	V_ucReturnData = WriteBinFile(C_ESAM, V_ucTemp, C_F_OpInfo, CF_O_CNumInOP, CLCustomer_Num);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}


	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_WritePara_PlainTextMAC(ulong32 V_ulDI,uchar8 *pV_ucData,uchar8 V_ucDataLen)
����������	1�����Mac��֤��ESAM��Ӧ����д
���������	*pV_ucData:		�������
			V_ucDataLen		�������ĳ���(����Mac)
			V_ulDI		���ݱ�ʶ
���������	��
���ز�����	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
����λ�ã�
��    ע��	pV_ucData�������е�����ʱ�����ġ�
			������֧��ͨ��ģ��֧�ֵı�ʶ�룬�������ֱ���Զ�̱�
*******************************************************************************/
ushort16  InF_S_WritePara_PlainTextMAC(ulong32 V_ulDI, uchar8 *pV_ucData, uchar8 V_ucDataLen)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;
	uchar8	V_ucFile_Offset;
	uchar8	V_ucFile_No;
	uchar8	V_ucOffsetInOP;
	uchar8	V_ucParmPlainText_O;

	/*���Ȳ��ȷ���ڱ��TB_ParmPlainText��ƫ��,�Ҳ������������˳�*/
	V_ucReturnData = LookForStr_ParmPlainText(V_ulDI, &V_ucParmPlainText_O);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}
	V_ucFile_No = TB_ParmPlainText[V_ucParmPlainText_O].FileNo;
	V_ucFile_Offset = TB_ParmPlainText[V_ucParmPlainText_O].Offset;
	V_ucOffsetInOP = TB_ParmPlainText[V_ucParmPlainText_O].OffsetInOP;

	#if 0
	/*�ж����ݳ����Ƿ����*/
	if(DataLen != (TB_ParmPlainText[V_ucParmPlainText_O].Len) + C_MacLen)
	{
		return(C_SERR_OtherErr);
	}
	#endif
	/*���ݽ��еߵ��ߵ����������Buf���ܳ���ΪDataLen*/
	PF_CopyDataBytes(pV_ucData, V_ucbuf, V_ucDataLen);
	if(V_ulDI == CBackUp_RateFF_Price)
	{
		DataReversed(CBackUp_RateFF_Price, V_ucbuf, C_RItem_Len_RateBak);
	}
	else if(V_ulDI == CBackUp_Ladder_Table)
	{
		DataReversed(CBackUp_Ladder_Table,V_ucbuf,C_RITem_Len_LadderBak);
	}
	else	/*��������+Mac���ֱ�ߵ�*/
	{
		PF_OneDataReversed(V_ucbuf, V_ucbuf, (V_ucDataLen - C_MacLen));
		PF_OneDataReversed(&V_ucbuf[(V_ucDataLen - C_MacLen)], &V_ucbuf[(V_ucDataLen - C_MacLen)], C_MacLen);
	}
	/*����������Mac��֤��д��ESAM*/
	V_ucReturnData = WriteBinFileMac(C_ESAM, V_ucbuf, V_ucFile_No, V_ucFile_Offset, V_ucDataLen);
	if(V_ucReturnData != C_OK)
	{
		if(V_ucReturnData == C_IC_MAC_ERR)
		{
			return(C_SERR_ESAM_VF);
		}
		else
		{
			return(C_SERR_OtherErr);
		}
	}

	/*�����Ҫд�����ļ�����д�����ļ�*/
	if(V_ucOffsetInOP != C_Invalid_Offset)
	{
		V_ucReturnData = WriteBinFile(C_ESAM, V_ucbuf, C_F_OpInfo, V_ucOffsetInOP, (V_ucDataLen - C_MacLen) );
		if(V_ucReturnData != C_OK)
		{
			return(C_SERR_OtherErr);
		}
	}

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_WritePara_CipherTextMAC(ulong32 V_ucDI,uchar8 *pV_ucData,uchar8 *pV_ucLength)
����������	2���������
���������	*pV_ucData:			�������(����+Mac)
			*pV_ucLength		�������ĳ���(����Mac)
			V_ulDI				���ݱ�ʶ
���������	*pV_ucData
			pV_ucLength:		���ܺ������/������
								��ȥ�����ܺ�����ݱ�ʶ��Mac����ʵ�����ݳ���
���ز�����	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
����λ�ã�
��    ע��	ע�⣬P_Data�����ٱ���100�ֽڵ����ݣ���������д
*******************************************************************************/
ushort16  InF_S_WritePara_CipherTextMAC(ulong32 V_ucDI,uchar8 *pV_ucData,uchar8 *pV_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;
	uchar8	V_ucFile_No;
	uchar8	V_ucDataLen;


	/*�ж����ݵ���ڲ����Ƿ���ȷ1������������2�����ݳ���С��5*/
	if((*pV_ucLength > (CLen_S_BufMaxLen - CLen_TB_ESAM_Lc ) ) || (*pV_ucLength < (C_MacLen + 1) ) )
	{
		return(C_SERR_OtherErr);
	}
	/*���ݵߵ�*/
	PF_OneDataReversed(pV_ucData, V_ucbuf, (*pV_ucLength - C_MacLen));
	PF_OneDataReversed(&pV_ucData[*pV_ucLength - C_MacLen], &V_ucbuf[*pV_ucLength - C_MacLen], C_MacLen);

	/*д���������ļ������н��ܺ�MAC��֤*/
	V_ucFile_No = 0x83;
	V_ucReturnData = WriteBinFileMac_1(C_ESAM, V_ucbuf, V_ucFile_No, *pV_ucLength);
	if(V_ucReturnData != C_OK)
	{
		if(V_ucReturnData == C_IC_MAC_ERR)
		{
			return(C_SERR_ESAM_VF);
		}
		else
		{
			return(C_SERR_OtherErr);
		}
	}
	V_ucDataLen = V_ucbuf[0] - CLen_DataDILEN;

#if 0
	PF_CopyDataBytes(&V_ucbuf[2],&V_ucbuf[0],*P_Length);
�������ݵ�������������:
0400040F(λ����Ϣ)/0401(2)0000��0401(2)0001-0401(2)0008ʱ��ʱ�α�
	switch(V_ucDI)
		{
			case		CMeter_Position:
				DataReversed(CMeter_Position, V_ucbuf, C_RITem_Len_MeterPosition);
				break;
			case		CFirst_TZone_Data:		/* 2��ʱ����ĵߵ���*/
			case		CSec_TZone_Data:		/*����14��ʱ������еߵ�������14��Ҳ����*/
				DataReversed(CDI_TZone_Data, V_ucbuf,C_RITem_Len_TZone_Data);
				break;
			case		CFirst_TZone_1PT_Data:		/* 16��ʱ�α�ĵߵ���*/
			case		CFirst_TZone_2PT_Data:		/* ����14����ʱ�α�ߵ����������������14����*/
			case		CFirst_TZone_3PT_Data:
			case		CFirst_TZone_4PT_Data:
			case		CFirst_TZone_5PT_Data:
			case		CFirst_TZone_6PT_Data:
			case		CFirst_TZone_7PT_Data:
			case		CFirst_TZone_8PT_Data:
			case		CSec_TZone_1PT_Data:
			case		CSec_TZone_2PT_Data:
			case		CSec_TZone_3PT_Data:
			case		CSec_TZone_4PT_Data:
			case		CSec_TZone_5PT_Data:
			case		CSec_TZone_6PT_Data:
			case		CSec_TZone_7PT_Data:
			case		CSec_TZone_8PT_Data:
				DataReversed(CDI_TZone_PT_Data, V_ucbuf, C_RITem_Len_TZone_PT_Data);
				break;
			default:
				if((V_ucDI&0xFFFF0000) == 0x04040000)	/*ѭ�ԡ�������ʾ����*/
				{
					PF_OneDataReversed(V_ucbuf, V_ucbuf, DataLen-1);	/*��ʽDI3-DI0+��ʾ����*/
				}
				else
				{
					PF_OneDataReversed(&V_ucbuf[CLen_DataLEN], &V_ucbuf[CLen_DataLEN], DataLen);
				}
				break;
		}
#endif

	PF_CopyDataBytes(&V_ucbuf[CLen_DataLEN], pV_ucData, V_ucDataLen);
	*pV_ucLength = V_ucDataLen;

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_MeterClear( uchar8 *pV_ucData, uchar8 *pV_ucLength)
����������	�������
���������	*pV_ucData:				�������(����+Mac)
			*pV_ucLength			�������ĳ���(����Mac)
���������	*pV_ucData
			pV_ucLength:	���ܺ������/������
								R1-R8
���ز�����	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
����λ�ã�
��    ע��	���ܺ�Ϊ8�ֽڡ�R1-R8
*******************************************************************************/
ushort16  InF_S_MeterClear( uchar8 *pV_ucData, uchar8 *pV_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;

	/*�����ȵ��ж�*/
	if(*pV_ucLength > CLen_S_BufMaxLen)
	{
		return(C_SERR_OtherErr);
	}

	/*���ݵߵ�.ע�����������Mac������ͳһ�ߵ�*/
	PF_OneDataReversed(pV_ucData, V_ucbuf, *pV_ucLength);

	/*���ܣ�����Mac.  Ȼ��������ܺ������	*/
	V_ucReturnData = WriteBinFileMac_1(C_ESAM, V_ucbuf, C_F_MeterClear_Dou645, *pV_ucLength);
	if(V_ucReturnData != C_OK)
	{
		if(V_ucReturnData == C_IC_MAC_ERR)
		{
			return(C_SERR_ESAM_VF);
		}
		else
		{
			return(C_SERR_OtherErr);
		}
	}


	/*���ݵߵ�����������*/
	*pV_ucData = V_ucbuf[0];			/*R1*/
	pV_ucData[1] = V_ucbuf[1];			/*R2*/
	PF_OneDataReversed(&V_ucbuf[CF_O_CMDEndTime], &pV_ucData[CF_O_CMDEndTime], CL_CMDEndTime);
	*pV_ucLength = 2 + CL_CMDEndTime;

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�	InF_S_DemandClear( uchar8 *pV_ucData,uchar8 *pV_ucLength)
����������	�������
���������	*pV_ucData:			�������(����+Mac)
			*pV_ucLength		�������ĳ���(����Mac)
���������	*pV_ucData
			pV_ucLength:		���ܺ������/������
								R1-R8
���ز�����	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
����λ�ã�
��    ע��	���ܺ�Ϊ8�ֽڡ�R1-R8
*******************************************************************************/
ushort16  InF_S_DemandClear( uchar8 *pV_ucData, uchar8 *pV_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;

	/*�����ȵ��ж�*/
	if(*pV_ucLength > CLen_S_BufMaxLen)
	{
		return(C_SERR_OtherErr);
	}

	/*���ݵߵ�.ע�����������Mac������ͳһ�ߵ�*/
	PF_OneDataReversed(pV_ucData, V_ucbuf, *pV_ucLength);

	/*���ܣ�����Mac.  Ȼ��������ܺ������*/
	V_ucReturnData = WriteBinFileMac_1(C_ESAM, V_ucbuf, C_F_D_E_Clear_Dou645, *pV_ucLength);
	if(V_ucReturnData != C_OK)
	{
		if(V_ucReturnData == C_IC_MAC_ERR)
		{
			return(C_SERR_ESAM_VF);
		}
		else
		{
			return(C_SERR_OtherErr);
		}
	}


	/*���ݵߵ�����������*/
	*pV_ucData = V_ucbuf[0];			/*R1*/
	pV_ucData[1] = V_ucbuf[1];			/*R2*/
	PF_OneDataReversed(&V_ucbuf[CF_O_CMDEndTime], &pV_ucData[CF_O_CMDEndTime], CL_CMDEndTime);
	*pV_ucLength = 2 + CL_CMDEndTime;

	return(C_OK);

}


/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_EventClear( uchar8 *pV_ucData,uchar8 *pV_ucLength)
����������	�������
���������	*pV_ucData:				�������(����+Mac)
			*pV_ucLength			�������ĳ���(����Mac)
���������	*pV_ucData
			pV_ucLength:	���ܺ������/������  R1-R12
���ز�����	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
����λ�ã�
��    ע��	���ܺ�Ϊ8�ֽڡ�R1-R12
*******************************************************************************/
ushort16  InF_S_EventClear( uchar8 *pV_ucData,uchar8 *pV_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;

	/*�����ȵ��ж�*/
	if(*pV_ucLength > CLen_S_BufMaxLen)
	{
		return(C_SERR_OtherErr);
	}

	/*���ݵߵ�.ע�����������Mac������ͳһ�ߵ�*/
	PF_OneDataReversed(pV_ucData, V_ucbuf, *pV_ucLength);

	/*���ܣ�����Mac.  Ȼ��������ܺ������	*/
	V_ucReturnData = WriteBinFileMac_1(C_ESAM, V_ucbuf, C_F_D_E_Clear_Dou645, *pV_ucLength);
	if(V_ucReturnData != C_OK)
	{
		if(V_ucReturnData == C_IC_MAC_ERR)
		{
			return(C_SERR_ESAM_VF);
		}
		else
		{
			return(C_SERR_OtherErr);
		}
	}


	/*���ݵߵ�����������.*/
	*pV_ucData = V_ucbuf[0];			/*R1*/
	pV_ucData[1] = V_ucbuf[1];			/*R2*/
	PF_OneDataReversed(&V_ucbuf[CF_O_CMDEndTime], &pV_ucData[CF_O_CMDEndTime], CL_CMDEndTime);
	PF_OneDataReversed(&V_ucbuf[CF_O_EventClearDI], &pV_ucData[CF_O_EventClearDI], CL_DI);
	*pV_ucLength = 2 + CL_CMDEndTime + CL_DI;

	return(C_OK);

}


/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_ControlCommand( uchar8 *pV_ucData,uchar8 *pV_ucLength)
����������	�����������
���������	*pV_ucData:				�������(����+Mac)
			*pV_ucLength			�������ĳ���(����Mac)
���������	*pV_ucData
			pV_ucLength:			���ܺ������/������			  R1-R12
���ز�����	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
����λ�ã�
��    ע��	���ܺ�Ϊ8�ֽڡ�R1-R12
*******************************************************************************/
ushort16  InF_S_ControlCommand( uchar8 *pV_ucData, uchar8 *pV_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;

	/*�����ȵ��ж�*/
	if(*pV_ucLength > CLen_S_BufMaxLen)
	{
		return(C_SERR_OtherErr);
	}

	/*���ݵߵ�.ע�����������Mac������ͳһ�ߵ�*/
	PF_OneDataReversed(pV_ucData,V_ucbuf, *pV_ucLength);

	/*���ܣ�����Mac.  Ȼ��������ܺ������	*/
	V_ucReturnData = WriteBinFileMac_1(C_ESAM, V_ucbuf, C_F_RemoteCtr_Dou645, *pV_ucLength);
	if(V_ucReturnData != C_OK)
	{
		if(V_ucReturnData == C_IC_MAC_ERR)
		{
			return(C_SERR_ESAM_VF);
		}
		else
		{
			return(C_SERR_OtherErr);
		}
	}


	/*���ݵߵ�����������*/
	*pV_ucData = V_ucbuf[0];			/*R1*/
	pV_ucData[1] = V_ucbuf[1];			/*R2*/
	PF_OneDataReversed(&V_ucbuf[CF_O_CMDEndTime], &pV_ucData[CF_O_CMDEndTime], CL_CMDEndTime);
	*pV_ucLength = 2 + CL_CMDEndTime;

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	SelectFile(uchar8	V_ucFileNo)
����������	ѡ���ļ�
���������	V_ucFileNo:				�ļ�
���������	��
���ز�����	C_OK/C_Error
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SelectFile(uchar8	V_ucFileNo)
{
	uchar8		V_ucbuf[10];
	uchar8		V_ucDataLen;
	ushort16	V_usReturnData16;

	PF_CopyDataBytes((uchar8 *)TB_SelectFile, V_ucbuf, CLen_TB_ESAM_Lc);
	V_ucbuf[5] = 0;
	V_ucbuf[6] = V_ucFileNo;
	V_ucDataLen = 10;

	V_usReturnData16 = INF_SendData_7816_Esam(V_ucbuf, (CLen_TB_ESAM_Lc + 2), V_ucbuf, &V_ucDataLen);

	if( (V_usReturnData16 == C_Security_CommandOk) || ( (V_usReturnData16 & C_Resp_61XXType) == C_Security_ProcessOk) )
	{
		return(C_OK);
	}
	else
	{
		return(C_Error);
	}
}


/*******************************************************************************
����ԭ�ͣ�	ushort16	InF_S_WriteESAMPara_PlainTextMAC(uchar8 *pV_ucData,uchar8 V_ucLength)
����������	���Ĵ�MacдESAM
���������	*pV_ucData:				�������
			V_ucLength				�������ĳ���(2(FN)+2(Offset)+L(D)+4(Mac))
���������	��
���ز�����	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
����λ�ã�
��    ע��
*******************************************************************************/
ushort16	InF_S_WriteESAMPara_PlainTextMAC(uchar8 *pV_ucData, uchar8 V_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;
	uchar8	V_ucFile_Ld;
	uchar8	V_ucFile_Offset,V_ucFile_OffsetH;
	uchar8	V_ucFile_No;

	/*�ļ���*/
	if( (pV_ucData[C_WESAM_O_FileNo] == 0x18) || (pV_ucData[C_WESAM_O_FileNo] == 0x1A)
		|| (pV_ucData[C_WESAM_O_FileNo] == 0x1B) || (pV_ucData[C_WESAM_O_FileNo] == 0x1C) )
	{
		V_ucFile_No = pV_ucData[C_WESAM_O_FileNo];
	}
	else
	{
		return(C_SERR_OtherErr);
	}

	V_ucFile_Offset = pV_ucData[C_WESAM_O_Offset] ;
	V_ucFile_OffsetH = pV_ucData[C_WESAM_O_Offset + 1];
	/*�ļ�����*/
	if(V_ucLength <= (CL_FileNO + CL_Offset + C_MacLen))
	{
		return(C_SERR_OtherErr);
	}
	V_ucFile_Ld = V_ucLength - CL_FileNO - CL_Offset ;		/*File_Ld��Mac ����*/

	/*���ݵߵ� */
	PF_OneDataReversed(&pV_ucData[C_WESAM_O_Data], V_ucbuf, (V_ucFile_Ld - C_MacLen) );
	PF_OneDataReversed(&pV_ucData[C_WESAM_O_Data + V_ucFile_Ld - C_MacLen], &V_ucbuf[V_ucFile_Ld - C_MacLen], C_MacLen);
	/*ѡ���ļ�*/
	V_ucReturnData = SelectFile(V_ucFile_No);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}

	/*д�ļ�*/
	V_ucReturnData = WriteBinFileMac_2(C_ESAM, V_ucbuf, V_ucFile_Offset, V_ucFile_OffsetH, V_ucFile_Ld);
	if(V_ucReturnData != C_OK)
	{
		if(V_ucReturnData == C_IC_MAC_ERR)
		{
			return(C_SERR_ESAM_VF);
		}
		else
		{
			return(C_SERR_OtherErr);
		}
	}

	return(C_OK);

}


/*******************************************************************************
����ԭ�ͣ�	ushort16  InF_S_WriteESAMPara_CipherTextMAC (uchar8 *pV_ucData, uchar8 V_ucLength)
����������	���Ĵ�MacдESAM
���������	*pV_ucData:				�������
			V_ucLength				�������ĳ���(2(FN)+2(Offset)+L(D)+4(Mac))
���������	��
���ز�����	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
����λ�ã�
��    ע��
*******************************************************************************/
ushort16  InF_S_WriteESAMPara_CipherTextMAC (uchar8 *pV_ucData, uchar8 V_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;
	uchar8	V_ucFile_Ld;
	uchar8	V_ucFile_Offset,V_ucFile_OffsetH;
	uchar8	V_ucFile_No;

	/*�ļ���*/
	if( (pV_ucData[C_WESAM_O_FileNo] == 0x15) || (pV_ucData[C_WESAM_O_FileNo] == 0x0B) )
	{
		V_ucFile_No = pV_ucData[C_WESAM_O_FileNo];
	}
	else
	{
		return(C_SERR_OtherErr);
	}


	V_ucFile_Offset = pV_ucData[C_WESAM_O_Offset] ;
	V_ucFile_OffsetH = pV_ucData[C_WESAM_O_Offset + 1];

	/*�ļ�����*/
	if(V_ucLength <= (CL_FileNO + CL_Offset + C_MacLen))
	{
		return(C_SERR_OtherErr);
	}
	V_ucFile_Ld = V_ucLength - CL_FileNO - CL_Offset ;		/*File_Ld��Mac ����*/

	/*���ݵߵ� */
	PF_OneDataReversed(&pV_ucData[C_WESAM_O_Data], V_ucbuf, (V_ucFile_Ld - C_MacLen));
	PF_OneDataReversed(&pV_ucData[C_WESAM_O_Data + V_ucFile_Ld - C_MacLen],&V_ucbuf[V_ucFile_Ld - C_MacLen], C_MacLen);
	/*ѡ���ļ�*/
	V_ucReturnData = SelectFile(V_ucFile_No);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}

	/*д�ļ�*/
	V_ucReturnData = WriteBinFileMac_2(C_ESAM, V_ucbuf, V_ucFile_Offset, V_ucFile_OffsetH, V_ucFile_Ld);
	if(V_ucReturnData != C_OK)
	{
		if(V_ucReturnData == C_IC_MAC_ERR)
		{
			return(C_SERR_ESAM_VF);
		}
		else
		{
			return(C_SERR_OtherErr);
		}
	}

	return(C_OK);

}



/*******************************************************************************
����ԭ�ͣ�uchar8	InF_Get_Key_Tol_Num(void)
������������ȡ���ݲ���Կ������
�����������
�����������
���ز�����
����λ�ã�
��    ע�����������ȡ���ɹ���Ĭ��Ϊ20��
*******************************************************************************/
uchar8	InF_Get_Key_Tol_Num(void)
{
	uchar8		V_ucReturnData;
	uchar8		V_ucKey_Tol_Num;
	ushort16	V_usDataLen;
	ushort16	V_usDataEnCode;

	V_usDataLen = CLKey_Tol_Num;
	V_ucReturnData = InF_Read_Data(CKey_Tol_Num, &V_ucKey_Tol_Num, &V_usDataLen, &V_usDataEnCode);
	if( (V_ucReturnData != C_OK) || (V_ucKey_Tol_Num == 0) || (V_ucKey_Tol_Num > C_Max_KeyNum) )
	{
		V_ucKey_Tol_Num = C_Default_KeyNum;
	}
	return(V_ucKey_Tol_Num);
}


/*******************************************************************************
����ԭ�ͣ�void  InF_S_GetMeterNum_ReworkDL(void)
������������ȡESAM�еı�ţ�������EE�б��
�����������
�����������
���ز�������
����λ�ã�
��    ע���ú�����ESAM��λ��Ϣ�е���
*******************************************************************************/
void  InF_S_GetMeterNum_ReworkDL(void)
{
	uchar8 		V_ucESAMMeterNum[15], V_ucDataLen;
	uchar8 		V_ucDLMeterNum[10];
	ushort16	V_usDataEnCode, V_usDataLen;

	if(InF_SC_RDBinFileNoMac(C_ESAM, C_F_MeterNO, 0, 13, V_ucESAMMeterNum) == C_OK)
	{
		PF_OneDataReversed(V_ucESAMMeterNum + 5, V_ucESAMMeterNum, CLMeter_Num);
		V_usDataLen = CLMeter_Num;
		InF_Read_Data(CMeter_Num, V_ucDLMeterNum, &V_usDataLen, &V_usDataEnCode);
		if(PF_Campare_Data(V_ucESAMMeterNum, V_ucDLMeterNum, CLMeter_Num) != C_Equal)
		{
			InF_Write_Data(C_Msg_Communication, CMeter_Num, V_ucESAMMeterNum, CLMeter_Num, C_W_SafeFlag);
		}
	}

	/*�ͻ���Ų�һ�£���esam���µ�EE*/
	V_ucDataLen = CLCustomer_Num;
	if(ReadRecordFile(V_ucESAMMeterNum, &V_ucDataLen, C_Custormer_Num) == C_OK)
	{
		V_usDataLen = CLCustomer_Num;
		InF_Read_Data(CCustomer_Num, V_ucDLMeterNum, &V_usDataLen, &V_usDataEnCode);
		if(PF_Campare_Data(V_ucESAMMeterNum, V_ucDLMeterNum, CLCustomer_Num) != C_Equal)
		{
			InF_Write_Data(C_Msg_Communication, CCustomer_Num, V_ucESAMMeterNum, CLCustomer_Num, C_W_SafeFlag);
		}
	}
}

/*******************************************************************************
����ԭ�ͣ�void  InF_S_GetKeyStatus_ReworkKeyStatus(void)
������������esam����Կ״̬������ʾ����ʾ����
�����������
�����������
���ز�������
����λ�ã�
��    ע���ú�����ESAM��λ��Ϣ�е���
*******************************************************************************/
void  InF_S_GetKeyStatus_ReworkKeyStatus(void)
{
	if(InF_JudgeKeyStatus() == C_StateOfOfficialKey)	/*ȫ��ʽ��Կ����C_PublicKeySign��*/
	{
		Comm_SendMsgToDisp(C_PublicKeySign, C_NotDisplay, C_Duration_Alway);
	}
	else	/*��C_PublicKeySign��*/
	{
		Comm_SendMsgToDisp(C_PublicKeySign, C_AlwaysDisplay, C_Duration_Alway);
	}
}


/*******************************************************************************
����ԭ�ͣ�	ushort16	InF_S_InitMoney(uchar8 V_ucSrcMsg,uchar8 *pV_ucData)
����������	Զ�̳�ʼ��Ǯ����ȫģ��ӿں���
���������	*pV_ucData	:Զ�̳�ʼ��Ǯ���ļ�������
						:�̶�16�ֽڣ���ʽ4�ֽ�Ԥ�ý��+Mac1
						:+4�ֽڹ������+Mac2
			V_ucSrcMsg	:ȡֵC_Msg_Communication��C_Msg_Card
						:ͨ�Ŵ��ݽ�������С��ģʽ���忨�������Ǵ��ģʽ��
���������	��
���ز�����	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
����λ�ã�
��    ע��	���	1)Mac��֤
					2)�жϹ������--���ǵ�����ͨ������ִ�С�
					3)ˢ��ESAMǮ���ļ���ʣ����͹������
*******************************************************************************/
ushort16	InF_S_InitMoney(uchar8 V_ucSrcMsg,uchar8 *pV_ucData)
{
	ushort16	V_usReturnData16;
	uchar8		V_ucbuf[C_Init_MoneyDataLen];

	/*�����ݵߵ�*/
	PF_CopyDataBytes(pV_ucData,V_ucbuf,C_Init_MoneyDataLen);
	if(V_ucSrcMsg == C_Msg_Communication)	/*ͨ�Ŵ��ݽ�������С��ģʽ���忨�������Ǵ��ģʽ��*/
	{
		DataReversed(CDI_Init_Money, V_ucbuf, C_RITem_Len_InitMoney);
	}

	/*��Mac д��¼�ļ�-ʣ����*/
	V_usReturnData16 = WriteRecordFile(&V_ucbuf[C_InitM_O_ChgBlHC], (CLChargeBal_Hex_Cent + C_MacLen) );
	if(V_usReturnData16 != C_OK)
	{
		return(V_usReturnData16);
	}

#if 0
	/*����Ԥ�ƿ�Ǯ���ļ�û�й������*/
	/*��Mac д��¼�ļ�-�������*/
	V_ReturnData16 = WriteRecordFile(&V_ucbuf[C_InitM_O_PC_Num],(CL_PurchasingE_Num+C_MacLen),C_PurchasingE_Num_Mac);
	if(V_ReturnData16 != C_OK)
	{
		return(V_ReturnData16);
	}
#endif

	return(C_OK);

}

#if (_DEBUG_LX)
/*******************************************************************************
����ԭ�ͣ�InF_S_GetPPNum(ulong32	*pV_ulPPNum)
������������ȡESAM�й������(Power Purchase Num)
���������pV_ulPPNum				:���������ַ
���������*pV_ulPPNum			:���������32λHex
���ز�����C_OK/C_SERR_OtherErr
����λ�ã�
��    ע������������������㣬����C_SERR_OtherErr
*******************************************************************************/
ushort16	InF_S_GetPPNum(ulong32	*pV_ulPPNum)
{
	uchar8	V_ucDataLen;
	uchar8	V_ucReturnData;
	uchar8	V_ucbuf[CLen_S_BufMaxLen];

	V_ucDataLen = CLen_S_BufMaxLen;
	V_ucReturnData = ReadRecordFile(V_ucbuf, &V_ucDataLen, C_PurchasingE_Num_Mac);
	if(V_ucReturnData != C_OK)
	{
		*pV_ulPPNum = 0;
		return(C_SERR_OtherErr);
	}

	/*����ת��С��ģʽ,����¼�ļ��ѵߵ���*/
	PF_Buffer4ToUlong32(V_ucbuf, pV_ulPPNum, CL_PurchasingE_Num);

	return(C_OK);
}
#endif

/*******************************************************************************
����ԭ�ͣ�	ushort16	InF_S_Purchase(uchar8	*pV_ucData)
����������	��ESAMǮ���ļ����г�ֵMac��֤����ֵ����
���������	*pV_ucData		:��ֵ���ġ���ʽ:������4+�������4+Mac1
							�������ݶ�����645��ʽ
���������	��
���ز�����	C_OK/C_SERR_ESAM_VF
����λ�ã�
��    ע��	pData�������ǲ���仯��
*******************************************************************************/
ushort16	InF_S_Purchase(uchar8	*pV_ucData)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	ushort16	V_usDataLen = CLen_S_BufMaxLen;

	/*��ֵ����֡Ϊ 80 42 00 00 00 0C +������+�������+Mac1*/
	PF_CopyDataBytes((uchar8 *)TB_Increase_698, V_ucbuf, CLen_TB_ESAM_Lc_698_Esam);
	/*copy+�ߵ�*/
	PF_OneDataReversed(&pV_ucData[C_ROAACB_O_ChgBlHC], &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam+C_ROAACB_O_ChgBlHC], CLChargeBal_Hex_Cent);
	PF_OneDataReversed(&pV_ucData[C_ROAACB_O_PC_Num], &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam+C_ROAACB_O_PC_Num], CL_PurchasingE_Num);
	PF_OneDataReversed(&pV_ucData[C_ROAACB_O_Mac1], &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam+C_ROAACB_O_Mac1], C_MacLen);

	PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);

	GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucbuf, (CLen_TB_ESAM_Lc_698_Esam + CLChargeBal_Hex_Cent + CL_PurchasingE_Num + C_MacLen),
					V_ucbuf, &V_usDataLen);
	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_SERR_ESAM_VF);
	}
	else
	{
		return(C_OK);
	}

}


/*******************************************************************************
����ԭ�ͣ�	uchar8	InF_S_ColdRestCard(uchar8	*pV_ucCardNo)
����������	�临λ��
���������	pV_ucCardNo				:�����к����ָ��
��������� 	*pV_ucCardNo			:�����кţ��̶�8�ֽڣ�����С��(645)ģʽ
���ز�����	C_OK/C_Error
����λ�ã�
��    ע��	1����λ������ɹ�����������λ3��
			2����λ���ɹ���*pCardNo�����޸�
*******************************************************************************/
uchar8	InF_S_ColdRestCard(uchar8	*pV_ucCardNo)
{
	uchar8	i;
	uchar8	V_ucCardBuf[10];

	for(i = 0; i < 2; i++)
	{
		if(INF_ColdReset_7816_Card(V_ucCardBuf) == C_OK)
		{
			break;
		}
	}
	if(i < 2)
	{
		PF_OneDataReversed(V_ucCardBuf, pV_ucCardNo, CL_UserCardNo);
		return(C_OK);
	}
	else
	{
		return(C_Error);
	}
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	InF_S_SelectFile(uchar8 V_ucCH, ushort16 V_usFileName)
����������	ѡ���ļ�
���������	V_ucCH			:ͨ����ȡֵC_ESAM/C_Card
			V_usFileName	:�ļ����ƣ�����C_F_MF				0x3F00
���������	��
���ز�����	C_OK/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR
����λ�ã�
��    ע��	1�����ӿں�������ESAM��card
			2�����ڷ���ֵΪC_Errorʱ�����pErr7816CMDHeader/pSW1_2
					C_OKʱ����д
			3�������������������С��ģʽ
*******************************************************************************/
uchar8	InF_S_SelectFile(uchar8 V_ucCH, ushort16 V_usFileName)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucDataLen;
	uchar8	V_ucReturnData;

	PF_CopyDataBytes( (uchar8 * )TB_SelectFile, V_ucbuf, CLen_TB_ESAM_Lc);

	PF_Ushort16ToBuffer2(&V_ucbuf[CLen_TB_ESAM_Lc], &V_usFileName);
	PF_OneDataReversed(&V_ucbuf[CLen_TB_ESAM_Lc], &V_ucbuf[CLen_TB_ESAM_Lc], 2);

	V_ucDataLen = CLen_S_BufMaxLen;

	PF_OneDataReversed(V_ucbuf,GV_7816CMD.Header, CL_7816Header);		/*����֮ǰ��������ͷ*/

	if(V_ucCH == C_ESAM)
	{
		GV_7816CMD.SW1_2 =  INF_SendData_7816_Esam(V_ucbuf, (CLen_TB_ESAM_Lc + 2), V_ucbuf, &V_ucDataLen);
		V_ucReturnData = C_IC_ESAM_RDWR_ERR;
	}
	else
	{
		GV_7816CMD.SW1_2 =  INF_SendData_7816_Card(V_ucbuf, (CLen_TB_ESAM_Lc+2), V_ucbuf, &V_ucDataLen);
		V_ucReturnData = C_IC_NOIN_ERR;
	}
	if( (GV_7816CMD.SW1_2 !=  C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(V_ucReturnData);
	}
	else
	{
		return(C_OK);
	}
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	InF_SC_RDBinFileNoMac(uchar8 V_ucCH,uchar8 V_ucFileNo,uchar8 V_ucParmOffset,ushort16 V_usParmLen,uchar8 *pV_ucData)
����������	��ȡ�����ļ�ͷ(68 + CMD+2�ֽڳ���)
���������	V_ucFileNo:				:��ȡ�Ķ������ļ��̱�ʶ�롣���궨��
			V_ucParmOffset			:���Ĳ���ƫ�ơ����궨��
			V_usParmLen				:��Ҫ���Ĳ������ȡ�
			pV_ucData				:���������ݵĻ������׵�ַ
			V_ucCH					:ͨ����ȡֵC_ESAM/C_Card
���������	*pV_ucData				:�������ݡ�����ΪParmLen
���ز�����	C_OK/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR
����λ�ã�
��    ע��	ע������2�����ļ��в������Ǵ��ģʽ�ġ�
			��Ϊ������ʲô���������
			ͬʱ���ٵĻ���������һ������ParmLen
*******************************************************************************/
uchar8	InF_SC_RDBinFileNoMac(uchar8 V_ucCH,uchar8 V_ucFileNo,uchar8 V_ucParmOffset,ushort16 V_usParmLen,uchar8 *pV_ucData)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucDataLen;
	ushort16	V_usDataLen;
	uchar8		V_ucReturnData;

	if(V_ucCH == C_Card)
	{
		/*����Mac���������ļ�������ͷ*/
		V_ucbuf[0] = 0x00;					/*����Mac���������ļ�����Ϊ00B0*/
		V_ucbuf[1] = 0xB0;
		V_ucbuf[2] = 0x80 | V_ucFileNo;			/*FileNoΪ�ļ��̱�ʶ�룬���÷�ʽ1, 100x xxxx xxxxxΪ�̱�ʶ��*/
		V_ucbuf[3] = V_ucParmOffset;			/*P2*/
		V_ucbuf[4] = V_usParmLen;				/*Le*/


		V_ucDataLen = CLen_S_BufMaxLen;
		PF_OneDataReversed(V_ucbuf,GV_7816CMD.Header, CL_7816Header);		/*����֮ǰ��������ͷ*/


		GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucbuf, CLen_TB_ESAM_Le, V_ucbuf, &V_ucDataLen);
		V_ucReturnData = C_IC_NOIN_ERR;
	}
	else
	{
		/*����Mac���������ļ�������ͷ*/
		V_ucbuf[0] = 0x80;					/*����Mac���������ļ�����Ϊ00B0*/
		V_ucbuf[1] = 0x2C;
		V_ucbuf[2] = 0x00;					/*FileNoΪ�ļ��̱�ʶ��*/
		V_ucbuf[3] = V_ucFileNo;				/*FileNoΪ�ļ��̱�ʶ��*/
		V_ucbuf[4] = 0x00;					/*�ļ�ƫ��*/
		V_ucbuf[5] = 0x05;					/*�������ݳ���*/
		V_ucbuf[6] = 0x00;
		V_ucbuf[7] = 0x00;					/*�ļ�ƫ��*/
		V_ucbuf[8] = V_ucParmOffset;			/*�ļ�ƫ��*/
		V_ucbuf[9] = (uchar8)(V_usParmLen>>8);	/*���ļ�����*/
		V_ucbuf[10] = (uchar8)V_usParmLen;		/*���ļ�����*/

		V_usDataLen = CLen_S_BufMaxLen;
		PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*����֮ǰ��������ͷ*/

		GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucbuf, 11, V_ucbuf, &V_usDataLen);
		V_ucReturnData = C_IC_ESAM_RDWR_ERR;
	}

	/*�ж�V_ReturnData16,����*/
	if( (GV_7816CMD.SW1_2 == C_Security_CommandOk) || ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) == C_Security_ProcessOk) )/*��ȷ*/
	{
		PF_CopyDataBytes_698(V_ucbuf, pV_ucData, V_usParmLen);
		return(C_OK);
	}
	else	/*����*/
	{
		return(V_ucReturnData);
	}
}

/*******************************************************************************
����ԭ�ͣ�void		InF_S_Dispatch_5s(void)
�����������ṩ���ȶ�ʱ5s���õĺ���
�����������
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void		InF_S_Dispatch_5s(void)
{
	SV_SafeByte = 0;

	if(SV_UpdateMInEsamTimer != 0)
	{
		SV_UpdateMInEsamTimer--;
	}
}


/*******************************************************************************
����ԭ�ͣ�void		UpdataChargeBalInESAMWithSwitch(void)
����������ˢ��ESAM��ʣ�����15min����ʱ��
�����������
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void		UpdataChargeBalInESAMWithSwitch(void)
{
	uchar8		V_ucReturnData;
	uchar8		V_ucbuf[CLChargeBal_Hex_Cent];
	ushort16	V_usDataLen,V_usCodeData;

	/*���ʱ�䲻�����򲻽���ͬ������*/
	if(SV_UpdateMInEsamTimer != 0)
	{
		return;
	}

	/*�����ݲ�ʣ����	*/
	V_usDataLen = CLChargeBal_Hex_Cent;
	V_ucReturnData = InF_GetData_ObjectManage(CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, &V_usCodeData);
	if(V_ucReturnData != C_OK)
	{
		return;					/*���������ݲ�ʣ������˳�*/
	}

	/*ͬ�����ݲ��ESAM��ʣ���ע�⣬һ������£��Ƕ�ESAM�ۼ���
	��������ݲ�ʣ�����������˷Ѳ�����*/
	InF_S_UpdataChargeBalInESAM(V_ucbuf);

	SV_UpdateMInEsamTimer = C_SV_UpdateMInEsamTimer;		/*����������ʱ��15min*/
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	InF_SC_L_Auth(uchar8	*pV_ucIC_CardNo)
����������	���������֤(Ҳ���ڲ���֤����Ӧͨ�������֤λ�ⲿ��֤)
���������	pV_ucIC_CardNo			:��Ƭ���к�(С�ˣ��̶�8�ֽ�)
���������	��
���ز�����	C_OK/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR/C_IC_AUTH_ERR
����λ�ã�
��    ע��	�ο���ȫ�淶��¼A.1.1�����ܰ�ȫоƬ6.1.1
			�ڵ��ñ�����ǰ��ESAM�Ϳ�Ƭ��������λ����Ƭ���к��ѱ���
			�Ѿ���Ŀ¼���ļ�ѡ��
*******************************************************************************/
uchar8	InF_SC_L_Auth(uchar8	*pV_ucIC_CardNo)
{
	uchar8		V_ucSendBuf[CL_Send_InIC];
	uchar8		V_ucReponseBuf[CL_Response_InIC];
	ushort16	V_usDataLen;
	uchar8		V_ucRand8[9];
	uchar8		V_ucK1[9],V_ucDataLen;


	/*ȡESAM 8�ֽ������	*/
	PF_CopyDataBytes( (uchar8 * )TB_GetChallenge_698_Esam, V_ucSendBuf, CLen_TB_ESAM_Lc_698_Esam);
	V_ucSendBuf[3] = 0x08;
	V_usDataLen = CL_Response_InIC;
	PF_OneDataReversed(V_ucSendBuf, GV_7816CMD.Header, CL_7816Header);		/*����֮ǰ��������ͷ*/
	GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucSendBuf, CLen_TB_ESAM_Le_698_Esam, V_ucRand8, &V_usDataLen);
	if(GV_7816CMD.SW1_2 != C_Security_CommandOk)	/*����SW !=9000*/
	{
		return(C_IC_ESAM_RDWR_ERR);
	}
	/*ʹ�ÿ�Ƭ���кŶ�ESAM��Ƕ��Կ���з�ɢ������������Կ��*/
	PF_CopyDataBytes((uchar8 *)TB_AuthDistributedkey_L_698, V_ucSendBuf, CLen_TB_ESAM_Lc_698_Esam);
	PF_OneDataReversed(pV_ucIC_CardNo, &V_ucSendBuf[CLen_TB_ESAM_Lc_698_Esam], CL_CardNo);
	PF_CopyDataBytes(V_ucRand8,&V_ucSendBuf[CLen_TB_ESAM_Lc_698_Esam + CL_CardNo], 8);			/*���������1*/
	V_usDataLen = CL_Response_InIC;
	PF_OneDataReversed(V_ucSendBuf,GV_7816CMD.Header, CL_7816Header);		/*����֮ǰ��������ͷ*/
	GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucSendBuf, (CLen_TB_ESAM_Lc_698_Esam + CL_CardNo + 8), V_ucK1, &V_usDataLen);
	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType)!= C_Security_ProcessOk) )
	{
		return(C_IC_ESAM_RDWR_ERR);
	}

	/*��Ƭ���м��������(�ڲ���֤����)*/
	PF_CopyDataBytes((uchar8 *) TB_CardEncryptingRand1, V_ucSendBuf, CLen_TB_ESAM_Lc);
	PF_CopyDataBytes(V_ucRand8,&V_ucSendBuf[CLen_TB_ESAM_Lc], 8);
	V_ucDataLen = CL_Response_InIC;
	PF_OneDataReversed(V_ucSendBuf,GV_7816CMD.Header, CL_7816Header);		/*����֮ǰ��������ͷ*/
	GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucSendBuf, (CLen_TB_ESAM_Lc + 8), V_ucReponseBuf, &V_ucDataLen);
	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_IC_NOIN_ERR);
	}

	/*��ȡ��Ƭ�м��ܺ�������K2*/
	/*	InF_Delay_us(3000);*/
	PF_CopyDataBytes((uchar8 *)TB_GetResponse, &V_ucSendBuf[0], CLen_TB_ESAM_4);
	V_ucSendBuf[CLen_TB_ESAM_4] = 8;					/*Rand1���ܺ����ĳ���Ϊ8*/
	V_ucDataLen = CL_Response_InIC;
	PF_OneDataReversed(V_ucSendBuf,GV_7816CMD.Header,CL_7816Header);		/*����֮ǰ��������ͷ*/
	GV_7816CMD.SW1_2 = INF_SendData_7816_Card(&V_ucSendBuf[0],(CLen_TB_ESAM_4 + 1), V_ucReponseBuf, &V_ucDataLen);
	if( (GV_7816CMD.SW1_2 !=C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_IC_NOIN_ERR);
	}
	/*�ȶ������K1/K2����ȣ��ڲ���֤ͨ����������û��ͨ����*/
	if(PF_Campare_Data(V_ucK1,V_ucReponseBuf, 8) == C_Equal)
	{
		return(C_OK);
	}
	else
	{
		return(C_IC_AUTH_ERR);
	}
}


/*******************************************************************************
����ԭ�ͣ�uchar8	InF_SC_Judge_CardFile(uchar8	*pV_ucFile)
�����������жϿ�Ƭ���ļ���ʽ
���������pFile				:��Ƭ���ļ���ʼ�׵�ַ
�����������
���ز�����C_OK/C_Error
����λ�ã�
��    ע��File��ʽ	1)������ϴ��ģʽ
					2) ֡��ʽ:0x68  + CMD + 2�ֽ�Len + ����Data +CS +0x16
					3) Len:��ʾ����Data����
					4)CS ��CMD��ʼ����CSǰ������
*******************************************************************************/
uchar8	InF_SC_Judge_CardFile(uchar8	*pV_ucFile)
{
	ushort16	V_usLen16;
	uchar8		V_uccs = 0;
	uchar8		i;

	/*�ļ���ʼ�ֽ�Ϊ0x68*/
	if(pV_ucFile[0] != 0x68)
	{
		return(C_Error);
	}

	/*ȡ���ȣ�ע��Ϊ���ģʽ*/
	V_usLen16 = pV_ucFile[2];
	V_usLen16 <<= 8;
	V_usLen16 |= (ushort16)pV_ucFile[3];

	/*����CS������cs�ĳ��ȴ�CMD��ʼ����һ��68�������ڣ�����pFile[0]�зŵ���68,
	Ϊ�˷��㣬ѭ���е�i��pFile�е�ƫ���������������Ҫ����һ��68�ĳ���Ҳ��������
	ʵ�ʼ���cs��pFile[1]��ʼ����i�ĳ�ʼֵΪ1*/
	for(i = 1; i< (V_usLen16 + 4); i++)		/*�������ֿ�ʼ*/
	{
		V_uccs = V_uccs + pV_ucFile[i];
	}
	if(pV_ucFile[i] != V_uccs)
	{
		return(C_Error);
	}
	i++;

	/*16*/
	if(pV_ucFile[i] != 0x16)
	{
		return(C_Error);
	}
	else
	{
		return(C_OK);
	}
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	InF_SC_GenerateRandToCalMac(uchar8	V_ucCH,uchar8 V_ucLength)
����������	ʹ�ð�ȫģ��/ESAM����N�ֽ�����������ڲ忨������Mac����
���������	V_ucCH					:ͨ���ţ�ȡֵC_Card/C_ESAM
���������	��
���ز�����	C_OK/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR
����λ�ã�
��    ע��	��������Mac �����4�ֽ����������������ʶ
			1��	Զ��ͨ�ţ�����λ���·������֤����ʱ������֡�������1�ĸ�4�ֽ�(645С��ģʽ)��
			����ESAM����λ�����·���Mac�����ݽ�����֤��
			2��	����ͨ�ţ���ȡESAM�������������Mac��֤��
			3��	�û�����д��ȡESAM������������ڷ�д�ļ��������
			4��	����ͨ�ţ��϶���ȡ��Զ�������֤��ɡ��������Զ���ٴ�ͨ�ţ��������������֤��
*******************************************************************************/
uchar8	InF_SC_GenerateRandToCalMac(uchar8	V_ucCH, uchar8 V_ucLength)
{
	uchar8		V_ucSendBuf[CL_Send_InIC];
	uchar8		V_ucDataLen;
	ushort16	V_usDataLen;
	uchar8		V_ucReturnData,V_ucRand1_4[6];


	if(V_ucCH == C_ESAM)
	{
		PF_CopyDataBytes((uchar8 *)TB_GetChallenge_698_Esam, V_ucSendBuf, CLen_TB_ESAM_Lc_698_Esam);
		V_ucSendBuf[3] = V_ucLength;	/*Le*/
		V_usDataLen = V_ucLength;					/*SV_Rand1_4���鳤��*/
		PF_OneDataReversed(V_ucSendBuf,GV_7816CMD.Header, CL_7816Header);	/*����֮ǰ��������ͷ*/

		GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucSendBuf, CLen_TB_ESAM_Lc_698_Esam, V_ucRand1_4, &V_usDataLen);
		V_ucReturnData = C_IC_ESAM_RDWR_ERR;

		PF_CopyDataBytes(V_ucRand1_4, SV_Rand1_4, V_ucLength);	/*����Ҫ�ߵ�*/
	}
	else
	{
		PF_CopyDataBytes((uchar8 *)TB_GetChallenge, V_ucSendBuf, CLen_TB_ESAM_4);
		V_ucSendBuf[CLen_TB_ESAM_4] = V_ucLength;	/*Le*/
		V_ucDataLen = V_ucLength;					/*SV_Rand1_4���鳤��*/
		PF_OneDataReversed(V_ucSendBuf, GV_7816CMD.Header, CL_7816Header);	/*����֮ǰ��������ͷ*/

		GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucSendBuf, CLen_TB_ESAM_Le, SV_Rand1_4, &V_ucDataLen);
		V_ucReturnData = C_IC_NOIN_ERR;
	}

	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(V_ucReturnData);
	}
	else
	{
		return(C_OK);
	}
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	SC_ReadRunFileMac(uchar8 V_ucCH, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, uchar8 *pV_ucData,
			uchar8 V_ucNxtCLA, uchar8 V_ucNxtINS, uchar8 V_ucNxtP1, uchar8 V_ucNxtP2, uchar8 V_ucLC, uchar8	 *pV_ucIC_CardNo)
����������	��Mac ��ȡ�������ļ����ݡ�ע��ͺ���ReadBinFileMac����
���������	V_ucCH				:ͨ���š�ȡֵC_Card/C_ESAM
			V_ucFileNo			:��ȡ�Ķ������ļ��̱�ʶ�롣���궨��
			V_ucParmOffset		:���Ĳ���ƫ�ơ����궨��
			V_ucNxtCLA/V_ucNxtINS/V_ucNxtP1/V_ucNxtP2:
							:��һ��ָ��������ױ�
			V_ucLC				:����������Ч����+Mac����
			*pV_ucIC_CardNo		:���ţ��̶�8�ֽڣ�С��ģʽ��
���������	*pV_ucData			:���ز������䳤��Ϊ�������ݳ���+4�ֽ�Mac
���ز�����	C_OK/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR
����λ�ã�
��    ע��	һ��Ҫע��P_Data�������ĳ���Ҫ��д�����ﲻ����󳤶�����
			���������ע������
			��Mac���������ļ�����ϸ����ȫ�淶��ϸ���1.2.12	ReadBinary�����������ļ���00B0/04B0
			1�������ʽΪ04 B0 P1 P2 Lc(=09,11) + Rand4 + "��һ��ָ�� CLA INS P0 P1 Lc1" +����ɢ���ӣ�
			2��Rand4����ΪMac��������е�һ������
			3����ΪMac�����Ǵ�����ͷ�����ֽ�CLA��ʼ������Ҫ��"��һ��ָ��"
			4����Mac����ͬ����Ҫ��Կ�������㡣
				a������ESAM��Mac����Զ��ͨ�Ų��ã������Ϊ��ɢ���ӡ�
				b������ESAM��Mac�������ز忨�����У����ÿ�����Ϊ��ɢ���ӡ�
					���Զ�ESAM��Mac����Lc=0x11����8�ֽڷ�ɢ����
				c��	���ڿ�����Mac����ֱ�Ӳ��ÿ�����Ϊ��ɢ���ӣ����봫�ݸ���������Lc = 09
			5��	LC1��2�ֺ��壺
				a��ͨ����LC1=Ҫ�������ݳ���+Mac����
				b�������ݻس�ʱ��LC1=��������+Mac����+��ɢ���ӳ��ȡ����ú���ReadBinFileMac
			6���������Ͻ��ͣ����ڶ�ESAM����ʱ�ٴ���ɢ���ӡ���������
				Զ�̴�Mac���Ѻ���ReadBinFileMac����ɣ���������ɢ���Ӷ��ǿ��š�
			7���������Ͻ���LC1 = ��Ҫ��������+Mac����
*******************************************************************************/
uchar8	SC_ReadRunFileMac(uchar8 V_ucCH, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, uchar8 *pV_ucData,
			uchar8 V_ucNxtCLA, uchar8 V_ucNxtINS, uchar8 V_ucNxtP1, uchar8 V_ucNxtP2, uchar8 V_ucLC, uchar8	 *pV_ucIC_CardNo)
{
	uchar8		V_ucSendBuf[CL_Send_InIC];
	ushort16	V_usDataLen;
	uchar8		V_ucSendLen;
	uchar8		V_ucReturnData;

	/*֡��ʽ:04+B0+P1(0x80|V_ucFileNo)+P2(V_ucParmOffset)+09(0x11)+Rand4+��һ��ָ��5�ֽ�����ͷ+(����) */
	V_ucSendBuf[0] = 0x83;
	V_ucSendBuf[1] = 0x2c;
	V_ucSendBuf[2] = 0x00;
	V_ucSendBuf[3] = V_ucFileNo;

	/*����ͨ������LC�������ܳ���,�÷�ɢ���ӿ���*/

	V_ucSendBuf[4] = 0x00;
	V_ucSendBuf[5] = 0x16;	/*LC1 22�ֽ�*/
	V_ucSendBuf[6] = 0x48;

	PF_OneDataReversed(pV_ucIC_CardNo, &V_ucSendBuf[7], CL_CardNo);

	/*copy Rand4*/
	PF_CopyDataBytes(SV_Rand1_4, &V_ucSendBuf[7 + CL_CardNo], 4);

	V_ucSendBuf[19] = 0x00;			/*P3*/
	V_ucSendBuf[20] = V_ucParmOffset;	/*P3*/
	V_ucSendBuf[21] = 0x00;			/*LEN ��Ҫ��ȡ������*/
	V_ucSendBuf[22] = (V_ucLC - 4);		/*LEN*/

	/*ȡ��һ��ָ�������ͷ*/
	V_ucSendBuf[23] = V_ucNxtCLA;
	V_ucSendBuf[24] = V_ucNxtINS;
	V_ucSendBuf[25] = V_ucNxtP1;
	V_ucSendBuf[26] = V_ucNxtP2;
	V_ucSendBuf[27] = V_ucLC;

	V_ucSendLen = 28;

	V_usDataLen = CL_Response_InIC;
	/*��ȡ����*/
	PF_OneDataReversed(V_ucSendBuf, GV_7816CMD.Header, CL_7816Header);	/*����֮ǰ��������ͷ*/

	GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucSendBuf, V_ucSendLen, pV_ucData, &V_usDataLen);
	V_ucReturnData = C_IC_ESAM_RDWR_ERR;

	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk)
		&& ((GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(V_ucReturnData);
	}
	else
	{
		return(C_OK);
	}
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	SC_ReadBinFileMac(uchar8 V_ucCH, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, uchar8 *pV_ucData,
			uchar8 V_ucNxtCLA, uchar8 V_ucNxtINS, uchar8 V_ucNxtP1, uchar8 V_ucNxtP2, uchar8 V_ucLC1,uchar8	 *pV_ucIC_CardNo)
����������	��Mac ��ȡ�������ļ����ݡ�ע��ͺ���ReadBinFileMac����
���������	V_ucCH				:ͨ���š�ȡֵC_Card/C_ESAM
			V_ucFileNo			:��ȡ�Ķ������ļ��̱�ʶ�롣���궨��
			V_ucParmOffset		:���Ĳ���ƫ�ơ����궨��
			V_ucNxtCLA/V_ucNxtINS/V_ucNxtP1/V_ucNxtP2:
								:��һ��ָ��������ױ�
			V_ucLC1				:����������Ч����+Mac����
			*pV_ucIC_CardNo		:���ţ��̶�8�ֽڣ�С��ģʽ��
���������	*pV_ucData			:���ز������䳤��Ϊ�������ݳ���+4�ֽ�Mac��
						:��LC1
���ز�����	C_OK/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR
����λ�ã�
��	  ע��	һ��Ҫע��P_Data�������ĳ���Ҫ��д�����ﲻ����󳤶�����
			���������ע������
			��Mac���������ļ�����ϸ����ȫ�淶��ϸ���1.2.12	ReadBinary�����������ļ���00B0/04B0
			1�������ʽΪ04 B0 P1 P2 Lc(=09,11) + Rand4 + "��һ��ָ�� CLA INS P0 P1 Lc1" +����ɢ���ӣ�
			2��Rand4����ΪMac��������е�һ������
			3����ΪMac�����Ǵ�����ͷ�����ֽ�CLA��ʼ������Ҫ��"��һ��ָ��"
			4����Mac����ͬ����Ҫ��Կ�������㡣
				a������ESAM��Mac����Զ��ͨ�Ų��ã������Ϊ��ɢ���ӡ�
				b������ESAM��Mac�������ز忨�����У����ÿ�����Ϊ��ɢ���ӡ�
					���Զ�ESAM��Mac����Lc=0x11����8�ֽڷ�ɢ����
				c��	���ڿ�����Mac����ֱ�Ӳ��ÿ�����Ϊ��ɢ���ӣ����봫�ݸ���������Lc = 09
			5��	LC1��2�ֺ��壺
				a��ͨ����LC1=Ҫ�������ݳ���+Mac����
				b�������ݻس�ʱ��LC1=��������+Mac����+��ɢ���ӳ��ȡ����ú���ReadBinFileMac
			6���������Ͻ��ͣ����ڶ�ESAM����ʱ�ٴ���ɢ���ӡ���������
				Զ�̴�Mac���Ѻ���ReadBinFileMac����ɣ���������ɢ���Ӷ��ǿ��š�
			7���������Ͻ���LC1 = ��Ҫ��������+Mac����
*******************************************************************************/
uchar8	SC_ReadBinFileMac(uchar8 V_ucCH, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, uchar8 *pV_ucData,
			uchar8 V_ucNxtCLA, uchar8 V_ucNxtINS, uchar8 V_ucNxtP1, uchar8 V_ucNxtP2, uchar8 V_ucLC1,uchar8	 *pV_ucIC_CardNo)
{
	uchar8	V_ucSendBuf[CL_Send_InIC];
	uchar8	V_ucReponseBuf[CL_Response_InIC];
	uchar8	V_ucDataLen;
	uchar8	V_ucSendLen;
	uchar8	V_ucReturnData;

	/*֡��ʽ:04+B0+P1(0x80|V_ucFileNo)+P2(V_ucParmOffset)+09(0x11)+Rand4+��һ��ָ��5�ֽ�����ͷ+(����)*/
	V_ucSendBuf[0] = 0x04;
	V_ucSendBuf[1] = 0xB0;
	V_ucSendBuf[2] = 0x80 | V_ucFileNo;
	V_ucSendBuf[3] = V_ucParmOffset;

	/*����ͨ������LC�������ܳ���,�÷�ɢ���ӿ���*/
	if(V_ucCH == C_ESAM)
	{
		V_ucSendBuf[4] = 0x11;
		V_ucSendLen = 22;
		PF_OneDataReversed(pV_ucIC_CardNo, &V_ucSendBuf[CLen_TB_ESAM_Lc + 4 + CLen_TB_ESAM_Lc], CL_CardNo);
	}
	else if(V_ucCH == C_Card)
	{
		V_ucSendBuf[4] = 0x09;
		V_ucSendLen = 14;
	}
	else	/*�����ϲ����ܳ��ִ˴��󣬼���C_IC_NOIN_ERR����*/
	{
		return(C_IC_NOIN_ERR);
	}

	/*copy Rand4*/
	PF_CopyDataBytes(SV_Rand1_4, &V_ucSendBuf[5], 4);
	/*ȡ��һ��ָ�������ͷ*/
	V_ucSendBuf[9] = V_ucNxtCLA;
	V_ucSendBuf[10] = V_ucNxtINS;
	V_ucSendBuf[11] = V_ucNxtP1;
	V_ucSendBuf[12] = V_ucNxtP2;
	V_ucSendBuf[13] = V_ucLC1;

	V_ucDataLen = CL_Response_InIC;
	/*��ȡ����*/
	PF_OneDataReversed(V_ucSendBuf, GV_7816CMD.Header, CL_7816Header);	/*����֮ǰ��������ͷ*/
	/* InF_Delay_us(3000);*/
	if(V_ucCH == C_ESAM)	/*ESAM��Ҫ�޸�*/
	{
		GV_7816CMD.SW1_2= INF_SendData_7816_Esam(V_ucSendBuf, V_ucSendLen, V_ucReponseBuf, &V_ucDataLen);
		V_ucReturnData = C_IC_ESAM_RDWR_ERR;
	}
	else
	{
		GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucSendBuf, V_ucSendLen, V_ucReponseBuf, &V_ucDataLen);
		V_ucReturnData = C_IC_NOIN_ERR;
	}
	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk)
		&& ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) !=  C_Security_ProcessOk) )
	{
		return(V_ucReturnData);
	}

	/*��ȡ��Ӧ�������61XX��XXֵ���ԡ�*/
	/*InF_Delay_us(3000);*/
	PF_CopyDataBytes((uchar8 *)TB_GetResponse, V_ucSendBuf, CLen_TB_ESAM_4);
	V_ucSendBuf[CLen_TB_ESAM_4] = V_ucLC1;
	V_ucDataLen = V_ucLC1;
	PF_OneDataReversed(V_ucSendBuf, GV_7816CMD.Header, CL_7816Header);		/*����֮ǰ��������ͷ*/
	if(V_ucCH == C_ESAM)	/*ESAM��Ҫ�޸�*/
	{
		GV_7816CMD.SW1_2 = INF_SendData_7816_Esam(V_ucSendBuf, CLen_TB_ESAM_Le, pV_ucData, &V_ucDataLen);
	}
	else
	{
		GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucSendBuf, CLen_TB_ESAM_Le, pV_ucData, &V_ucDataLen);
	}
	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(V_ucReturnData);
	}
	else
	{
		return(C_OK);
	}
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	InF_SC_Get_MFile_PreSetCard(StrCardParse	*pStr_CardParse)
����������	����Ԥ�ÿ����û����ж���Ǯ���ļ�
���������	pStr_CardParse->CardNo :����(IC_CardNo,С��8�ֽ�)(ʵ��û���ã�����Ϊָ�봫��)
���������
			����Ԥ�ÿ�
			pStr_CardParse->PPMoney	:������Ԥ�ý�hex����λΪ��
			pStr_CardParse->IC_File[]	:Ԥ�ý��+Mac�����ݷ��ϴ��ģʽ

			�û���
			pStr_CardParse->PPMoney	:������Ԥ�ý�hex����λΪ��
			pStr_CardParse->PPNum		:�������
���ز�����	C_OK/C_IC_NOIN_ERR
����λ�ã�	�����û���������Ԥ�ÿ��ļ�
��	  ע��	����+Mac��ʽ��ȡʣ����
*******************************************************************************/
uchar8	InF_SC_Get_MFile_Card(StrCardParse 		*pStr_CardParse)
{
	uchar8	V_ucReturnData;
	uchar8	V_ucbuf[4];				/*Ǯ���ļ��й��������ʣ�����4�ֽ�*/

	if(pStr_CardParse->CardType == C_PresetCardCommand)	/*����Ԥ�ÿ�*/
	{
		/*��Mac������Ԥ�ÿ���ʣ����ݴ浽IC_InitM_PPMoney��
		��һ��ָ��Ϊ�Ը���ESAMǮ���ļ���833E000008=�������+4Mac*/
		V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_MoneyInPSC, CO_PSCM_PPMoney, IC_InitM_PPMoney,
					0x83, 0x3e, 0x00, 0x00, 0x08, IC_CardNo);
		if(V_ucReturnData != C_OK)
		{
			return(V_ucReturnData);
		}

		PF_OneDataReversed(IC_InitM_PPMoney, V_ucbuf, CLChargeBal_Hex_Cent);
		PF_Buffer4ToUlong32(V_ucbuf, &pStr_CardParse->PPMoney, CLChargeBal_Hex_Cent);

		#if 0
		/*����Ԥ�ƿ���ֻ�й����û�й������*/
		/*��Mac������Ԥ�ÿ��еĹ���������ݴ浽IC_InitM_PPNum
		��һ��ָ��Ϊ�Զ�ESAM��ֵ����¼��03����¼�ļ���1��08=�������+Mac����*/
		V_ReturnData = SC_ReadBinFileMac(C_Card,C_FC_MoneyInPSC,CO_PSCM_PPNum,IC_InitM_PPNum,
					0x83,0x3e,0x00,0x00,0x08,IC_CardNo);
		if(V_ReturnData != C_OK)
		{
			return(C_IC_NOIN_ERR);
		}
		PF_OneDataReversed(IC_InitM_PPNum, V_ucbuf, CL_PurchasingE_Num);
		PF_Buffer4ToUlong32(V_ucbuf, &pV_CardParse->PPNum, CL_PurchasingE_Num);
		#endif

		return(C_OK);
	}
	else if(pStr_CardParse->CardType == C_UserCardCommand)	/*�û���*/
	{
		/*��mac��ȡǮ���ļ����ݴ�IC_PPMoney������ָ��Ϊ��ֵ����*/
		V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_MoneyInUseCard, CO_UC_PPMoney, IC_PPMoney,
			0x80, 0x42, 0x00, 0x00, 0x0c, IC_CardNo);
		if(V_ucReturnData != C_OK)
		{
			return(C_IC_NOIN_ERR);
		}

		PF_OneDataReversed(IC_PPMoney, IC_PPMoney, CLChargeBal_Hex_Cent);
		PF_OneDataReversed(IC_PPNum, IC_PPNum, CL_PurchasingE_Num);
		PF_OneDataReversed(IC_PPMac, IC_PPMac, C_MacLen);

		PF_Buffer4ToUlong32(IC_PPMoney, &pStr_CardParse->PPMoney, CLChargeBal_Hex_Cent);
		PF_Buffer4ToUlong32(IC_PPNum, &pStr_CardParse->PPNum, CL_PurchasingE_Num);

		return(C_OK);
	}
	else
	{
		return(C_Error);
	}

}

/*******************************************************************************
����ԭ�ͣ�	uchar8	InF_SC_Backup_With_Mac(uchar8	V_ucType, uchar8 *pV_ucData)
����������	��Mac��ȡ��������
���������	V_ucType					:��ȡ���ͣ�ȡֵ����ע
			pV_ucData				:�������׵�ַ
���������	*pV_ucData				:���������ݡ����ģʽ��������Type��
���ز�����	C_OK/C_IC_NOIN_ERR
����λ�ã�
��    ע��	V_ucType = (�ο�����΢������ʽ���μ�BACKBUF)
			C_UPType_CurRate 	4�ֽ�(68 CMD Len1 Len2)��ǰ���ʵ��+Mac����137+4MAC
			C_UPType_BakRate	4�ֽ�(68 CMD Len1 Len2)���÷��ʵ��+�л�ʱ��+Mac����137+12(�л�)+4MAC
			C_UPType_CurLadder	��ǰ�׽���+Mac����89+4MAC
			C_UPType_BakLadder	�����׵��+�л�ʱ��+Mac����89+12+4MAC
			���ñ�������pV_ucData��Сһ�����㡣
*******************************************************************************/
uchar8	InF_SC_Backup_With_Mac(uchar8	V_ucType, uchar8 *pV_ucData)
{
	uchar8	V_ucReturnData;
	uchar8	V_ucbuf[8];			/*�ṩ���溯��һ����ָ��*/

	switch(V_ucType)
	{
		case		C_UPType_Other:		/*��������*/
			V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_INS, CO_INS_Bak_3, pV_ucData,
						0x83, 0x2A, (0x80|C_F_ParmInf), CO_INS_Bak_3, CL_UPType_Other, V_ucbuf);
			break;
		case		C_UPType_CurRate:	/*��ǰ���ʵ��,���ļ�0x68��ʼ*/
			V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_Price_InPSC_InUse, 0, pV_ucData,
						0x83, 0x2A, (0x80|C_F_ElePrice), 0, CL_UPType_CurRate, V_ucbuf);
			break;
		case		C_UPType_BakRate:	/*�����׷��ʵ��*/
			V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_PriceBak_InPSC_InUse, 0, pV_ucData,
						0x83, 0x2A, (0x80|C_F_ElePriceBak), 0, CL_UPType_BakRate, V_ucbuf);
			break;
		case		C_UPType_ChgRateClock:	/*���ʵ���л�ʱ��-��ָ���ļ���ƫ��10*/
			V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_INS, CO_INS_ChgRate, pV_ucData,
						0x83, 0x2A, (0x80|C_F_ParmInf), CO_INS_ChgRate, CL_UPType_ChgRateClock, V_ucbuf);
			break;
		case		C_UPType_CurLadder:		/*��ǰ����*/
			V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_Price_InPSC_InUse, CF_O_LadderBak, pV_ucData,
						0x83, 0x2A, (0x80|C_F_ElePrice), CF_O_LadderBak, CL_UPType_CurLadder, V_ucbuf);
			break;
		case		C_UPType_BakLadder:		/*�����׽���*/
			V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_PriceBak_InPSC_InUse, CF_O_LadderBak, pV_ucData,
						0x83, 0x2A, (0x80|C_F_ElePriceBak), CF_O_LadderBak, CL_UPType_BakLadder, V_ucbuf);
			break;

		default:							/*�������ǲ����ܵģ�����C_IC_NOIN_ERR����*/
			V_ucReturnData = C_IC_NOIN_ERR;
			break;
	}
	return(V_ucReturnData);
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	InF_SC_BackupW_With_Mac(uchar8 	V_ucType, uchar8 *pV_ucData)
����������	��MacдESAM����Mac��֤
���������	V_ucType				:��ȡ���ͣ�ȡֵ����ע
			*pV_ucData				:���������ݡ����ģʽ��������Type��
���������	��
���ز�����	C_OK/C_IC_ESAM_RDWR_ERR
����λ�ã�
��    ע��	V_ucType = (�ο�����΢������ʽ���μ�BACKBUF)
			C_UPType_CurRate 	4�ֽ�(68 CMD Len1 Len2)��ǰ���ʵ��+Mac����137+4MAC
			C_UPType_BakRate	4�ֽ�(68 CMD Len1 Len2)���÷��ʵ��+�л�ʱ��+Mac����137+12(�л�)+4MAC
			C_UPType_CurLadder	��ǰ�׽���+Mac����89+4MAC
			C_UPType_BakLadder	�����׵��+�л�ʱ��+Mac����89+12+4MAC
			���ñ�������pData��Сһ�����㡣
*******************************************************************************/
uchar8	InF_SC_BackupW_With_Mac(uchar8 	V_ucType, uchar8 *pV_ucData)
{
	uchar8	V_ucReturnData;

	switch(V_ucType)
	{
		case		C_UPType_Other:		/*��������*/
			V_ucReturnData = WriteBinFileMac(C_ESAM, pV_ucData, C_F_ParmInf, CO_INS_Bak_3, CL_UPType_Other);
			if(V_ucReturnData == C_OK)	/*��֤�ɹ�����Ϊ������������ˢ�������ļ���2�����,֮ǰ��1�ֽڵı����ֽںͱ������1�ͱ������2����9�ֽڡ�*/
			{
				WriteBinFile(C_ESAM, pV_ucData + 9, C_F_OpInfo, CF_O_RatioCTInOP,(3 + 3) );
			}
			break;
		case		C_UPType_CurRate:		/*��ǰ���ʵ��,���ļ�0x68��ʼ*/
			V_ucReturnData = WriteBinFileMac(C_ESAM, pV_ucData, C_F_ElePrice, 0, CL_UPType_CurRate);
			break;
		case		C_UPType_BakRate:		/*�����׷��ʵ��*/
			V_ucReturnData = WriteBinFileMac(C_ESAM, pV_ucData, C_F_ElePriceBak, 0, CL_UPType_BakRate);
			break;
		case		C_UPType_ChgRateClock:	/*���ʵ���л�ʱ��-��ָ���ļ���ƫ��10*/
			V_ucReturnData = WriteBinFileMac(C_ESAM, pV_ucData, C_F_ParmInf, CO_INS_ChgRate, CL_UPType_ChgRateClock);
			break;
		case		C_UPType_CurLadder:		/*��ǰ����*/
			V_ucReturnData = WriteBinFileMac(C_ESAM, pV_ucData, C_F_ElePrice, CF_O_LadderBak, CL_UPType_CurLadder);
			break;
		case		C_UPType_BakLadder:		/*�����׽���*/
			V_ucReturnData = WriteBinFileMac(C_ESAM,pV_ucData,C_F_ElePriceBak, CF_O_LadderBak, CL_UPType_BakLadder);
			break;
		default:							/*�������ǲ����ܵģ�����C_IC_NOIN_ERR����*/
			V_ucReturnData = C_IC_ESAM_RDWR_ERR;
			break;
	}

	return(V_ucReturnData);
}


/*******************************************************************************
����ԭ�ͣ�	void		InF_BackupData_Reversal(uchar8 V_ucType, uchar8 *pV_ucData)
����������	��������ߵ����������ݲ�д��
���������	V_ucType				:��ȡ���ͣ�ȡֵ����ע
			*pV_ucData				:���������ݡ����ģʽ��������Type��
���������	*pV_ucData				:�ߵ�������ݡ�С��ģʽ��������Type��
���ز�����	��
����λ�ã�
��    ע��	Type = (�ο�����΢������ʽ���μ�BACKBUF)
			C_UPType_Other	1�ֽڱ��ñ������1��2+��ѹ���������������+MAC   ��19���ֽ�
			C_UPType_CurRate 	4�ֽ�(68 CMD Len1 Len2)��ǰ���ʵ��+Mac����136
			C_UPType_BakRate	4�ֽ�(68 CMD Len1 Len2)���÷��ʵ��+Mac����136
			C_UPType_ChgRateClock		2�׷��ʵ���л�ʱ��+Mac����9�ֽ�
			C_UPType_CurLadder	��ǰ�׵��+Mac����68�ֽ�
			C_UPType_BakRate		�����׵��+�л�ʱ��+Mac����73�ֽ�
			���ñ�������pData��Сһ�����㡣
*******************************************************************************/
void		InF_BackupData_Reversal(uchar8 V_ucType, uchar8 *pV_ucData)
{

	switch(V_ucType)
	{
		case		C_UPType_Other:		/*��������*/
			PF_OneDataReversed(&pV_ucData[CO_UPOther_Alam1], &pV_ucData[CO_UPOther_Alam1], CLAlam1_Money);
			PF_OneDataReversed(&pV_ucData[CO_UPOther_Alam2], &pV_ucData[CO_UPOther_Alam2], CLAlam2_Money);
			PF_OneDataReversed(&pV_ucData[CO_UPOther_Ratio_CT], &pV_ucData[CO_UPOther_Ratio_CT], CLRatio_Curr_Tran_Esam);
			PF_OneDataReversed(&pV_ucData[CO_UPOther_Ratio_VT], &pV_ucData[CO_UPOther_Ratio_VT], CLRatio_Vol_Tran_Esam);
			return;
		case		C_UPType_CurRate:		/*��ǰ���ʵ��,���ļ�0x68��ʼ*/
		case		C_UPType_BakRate:		/*�����׷��ʵ��*/
			DataReversed(CBackUp_RateFF_Price, pV_ucData, C_RItem_Len_RateBak);
			return;
		case		C_UPType_ChgRateClock:	/*���ʵ���л�ʱ��-��ָ���ļ���ƫ��10*/
			PF_OneDataReversed(pV_ucData, pV_ucData, CLChange_Rate_Esam);
			return;
		case		C_UPType_CurLadder:		/*��ǰ����*/
			DataReversed(CBackUp_Ladder_Table, pV_ucData, (C_RITem_Len_LadderBak - 1) );
			return;
		case		C_UPType_BakLadder:		/*�����׽���*/
			DataReversed(CBackUp_Ladder_Table, pV_ucData, (C_RITem_Len_LadderBak - 1) );
			/*�͵�ǰ���ݱȣ�����1���л�ʱ��*/
			PF_OneDataReversed(&pV_ucData[CO_UPLadderChgClock], &pV_ucData[CO_UPLadderChgClock], CLChange_Ladder_Esam);
			return;
		default:						/*�������ǲ����ܵģ�����C_IC_NOIN_ERR����*/
			return;
	}
}


/*******************************************************************************
����ԭ�ͣ�uchar8	InF_SC_CardExtAuth(uchar8	*pV_ucCardNo)
�����������ⲿ��֤
���������pV_ucCardNo	:�����кţ�С�ˣ��̶�8�ֽ�
�����������
���ز�����C_OK/C_IC_NOIN_ERR/C_IC_ESAM_RDWR_ERR/C_IC_EXAUTH_ERR
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	InF_SC_CardExtAuth(uchar8	*pV_ucCardNo)
{
	uchar8		V_ucRand8[10];
	uchar8		V_ucSendBuf[CL_Send_InIC];
	uchar8		V_ucReponseBuf[CL_Response_InIC];
	uchar8		V_ucDataLen;
	ushort16	V_usDataLen;

	/*�ÿ�����Rand8*/
	PF_CopyDataBytes((uchar8 * )TB_GetChallenge, V_ucSendBuf, CLen_TB_ESAM_4);
	V_ucSendBuf[CLen_TB_ESAM_4] = 8;
	V_ucDataLen = 8;
	PF_OneDataReversed(V_ucSendBuf,GV_7816CMD.Header, CL_7816Header);		/*����֮ǰ��������ͷ*/
	GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucSendBuf, CLen_TB_ESAM_Le, V_ucRand8, &V_ucDataLen);
	if(GV_7816CMD.SW1_2 != C_Security_CommandOk)	/*����SW !=9000*/
	{
		return(C_IC_NOIN_ERR);
	}

	/*���ܵõ�����(��ǰ2���ϲ���1��)*/
	/*800808020020+cardreset8+rand8*/
	PF_CopyDataBytes((uchar8 * )TB_AuthDistributedkey_698, V_ucSendBuf, CLen_TB_ESAM_Lc_698_Esam);
	PF_OneDataReversed(pV_ucCardNo, &V_ucSendBuf[CLen_TB_ESAM_Lc_698_Esam], CL_CardNo);	/*��ɢ����Ϊ����*/
	PF_CopyDataBytes(V_ucRand8, &V_ucSendBuf[CLen_TB_ESAM_Lc_698_Esam + CL_CardNo], 8);
	V_usDataLen = CL_Response_InIC;
	GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucSendBuf, (CLen_TB_ESAM_Lc_698_Esam + CL_CardNo + 8), V_ucReponseBuf, &V_usDataLen);
	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType)!= C_Security_ProcessOk) )
	{
		return(C_IC_ESAM_RDWR_ERR);
	}


	/*�ⲿ��֤00 82 00 02 08 + dest8 ע������P2Ҫ���ĳ�02����Կ����*/
	/*InF_Delay_us(3000);*/
	PF_CopyDataBytes((uchar8 * )TB_IRExtAuth, V_ucSendBuf, CLen_TB_ESAM_Lc);
	V_ucSendBuf[3] = 2;				/*P2=2*/
	PF_CopyDataBytes(V_ucReponseBuf,&V_ucSendBuf[CLen_TB_ESAM_Lc],8);
	PF_OneDataReversed(V_ucSendBuf, GV_7816CMD.Header, CL_7816Header);		/*����֮ǰ��������ͷ*/
	V_ucDataLen = CL_Response_InIC;
	GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucSendBuf, (CLen_TB_ESAM_Lc + 8), V_ucReponseBuf, &V_ucDataLen);
	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_IC_EXAUTH_ERR);
	}
	else
	{
		return(C_OK);
	}
}



/*******************************************************************************
����ԭ�ͣ�uchar8	Is_Meter_Num_OK(uchar8	*pV_ucFlag)
�����������ж��������Ƿ�����ݲ���һ��
���������*pV_ucFlag	:��ţ����ģʽ�̶�6�ֽ�
�����������
���ز�����C_OK/C_Error
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	InF_SC_Meter_Num_OK(uchar8 *pV_ucMeterNum)
{
	uchar8		V_ucbuf1[CLMeter_Num];
	uchar8		V_ucbuf2[CLMeter_Num];
	ushort16	V_usDataLen = CLMeter_Num;
	ushort16	V_usDataEnCode;

	/*��Ŵ�˸ĳ�С��*/
	PF_OneDataReversed(pV_ucMeterNum, V_ucbuf1, CLMeter_Num_Esam);

	/*�����ݲ���*/
	if(InF_Read_Data(CMeter_Num, V_ucbuf2, &V_usDataLen, &V_usDataEnCode) != C_OK)
	{
		return(C_Error);
	}
	if(PF_Campare_Data(V_ucbuf1, V_ucbuf2, CLMeter_Num_Esam) == C_Equal)
	{
		return(C_OK);
	}
	else
	{
		return(C_Error);
	}
}


/*******************************************************************************
����ԭ�ͣ�uchar8	InF_SC_Is_UserCardNull(uchar8	*pV_ucFlag)
�����������ж��û����Ƿ�Ϊ��
���������
���������*pV_ucFlag				:Ϊ�ձ�־��C_OK��ʾ�գ�C_Error��ʾ�ǿ�
���ز�����C_OK/C_IC_NOIN_ERR
����λ�ã�
��    ע��������΢�жϷ�д�ļ��е���������ֵΪȫ0����Ϊ��
*******************************************************************************/
uchar8	InF_SC_Is_UserCardNull(uchar8	*pV_ucFlag)
{
	uchar8	V_ucReturnData;
	uchar8	V_ucReponseBuf[CL_Response_InIC];

	V_ucReturnData = InF_SC_RDBinFileNoMac(C_Card, C_FC_WRBackInUseCard, 0, 49, V_ucReponseBuf);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}
	if( (V_ucReponseBuf[CF_O_OPI_RWRClock] != 0)			/*68 CMD Len����һ���ֽڲ�Ϊ0��������д�ļ���Ϊ��698�ķ����û�����*/
		|| (V_ucReponseBuf[CF_O_OPI_RWRClock + 1] != 0)		/*	68 11 00 2B 00 ...00 CS 16(��������ԭ�����жϷ���) */
		|| (V_ucReponseBuf[CF_O_OPI_RWRClock + 2] != 0)
		|| (V_ucReponseBuf[CF_O_OPI_RWRClock + 3] != 0)
		|| (V_ucReponseBuf[CF_O_OPI_RWRClock + 4] != 0) )
	{
		*pV_ucFlag = C_Error;
	}
	else	/*��д�ļ�Ϊ��*/
	{
		*pV_ucFlag = C_OK;
	}
	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�uchar8	InF_SC_GetCustNumWithMac_UseCard(uchar8 *pCustNum)
������������mac��ȡ�û����еĿͻ����
���������
���������pV_ucCustNum				:�ͻ���ţ��̶�10�ֽ�С��ģʽ
���ز�����C_OK/C_IC_NOIN_ERR
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	InF_SC_GetCustNumWithMac_UseCard(uchar8 *pV_ucCustNum)
{
	uchar8	V_ucReponseBuf[CL_Response_InIC];
	uchar8	V_ucReturnData;

	V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_INS, CO_INS_UseC_CustNum, V_ucReponseBuf,
		0x83, 0x2A, 0x8F, 0x06, (CLCustomer_Num + C_MacLen), V_ucReponseBuf);
	if(V_ucReturnData != C_OK)
	{
		return(C_IC_NOIN_ERR);
	}
	else
	{
		PF_OneDataReversed(V_ucReponseBuf, pV_ucCustNum, CLCustomer_Num);
		PF_OneDataReversed(&V_ucReponseBuf[CLCustomer_Num], &pV_ucCustNum[CLCustomer_Num], C_MacLen);
		return(C_OK);
	}
}


/*******************************************************************************
����ԭ�ͣ�uchar8	InF_SC_WR_UCReturnFile(uchar8	*pV_ucCardNo)
������������д�û�����д�ļ�
���������pV_ucCardNo				:����ţ��̶�8�ֽڣ�С��ģʽ
�����������
���ز�����C_OK/C_IC_NOIN_ERR/C_IC_ESAM_RDWR_ERR
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	InF_SC_WR_UCReturnFile(uchar8	*pV_ucCardNo)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;

	/*д�������ļ�	*/
	V_ucReturnData = SC_ReadRunFileMac(C_ESAM, C_F_OpInfo, CF_O_OPI_Start, V_ucbuf,
		0x04, 0xD6,(0x80|C_FC_WRBackInUseCard), CF_O_OPI_Start, (CL_OPI + C_MacLen), pV_ucCardNo);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}

	/*��д*/
	V_ucReturnData = WriteBinFileMac(C_Card, V_ucbuf, C_FC_WRBackInUseCard, CF_O_OPI_Start, CL_OPI + C_MacLen);

	return(V_ucReturnData);
}


/*******************************************************************************
����ԭ�ͣ�	ushort16	InF_S_WR_ReturnFile(uchar8 *pV_ucData, uchar8 V_ucLength)
����������	д�˷��ļ������н���
���������	*pV_ucData			:����
			V_ucLength		:����
���������	*pV_ucData			:���ܺ��(����)�˷ѽ��+mac���̶�8�ֽڣ�С��ģʽ
���ز�����	C_OK/C_SERR_ESAM_VF/C_SERR_OtherErr
����λ�ã�
��    ע��	pData���뱣֤8�ֽڿռ�
*******************************************************************************/
ushort16	InF_S_WR_ReturnFile(uchar8 *pV_ucData, uchar8 V_ucLength)
{
	uchar8	V_ucbuf[20];
	uchar8	V_ucReturnData;

	/*���ȳ�������Χ*/
	if( (V_ucLength > 20) || (V_ucLength < 4) )		/*���ȴ���*/
	{
		return(C_SERR_OtherErr);
	}

	/*���ݵߵ�---���϶���������ص㣬�������ݣ����ĺ�Mac�ֿ��ߵ�*/
	PF_OneDataReversed(pV_ucData, V_ucbuf, (V_ucLength - C_MacLen) );
	PF_OneDataReversed(&pV_ucData[V_ucLength - C_MacLen], &V_ucbuf[V_ucLength - C_MacLen], C_MacLen);

	/*��Macд�������ļ�(�˷��ļ����ļ���0C)*/
	V_ucReturnData = WriteBinFileMac(C_ESAM, V_ucbuf, C_F_ReturnFile, 0, V_ucLength);
	if(V_ucReturnData != C_OK)
	{
		if(V_ucReturnData == C_IC_MAC_ERR)
		{
			return(C_SERR_ESAM_VF);
		}
		else
		{
			return(C_SERR_OtherErr);
		}
	}
	/*���������ļ�����+mac*/
	V_ucReturnData = InF_SC_RDBinFileNoMac(C_ESAM, C_F_ReturnFile, 0, (CLReturn_Money + C_MacLen), V_ucbuf);
	if(V_ucReturnData == C_OK)
	{
		PF_OneDataReversed(V_ucbuf, pV_ucData, CLReturn_Money);
		PF_OneDataReversed(&V_ucbuf[CLReturn_Money], &pV_ucData[CLReturn_Money], C_MacLen);

		return(C_OK);
	}
	else
	{
		return(C_SERR_OtherErr);
	}
}

/*******************************************************************************
����ԭ�ͣ�	ushort16	InF_S_OPMoneyFile_Return(uchar8 *pV_ucData)
����������	���Ǯ���˷���֤
���������	*pV_ucData				:�˷ѽ��+Mac��8�ֽڣ�С��
���������	��
���ز�����	C_OK/C_SERR_ESAM_VF/C_SERR_OtherErr
����λ�ã�
��    ע��	������ESAM�������˷�Mac��֤��ͬʱ�ж��˹��������
			��������仯1�Σ��������˷�1��
			*pV_ucDataά�ֲ���
*******************************************************************************/
ushort16	InF_S_OPMoneyFile_Return(uchar8 *pV_ucData)
{
	uchar8		V_ucSendBuf[CL_Send_InIC];
	uchar8		V_ucResponseBuf[CL_Response_InIC];
	uchar8		V_ucDataLen = CL_Response_InIC;
	ushort16	V_usReturnData;

	/*��ȡ����ͷ*/
	V_ucSendBuf[0] = 0x84;			/*��Mac�ۿ�*/
	V_ucSendBuf[1] = 0x30;
	V_ucSendBuf[2] = 0x02;			/*��¼��*/
	V_ucSendBuf[3] = 0x0C;			/*bit7-3�ļ��ţ�1��Ǯ���ļ�,bit2-0=100��ʾ��ǰ��¼��ΪP1*/
	V_ucSendBuf[4] = 0x08;			/*����*/

	/*��������*/
	PF_OneDataReversed(pV_ucData, &V_ucSendBuf[CLen_TB_ESAM_Lc], CLReturn_Money);
	PF_OneDataReversed(&pV_ucData[CLReturn_Money], &V_ucSendBuf[CLen_TB_ESAM_Lc+CLReturn_Money], C_MacLen);

	V_usReturnData = INF_SendData_7816_Esam(V_ucSendBuf, (CLen_TB_ESAM_Lc + CLReturn_Money + C_MacLen), V_ucResponseBuf, &V_ucDataLen);

	if( (V_usReturnData != C_Security_CommandOk) && ( (V_usReturnData & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		if( (V_usReturnData == C_Security_SafetyDataIncorrect) || (GV_7816CMD.SW1_2 == C_Security_MacErr) )
		{
			return(C_SERR_ESAM_VF);
		}
		else
		{
			return(C_SERR_OtherErr);
		}
	}
	else	/*����ȱ������ͣ�00C0000008 ���أ�ʣ����+���ν��׽��+9000 */
	{
		return(C_OK);
	}
}


/*******************************************************************************
����ԭ�ͣ�	ushort16	InF_S_Software_Campare(uchar8 *pV_ucData, uchar8 *pV_ucFactorData, uchar8 V_ucKeyNum)
����������	�������ȶ����ݼ���
���������	*pV_ucData	:��ַpData���������ݣ�
			pV_ucFactorData:��ɢ���ӵ�ַ
			V_ucKeyNum:��Կ����
���������	*pV_ucData���ܺ�����
���ز�����	C_OK/C_SERR_ESAM_VF/C_SERR_OtherErr
����λ�ã�
��    ע��
*******************************************************************************/
ushort16	InF_S_Software_Campare(uchar8 *pV_ucData, uchar8 *pV_ucFactorData, uchar8 V_ucKeyNum)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen], V_ucDataLen;
	ushort16	V_usReturnData16;

	/*��ESAM�Է�ɢ���ӽ��з�ɢ*/
	V_ucDataLen = CLen_S_BufMaxLen;
	PF_CopyDataBytes((uchar8 *)TB_AuthDistributedkey, &V_ucbuf[0], CLen_TB_ESAM_Lc);		/*��ȡ����ͷ*/
	V_ucbuf[3] = V_ucKeyNum;	/*�滻��Կ����*/
	PF_CopyDataBytes(pV_ucFactorData, &V_ucbuf[CLen_TB_ESAM_Lc], CL_Auth_Dis_factor);		/*�����ɢ���ӣ�û�����ݵߵ�����	*/
	V_usReturnData16 = INF_SendData_7816_Esam(&V_ucbuf[0], (CLen_TB_ESAM_Lc + CL_Auth_Dis_factor), &V_ucbuf[0], &V_ucDataLen);
	if( (V_usReturnData16 !=C_Security_CommandOk) && ( (V_usReturnData16 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_Error);
	}

	/*����ʱ��ɢ��Կ��������*/
	V_ucDataLen = CLen_S_BufMaxLen;
	PF_CopyDataBytes((uchar8 *)TB_SoftwareCampare, &V_ucbuf[0], CLen_TB_ESAM_Lc);			/*��ȡ����ͷ*/
	PF_CopyDataBytes(pV_ucData, &V_ucbuf[CLen_TB_ESAM_Lc], CL_SoftwareCampare_Data);		/*������������ݣ�û�����ݵߵ�����*/
	V_usReturnData16 = INF_SendData_7816_Esam(&V_ucbuf[0],(CLen_TB_ESAM_Lc + CL_SoftwareCampare_Data), &V_ucbuf[0], &V_ucDataLen);
	if( (V_usReturnData16 != C_Security_CommandOk) && ( (V_usReturnData16 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_Error);
	}

	/*����Ӧ*/
	V_ucDataLen = CLen_S_BufMaxLen;
	PF_CopyDataBytes( (uchar8 * )TB_GetResponse, V_ucbuf, CLen_TB_ESAM_4);
	V_ucbuf[CLen_TB_ESAM_4] = CL_SoftwareCampare_Data;
	V_usReturnData16 = INF_SendData_7816_Esam(V_ucbuf, (CLen_TB_ESAM_4 + 1), V_ucbuf, &V_ucDataLen);
	if( (V_usReturnData16 != C_Security_CommandOk) && ( (V_usReturnData16 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_Error);
	}
	PF_OneDataReversed(V_ucbuf, pV_ucData, CL_SoftwareCampare_Data);

	return C_OK;
}

/*******************************************************************************
����ԭ�ͣ�	ushort16	InF_S_Software_Campare_698(uchar8 *pV_ucData, uchar8 *pV_ucFactorData, uchar8 V_ucKeyNum, ushort16 *pV_usDataLen, uchar8 *pV_ucRN_Data)
����������	���698����ȶ����ݼ���
���������	*pV_ucData			:��ַpData���������ݣ�
			pV_ucFactorData	:��ɢ���ӵ�ַ
			V_ucKeyNum	:��Կ����
���������	*pV_ucData���ܺ�����
���ز�����	C_OK/C_SERR_ESAM_VF/C_SERR_OtherErr
����λ�ã�
��    ע��
*******************************************************************************/
ushort16	InF_S_Software_Campare_698(uchar8 *pV_ucData, uchar8 *pV_ucFactorData, uchar8 V_ucKeyNum, ushort16 *pV_usDataLen, uchar8 *pV_ucRN_Data)
{
	uchar8		V_ucbuf[300];
	ushort16	V_usReturnData16, V_usDataLen, V_usDataLen2;

	V_usDataLen = 300;

	/*��ȡ����ͷ*/
	V_ucbuf[0] = 0x80;
	V_ucbuf[1] = 0x0A;
	V_ucbuf[2] = 0x48;
	V_ucbuf[3] = V_ucKeyNum;	/*��Կ����*/
	V_usDataLen2 = *pV_usDataLen + CL_Auth_Dis_factor + CL_Auth_Rand1_SoftCam;
	PF_Ushort16ToBuffer2(&V_ucbuf[4], &V_usDataLen2);		/*lc*/
	PF_OneDataReversed(&V_ucbuf[4], &V_ucbuf[4], 2);
	PF_CopyDataBytes(pV_ucFactorData, &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], CL_Auth_Dis_factor);	/*�����ɢ���ӣ���ʱ���ñȶ�������Ϊ��ɢ���ӣ���������������	*/
	/*�����������ȡ������ʼ��ַ��������ʼ��ַ����λ��0*/
	PF_CopyDataBytes_698(pV_ucRN_Data, &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam + CL_Auth_Dis_factor], CL_Auth_Rand1_SoftCam);	/*���������*/

	PF_CopyDataBytes_698(pV_ucData, &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam + CL_Auth_Dis_factor + CL_Auth_Rand1_SoftCam], *pV_ucData);	/*������������ݣ�û�����ݵߵ�����	*/
	V_usReturnData16 = INF_SendData_698_Esam(&V_ucbuf[0], (CLen_TB_ESAM_Lc_698_Esam + V_usDataLen2), &V_ucbuf[0], &V_usDataLen);
	if( (V_usReturnData16 != C_Security_CommandOk) && ( (V_usReturnData16 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_Error);
	}
	PF_CopyDataBytes_698(&V_ucbuf[0], pV_ucData, V_usDataLen);
	*pV_usDataLen = V_usDataLen;

	return C_OK;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 InF_IS_UpdateMInEsamTimer(void)
������������ǰ�Ƿ���״̬��ѯ15min��ʱ�жϺ�
�����������
�����������
���ز�����C_OK:��ǰ������15min��ʱ�ڼ���Ը���EE��ESAM����,C_Error��ǰ������ʱ�ڼ䲻�ܸ���EE��ESAM����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 InF_IS_UpdateMInEsamTimer(void)
{
	if(SV_UpdateMInEsamTimer == 0)
	{
		return C_OK;
	}
	else
	{
		return C_Error;
	}
}


