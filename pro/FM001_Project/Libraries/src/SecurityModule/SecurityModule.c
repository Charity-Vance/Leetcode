/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     SecurityModule.c
Version:       V1
Author:        jiangzs
Date:          2014-3-31
Description:   安全文件
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:   20211021
   	   Author: lx
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
----------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
   	   Author:
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
******************************************************************************/

#include    "SecurityModule.h"

Str7816HeaderSW		GV_7816CMD;

MoneyClient_Type	MoneyClient_Table;			/*暂存需要写数据层变量*/

uchar8 GV_ESAMAction9_SIDP1P2;



const Str_EsamTable	C_EsamNatureToAction[]=
{
/*698属性DI1DI0		esam命令码P2		偏移	长度*/
	{0x0200,			0x02,			0,		8},		/*ESAM序列号*/
	{0x0300,			0x01,			0,		5},		/*ESAM版本号*/
	{0x0400,			0x04,			0,		16},	/*对称密钥版本*/
	{0x0500,			0x05,			0,		4},		/*会话时效门限 + 剩余时间*/
	{0x0600,			0x05,			4,		4},		/*会话时效剩余时间*/
	{0x0700,			0x06,			0,		12},	/*当前计数器*/
	{0x1100,			0x08,			0,		1},		/*身份认证权限*/
	{0x1200,			0x11,			0,		8},		/*终端地址*/
	{0x1300,			0x12,			0,		4},		/*终端广播计数器*/
	{0x1400,			0x13,			0,		4},		/*终端与电表会话计数器*/
	{0x1500,			0x14,			0,		8},		/*终端会话时效门限 +剩余时间*/
	{0x1501,			0x14,			0,		4},		/*终端会话时效门限*/
	{0x1502,			0x14,			4,		4},		/*终端会话剩余时间*/

/*	{C_Remain_termal_Item,	0x14}*//*终端会话剩余时间(自扩命令程序内部用)*/

};


#define	CL_EsamNature	(sizeof (C_EsamNatureToAction) / sizeof (Str_EsamTable) )

/*******************************************************************************
函数原型：	uchar8 InF_Get_SafeModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
功能描述：	读安全模块接口函数，支持读esam属性
输入参数：	V_ulOAD：读取的数据的OAD标识码
输出参数：	pV_ucDataBuf：返回数据首地址
			pV_usDataLen：返回数据长度
			pV_usDataEncode：返回数据编码
返回参数：	C_OK:表示成功;应答错误:C_Error;
调用位置：
备    注：	供对象管理层调用
			返回数据都是小端格式
*******************************************************************************/
uchar8 InF_Get_SafeModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
{
	uchar8		V_ucReturn = C_Error, V_ucLen;
	ushort16	V_usActionID, V_usLen;
	uchar8		V_ucBuffer[C_Max_EsamLen];

	V_usLen = C_Max_EsamLen;
	V_ucLen = C_Max_EsamLen;

	if( (V_ulOAD & 0xFFFF0000) == 0xF1000000) 	/*ESAM属性*/
	{
		if( (V_ulOAD == C_IRAuth_Timer)					/*红外认证时效门限*/
			|| (V_ulOAD == CID_Auth_T_Remain_Time)		/*终端身份认证剩余时间*/
			|| (V_ulOAD == CInfra_Auth_Remain_Time) )	/*红外认证剩余时间*/

		{
			V_ucReturn = InF_Read_Data(V_ulOAD, &V_ucBuffer[0], &V_usLen, pV_usDataEncode);	/*读数据层*/
		}
		else
		{
			V_usActionID = (ushort16)(V_ulOAD);
			V_ucReturn = S_ReadEsam_698(&V_ucBuffer[0], &V_usLen, V_usActionID);	/*读ESAM*/

			/*数据翻转*/
			PF_OneDataReversed(V_ucBuffer, V_ucBuffer,V_usLen);
		}
	}
	else if(V_ulOAD == CPurchasePowTime)	/*钱包文件的购电次数*/
	{
		V_ucReturn = ReadRecordFile(&V_ucBuffer[0], &V_ucLen, C_PurchasingE_Num_Mac);
		V_usLen = V_ucLen;
	}
	else
	{
		V_ucReturn = C_IDError;
	}


	/*********以下为置返回参数 ******************************/
	if(V_ucReturn == C_OK)
	{
		if(*pV_usDataLen < V_usLen)
		{
			V_ucReturn =  C_DataLenError;	/*数据长度错*/
		}
		else
		{
			/*拷贝数据*/
			*pV_usDataLen = V_usLen;
			memcpy( pV_ucDataBuf, V_ucBuffer, *pV_usDataLen);
		}
	}


	return(V_ucReturn);

};



/*******************************************************************************
函数原型：uchar8 InF_JudgeKeyStatus(void)
功能描述：判断当前密钥状态
输入参数：无
输出参数：无
返回参数：C_StateOfTestKey/C_StateOfOfficialKey
调用位置：
备    注：
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
函数原型：	uchar8 InF_S_Authentication_698(uchar8 *pV_ucData, ushort16* pV_usLen,uchar8 V_ClientAddr)
功能描述：	身份认证接口函数
输入参数：	pV_ucData:   	数据的起始指针 注意：发送数据长度(固定:32字节+4字节MAC)
			V_ucClientAddr:主站/终端地址
输出参数：	pV_ucData:		返回的数据
			pV_usLen:	返回数据长度(固定:48字节+4字节MAC)
返回参数：	C_OK:表示成功;应答错误:C_Error;
调用位置：
备    注：	1:至少52字节
			接收的数据格式:XX(密文长度)+XX...XX(密文内容)+XX(MAC长度)+XX...XX(MAC内容)
			发送ESAM数据格式:8102000000+24+XX...XX(密文内容)+XX...XX(MAC内容)
*******************************************************************************/
uchar8 InF_S_Authentication_698(uchar8 *pV_ucData, ushort16 *pV_usLen, uchar8 V_ucClientAddr)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	ushort16	V_usReceiveLen, V_usReturnData16, V_usSendLen;
	uchar8		V_ucAuthSessionLen, V_ucMACLen;

	if(V_ucClientAddr == Termal_Address)		/*终端身份认证*/
	{
		PF_CopyDataBytes((uchar8 * )TB_Authentication_698_termal, V_ucDataBuffer, CLen_TB_ESAM_Lc_698);
	}
	else	/*主站身份认证*/
	{
		PF_CopyDataBytes((uchar8 * )TB_Authentication_698, V_ucDataBuffer, CLen_TB_ESAM_Lc_698);
	}

	V_ucDataBuffer[CLen_TB_ESAM_Lc_698] = AuthSessionData1Len_698 + C_MAC_Length_698;

	/*拷贝密文数据长度*/
	V_ucAuthSessionLen = *pV_ucData;
	PF_CopyDataBytes(&pV_ucData[C_len_698], &V_ucDataBuffer[CLen_TB_ESAM_Lc_698 + C_len_698], V_ucAuthSessionLen);

	/*拷贝密文数据长度*/
	V_ucMACLen = *(pV_ucData + C_len_698 + V_ucAuthSessionLen);
	PF_CopyDataBytes((pV_ucData + C_len_698 * 2 + V_ucAuthSessionLen), &V_ucDataBuffer[CLen_TB_ESAM_Lc_698 + C_len_698 + V_ucAuthSessionLen], V_ucMACLen);

	/********* 以下发送esam数据 *********************************************************/
	V_usSendLen =CLen_TB_ESAM_Lc + C_len_698 + AuthSessionData1Len_698 + C_MAC_Length_698;		/*发送数据长度*/

	V_usReceiveLen = MaxLength_698;		/*接收数据最大长度*/
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

	/*********以下为置返回参数 *********************************************************/
	*pV_usLen = V_usReceiveLen;

	if(V_ucClientAddr == Master_Address)
	{
		if(*pV_usLen != (AuthSessionData2Len_698 + C_MAC_Length_698) )	/*返回48个字节+4MAC*/
		{
			return(C_SCErr_DAR);
		}

		*pV_usLen = *pV_usLen + C_len_698 + C_len_698;
		pV_ucData[0] = AuthSessionData2Len_698;
		PF_CopyDataBytes(V_ucDataBuffer, &pV_ucData[1], pV_ucData[0]);	/*应答APDU*/
		pV_ucData[AuthSessionData2Len_698 + C_len_698] = C_MAC_Length_698;
		PF_CopyDataBytes(&V_ucDataBuffer[AuthSessionData2Len_698], &pV_ucData[C_len_698 + C_len_698 + AuthSessionData2Len_698], C_MAC_Length_698);	/*应答APDU*/

	}
	else
	{
		if(*pV_usLen != (AuthSessionData2Len_698_termal + C_MAC_Length_698) )		/*返回48个字节+4MAC*/
		{
			return(C_SCErr_DAR);
		}

		*pV_usLen = *pV_usLen + C_len_698 + C_len_698;
		pV_ucData[0] = AuthSessionData2Len_698_termal;
		PF_CopyDataBytes(V_ucDataBuffer, &pV_ucData[1], pV_ucData[0]);	/*应答APDU*/
		pV_ucData[AuthSessionData2Len_698_termal + C_len_698] = C_MAC_Length_698;
		PF_CopyDataBytes(&V_ucDataBuffer[AuthSessionData2Len_698_termal], &pV_ucData[C_len_698 + C_len_698 + AuthSessionData2Len_698_termal], C_MAC_Length_698);	/*应答APDU*/

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
函数原型：		uchar8  INF_S_Decrypt_698(uchar8 *pV_ucAPDU,ushort16 *Len,uchar8 V_ucSecurityMode,uchar8 *SID_Data)
功能描述：		解密APDU
输入参数： 		pV_ucAPDU:		需解密的APDU首地址
			pV_usLen:		需验证数据长度
			V_ucSecurityMode:2种数据验证模式:SID_698;SID_MAC_698
			pV_ucSID_Data:	数据验证信息首地址
输出参数：		pV_ucAPDU:		解密后的APDU首地址
			pV_usLen:		解密后的数据长度
返回参数：		应答成功:C_OK;
	   		应答错误分以下几种:
   			对称解密错误:C_SymmetryDecodeErr_DAR;签名错误:C_SignatureErr_DAR;其它错误:C_Error;
调用位置：
备    注：		P_ APDU开512字节
		 	通信发送的数据格式: SID_Data(SID_MAC_698):	XXXXXXXX(标识)+xx(附加数据长度)+XX...XX(附加数据)+xx(MAC长度)+XX...XX(MAC)
		 	通信发送的数据格式: SID_Data(SID_698):		XXXXXXXX(标识)+xx(附加数据长度)+XX...XX(附加数据)
		 	发送给ESAM的格式:	SID_MAC_698:	XXXXXXXX(标识)+XX...XX(附加数据)+XX...XX(密文)+XX...XX(MAC)
		 	发送给ESAM的格式:	SID_698:		XXXXXXXX(标识)+XX...XX(附加数据)+XX...XX(密文)
*******************************************************************************/
uchar8  INF_S_Decrypt_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucSecurityMode, uchar8 *pV_ucSID_Data)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	uchar8		V_ucAttachLength,V_ucAttachOffset;
	uchar8		V_ucDataOffset;
	uchar8		V_ucMACLength = 0,V_ucMACOffset;
	ushort16	V_usReturnData16,V_usSendLen,V_usDataLength,V_usReceiveLen;


	/*偏移和长度*/
	/*密文*/
	V_ucDataOffset = 0;
	V_usDataLength = *pV_usLen;

	/*附加数据*/
	V_ucAttachLength = *(pV_ucSID_Data + C_DataID_Length_698);	/*附加数据长度*/
	V_ucAttachOffset = C_DataID_Length_698 + C_len_698;


	if( (V_ucSecurityMode != SID_MAC_698) && (V_ucSecurityMode != SID_698) )	/*SID_MAC,SID*/
	{
		return(C_OK);
	}

	/*拷贝数据*/
	/*标识*/
	PF_CopyDataBytes_698(pV_ucSID_Data,V_ucDataBuffer, C_DataID_Length_698);	/*标识*/

	/*附加数据*/
	PF_CopyDataBytes_698(pV_ucSID_Data+V_ucAttachOffset,V_ucDataBuffer + C_DataID_Length_698, V_ucAttachLength);

	/*标识密文*/
	PF_CopyDataBytes_698(pV_ucAPDU+V_ucDataOffset,V_ucDataBuffer + C_DataID_Length_698 + V_ucAttachLength, V_usDataLength);

	if(V_ucSecurityMode == SID_MAC_698)
	{
		/*MAC*/
		V_ucMACLength = *(pV_ucSID_Data + C_DataID_Length_698 + C_len_698 + V_ucAttachLength);
		V_ucMACOffset = C_DataID_Length_698 + C_len_698 + V_ucAttachLength + C_len_698;

		PF_CopyDataBytes(pV_ucSID_Data + V_ucMACOffset, V_ucDataBuffer + C_DataID_Length_698 + V_ucAttachLength + V_usDataLength, V_ucMACLength);	/*MAC*/
	}

	/********* 以下发送esam数据 *********************************************************/
	V_usSendLen = C_DataID_Length_698 + V_ucAttachLength + V_usDataLength + V_ucMACLength;
	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		if( (V_usReturnData16 == C_Security_SafetyDataIncorrect) || (V_usReturnData16 == C_Security_MacErr) )
		{
		/*	if(V_ucDataBuffer[0] != 0x05)*/		/*读操作，不累计mac错*/

			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}

		return(C_SymmetryDecodeErr_DAR);
	/*	return(C_ESAMErr_DAR);*/
	}

	/*********以下为置返回参数*********************************************************/
	*pV_usLen = V_usReceiveLen;
	PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucAPDU, *pV_usLen);		/*应答APDU*/

	return(C_OK);
}

/*******************************************************************************
函数原型：	uchar8  S_Encrypt_RN_698(uchar8 *pV_ucAPDU,ushort16 *pV_usLen,uchar8 V_ucEncryptMode,uchar8 *pV_ucRN_Data,uchar8 *pV_ucMAC)
功能描述：	读数据加密
输入参数： 	pV_ucAPDU:		需加密的APDU首地址
			pV_usLen:		需加密数据长度
 			pV_ucRN_Data:		验证数据首地址
			V_ucEncryptMode:三种数据加密方式:明文+MAC;密文;密文+MAC
输出参数：	pV_ucAPDU:		加密后的数据
			pV_usLen:		加密后的数据长度
返回参数：	应答成功:C_OK;
			应答错误分以下几种:
			安全认证失败:C_SCErr_DAR;其它错误:C_Error;
调用位置：
备    注：	发送给ESAM的格式:	XXXXXXXX(数据头)+LC+XX...XX(RN)+XX...XX(明文)
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

	V_ucRD_Len = *(pV_ucRN_Data + C_len_698);	/*RN数据长度*/

	PF_CopyDataBytes_698(pV_ucRN_Data + 2, &V_ucDataBuffer[CLen_TB_ESAM_4_698 + CLen_LC_Len_698], V_ucRD_Len);	/*拷贝RN*/
	PF_CopyDataBytes_698(pV_ucAPDU, &V_ucDataBuffer[CLen_TB_ESAM_4_698 + CLen_LC_Len_698 + V_ucRD_Len], *pV_usLen);	/*拷贝明文数据*/

	/********* 以下发送esam数据 *********************************************************/
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


/*********以下为置返回参数 *********************************************************/
	*pV_usLen = V_usReceiveLen;
	if(V_ucEncryptMode == RN_698)
	{
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucRN_Data, *pV_usLen);		/*应答APDU*/
	}
	else
	{
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucAPDU, *pV_usLen);			/*应答APDU*/
	}

	return(C_OK);
}


/*******************************************************************************
函数原型：	uchar8  S_Encrypt_698(uchar8 *pV_ucAPDU,ushort16 *pV_usLen,uchar8 V_ucEncryptMode,uchar8 *pV_ucMAC)
功能描述：	数据加密
输入参数：	pV_ucAPDU:		需加密的APDU首地址
			pV_usLen:		需加密数据长度
			V_ucEncryptMode:三种数据加密方式:明文+MAC;密文;密文+MAC
输出参数：	pV_ucAPDU:		加密后的数据
			pV_usLen:		加密后的数据长度
			pV_uc_MAC:		MAC的数据
返回参数： 	应答正确:C_OK;		应答错误:C_Error;
调用位置：
备    注：	发送给ESAM的格式:	811C00P2(标识)+XX(P2)+XXXX(LC)+XX...XX(明文)
*******************************************************************************/
uchar8  S_Encrypt_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucEncryptMode, uchar8 *pV_ucMAC)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	ushort16	V_usReturnData16, V_usReceiveLen, V_usSendLen;

	PF_CopyDataBytes( (uchar8 * )TB_Encrypt_EncodedData_MAC_698, V_ucDataBuffer, CLen_TB_ESAM_4_698);
	V_ucDataBuffer[3] = V_ucEncryptMode;	/*P2*/

	PF_CopyDataBytes_698(pV_ucAPDU, &V_ucDataBuffer[CLen_TB_ESAM_4_698+CLen_LC_Len_698], *pV_usLen);	/*拷贝明文数据*/

	/********* 以下发送esam数据 *********************************************************/
	V_usSendLen = CLen_TB_ESAM_4_698 + CLen_LC_Len_698 + (*pV_usLen);

	PF_Ushort16ToBuffer2_698(&V_ucDataBuffer[4], pV_usLen);

	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_ESAMErr_DAR);
	}

	/*********以下为置返回参数 *********************************************************/
	*pV_usLen = V_usReceiveLen;
	if(V_ucEncryptMode == CodedData_698)
	{
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucAPDU, *pV_usLen);	/*应答APDU*/
	}
	else
	{
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucAPDU, V_usReceiveLen - 4);		/*应答APDU*/
		*pV_usLen -= 4;
		PF_CopyDataBytes_698(&V_ucDataBuffer[V_usReceiveLen - 4], pV_ucMAC, 4);	/*应答APDU*/
	}

	return(C_OK);
}

/*******************************************************************************
函数原型：	uchar8  S_Encrypt_698_terminal(uchar8 *pV_ucAPDU,ushort16 *pV_usLen,uchar8 V_ucEncryptMode,uchar8 *pV_ucMAC)
功能描述：	数据加密
输入参数：	 pV_ucAPDU:		需加密的APDU首地址
			pV_usLen:		需加密数据长度
			V_ucEncryptMode:三种数据加密方式:明文+MAC;密文;密文+MAC
输出参数：	pV_ucAPDU:		加密后的数据
			Len:		加密后的数据长度
			pV_uc_MAC:		MAC的数据
返回参数：	应答正确:C_OK;		应答错误:C_Error;
调用位置：
备    注：	发送给ESAM的格式:	811C00P2(标识)+XX(P2)+XXXX(LC)+XX...XX(明文)
*******************************************************************************/
uchar8  S_Encrypt_698_terminal(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucEncryptMode, uchar8 *pV_uc_MAC)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	ushort16	V_usReturnData16,V_usReceiveLen, V_usSendLen;
	ushort16	V_usOffset;
	ushort16	V_usLC, V_usLC1;

	if(V_ucEncryptMode == Plain_MAC)	/*明文+MAC*/
	{
		PF_CopyDataBytes( (uchar8 * )TB_Encrypt_EncodedData_Plain_MAC_698_terminal, V_ucDataBuffer, CLen_TB_ESAM_4_698);

		PF_CopyDataBytes_698(pV_ucAPDU, &V_ucDataBuffer[CLen_TB_ESAM_4_698 + CLen_LC_Len_698], *pV_usLen);	/*拷贝明文数据*/

		V_usOffset = CLen_TB_ESAM_4_698 + CLen_LC_Len_698 + (*pV_usLen);

		PF_CopyDataBytes((uchar8 * )TB_Encrypt_EncodedData_Plain_MAC_698_terminal_back, &V_ucDataBuffer[V_usOffset], CLen_TB_ESAM_4_698);
		V_usOffset += 4;

		V_usLC1 = *pV_usLen + 4;
		PF_Ushort16ToBuffer2_698( &V_ucDataBuffer[V_usOffset], &V_usLC1);
		V_usOffset += 2;

		V_usLC = *pV_usLen + 4 + 2;		/*LC长度*/
		V_usSendLen = V_usOffset;	/*赋值发送数据长度*/

	}
	else if(V_ucEncryptMode == Secret)/*密文*/
	{
		PF_CopyDataBytes((uchar8 * )TB_Encrypt_EncodedData_698_terminal, V_ucDataBuffer, CLen_TB_ESAM_4_698);
		PF_CopyDataBytes_698(pV_ucAPDU, &V_ucDataBuffer[CLen_TB_ESAM_4_698 + CLen_LC_Len_698], *pV_usLen);	/*拷贝明文数据*/

		V_usLC = *pV_usLen;
		V_usSendLen = CLen_TB_ESAM_4_698 + CLen_LC_Len_698 + (*pV_usLen);

	}
	else if(V_ucEncryptMode == Secret_MAC)	/*密文+SID_MAC*/
	{
		PF_CopyDataBytes((uchar8 * )TB_Encrypt_EncodedData_MAC_698_terminal, V_ucDataBuffer, CLen_TB_ESAM_4_698);

		PF_CopyDataBytes_698(pV_ucAPDU, &V_ucDataBuffer[CLen_TB_ESAM_4_698 + CLen_LC_Len_698], *pV_usLen);		/*拷贝明文数据*/

		V_usOffset = CLen_TB_ESAM_4_698 + CLen_LC_Len_698 + (*pV_usLen);

		PF_CopyDataBytes((uchar8 * )TB_Encrypt_EncodedData_MAC_698_terminal_back, &V_ucDataBuffer[V_usOffset], CLen_TB_ESAM_4_698);
		V_usOffset += 4;

		V_usLC1 = *pV_usLen + 3;	/*LC1长度计算明文数据+3后补齐16字节的整数倍+4*/
		V_usLC1 += (16 - (V_usLC1%16) ) + 4;	/*esam更新否则加密出来密文长度少6个字节*/

		PF_Ushort16ToBuffer2_698( &V_ucDataBuffer[V_usOffset], &V_usLC1);
		V_usOffset += 2;

		V_usLC = *pV_usLen + 4 + 2;	/*LC长度计算*/


		V_usSendLen = V_usOffset;	/*赋值发送数据长度*/
	}
	else
	{
		return(C_OtherErr_DAR);
	}


	PF_Ushort16ToBuffer2_698(&V_ucDataBuffer[4],&V_usLC);

	/********* 以下发送esam数据 *********************************************************/
	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 !=C_Security_CommandOk)
	{
		return(C_ESAMErr_DAR);
	}

	/*********以下为置返回参数 *********************************************************/
	*pV_usLen = V_usReceiveLen;
	if(V_ucEncryptMode == CodedData_698)
	{
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucAPDU, *pV_usLen);		/*应答APDU*/
	}
	else
	{
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucAPDU, V_usReceiveLen - 4);	/*应答APDU*/
		*pV_usLen -= 4;
		PF_CopyDataBytes_698(&V_ucDataBuffer[V_usReceiveLen - 4], pV_uc_MAC, 4);		/*应答APDU*/
	}

	return(C_OK);
}

/*******************************************************************************
函数原型：	uchar8 S_Encrypt_RN_MAC_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucEncryptMode, uchar8 *pV_ucRN_Data, uchar8 *pV_ucMAC_Data)
功能描述：	数据加密(主动上报)
输入参数： 	pV_ucAPDU:		需加密的APDU首地址
			pV_usLen:		需加密数据长度
			V_ucEncryptMode:三种数据加密方式:明文+MAC;密文;密文+MAC
输出参数：	pV_ucAPDU:		加密后的数据
			pV_usLen:		加密后的数据长度
返回参数：	应答正确:C_OK;		应答错误:C_Error;
调用位置：
备    注：
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
函数原型：	uchar8 S_Encrypt_MAC_698(uchar8 *pV_ucAPDU,ushort16 *Len,uchar8 V_ucEncryptMode,uchar8 *pV_ucRN_Data,uchar8 *pV_ucMAC_Data)
功能描述：	数据加密(主动上报)
输入参数：	 pV_ucAPDU:		需加密的APDU首地址
			pV_usLen:		需加密数据长度
			V_ucEncryptMode:三种数据加密方式:明文+MAC;密文;密文+MAC
输出参数：	pV_ucAPDU:		加密后的数据
			Len:		加密后的数据长度
返回参数：	应答正确:C_OK;		应答错误:C_Error;
调用位置：
备    注：
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
函数原型：	ushort16	S_InitMoney_698(uchar8 *pV_ucData,ushort16 *pV_usLen)
功能描述：	远程初始化钱包安全模块接口函数
输入参数：	*pV_ucData				:远程初始化钱包文件的数据:格式4字节预置金额+SID_MAC(数据长度不固定)
			pV_usLen				:数据长度
输出参数：	无
返回参数：	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
调用位置：
备    注：	数据结构 预置金额+SID_MAC
			通信发送的数据格式: 	XXXXXXXX(预置金额)+XXXXXXXX(标识)+xx(附加数据长度)+XX...XX(附加数据)+xx(MAC长度)+XX...XX(MAC)
			02 (结构体)
			02
			06
			00 00 30 39 (预置金额)
			5E （SID-MAC）
			81 3E 00 00 (标识)
			03
			00 09 10 （附加数据）
			04
			64 5B 4C 97 （MAC）
			发送给ESAM的格式:		XXXXXXXX(标识)+XX...XX(附加数据)+XXXXXXXX(预置金额)+XX...XX(MAC)
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

	/*预置金额*/
	V_ucMoneyOffset = 3;
	V_ucMoneyLen = C_PreSetMoney_len_698;
	PF_OneDataReversed(pV_ucData + V_ucMoneyOffset, (uchar8 *)&(MoneyClient_Table.V_ulMoney), V_ucMoneyLen);

	if(MoneyClient_Table.V_ulMoney > C_MoneyLimit)
	{
		return C_RechargeHoarding_DAR;
	}

	/*判断是否处于私钥状态*/
	if(InF_JudgeKeyStatus() == C_StateOfOfficialKey)
	{
		return(C_OtherErr_DAR);
	}

	/*(标识)*/
	V_ucSIDOffset = 3 + V_ucMoneyLen + C_len_698;
	V_ucSIDLen = C_DataID_Length_698;

	/*附件信息*/
	V_ucAttachDataLen = pV_ucData[V_ucSIDOffset + V_ucSIDLen];
	V_ucAttachDataOffset = V_ucSIDOffset + V_ucSIDLen + C_len_698;

	/*MAC*/
	V_ucMACLen = pV_ucData[V_ucAttachDataOffset + V_ucAttachDataLen];
	V_ucMACOffset = V_ucAttachDataOffset + V_ucAttachDataLen + C_len_698;

	/*赋值数据*/
	/*标识*/
	PF_CopyDataBytes(pV_ucData + V_ucSIDOffset, V_ucDataBuffer, V_ucSIDLen);

	/*附加数据*/
	PF_CopyDataBytes(pV_ucData + V_ucAttachDataOffset, V_ucDataBuffer + C_DataID_Length_698, V_ucAttachDataLen);/*附加数据*/

	/*预置金额*/
	PF_CopyDataBytes(pV_ucData + V_ucMoneyOffset, V_ucDataBuffer + C_DataID_Length_698 + V_ucAttachDataLen, V_ucMoneyLen);

	/*MAC*/
	PF_CopyDataBytes(pV_ucData + V_ucMACOffset, V_ucDataBuffer + C_DataID_Length_698+V_ucAttachDataLen + C_PreSetMoney_len_698, V_ucMACLen);

	/*计算发送数据长度*/
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


	/*********以下为置返回参数 *********************************************************/
	*pV_usLen = V_usReceiveLen;
	PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucData, *pV_usLen);	/*应答APDU*/

	return(C_OK);
}

/*******************************************************************************
函数原型：	ushort16  S_DataExcerption_698(uchar8 *pV_ucData,ushort16 *pV_ucLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen)
功能描述：	读取ESAM文件(数据回抄)
输入参数：	*pV_ucData:				回抄标识，固定8字节
			*pV_ucLen				开辟的缓冲区的长度
输出参数：	*pV_ucDataOutBuf:		回抄数据(回抄标识8+回抄数据Ld+Mac 4
			*pV_usDataOutLen		返回数据实际长度
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：	函数备注	调用前保证p_Data指向数据固定8字节
			通信发送的数据格式: 	XXXXXXXX(标识)+xx(附加数据长度)+XX...XX(附加数据)
			发送给ESAM的格式:		XXXXXXXX(标识)+XX...XX(附加数据)
*******************************************************************************/
ushort16  S_DataExcerption_698(uchar8 *pV_ucData, ushort16 *pV_usLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	uchar8		V_ucAttachDataLen,V_ucAttachDataOffset;
	ushort16	V_usSendLen,V_usReceiveLen;
	ushort16	V_usReturnData16,V_usDataOff;

	/*标识*/
	PF_CopyDataBytes(&pV_ucData[C_len_698], V_ucDataBuffer, C_DataID_Length_698);

	/*附加数据*/
	V_ucAttachDataLen = *( pV_ucData + C_len_698 + C_DataID_Length_698);	/*附加数据长度*/
	V_ucAttachDataOffset = C_DataID_Length_698 + C_len_698 + C_len_698;
	PF_CopyDataBytes(pV_ucData + V_ucAttachDataOffset, V_ucDataBuffer + C_DataID_Length_698, V_ucAttachDataLen);	/*附加数据*/


	/*计算发送数据长度*/
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

/*********以下为置返回参数 *********************************************************/
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

	PF_CopyDataBytes_698(V_ucDataBuffer, &pV_ucDataOutBuf[V_usDataOff], V_usReceiveLen);	/*应答APDU*/
	V_usDataOff += V_usReceiveLen;

	*pV_usDataOutLen = V_usDataOff;

	return(C_OK);
}

/*******************************************************************************
函数原型：	ushort16  S_WritePara_PlainTextMAC_698(uchar8 *pV_ucData, ushort16 *pV_usLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen)
功能描述：	1类参数Mac验证及ESAM对应参数写
输入参数：	*pV_ucData:	输入参数(数据更新信息+参数内容D1+SID_MAC) 注:数据长度不固定
			pV_usLen		输入数据的长度(包括Mac)
			--------------------------------
			设置表号
			0D
			40 02 02 00 08 00 00 00 00 00 00 00 00
			04
			80 2A 00 01
			06
			00 15 40 01 00 00
			04
			63 2A 1E A3
			00
			设置互感器变比
			08
			40 1C 02 00 03 00 00 10
			04
			81 2A 00 04
			05
			00 0A 40 00 18
			04
			BC 70 41 33
			00
输出参数：	pV_ucDataOutBuf：输出数据
			pV_usDataOutLen：输出数据长度
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：	P_Data缓冲区中的数据时不会变的。
			通信发送的数据格式: 	xx(参数长度)+XX...XX(参数内容)+XXXXXXXX(标识)+xx(附加数据长度)+XX...XX(附加数据)+xx(MAC长度)+XX...XX(MAC)
			发送给ESAM的格式:		XXXXXXXX(标识)+XX...XX(附加数据)+XX...XX(参数内容)+XX...XX(MAC)
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

	/*偏移和长度*/
	/*参数*/
	if(pV_ucData[0] & 0x80)
	{
		if( (pV_ucData[0] & 0x7F) == 2)
		{
			V_ucParaOffset = 3;
			V_usParaLen = PF_Buffer2ToLong16_698(&pV_ucData[V_ucParaOffset - 2]);
		}
		else	/*费率表参数*/
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
	/*本地表才允许设置费率和阶梯表*/
	if(C_Meter_Type != C_L_SmartMeter)
	{
		switch(V_ulOID &0xFFFFFF00)
		{
				case		0x401e0200:				/*报警金额*/
				case		CChange_Rate:			/*两套费率电价切换时间*/
				case		CChange_Ladder:			/*两套阶梯电价切换时间*/
				case		CCurrent_RateFF_Price:	/*当前套费率表*/
				case		CBackUp_RateFF_Price:	/*备用套费率表*/
				case		CCurrent_Ladder_Table: 	/*当前套阶梯表*/
				case		CBackUp_Ladder_Table: 	/*备用套阶梯表*/
					return(C_ObjectNotExist_DAR);
				default:
					break;					/*注意这里是break，到下一步判断*/
		}
	}
	if(InF_JudgeKeyStatus() == C_StateOfOfficialKey)	/*私钥下不允许设置表号、客户编号*/
	{
		if( (V_ulOID == CCustomer_Num) || (V_ulOID == CMeter_Num) )
		{
			return(C_RWForbid_DAR);
		}
	}
	#endif

	if( (V_ucOID[0] == 0x40) && (V_ucOID[1] == 0x02) )		/*设置表号*/
	{
		/*参数*/
		V_ucParaOffset = C_len_698;
		V_usParaLen = pV_ucData[V_ucParaOffset - C_len_698];
		/*SID长度及偏移*/
		V_ucSIDOffset = C_len_698 + V_usParaLen + V_ucParaOffset;
		V_ucSIDLen = pV_ucData[V_usParaLen + V_ucParaOffset];
		/*附件信息*/
		V_ucAttachDataLen = pV_ucData[V_ucSIDLen + V_ucSIDOffset];
		V_ucAttachDataOffset = C_len_698 + V_ucSIDOffset + V_ucSIDLen;
		/*MAC*/
		V_ucMACLen = pV_ucData[V_ucAttachDataOffset + V_ucAttachDataLen];
		V_ucMACOffset = C_len_698 + V_ucAttachDataOffset + V_ucAttachDataLen;
	}
	else
	{
		/*参数*/
		V_ucParaOffset += 5;
		V_usParaLen = pV_ucData[V_ucParaOffset - C_len_698];
		/*SID长度及偏移*/
		V_ucSIDOffset = C_len_698 + V_usParaLen + V_ucParaOffset;
		V_ucSIDLen = pV_ucData[V_usParaLen + V_ucParaOffset];
		/*附件信息*/
		V_ucAttachDataLen = pV_ucData[V_ucSIDLen + V_ucSIDOffset];
		V_ucAttachDataOffset = C_len_698 + V_ucSIDOffset + V_ucSIDLen;
		/*MAC*/
		V_ucMACLen = pV_ucData[V_ucAttachDataOffset + V_ucAttachDataLen];
		V_ucMACOffset = C_len_698 + V_ucAttachDataOffset + V_ucAttachDataLen;
	}
	/*标识*/
	PF_CopyDataBytes(pV_ucData + V_ucSIDOffset, V_ucDataBuffer, V_ucSIDLen);
	/*附加数据*/
	PF_CopyDataBytes(pV_ucData + V_ucAttachDataOffset, V_ucDataBuffer + V_ucSIDLen, V_ucAttachDataLen);	/*附加数据*/
	/*数据*/
	PF_CopyDataBytes_698(pV_ucData + V_ucParaOffset, V_ucDataBuffer + V_ucSIDLen + V_ucAttachDataLen, V_usParaLen);	/*附加数据*/
	/*MAC*/
	PF_CopyDataBytes(pV_ucData + V_ucMACOffset, V_ucDataBuffer + V_ucSIDLen + V_ucAttachDataLen + V_usParaLen, V_ucMACLen);

	/*计算发送数据长度*/
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



	/*********以下写运行信息文件*********************************************************/

	/*首先查表确定在表格TB_ParmPlainText中偏移,找不到其他错误退出*/
	if(LookForStr_ParmPlainText(V_ulOID,&V_ucParmPlainText_O) == C_OK)
	{
		V_ucOffsetInOP = TB_ParmPlainText[V_ucParmPlainText_O].OffsetInOP;
		/*如果需要写运行文件，则写运行文件*/
		if(V_ucOffsetInOP != C_Invalid_Offset)
		{
			if(V_ulOID == CMeter_Num)
			{
				DataLen = V_usParaLen - 5 - 2;
				PF_CopyDataBytes_698(pV_ucData + V_ucParaOffset + 5 + 2, V_ucbuf, DataLen);	/*运行信息文件表号长度6字节，偏移2字节，去掉最高位*/
			}
			else
			{
				DataLen = V_usParaLen;
				PF_CopyDataBytes_698(pV_ucData + V_ucParaOffset, V_ucbuf, DataLen);	/*数据*/
			}
			V_ucReturnData = WriteBinFile(C_ESAM, V_ucbuf, C_F_OpInfo, V_ucOffsetInOP, DataLen);
			if(V_ucReturnData != C_OK)
			{
				return(C_SERR_OtherErr);
			}
		}
	}


	/*********以下为置返回参数 *********************************************************/
	if(V_ulOID == CMeter_Num)	/*表号特殊*/
	{
		*pV_usDataOutLen = V_usParaLen - 5;
		PF_OneDataReversed(pV_ucData + V_ucParaOffset + 5, pV_ucDataOutBuf, *pV_usDataOutLen);
	}
	else if(V_ulOID == CCustomer_Num) 	/*客户编号*/
	{
		*pV_usDataOutLen = V_usParaLen;
		PF_OneDataReversed(pV_ucData + V_ucParaOffset, pV_ucDataOutBuf, *pV_usDataOutLen);
	}
	else if( (V_ulOID == CRatio_Curr_Tran) || (V_ulOID == CRatio_Vol_Tran) )	/*互感器变比*/
	{
		/*3字节BCD转4字节的hex*/
		*pV_usDataOutLen = 4;

		PF_OneDataReversed(pV_ucData + V_ucParaOffset, pV_ucDataOutBuf, V_usParaLen);
		PF_BCDtoHexBytes(pV_ucDataOutBuf, &V_ulDataTemp, V_usParaLen);
		PF_Ulong32ToBuffer4(pV_ucDataOutBuf, &V_ulDataTemp, 4);

	}
	else if(V_ulOID == CAlam_Money) 	/*报警金额集合*/
	{
		/*4字节BCD转4字节hex（2次）*/
		*pV_usDataOutLen = 8;

		PF_OneDataReversed(pV_ucData + V_ucParaOffset, pV_ucDataOutBuf, 4);
		PF_BCDtoHexBytes(pV_ucDataOutBuf, &V_ulDataTemp, 4);
		PF_Ulong32ToBuffer4(pV_ucDataOutBuf, &V_ulDataTemp, 4);

		PF_OneDataReversed(pV_ucData + V_ucParaOffset + 4, pV_ucDataOutBuf + 4, 4);
		PF_BCDtoHexBytes(pV_ucDataOutBuf + 4, &V_ulDataTemp, 4);
		PF_Ulong32ToBuffer4(pV_ucDataOutBuf + 4, &V_ulDataTemp, 4);

	}
	else if( (V_ulOID == CChange_Rate) || (V_ulOID == CChange_Ladder) )		/*切换时间*/
	{
		*pV_usDataOutLen = 7;

		memcpy(&V_ucTime[1], pV_ucData + V_ucParaOffset, 5);

		if(PF_Is_Buf_AllFixedData(&V_ucTime[1],0x00,5) == C_OK)	/*全0*/
		{
			*pV_ucDataOutBuf = 0xFF;	/*秒默认FF*/
			memset(pV_ucDataOutBuf + 1, 0x00, 6);
		}
		else if(PF_Is_Buf_AllFixedData(&V_ucTime[1],0xFF,5) == C_OK)	/*全FF*/
		{
			*pV_ucDataOutBuf = 0xFF;	/*秒默认FF*/
			memset(pV_ucDataOutBuf + 1, 0xFF, 6);
		}
		else if(PF_Is_Buf_AllFixedData(&V_ucTime[1],0x99,5) == C_OK)	/*全99*/
		{
			*pV_ucDataOutBuf = 0xFF;	/*秒默认FF*/
			memset(pV_ucDataOutBuf + 1, 0x63, 6);	/*99转换成0x63写到数据层*/
		}
		else	/*合法日期时间*/
		{
			/*5字节BCD大端转换成7字节data_time_s*/
			PF_OneDataReversed(pV_ucData + V_ucParaOffset, &V_ucTime[1], 5);
			V_ucTime[0] = 0xFF;	/*秒默认FF*/
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
	else if(V_ulOID == CBackUp_RateFF_Price)	/*备用套费率电价数据块*/
	{

		*pV_usDataOutLen = V_usParaLen;

		V_ucNum = V_usParaLen / 4;	/*设置了几个费率*/

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
	else if(V_ulOID == CBackUp_Ladder_Table)	/*备用套阶梯电价数据块（55字节）*/
	{

		*pV_usDataOutLen = V_usParaLen;

		V_ucNum = 6 + 7;	/*6个阶梯和7个阶梯电价*/
		for(i = 0; i < V_ucNum; i++)
		{
			PF_OneDataReversed(pV_ucData + V_ucParaOffset + 4 * i, pV_ucDataOutBuf + 4 * i, 4);
			PF_BCDtoHexBytes(pV_ucDataOutBuf + 4 * i, &V_ulDataTemp, 4);
			PF_Ulong32ToBuffer4(pV_ucDataOutBuf + 4 * i, &V_ulDataTemp, 4);
		}

		/*月、日、时转换成*/
		V_ucNum = 4;	/*4个结算日*/

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
	else	/*正常不会到这里面来*/
	{
		*pV_usDataOutLen = V_usReceiveLen;
		PF_CopyDataBytes_698(pV_ucDataOutBuf, pV_ucData, *pV_usDataOutLen);	/*应答APDU*/

	}


	return(C_OK);
}

/*******************************************************************************
函数原型：	ushort16  S_Key_Update_698(uchar8 *pV_ucData,ushort16 *pV_ucLen)
功能描述：	完成密钥更新，密钥状态另行刷新
输入参数：	pV_ucData:	输入数据首地址。格式(密文+SID_MAC) 长度不固定
输出参数：	pV_ucData：	输出数据
			pV_ucLen：	输出数据长度
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：	P_Data中数据无变化；判断标识码为812E0000
			通信发送的数据格式: 	xx(密钥密文长度)+XX...XX(密钥密文内容)+XXXXXXXX(标识)+xx(附加数据长度)+XX...XX(附加数据)+xx(MAC长度)+XX...XX(MAC)
			发送给ESAM的格式:		XXXXXXXX(标识)+XX...XX(附加数据)+XX...XX(参数内容)+XX...XX(MAC)
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

	/*偏移和长度*/
	/*参数*/
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
	/*SID长度及偏移*/
	V_usSIDOffset = C_len_698 + V_usParaLen + V_usParaOffset;
	V_usSIDLen = pV_ucData[V_usParaLen + V_usParaOffset];
	/*附件信息*/
	V_usAttachDataLen = pV_ucData[V_usSIDLen + V_usSIDOffset];
	V_usAttachDataOffset = C_len_698 + V_usSIDOffset + V_usSIDLen;
	/*MAC*/
	V_usMACLen = pV_ucData[V_usAttachDataOffset + V_usAttachDataLen];
	V_usMACOffset = C_len_698 + V_usAttachDataOffset + V_usAttachDataLen;

	/*拷贝数据*/
	/*标识*/
	PF_CopyDataBytes_698(pV_ucData + V_usSIDOffset, V_ucDataBuffer, V_usSIDLen);
	PF_CopyDataBytes_698(pV_ucData + V_usSIDOffset, (uchar8 *)&V_ulDataID, C_DataID_Length_698);

	if(V_ulDataID != 0x00002E81)	/*0x812E0000颠倒*/
	{
		return(C_OtherErr_DAR);
	}

	/*附加数据*/
	PF_CopyDataBytes_698(pV_ucData + V_usAttachDataOffset, V_ucDataBuffer + C_DataID_Length_698, V_usAttachDataLen);	/*附加数据*/
	/*参数*/
	PF_CopyDataBytes_698(pV_ucData + V_usParaOffset, V_ucDataBuffer + C_DataID_Length_698 + V_usAttachDataLen, V_usParaLen);
	/*MAC*/
	PF_CopyDataBytes_698(pV_ucData + V_usMACOffset, V_ucDataBuffer + C_DataID_Length_698 + V_usAttachDataLen + V_usParaLen, V_usMACLen);

	/*计算发送数据长度*/
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


	/*********以下为置返回参数 *********************************************************/
	*pV_usLen = V_usReceiveLen;
	PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucData, *pV_usLen);	/*应答APDU*/

	return(C_OK);
}



/*******************************************************************************
函数原型：	ushort16  S_IR_ID_Request(uchar8 *pV_ucData, ushort16 *pV_ucLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen, uchar8 V_ucClientAddr)
功能描述：	红外认证请求
输入参数：	pV_ucData:		输入数据首地址。格式(密文+SID_MAC) 长度不固定
			pV_usLen：输入数据长度
			V_ucClientAddr：终端地址还是主站地址
输出参数：	pV_ucDataOutBuf：输出数据
			pV_usDataOutLen：输出数据长度
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：	P_Data中数据无变化；判断标识码为812E0000
			通信发送的数据格式: 	RN(长度)+XX...XX(密钥密文内容)
			发送给ESAM的格式:		800808030010+表号+RN1
			返回:		0X10+ENDATA1+0X08+RN2
*******************************************************************************/
ushort16  S_IR_ID_Request(uchar8 *pV_ucData, ushort16 *pV_usLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen, uchar8 V_ucClientAddr)
{
	uchar8		V_ucDataBuffer[MaxLength_698], V_ucReturnData, V_ucbuf[16], V_ucoffset;
	ushort16	V_usReceiveLen, V_usReturnData16, V_usSendLen;
	uchar8 		V_ucAuthSessionLen;
	uchar8		V_ucMeterNo[8], V_ucEsamno[8], V_ucRN1Encode[16], V_ucRN2[16];
	uchar8		V_ucReturnData8;
	ushort16	V_usDataEnCode, V_usDataLen;

	if(V_ucClientAddr == Termal_Address)	/*终端身份认证*/
	{
		PF_CopyDataBytes((uchar8 * )TB_IR_ID_Request_698_Termal, V_ucDataBuffer, CLen_TB_ESAM_6_698);

		/*拷贝表号*/
		V_usDataLen = CLMeter_Num;
		V_ucReturnData = InF_Read_Data(CMeter_Num, &V_ucbuf[0], &V_usDataLen, &V_usDataEnCode);		/*读表号*/
		if(V_ucReturnData != C_OK)
		{
			return(C_OtherErr_DAR);
		}
		PF_OneDataReversed(&V_ucbuf[0], &V_ucMeterNo[0], CLMeter_Num);				/*读出来的表号需要颠倒使用*/


		/*拷贝RN*/
		V_ucAuthSessionLen = *(pV_ucData + 1);
		PF_CopyDataBytes(&pV_ucData[C_len_698 + 1], &V_ucDataBuffer[CLen_TB_ESAM_6_698 ], V_ucAuthSessionLen);
		/********* 以下发送esam数据 *********************************************************/
		V_usSendLen = CLen_TB_ESAM_6_698 + V_ucAuthSessionLen;		/*发送数据长度*/
	}
	else
	{
		PF_CopyDataBytes( (uchar8 * )TB_IR_ID_Request_698, V_ucDataBuffer, CLen_TB_ESAM_6_698);
		/*拷贝表号*/
		V_usDataLen = CLMeter_Num;
		V_ucReturnData = InF_Read_Data(CMeter_Num, &V_ucbuf[0], &V_usDataLen, &V_usDataEnCode);		/*读表号*/
		if(V_ucReturnData != C_OK)
		{
			return(C_OtherErr_DAR);
		}
		PF_OneDataReversed(&V_ucbuf[0], &V_ucMeterNo[0], CLMeter_Num);				/*读出来的表号需要颠倒使用*/
		PF_CopyDataBytes(&V_ucMeterNo[0], &V_ucDataBuffer[CLen_TB_ESAM_6_698], CLMeter_Num);

		/*拷贝RN*/
		V_ucAuthSessionLen = *(pV_ucData + 1);
		PF_CopyDataBytes(&pV_ucData[C_len_698 + 1], &V_ucDataBuffer[CLen_TB_ESAM_6_698 + CLMeter_Num], V_ucAuthSessionLen);

		/********* 以下发送esam数据 *********************************************************/
		V_usSendLen = CLen_TB_ESAM_6_698 + CLMeter_Num + V_ucAuthSessionLen;	/*发送数据长度*/
	}
	V_usReceiveLen = MaxLength_698;	/*接收数据最大长度*/
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SCErr_DAR);
	}
	if(V_usReceiveLen != (IRidRequestData1Len_698) )	/*返回8个字节密文*/
	{
		return(C_SCErr_DAR);
	}
	PF_CopyDataBytes(V_ucDataBuffer, &V_ucRN1Encode[0], IRidRequestData1Len_698);	/*应答APDU*/

	/********* 以下发送esam数据 *********************************************************/
	PF_CopyDataBytes((uchar8 * )TB_IR_ID_Request2_698, V_ucDataBuffer, CLen_TB_ESAM_6_698);
	V_usSendLen = CLen_TB_ESAM_6_698;	/*发送数据长度	*/
	V_usReceiveLen = MaxLength_698;		/*接收数据最大长度*/
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SCErr_DAR);
	}
	if(V_usReceiveLen != (IRidRequestData2Len_698) )	/*返回8个字节RN*/
	{
		return(C_SCErr_DAR);
	}
	PF_CopyDataBytes(V_ucDataBuffer, &V_ucRN2[0], IRidRequestData2Len_698);	/*应答APDU*/
	V_ucReturnData8 = S_ReadEsam_698(V_ucEsamno, &V_usReceiveLen, 0x0200);	/*读esam序列号*/
	if(V_ucReturnData8 != C_OK)
	{
		return(C_OtherErr_DAR);
	}

	/*********以下为置返回参数 *********************************************************/
	V_ucDataBuffer[0] = C_structure;
	V_ucDataBuffer[1] = 4;
	/*表号*/
	V_ucDataBuffer[2] = C_octet_string;
	V_ucDataBuffer[3] = CLMeter_Num;
	V_ucoffset = 4;
	PF_CopyDataBytes(&V_ucMeterNo[0], &V_ucDataBuffer[V_ucoffset] , CLMeter_Num);
	V_ucoffset += CLMeter_Num;
	/*esam序列号*/
	V_ucDataBuffer[V_ucoffset] = C_octet_string;
	V_ucoffset += 1;
	V_ucDataBuffer[V_ucoffset] = 8;
	V_ucoffset += 1;
	PF_CopyDataBytes(&V_ucEsamno[0], &V_ucDataBuffer[V_ucoffset], 8);
	V_ucoffset += 8;
	/*RN1密文*/
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
		return(C_DataLenError);		/*表示数据长度错*/
	}
	else
	{
		*pV_usDataOutLen = V_ucoffset;
		memcpy(pV_ucDataOutBuf, V_ucDataBuffer, *pV_usDataOutLen);
	}

	return(C_OK);
}

/*******************************************************************************
函数原型：	ushort16  S_IR_ID(uchar8 *pV_ucData,ushort16 *pV_ucLen)
功能描述：	红外认证
输入参数：	pV_ucData:	输入数据首地址。格式(密文+SID_MAC) 长度不固定
输出参数：	pV_usLen：	返回数据长度
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：	pV_ucData中数据无变化；判断标识码为812E0000
			通信发送的数据格式: 	RN(长度)+XX...XX(密钥密文内容)
			发送给ESAM的格式:		800808030010+表号+RN1
			返回:		0X10+ENDATA1+0X08+RN2
*******************************************************************************/
ushort16  S_IR_ID(uchar8 *pV_ucData, ushort16 *pV_usLen)
{
	uchar8		V_ucDataBuffer[MaxLength_698];
	ushort16	V_usReceiveLen, V_usReturnData16, V_usSendLen;
	uchar8		V_ucAuthSessionLen;

	PF_CopyDataBytes((uchar8 * )TB_IR_ID_698, V_ucDataBuffer, CLen_TB_ESAM_6_698);
	/*拷贝RN*/
	V_ucAuthSessionLen = *(pV_ucData + 1);
	PF_CopyDataBytes(&pV_ucData[C_len_698 + 1], &V_ucDataBuffer[CLen_TB_ESAM_6_698], V_ucAuthSessionLen);

	/********* 以下发送esam数据 *********************************************************/
	V_usSendLen = CLen_TB_ESAM_6_698 + V_ucAuthSessionLen;	/*发送数据长度*/
	V_usReceiveLen = MaxLength_698;		/*接收数据最大长度*/
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
函数原型：	ushort16	Comm_OpenChgBL_698()
功能描述：	远程开户、充值命令的解析
输入参数：	无
输出参数：	无
返回参数：	无
调用位置：
备    注：	在进入本函数之前，已判断200次挂起，身份认证有效权限
			本函数处理通信远程开户和充值2条命令的解析处理
*******************************************************************************/
ushort16	Comm_OpenChgBL_698()
{
	ulong32		V_ulChargeBal_Hex_Cent;			/*充值金额*/
	ulong32		V_ulPC_Num;						/*购电次数*/
	ushort16	V_usReturn16 = C_OK;

	/*判断是否处于私钥状态*/
	if(InF_JudgeKeyStatus() == C_StateOfTestKey)	/*不是全部处于私钥状态	*/
	{
		return C_OtherErr_DAR;
	}

	/*将购电次数和购电金额转换成32位16进制数*/
	V_ulChargeBal_Hex_Cent = MoneyClient_Table.V_ulMoney;
	V_ulPC_Num = MoneyClient_Table.V_ulBuyMoneyTime;

	/*判断是否已开户(远程或本地)*/
	if( (InF_DealWith_L_R_OAAFlag(C_Judge_Method_R, C_HaveOpenAnAccount) == C_HaveOpenAnAccount)
		|| (InF_DealWith_L_R_OAAFlag(C_Judge_Method_L, C_HaveOpenAnAccount) == C_HaveOpenAnAccount) )	/*远程或本地已开过户,比对客户编号是否一致*/
	{
		if(InF_Compare_CustomerNum(&MoneyClient_Table.V_ucClientNum[0]) != C_OK)
		{
			return C_CNMismatch_DAR;
		}
	}
	else	/*未开户*/
	{
		if(MoneyClient_Table.V_ucOpenFlag == 1)	/*未开户，进行远程充值，应答充值次数错(复旦微也是如此)*/
		{
			return C_RechargeNumErr_DAR;
		}
	}
	/*如果是开户命令，则购电次数只能是0或1*/
	if(MoneyClient_Table.V_ucOpenFlag == 0)
	{
		if(MoneyClient_Table.V_ulBuyMoneyTime > 1)	/*购电次数不等于0或1*/
		{
			return C_RechargeNumErr_DAR;
		}
	}

	/*判断购电次数和购电金额是否满足购电条件，
	只有在满足情况下才进行钱包充值动作*/
	V_usReturn16 = InF_Judge_ChgBal_PC_Num(V_ulChargeBal_Hex_Cent, V_ulPC_Num);
	MoneyClient_Table.V_CanRecharge = V_usReturn16;

	switch(V_usReturn16)
	{
		case		C_Can_EPurchase:			/*可以充值*/
			return C_OK;

		case		C_PC_Num_Equal:			/*购电次数相等*/
			if(MoneyClient_Table.V_ucOpenFlag == 0)	/*如果是开户命令，则不进行充值判断，直接退出*/
			{
				return C_OK;
			}
			else	/*其他为充值命令，应答重复充值*/
			{
				return C_ReRecharge_DAR;
			}

		case		C_MeterPC_Num_Large:		/*表内购电次数大*/
			return C_ReRecharge_DAR;

		case		C_SERR_RechargeNumErr:		/*充值次数错*/
			return C_RechargeNumErr_DAR;

		case		C_SERR_RechargeHoarding:		/*购电超囤积*/
			return C_RechargeHoarding_DAR;

		default:	/*远程充值，错了不进行显示提示。*/

			return C_OtherErr_DAR;

	}

}


/*******************************************************************************
函数原型：uchar8		DV_Return_Money_698(uchar8 *pV_ucReturnMoney)
功能描述：退费金额有效性判断
输入参数：*pV_ucReturnMoney				:接收到的数据帧
输出参数：
返回参数：C_OK/C_OtherErr
调用位置：
备    注：hex，并且必须小于钱包金额
*******************************************************************************/
uchar8		DV_Return_Money_698(uchar8 *pV_ucReturnMoney)
{
	uchar8		V_ucReturnData;
	uchar8		V_ucChargeBal_Hex_Cent[CLChargeBal_Hex_Cent];
	ushort16	V_usDataLen;
	ushort16	V_usdataCode;

	/*同步后，再读数据层剩余金额。因为同步中，可能会以ESAM为准，扣减数据层*/
	V_usDataLen = CLChargeBal_Hex_Cent;
	InF_GetData_ObjectManage(CChargeBal_Hex_Cent, V_ucChargeBal_Hex_Cent, &V_usDataLen, &V_usdataCode);
	/*比较*/
	V_ucReturnData = PF_Campare_Data(&pV_ucReturnMoney[0], V_ucChargeBal_Hex_Cent, CLChargeBal_Hex_Cent);
	if( (V_ucReturnData == C_GreaterThan) || (Is_Buf_AllZero(V_ucChargeBal_Hex_Cent, CLChargeBal_Hex_Cent) == C_OK) )	/*C_GreaterThan表示数组1大于数组2*/
	{
		return(C_OtherErr_DAR);
	}
	else
	{
		return(C_OK);
	}
}

/*******************************************************************************
函数原型：	ushort16	S_Purchase_ReturnFile_698(uchar8 *pV_ucData,ushort16 *pV_ucLen)
功能描述：	对ESAM钱包文件进行充值SID_MAC验证及充值操作，钱包退费
输入参数：	*pV_ucData		:充值报文。格式:钱包操作信息D1+表号
			pV_ucLen		:长度
输出参数：	C_OK/C_SERR_ESAM_VF
返回参数：
调用位置：
备    注：	pData的数据是不会变化的;通信判断是否需要进行钱包充值;
			充值标识:80420000 数据标识80420000(充值) 81440000(退费)
			02
			06
			0F （integer）
			00 0-开户 1-充值 2-退费
			06
			00 00 0B B8 （购电金额3000元）
			06
			00 00 00 64 （购电次数100次）
			09
			06
			00 00 00 00 00 01 （户号）
			5E （SID_MAC）
			81 42 00 00 (SID)
			03
			00 13 10 (附件数据)
			04
			55 B0 0C 0D （MAC）
			09 (OCTET STRING)
			08
			00 00 00 00 00 00 00 00 (表号)
			通信发送的数据格式: 	XX(操作类型)+XXXXXXXX(购电金额)+XXXXXXXX(购电次数)+XX(户号长度)+XX...XX(户号)+XXXXXXXX(标识)+xx(附加数据长度)+XX...XX(附加数据)+xx(MAC长度)+XX...XX(MAC)+xx(表号长度)+XX...XX(表号)
			发送给ESAM的格式:		XXXXXXXX(标识)+XX...XX(附加数据)+XX...XX(购电金额+购电次数+客户编号)+XX...XX(MAC)
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

	/*赋值开户标识*/
	MoneyClient_Table.V_ucOpenFlag = *(pV_ucData + 3);
	MoneyClient_Table.V_CanRecharge = 0;	/*不允许充值*/

	/*偏移和长度*/
	/*购电金额*/
	V_ucMoneyOffset = 5;
	V_ucMoneyLen = C_BuyMoney_len_698;
	PF_OneDataReversed(pV_ucData + V_ucMoneyOffset, (uchar8 *)&(MoneyClient_Table.V_ulMoney), V_ucMoneyLen);

	/*购电次数*/
	V_ucBuyNumOffset = V_ucMoneyOffset + C_BuyMoney_len_698 + C_len_698;
	V_ucBuyNumLen = C_BuyMoneyNum_len_698;
	PF_OneDataReversed(pV_ucData + V_ucBuyNumOffset, (uchar8 *)&(MoneyClient_Table.V_ulBuyMoneyTime), V_ucBuyNumLen);

	/*客户编号*/
	V_ucClientNumOffset = V_ucBuyNumOffset + V_ucBuyNumLen + 2;
	V_ucClientNumLen = C_ClientNum_len_698;
	PF_OneDataReversed(pV_ucData + V_ucClientNumOffset, (uchar8 *)&(MoneyClient_Table.V_ucClientNum), V_ucClientNumLen);

	/*开户充值操作，判断是否可以充值*/
	if( (MoneyClient_Table.V_ucOpenFlag == 0) || (MoneyClient_Table.V_ucOpenFlag == 1) )
	{
		V_usReturnData16 = Comm_OpenChgBL_698();
		if(V_usReturnData16 != C_OK)
		{
			return V_usReturnData16;	/*返回错误*/
		}
	}
	else if(MoneyClient_Table.V_ucOpenFlag == 2)	/*退费*/
	{
		V_usReturnData16 = DV_Return_Money_698( (uchar8 *)&MoneyClient_Table.V_ulMoney);
		if(V_usReturnData16 != C_OK)
		{
			return V_usReturnData16;	/*返回错误*/
		}
	}
	else
	{
		return(C_OtherErr_DAR);		/*返回其他错误*/
	}


	/*(标识)*/
	V_ucSIDOffset = V_ucClientNumOffset + C_ClientNum_len_698 + C_len_698;
	V_ucSIDLen = C_DataID_Length_698;
	/*附加数据*/
	V_ucAttachDataLen = pV_ucData[V_ucSIDOffset + V_ucSIDLen];
	V_ucAttachDataOffset = V_ucSIDOffset + V_ucSIDLen + C_len_698;
	/*MAC*/
	V_ucMACLen = pV_ucData[V_ucAttachDataOffset + V_ucAttachDataLen];
	V_ucMACOffset = V_ucAttachDataOffset + V_ucAttachDataLen + C_len_698;

	/*判断表号是否相等。*/
	if(InF_SC_Meter_Num_OK(pV_ucData + V_ucMACOffset + V_ucMACLen + 2) != C_OK)
	{
		return(C_OtherErr_DAR);	/*返回其他错误*/
	}

	/*拷贝数据*/
	/*标识*/
	PF_CopyDataBytes(pV_ucData + V_ucSIDOffset, V_ucDataBuffer, V_ucSIDLen);

	/*附加数据*/
	PF_CopyDataBytes(pV_ucData + V_ucAttachDataOffset, V_ucDataBuffer + V_ucSIDLen, V_ucAttachDataLen);	/*附加数据*/

	/*购电金额*/
	PF_CopyDataBytes(pV_ucData + V_ucMoneyOffset, V_ucDataBuffer + V_ucSIDLen + V_ucAttachDataLen, V_ucMoneyLen);


	/*购电次数*/
	PF_CopyDataBytes(pV_ucData + V_ucBuyNumOffset, V_ucDataBuffer + V_ucSIDLen + V_ucAttachDataLen + V_ucMoneyLen, V_ucBuyNumLen);

	/*客户编号*/
	PF_CopyDataBytes(pV_ucData + V_ucClientNumOffset, V_ucDataBuffer + V_ucSIDLen + V_ucAttachDataLen + V_ucMoneyLen + V_ucBuyNumLen, V_ucClientNumLen);

	/*MAC*/
	PF_CopyDataBytes(pV_ucData + V_ucMACOffset,V_ucDataBuffer + V_ucSIDLen + V_ucAttachDataLen + V_ucMoneyLen+V_ucBuyNumLen+V_ucClientNumLen, V_ucMACLen);


	/*计算发送数据长度*/
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

	/*********以下为置返回参数 *********************************************************/
	*pV_usLen = V_usReceiveLen;
	PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucData, *pV_usLen);	/*应答APDU*/

	if(MoneyClient_Table.V_ucOpenFlag == 0)
	{
		PF_OneDataReversed(&(MoneyClient_Table.V_ucClientNum[0]), V_ucTemp, CLCustomer_Num);
		/*写运行信息文件的客户编号*/
		WriteBinFile(C_ESAM, V_ucTemp, C_F_OpInfo, CF_O_CNumInOP, CLCustomer_Num);
	}

	return(C_OK);
}

/*******************************************************************************
函数原型：	ushort16  S_Action_Esam_698(uchar8 *pV_ucData,ushort16 *pV_ucLen)
功能描述：	esam的action操作
输入参数：	pV_ucData:		输入数据首地址。格式参数内容  octet-string，安全标识+SID长度不固定
			pV_usLen：输入数据长度

输出参数：	pV_ucData:		输出数据首地址。格式参数内容  octet-string，安全标识+SID长度不固定
			pV_usLen：输出数据长度
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：	会话时效门限
			通信发送的数据格式: 	xx(密钥密文长度)+XX...XX(密钥密文内容)+XX(sid长度04)+XXXXXXXX(标识)+xx(附加数据长度02)+XX...XX(附加数据)
			发送给ESAM的格式:		XXXXXXXX(标识)+XX...XX(附加数据)+XX...XX(参数内容)+XX...XX(MAC)
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

	/*偏移和长度*/
	/*参数*/
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

	/*SID长度及偏移*/
	V_usSIDOffset = C_len_698 + V_usParaLen + V_usParaOffset;
	V_usSIDLen = pV_ucData[V_usParaLen + V_usParaOffset];

	/*根据SID的第3字节P1来判断是什么参数设置*/
	GV_ESAMAction9_SIDP1P2 = pV_ucData[V_usSIDOffset + 2];


	/*附件信息*/
	V_usAttachDataLen = pV_ucData[V_usSIDLen + V_usSIDOffset];
	V_usAttachDataOffset = C_len_698 + V_usSIDOffset + V_usSIDLen;

	/*拷贝数据*/
	/*标识*/
	PF_CopyDataBytes_698(pV_ucData + V_usSIDOffset, V_ucDataBuffer, V_usSIDLen);
	PF_CopyDataBytes_698(pV_ucData + V_usSIDOffset, (uchar8 *)&V_ulDataID, C_DataID_Length_698);

	#if 0
	if(V_ulDataID != 0x00002E81)	/*0x812E0000颠倒*/
	{
		return(C_OtherErr_DAR);
	}
	#endif

	/*附加数据*/
	PF_CopyDataBytes_698(pV_ucData + V_usAttachDataOffset, V_ucDataBuffer + C_DataID_Length_698, V_usAttachDataLen);		/*附加数据*/
	/*参数*/
	PF_CopyDataBytes_698(pV_ucData + V_usParaOffset, V_ucDataBuffer + C_DataID_Length_698 + V_usAttachDataLen, V_usParaLen);

	/*计算发送数据长度*/
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


	/*********以下为置返回参数 *********************************************************/
	*pV_usLen = V_usReceiveLen;
	PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucData, *pV_usLen);		/*应答APDU*/

	return(C_OK);
}


/*******************************************************************************
函数原型：	uchar8	S_ReadEsam_698(uchar8 *pV_ucData, ushort16 *pV_usLen, ushort16 V_usItem)
功能描述：	读esam内部属性
输入参数：	V_usItem：属性DI1DI0
输出参数：	*pV_ucData			:返回数据
			pV_usLen：返回数据长度
返回参数：
调用位置：
备    注：
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
	else if(V_usItem == 0x00fe)		/*终端集合命令*/
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

	/*计算发送数据长度*/
	V_usSendLen = CLen_TB_ESAM_4_698 + 2;

	V_usReceiveLen = MaxLength_698;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_Error);
	}

	/*********以下为置返回参数 ******************************/
	if(*pV_usLen < C_EsamNatureToAction[i].V_ucLen)
	{
		return(C_DataLenError);
	}
	else
	{
		*pV_usLen = C_EsamNatureToAction[i].V_ucLen;
		PF_CopyDataBytes_698(&V_ucDataBuffer[C_EsamNatureToAction[i].V_ucOffset], pV_ucData, *pV_usLen); 	/*应答APDU*/
	}

#if 0
	/*********以下为置返回参数 ******************************/
    if( (Item == 6) || (Item == C_Remain_termal_Item) )		/*终端会话时效剩余时间*/
	{

		/*主站剩余会话时间特殊处理*/
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
		PF_CopyDataBytes_698(&V_ucDataBuffer[4], pV_ucData, *pV_ucLen);		/*应答APDU*/
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
		PF_CopyDataBytes_698(V_ucDataBuffer, pV_ucData, *pV_ucLen);	/*应答APDU*/
	}
#endif

	return(C_OK);
}


/*******************************************************************************
函数原型：	uchar8  INF_S_Encrypt_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucSecurityMode, uchar8 V_ucEncryptMode, uchar8 *pV_ucRN_Data, uchar8 *pV_ucMAC_Data, uchar8 V_ucClientAddr)
功能描述：	加密APDU
输入参数：	pV_ucAPDU:		需加密的APDU首地址
			pV_usLen:		需加密数据长度
			V_ucSecurityMode:四种数据验证模式:RN_698;RN_MAC_698;SID_698;SID_MAC_698
			V_ucEncryptMode:三种数据加密方式:明文+MAC;密文;密文+MAC;
			pV_ucRN_Data:	输入RN首地址(RN_698有效)
			V_ucClientAddr：	客户端地址
输出参数：	pV_ucAPDU:		加密后的APDU首地址(明文或密文数据)
			Len:		加密后(或者明文)数据长度
			pV_ucRN_Data:	返回数据RN首地址(RN_MAC_698有效)
			pV_ucMAC_Data	MAC数据返回首地址(明文+MAC;密文+MAC有效;RN_MAC_698有效)
返回参数：	应答成功:C_OK;
			应答错误分以下几种:
		    安全认证失败:C_SCErr_DAR;其它错误:C_Error;
调用位置：
备    注：	SecurityMode：	如果是RN_698模式，p_RN_Data输入有效；
							如果是RN_MAC_698模式，p_RN_Data、p_MAC_Data输出有效；
							如果是其它模式，p_RN_Data无效；
		 	p_APDU开buffer 512字节，p_RN_Data开20个字节，p_MAC_Data开4字节
		 	p_RN_Data、p_MAC_Data应答的是octet-string格式
*******************************************************************************/
uchar8  INF_S_Encrypt_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucSecurityMode, uchar8 V_ucEncryptMode, uchar8 *pV_ucRN_Data, uchar8 *pV_ucMAC_Data, uchar8 V_ucClientAddr)
{
	uchar8 V_ucReturnFlag;

	if(V_ucSecurityMode == RN_698)	/*RN 带随机数读加密*/
	{
		V_ucReturnFlag = S_Encrypt_RN_698(pV_ucAPDU, pV_usLen, V_ucEncryptMode, pV_ucRN_Data, pV_ucMAC_Data);
	}
	else if(V_ucSecurityMode == RN_MAC_698)	/*RN_MAC 主动上报加密*/
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
			V_ucReturnFlag = S_Encrypt_698_terminal(pV_ucAPDU, pV_usLen, V_ucEncryptMode, pV_ucMAC_Data);	/*终端加密	*/
		}
		else
		{
			V_ucReturnFlag = S_Encrypt_698(pV_ucAPDU, pV_usLen, V_ucEncryptMode, pV_ucMAC_Data);	/*主战加密*/
		}
	}

	return(V_ucReturnFlag);
}


/*******************************************************************************
函数原型：	uchar8  INF_S_ActionEsam_698(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen,uchar8 V_ucClientAddr)
功能描述：	操作ESAM
输入参数：	V_ulOAD:			action的OAD
			pV_ucDataBuf:		输入数据首地址
			pV_usDataLen:		输入数据长度
输出参数：	pV_ucDataOutBuf:	返回的数据首地址
			pV_usDataOutLen:	返回的数据长度
			V_ucClientAddr：	客户端地址
返回参数：	C_OK;
			应答错误分以下几种:
		    安全认证失败:C_SCErr_DAR;其它错误:C_Error;
调用位置：
备    注：
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
		case C_EsamAction_MoneyInit:	/*钱包初始化*/
			V_usReturnData16 = S_InitMoney_698(pV_ucDataBuf,pV_usDataLen);
			*pV_usDataOutLen = 0;
			break;
		case C_EsamAction_ReadData:		/*读ESAM文件,需要应答*/
			V_usReturnData16 = S_DataExcerption_698(pV_ucDataBuf, pV_usDataLen, pV_ucDataOutBuf, pV_usDataOutLen);
			break;
		case C_EsamAction_DataUpdate:	/*数据更新、需要返回数据*/
			V_usReturnData16 = S_WritePara_PlainTextMAC_698(pV_ucDataBuf, pV_usDataLen, pV_ucDataOutBuf, pV_usDataOutLen);
			break;
		case C_EsamAction_KetUpdate:	/*密钥更新*/
			V_usReturnData16 = S_Key_Update_698(pV_ucDataBuf, pV_usDataLen);
			*pV_usDataOutLen = 0;
			break;
		case C_EsamAction_MoneyAction:	/*钱包操作:开户、充值、退费*/
			/*进行esam操作前先进行钱包金额的同步*/
			V_usCodeData = CLChargeBal_Hex_Cent;
			if(InF_GetData_ObjectManage(CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, &V_usCodeData) == C_OK)
			{
				InF_S_UpdataChargeBalInESAM(V_ucbuf);
			}

			V_usReturnData16 = S_Purchase_ReturnFile_698(pV_ucDataBuf, pV_usDataLen);
			*pV_usDataOutLen = 0;
			break;
		case C_EsamAction_Auth_Time:	/*协商时效设置+终端地址+终端广播计数器+身份认证启用参数+*/
			V_usReturnData16 = S_Action_Esam_698(pV_ucDataBuf, pV_usDataLen);
			*pV_usDataOutLen = 0;
			break;
		case C_EsamAction_Unvalid:		/*协商失效,需要应答*/
			if(*pV_usDataOutLen < (CLDate_Time + 1) )
			{
				return(C_DataLenError); 	/*表示数据长度错*/
			}
			else
			{
				*pV_usDataOutLen = CLDate_Time;
				V_usReturnData16 = InF_Read_Data(CDate_Time, &pV_ucDataOutBuf[1], pV_usDataOutLen, &V_usDataEnCode);
				pV_ucDataOutBuf[0] = C_date_time_s;
				*pV_usDataOutLen += 1;
			}
			break;
		case C_EsamAction_IRRequest:	/*红外认证请求,需要应答*/
			V_usReturnData16 = S_IR_ID_Request(pV_ucDataBuf, pV_usDataLen,  pV_ucDataOutBuf, pV_usDataOutLen, V_ucClientAddr);
			break;
		case C_EsamAction_IRID:		/*红外认证*/
			V_usReturnData16 = S_IR_ID(pV_ucDataBuf, pV_usDataLen);
			/*红外定时器处理*/
			if(V_usReturnData16 != C_OK)
			{
				/****************红外认证失败结束红外认证有效***********************/
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
			else	/*正确，应答并赋值红外认证定时器	*/
			{
				V_usDataLen = CL_IRAuth_Timer;	/*数据长度4字节*/
				if(InF_Read_Data(C_IRAuth_Timer, V_ucbuf, &V_usDataLen, &V_usDataEnCode) != C_OK)
				{
					V_ucbuf[0] = C_IRAuthTime_L;		/*数据层读不出数据，则默认为30分钟*/
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
函数原型：	void DataReversed(ulong32 V_ulReversedMethod,uchar8 *pV_ucData,uchar8 V_ucR_ItemNum)
功能描述：	完成指定缓冲区的数据项的颠倒
输入参数：	V_ulReversedMethod:    	颠倒的方法，多数情况下以标识码宏代替
		 	pV_ucData:			需要颠倒数据的缓冲区首地址
		 	V_ucR_ItemNum:		需要颠倒的项目数
输出参数：	pV_ucData:颠倒后数据存放位置。和输入参数同
返回参数：
调用位置：
备    注：	这里颠倒前后字节总数是不变的。
			功能说明:
			1、根据ReversedMethod，如果是1项数据，则根据R_Len直接颠倒数据退出
			2、根据ReversedMethod，确认颠倒数据中分项数据表格首地址
			3、查表确定分项颠倒数据的长度，分项循环颠倒。循环长度为R_ItemNum
			4、颠倒结束，将数据copy到出口缓冲区退出
*******************************************************************************/
void DataReversed(ulong32 V_ulReversedMethod, uchar8 *pV_ucData, uchar8 V_ucR_ItemNum)
{
	uchar8	*pV_ucTB_DataReversed;		/*需颠倒数据缓冲区中每个数据项数据长度表*/
	uchar8	i;
	uchar8	*pV_ucSdata;
	uchar8	*pV_ucDdata;

	switch(V_ulReversedMethod)
	{
		case		CDI_Auth:				/*这里往下case，也可以建一张表，看到底多不多。*/
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

	/*开始循环颠倒*/
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
函数原型：	uchar8	ReadRecordFile(uchar8 * pV_ucData, uchar8 * pV_ucLen, uchar8 V_ucRecordNo)
功能描述：	完成钱包文件中记录项的读取
输入参数：	V_ucRecordNo:	读取的记录号及方法取值为:
							C_ChargeBal(金额)
							C_PurchasingE_Num(购电次数)
							C_Custormer_Num(客户编号)
输出参数：	*pV_ucData:	ESAM中记录文件的购电次数，剩余金额和客户编号
			*pV_ucLen:	返回最大长度
返回参数：	C_OK/C_Error
调用位置：
备    注：	函数返回的数据已经颠倒过!
*******************************************************************************/
uchar8	ReadRecordFile(uchar8 *pV_ucData, uchar8 * pV_ucLen, uchar8 V_ucRecordNo)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	ushort16	V_usDataLen;
	ushort16	V_usReturnData16;

	PF_CopyDataBytes( (uchar8 *)TB_ReadRecord_698, &V_ucbuf[0], CLen_TB_ReadRecord_698);					/*获取命令体*/
	V_usDataLen = CLen_S_BufMaxLen;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucbuf, CLen_TB_ReadRecord_698, V_ucbuf, &V_usDataLen);
	if( (V_usReturnData16 != C_Security_CommandOk) && ( (V_usReturnData16 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_Error);
	}

	/*拷贝数据*/
	if(V_ucRecordNo == C_ChargeBal_Mac)
	{
		if(*pV_ucLen < CLChargeBal_Hex_Cent)
		{
			return(C_DataLenError);
		}
		else
		{
			*pV_ucLen = CLChargeBal_Hex_Cent;
			PF_OneDataReversed(V_ucbuf, pV_ucData, CLChargeBal_Hex_Cent);	/*4字节购电金额		*/
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

			PF_OneDataReversed(V_ucbuf + CLChargeBal_Hex_Cent, pV_ucData, CL_PurchasingE_Num);	/*4字节购电次数	*/
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
			PF_OneDataReversed(V_ucbuf + CLChargeBal_Hex_Cent + CL_PurchasingE_Num, pV_ucData, CLCustomer_Num);	/*客户编号	*/
		}
	}
	else
	{
		return(C_Error);
	}


	return(C_OK);
}

/*******************************************************************************
函数原型：	ReadRecordFile_1(uchar8 * pV_ucData, uchar8 *pV_ucLen)
功能描述：	完成记录文件中记录项的读取(必须带Mac读)
输入参数：
输出参数：	*pV_ucData:		ESAM中记录文件的购电次数，剩余金额+mac
			pV_ucLen:		*pV_ucData实际长度

返回参数：	C_OK/C_Error
调用位置：
备    注：	函数备注	函数返回的数据已经颠倒过!
			函数备注	645对应远程交互命令状态查询专用
*******************************************************************************/
uchar8	ReadRecordFile_1(uchar8 * pV_ucData, uchar8 *pV_ucLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucReturnData;
	uchar8		V_ucResponseLen;
	ushort16	V_usDataLen1;
	ushort16	V_usReturnData16;
	ushort16	V_usDataEnCode, V_usDataLen;

	/*判断入口参数* pDataLen是否正确*/

	if(*pV_ucLen < (C_MacLen + CLChargeBal_Hex_Cent + CL_PurchasingE_Num + CLCustomer_Num + 4) )
	{

		return(C_Error);
	}
	V_ucResponseLen = C_MacLen + CLChargeBal_Hex_Cent + CL_PurchasingE_Num + CLCustomer_Num + 4;


	/*带Mac读记录文件，采用80 48 00 00 00 0d 48 + 00 00 +表号+4字节随机数。*/
	/*其中P1为记录号*/
	V_usDataLen = CLMeter_Num;
	PF_CopyDataBytes( (uchar8 *)TB_ReadRecord, &V_ucbuf[0], CLen_TB_ReadRecord);			/*获取命令体*/
	V_ucReturnData = InF_Read_Data(CMeter_Num, &V_ucbuf[C_O_MeterNum], &V_usDataLen, &V_usDataEnCode);			/*读表号*/
	if(V_ucReturnData != C_OK)
	{
		return(C_Error);
	}
	PF_OneDataReversed(&V_ucbuf[C_O_MeterNum], &V_ucbuf[C_O_MeterNum], CLMeter_Num);				/*读出来的表号需要颠倒使用*/
	PF_CopyDataBytes(SV_Rand1_4, &V_ucbuf[CLen_TB_ReadRecord + CLMeter_Num], 4);				/*取随机数，用于计算Mac*/
	V_usDataLen1 = CLen_S_BufMaxLen;
	V_usReturnData16 = INF_SendData_698_Esam(V_ucbuf, (CLen_TB_ReadRecord + CLMeter_Num + 4), V_ucbuf, &V_usDataLen1);
	if( (V_usReturnData16 != C_Security_CommandOk) && ( (V_usReturnData16 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_Error);
	}

	/*返回数据为0012+剩余金额+购电次数+客户编号+MAC	*/
	PF_CopyDataBytes(V_ucbuf, pV_ucData, V_ucResponseLen);

	/*分别颠倒*/
	PF_OneDataReversed(pV_ucData, pV_ucData, CLChargeBal_Hex_Cent);
	PF_OneDataReversed(&pV_ucData[CLChargeBal_Hex_Cent], &pV_ucData[CLChargeBal_Hex_Cent], C_BuyMoneyNum_len_698);
	PF_OneDataReversed(&pV_ucData[CLChargeBal_Hex_Cent + C_BuyMoneyNum_len_698], &pV_ucData[CLChargeBal_Hex_Cent + C_BuyMoneyNum_len_698], CLCustomer_Num);
	PF_OneDataReversed(&pV_ucData[CLChargeBal_Hex_Cent + C_BuyMoneyNum_len_698 + CLCustomer_Num], &pV_ucData[CLChargeBal_Hex_Cent+C_BuyMoneyNum_len_698 + CLCustomer_Num], C_MacLen);

	*pV_ucLen = CLChargeBal_Hex_Cent + C_BuyMoneyNum_len_698 + CLCustomer_Num + C_MacLen;

	return(C_OK);
}


/*******************************************************************************
函数原型：	ushort16	WriteRecordFile(uchar8 * pV_ucData, uchar8 V_ucLen)
功能描述：	写ESAM记录文件(钱包文件)
输入参数：	pV_ucData				:待写数据首地址
			V_ucLen				:待写数据的长度
输出参数：	无
返回参数：	C_OK/C_Error/C_SERR_ESAM_VF/C_SERR_OtherErr
调用位置：
备    注：	1、记录文件指的就是钱包文件
			2、数据符合ESAM大端模式。调用本函数时必须颠倒好!
			3、实际*pData固定成8字节的。
*******************************************************************************/
ushort16	WriteRecordFile(uchar8 * pV_ucData, uchar8 V_ucLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	ushort16	V_usDataLen;

	/*置7816指令*/
	PF_CopyDataBytes( (uchar8 * )TB_WriteRecord_698, V_ucbuf, CLen_TB_ESAM_Lc_698_Esam);
	if(V_ucLen != 8)
	{
		return(C_SERR_OtherErr);
	}
	PF_CopyDataBytes(pV_ucData, &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], V_ucLen);

	PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*操作之前保存命令头*/
	/*写ESAM*/
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
函数原型：	uchar8	ReadBinFileMac(uchar8 * pV_ucData, uchar8 *V_ucFileNo,uchar8 *V_ucParmOffset,uchar8 *V_ucParmLen)
功能描述：	带Mac 读取二进制文件中的一个参数。用于数据回抄。
输入参数：	V_ucFileNo:		读取的二进制文件短标识码。见宏定义
			V_ucParmOffset	读的参数偏移。见宏定义
			V_ucParmLen		需要读的参数长度。
输出参数：	*pV_ucData:		返回参数，其长度为读的数据长度+4字节Mac
返回参数：	C_OK/C_Error
调用位置：
备    注：	函数返回值没有颠倒过!和上面读记录文件不同!!
			缓冲区应该包含读的数据长度+4字节Mac长度
			采用表号作为分散因子。LC1=读取数据长度+4(Mac)+8(分散因子)
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

	/*组织命令帧并发送*/
	PF_CopyDataBytes( (uchar8 *)TB_ReadBinFile_Mac, V_ucbuf, CLen_TB_ReadBinFileMac);
	PF_CopyDataBytes(pV_ucFileNo, &V_ucbuf[C_O_P1], 2);

	PF_CopyDataBytes(SV_Rand1_4, &V_ucbuf[C_O_Rand4], 4);		/*取随机数，用于计算Mac*/
	PF_CopyDataBytes(pV_ucParmOffset, &V_ucbuf[C_O_P2BinFile], 2);	/*P2*/
	PF_CopyDataBytes(pV_ucParmLen, &V_ucbuf[C_O_lenBinFile], 2);		/*len*/

	PF_Buffer2ToUshort16(pV_ucParmLen, &V_usShort16Buufer);
	V_usShort16Buufer = V_usShort16Buufer + 4;
	PF_Ushort16ToBuffer2(&V_ucbuf[C_O_Lc2], &V_usShort16Buufer);	/*lc2=len+4*/
	/*表号*/
	V_usDataLen = CLMeter_Num;
	V_ucReturnData = InF_Read_Data(CMeter_Num, &V_ucbuf[C_O_MeterNumBinFile], &V_usDataLen, &V_usDataEnCode);	/*读表号*/
	if(V_ucReturnData != C_OK)
	{
		return(C_Error);
	}
	PF_OneDataReversed(&V_ucbuf[C_O_MeterNumBinFile], &V_ucbuf[C_O_MeterNumBinFile], CLMeter_Num);	/*读出来的表号需要颠倒使用*/
	/*发送数据	*/
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
函数原型：	uchar8	WriteBinFile(uchar8 V_ucCH,uchar8 * pV_ucData, uchar8 V_ucFileNo,uchar8 V_ucParmOffset,uchar8 V_ucParmLen)
功能描述：	不带Mac 写二进制文件中的一个参数
输入参数：	pV_ucData:		需要写的数据缓冲区
			V_ucFileNo:		二进制文件短标识码。见宏定义
			V_ucParmOffset	参数偏移。见宏定义
			V_ucParmLen		需要写的参数长度。
			V_ucCH			通道C_ESAM/C_Card
输出参数：	无
返回参数：	C_OK/C_Error
调用位置：
备    注：	入口参数已经符合ESAM的大端模式
			注:只符合写esam的返写信息文件(esam其它文件不支持写)，卡文件都不支持明文写
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
		V_ucbuf[0] = 0x80;			/*不带Mac写二进制文件*/
		V_ucbuf[1] = 0x2A;
		V_ucbuf[2] = 0x00;			/*FileNo为文件短标识码，采用方式1, 100x xxxx xxxxx为短标识码*/
		V_ucbuf[3] = 0x07;			/*P2*/
		V_ucbuf[4] = 0x00;			/*Lc*/
		V_ucbuf[5] = V_ucParmLen + 3;		/*Lc*/
		V_ucbuf[6] = 0x00;			/*Lc*/
		V_ucbuf[7] = 0x00;			/*Lc*/
		V_ucbuf[8] = V_ucParmOffset;	/*Lc*/

		PF_CopyDataBytes(pV_ucData, &V_ucbuf[9], V_ucParmLen);

		PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*暂存7816命令头*/

		V_ucDataLen = 9 + V_ucParmLen;

		V_usDataLen2 = CLen_S_BufMaxLen;


		GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucbuf, V_ucDataLen, V_ucbuf, &V_usDataLen2);
	}
	else	/*实际上不可能走到这个分支，因为不能明文下卡文件*/
	{
		V_ucbuf[0] = 0x00;					/*不带Mac写二进制文件*/
		V_ucbuf[1] = 0xD6;
		V_ucbuf[2] = 0x80 | V_ucFileNo;			/*FileNo为文件短标识码，采用方式1, 100x xxxx xxxxx为短标识码*/
	/*	V_ucbuf[2] = 0xC0 & V_ucbuf[2] ;*/
		V_ucbuf[3] = V_ucParmOffset;			/*P2*/
		V_ucbuf[4] = V_ucParmLen;				/*Lc*/

		PF_CopyDataBytes(pV_ucData, &V_ucbuf[5], V_ucParmLen);

		PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*暂存7816命令头*/

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
函数原型：	uchar8	WriteBinFileMac(uchar8 V_ucCH, uchar8 * pV_ucData, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, ushort16 V_ucParmLen)
功能描述：	带Mac 写二进制文件中的一个参数
输入参数：	pV_ucData:		需要写的数据缓冲区
			V_ucFileNo:		二进制文件短标识码。见宏定义
			V_ucParmOffset	参数偏移。见宏定义
			V_ucParmLen		需要写的参数长度。包含Mac长度
			V_ucCH			通道号，取值C_ESAM/C_Card
输出参数：	无
返回参数：	C_OK/C_IC_MAC_ERR/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR/C_Error
调用位置：
备    注：	入口参数已经符合ESAM的大端模式
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
		V_ucbuf[0] = 0x83;							/*不带Mac读二进制文件命令为00B0*/
		V_ucbuf[1] = 0x2a;
		V_ucbuf[2] = 0x80 | V_ucFileNo;					/*FileNo为文件短标识码，采用方式1, 100x xxxx xxxxx为短标识码*/
		V_ucbuf[3] = V_ucParmOffset;					/*P2*/
		V_ucbuf[4] = (uchar8)(V_usParmLen >> 8);		/*Lc*/
		V_ucbuf[5] = (uchar8)V_usParmLen;				/*Lc*/

		PF_CopyDataBytes_698(pV_ucData, &V_ucbuf[6], V_usParmLen);

		PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*7816命令头暂存*/

		V_usDataLen = CLen_TB_ESAM_Lc_698_Esam + V_usParmLen;

		V_usDataLen2 = CLen_S_BufMaxLen;


		GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucbuf, V_usDataLen, V_ucbuf, &V_usDataLen2);
		V_ucReturnData = C_IC_ESAM_RDWR_ERR;
	}
	else
	{
		V_ucbuf[0] = 0x04;					/*不带Mac读二进制文件命令为00B0*/
		V_ucbuf[1] = 0xD6;
		V_ucbuf[2] = 0x80 | V_ucFileNo;			/*FileNo为文件短标识码，采用方式1, 100x xxxx xxxxx为短标识码*/
		V_ucbuf[3] = V_ucParmOffset;			/*P2*/
		V_ucbuf[4] = (uchar8)V_usParmLen;		/*Lc*/

		PF_CopyDataBytes_698(pV_ucData, &V_ucbuf[5], V_usParmLen);

		PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*7816命令头暂存*/

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
函数原型：	uchar8	WriteBinFileMac_1(uchar8 V_ucCH,uchar8 * pV_ucData, uchar8 V_ucFileNo,uchar8 V_ucParmLen)
功能描述：	带Mac写二进制文件
输入参数：	V_ucCH			通道号，取值C_ESAM/C_Card
			pV_ucData:		需要写的数据缓冲区
			V_ucFileNo:		二进制文件短标识码。见宏定义
			V_ucParmLen		需要写的参数长度。包含Mac长度
输出参数：	无
返回参数：	C_OK/C_IC_MAC_ERR/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR/C_Error
调用位置：	645协议的远程控制命令、电量清零、事件/需量清零
备    注：	命令8012C08X+LC
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
	V_ucbuf[0] = 0x80;				/*不带Mac读二进制文件命令为00B0*/
	V_ucbuf[1] = 0x12;
	V_ucbuf[2] = 0xC0;
	V_ucbuf[3] = V_ucFileNo;			/*FileNo为文件短标识码，采用方式1, 100x xxxx xxxxx为短标识码*/
	V_ucbuf[4] = 0x00;				/*Lc*/
	V_ucbuf[5] = V_ucParmLen;

	PF_CopyDataBytes(pV_ucData, &V_ucbuf[6], V_ucParmLen);

	PF_OneDataReversed(V_ucbuf,GV_7816CMD.Header, CL_7816Header);		/*7816命令头暂存*/

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
函数原型：	uchar8	WriteBinFileMac_2(uchar8 V_ucCH, uchar8 * pV_ucData, uchar8 V_ucParmOffsetL, uchar8 V_ucParmOffsetH, uchar8 V_ucParmLen)
功能描述：	带Mac 写二进制文件
输入参数：	pV_ucData:		需要写的数据缓冲区
			V_ucParmOffsetL:		偏移地址低字节
			V_ucParmOffsetH	偏移地址高字节
			V_ucParmLen		需要写的参数长度。包含Mac长度
			V_ucCH			通道号，取值C_ESAM/C_Card
输出参数：	无
返回参数：	C_OK/C_IC_MAC_ERR/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR/C_Error
调用位置：	645协议的明文带mac写esam和645协议的密文带mac写esam
备    注：	入口参数已经符合ESAM的大端模式
			和函数WriteBinFileMac区别为：
			1、WriteBinFileMac采用方式一，即P1P2 = 1	0	0	5位短的文件标识码	8位文件的偏移量
			2、WriteBinFileMac_2采用方式二，即P1P2 = 0 15位偏移。写之前，必须先选择文件
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
	V_ucbuf[0] = 0x04;					/*不带Mac读二进制文件命令为00B0*/
	V_ucbuf[1] = 0xD6;
	V_ucbuf[2] = V_ucParmOffsetH;			/*FileNo为文件短标识码，采用方式1, 100x xxxx xxxxx为短标识码*/
	V_ucbuf[3] = V_ucParmOffsetL;			/*P2*/
	V_ucbuf[4] = V_ucParmLen;				/*Lc*/

	PF_CopyDataBytes(pV_ucData, &V_ucbuf[5], V_ucParmLen);

	PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*7816命令头暂存*/

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
函数原型：	void	InF_S_UpdataChargeBalInESAM(uchar8 *pV_ucChargeBal_Hex_Cent)
功能描述：	刷新ESAM中的剩余金额
输入参数：	*pV_ucChargeBal_Hex_Cent:	数据层存储的剩余金额(009002F9)，Hex，单位为分
								长度固定为4字节,小端
输出参数：	ESAM中的剩余金额和数据层同步
返回参数：	无
调用位置：	无
备    注：	20140820根据复旦微做法，修改如下:
			1、如果ESAM金额小于数据层剩余金额，对数据层进行退费操作。
			2、反之，对数据层进行负充值
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

	/*读取ESAM中的剩余金额*/
	V_ucDataLen = CLen_S_BufMaxLen;
	V_ucReturnData = ReadRecordFile(V_ucbuf, &V_ucDataLen, C_ChargeBal_Mac);
	if(V_ucReturnData != C_OK)
	{
		SV_SafeByte = 0x00;
		return;
	}
	PF_Buffer4ToUlong32(V_ucbuf, &V_ulChargeBal_ESAM, CLChargeBal_Hex_Cent);

	SV_SafeByte = SV_SafeByte | C_W_SafeFlag_2;

	/*比较ESAM中剩余金额和数据层的剩余金额。
	如果ESAM中的大于数据层，进行扣减
	反之，对数据层进行负充值。*/
	if(V_ulChargeBal_ESAM > V_ulChargeBal_DataLayer)	/*ESAM扣减*/
	{
		/*扣减命令80 46 00 00 00 04 +4字节扣减金额*/
		V_ucDataLen = CLen_S_BufMaxLen;
		/*获取命令头，调整长度*/
		PF_CopyDataBytes((uchar8 *)TB_Decrease_698, &V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam);		/*获取命令体*/
		V_ucSendDataLen = CLen_TB_ESAM_Lc_698_Esam;

		/*获取扣减金额，调整长度*/
		V_ulDecrease_ChargeBal = V_ulChargeBal_ESAM - V_ulChargeBal_DataLayer;							/*扣减的金额*/
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
	else if(V_ulChargeBal_ESAM < V_ulChargeBal_DataLayer)	/*负充值，以ESAM为准，写数据层。*/
	{
		SV_SafeByte = SV_SafeByte | C_W_SafeFlag_3;

		V_ulDecrease_ChargeBal = V_ulChargeBal_DataLayer - V_ulChargeBal_ESAM;

		InF_ReturnMoneyFromPurchase(V_ulDecrease_ChargeBal, SV_SafeByte);

		SV_SafeByte = 0;
	}
	else	/*相等，都不进行操作*/
	{
		SV_SafeByte = 0;
	}
}



/*******************************************************************************
函数原型：	void		Updata_ESAM_OpParm(uchar8	V_ucMsgNum)
功能描述：	刷新ESAM中运行参数
输入参数：	MsgNum:消息号，取值C_Msg_Communication/C_Msg_Card
输出参数：
返回参数：	无
调用位置：
备    注：	I类参数在更新时，直接刷新运行文件了，所以这里不管
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

	/*暂存运行文件*/
	InF_SC_RDBinFileNoMac(C_ESAM, C_F_OpInfo, CF_O_OPI_Start, CL_OPI, V_ucbuf1);
	PF_CopyDataBytes(V_ucbuf1, V_ucbuf2, CL_OPI);
	/*以下数据只有本地表才会有变化*/
	if(C_Meter_Type == C_L_SmartMeter)
	{
		/*读钱包文件中剩余金额*/
		V_ucDataLen = CL_Response_InIC;
		V_ucReturnData = ReadRecordFile(V_ucReponseBuf, &V_ucDataLen, C_ChargeBal_Mac);
		if(V_ucReturnData != C_OK)
		{
			return;
		}
		PF_OneDataReversed(V_ucReponseBuf, &V_ucbuf1[CF_O_OPI_ChBal_H_C], CLChargeBal_Hex_Cent);		/*读记录文件，数据时已符合小端这里改成大端	*/
		/*读钱包文件中购电次数*/
		V_ucDataLen = CL_Response_InIC;
		V_ucReturnData = ReadRecordFile(V_ucReponseBuf, &V_ucDataLen, C_PurchasingE_Num_Mac);
		if(V_ucReturnData != C_OK)
		{
			return;
		}
		PF_OneDataReversed(V_ucReponseBuf, &V_ucbuf1[CF_O_OPI_PEN], CL_PurchasingE_Num);		/*读记录文件，数据时已符合小端这里改成大端*/

		/*读透支金额	hex格式转换成BCD格式*/
		V_usDataLen = CLOverDraft_Hex_Cent;
		V_ucReturnData = InF_GetData_ObjectManage(COverDraft_Hex_Cent, V_ucReponseBuf, &V_usDataLen, &V_usCodeData);
		if(V_ucReturnData != C_OK)
		{
			return;
		}
		PF_Buffer4ToUlong32(V_ucReponseBuf, &V_ulhexData, CLOverDraft_Hex_Cent);
		V_ucDataLen = CLOverDraft_Hex_Cent;
		PF_HextoBCDBytes(&V_ulhexData, V_ucReponseBuf, &V_ucDataLen);
		PF_OneDataReversed(V_ucReponseBuf, &V_ucbuf1[CF_O_OPI_OD_B], CLOverDraft_BCD);	/*大端写esam*/

		/*读非法插卡次数*/
		V_usDataLen = CLLawlessC_Degree;
		InF_Read_Data(CLawlessC_Degree, V_ucReponseBuf, &V_usDataLen, &V_usCodeData);
		if(V_ucReturnData != C_OK)
		{
			return;
		}
		PF_OneDataReversed(V_ucReponseBuf, &V_ucbuf1[CF_O_OPI_LawLessIC], (CLLawlessC_Degree - 1) );
		/*读返写时间*/
		if(V_ucMsgNum == C_Msg_Card)
		{
			V_usDataLen = CL_Response_InIC;
			InF_Read_Data(CDate_Time, V_ucReponseBuf, &V_usDataLen, &V_usCodeData);
			PF_OneDataReversed(&V_ucReponseBuf[1], &V_ucbuf1[CF_O_OPI_RWRClock], (CLDate_Time - 1) );
		}
	}

	/*置固定值，算CS，16*/
	V_ucbuf1[CF_O_OPI_Start] = 0x68;
	V_ucbuf1[CF_O_OPI_CMD] = 0x11;
	V_ucbuf1[CF_O_OPI_Len] = 0x00;
	V_ucbuf1[CF_O_OPI_Len+1] = CL_OPI-6;		/*49-(68 11 00 2b cs 16)*/

	/*计算CS*/
	V_ucbuf1[CF_O_OPI_CS] = 0;
	for(i = 1; i < (CL_OPI - 2); i++)				/*去掉68 cs 16*/
	{
		V_ucbuf1[CF_O_OPI_CS] = V_ucbuf1[CF_O_OPI_CS] + V_ucbuf1[i];
	}
	V_ucbuf1[CF_O_OPI_End] = 0x16;

	/*比较文件前后是否相同，不同则刷新*/
	if(PF_Campare_Data(V_ucbuf1, V_ucbuf2, CL_OPI) != C_Equal)
	{
		WriteBinFile(C_ESAM, V_ucbuf1, C_F_OpInfo, CF_O_OPI_Start, CL_OPI);
	}
}


/*******************************************************************************
函数原型：	ushort16 InF_S_Authentication(uchar8 *pV_ucData, uchar8 *pV_ucLen)
功能描述：	身份认证接口函数
输入参数：	pV_ucData:     数据的起始指针（密文、随机数和分散因子）
			*pV_ucLen:   数据长度(固定成3*8=24 字节)
输出参数：	*P_DataPtr: 数据(随机数2、ESAM序列号、身份认证有效时长（该数据项不返回到主站）)
			*pV_ucLen:   返回数据长度(固定返回成4+8+2 = 14)
返回参数：	C_OK        表示成功
			其他表示错误: C_SERR_AF/  C_SERR_OtherErr

调用位置：
备    注：
*******************************************************************************/
ushort16 InF_S_Authentication(uchar8 *pV_ucData, uchar8 *pV_ucLen)
{
	uchar8 		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucReturnData;
	ushort16	V_usReturnData16, V_usDataLen16;
	ushort16	V_usDataEnCode;

	/*判断长度是否正确*/
	if(*pV_ucLen != C_Authentication_Len)
	{
		return(C_SERR_OtherErr);
	}

	/*读数据层表号，判断和收到的分散因子是否一致*/
	V_usDataLen16 = CLMeter_Num;
	V_ucReturnData = InF_Read_Data(CMeter_Num, &V_ucbuf[0], &V_usDataLen16, &V_usDataEnCode);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);		/*表号读不出*/
	}

	V_ucReturnData = PF_Campare_Data(&V_ucbuf[0], &pV_ucData[C_Auth_O_Dis_factor], CLMeter_Num_645); /*6字节*/
	if(V_ucReturnData != C_Equal)		/*分散因子高2位应该为0   前2字节不判*/
	{
		return(C_SERR_OtherErr);
	}

	/*对接收到报文进行颠倒，以备下面进行使用。*/
	DataReversed(CDI_Auth, pV_ucData, C_RItem_Len_Auth);

	SF_ColdReset_7816_Esam_No();

	InF_Clear698ConectTimer();

	/*表号分散得到临时密钥并对随机数R1进行加密，获取密文K2*/
	V_usDataLen16 = CLen_S_BufMaxLen;
	PF_CopyDataBytes((uchar8 *)TB_AuthDistributedkey_645, &V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam);
	PF_CopyDataBytes(&pV_ucData[C_Auth_O_Dis_factor], &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], CL_Auth_Dis_factor);		/*加入分散因子。有没有数据颠倒问题*/
	PF_CopyDataBytes(&pV_ucData[C_Auth_O_Rand1], &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam + CL_Auth_Dis_factor], CL_Auth_Rand1);	/*加入RAND1。有没有数据颠倒问题*/
	V_usReturnData16 = INF_SendData_698_Esam(&V_ucbuf[0], (CLen_TB_ESAM_Lc_698_Esam + CL_Auth_Dis_factor + CL_Auth_Rand1), &V_ucbuf[0], &V_usDataLen16);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SERR_AF);
	}

	/*比对收到的密文K1和随机数1加密后密文K2。相等身份认证通过!*/
	V_ucReturnData = PF_Campare_Data(&V_ucbuf[CLen_Respond_Auth], &pV_ucData[C_Auth_O_CiphertextK1], CL_Auth_CiphertextK1);
	if(V_ucReturnData != C_Equal)
	{
		return(C_SERR_AF);
	}

	/*********   以下为置返回参数 *********************************************************/
	/*获取随机数2，长度为4。用于返回主站。*/
	V_usDataLen16 = CLen_S_BufMaxLen;
	PF_CopyDataBytes((uchar8 *)TB_GetChallenge_645_Esam, &V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam);
	V_usReturnData16 = INF_SendData_698_Esam(&V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam, &V_ucbuf[0], &V_usDataLen16);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SERR_AF);
	}
	PF_CopyDataBytes(&V_ucbuf[CLen_Respond_Auth], pV_ucData, CLen_Rand2);
	*pV_ucLen = CLen_Rand2;

	/*获取ESAM序列号，长度为8。用于返回主站。*/
	V_usDataLen16 = CLen_S_BufMaxLen;
	PF_CopyDataBytes((uchar8 *)TB_RdESAMNo_645,&V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam);
	V_usReturnData16 = INF_SendData_698_Esam(&V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam, &V_ucbuf[0], &V_usDataLen16);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SERR_AF);
	}
	PF_CopyDataBytes(&V_ucbuf[CLen_Respond_Auth], &pV_ucData[CLen_Rand2], CLen_ESAMNo);
	*pV_ucLen = CLen_Rand2 + CLen_ESAMNo;



	/*获取身份认证有效时长。*/
	V_usDataLen16 = CLen_S_BufMaxLen;						/*身份认证有效时长的长度为4*/
	V_ucReturnData = S_ReadEsam_698(V_ucbuf, &V_usDataLen16, 0x0500);

	/*DataLen =  (uchar8)V_usDataLen16;*/
	PF_OneDataReversed(V_ucbuf, V_ucbuf, V_usDataLen16);
	PF_OneDataReversed(V_ucbuf, V_ucbuf, CLen_AuthPTime);

	if( (V_ucReturnData != C_OK ) || ( (V_ucbuf[0] == 0x00) && (V_ucbuf[1] == 0x00) ) )
	{
		V_ucbuf[1] = C_AuthPTime_LByte;
		V_ucbuf[0] = C_AuthPTime_HByte;				/*这里注意ESAM返回的是大端模式，后面要统一颠倒*/
	}
	PF_CopyDataBytes(&V_ucbuf[0], &pV_ucData[C_R_Auth_O_AuthPTime], CLen_AuthPTime);
	*pV_ucLen = *pV_ucLen + CLen_AuthPTime;

	/*响应数据需要颠倒成645格式!*/
	DataReversed(CDI_Auth_R, pV_ucData, C_RItem_Len_AuthR);

	return(C_OK);
}

/*******************************************************************************
函数原型：	ushort16  InF_S_Certification_Invaliad(uchar8 *pV_ucData,uchar8 *pV_ucLen)
功能描述：	完成身份认证失效操作。实际是组织应答帧
输入参数：	pV_ucData:		返回数据缓冲区
			*pV_ucLen:	缓冲区最大长度
输出参数：	*pV_ucData:	ESAM中6字节客户编号，4字节剩余金额，
			4字节购电次数，4字节密钥信息
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：
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
	/*如果是本地表，刷新ESAM中的剩余金额。
	但这里是不需要管表的类型。反正远程表读数据层剩余金额是读不出来的*/
 	V_ReturnData = InF_ReadEnergy_Protocol(CChargeBal_Hex_Cent, V_ucbuf, CLChargeBal_Hex_Cent);
 	if(V_ReturnData == C_OK)
	{
		InF_S_UpdataChargeBalInESAM(V_ucbuf);
	}							/*反正不成功，不刷新ESAM*/


#endif

	/*同步ESAM中剩余金额。15min闭锁*/
	UpdataChargeBalInESAMWithSwitch();

	/*读客户编号。
	读数据层*/
	V_usDataLen = CLCustomer_Num;
	V_ucReturnData = InF_Read_Data(CCustomer_Num, &V_ucbuf[C_AInvR_O_CustomerNo], &V_usDataLen, &V_usDataEnCode);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}

#if 0
	/*读ESAM 在参数信息文件中*/
	V_ReturnData = ReadBinFileNoMac(&V_ucbuf[C_AInvR_O_CustomerNo], C_F_ParmInf, CF_O_CNumInParm,CLCustomer_Num);
	if(V_ReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}
	PF_OneDataReversed(&V_ucbuf[C_AInvR_O_CustomerNo], &V_ucbuf[C_AInvR_O_CustomerNo], CLCustomer_Num);
#endif


	/*读剩余金额,读记录文件中已将数据颠倒*/
	V_ucDataLen = CLen_S_BufMaxLen - CLCustomer_Num;
	V_ucReturnData = ReadRecordFile(&V_ucbuf[C_AInvR_O_ChargeB_B], &V_ucDataLen, C_ChargeBal_Mac);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}

	/*读购电次数,读记录文件中已将数据颠倒*/
	V_ucDataLen = CLen_S_BufMaxLen - CLCustomer_Num - CLChargeBal_Hex_Cent;
	V_ucReturnData = ReadRecordFile(&V_ucbuf[C_AInvR_O_PE_Num], &V_ucDataLen, C_PurchasingE_Num_Mac);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}

#if 0
	/*读密钥状态，读数据层*/
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


	/*读密钥状态，读ESAM*/
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
函数原型：void	InF_S_PowerOn(void)
功能描述：安全模块上电初始化
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void	InF_S_PowerOn(void)
{
	SV_SafeByte = 0x00;
	SV_UpdateMInEsamTimer = 0;
}


/*******************************************************************************
函数原型：ushort16	InF_S_WriteCertificationTime(uchar8	*pV_ucData)
功能描述：完成身份认证时长设置
输入参数：P_Data:		输入数据首地址。固定2+4 字节；符合645的小端模式
输出参数：无
返回参数：C_OK/C_SERR_ESAM_VF/C_SERR_OtherErr
调用位置：无
备    注：无
*******************************************************************************/
ushort16	InF_S_WriteCertificationTime(uchar8	*pV_ucData)
{
	uchar8	V_ucReturnData;

	/*判断数据是否为合法*/
	V_ucReturnData = PF_Judge_BCD(CLen_AuthPTime, pV_ucData);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}

	/*将传递进来的数据进行颠倒*/
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
函数原型：	ushort16  InF_S_IRCertification_Request(uchar8 *pV_ucData,uchar8 *pV_ucLen,uchar8 V_ucBufMaxLen)
功能描述：	完成红外认证请求
输入参数：	pV_ucData:		输入数据首地址。
			*pV_ucLen:		输入*P_Data长度。实际固定8 字节
输出参数：	*pV_ucData:		输出参数内容。按照表号，序列号，K1，Rand2排列
			*pV_ucLen:		返回参数长度6+8+8+8
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：
*******************************************************************************/
ushort16  InF_S_IRCertification_Request(uchar8 *pV_ucData,uchar8 *pV_ucLen,uchar8 V_ucBufMaxLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucReturnData;
	ushort16	V_usReturnData16;
	uchar8		V_ucReponseBuf[CL_IRReq_Response+2];		/*响应数据，底层应该是不需要附加2字节SW，但这里增加2字节*/
	uchar8		V_ucReponseLen = 0;							/*响应数据长度临时缓存*/
	ushort16 	V_usDataLen16;
	ushort16	V_usDataEnCode;

	/*判断缓冲区是否小于应返回的数据长度*/
	if((V_ucBufMaxLen < CL_IRReq_Response) || (*pV_ucLen !=CL_Auth_Rand1) )
	{
		return(C_SERR_OtherErr);
	}

	/*读表号，作为应答数据第 1 项*/
	V_usDataLen16 = CLMeter_Num;
	V_ucReturnData = InF_Read_Data(CMeter_Num, &V_ucReponseBuf[C_RIRCReq_O_M_Num_645], &V_usDataLen16, &V_usDataEnCode);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}
	V_ucReponseLen = V_ucReponseLen + CLMeter_Num_645;

	/*读取ESAM序列号,作为应答数据的第2项*/
	V_usDataLen16 = CL_IRReq_Response - V_ucReponseLen;
	V_usReturnData16 = INF_SendData_698_Esam
				((uchar8 *)TB_RdESAMNo_645, CLen_TB_ESAM_Lc_698_Esam, &V_ucReponseBuf[C_RIRCReq_O_ESAMNo_645], &V_usDataLen16); /*2字节，698表号8字节，645表号6字节，*/
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SERR_OtherErr);
	}
	PF_OneDataReversed(&V_ucReponseBuf[C_RIRCReq_O_ESAMNo_645], &V_ucReponseBuf[C_RIRCReq_O_ESAMNo_645], CLen_ESAMNo);
	V_ucReponseLen = V_ucReponseLen + CLen_ESAMNo;
	/*取随机数1的加密后数据K1,作为应答数据的第3项。*/
	PF_CopyDataBytes((uchar8 *)TB_AuthDistributedkey_645, &V_ucbuf[0], CLen_TB_ESAM_Lc_698_Esam);		/*获取命令头*/
	PF_CopyDataBytes(&V_ucReponseBuf[C_RIRCReq_O_M_Num_645], &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], CLMeter_Num_645);	/*先取表号*/
	V_ucbuf[CLen_TB_ESAM_Lc_698_Esam + CLMeter_Num_645] = 0x00;
	V_ucbuf[CLen_TB_ESAM_Lc_698_Esam + CLMeter_Num_645+1] = 0x00;
	PF_OneDataReversed(&V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], (CLMeter_Num_645 + 2));	/*表号+0000颠倒后成分散因子*/
	PF_CopyDataBytes(pV_ucData,&V_ucbuf[CLen_TB_ESAM_Lc_698_Esam + CLMeter_Num_645 + 2], CL_Auth_Rand1);				/*取Rand1*/
	PF_OneDataReversed(&V_ucbuf[C_RIRCReq_O_RandK1_645], &V_ucbuf[C_RIRCReq_O_RandK1_645], CL_Auth_Rand1);				/*随机数1颠倒后使用*/
	V_usDataLen16 = CL_Auth_CiphertextK1;
	V_usReturnData16 = INF_SendData_698_Esam(&V_ucbuf[0], (CLen_TB_ESAM_Lc_698_Esam + CLMeter_Num_645 + 2 + CL_Auth_Rand1), &V_ucbuf[0], &V_usDataLen16);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SERR_OtherErr);
	}
	PF_CopyDataBytes(V_ucbuf,&V_ucReponseBuf[C_RIRCReq_O_RandK1_645], CL_Auth_CiphertextK1);	/*取K1*/
	PF_OneDataReversed(&V_ucReponseBuf[C_RIRCReq_O_RandK1_645], &V_ucReponseBuf[C_RIRCReq_O_RandK1_645], CL_Auth_CiphertextK1);
	V_ucReponseLen = V_ucReponseLen + CL_Auth_CiphertextK1;

	/*获取随机数2,Rand2,作为应答数据的第4项*/
	V_usDataLen16 = CLen_S_BufMaxLen;
	PF_CopyDataBytes((uchar8 *)TB_IR_ID_Request2_698, &V_ucbuf[0], CLen_TB_ESAM_Le_698_Esam);
	V_usReturnData16 = INF_SendData_698_Esam(&V_ucbuf[0], CLen_TB_ESAM_Le_698_Esam, &V_ucbuf[0], &V_usDataLen16);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SERR_OtherErr);
	}
	PF_OneDataReversed(&V_ucbuf[0], &V_ucReponseBuf[C_RIRCReq_O_Rand2_645], CL_RIRCReq_Rand2);
	V_ucReponseLen = V_ucReponseLen + CL_RIRCReq_Rand2;

	/*赋值出口参数*/
	PF_CopyDataBytes(V_ucReponseBuf, pV_ucData, V_ucReponseLen);
	*pV_ucLen = V_ucReponseLen;

	return(C_OK);

}


/*******************************************************************************
函数原型：	ushort16  InF_S_IRCertification_Instruction(uchar8 *pV_ucData)
功能描述：	完成红外认证
输入参数：	pV_ucData:		输入数据首地址 固定8 字节
输出参数：	无
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：
*******************************************************************************/
ushort16  InF_S_IRCertification_Instruction(uchar8 *pV_ucData)
{
	uchar8 V_ucDataBuffer[MaxLength_698];
	ushort16 V_usReceiveLen,V_usReturnData16,V_usSendLen;
	uchar8 V_ucAuthSessionLen;

	PF_CopyDataBytes((uchar8 * )TB_IR_ID_698, V_ucDataBuffer, CLen_TB_ESAM_6_698);
	/*拷贝RN*/
	V_ucAuthSessionLen = CL_Auth_CiphertextK2;
	PF_OneDataReversed(pV_ucData, &V_ucDataBuffer[CLen_TB_ESAM_6_698], V_ucAuthSessionLen);

	/********* 以下发送esam数据 *********************************************************/
	V_usSendLen =CLen_TB_ESAM_6_698 + V_ucAuthSessionLen;		/*发送数据长度*/
	V_usReceiveLen = MaxLength_698;		/*接收数据最大长度*/
	V_usReturnData16 = INF_SendData_698_Esam(V_ucDataBuffer, V_usSendLen, V_ucDataBuffer, &V_usReceiveLen);
	if(V_usReturnData16 != C_Security_CommandOk)
	{
		return(C_SCErr_DAR);
	}

	return(C_OK);
}


/*******************************************************************************
函数原型：	uchar8	JudgeS_Key_V_Mac_InP(uchar8 *pV_ucData, uchar8 V_ucDataLen, uchar8 *pV_ucMsgReupdataKey, uchar8 *pV_ucKeyNum)
功能描述：	完成密钥更新Mac验证中输入参数正确性的判断。
输入参数：	pV_ucData:				输入数据首地址。长度为V_ucKeyNum*36
			V_ucDataLen:			输入参数的长度。
			pV_ucMsgReupdataKey:	返回参数地址
			pV_ucKeyNum:			返回密钥条数地址
输出参数：	*pV_ucMsgReupdataKey:	返回是否需要重新更新的标志
			*pV_ucKeyNum:			返回密钥条目数(1-4)
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：
*******************************************************************************/
uchar8	JudgeS_Key_V_Mac_InP(uchar8 *pV_ucData, uchar8 V_ucDataLen, uchar8 *pV_ucMsgReupdataKey, uchar8 *pV_ucKeyNum)
{
	uchar8	i;
	uchar8	V_ucoffset;
	uchar8	V_ucKeyNumTemp;
	uchar8	V_ucKeyNum;

	*pV_ucMsgReupdataKey = CMsg_Null;							/*默认不重新更新*/

	/*入口参数合法性判断,数据长度的判断*/

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

	/*密钥总条数判断*/

	V_ucKeyNumTemp = InF_Get_Key_Tol_Num();
	V_ucoffset = C_UpKey_O_KeyNum_1;

	for(i=0; i < V_ucKeyNum; i++)
	{
		if(pV_ucData[V_ucoffset] != V_ucKeyNumTemp)
		{
			*pV_ucMsgReupdataKey = CMsg_ReUpdataKey;		/* 收到的密钥信息中密钥总条数不等于数据层*/
			return(C_SERR_OtherErr);					/*需重启更新*/
		}
		V_ucoffset = V_ucoffset + CL_KeyWithInfo_1;
	}

	/*密钥信息中所有密钥编号必须小于数据层密钥总条数*/
	V_ucoffset = C_UpKey_O_KeyNo_1;
	for(i=0;i<V_ucKeyNum;i++)
	{
		if(pV_ucData[V_ucoffset] >= V_ucKeyNumTemp)					/*密钥编号从0开始。*/
		{
			*pV_ucMsgReupdataKey = CMsg_ReUpdataKey;		/* 收到的密钥信息中密钥编号大于密钥总条数*/
			return(C_SERR_OtherErr);					/*需重启更新*/
		}
		V_ucoffset = V_ucoffset + CL_KeyWithInfo_1;
	}

	/*密钥信息中密钥状态必须相等，且等于00或01*/
	if( (pV_ucData[C_UpKey_O_KeyState_1] != CInfo_TestKey)
		&&(pV_ucData[C_UpKey_O_KeyState_1] != CInfo_OfficialKey) )
	{
		*pV_ucMsgReupdataKey = CMsg_ReUpdataKey;		/* 收到的密钥信息中密钥状态既不是公钥又不是私钥*/
		return(C_SERR_OtherErr);					/*需重启更新*/
	}
	V_ucoffset = C_UpKey_O_KeyState_1;
	for(i = 0; i < V_ucKeyNum; i++)
	{
		if(pV_ucData[V_ucoffset] !=pV_ucData[C_UpKey_O_KeyState_1])
		{
			*pV_ucMsgReupdataKey = CMsg_ReUpdataKey;		/* 收到的密钥信息中密钥状态既不是公钥又不是私钥*/

			return(C_SERR_OtherErr);					/*需重启更新*/
		}
		V_ucoffset = V_ucoffset + CL_KeyWithInfo_1;
	}

	*pV_ucKeyNum = V_ucKeyNum;						/*取密钥信息*/

	return(C_OK);

}



/*******************************************************************************
函数原型：	ushort16  InF_S_Key_Update (uchar8 *pV_ucData, uchar8 V_ucKeyNO)
功能描述：	完成密钥更新，密钥状态另行刷新
输入参数：	pV_ucData:		输入数据首地址。长度为32字节
			V_ucKeyNO:		密钥序号,00为主控密钥值
输出参数：
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：	pV_ucData中数据无变化
*******************************************************************************/
ushort16  InF_S_Key_Update (uchar8 *pV_ucData, uchar8 V_ucKeyNO)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucDataLen;
	ushort16	V_usReturnData16;
	uchar8		V_ucKeyNum;

	/*判断密钥编号是否大于密钥总条数*/
	V_ucKeyNum = InF_Get_Key_Tol_Num();
	if(V_ucKeyNO > V_ucKeyNum)
	{
		return(C_SERR_OtherErr);
	}

	/*更新密钥到ESAM，命令为0x84,0xD4,0x01,0xFF,0x20  如果为主控，P2=00*/
	PF_CopyDataBytes( (uchar8 *)TB_UpdateKey, V_ucbuf, CLen_TB_ESAM_Lc);
	if(V_ucKeyNO == 0x00)
	{
		V_ucbuf[3] = 0x00;			/*P2=00 代表主控，=0xFF代表其他密钥*/
	}
	V_ucDataLen = CLen_S_BufMaxLen;
	PF_OneDataReversed(pV_ucData, &V_ucbuf[CLen_TB_ESAM_Lc], CL_Key);		/*密钥颠倒后写入ESAM*/
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
函数原型：	ushort16  InF_S_ReadKeyStateInESAM(uchar8 *pV_ucData,uchar8 *pV_ucDataLen)
功能描述：	读取ESAM中的密钥状态
输入参数：	pV_ucData:		输出参数指针
			*pV_ucDataLen	开辟的缓冲区的长度
输出参数：	*pV_ucData:		密钥状态
			*pV_ucDataLen	返回数据实际长度
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：	出口参数密钥状态符合645小端模式。
*******************************************************************************/
ushort16  InF_S_ReadKeyStateInESAM(uchar8 *pV_ucData, uchar8 *pV_ucDataLen)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;

	/*长度合法性判断*/
	if(*pV_ucDataLen < CLKey_State)
	{
		return(C_SERR_OtherErr);
	}

/*读取数据*/
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
函数原型：	ushort16  InF_S_GetStatus(uchar8 *pV_ucData,uchar8 *pV_ucLen)
功能描述：	状态查询
输入参数：	pV_ucData:		输出参数指针
			*pV_ucLen		开辟的缓冲区的长度
输出参数：	*pV_ucData:		状态查询数据。（剩余金额+Mac，购电次数+Mac，客户编号，密钥状态）
			*pV_ucLen		返回数据实际长度
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：
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

	/*如果是本地表，刷新ESAM中的剩余金额。
	但这里是不需要管表的类型。反正远程表读数据层剩余金额是读不出来的*/


	/*同步ESAM中剩余金额。15min闭锁*/
	UpdataChargeBalInESAMWithSwitch();

	/*读剩余金额,购电次数,读客户编号,读记录文件中已将数据颠倒*/
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
	/*读密钥状态，读数据层*/
	pDataLen = CLKey_State;
	V_ReturnData = InF_Read_Data(CKey_State, &V_ucbuf[C_GetS_O_Key_State], &pDataLen);
	if(V_ReturnData != C_OK)
	{
		return(C_Error);
	}

	PF_CopyDataBytes(V_ucbuf, &pV_ucData[CLChargeBal_BCD + C_MacLen + CL_PurchasingE_Num + C_MacLen + CLCustomer_Num], CLKey_State);
#endif

	/*读密钥状态，读ESAM*/
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
函数原型：	ushort16      InF_S_DataExcerption(uchar8 *pV_ucData,uchar8 *pV_ucLen)
功能描述：	数据回抄
输入参数：	*pV_ucData:		回抄标识，固定8字节
			*pV_ucLen		开辟的缓冲区的长度
输出参数：	*pV_ucData:		回抄数据(回抄标识8+回抄数据Ld+Mac 4
			*pV_ucLen		返回数据实际长度
返回参数：	C_OK/C_SERR_OtherErr
调用位置：
备    注：	调用前保证p_Data指向数据固定8字节
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


	/*将文件标识进行解析。*/
	PF_Buffer2ToUshort16(&pV_ucData[C_DExc_O_Dir], &V_usFile_Dir);
	PF_Buffer2ToUshort16(&pV_ucData[C_DExc_O_FileNo], &V_usFile_No);
	PF_Buffer2ToUshort16(&pV_ucData[C_DExc_O_Offset], &V_usFile_Offset);
	PF_Buffer2ToUshort16(&pV_ucData[C_DExc_O_Ld], &V_usFile_Ld);
	V_ucFile_Ld_8 = pV_ucData[C_DExc_O_Ld];

	/*判断入口参数是否正确,文件目录如何判断必须是DF01*/
	if(V_usFile_Dir != C_F_MainDir)
	{
		return(C_SERR_OtherErr);
	}
	/*不允许抄读主文件、密钥文件*/
	if( (V_usFile_No == C_F_MF) || (V_usFile_No == C_F_MasterKey) )
	{
		return(C_SERR_OtherErr);
	}

	/*长度判断是否正确*/
	if(V_usFile_No == C_F_Purse)
	{
		/*回抄钱包文件，不管其他参数，应答剩余金额+Mac和购电次数+mac*/
		V_usResponseLen = V_usResponseLen + CLChargeBal_Hex_Cent + CL_PurchasingE_Num + CLCustomer_Num + C_MacLen;
	}
	else
	{
		V_usResponseLen = V_usResponseLen + V_usFile_Ld + C_MacLen;
	}
	if( (*pV_ucLen < V_usResponseLen) || (V_usResponseLen > (C_F_Pam_Max - 2) ) )		/*缓冲区开小了，或读取数据超过100*/
	{
		return(C_SERR_OtherErr);
	}

	/*刷新ESAM中钱包文件和运行文件中的个别参数*/
	if( (V_usFile_No == C_F_Purse) || (V_usFile_No == C_F_OpInfo) )
	{
		/*仅在回抄钱包文件和运行文件时，进行钱包文件和运行信息文件中剩余金额
		等参数和数据层同步，并15min闭锁
		同步ESAM中剩余金额。15min闭锁*/
		UpdataChargeBalInESAMWithSwitch();
	}
	if(V_usFile_No == C_F_OpInfo)	/*同步运行文件。注意这里运行文件本次和上一次不同才更新。*/
	{
		Updata_ESAM_OpParm(C_Msg_Communication);
	}

	/*如果是回抄钱包文件，不管文件偏移，长度都必须应答剩余金额+Mac,购电次数+Mac*/
	if(V_usFile_No == C_F_Purse)
	{
		/*带Mac读剩余金额+购电次数+客户编号+MAC*/
		V_ucDataLen = V_usResponseLen - CL_FileDataCode;
		V_ucReturnData = ReadRecordFile_1(&pV_ucData[C_DExcR_O_ChgBlHC], &V_ucDataLen);
		if(V_ucReturnData != C_OK)
		{
			return(C_SERR_OtherErr);
		}
	}
	/*如果是回抄其他文件*/
	else
	{
		/*读二进制文件*/
		V_ucReturnData = ReadBinFileMac(&pV_ucData[C_DExcR_O_Data], &pV_ucData[C_DExc_O_FileNo], &pV_ucData[C_DExc_O_Offset], &pV_ucData[C_DExc_O_Ld]);
		/*数据和Mac分别颠倒。*/
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
函数原型：	uchar8	InF_S_Is_ParmPlainTextMAC(ulong32	V_ulDI,	uchar8 	*pV_ucDataLen)
功能描述：	判断是否为1类参数，是则返回该参数长度
输入参数：	pV_ucDataLen:	长度指针
			V_ulDI		数据标识
输出参数：	*pV_ucDataLen	1类参数长度，不含Mac
返回参数：	C_OK/C_Error
调用位置：
备    注：	本处仅支持通信模块支持的标识码，但不区分本地远程表
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
函数原型：	uchar8	LookForStr_ParmPlainText(ulong32	V_ulDI,	uchar8 	*pV_ucParmPlainText_O)
功能描述：	根据输入标识码，搜素Str_ParmPlainText型变量
输入参数：	pV_ucParmPlainText_O:	表格中数组下标指针
			V_ulDI			数据标识
输出参数：	*pV_ucParmPlainText_O	表格中数组下标
返回参数：	C_OK/C_Error
调用位置：
备    注：	本处仅支持通信模块支持的标识码，但不区分本地远程表
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
函数原型：	ushort16  InF_S_WriteCustermerNumMAC(ulong32 V_ulDI,uchar8 *pV_ucData,uchar8 V_ucDataLen)
功能描述：	客户编号写esam
输入参数：	V_ulDI			数据标识
			*pV_ucData:		输入参数
			V_ucDataLen		缓冲区的长度(包括Mac)

输出参数：	无
返回参数：	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
调用位置：
备    注：	P_Data缓冲区中的数据时不会变的
*******************************************************************************/
ushort16  InF_S_WriteCustermerNumMAC(ulong32 V_ulDI, uchar8 *pV_ucData, uchar8 V_ucDataLen)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen],V_ucTemp[6];
	uchar8		V_ucReturnData;
	ushort16	V_usDataLen1;

	V_ucbuf[0] = 0x83;			/*不带Mac读二进制文件命令为00B0*/
	V_ucbuf[1] = 0x2A;
	V_ucbuf[2] = 0x8F;			/*FileNo为文件短标识码，采用方式1, 100x xxxx xxxxx为短标识码*/
	V_ucbuf[3] = 0x06;			/*P2*/
	V_ucbuf[4] = 0x00;			/*Lc*/
	V_ucbuf[5] = 0x0A;			/*Lc*/

	/*单项数据+Mac，分别颠倒*/
	PF_OneDataReversed(pV_ucData, &V_ucbuf[6], (V_ucDataLen - C_MacLen));

	PF_OneDataReversed(&pV_ucData[(V_ucDataLen - C_MacLen)], &V_ucbuf[(6 + V_ucDataLen - C_MacLen)], C_MacLen);

	PF_OneDataReversed(V_ucbuf,GV_7816CMD.Header,CL_7816Header);		/*7816命令头暂存*/

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



	/*客户编号不带mac写运行文件*/
	PF_OneDataReversed(pV_ucData, V_ucTemp, (V_ucDataLen - C_MacLen) );

	V_ucReturnData = WriteBinFile(C_ESAM, V_ucTemp, C_F_OpInfo, CF_O_CNumInOP, CLCustomer_Num);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}


	return(C_OK);
}


/*******************************************************************************
函数原型：	ushort16  InF_S_WritePara_PlainTextMAC(ulong32 V_ulDI,uchar8 *pV_ucData,uchar8 V_ucDataLen)
功能描述：	1类参数Mac验证及ESAM对应参数写
输入参数：	*pV_ucData:		输入参数
			V_ucDataLen		缓冲区的长度(包括Mac)
			V_ulDI		数据标识
输出参数：	无
返回参数：	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
调用位置：
备    注：	pV_ucData缓冲区中的数据时不会变的。
			本处仅支持通信模块支持的标识码，但不区分本地远程表
*******************************************************************************/
ushort16  InF_S_WritePara_PlainTextMAC(ulong32 V_ulDI, uchar8 *pV_ucData, uchar8 V_ucDataLen)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;
	uchar8	V_ucFile_Offset;
	uchar8	V_ucFile_No;
	uchar8	V_ucOffsetInOP;
	uchar8	V_ucParmPlainText_O;

	/*首先查表确定在表格TB_ParmPlainText中偏移,找不到其他错误退出*/
	V_ucReturnData = LookForStr_ParmPlainText(V_ulDI, &V_ucParmPlainText_O);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}
	V_ucFile_No = TB_ParmPlainText[V_ucParmPlainText_O].FileNo;
	V_ucFile_Offset = TB_ParmPlainText[V_ucParmPlainText_O].Offset;
	V_ucOffsetInOP = TB_ParmPlainText[V_ucParmPlainText_O].OffsetInOP;

	#if 0
	/*判断数据长度是否合理*/
	if(DataLen != (TB_ParmPlainText[V_ucParmPlainText_O].Len) + C_MacLen)
	{
		return(C_SERR_OtherErr);
	}
	#endif
	/*数据进行颠倒颠倒后的数据在Buf，总长度为DataLen*/
	PF_CopyDataBytes(pV_ucData, V_ucbuf, V_ucDataLen);
	if(V_ulDI == CBackUp_RateFF_Price)
	{
		DataReversed(CBackUp_RateFF_Price, V_ucbuf, C_RItem_Len_RateBak);
	}
	else if(V_ulDI == CBackUp_Ladder_Table)
	{
		DataReversed(CBackUp_Ladder_Table,V_ucbuf,C_RITem_Len_LadderBak);
	}
	else	/*单项数据+Mac，分别颠倒*/
	{
		PF_OneDataReversed(V_ucbuf, V_ucbuf, (V_ucDataLen - C_MacLen));
		PF_OneDataReversed(&V_ucbuf[(V_ucDataLen - C_MacLen)], &V_ucbuf[(V_ucDataLen - C_MacLen)], C_MacLen);
	}
	/*将参数进行Mac验证并写入ESAM*/
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

	/*如果需要写运行文件，则写运行文件*/
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
函数原型：	ushort16  InF_S_WritePara_CipherTextMAC(ulong32 V_ucDI,uchar8 *pV_ucData,uchar8 *pV_ucLength)
功能描述：	2类参数解密
输入参数：	*pV_ucData:			输入参数(密文+Mac)
			*pV_ucLength		缓冲区的长度(包括Mac)
			V_ulDI				数据标识
输出参数：	*pV_ucData
			pV_ucLength:		解密后的数据/及长度
								已去除解密后的数据标识和Mac，是实际数据长度
返回参数：	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
调用位置：
备    注：	注意，P_Data后，至少保留100字节的数据，供参数返写
*******************************************************************************/
ushort16  InF_S_WritePara_CipherTextMAC(ulong32 V_ucDI,uchar8 *pV_ucData,uchar8 *pV_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;
	uchar8	V_ucFile_No;
	uchar8	V_ucDataLen;


	/*判断数据的入口参数是否正确1、超出处理长度2、数据长度小于5*/
	if((*pV_ucLength > (CLen_S_BufMaxLen - CLen_TB_ESAM_Lc ) ) || (*pV_ucLength < (C_MacLen + 1) ) )
	{
		return(C_SERR_OtherErr);
	}
	/*数据颠倒*/
	PF_OneDataReversed(pV_ucData, V_ucbuf, (*pV_ucLength - C_MacLen));
	PF_OneDataReversed(&pV_ucData[*pV_ucLength - C_MacLen], &V_ucbuf[*pV_ucLength - C_MacLen], C_MacLen);

	/*写参数更新文件，进行解密和MAC验证*/
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
进行数据倒项。其中特殊的有:
0400040F(位置信息)/0401(2)0000，0401(2)0001-0401(2)0008时区时段表
	switch(V_ucDI)
		{
			case		CMeter_Position:
				DataReversed(CMeter_Position, V_ucbuf, C_RITem_Len_MeterPosition);
				break;
			case		CFirst_TZone_Data:		/* 2个时区表的颠倒。*/
			case		CSec_TZone_Data:		/*按照14个时区表进行颠倒。不满14个也不管*/
				DataReversed(CDI_TZone_Data, V_ucbuf,C_RITem_Len_TZone_Data);
				break;
			case		CFirst_TZone_1PT_Data:		/* 16个时段表的颠倒。*/
			case		CFirst_TZone_2PT_Data:		/* 按照14个日时段表颠倒，不会溢出。不满14不管*/
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
				if((V_ucDI&0xFFFF0000) == 0x04040000)	/*循显、按键显示参数*/
				{
					PF_OneDataReversed(V_ucbuf, V_ucbuf, DataLen-1);	/*格式DI3-DI0+显示屏数*/
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
函数原型：	ushort16  InF_S_MeterClear( uchar8 *pV_ucData, uchar8 *pV_ucLength)
功能描述：	清零解密
输入参数：	*pV_ucData:				输入参数(密文+Mac)
			*pV_ucLength			缓冲区的长度(包括Mac)
输出参数：	*pV_ucData
			pV_ucLength:	解密后的数据/及长度
								R1-R8
返回参数：	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
调用位置：
备    注：	解密后为8字节。R1-R8
*******************************************************************************/
ushort16  InF_S_MeterClear( uchar8 *pV_ucData, uchar8 *pV_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;

	/*处理长度的判断*/
	if(*pV_ucLength > CLen_S_BufMaxLen)
	{
		return(C_SERR_OtherErr);
	}

	/*数据颠倒.注意特殊命令都是Mac和密文统一颠倒*/
	PF_OneDataReversed(pV_ucData, V_ucbuf, *pV_ucLength);

	/*解密，计算Mac.  然后读出解密后的数据	*/
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


	/*数据颠倒并返回数据*/
	*pV_ucData = V_ucbuf[0];			/*R1*/
	pV_ucData[1] = V_ucbuf[1];			/*R2*/
	PF_OneDataReversed(&V_ucbuf[CF_O_CMDEndTime], &pV_ucData[CF_O_CMDEndTime], CL_CMDEndTime);
	*pV_ucLength = 2 + CL_CMDEndTime;

	return(C_OK);
}


/*******************************************************************************
函数原型：	InF_S_DemandClear( uchar8 *pV_ucData,uchar8 *pV_ucLength)
功能描述：	需清解密
输入参数：	*pV_ucData:			输入参数(密文+Mac)
			*pV_ucLength		缓冲区的长度(包括Mac)
输出参数：	*pV_ucData
			pV_ucLength:		解密后的数据/及长度
								R1-R8
返回参数：	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
调用位置：
备    注：	解密后为8字节。R1-R8
*******************************************************************************/
ushort16  InF_S_DemandClear( uchar8 *pV_ucData, uchar8 *pV_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;

	/*处理长度的判断*/
	if(*pV_ucLength > CLen_S_BufMaxLen)
	{
		return(C_SERR_OtherErr);
	}

	/*数据颠倒.注意特殊命令都是Mac和密文统一颠倒*/
	PF_OneDataReversed(pV_ucData, V_ucbuf, *pV_ucLength);

	/*解密，计算Mac.  然后读出解密后的数据*/
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


	/*数据颠倒并返回数据*/
	*pV_ucData = V_ucbuf[0];			/*R1*/
	pV_ucData[1] = V_ucbuf[1];			/*R2*/
	PF_OneDataReversed(&V_ucbuf[CF_O_CMDEndTime], &pV_ucData[CF_O_CMDEndTime], CL_CMDEndTime);
	*pV_ucLength = 2 + CL_CMDEndTime;

	return(C_OK);

}


/*******************************************************************************
函数原型：	ushort16  InF_S_EventClear( uchar8 *pV_ucData,uchar8 *pV_ucLength)
功能描述：	需清解密
输入参数：	*pV_ucData:				输入参数(密文+Mac)
			*pV_ucLength			缓冲区的长度(包括Mac)
输出参数：	*pV_ucData
			pV_ucLength:	解密后的数据/及长度  R1-R12
返回参数：	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
调用位置：
备    注：	解密后为8字节。R1-R12
*******************************************************************************/
ushort16  InF_S_EventClear( uchar8 *pV_ucData,uchar8 *pV_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;

	/*处理长度的判断*/
	if(*pV_ucLength > CLen_S_BufMaxLen)
	{
		return(C_SERR_OtherErr);
	}

	/*数据颠倒.注意特殊命令都是Mac和密文统一颠倒*/
	PF_OneDataReversed(pV_ucData, V_ucbuf, *pV_ucLength);

	/*解密，计算Mac.  然后读出解密后的数据	*/
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


	/*数据颠倒并返回数据.*/
	*pV_ucData = V_ucbuf[0];			/*R1*/
	pV_ucData[1] = V_ucbuf[1];			/*R2*/
	PF_OneDataReversed(&V_ucbuf[CF_O_CMDEndTime], &pV_ucData[CF_O_CMDEndTime], CL_CMDEndTime);
	PF_OneDataReversed(&V_ucbuf[CF_O_EventClearDI], &pV_ucData[CF_O_EventClearDI], CL_DI);
	*pV_ucLength = 2 + CL_CMDEndTime + CL_DI;

	return(C_OK);

}


/*******************************************************************************
函数原型：	ushort16  InF_S_ControlCommand( uchar8 *pV_ucData,uchar8 *pV_ucLength)
功能描述：	控制命令解密
输入参数：	*pV_ucData:				输入参数(密文+Mac)
			*pV_ucLength			缓冲区的长度(包括Mac)
输出参数：	*pV_ucData
			pV_ucLength:			解密后的数据/及长度			  R1-R12
返回参数：	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
调用位置：
备    注：	解密后为8字节。R1-R12
*******************************************************************************/
ushort16  InF_S_ControlCommand( uchar8 *pV_ucData, uchar8 *pV_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;

	/*处理长度的判断*/
	if(*pV_ucLength > CLen_S_BufMaxLen)
	{
		return(C_SERR_OtherErr);
	}

	/*数据颠倒.注意特殊命令都是Mac和密文统一颠倒*/
	PF_OneDataReversed(pV_ucData,V_ucbuf, *pV_ucLength);

	/*解密，计算Mac.  然后读出解密后的数据	*/
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


	/*数据颠倒并返回数据*/
	*pV_ucData = V_ucbuf[0];			/*R1*/
	pV_ucData[1] = V_ucbuf[1];			/*R2*/
	PF_OneDataReversed(&V_ucbuf[CF_O_CMDEndTime], &pV_ucData[CF_O_CMDEndTime], CL_CMDEndTime);
	*pV_ucLength = 2 + CL_CMDEndTime;

	return(C_OK);
}


/*******************************************************************************
函数原型：	uchar8	SelectFile(uchar8	V_ucFileNo)
功能描述：	选择文件
输入参数：	V_ucFileNo:				文件
输出参数：	无
返回参数：	C_OK/C_Error
调用位置：
备    注：
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
函数原型：	ushort16	InF_S_WriteESAMPara_PlainTextMAC(uchar8 *pV_ucData,uchar8 V_ucLength)
功能描述：	明文带Mac写ESAM
输入参数：	*pV_ucData:				输入参数
			V_ucLength				缓冲区的长度(2(FN)+2(Offset)+L(D)+4(Mac))
输出参数：	无
返回参数：	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
调用位置：
备    注：
*******************************************************************************/
ushort16	InF_S_WriteESAMPara_PlainTextMAC(uchar8 *pV_ucData, uchar8 V_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;
	uchar8	V_ucFile_Ld;
	uchar8	V_ucFile_Offset,V_ucFile_OffsetH;
	uchar8	V_ucFile_No;

	/*文件名*/
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
	/*文件长度*/
	if(V_ucLength <= (CL_FileNO + CL_Offset + C_MacLen))
	{
		return(C_SERR_OtherErr);
	}
	V_ucFile_Ld = V_ucLength - CL_FileNO - CL_Offset ;		/*File_Ld含Mac 长度*/

	/*数据颠倒 */
	PF_OneDataReversed(&pV_ucData[C_WESAM_O_Data], V_ucbuf, (V_ucFile_Ld - C_MacLen) );
	PF_OneDataReversed(&pV_ucData[C_WESAM_O_Data + V_ucFile_Ld - C_MacLen], &V_ucbuf[V_ucFile_Ld - C_MacLen], C_MacLen);
	/*选择文件*/
	V_ucReturnData = SelectFile(V_ucFile_No);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}

	/*写文件*/
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
函数原型：	ushort16  InF_S_WriteESAMPara_CipherTextMAC (uchar8 *pV_ucData, uchar8 V_ucLength)
功能描述：	密文带Mac写ESAM
输入参数：	*pV_ucData:				输入参数
			V_ucLength				缓冲区的长度(2(FN)+2(Offset)+L(D)+4(Mac))
输出参数：	无
返回参数：	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
调用位置：
备    注：
*******************************************************************************/
ushort16  InF_S_WriteESAMPara_CipherTextMAC (uchar8 *pV_ucData, uchar8 V_ucLength)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;
	uchar8	V_ucFile_Ld;
	uchar8	V_ucFile_Offset,V_ucFile_OffsetH;
	uchar8	V_ucFile_No;

	/*文件名*/
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

	/*文件长度*/
	if(V_ucLength <= (CL_FileNO + CL_Offset + C_MacLen))
	{
		return(C_SERR_OtherErr);
	}
	V_ucFile_Ld = V_ucLength - CL_FileNO - CL_Offset ;		/*File_Ld含Mac 长度*/

	/*数据颠倒 */
	PF_OneDataReversed(&pV_ucData[C_WESAM_O_Data], V_ucbuf, (V_ucFile_Ld - C_MacLen));
	PF_OneDataReversed(&pV_ucData[C_WESAM_O_Data + V_ucFile_Ld - C_MacLen],&V_ucbuf[V_ucFile_Ld - C_MacLen], C_MacLen);
	/*选择文件*/
	V_ucReturnData = SelectFile(V_ucFile_No);
	if(V_ucReturnData != C_OK)
	{
		return(C_SERR_OtherErr);
	}

	/*写文件*/
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
函数原型：uchar8	InF_Get_Key_Tol_Num(void)
功能描述：获取数据层密钥总条数
输入参数：无
输出参数：无
返回参数：
调用位置：
备    注：这里如果获取不成功，默认为20条
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
函数原型：void  InF_S_GetMeterNum_ReworkDL(void)
功能描述：读取ESAM中的表号，并更新EE中表号
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：该函数在ESAM复位消息中调用
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

	/*客户编号不一致，将esam更新到EE*/
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
函数原型：void  InF_S_GetKeyStatus_ReworkKeyStatus(void)
功能描述：读esam中密钥状态，给显示发显示符号
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：该函数在ESAM复位消息中调用
*******************************************************************************/
void  InF_S_GetKeyStatus_ReworkKeyStatus(void)
{
	if(InF_JudgeKeyStatus() == C_StateOfOfficialKey)	/*全正式密钥，发C_PublicKeySign清*/
	{
		Comm_SendMsgToDisp(C_PublicKeySign, C_NotDisplay, C_Duration_Alway);
	}
	else	/*发C_PublicKeySign亮*/
	{
		Comm_SendMsgToDisp(C_PublicKeySign, C_AlwaysDisplay, C_Duration_Alway);
	}
}


/*******************************************************************************
函数原型：	ushort16	InF_S_InitMoney(uchar8 V_ucSrcMsg,uchar8 *pV_ucData)
功能描述：	远程初始化钱包安全模块接口函数
输入参数：	*pV_ucData	:远程初始化钱包文件的数据
						:固定16字节，格式4字节预置金额+Mac1
						:+4字节购电次数+Mac2
			V_ucSrcMsg	:取值C_Msg_Communication、C_Msg_Card
						:通信传递进来的是小端模式。插卡传进来是大端模式。
输出参数：	无
返回参数：	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
调用位置：
备    注：	完成	1)Mac验证
					2)判断购电次数--还是调整到通信命令执行。
					3)刷新ESAM钱包文件的剩余金额和购电次数
*******************************************************************************/
ushort16	InF_S_InitMoney(uchar8 V_ucSrcMsg,uchar8 *pV_ucData)
{
	ushort16	V_usReturnData16;
	uchar8		V_ucbuf[C_Init_MoneyDataLen];

	/*将数据颠倒*/
	PF_CopyDataBytes(pV_ucData,V_ucbuf,C_Init_MoneyDataLen);
	if(V_ucSrcMsg == C_Msg_Communication)	/*通信传递进来的是小端模式。插卡传进来是大端模式。*/
	{
		DataReversed(CDI_Init_Money, V_ucbuf, C_RITem_Len_InitMoney);
	}

	/*带Mac 写记录文件-剩余金额*/
	V_usReturnData16 = WriteRecordFile(&V_ucbuf[C_InitM_O_ChgBlHC], (CLChargeBal_Hex_Cent + C_MacLen) );
	if(V_usReturnData16 != C_OK)
	{
		return(V_usReturnData16);
	}

#if 0
	/*参数预制卡钱包文件没有购电次数*/
	/*带Mac 写记录文件-购电次数*/
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
函数原型：InF_S_GetPPNum(ulong32	*pV_ulPPNum)
功能描述：获取ESAM中购电次数(Power Purchase Num)
输入参数：pV_ulPPNum				:购电次数地址
输出参数：*pV_ulPPNum			:购电次数，32位Hex
返回参数：C_OK/C_SERR_OtherErr
调用位置：
备    注：读不出输出参数清零，返回C_SERR_OtherErr
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

	/*不用转成小端模式,读记录文件已颠倒。*/
	PF_Buffer4ToUlong32(V_ucbuf, pV_ulPPNum, CL_PurchasingE_Num);

	return(C_OK);
}
#endif

/*******************************************************************************
函数原型：	ushort16	InF_S_Purchase(uchar8	*pV_ucData)
功能描述：	对ESAM钱包文件进行充值Mac验证及充值操作
输入参数：	*pV_ucData		:充值报文。格式:购电金额4+购电次数4+Mac1
							所有数据都符合645格式
输出参数：	无
返回参数：	C_OK/C_SERR_ESAM_VF
调用位置：
备    注：	pData的数据是不会变化的
*******************************************************************************/
ushort16	InF_S_Purchase(uchar8	*pV_ucData)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	ushort16	V_usDataLen = CLen_S_BufMaxLen;

	/*充值命令帧为 80 42 00 00 00 0C +购电金额+购电次数+Mac1*/
	PF_CopyDataBytes((uchar8 *)TB_Increase_698, V_ucbuf, CLen_TB_ESAM_Lc_698_Esam);
	/*copy+颠倒*/
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
函数原型：	uchar8	InF_S_ColdRestCard(uchar8	*pV_ucCardNo)
功能描述：	冷复位卡
输入参数：	pV_ucCardNo				:卡序列号入口指针
输出参数： 	*pV_ucCardNo			:卡序列号，固定8字节，符合小端(645)模式
返回参数：	C_OK/C_Error
调用位置：
备    注：	1、复位如果不成功，则连续复位3次
			2、复位不成功，*pCardNo不会修改
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
函数原型：	uchar8	InF_S_SelectFile(uchar8 V_ucCH, ushort16 V_usFileName)
功能描述：	选择文件
输入参数：	V_ucCH			:通道，取值C_ESAM/C_Card
			V_usFileName	:文件名称，例如C_F_MF				0x3F00
输出参数：	无
返回参数：	C_OK/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR
调用位置：
备    注：	1、本接口函数兼容ESAM和card
			2、仅在返回值为C_Error时，输出pErr7816CMDHeader/pSW1_2
					C_OK时不改写
			3、所有输出参数都符合小端模式
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

	PF_OneDataReversed(V_ucbuf,GV_7816CMD.Header, CL_7816Header);		/*操作之前保存命令头*/

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
函数原型：	uchar8	InF_SC_RDBinFileNoMac(uchar8 V_ucCH,uchar8 V_ucFileNo,uchar8 V_ucParmOffset,ushort16 V_usParmLen,uchar8 *pV_ucData)
功能描述：	获取卡中文件头(68 + CMD+2字节长度)
输入参数：	V_ucFileNo:				:读取的二进制文件短标识码。见宏定义
			V_ucParmOffset			:读的参数偏移。见宏定义
			V_usParmLen				:需要读的参数长度。
			pV_ucData				:待读出数据的缓冲区首地址
			V_ucCH					:通道号取值C_ESAM/C_Card
输出参数：	*pV_ucData				:读出内容。长度为ParmLen
返回参数：	C_OK/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR
调用位置：
备    注：	注意这里2进制文件中参数都是大端模式的。
			因为到底有什么参数不清楚
			同时开辟的缓冲区长度一定大于ParmLen
*******************************************************************************/
uchar8	InF_SC_RDBinFileNoMac(uchar8 V_ucCH,uchar8 V_ucFileNo,uchar8 V_ucParmOffset,ushort16 V_usParmLen,uchar8 *pV_ucData)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen];
	uchar8		V_ucDataLen;
	ushort16	V_usDataLen;
	uchar8		V_ucReturnData;

	if(V_ucCH == C_Card)
	{
		/*不带Mac读二进制文件的命令头*/
		V_ucbuf[0] = 0x00;					/*不带Mac读二进制文件命令为00B0*/
		V_ucbuf[1] = 0xB0;
		V_ucbuf[2] = 0x80 | V_ucFileNo;			/*FileNo为文件短标识码，采用方式1, 100x xxxx xxxxx为短标识码*/
		V_ucbuf[3] = V_ucParmOffset;			/*P2*/
		V_ucbuf[4] = V_usParmLen;				/*Le*/


		V_ucDataLen = CLen_S_BufMaxLen;
		PF_OneDataReversed(V_ucbuf,GV_7816CMD.Header, CL_7816Header);		/*操作之前保存命令头*/


		GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucbuf, CLen_TB_ESAM_Le, V_ucbuf, &V_ucDataLen);
		V_ucReturnData = C_IC_NOIN_ERR;
	}
	else
	{
		/*不带Mac读二进制文件的命令头*/
		V_ucbuf[0] = 0x80;					/*不带Mac读二进制文件命令为00B0*/
		V_ucbuf[1] = 0x2C;
		V_ucbuf[2] = 0x00;					/*FileNo为文件短标识码*/
		V_ucbuf[3] = V_ucFileNo;				/*FileNo为文件短标识码*/
		V_ucbuf[4] = 0x00;					/*文件偏移*/
		V_ucbuf[5] = 0x05;					/*后续数据长度*/
		V_ucbuf[6] = 0x00;
		V_ucbuf[7] = 0x00;					/*文件偏移*/
		V_ucbuf[8] = V_ucParmOffset;			/*文件偏移*/
		V_ucbuf[9] = (uchar8)(V_usParmLen>>8);	/*读文件长度*/
		V_ucbuf[10] = (uchar8)V_usParmLen;		/*读文件长度*/

		V_usDataLen = CLen_S_BufMaxLen;
		PF_OneDataReversed(V_ucbuf, GV_7816CMD.Header, CL_7816Header);		/*操作之前保存命令头*/

		GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucbuf, 11, V_ucbuf, &V_usDataLen);
		V_ucReturnData = C_IC_ESAM_RDWR_ERR;
	}

	/*判断V_ReturnData16,返回*/
	if( (GV_7816CMD.SW1_2 == C_Security_CommandOk) || ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) == C_Security_ProcessOk) )/*正确*/
	{
		PF_CopyDataBytes_698(V_ucbuf, pV_ucData, V_usParmLen);
		return(C_OK);
	}
	else	/*错误*/
	{
		return(V_ucReturnData);
	}
}

/*******************************************************************************
函数原型：void		InF_S_Dispatch_5s(void)
功能描述：提供调度定时5s调用的函数
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
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
函数原型：void		UpdataChargeBalInESAMWithSwitch(void)
功能描述：刷新ESAM中剩余金额，带15min闭锁时间
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void		UpdataChargeBalInESAMWithSwitch(void)
{
	uchar8		V_ucReturnData;
	uchar8		V_ucbuf[CLChargeBal_Hex_Cent];
	ushort16	V_usDataLen,V_usCodeData;

	/*如果时间不到，则不进行同步操作*/
	if(SV_UpdateMInEsamTimer != 0)
	{
		return;
	}

	/*读数据层剩余金额	*/
	V_usDataLen = CLChargeBal_Hex_Cent;
	V_ucReturnData = InF_GetData_ObjectManage(CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, &V_usCodeData);
	if(V_ucReturnData != C_OK)
	{
		return;					/*读不出数据层剩余金额，则退出*/
	}

	/*同步数据层和ESAM中剩余金额。注意，一般情况下，是对ESAM扣减，
	但如果数据层剩余金额大，则进行退费操作。*/
	InF_S_UpdataChargeBalInESAM(V_ucbuf);

	SV_UpdateMInEsamTimer = C_SV_UpdateMInEsamTimer;		/*启动闭锁定时器15min*/
}


/*******************************************************************************
函数原型：	uchar8	InF_SC_L_Auth(uchar8	*pV_ucIC_CardNo)
功能描述：	本地身份认证(也称内部认证。对应通信身份认证位外部认证)
输入参数：	pV_ucIC_CardNo			:卡片序列号(小端，固定8字节)
输出参数：	无
返回参数：	C_OK/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR/C_IC_AUTH_ERR
调用位置：
备    注：	参考安全规范附录A.1.1及智能安全芯片6.1.1
			在调用本函数前，ESAM和卡片都经过复位，卡片序列号已保存
			已经过目录和文件选择
*******************************************************************************/
uchar8	InF_SC_L_Auth(uchar8	*pV_ucIC_CardNo)
{
	uchar8		V_ucSendBuf[CL_Send_InIC];
	uchar8		V_ucReponseBuf[CL_Response_InIC];
	ushort16	V_usDataLen;
	uchar8		V_ucRand8[9];
	uchar8		V_ucK1[9],V_ucDataLen;


	/*取ESAM 8字节随机数	*/
	PF_CopyDataBytes( (uchar8 * )TB_GetChallenge_698_Esam, V_ucSendBuf, CLen_TB_ESAM_Lc_698_Esam);
	V_ucSendBuf[3] = 0x08;
	V_usDataLen = CL_Response_InIC;
	PF_OneDataReversed(V_ucSendBuf, GV_7816CMD.Header, CL_7816Header);		/*操作之前保存命令头*/
	GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucSendBuf, CLen_TB_ESAM_Le_698_Esam, V_ucRand8, &V_usDataLen);
	if(GV_7816CMD.SW1_2 != C_Security_CommandOk)	/*返回SW !=9000*/
	{
		return(C_IC_ESAM_RDWR_ERR);
	}
	/*使用卡片序列号对ESAM内嵌密钥进行分散，产生过程密钥；*/
	PF_CopyDataBytes((uchar8 *)TB_AuthDistributedkey_L_698, V_ucSendBuf, CLen_TB_ESAM_Lc_698_Esam);
	PF_OneDataReversed(pV_ucIC_CardNo, &V_ucSendBuf[CLen_TB_ESAM_Lc_698_Esam], CL_CardNo);
	PF_CopyDataBytes(V_ucRand8,&V_ucSendBuf[CLen_TB_ESAM_Lc_698_Esam + CL_CardNo], 8);			/*加入随机数1*/
	V_usDataLen = CL_Response_InIC;
	PF_OneDataReversed(V_ucSendBuf,GV_7816CMD.Header, CL_7816Header);		/*操作之前保存命令头*/
	GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucSendBuf, (CLen_TB_ESAM_Lc_698_Esam + CL_CardNo + 8), V_ucK1, &V_usDataLen);
	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType)!= C_Security_ProcessOk) )
	{
		return(C_IC_ESAM_RDWR_ERR);
	}

	/*卡片进行加密随机数(内部认证命令)*/
	PF_CopyDataBytes((uchar8 *) TB_CardEncryptingRand1, V_ucSendBuf, CLen_TB_ESAM_Lc);
	PF_CopyDataBytes(V_ucRand8,&V_ucSendBuf[CLen_TB_ESAM_Lc], 8);
	V_ucDataLen = CL_Response_InIC;
	PF_OneDataReversed(V_ucSendBuf,GV_7816CMD.Header, CL_7816Header);		/*操作之前保存命令头*/
	GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucSendBuf, (CLen_TB_ESAM_Lc + 8), V_ucReponseBuf, &V_ucDataLen);
	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_IC_NOIN_ERR);
	}

	/*获取卡片中加密后的随机数K2*/
	/*	InF_Delay_us(3000);*/
	PF_CopyDataBytes((uchar8 *)TB_GetResponse, &V_ucSendBuf[0], CLen_TB_ESAM_4);
	V_ucSendBuf[CLen_TB_ESAM_4] = 8;					/*Rand1加密后密文长度为8*/
	V_ucDataLen = CL_Response_InIC;
	PF_OneDataReversed(V_ucSendBuf,GV_7816CMD.Header,CL_7816Header);		/*操作之前保存命令头*/
	GV_7816CMD.SW1_2 = INF_SendData_7816_Card(&V_ucSendBuf[0],(CLen_TB_ESAM_4 + 1), V_ucReponseBuf, &V_ucDataLen);
	if( (GV_7816CMD.SW1_2 !=C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_IC_NOIN_ERR);
	}
	/*比对随机数K1/K2，相等，内部认证通过；不等则没有通过。*/
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
函数原型：uchar8	InF_SC_Judge_CardFile(uchar8	*pV_ucFile)
功能描述：判断卡片中文件格式
输入参数：pFile				:卡片中文件开始首地址
输出参数：无
返回参数：C_OK/C_Error
调用位置：
备    注：File格式	1)单项符合大端模式
					2) 帧格式:0x68  + CMD + 2字节Len + 数据Data +CS +0x16
					3) Len:表示数据Data长度
					4)CS 从CMD开始，到CS前的数据
*******************************************************************************/
uchar8	InF_SC_Judge_CardFile(uchar8	*pV_ucFile)
{
	ushort16	V_usLen16;
	uchar8		V_uccs = 0;
	uchar8		i;

	/*文件起始字节为0x68*/
	if(pV_ucFile[0] != 0x68)
	{
		return(C_Error);
	}

	/*取长度，注意为大端模式*/
	V_usLen16 = pV_ucFile[2];
	V_usLen16 <<= 8;
	V_usLen16 |= (ushort16)pV_ucFile[3];

	/*计算CS，计算cs的长度从CMD开始，第一个68不算在内，由于pFile[0]中放的是68,
	为了方便，循环中的i是pFile中的偏移数，因此这里需要将第一个68的长度也计算在内
	实际计算cs从pFile[1]开始，即i的初始值为1*/
	for(i = 1; i< (V_usLen16 + 4); i++)		/*从命令字开始*/
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
函数原型：	uchar8	InF_SC_GenerateRandToCalMac(uchar8	V_ucCH,uchar8 V_ucLength)
功能描述：	使得安全模块/ESAM产生N字节随机数，用于插卡过程中Mac计算
输入参数：	V_ucCH					:通道号，取值C_Card/C_ESAM
输出参数：	无
返回参数：	C_OK/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR
调用位置：
备    注：	对于用于Mac 计算的4字节随机数，有如下认识
			1、	远程通信，是上位机下发身份认证命令时，命令帧中随机数1的高4字节(645小端模式)。
			用于ESAM对上位机的下发带Mac的数据进行验证。
			2、	本地通信，是取ESAM的随机数，用于Mac验证。
			3、	用户卡返写，取ESAM得随机数，用于返写文件的随机数
			4、	本地通信，肯定会取消远程身份认证许可。这样如果远程再次通信，必须重新身份认证。
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
		V_usDataLen = V_ucLength;					/*SV_Rand1_4数组长度*/
		PF_OneDataReversed(V_ucSendBuf,GV_7816CMD.Header, CL_7816Header);	/*操作之前保存命令头*/

		GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucSendBuf, CLen_TB_ESAM_Lc_698_Esam, V_ucRand1_4, &V_usDataLen);
		V_ucReturnData = C_IC_ESAM_RDWR_ERR;

		PF_CopyDataBytes(V_ucRand1_4, SV_Rand1_4, V_ucLength);	/*不需要颠倒*/
	}
	else
	{
		PF_CopyDataBytes((uchar8 *)TB_GetChallenge, V_ucSendBuf, CLen_TB_ESAM_4);
		V_ucSendBuf[CLen_TB_ESAM_4] = V_ucLength;	/*Le*/
		V_ucDataLen = V_ucLength;					/*SV_Rand1_4数组长度*/
		PF_OneDataReversed(V_ucSendBuf, GV_7816CMD.Header, CL_7816Header);	/*操作之前保存命令头*/

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
函数原型：	uchar8	SC_ReadRunFileMac(uchar8 V_ucCH, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, uchar8 *pV_ucData,
			uchar8 V_ucNxtCLA, uchar8 V_ucNxtINS, uchar8 V_ucNxtP1, uchar8 V_ucNxtP2, uchar8 V_ucLC, uchar8	 *pV_ucIC_CardNo)
功能描述：	带Mac 读取二进制文件数据。注意和函数ReadBinFileMac区别
输入参数：	V_ucCH				:通道号。取值C_Card/C_ESAM
			V_ucFileNo			:读取的二进制文件短标识码。见宏定义
			V_ucParmOffset		:读的参数偏移。见宏定义
			V_ucNxtCLA/V_ucNxtINS/V_ucNxtP1/V_ucNxtP2:
							:下一条指令的命令首标
			V_ucLC				:待读数据有效长度+Mac长度
			*pV_ucIC_CardNo		:卡号，固定8字节，小端模式。
输出参数：	*pV_ucData			:返回参数，其长度为读的数据长度+4字节Mac
返回参数：	C_OK/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR
调用位置：
备    注：	一定要注意P_Data缓冲区的长度要够写。这里不做最大长度限制
			其他理解性注释如下
			带Mac读二进制文件，详细见安全规范详细设计1.2.12	ReadBinary（读二进制文件）00B0/04B0
			1、命令格式为04 B0 P1 P2 Lc(=09,11) + Rand4 + "下一条指令 CLA INS P0 P1 Lc1" +（分散因子）
			2、Rand4，作为Mac运算过程中的一个因子
			3、因为Mac运算是从命令头的首字节CLA开始，所以要带"下一条指令"
			4、带Mac读，同样需要密钥进行运算。
				a、对于ESAM带Mac读，远程通信采用，表号作为分散因子。
				b、对于ESAM带Mac读，本地插卡过程中，采用卡号作为分散因子。
					所以对ESAM带Mac读，Lc=0x11，多8字节分散因子
				c、	对于卡采用Mac读，直接采用卡号作为分散因子，无须传递给卡。所以Lc = 09
			5、	LC1有2种含义：
				a、通常，LC1=要读的数据长度+Mac长度
				b、在数据回抄时，LC1=参数长度+Mac长度+分散因子长度。采用函数ReadBinFileMac
			6、根据以上解释，仅在对ESAM操作时再带分散因子。而且由于
				远程带Mac读已函数ReadBinFileMac已完成，因此这里分散因子都是卡号。
			7、根据以上解释LC1 = 需要读的数据+Mac长度
*******************************************************************************/
uchar8	SC_ReadRunFileMac(uchar8 V_ucCH, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, uchar8 *pV_ucData,
			uchar8 V_ucNxtCLA, uchar8 V_ucNxtINS, uchar8 V_ucNxtP1, uchar8 V_ucNxtP2, uchar8 V_ucLC, uchar8	 *pV_ucIC_CardNo)
{
	uchar8		V_ucSendBuf[CL_Send_InIC];
	ushort16	V_usDataLen;
	uchar8		V_ucSendLen;
	uchar8		V_ucReturnData;

	/*帧格式:04+B0+P1(0x80|V_ucFileNo)+P2(V_ucParmOffset)+09(0x11)+Rand4+下一条指令5字节命令头+(卡号) */
	V_ucSendBuf[0] = 0x83;
	V_ucSendBuf[1] = 0x2c;
	V_ucSendBuf[2] = 0x00;
	V_ucSendBuf[3] = V_ucFileNo;

	/*根据通道，置LC及发送总长度,置分散因子卡号*/

	V_ucSendBuf[4] = 0x00;
	V_ucSendBuf[5] = 0x16;	/*LC1 22字节*/
	V_ucSendBuf[6] = 0x48;

	PF_OneDataReversed(pV_ucIC_CardNo, &V_ucSendBuf[7], CL_CardNo);

	/*copy Rand4*/
	PF_CopyDataBytes(SV_Rand1_4, &V_ucSendBuf[7 + CL_CardNo], 4);

	V_ucSendBuf[19] = 0x00;			/*P3*/
	V_ucSendBuf[20] = V_ucParmOffset;	/*P3*/
	V_ucSendBuf[21] = 0x00;			/*LEN 将要读取的数据*/
	V_ucSendBuf[22] = (V_ucLC - 4);		/*LEN*/

	/*取下一条指令的命令头*/
	V_ucSendBuf[23] = V_ucNxtCLA;
	V_ucSendBuf[24] = V_ucNxtINS;
	V_ucSendBuf[25] = V_ucNxtP1;
	V_ucSendBuf[26] = V_ucNxtP2;
	V_ucSendBuf[27] = V_ucLC;

	V_ucSendLen = 28;

	V_usDataLen = CL_Response_InIC;
	/*读取数据*/
	PF_OneDataReversed(V_ucSendBuf, GV_7816CMD.Header, CL_7816Header);	/*操作之前保存命令头*/

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
函数原型：	uchar8	SC_ReadBinFileMac(uchar8 V_ucCH, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, uchar8 *pV_ucData,
			uchar8 V_ucNxtCLA, uchar8 V_ucNxtINS, uchar8 V_ucNxtP1, uchar8 V_ucNxtP2, uchar8 V_ucLC1,uchar8	 *pV_ucIC_CardNo)
功能描述：	带Mac 读取二进制文件数据。注意和函数ReadBinFileMac区别
输入参数：	V_ucCH				:通道号。取值C_Card/C_ESAM
			V_ucFileNo			:读取的二进制文件短标识码。见宏定义
			V_ucParmOffset		:读的参数偏移。见宏定义
			V_ucNxtCLA/V_ucNxtINS/V_ucNxtP1/V_ucNxtP2:
								:下一条指令的命令首标
			V_ucLC1				:待读数据有效长度+Mac长度
			*pV_ucIC_CardNo		:卡号，固定8字节，小端模式。
输出参数：	*pV_ucData			:返回参数，其长度为读的数据长度+4字节Mac，
						:即LC1
返回参数：	C_OK/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR
调用位置：
备	  注：	一定要注意P_Data缓冲区的长度要够写。这里不做最大长度限制
			其他理解性注释如下
			带Mac读二进制文件，详细见安全规范详细设计1.2.12	ReadBinary（读二进制文件）00B0/04B0
			1、命令格式为04 B0 P1 P2 Lc(=09,11) + Rand4 + "下一条指令 CLA INS P0 P1 Lc1" +（分散因子）
			2、Rand4，作为Mac运算过程中的一个因子
			3、因为Mac运算是从命令头的首字节CLA开始，所以要带"下一条指令"
			4、带Mac读，同样需要密钥进行运算。
				a、对于ESAM带Mac读，远程通信采用，表号作为分散因子。
				b、对于ESAM带Mac读，本地插卡过程中，采用卡号作为分散因子。
					所以对ESAM带Mac读，Lc=0x11，多8字节分散因子
				c、	对于卡采用Mac读，直接采用卡号作为分散因子，无须传递给卡。所以Lc = 09
			5、	LC1有2种含义：
				a、通常，LC1=要读的数据长度+Mac长度
				b、在数据回抄时，LC1=参数长度+Mac长度+分散因子长度。采用函数ReadBinFileMac
			6、根据以上解释，仅在对ESAM操作时再带分散因子。而且由于
				远程带Mac读已函数ReadBinFileMac已完成，因此这里分散因子都是卡号。
			7、根据以上解释LC1 = 需要读的数据+Mac长度
*******************************************************************************/
uchar8	SC_ReadBinFileMac(uchar8 V_ucCH, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, uchar8 *pV_ucData,
			uchar8 V_ucNxtCLA, uchar8 V_ucNxtINS, uchar8 V_ucNxtP1, uchar8 V_ucNxtP2, uchar8 V_ucLC1,uchar8	 *pV_ucIC_CardNo)
{
	uchar8	V_ucSendBuf[CL_Send_InIC];
	uchar8	V_ucReponseBuf[CL_Response_InIC];
	uchar8	V_ucDataLen;
	uchar8	V_ucSendLen;
	uchar8	V_ucReturnData;

	/*帧格式:04+B0+P1(0x80|V_ucFileNo)+P2(V_ucParmOffset)+09(0x11)+Rand4+下一条指令5字节命令头+(卡号)*/
	V_ucSendBuf[0] = 0x04;
	V_ucSendBuf[1] = 0xB0;
	V_ucSendBuf[2] = 0x80 | V_ucFileNo;
	V_ucSendBuf[3] = V_ucParmOffset;

	/*根据通道，置LC及发送总长度,置分散因子卡号*/
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
	else	/*理论上不可能出现此错误，记作C_IC_NOIN_ERR错误*/
	{
		return(C_IC_NOIN_ERR);
	}

	/*copy Rand4*/
	PF_CopyDataBytes(SV_Rand1_4, &V_ucSendBuf[5], 4);
	/*取下一条指令的命令头*/
	V_ucSendBuf[9] = V_ucNxtCLA;
	V_ucSendBuf[10] = V_ucNxtINS;
	V_ucSendBuf[11] = V_ucNxtP1;
	V_ucSendBuf[12] = V_ucNxtP2;
	V_ucSendBuf[13] = V_ucLC1;

	V_ucDataLen = CL_Response_InIC;
	/*读取数据*/
	PF_OneDataReversed(V_ucSendBuf, GV_7816CMD.Header, CL_7816Header);	/*操作之前保存命令头*/
	/* InF_Delay_us(3000);*/
	if(V_ucCH == C_ESAM)	/*ESAM需要修改*/
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

	/*读取响应。这里对61XX中XX值不对。*/
	/*InF_Delay_us(3000);*/
	PF_CopyDataBytes((uchar8 *)TB_GetResponse, V_ucSendBuf, CLen_TB_ESAM_4);
	V_ucSendBuf[CLen_TB_ESAM_4] = V_ucLC1;
	V_ucDataLen = V_ucLC1;
	PF_OneDataReversed(V_ucSendBuf, GV_7816CMD.Header, CL_7816Header);		/*操作之前保存命令头*/
	if(V_ucCH == C_ESAM)	/*ESAM需要修改*/
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
函数原型：	uchar8	InF_SC_Get_MFile_PreSetCard(StrCardParse	*pStr_CardParse)
功能描述：	参数预置卡、用户卡中读出钱包文件
输入参数：	pStr_CardParse->CardNo :卡号(IC_CardNo,小端8字节)(实际没有用，仅作为指针传递)
输出参数：
			参数预置卡
			pStr_CardParse->PPMoney	:读出的预置金额。hex，单位为分
			pStr_CardParse->IC_File[]	:预置金额+Mac。数据符合大端模式

			用户卡
			pStr_CardParse->PPMoney	:读出的预置金额。hex，单位为分
			pStr_CardParse->PPNum		:购电次数
返回参数：	C_OK/C_IC_NOIN_ERR
调用位置：	插入用户卡、参数预置卡文件
备	  注：	明文+Mac方式读取剩余金额
*******************************************************************************/
uchar8	InF_SC_Get_MFile_Card(StrCardParse 		*pStr_CardParse)
{
	uchar8	V_ucReturnData;
	uchar8	V_ucbuf[4];				/*钱包文件中购电次数和剩余金额都是4字节*/

	if(pStr_CardParse->CardType == C_PresetCardCommand)	/*参数预置卡*/
	{
		/*带Mac读参数预置卡中剩余金额并暂存到IC_InitM_PPMoney。
		下一条指令为对更新ESAM钱包文件，833E000008=购电金额长度+4Mac*/
		V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_MoneyInPSC, CO_PSCM_PPMoney, IC_InitM_PPMoney,
					0x83, 0x3e, 0x00, 0x00, 0x08, IC_CardNo);
		if(V_ucReturnData != C_OK)
		{
			return(V_ucReturnData);
		}

		PF_OneDataReversed(IC_InitM_PPMoney, V_ucbuf, CLChargeBal_Hex_Cent);
		PF_Buffer4ToUlong32(V_ucbuf, &pStr_CardParse->PPMoney, CLChargeBal_Hex_Cent);

		#if 0
		/*参数预制卡中只有购电金额，没有购电次数*/
		/*带Mac读参数预置卡中的购电次数并暂存到IC_InitM_PPNum
		下一条指令为对对ESAM充值，记录号03，记录文件号1，08=购电次数+Mac长度*/
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
	else if(pStr_CardParse->CardType == C_UserCardCommand)	/*用户卡*/
	{
		/*待mac读取钱包文件，暂存IC_PPMoney。下条指令为充值命令*/
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
函数原型：	uchar8	InF_SC_Backup_With_Mac(uchar8	V_ucType, uchar8 *pV_ucData)
功能描述：	带Mac读取参数保存
输入参数：	V_ucType					:读取类型，取值见备注
			pV_ucData				:缓冲区首地址
输出参数：	*pV_ucData				:读出的数据。大端模式。长度由Type定
返回参数：	C_OK/C_IC_NOIN_ERR
调用位置：
备    注：	V_ucType = (参考复旦微读出格式。参见BACKBUF)
			C_UPType_CurRate 	4字节(68 CMD Len1 Len2)当前费率电价+Mac，共137+4MAC
			C_UPType_BakRate	4字节(68 CMD Len1 Len2)备用费率电价+切换时间+Mac，共137+12(切换)+4MAC
			C_UPType_CurLadder	当前套阶梯+Mac，共89+4MAC
			C_UPType_BakLadder	备用套电价+切换时间+Mac，共89+12+4MAC
			调用本函数，pV_ucData大小一定开足。
*******************************************************************************/
uchar8	InF_SC_Backup_With_Mac(uchar8	V_ucType, uchar8 *pV_ucData)
{
	uchar8	V_ucReturnData;
	uchar8	V_ucbuf[8];			/*提供下面函数一个空指针*/

	switch(V_ucType)
	{
		case		C_UPType_Other:		/*其他参数*/
			V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_INS, CO_INS_Bak_3, pV_ucData,
						0x83, 0x2A, (0x80|C_F_ParmInf), CO_INS_Bak_3, CL_UPType_Other, V_ucbuf);
			break;
		case		C_UPType_CurRate:	/*当前费率电价,从文件0x68开始*/
			V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_Price_InPSC_InUse, 0, pV_ucData,
						0x83, 0x2A, (0x80|C_F_ElePrice), 0, CL_UPType_CurRate, V_ucbuf);
			break;
		case		C_UPType_BakRate:	/*备用套费率电价*/
			V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_PriceBak_InPSC_InUse, 0, pV_ucData,
						0x83, 0x2A, (0x80|C_F_ElePriceBak), 0, CL_UPType_BakRate, V_ucbuf);
			break;
		case		C_UPType_ChgRateClock:	/*费率电价切换时间-在指令文件中偏移10*/
			V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_INS, CO_INS_ChgRate, pV_ucData,
						0x83, 0x2A, (0x80|C_F_ParmInf), CO_INS_ChgRate, CL_UPType_ChgRateClock, V_ucbuf);
			break;
		case		C_UPType_CurLadder:		/*当前阶梯*/
			V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_Price_InPSC_InUse, CF_O_LadderBak, pV_ucData,
						0x83, 0x2A, (0x80|C_F_ElePrice), CF_O_LadderBak, CL_UPType_CurLadder, V_ucbuf);
			break;
		case		C_UPType_BakLadder:		/*备用套阶梯*/
			V_ucReturnData = SC_ReadBinFileMac(C_Card, C_FC_PriceBak_InPSC_InUse, CF_O_LadderBak, pV_ucData,
						0x83, 0x2A, (0x80|C_F_ElePriceBak), CF_O_LadderBak, CL_UPType_BakLadder, V_ucbuf);
			break;

		default:							/*到这里是不可能的，借用C_IC_NOIN_ERR错误*/
			V_ucReturnData = C_IC_NOIN_ERR;
			break;
	}
	return(V_ucReturnData);
}


/*******************************************************************************
函数原型：	uchar8	InF_SC_BackupW_With_Mac(uchar8 	V_ucType, uchar8 *pV_ucData)
功能描述：	带Mac写ESAM进行Mac验证
输入参数：	V_ucType				:读取类型，取值见备注
			*pV_ucData				:读出的数据。大端模式。长度由Type定
输出参数：	无
返回参数：	C_OK/C_IC_ESAM_RDWR_ERR
调用位置：
备    注：	V_ucType = (参考复旦微读出格式。参见BACKBUF)
			C_UPType_CurRate 	4字节(68 CMD Len1 Len2)当前费率电价+Mac，共137+4MAC
			C_UPType_BakRate	4字节(68 CMD Len1 Len2)备用费率电价+切换时间+Mac，共137+12(切换)+4MAC
			C_UPType_CurLadder	当前套阶梯+Mac，共89+4MAC
			C_UPType_BakLadder	备用套电价+切换时间+Mac，共89+12+4MAC
			调用本函数，pData大小一定开足。
*******************************************************************************/
uchar8	InF_SC_BackupW_With_Mac(uchar8 	V_ucType, uchar8 *pV_ucData)
{
	uchar8	V_ucReturnData;

	switch(V_ucType)
	{
		case		C_UPType_Other:		/*其他参数*/
			V_ucReturnData = WriteBinFileMac(C_ESAM, pV_ucData, C_F_ParmInf, CO_INS_Bak_3, CL_UPType_Other);
			if(V_ucReturnData == C_OK)	/*验证成功，且为其他参数，则刷新运行文件中2个变比,之前有1字节的保留字节和报警金额1和报警金额2，共9字节。*/
			{
				WriteBinFile(C_ESAM, pV_ucData + 9, C_F_OpInfo, CF_O_RatioCTInOP,(3 + 3) );
			}
			break;
		case		C_UPType_CurRate:		/*当前费率电价,从文件0x68开始*/
			V_ucReturnData = WriteBinFileMac(C_ESAM, pV_ucData, C_F_ElePrice, 0, CL_UPType_CurRate);
			break;
		case		C_UPType_BakRate:		/*备用套费率电价*/
			V_ucReturnData = WriteBinFileMac(C_ESAM, pV_ucData, C_F_ElePriceBak, 0, CL_UPType_BakRate);
			break;
		case		C_UPType_ChgRateClock:	/*费率电价切换时间-在指令文件中偏移10*/
			V_ucReturnData = WriteBinFileMac(C_ESAM, pV_ucData, C_F_ParmInf, CO_INS_ChgRate, CL_UPType_ChgRateClock);
			break;
		case		C_UPType_CurLadder:		/*当前阶梯*/
			V_ucReturnData = WriteBinFileMac(C_ESAM, pV_ucData, C_F_ElePrice, CF_O_LadderBak, CL_UPType_CurLadder);
			break;
		case		C_UPType_BakLadder:		/*备用套阶梯*/
			V_ucReturnData = WriteBinFileMac(C_ESAM,pV_ucData,C_F_ElePriceBak, CF_O_LadderBak, CL_UPType_BakLadder);
			break;
		default:							/*到这里是不可能的，借用C_IC_NOIN_ERR错误*/
			V_ucReturnData = C_IC_ESAM_RDWR_ERR;
			break;
	}

	return(V_ucReturnData);
}


/*******************************************************************************
函数原型：	void		InF_BackupData_Reversal(uchar8 V_ucType, uchar8 *pV_ucData)
功能描述：	将数据项颠倒，用于数据层写。
输入参数：	V_ucType				:读取类型，取值见备注
			*pV_ucData				:读出的数据。大端模式。长度由Type定
输出参数：	*pV_ucData				:颠倒后的数据。小端模式。长度由Type定
返回参数：	无
调用位置：
备    注：	Type = (参考复旦微读出格式。参见BACKBUF)
			C_UPType_Other	1字节备用报警金额1、2+电压、电流互感器变比+MAC   共19个字节
			C_UPType_CurRate 	4字节(68 CMD Len1 Len2)当前费率电价+Mac，共136
			C_UPType_BakRate	4字节(68 CMD Len1 Len2)备用费率电价+Mac，共136
			C_UPType_ChgRateClock		2套费率电价切换时间+Mac，共9字节
			C_UPType_CurLadder	当前套电价+Mac，共68字节
			C_UPType_BakRate		备用套电价+切换时间+Mac，共73字节
			调用本函数，pData大小一定开足。
*******************************************************************************/
void		InF_BackupData_Reversal(uchar8 V_ucType, uchar8 *pV_ucData)
{

	switch(V_ucType)
	{
		case		C_UPType_Other:		/*其他参数*/
			PF_OneDataReversed(&pV_ucData[CO_UPOther_Alam1], &pV_ucData[CO_UPOther_Alam1], CLAlam1_Money);
			PF_OneDataReversed(&pV_ucData[CO_UPOther_Alam2], &pV_ucData[CO_UPOther_Alam2], CLAlam2_Money);
			PF_OneDataReversed(&pV_ucData[CO_UPOther_Ratio_CT], &pV_ucData[CO_UPOther_Ratio_CT], CLRatio_Curr_Tran_Esam);
			PF_OneDataReversed(&pV_ucData[CO_UPOther_Ratio_VT], &pV_ucData[CO_UPOther_Ratio_VT], CLRatio_Vol_Tran_Esam);
			return;
		case		C_UPType_CurRate:		/*当前费率电价,从文件0x68开始*/
		case		C_UPType_BakRate:		/*备用套费率电价*/
			DataReversed(CBackUp_RateFF_Price, pV_ucData, C_RItem_Len_RateBak);
			return;
		case		C_UPType_ChgRateClock:	/*费率电价切换时间-在指令文件中偏移10*/
			PF_OneDataReversed(pV_ucData, pV_ucData, CLChange_Rate_Esam);
			return;
		case		C_UPType_CurLadder:		/*当前阶梯*/
			DataReversed(CBackUp_Ladder_Table, pV_ucData, (C_RITem_Len_LadderBak - 1) );
			return;
		case		C_UPType_BakLadder:		/*备用套阶梯*/
			DataReversed(CBackUp_Ladder_Table, pV_ucData, (C_RITem_Len_LadderBak - 1) );
			/*和当前阶梯比，多了1个切换时间*/
			PF_OneDataReversed(&pV_ucData[CO_UPLadderChgClock], &pV_ucData[CO_UPLadderChgClock], CLChange_Ladder_Esam);
			return;
		default:						/*到这里是不可能的，借用C_IC_NOIN_ERR错误*/
			return;
	}
}


/*******************************************************************************
函数原型：uchar8	InF_SC_CardExtAuth(uchar8	*pV_ucCardNo)
功能描述：外部认证
输入参数：pV_ucCardNo	:卡序列号，小端，固定8字节
输出参数：无
返回参数：C_OK/C_IC_NOIN_ERR/C_IC_ESAM_RDWR_ERR/C_IC_EXAUTH_ERR
调用位置：
备    注：
*******************************************************************************/
uchar8	InF_SC_CardExtAuth(uchar8	*pV_ucCardNo)
{
	uchar8		V_ucRand8[10];
	uchar8		V_ucSendBuf[CL_Send_InIC];
	uchar8		V_ucReponseBuf[CL_Response_InIC];
	uchar8		V_ucDataLen;
	ushort16	V_usDataLen;

	/*让卡产生Rand8*/
	PF_CopyDataBytes((uchar8 * )TB_GetChallenge, V_ucSendBuf, CLen_TB_ESAM_4);
	V_ucSendBuf[CLen_TB_ESAM_4] = 8;
	V_ucDataLen = 8;
	PF_OneDataReversed(V_ucSendBuf,GV_7816CMD.Header, CL_7816Header);		/*操作之前保存命令头*/
	GV_7816CMD.SW1_2 = INF_SendData_7816_Card(V_ucSendBuf, CLen_TB_ESAM_Le, V_ucRand8, &V_ucDataLen);
	if(GV_7816CMD.SW1_2 != C_Security_CommandOk)	/*返回SW !=9000*/
	{
		return(C_IC_NOIN_ERR);
	}

	/*加密得到密文(以前2步合并成1步)*/
	/*800808020020+cardreset8+rand8*/
	PF_CopyDataBytes((uchar8 * )TB_AuthDistributedkey_698, V_ucSendBuf, CLen_TB_ESAM_Lc_698_Esam);
	PF_OneDataReversed(pV_ucCardNo, &V_ucSendBuf[CLen_TB_ESAM_Lc_698_Esam], CL_CardNo);	/*分散因子为卡号*/
	PF_CopyDataBytes(V_ucRand8, &V_ucSendBuf[CLen_TB_ESAM_Lc_698_Esam + CL_CardNo], 8);
	V_usDataLen = CL_Response_InIC;
	GV_7816CMD.SW1_2 = INF_SendData_698_Esam(V_ucSendBuf, (CLen_TB_ESAM_Lc_698_Esam + CL_CardNo + 8), V_ucReponseBuf, &V_usDataLen);
	if( (GV_7816CMD.SW1_2 != C_Security_CommandOk) && ( (GV_7816CMD.SW1_2 & C_Resp_61XXType)!= C_Security_ProcessOk) )
	{
		return(C_IC_ESAM_RDWR_ERR);
	}


	/*外部认证00 82 00 02 08 + dest8 注意这里P2要更改成02，密钥索引*/
	/*InF_Delay_us(3000);*/
	PF_CopyDataBytes((uchar8 * )TB_IRExtAuth, V_ucSendBuf, CLen_TB_ESAM_Lc);
	V_ucSendBuf[3] = 2;				/*P2=2*/
	PF_CopyDataBytes(V_ucReponseBuf,&V_ucSendBuf[CLen_TB_ESAM_Lc],8);
	PF_OneDataReversed(V_ucSendBuf, GV_7816CMD.Header, CL_7816Header);		/*操作之前保存命令头*/
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
函数原型：uchar8	Is_Meter_Num_OK(uchar8	*pV_ucFlag)
功能描述：判断输入表号是否和数据层表号一致
输入参数：*pV_ucFlag	:表号，大端模式固定6字节
输出参数：无
返回参数：C_OK/C_Error
调用位置：
备    注：
*******************************************************************************/
uchar8	InF_SC_Meter_Num_OK(uchar8 *pV_ucMeterNum)
{
	uchar8		V_ucbuf1[CLMeter_Num];
	uchar8		V_ucbuf2[CLMeter_Num];
	ushort16	V_usDataLen = CLMeter_Num;
	ushort16	V_usDataEnCode;

	/*表号大端改成小端*/
	PF_OneDataReversed(pV_ucMeterNum, V_ucbuf1, CLMeter_Num_Esam);

	/*读数据层表号*/
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
函数原型：uchar8	InF_SC_Is_UserCardNull(uchar8	*pV_ucFlag)
功能描述：判断用户卡是否为空
输入参数：
输出参数：*pV_ucFlag				:为空标志，C_OK表示空，C_Error表示非空
返回参数：C_OK/C_IC_NOIN_ERR
调用位置：
备    注：按复旦微判断返写文件中电流互感器值为全0，则为空
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
	if( (V_ucReponseBuf[CF_O_OPI_RWRClock] != 0)			/*68 CMD Len中有一个字节不为0，表明返写文件不为空698的发完用户卡，*/
		|| (V_ucReponseBuf[CF_O_OPI_RWRClock + 1] != 0)		/*	68 11 00 2B 00 ...00 CS 16(不适用于原来的判断方法) */
		|| (V_ucReponseBuf[CF_O_OPI_RWRClock + 2] != 0)
		|| (V_ucReponseBuf[CF_O_OPI_RWRClock + 3] != 0)
		|| (V_ucReponseBuf[CF_O_OPI_RWRClock + 4] != 0) )
	{
		*pV_ucFlag = C_Error;
	}
	else	/*返写文件为空*/
	{
		*pV_ucFlag = C_OK;
	}
	return(C_OK);
}


/*******************************************************************************
函数原型：uchar8	InF_SC_GetCustNumWithMac_UseCard(uchar8 *pCustNum)
功能描述：带mac读取用户卡中的客户编号
输入参数：
输出参数：pV_ucCustNum				:客户编号，固定10字节小端模式
返回参数：C_OK/C_IC_NOIN_ERR
调用位置：
备    注：
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
函数原型：uchar8	InF_SC_WR_UCReturnFile(uchar8	*pV_ucCardNo)
功能描述：返写用户卡返写文件
输入参数：pV_ucCardNo				:卡序号，固定8字节，小端模式
输出参数：无
返回参数：C_OK/C_IC_NOIN_ERR/C_IC_ESAM_RDWR_ERR
调用位置：
备    注：
*******************************************************************************/
uchar8	InF_SC_WR_UCReturnFile(uchar8	*pV_ucCardNo)
{
	uchar8	V_ucbuf[CLen_S_BufMaxLen];
	uchar8	V_ucReturnData;

	/*写二进制文件	*/
	V_ucReturnData = SC_ReadRunFileMac(C_ESAM, C_F_OpInfo, CF_O_OPI_Start, V_ucbuf,
		0x04, 0xD6,(0x80|C_FC_WRBackInUseCard), CF_O_OPI_Start, (CL_OPI + C_MacLen), pV_ucCardNo);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}

	/*返写*/
	V_ucReturnData = WriteBinFileMac(C_Card, V_ucbuf, C_FC_WRBackInUseCard, CF_O_OPI_Start, CL_OPI + C_MacLen);

	return(V_ucReturnData);
}


/*******************************************************************************
函数原型：	ushort16	InF_S_WR_ReturnFile(uchar8 *pV_ucData, uchar8 V_ucLength)
功能描述：	写退费文件，进行解密
输入参数：	*pV_ucData			:密文
			V_ucLength		:长度
输出参数：	*pV_ucData			:解密后的(明文)退费金额+mac，固定8字节，小端模式
返回参数：	C_OK/C_SERR_ESAM_VF/C_SERR_OtherErr
调用位置：
备    注：	pData必须保证8字节空间
*******************************************************************************/
ushort16	InF_S_WR_ReturnFile(uchar8 *pV_ucData, uchar8 V_ucLength)
{
	uchar8	V_ucbuf[20];
	uchar8	V_ucReturnData;

	/*长度超出处理范围*/
	if( (V_ucLength > 20) || (V_ucLength < 4) )		/*长度错误*/
	{
		return(C_SERR_OtherErr);
	}

	/*数据颠倒---符合二类参数的特点，所有数据，密文和Mac分开颠倒*/
	PF_OneDataReversed(pV_ucData, V_ucbuf, (V_ucLength - C_MacLen) );
	PF_OneDataReversed(&pV_ucData[V_ucLength - C_MacLen], &V_ucbuf[V_ucLength - C_MacLen], C_MacLen);

	/*带Mac写二进制文件(退费文件，文件号0C)*/
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
	/*读二进制文件明文+mac*/
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
函数原型：	ushort16	InF_S_OPMoneyFile_Return(uchar8 *pV_ucData)
功能描述：	完成钱包退费验证
输入参数：	*pV_ucData				:退费金额+Mac，8字节，小端
输出参数：	无
返回参数：	C_OK/C_SERR_ESAM_VF/C_SERR_OtherErr
调用位置：
备    注：	本动作ESAM进行了退费Mac验证，同时判断了购电次数，
			购电次数变化1次，仅允许退费1次
			*pV_ucData维持不变
*******************************************************************************/
ushort16	InF_S_OPMoneyFile_Return(uchar8 *pV_ucData)
{
	uchar8		V_ucSendBuf[CL_Send_InIC];
	uchar8		V_ucResponseBuf[CL_Response_InIC];
	uchar8		V_ucDataLen = CL_Response_InIC;
	ushort16	V_usReturnData;

	/*获取命令头*/
	V_ucSendBuf[0] = 0x84;			/*带Mac扣款*/
	V_ucSendBuf[1] = 0x30;
	V_ucSendBuf[2] = 0x02;			/*记录号*/
	V_ucSendBuf[3] = 0x0C;			/*bit7-3文件号，1号钱包文件,bit2-0=100表示当前记录号为P1*/
	V_ucSendBuf[4] = 0x08;			/*长度*/

	/*补充数据*/
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
	else	/*这里缺少命令发送：00C0000008 返回：剩余金额+本次交易金额+9000 */
	{
		return(C_OK);
	}
}


/*******************************************************************************
函数原型：	ushort16	InF_S_Software_Campare(uchar8 *pV_ucData, uchar8 *pV_ucFactorData, uchar8 V_ucKeyNum)
功能描述：	完成软件比对数据加密
输入参数：	*pV_ucData	:地址pData待加密数据，
			pV_ucFactorData:分散因子地址
			V_ucKeyNum:密钥索引
输出参数：	*pV_ucData加密后数据
返回参数：	C_OK/C_SERR_ESAM_VF/C_SERR_OtherErr
调用位置：
备    注：
*******************************************************************************/
ushort16	InF_S_Software_Campare(uchar8 *pV_ucData, uchar8 *pV_ucFactorData, uchar8 V_ucKeyNum)
{
	uchar8		V_ucbuf[CLen_S_BufMaxLen], V_ucDataLen;
	ushort16	V_usReturnData16;

	/*让ESAM对分散因子进行分散*/
	V_ucDataLen = CLen_S_BufMaxLen;
	PF_CopyDataBytes((uchar8 *)TB_AuthDistributedkey, &V_ucbuf[0], CLen_TB_ESAM_Lc);		/*获取命令头*/
	V_ucbuf[3] = V_ucKeyNum;	/*替换密钥索引*/
	PF_CopyDataBytes(pV_ucFactorData, &V_ucbuf[CLen_TB_ESAM_Lc], CL_Auth_Dis_factor);		/*加入分散因子，没有数据颠倒问题	*/
	V_usReturnData16 = INF_SendData_7816_Esam(&V_ucbuf[0], (CLen_TB_ESAM_Lc + CL_Auth_Dis_factor), &V_ucbuf[0], &V_ucDataLen);
	if( (V_usReturnData16 !=C_Security_CommandOk) && ( (V_usReturnData16 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_Error);
	}

	/*用临时分散密钥加密数据*/
	V_ucDataLen = CLen_S_BufMaxLen;
	PF_CopyDataBytes((uchar8 *)TB_SoftwareCampare, &V_ucbuf[0], CLen_TB_ESAM_Lc);			/*获取命令头*/
	PF_CopyDataBytes(pV_ucData, &V_ucbuf[CLen_TB_ESAM_Lc], CL_SoftwareCampare_Data);		/*加入待加密数据，没有数据颠倒问题*/
	V_usReturnData16 = INF_SendData_7816_Esam(&V_ucbuf[0],(CLen_TB_ESAM_Lc + CL_SoftwareCampare_Data), &V_ucbuf[0], &V_ucDataLen);
	if( (V_usReturnData16 != C_Security_CommandOk) && ( (V_usReturnData16 & C_Resp_61XXType) != C_Security_ProcessOk) )
	{
		return(C_Error);
	}

	/*读响应*/
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
函数原型：	ushort16	InF_S_Software_Campare_698(uchar8 *pV_ucData, uchar8 *pV_ucFactorData, uchar8 V_ucKeyNum, ushort16 *pV_usDataLen, uchar8 *pV_ucRN_Data)
功能描述：	完成698软件比对数据加密
输入参数：	*pV_ucData			:地址pData待加密数据，
			pV_ucFactorData	:分散因子地址
			V_ucKeyNum	:密钥索引
输出参数：	*pV_ucData加密后数据
返回参数：	C_OK/C_SERR_ESAM_VF/C_SERR_OtherErr
调用位置：
备    注：
*******************************************************************************/
ushort16	InF_S_Software_Campare_698(uchar8 *pV_ucData, uchar8 *pV_ucFactorData, uchar8 V_ucKeyNum, ushort16 *pV_usDataLen, uchar8 *pV_ucRN_Data)
{
	uchar8		V_ucbuf[300];
	ushort16	V_usReturnData16, V_usDataLen, V_usDataLen2;

	V_usDataLen = 300;

	/*获取命令头*/
	V_ucbuf[0] = 0x80;
	V_ucbuf[1] = 0x0A;
	V_ucbuf[2] = 0x48;
	V_ucbuf[3] = V_ucKeyNum;	/*密钥索引*/
	V_usDataLen2 = *pV_usDataLen + CL_Auth_Dis_factor + CL_Auth_Rand1_SoftCam;
	PF_Ushort16ToBuffer2(&V_ucbuf[4], &V_usDataLen2);		/*lc*/
	PF_OneDataReversed(&V_ucbuf[4], &V_ucbuf[4], 2);
	PF_CopyDataBytes(pV_ucFactorData, &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam], CL_Auth_Dis_factor);	/*加入分散因子，暂时采用比对因子作为分散因子，技术资料有疑问	*/
	/*加入随机数，取因子起始地址和数据起始地址，高位补0*/
	PF_CopyDataBytes_698(pV_ucRN_Data, &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam + CL_Auth_Dis_factor], CL_Auth_Rand1_SoftCam);	/*加入随机数*/

	PF_CopyDataBytes_698(pV_ucData, &V_ucbuf[CLen_TB_ESAM_Lc_698_Esam + CL_Auth_Dis_factor + CL_Auth_Rand1_SoftCam], *pV_ucData);	/*加入待加密数据，没有数据颠倒问题	*/
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
函数原型：uchar8 InF_IS_UpdateMInEsamTimer(void)
功能描述：当前是否处于状态查询15min延时判断函
输入参数：无
输出参数：无
返回参数：C_OK:当前不处于15min延时期间可以更新EE和ESAM数据,C_Error当前处于延时期间不能更新EE和ESAM数据
调用位置：
备    注：
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


