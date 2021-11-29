/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Card.c
Version:       V1
Author:        jiangzs
Date:          2014-3-31
Description:   �������ļ�
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


#include    "Card.h"
#include    "Timer.h"



/*******************************************************************************
����ԭ�ͣ�uchar8	InF_Card_Message(Str_Msg_Parameter * pStr_Msg_Parameter)
������������������Ϣ��������
���������*pStr_Msg_Parameter:			��Ϣ�ṹ��		
�����������
���ز�����C_OK/C_Error
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	InF_Card_Message(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	uchar8	*pV_ucParm;
	
	/*������ȷ�������ͣ�磬��ôֱ���˳�������C_OK	*/
	if(pStr_Msg_Parameter->PowerFlag == C_PowerFalling)
	{
		return(C_OK);
	}
	
	/*�ж���Ϣ���������Ƿ���ȷ*/
	pV_ucParm = pStr_Msg_Parameter->Parameter;
	if(*pV_ucParm == Pt_CardFlag)
	{
		SV_IC_SafeFlag = 0;
		MF_Card_Message();
		return(C_OK);
	}
	else
	{
		SV_IC_SafeFlag = 0;
		return(C_Error);
	}
	
}


/*******************************************************************************
����ԭ�ͣ�void		MF_Card_Message(void)
������������������Ϣ��������
�����������
�����������
���ز�������
����λ�ã�
��    ע����ɿ����༰�����쳣�忨�¼���¼����������ɰ�ȫ�淶��¼A.1.2 a/b/h/i����
*******************************************************************************/
void	MF_Card_Message(void)
{
	StrCardParse	pStr_CardParse;	
	ushort16		V_usTemp16 = 0;
	
	pStr_CardParse.PreMoneyClock = 0;				/*Ĭ�Ϲ���ǰʣ�����ʾ*/
	
	/*	InF_SwithPeripherals(C_TripLed,C_On);*/  /*test*/

	SV_IC_SafeFlag = SV_IC_SafeFlag | C_W_SafeFlag_1;
	/*�ж��Ƿ�Ϊ���ر���Ϊ���ر�ֱ���˳�*/
	if(C_Meter_Type != C_L_SmartMeter)
	{
		SV_IC_SafeFlag =0;
		return;
	}	
	/*�ж��Ƿ������п�*/
	if(InF_GetPeripheralStatus(C_CardStatus) != C_Valid)
	{
		SV_IC_SafeFlag =0;
		
		return;
	}
	/*�����쳣�忨�¼���¼������ʼ��*/
	MF_Init_IC_ErrEvent(&pStr_CardParse);

	/*MF_Card_SendMsgToDisp(C_HoardingSign,C_NotDisplay,CCDsp_Duration_Alway);	*/ /*����ȡ�����ڻ���ʾ�������ϴ�10s�ڣ��忨�ڻ��쳣��ʾ*/

	/*�жϵ�Դ�Ƿ�����*/
	if (InF_JudgeVolage_Relay() == C_VoltageOk)				/*��ѹ����*/
	{
		/*����ʾ������*/
		/*MF_Card_SendMsgToDisp(C_ReadCardSign,C_AlwaysDisplay,CCDsp_Duration_Alway);*/	/*��ʾ����*/
		/*MF_Card_SendMsgToDisp(C_DoingSign,C_AlwaysDisplay,CCDsp_Duration_Alway);*/		/*��ʾ��*/
		MF_Card_SendMsgToDisp(C_FailSign, C_NotDisplay, CCDsp_Duration_Alway);				/*����ʾʧ��*/
		MF_Card_SendMsgToDisp(C_SuccessSign, C_NotDisplay, CCDsp_Duration_Alway);			/*����ʾ�ɹ�*/
		/*��������60s������΢���е�ѹ֮ǰ��ִ�С�*/ 
        /*SF_ReadDispBuff(GV_ucDispArray); */                                         		/*��ȡҺ��״̬*/
        MF_Card_SendMsgToDisp(C_BackLED, C_AlwaysDisplay, CCDsp_Duration_60s);
		InF_OprateTimer(C_StartTimer, 10000);			/*����10s��ʱ����Ϊ�忨�����ж�ʱʹ��*/

		pStr_CardParse.IC_ErrEvent[CO_CE_ErrStatus] = MF_Card_Esam_Proc(&pStr_CardParse);
				
		/*��Ƭͣ��*/
		InF_Deactivation_7816_Card();

		MF_Card_SendICMsg();			/*�����⿨���������̵�����բ������Ϣ*/

	}
	else	/*��ѹ����*/
	{

		pStr_CardParse.IC_ErrEvent[CO_CE_ErrStatus] = C_IC_VLOW_ERR;
		MF_Card_SendICMsg();			/*�͵�ѹҲ�����忨��Ϣ�������ѹ�ָ����բ*/
	}
	
	/*�쳣�忨��¼��Һ��������ʾ*/	
	if(pStr_CardParse.IC_ErrEvent[CO_CE_ErrStatus] != C_OK)	/*����������д���*/
	{
		MF_Write_IC_ErrEvent(&pStr_CardParse);				/*д�쳣�忨�¼���¼*/
		
		/*MF_Card_SendMsgToDisp(C_ReadCardSign, C_AlwaysDisplay, CCDsp_Duration_10s);*/	/*����10s*/
		/*MF_Card_SendMsgToDisp(C_DoingSign, C_NotDisplay, CCDsp_Duration_Alway);*/		/*ȡ����*/
		MF_Card_SendMsgToDisp(C_SuccessSign, C_NotDisplay, CCDsp_Duration_Alway);			/*ȡ���ɹ�*/
		MF_Card_SendMsgToDisp(C_FailSign, C_AlwaysDisplay, CCDsp_Duration_10s);			/*����10s*/
		InF_BeeperOut(C_TwinkleDisplay, 750, 250);			/*����������125ms���3��,��ʱ��750������250*/
		MF_Card_LCDView(CType_IC_Err, &pStr_CardParse);		/*��ʾErr-XX*/
		V_usTemp16 = InF_OprateTimer(C_GetTimer, 0);
		/*�����⾫ȷ��ʱ*/
		V_usTemp16 = CCDsp_Duration_60s - ( (10000 - V_usTemp16) / 1000);
		MF_Card_SendMsgToDisp(C_BackLED, C_AlwaysDisplay, V_usTemp16);
		InF_WriteCardStatus(C_CardStatusERR);
	}
	else	/*һ����������ʾ������ʣ����*/
	{
		/*MF_Card_SendMsgToDisp(C_ReadCardSign,C_AlwaysDisplay,CCDsp_Duration_10s);*/	/*����10s*/
		/*MF_Card_SendMsgToDisp(C_DoingSign,C_NotDisplay,CCDsp_Duration_Alway);*/		/*ȡ����*/
		MF_Card_SendMsgToDisp(C_FailSign, C_NotDisplay, CCDsp_Duration_Alway);		    /*ȡ��ʧ��*/
		MF_Card_SendMsgToDisp(C_SuccessSign, C_AlwaysDisplay, CCDsp_Duration_10s);		/*�ɹ�10s*/

		InF_BeeperOut(C_AlwaysDisplay, 650, 0);		/*����������650ms*/
		if(pStr_CardParse.PreMoneyClock != 0)			/*����ǰʣ������ʾʱ�����¶�ʱ�ˣ���ȡ��ȷ��2s��ʱ*/
		{
			do
			{
				V_usTemp16 = InF_OprateTimer(C_GetTimer, 0);
				if( (pStr_CardParse.PreMoneyClock - V_usTemp16) >= 2000)
				{
					break;							/*����ǰʣ������ʾ��ʱ2s����*/
				}
			}while(V_usTemp16 != 0);
		}
		MF_Card_LCDView(CType_RemainMoney, &pStr_CardParse);
		/*�����⾫ȷ��ʱ*/
		V_usTemp16 = CCDsp_Duration_60s - ( (10000 - V_usTemp16) / 1000);
		MF_Card_SendMsgToDisp(C_BackLED, C_AlwaysDisplay, V_usTemp16);
		InF_WriteCardStatus(C_CardStatusOK);
	}
	SV_IC_SafeFlag = 0;
	
	/*	InF_SwithPeripherals(C_TripLed, C_On);*/	/*test*/
}


/*******************************************************************************
����ԭ�ͣ�	uchar8		MF_Card_Esam_Proc(StrCardParse	*pStr_CardParse)
����������	��Ƭ����
���������	*pStr_CardParse				:������ͨ�ýṹ��
���������	*pStr_CardParse				:������ͨ�ýṹ��
���ز�����	C_OK/�忨���̴����룬��C_IC_KER_ERR�ȶ���
����λ�ã�
��    ע��	��������Ҫ�ο���ȫ�淶��¼A.1.2-c/d/e/f/g����
			ע��������ǲ�����Ƭ��ESAM�����з�����������ͷ��SWΪȫ0(�����ԣ�����΢Ҳ��ô��)
			����΢��C_IC_ESAM_RDWR_ERR/C_IC_NOFX_ERR/C_IC_MAC_ERR/C_IC_NOIN_ERR/C_IC_EXAUTH_ERR
			�⼸������¼�¼��������ͷ
*******************************************************************************/
uchar8		MF_Card_Esam_Proc(StrCardParse		*pStr_CardParse)
{
	uchar8	V_ucReturnData;

	/*���ȶԿ�Ƭ���и�λ*/
	if(InF_S_ColdRestCard(IC_CardNo) != C_OK)
	{
		return(C_IC_IC_RST_ERR);
	}
	
	/*��ζ�ESAM���и�λ*/
	/*�Ͽ�Ӧ������,�临λESAM*/
	V_ucReturnData = INF_RELEASE_Service_Deal_Card();
	if(V_ucReturnData != C_OK)
	{
		return(C_IC_ESAM_RST_ERR);
	}
	
	/*ֹͣԶ�������֤��Ч������Զ�̱�̼�¼���ơ�*/
	INF_StopCommProgState();
	
	/*ѡ��3F00,DF01 --����΢��ִ��ѡ��DF01*/
	V_ucReturnData = InF_S_SelectFile(C_Card, C_F_MF);
	if(V_ucReturnData != C_OK)
	{
		/*return(V_ReturnData);*/
		return(C_IC_IC_RST_ERR);	/*�ܷѿذ�ȫ����(�û�����������)�޸�*/
	}
	V_ucReturnData = InF_S_SelectFile(C_Card, C_F_MainDir);
	if(V_ucReturnData != C_OK)
	{
		/*return(V_ReturnData);*/
		return(C_IC_IC_RST_ERR);	/*�ܷѿذ�ȫ����(�û�����������)�޸�*/
	}

	#if 0
	/*ѡ��ESAM3F00 --�����踴��΢��ִ��*/
	V_ReturnData = InF_S_SelectFile(C_ESAM,C_F_MF);
	if(V_ReturnData != C_OK)
	{
		return(V_ReturnData);
	}
	#endif	

	/*test ��ֹ����err-35����,������FF68*/
	InF_Delay_us(1000);
	
	/*��ȡָ���ļ��п�Ƭ���ͼ���Ч���ݳ���*/
	V_ucReturnData = InF_SC_RDBinFileNoMac(C_Card, C_FC_INS, CO_INS_Start, 4, pStr_CardParse->IC_File);
	if(V_ucReturnData != C_OK)	/*����*/
	{
		if(GV_7816CMD.SW1_2 == C_Security_ParameterError)	/*6B00������΢��Ϊ����Ч��Ƭ*/
		{
			return C_IC_NOFX_ERR;	/*δ���п�Ƭ*/
		}
		else	/*����������Ϊ�Ƕ�д��Ƭʧ��*/
		{
			return C_IC_NOIN_ERR;	/*������ƬͨѶ����(��д��Ƭʧ��)*/
		}
	}
	else	/*��ȷ��*/
	{
		pStr_CardParse->CardType = IC_INS_CMD;	/*���濨Ƭ����*/
		
		if(IC_INS_CMD == C_UserCardCommand) 	/*�û���*/
		{
			InF_Card_DispDynamicSign();	/*��ʾ----------*/
			V_ucReturnData = MF_UserCard_Esam_Proc(pStr_CardParse);
		}
		else if(IC_INS_CMD == C_PresetCardCommand)	/*����Ԥ�ÿ�*/
		{		
			InF_Card_DispDynamicSign();	/*��ʾ----------*/
			V_ucReturnData = MF_PreSetCard_Esam_Proc(pStr_CardParse);
		}
		else	/*��Ƭ���ʹ���*/
		{
			V_ucReturnData = C_IC_TYPE_ERR;
		}
		
		return(V_ucReturnData);
	}
}


/*******************************************************************************
����ԭ�ͣ�uchar8		MF_PreSetCard_Esam_Proc(StrCardParse	*pStr_CardParse)
������������ɲ���Ԥ�ÿ��Ĵ���
���������*pStr_CardParse				:������ͨ�ýṹ��
���������*pStr_CardParse				:������ͨ�ýṹ��
���ز�����C_OK/�忨���̴����룬��C_IC_KER_ERR�ȶ���
����λ�ã�
��    ע����Ҫ�ο���ȫ�淶��¼A.1.3
*******************************************************************************/
uchar8		MF_PreSetCard_Esam_Proc(StrCardParse	*pStr_CardParse)
{
	uchar8		V_ucReturnData;
	ushort16	V_usTemp16;
	uchar8		V_ucbuf[10], V_ucFlag;
	
	/*����Ԥ�ÿ�Ҫ��������Կ�����ǹ�Կ��
	A.1.3��Ҫ�󸴵�΢Ҳ���������֤ǰ�ж�*/
	if(InF_JudgeKeyStatus() != C_StateOfTestKey)	/*���е�ȫ��Ϊ��ʽ��Կ*/
	{
		return(C_IC_KER_ERR);
	}

	/*�����֤*/
	V_ucReturnData = InF_SC_L_Auth(IC_CardNo);
	if( V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}

	SV_IC_SafeFlag = SV_IC_SafeFlag | C_W_SafeFlag_2;
	/*�ٶ�ȡָ���ļ����ж�*/
	V_ucReturnData = InF_SC_RDBinFileNoMac(C_Card, C_FC_INS, 0, (CL_PresetCardCMD + 6), pStr_CardParse->IC_File);
	if(V_ucReturnData != C_OK)	/*������,ǰ���жϹ�6B00�����ﲻ�ж���*/
	{
		return(V_ucReturnData);
	}

	if(InF_SC_Judge_CardFile(pStr_CardParse->IC_File) != C_OK)	/*��Ƭ�ļ���ʽ����*/
	{
		return(C_IC_FORMAT_ERR);
	}

	/*����������±�־��*/
	pStr_CardParse->UpdateFlag = IC_INS_UpdataPFlag;
	/*��ESAM����Rand1-4������Mac����*/
	V_ucReturnData = InF_SC_GenerateRandToCalMac(C_ESAM, C_Length_4);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);			/*����ʵ���Ͽɲ��С�*/
	}

	/*��Ǯ���ļ���Ԥ�ý��,698����Ԥ�ƿ���Ǯ���ļ���û�й������*/
	V_ucReturnData = InF_SC_Get_MFile_Card(pStr_CardParse);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);	
	}

	#if 0
	if(pStr_CardParse->PPNum != 0)	/*����Ԥ�ÿ��й�����������Ϊ0���ͱ���!*/
	{
		return(C_IC_TIMES_ERR);
	}
	#endif

	if(pStr_CardParse->PPMoney > 99999999)	/*Ԥ�ý��ܴ���99999999�֣������жϳ��ڻ�*/
	{
		return(C_IC_OVERMAX_ERR);			/*ʵ�ʲ����ܣ�����Ϊ��ֹ������ҡ�*/
	}
	
	/*��ֵ�����Mac��֤*/
	V_usTemp16 = InF_S_InitMoney(C_Msg_Card, pStr_CardParse->IC_File);
	if(V_usTemp16 != C_OK)
	{
		if(V_usTemp16 == C_SERR_ESAM_VF)	/*����΢����û��Mac����*/
		{
			return(C_IC_MAC_ERR);
		}
		else
		{
			return(C_IC_NOIN_ERR);
		}
	}

	/*Ǯ����ʼ���ɹ������ԶԵ��ܱ���г�ʼ������(�ڲ���������ɺ����)*/
	SV_IC_SafeFlag = SV_IC_SafeFlag | C_W_SafeFlag_3;
	
    memset(V_ucbuf, 0, CL_UserCardNo);
	InF_Write_Data(C_Msg_Card, C_UserCardNo, V_ucbuf, CL_UserCardNo, SV_IC_SafeFlag);	/*�忨�ţ�ȡ���û�������*/

	InF_DealWith_L_R_OAAFlag(C_Set_Method_R, C_HaveNoOpenAnAccount);					/*��2������״̬*/

	InF_DealWith_L_R_OAAFlag(C_Set_Method_L, C_HaveNoOpenAnAccount);

	InF_UpdateAccountStateInMeterStatus3();												/*ˢ��״̬��3�п���״̬*/

	/*������Ҫ��������Ϣ,�����ۣ����㲥����*/
	V_ucbuf[0] = Pt_MeterClear;
	MF_Card_SendMsg(V_ucbuf, (Pt_MeterClear_Len + 1), C_Msg_BroadcastAddress);
	
	/*���ݲ������±�־���������в�����ȡ��
	mac��֤��д���ݲ㼰����¼��������ϱ�*/
	V_ucReturnData = MF_IC_UpdateParm(pStr_CardParse);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}

	InF_S_GetMeterNum_ReworkDL();	/*�����Ԥ�ƿ�����¿ͻ����Ϊ0��ֱ��ͬ���ͻ����*/

	/*�����ݲ���г�ʼ������д�����¼
	���������ϱ�-���ڲ����Ԥ�ÿ����ڹ�Կ״̬���ǲ����ϱ��ġ�*/
	SV_Comm_Parse_Local.SafeControlFlag = C_W_SafeFlag;
	INF_WrClearAllRecord(IC_CardNo, SV_IC_SafeFlag);

	/*���ݲ��ֵ�����¼*/
	/*InF_MoneyToPurchase_Init(pStr_CardParse->PPMoney,SV_IC_SafeFlag);*/

	/*д���һ�ι����¼
	��ʼ��Ǯ��д�����¼�����й���ǰʣ����д��0
	������Ϊ����Ԥ�ý������ܽ��������壬
	��1�ι����������Ϊ0��
	���Կ��Բ�����1�μ�¼�й����ܽ��+���ι�����*/
	V_ucFlag = C_Money_Init;
	InF_WRPre1PowerPurchaseRecord(pStr_CardParse->PPMoney, SV_IC_SafeFlag, V_ucFlag);

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�uchar8		MF_UserCard_Esam_Proc(StrCardParse	*pStr_CardParse)
��������������û����Ĵ���
���������*pStr_CardParse				:������ͨ�ýṹ��
���������*pStr_CardParse				:������ͨ�ýṹ��
���ز�����C_OK/�忨���̴����룬��C_IC_KER_ERR�ȶ���
����λ�ã�
��    ע����Ҫ�ο���ȫ�淶��¼A.1.4
*******************************************************************************/
uchar8		MF_UserCard_Esam_Proc(StrCardParse	*pStr_CardParse)
{
	uchar8		V_ucReturnData;
	ushort16	V_usDataLen;
	uchar8		V_ucbuf[10];
	uchar8		V_ucErrStatus;
	ushort16	V_usDataCode;

/*�û���Ҫ�����е���ԿΪ˽Կ--0514-62
	V_ReturnData = Is_AllOfficialKey();*/
	if(InF_JudgeKeyStatus() != C_StateOfOfficialKey)
	{
		return(C_IC_KER_ERR);
	}
	
/*ִ��ESAM�����ݲ�ʣ�����ͬ��*/
	V_usDataLen = CLChargeBal_Hex_Cent;
	if( InF_GetData_ObjectManage(CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, &V_usDataCode) == C_OK )
	{
		InF_S_UpdataChargeBalInESAM(V_ucbuf);
	}
	
	/*�����֤*/
	V_ucReturnData = InF_SC_L_Auth(IC_CardNo);
	if( V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}
	SV_IC_SafeFlag = SV_IC_SafeFlag | C_W_SafeFlag_2;
	
	/*��ȡָ���ļ����ж�*/
	V_ucReturnData = InF_SC_RDBinFileNoMac(C_Card, C_FC_INS, 0, (CL_UserCardCMD + 6), pStr_CardParse->IC_File);
	if(V_ucReturnData != C_OK)	/*������,ǰ���жϹ�6B00�����ﲻ�ж���*/
	{
		return(V_ucReturnData);
	}
	if(InF_SC_Judge_CardFile(pStr_CardParse->IC_File) != C_OK)		/*��Ƭ�ļ���ʽ����*/
	{
		return(C_IC_FORMAT_ERR);
	}
	/*����������±�־������ݴ�IC_File��*/
	pStr_CardParse->UpdateFlag = IC_INS_UpdataPFlag;
	pStr_CardParse->UserCardType = IC_INS_UseC_Type;
	
	/*�ⲿ��֤*/
	V_ucReturnData = InF_SC_CardExtAuth(IC_CardNo);
	if( V_ucReturnData!= C_OK)
	{
		return(V_ucReturnData);
	}
	
	/*��ESAM����Rand1-4������Mac����*/
	V_ucReturnData = InF_SC_GenerateRandToCalMac(C_ESAM, C_Length_4);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);			/*����ʵ���Ͽɲ��С�*/
	}
	
	/*�жϱ���Ƿ���ȡ������IC_File�������ˡ�*/
	if(InF_SC_Meter_Num_OK(IC_INS_UseC_MeterNum) != C_OK)
	{
		return(C_IC_ID_ERR);
	}
	
	/*��ȡ�û���Ǯ���ļ�,��Mac ���ļ�������IC_File��,��PPMoney PPNum��*/
	V_ucReturnData = InF_SC_Get_MFile_Card(pStr_CardParse);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}
	SV_IC_SafeFlag = SV_IC_SafeFlag | C_W_SafeFlag_3;
	
	/*�����û������ͣ��ֱ���ÿ����������翨������*/
	switch(pStr_CardParse->UserCardType)
	{
		case		C_OpenCard:					/*������*/
		case		C_PPCard:					/*���翨*/
		case		C_SupplementCard:			/*����-Ŀǰ������������ͳһ��һ�֡�*/
			V_ucReturnData = MF_OPS_Card_Esam_Proc(pStr_CardParse, &V_ucErrStatus);
			if(V_ucReturnData != C_OK)			/*���÷�д*/
			{
				return(V_ucErrStatus);
			}
			else
			{
				break;
			}
		default:
			return(C_IC_TYPE_ERR);
	}
	
	/*����ESAM�����ļ���ͬʱ��д�û���*/
	Updata_ESAM_OpParm(C_Msg_Card);
	
	/*�ÿ���������Mac���������ԭ�������ʧЧ*/
	V_ucReturnData = InF_SC_GenerateRandToCalMac(C_Card, C_Length_4);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}
	
	/*��д*/
	V_ucReturnData = InF_SC_WR_UCReturnFile(IC_CardNo);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}
	else
	{
		return(V_ucErrStatus);
	}	
}


/*******************************************************************************
����ԭ�ͣ�	uchar8	MF_OPS_Card_Esam_Proc(StrCardParse	*pStr_CardParse, uchar8 *pV_ucIC_ErrStatus)
����������	�����������翨��������������
���������	pStr_CardParse			:�忨������ͨ�ýṹ��	(PPMoney��PPNum��IC_File��ΪǮ���ļ��ʹ�Mac����)
��������� 	*pStr_CardParse			:������ͨ�ýṹ��
			*pIC_ErrStatus			:�忨������롣��C_IC_NOIN_ERR
���ز�����	C_OK����д/C_Error������д
����λ�ã�
��    ע��	��Ҫ�ο�A.1.5 A.1.6 A.1.7,��д�˻ص��û����������д���
			��Щ����Ƿ���OK����������뻹���еġ����翪����
			��д�ļ���Ϊ�ա�
*******************************************************************************/
uchar8	MF_OPS_Card_Esam_Proc(StrCardParse	*pStr_CardParse, uchar8 *pV_ucIC_ErrStatus)
{
	uchar8		V_ucReturnData;
	ushort16	V_usReturnData16;
	ushort16	V_usPPNumFlag;
	
	/*��д�ļ��Ƿ�Ϊ�յ��ж�-����΢��*/
	*pV_ucIC_ErrStatus = C_OK;
	V_ucReturnData = InF_SC_Is_UserCardNull(&pStr_CardParse->UserCardNull);
	if(V_ucReturnData != C_OK)
	{
		*pV_ucIC_ErrStatus = V_ucReturnData;
		return(C_Error);
	}
	
	/*��Ǯ���ļ�--ǰ���Ѿ�����������΢����������ġ�
	��Mac��ȡ�ͻ�����*/
	V_ucReturnData = InF_SC_GetCustNumWithMac_UseCard(pStr_CardParse->UPType_CustNum);
	if(V_ucReturnData != C_OK)
	{
		*pV_ucIC_ErrStatus = V_ucReturnData;
		return(C_Error);
	}
	
	/*����״̬����Ƭ��š��ͻ����һ�����ж�*/
	V_ucReturnData = MF_Judge_OpenStutusAndCustNumCardNo(pStr_CardParse);
	if(V_ucReturnData != C_OK)
	{
		*pV_ucIC_ErrStatus = V_ucReturnData;
		return(C_Error);
	}
	
	/*���ڿ���������ֵ����ֻ��Ϊ0��1*/
	if( (pStr_CardParse->UserCardType == C_OpenCard) && (pStr_CardParse->PPNum > 1) )
	{
		*pV_ucIC_ErrStatus = C_IC_TIMES_ERR;
		return(C_Error);
	}
	
	/*��ɳ�ֵ������������ж�*/
	V_usPPNumFlag = InF_Judge_ChgBal_PC_Num(pStr_CardParse->PPMoney, pStr_CardParse->PPNum);
	switch(V_usPPNumFlag)
	{
		case		C_SERR_RechargeHoarding:			/*���������1�������ڻ������*/
			if(pStr_CardParse->UserCardNull != C_OK)	/*��д�ļ���Ϊ��,���������1�����ڻ���*/
			{
				*pV_ucIC_ErrStatus = C_IC_NONULL_ERR;
				return(C_OK);							/*�����������д�������Ϊ��д��Ϊ��*/
			}
			/*���ڻ�����д*/
			*pV_ucIC_ErrStatus = C_IC_OVERMAX_ERR;
			/*��ʾ���ڻ�*/
			MF_Card_SendMsgToDisp(C_HoardingSign, C_AlwaysDisplay, CCDsp_Duration_10s);
			
			return(C_Error);
		case		C_MeterPC_Num_Large:				/*���ڹ��������*/
			/*���ڿ������Ͳ��������п�������������ֵ��������ȷ��
			ע���������ò��Ÿ��¿ͻ���ŵġ�*/
			if( (pStr_CardParse->UserCardType == C_OpenCard) || (pStr_CardParse->UserCardType == C_SupplementCard) )
			{
				MF_Finish_L_Open(pStr_CardParse);
			}
			
			return(C_OK);
		case		C_SERR_RechargeNumErr:				/*���ڱ��ڹ������2��2����*/
			/*д�쳣�忨��¼�践д�ļ���*/
			*pV_ucIC_ErrStatus = C_IC_TIMES_ERR;
			
			return(C_OK); 
		case		C_PC_Num_Equal:						/*����������*/
		case		C_Can_EPurchase:					/*���Գ�ֵ,������ֵ��������1*/
			break;				
		case		C_SERR_OtherErr:					/*����Ӧ���ǲ����ܵģ��������������ESAM��������*/
		default:
			*pV_ucIC_ErrStatus = C_IC_ESAM_RDWR_ERR;	/*���忨�쳣��¼��7816Header SWû��*/
			return(C_Error);
			
	}
	
	/*��������ڹ��������Ȼ�ɳ�ֵ2�����*/
	if(pStr_CardParse->UserCardNull == C_OK)			/*��д�ļ�Ϊ��*/
	{
		if(pStr_CardParse->UserCardType == C_OpenCard)	/*����ο���0514-39��ֻҪ�ǿ��������������������пͻ��������*/
		{
			/*����ǿ����������Թ��磬����пͻ������֤��������
			�ͻ����Mac��֤-����΢����Զ�̿����ͳ�ֵʱ�Ž��пͻ����Mac��֤��*/	
			/*698����дǮ���ļ���������Ϣ�ļ��Ŀͻ����*/
			V_usReturnData16 = InF_S_WriteCustermerNumMAC(CCustomer_Num, pStr_CardParse->UPType_CustNum, (CLCustomer_Num + C_MacLen) );

			if(V_usReturnData16 != C_OK)
			{
				if(V_usReturnData16 == C_SERR_ESAM_VF)
				{
					*pV_ucIC_ErrStatus = C_IC_MAC_ERR;
				}
				else
				{
					*pV_ucIC_ErrStatus = C_IC_ESAM_RDWR_ERR;
				}
				return(C_Error);
			}
						
			InF_Write_Data(C_Msg_Card, CCustomer_Num, pStr_CardParse->UPType_CustNum, CLCustomer_Num, SV_IC_SafeFlag);
		}
	
		if(V_usPPNumFlag == C_Can_EPurchase)
		{
			/*�����ֵ�����Ƚ��г�ֵMac��֤*/
			V_usReturnData16 = InF_S_Purchase(pStr_CardParse->IC_File);
			if(V_usReturnData16 != C_OK)
			{
				*pV_ucIC_ErrStatus = C_IC_MAC_ERR;
				return(C_Error);
			}
			/*��ʾ��ֵǰ��ʣ����2s*/
			MF_Card_LCDView(CType_RemainMoney, pStr_CardParse);
			pStr_CardParse->PreMoneyClock = InF_OprateTimer(C_GetTimer, 2000);
			/*�������ݲ��ֵ�������й����¼*/
			InF_PurchaseDL(pStr_CardParse->PPMoney, SV_IC_SafeFlag);
		}
		
		/*���²���*/
		V_ucReturnData = MF_IC_UpdateParm(pStr_CardParse);
		if(V_ucReturnData!=C_OK)		/*���²���ʧ�ܣ�Ҳ�����з�д*/
		{
			*pV_ucIC_ErrStatus = V_ucReturnData;
			return(C_Error);
		}
		/*����ǿ������򲹿������п�������*/
		if( (pStr_CardParse->UserCardType == C_OpenCard) || (pStr_CardParse->UserCardType == C_SupplementCard) )
		{
			MF_Finish_L_Open(pStr_CardParse);		/*�����ϲ�����Ӧ���ÿ�����־������¼���š�*/
												/*��ǰ�������������δ�������ܱ��У��ᱨ���˳���*/
												/*���û�����⡣*/
		}
		return(C_OK);
	}
	else
	{
		/*��д�ļ���Ϊ��*/
		if( (V_usPPNumFlag == C_PC_Num_Equal) && (pStr_CardParse->CardNoEqualFlag != C_Equal) )
		{
			/*��д��Ϊ�գ�����������,���Ų�ͬ���û������÷�д�����ش���*/
			if( (pStr_CardParse->UserCardType == C_OpenCard) || (pStr_CardParse->UserCardType == C_SupplementCard) )
			{
				*pV_ucIC_ErrStatus = C_IC_SERIAL_ERR;
				return(C_Error);
			}
		}
		
		/*���翨���Ų��ȣ�����˳������ˡ�
		�淶�ж����п�����д�ļ���Ϊ�գ��践д�ļ�
		���ڿ��������������û��˵д�����־������Ͳ�����д�����־��
		���ﲻ������ͳͳд�����־�˳���20141027��д��Ϊ�գ����ڹ��������ֵΪ1ʱ����������󡣸��ݸ���΢����*/
		if(V_usPPNumFlag == C_Can_EPurchase)
		{
			*pV_ucIC_ErrStatus = C_IC_NONULL_ERR;
		}
		
		return(C_OK);
	}
}

/*******************************************************************************
����ԭ�ͣ�void		MF_Finish_L_Open(StrCardParse	*pStr_CardParse)
������������ɱ��ؿ�������:���濨�ţ���д���ؿ���״̬
���������pStr_CardParse��IC_CardNo		:����	
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void		MF_Finish_L_Open(StrCardParse	*pStr_CardParse)
{
	InF_Write_Data(C_Card, C_UserCardNo, IC_CardNo, CL_UserCardNo, SV_IC_SafeFlag);
	
	if( (pStr_CardParse->CardType == C_UserCardCommand) && (pStr_CardParse->UserCardType == C_OpenCard))		/*ֻ���û����Ŀ������Ÿ��±��ؿ���״̬*/
	{
		InF_DealWith_L_R_OAAFlag(C_Set_Method_L, C_HaveOpenAnAccount);
	}
}


/*******************************************************************************
����ԭ�ͣ�	uchar8		MF_Judge_OpenStutusAndCustNumCardNo(StrCardParse	*pStr_CardParse)
����������	�жϿ���״̬���ͻ���źͿ���
���������	pStr_CardParse->CardType		:��Ƭ����
			pStr_CardParse->UserCardType		:�û�������
			pStr_CardParse->UPType_CustNum	:�ͻ����
���������	pStr_CardParse->CardNoEqualFlag	:������ȱ�־��ȡֵC_Equal��C_GreaterThan��
���ز�����	C_OK/C_IC_HUHAO_ERR/C_IC_SERIAL_ERR/C_IC_NOOPEN_ERR/C_IC_NOOPEN2_ERR/C_IC_TYPE_ERR
����λ�ã�
��    ע��	1��Զ�̻򱾵�һ���ѿ�������
				a���жϿͻ�����Ƿ�һ�¡�һ�µ���һ�������򷵻ؿͻ���Ŵ�
				b����¼����һ�±�־������ǹ��翨��һ�·�����ȷ�����򷵻ش���
						������������ȷ
			2��δ������
				a������ǹ��翨�򲹿����򷵻ش���
				b�����������ÿ��Ų�һ�±�־��������ȷ
*******************************************************************************/
uchar8		MF_Judge_OpenStutusAndCustNumCardNo(StrCardParse *pStr_CardParse)
{
	uchar8		V_ucValue = C_HaveOpenAnAccount;
	uchar8		V_ucbuf[8];
	ushort16	V_usDataEnCode,V_usLen;
	
	if( (InF_DealWith_L_R_OAAFlag(C_Judge_Method_L, V_ucValue) == C_HaveOpenAnAccount)
		|| (InF_DealWith_L_R_OAAFlag(C_Judge_Method_R, V_ucValue) == C_HaveOpenAnAccount) )			/*�ѿ��������ȱȶԿͻ����*/
	{
		V_usLen = CLCustomer_Num;
		if(InF_Read_Data(CCustomer_Num, V_ucbuf, &V_usLen, &V_usDataEnCode) != C_OK)				/*����������Ϊ�����*/
		{
			return(C_IC_HUHAO_ERR);
		}
		if(PF_Campare_Data(V_ucbuf, pStr_CardParse->UPType_CustNum, CLCustomer_Num) != C_Equal)		/*�����*/
		{
			return(C_IC_HUHAO_ERR);
		}
		/*�ÿ��űȽϱ�־*/
		V_usLen = CL_UserCardNo;
		if(InF_Read_Data(C_UserCardNo, V_ucbuf, &V_usLen, &V_usDataEnCode) == C_OK)
		{
			pStr_CardParse->CardNoEqualFlag = PF_Campare_Data(V_ucbuf, IC_CardNo, CL_UserCardNo);
		}
		else
		{
			pStr_CardParse->CardNoEqualFlag = C_GreaterThan;
		}
		
		if(pStr_CardParse->UserCardType == C_PPCard)	/*���翨Ҫ�ȽϿ�����Ƿ����*/
		{
			if(pStr_CardParse->CardNoEqualFlag == C_Equal)
			{
				return(C_OK);
			}
			else
			{
				return(C_IC_SERIAL_ERR);
			}
		}
		else	/*���ڲ����Ϳ�����������Ҫ�ͻ�������*/
		{
			return(C_OK);
		}
	}
	else		/*δ����-��������������*/
	{
		switch(pStr_CardParse->UserCardType)
		{
			case		C_OpenCard:
				pStr_CardParse->CardNoEqualFlag = C_GreaterThan;
				return(C_OK);
				
			case		C_PPCard:
				return(C_IC_NOOPEN_ERR);		/*��������:���翨����δ������*/

			case		C_SupplementCard:
				return(C_IC_NOOPEN2_ERR);		/*��������:��������δ������*/

			default:
				return(C_IC_TYPE_ERR);
		}
	}
}



/*******************************************************************************
����ԭ�ͣ�void	MF_TimeConvert(uchar8	*V_ucTime)
����������5�ֽ�BCDת7�ֽ�data_time_s
���������V_ucTime ��ת����5�ֽ�BCDʱ��
���������V_ucTime ת�����7�ֽ�data_time_s
���ز�����
����λ�ã�
��    ע��	
*******************************************************************************/
void	MF_TimeConvert(uchar8	*V_ucTime)
{
	ulong32 V_ulHexBuffer;

	/*���ڿ��л�ʱ��5���ֽڣ���Ҫת��*/
	if(PF_Is_Buf_AllFixedData(&V_ucTime[1], 0x00, 5) == C_OK)			/*ȫ0*/
	{
		V_ucTime[0] = 0xFF; /*����*/				
		V_ucTime[6] = 0;	/*����*/
	}
	else if(PF_Is_Buf_AllFixedData(&V_ucTime[1], 0xFF, 5) == C_OK)		/*ȫff*/
	{
		V_ucTime[0] = 0xFF; /*����*/				
		V_ucTime[6] = 0xFF; /*����*/
	}
	else if(PF_Is_Buf_AllFixedData(&V_ucTime[1], 0x99, 5) == C_OK)		/*ȫ99*/
	{			
		V_ucTime[0] = 0xFF; /*����*/
		memset(&V_ucTime[1], 0x63, 6);	/*99ת����0x63д�����ݲ�*/
	}
	else
	{			
		V_ucTime[0] = 0xFF; 			/*����*/
		V_ucTime[6] = 0x20; 			/*����*/
		
		V_ucTime [1] = PF_BCDtoHexOneByte(V_ucTime[1]);
		V_ucTime [2] = PF_BCDtoHexOneByte(V_ucTime[2]);
		V_ucTime [3] = PF_BCDtoHexOneByte(V_ucTime[3]);
		V_ucTime [4] = PF_BCDtoHexOneByte(V_ucTime[4]);
		
		PF_BCDtoHexBytes(&V_ucTime[5], &V_ulHexBuffer, 2);
		PF_Ulong32ToBuffer4(&V_ucTime [5], &V_ulHexBuffer, 2);
	}
}

/*******************************************************************************
����ԭ�ͣ�	uchar8	MF_IC_UpdateParm(StrCardParse	*pStr_CardParse)
����������	�忨�����и��²���(���б������ݣ�ESAM��֤��д���ݲ㣬д��Ӧ���ݼ�¼
���������	pStr_CardParse->CardType		:��Ƭ����
			pStr_CardParse->UserCardType		:�û�������
			pStr_CardParse->UpdateFlag		:���±�־
���������	��
���ز�����	C_OK/C_IC_MAC_ERR/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR
����λ�ã�
��    ע��	1������΢û�жԲ����Ϸ��Խ����жϣ�����Ҳ���ж�
			2������Ԥ�ÿ������б����ؼ�¼
			3�����翨�Ͳ�����ֻ�ܸ��±����ף����ܸ��µ�ǰ�ס�
			4����ȫ�淶7.8Ҫ�󣬱�����ݲ������±�־��������ȫ��������
				�ٽ���ESAM��֤������������ʹ��ǰ�ο���Ҳ�ܱ�֤����Ҫôȫ��д
				Ҫôȫ����д
			5�����û���������ʱ����Ҫ�жϹ�������ͷ�д�ļ��Ƿ�Ϊ�ա�
				�ⲿִ��
*******************************************************************************/
uchar8	MF_IC_UpdateParm(StrCardParse	*pStr_CardParse)
{
	uchar8			V_ucReturnData;
	Str_Comm_645	Str_645Frame;
	uchar8			V_ucTime[7];
	uchar8			V_ucDI[4];
	uchar8			V_ucCode[4];
	uchar8			V_ucNum,i;
	ulong32			V_ulHexBuffer;
	uchar8			V_ucTempbuffer[CLCurrent_Ladder_Table];
	uchar8			V_ucDataTemp[3];
	
	/*���翨�Ͳ�����ֻ�ܸ��±����ף����ܸ��µ�ǰ�ס�*/
	if( (pStr_CardParse->CardType == C_UserCardCommand) 
		&& ( (pStr_CardParse->UserCardType == C_PPCard) || (pStr_CardParse->UserCardType == C_SupplementCard) ) )
	{
		pStr_CardParse->UpdateFlag = pStr_CardParse->UpdateFlag & (~C_UPType_CurRate);
		pStr_CardParse->UpdateFlag = pStr_CardParse->UpdateFlag & (~C_UPType_CurLadder);
		pStr_CardParse->UpdateFlag = pStr_CardParse->UpdateFlag & (~C_UPType_Other);
	}
		
	/*����UpdateFlag���в�����ȡ��Mac��֤��д���ݲ�
	���д����²��������ݴ�ESAM���ݵ��ڴ档*/
	if( (pStr_CardParse->UpdateFlag & C_UPType_CurRate) != 0)		/*���µ�ǰ�׷��ʵ�۱�־Ϊ1*/
	{
		V_ucReturnData = InF_SC_Backup_With_Mac(C_UPType_CurRate, pStr_CardParse->UPType_CurRate);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}

	if( (pStr_CardParse->UpdateFlag & C_UPType_BakRate) != 0)		/*���±����׷��ʵ�۱�־Ϊ1*/
	{
		V_ucReturnData = InF_SC_Backup_With_Mac(C_UPType_BakRate, pStr_CardParse->UPType_BakRate);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}

		V_ucReturnData = InF_SC_Backup_With_Mac(C_UPType_ChgRateClock, pStr_CardParse->UPType_ChgRateClock);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}

	if( (pStr_CardParse->UpdateFlag & C_UPType_CurLadder) != 0)		/*���µ�ǰ�׽��ݱ�־Ϊ1*/
	{
		V_ucReturnData = InF_SC_Backup_With_Mac(C_UPType_CurLadder, pStr_CardParse->UPType_CurLadder);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}
 
	if( (pStr_CardParse->UpdateFlag & C_UPType_BakLadder) != 0)		/*���±����׽��ݱ�־Ϊ1*/
	{
		V_ucReturnData = InF_SC_Backup_With_Mac(C_UPType_BakLadder, pStr_CardParse->UPType_BakLadder);
		if(V_ucReturnData != C_OK)
		{
			return(V_ucReturnData);
		}
	}

	if( (pStr_CardParse->UpdateFlag & C_UPType_Other) != 0)			/*��������������־Ϊ1*/
	{
		V_ucReturnData = InF_SC_Backup_With_Mac(C_UPType_Other, pStr_CardParse->UPType_Other);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}

/*����ȫ�������²�����ȡ��ϣ�����Mac��֤��*/
	if( (pStr_CardParse->UpdateFlag & C_UPType_CurRate) != 0)		/*���µ�ǰ�׷��ʵ�۱�־Ϊ1*/
	{
		V_ucReturnData = InF_SC_BackupW_With_Mac(C_UPType_CurRate, pStr_CardParse->UPType_CurRate);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}

	if((pStr_CardParse->UpdateFlag & C_UPType_BakRate) != 0)	/*���±����׷��ʵ�۱�־Ϊ1*/
	{
		V_ucReturnData = InF_SC_BackupW_With_Mac(C_UPType_BakRate, pStr_CardParse->UPType_BakRate);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}

		V_ucReturnData = InF_SC_BackupW_With_Mac(C_UPType_ChgRateClock, pStr_CardParse->UPType_ChgRateClock);
		if(V_ucReturnData != C_OK)
		{
			return(V_ucReturnData);
		}
	}

	if((pStr_CardParse->UpdateFlag & C_UPType_CurLadder) != 0)	/*���µ�ǰ�׽��ݱ�־Ϊ1*/
	{
		V_ucReturnData = InF_SC_BackupW_With_Mac(C_UPType_CurLadder, pStr_CardParse->UPType_CurLadder);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}

	if((pStr_CardParse->UpdateFlag & C_UPType_BakLadder) != 0)	/*���±����׽��ݱ�־Ϊ1*/
	{
		V_ucReturnData = InF_SC_BackupW_With_Mac(C_UPType_BakLadder, pStr_CardParse->UPType_BakLadder);
		if(V_ucReturnData != C_OK) 
		{	
			return(V_ucReturnData);
		}
	}

	if((pStr_CardParse->UpdateFlag & C_UPType_Other) != 0)		/*����������־Ϊ1*/
	{
		V_ucReturnData = InF_SC_BackupW_With_Mac(C_UPType_Other, pStr_CardParse->UPType_Other);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}

/*ESAM��֤ȫ����ȷ�󣬽���д���ݲ㶯����*/

/*���Ƚ���������ߵ���*/
	InF_BackupData_Reversal(C_UPType_CurRate, pStr_CardParse->UPType_CurRate);
	InF_BackupData_Reversal(C_UPType_BakRate, pStr_CardParse->UPType_BakRate);	
	InF_BackupData_Reversal(C_UPType_ChgRateClock, pStr_CardParse->UPType_ChgRateClock);
	InF_BackupData_Reversal(C_UPType_CurLadder, pStr_CardParse->UPType_CurLadder);
	InF_BackupData_Reversal(C_UPType_BakLadder, pStr_CardParse->UPType_BakLadder);
	InF_BackupData_Reversal(C_UPType_Other, pStr_CardParse->UPType_Other);

/*д���ݲ�*/
	if( (pStr_CardParse->UpdateFlag & C_UPType_CurRate) != 0)		/*���µ�ǰ�׷��ʵ�۱�־Ϊ1*/
	{
		Str_645Frame.DI = CCurrent_RateFF_Price;
		Str_645Frame.DataLen = CLCurrent_RateFF_Price + C_Data_OFS_14;

		/*�������ݸ�ʽת����12������ BCDתhex��ʽ*/
		V_ucNum = CLCurrent_RateFF_Price / CLCurrent_Rate1_Price;
		for(i = 0; i < V_ucNum; i++)	/*���ݴ�С���Ѿ���ת����*/
		{
			PF_BCDtoHexBytes(&pStr_CardParse->UPType_CurRate[CO_UPRate + i * CLCurrent_Rate1_Price], &V_ulHexBuffer, CLCurrent_Rate1_Price);
			PF_Ulong32ToBuffer4(&Str_645Frame.Data[C_Data_OFS_14 + i * CLCurrent_Rate1_Price], &V_ulHexBuffer, CLCurrent_Rate1_Price);
		}
		/*PF_CopyDataBytes(&pStr_CardParse->UPType_CurRate[CO_UPRate], &V_645Frame.Data[C_Data_OFS_14], CLCurrent_RateFF_Price);	*/		

		SV_Comm_Parse_Local.RecFlag = C_CommRecFlagForInt_Ok;			
		SV_Comm_Parse_Local.SafeControlFlag = C_W_SafeFlag;
		Have_IPEvent_Prog_698(CProgTPara_Note_1, CProgTPara_Degree, &Str_645Frame);

#if 0		
		if(pStr_CardParse->CardType == C_UserCardCommand)	/*������û������з��ʱ����¼���¼������Ԥ�ÿ������б�̼�¼*/
		{
			INF_WrRateProgRecord(IC_CardNo,SV_IC_SafeFlag);
			Inf_EventReport_HP(C_ProgTParaEventNo,C_Happen_EventReport);  
		}
		InF_Write_Data(C_Msg_Card,CCurrent_RateFF_Price,&pStr_CardParse->UPType_CurRate[CO_UPRate],CLCurrent_RateFF_Price,SV_IC_SafeFlag);
		InF_ActiveReportSetting(C_Times_ReworkRatesCharge);		/*���ʱ��������ϱ�����*/
#endif

	}

	if((pStr_CardParse->UpdateFlag & C_UPType_BakRate) != 0)	/*���±����׷��ʵ�۱�־Ϊ1*/
	{
		Str_645Frame.DI = CBackUp_RateFF_Price;
		Str_645Frame.DataLen = CLBackUp_RateFF_Price + C_Data_OFS_14;

		/*�������ݸ�ʽת����12������ BCDתhex��ʽ*/
		V_ucNum = CLBackUp_RateFF_Price / CLBackUp_Rate1_Price;
		for(i = 0; i < V_ucNum; i++)
		{
			PF_BCDtoHexBytes(&pStr_CardParse->UPType_BakRate[CO_UPRate + i * CLBackUp_Rate1_Price], &V_ulHexBuffer, CLBackUp_Rate1_Price);
			PF_Ulong32ToBuffer4(&Str_645Frame.Data[C_Data_OFS_14 + i * CLBackUp_Rate1_Price], &V_ulHexBuffer, CLBackUp_Rate1_Price);
		}

		/*PF_CopyDataBytes(&pStr_CardParse->UPType_BakRate[CO_UPRate], &V_645Frame.Data[C_Data_OFS_14], CLBackUp_RateFF_Price );*/			

		SV_Comm_Parse_Local.RecFlag = C_CommRecFlagForInt_Ok;			
		SV_Comm_Parse_Local.SafeControlFlag = C_W_SafeFlag;
		Have_IPEvent_Prog_698(CProgTPara_Note_1, CProgTPara_Degree, &Str_645Frame);

		#if 0
		if(pStr_CardParse->CardType == C_UserCardCommand)	/*������û������з��ʱ����¼���¼������Ԥ�ÿ������б�̼�¼*/
		{
			INF_WrRateProgRecord(IC_CardNo,SV_IC_SafeFlag);
			Inf_EventReport_HP(C_ProgTParaEventNo,C_Happen_EventReport);
		}
		InF_Write_Data(C_Msg_Card,CBackUp_RateFF_Price,&pStr_CardParse->UPType_BakRate[CO_UPRate],CLBackUp_RateFF_Price,SV_IC_SafeFlag);
		#endif

		/*���ڿ��л�ʱ��5���ֽڣ���Ҫת��*/
		PF_CopyDataBytes(pStr_CardParse->UPType_ChgRateClock, &V_ucTime[1], 5);
		MF_TimeConvert(V_ucTime);
		InF_Write_Data(C_Msg_Card, CChange_Rate, V_ucTime, CLChange_Rate, SV_IC_SafeFlag);
/*		InF_ActiveReportSetting(C_Times_ReworkRatesCharge);	*/	/*���ʱ��������ϱ�����*/
	}	

	if((pStr_CardParse->UpdateFlag & C_UPType_CurLadder) != 0)	/*���µ�ǰ�׽��ݱ�־Ϊ1*/
	{
		Str_645Frame.DI = CCurrent_Ladder_Table;
		Str_645Frame.DataLen = CLCurrent_Ladder_Table + C_Data_OFS_14;

		/*����ת�� :13��4�ֽ�BCDת4�ֽ�hex��4������ʱ*/				
		PF_CopyDataBytes(pStr_CardParse->UPType_CurLadder, V_ucTempbuffer, CLCurrent_Ladder_Table);			

		V_ucNum = 6 + 7;	/*6������+7�����ݵ��*/	
		for(i = 0; i < V_ucNum; i++)
		{		
			PF_BCDtoHexBytes(&V_ucTempbuffer[4 * i], &V_ulHexBuffer, 4);
			PF_Ulong32ToBuffer4(&V_ucTempbuffer[4 * i], &V_ulHexBuffer, 4);
		}

		/*�¡��ա�ʱת����*/
		V_ucNum = 4;	/*4��������*/	
		for(i = 0; i < V_ucNum; i++)	/*�ڲ��ٷ�תһ��*/
		{
			memcpy(V_ucDataTemp, &V_ucTempbuffer[4 * 13 + i * 3], 3);
			if(V_ucDataTemp[2] != 0xFF)
			{
				V_ucTempbuffer[4 * 13 + i * 3] = PF_BCDtoHexOneByte(V_ucDataTemp[2]);
			}
			else
			{
				V_ucTempbuffer[4 * 13 + i * 3] = 0xFF;
			}
			
			if(V_ucDataTemp[1] != 0xFF)
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 1] = PF_BCDtoHexOneByte(V_ucDataTemp[1]);
			}
			else
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 1] = 0xFF;
			}
			
			if(V_ucTempbuffer[0] != 0xFF)
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 2] = PF_BCDtoHexOneByte(V_ucDataTemp[0]);
			}
			else
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 2] = 0xFF;
			}	
		}
		
		PF_CopyDataBytes(V_ucTempbuffer, &Str_645Frame.Data[C_Data_OFS_14], CLCurrent_Ladder_Table);
		SV_Comm_Parse_Local.RecFlag = C_CommRecFlagForInt_Ok;			
		SV_Comm_Parse_Local.SafeControlFlag = C_W_SafeFlag;
		Have_IPEvent_Prog_698(CProgLad_Note_1, CProgLad_Degree, &Str_645Frame);

		#if 0			
		if(pStr_CardParse->CardType == C_UserCardCommand)	/*������û������н��ݱ����¼���¼������Ԥ�ÿ������б�̼�¼*/
		{
			INF_WrStepProgRecord(IC_CardNo,SV_IC_SafeFlag);
			Inf_EventReport_HP(C_ProgLadEventNo,C_Happen_EventReport);
			MF_Card_SendMsgToSettlement();		/*���µ�ǰ�׽��ݱ��������Ϣ������ģ�飬�ж���������Ƿ�仯���仯����������*/
		}
		InF_Write_Data(C_Msg_Card,CCurrent_Ladder_Table,pStr_CardParse->UPType_CurLadder,CLCurrent_Ladder_Table,SV_IC_SafeFlag);
		InF_ActiveReportSetting(C_Times_ReworkStepPara);			/*���ݱ��������ϱ�����*/
		#endif
	}

	if( (pStr_CardParse->UpdateFlag & C_UPType_BakLadder) != 0)		/*���±����׽��ݱ�־Ϊ1*/
	{
		Str_645Frame.DI = CBackUp_Ladder_Table;
		Str_645Frame.DataLen = CLBackUp_Ladder_Table + C_Data_OFS_14;

		/*����ת�� :13��4�ֽ�BCDת4�ֽ�hex��4������ʱ*/
		PF_CopyDataBytes(pStr_CardParse->UPType_BakLadder, V_ucTempbuffer, CLCurrent_Ladder_Table);

		V_ucNum = 6 + 7;	/*6�����ݺ�7�����ݵ��*/	
		for(i = 0; i < V_ucNum; i++)
		{		
			PF_BCDtoHexBytes(&V_ucTempbuffer[4 * i], &V_ulHexBuffer, 4);
			PF_Ulong32ToBuffer4(&V_ucTempbuffer[4 * i], &V_ulHexBuffer, 4);
		}

		/*�¡��ա�ʱת����*/
		V_ucNum = 4;	/*4��������*/	
		for(i = 0; i < V_ucNum; i++)
		{
			memcpy(V_ucDataTemp, &V_ucTempbuffer[4 * 13 + i * 3], 3);
			if(V_ucDataTemp[2] != 0xFF)
			{
				V_ucTempbuffer[4 * 13 + i * 3] = PF_BCDtoHexOneByte(V_ucDataTemp[2]);
			}
			else
			{
				V_ucTempbuffer[4 * 13 + i * 3] = 0xFF;
			}
			
			if(V_ucDataTemp[1] != 0xFF)
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 1] = PF_BCDtoHexOneByte(V_ucDataTemp[1]);
			}
			else
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 1] = 0xFF;
			}
			
			if(V_ucTempbuffer[0] != 0xFF)
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 2] = PF_BCDtoHexOneByte(V_ucDataTemp[0]);
			}
			else
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 2] = 0xFF;
			}	
		}

		PF_CopyDataBytes(V_ucTempbuffer, &Str_645Frame.Data[C_Data_OFS_14], CLBackUp_Ladder_Table );
		SV_Comm_Parse_Local.RecFlag = C_CommRecFlagForInt_Ok;
		SV_Comm_Parse_Local.SafeControlFlag = C_W_SafeFlag;
		Have_IPEvent_Prog_698(CProgLad_Note_1, CProgLad_Degree, &Str_645Frame);

		#if 0
		if(pStr_CardParse->CardType == C_UserCardCommand)/*������û������н��ݱ����¼���¼������Ԥ�ÿ������б�̼�¼*/
		{
			INF_WrStepProgRecord(IC_CardNo,SV_IC_SafeFlag);
            Inf_EventReport_HP(C_ProgLadEventNo,C_Happen_EventReport);
		}
		InF_Write_Data(C_Msg_Card,CBackUp_Ladder_Table,pStr_CardParse->UPType_BakLadder,CLBackUp_Ladder_Table,SV_IC_SafeFlag);
		#endif
		
		/*���ڿ��л�ʱ��5���ֽڣ���Ҫת��*/
		PF_CopyDataBytes(&pStr_CardParse->UPType_BakLadder[CO_UPLadderChgClock], &V_ucTime[1], 5);
		MF_TimeConvert(V_ucTime);
		
		InF_Write_Data(C_Msg_Card, CChange_Ladder, V_ucTime, CLChange_Ladder, SV_IC_SafeFlag);

/*			InF_ActiveReportSetting(C_Times_ReworkStepPara);	*/		/*���ݱ��������ϱ�����*/
	}

	if( (pStr_CardParse->UpdateFlag & C_UPType_Other) != 0)	/*����������־Ϊ1*/
	{
		/*�������1 ��Ҫ4�ֽ�BCDת4�ֽ�hex*/
		PF_BCDtoHexBytes(&pStr_CardParse->UPType_Other[CO_UPOther_Alam1], &V_ulHexBuffer, CLAlam1_Money);
		PF_Ulong32ToBuffer4(V_ucTempbuffer, &V_ulHexBuffer, CLAlam1_Money);
		InF_Write_Data(C_Msg_Card, CAlam1_Money, V_ucTempbuffer, CLAlam1_Money, SV_IC_SafeFlag);

		/*�������2 ��Ҫ4�ֽ�BCDת4�ֽ�hex*/
		PF_BCDtoHexBytes(&pStr_CardParse->UPType_Other[CO_UPOther_Alam2], &V_ulHexBuffer, CLAlam2_Money);
		PF_Ulong32ToBuffer4(V_ucTempbuffer, &V_ulHexBuffer, CLAlam2_Money);
		InF_Write_Data(C_Msg_Card, CAlam2_Money, V_ucTempbuffer, CLAlam2_Money, SV_IC_SafeFlag);

		/*�������,��Ҫ3�ֽ�BCDת4�ֽ�hex*/
		PF_CopyDataBytes(&pStr_CardParse->UPType_Other[CO_UPOther_Ratio_CT], &V_ucTempbuffer[0], CLRatio_Curr_Tran_Esam);	
		V_ucTempbuffer[3] = 0;	/*����λ*/
		PF_BCDtoHexBytes(&V_ucTempbuffer[0], &V_ulHexBuffer, CLRatio_Curr_Tran);
		PF_Ulong32ToBuffer4(&V_ucTempbuffer[0], &V_ulHexBuffer, CLRatio_Curr_Tran);		
		InF_Write_Data(C_Msg_Card, CRatio_Curr_Tran, V_ucTempbuffer, CLRatio_Curr_Tran, SV_IC_SafeFlag);

		/*��ѹ���,��Ҫ3�ֽ�BCDת4�ֽ�hex*/
		PF_CopyDataBytes(&pStr_CardParse->UPType_Other[CO_UPOther_Ratio_VT], &V_ucTempbuffer[0], CLRatio_Vol_Tran_Esam);
		V_ucTempbuffer[3] = 0;	/*����λ*/
		PF_BCDtoHexBytes(&V_ucTempbuffer[0], &V_ulHexBuffer, CLRatio_Vol_Tran);
		PF_Ulong32ToBuffer4(&V_ucTempbuffer[0], &V_ulHexBuffer, CLRatio_Vol_Tran);
		InF_Write_Data(C_Msg_Card, CRatio_Vol_Tran, V_ucTempbuffer, CLRatio_Vol_Tran, SV_IC_SafeFlag);
	
		/*����Ϣ������ģ�飬���и澯��Ԥ��բ��͸֧��������բ���ж�*/
		MF_Card_SendMsgForUpdataParm(C_ReworkWarningPara, C_Msg_EnergyMetering);
	}

	/*����Ϣ������ģ�飬���з��ʱ����ݱ��л��жϣ����ﲻ���Ƿ���¶��������ж�һ��û�й�ϵ*/
	MF_Card_SendMsgForUpdataParm(C_ReMultiRatesParm, C_Msg_Deal_MultiRates);

	/*д�ܱ�̼�¼*/
	if( (pStr_CardParse->CardType == C_UserCardCommand) 
		&& ( (pStr_CardParse->UpdateFlag & (C_UPType_Other|C_UPType_BakLadder|C_UPType_CurLadder|C_UPType_BakRate|C_UPType_CurRate) ) != 0) )
	{
		V_ucDI[0] = pStr_CardParse->UpdateFlag;
		V_ucDI[1] = pStr_CardParse->CardType;
		V_ucDI[2] = 0x98;
		V_ucDI[3] = 0x99;
		INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord,C_ACTION_Request);
		
		#if 0
		if(pStr_CardParse->UpdateFlag &C_UPType_BakRate)	/*���±����׷��ʵ��*/
		{			
			V_ulDI = CBackUp_RateFF_Price;
			PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
			INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord);
		}

		if(pStr_CardParse->UpdateFlag &C_UPType_BakLadder)	/*���±����׽��ݵ��*/
		{			
			V_ulDI = CBackUp_Ladder_Table;
			PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
			INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord);
		}
		
		if(pStr_CardParse->UpdateFlag &C_UPType_Other)	/*������������*/
		{
			/*�������1*/
			V_ulDI = CAlam1_Money;
			PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
			INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord);

			/*�������2*/
			V_ulDI = CRatio_Curr_Tran;
			PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
			INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord);

			/*��ѹ���������*/
			V_ulDI = CRatio_Vol_Tran;
			PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
			INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord);
			/*�������������*/
			V_ulDI = CBackUp_RateFF_Price;
			PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
			INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord);
		
		}
		#endif

		/*д����*/
		INF_StopCommProgState();
	}

	return(C_OK);
}


/*******************************************************************************
����ԭ�ͣ�	MF_Card_SendMsg(uchar8	 *pStr_MsgParmData, uchar8 V_ucLen, uchar8 V_ucDestAddress)
����������	����Ϣ������Ϣ
���������	*pMsgParmData			:�������׵�ַ
			Len						:�����򳤶Ȱ���PT
			DestAddress				:Ŀ�ĵ�ַ
���������	��
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void		MF_Card_SendMsg(uchar8	 *pStr_MsgParmData, uchar8 V_ucLen, uchar8 V_ucDestAddress)
{
	Str_Msg_Parameter	Str_MsgParm;
	
	Str_MsgParm.SourceAddr = C_Msg_Card;
	Str_MsgParm.Parameter = pStr_MsgParmData;
	Str_MsgParm.Length = V_ucLen;

	Str_MsgParm.DerictAddr = V_ucDestAddress;

	InF_WriteMessege(&Str_MsgParm);
}

/*******************************************************************************
����ԭ�ͣ�void		MF_Card_SendICMsg(void)
���������������忨��Ϣ
�����������
�����������
���ز�����
����λ�ã�
��    ע�������忨��Ϣ
*******************************************************************************/
void		MF_Card_SendICMsg(void)
{
	Str_Msg_Parameter	Str_MsgParm;
	uchar8				V_ucbuf;
	
	V_ucbuf = Pt_CardFlag;
	Str_MsgParm.SourceAddr = C_Msg_Card;
	Str_MsgParm.Parameter = &V_ucbuf;
	Str_MsgParm.Length = Pt_CardFlag_Len + 1;

	Str_MsgParm.DerictAddr = C_Msg_Deal_RelayStatus;

	InF_WriteMessege(&Str_MsgParm);
}


/*******************************************************************************
����ԭ�ͣ�	void		MF_Card_SendMsgToDisp(uchar8 V_ucDispSign, uchar8 V_ucDispMode, ushort16 V_usDuration)
����������	�������ʾģ�鴦��һ���ַ�
���������	V_ucDispSign:	��ʾ����
			V_ucDispMode��	��ʾģʽ
			V_usDuration��	��ʾʱ��
���������	��
���ز�����	��
����λ�ã�
��    ע��
*******************************************************************************/
void		MF_Card_SendMsgToDisp(uchar8 V_ucDispSign, uchar8 V_ucDispMode, ushort16 V_usDuration)
{
	Str_Msg_Parameter	Str_MsgParm;
	uchar8				V_ucbuf[4];
	
	Str_MsgParm.DerictAddr = C_Msg_Display;
	Str_MsgParm.SourceAddr = C_Msg_Card;
	V_ucbuf[0] = Pt_DisplayStatus;
	V_ucbuf[1] = V_ucDispSign | V_ucDispMode;
	PF_Ushort16ToBuffer2(&V_ucbuf[2], &V_usDuration);
	Str_MsgParm.Parameter = V_ucbuf;
	Str_MsgParm.Length = Pt_DisplayStatus_Len + 1;

	InF_Display_Message(&Str_MsgParm);
}


/*******************************************************************************
����ԭ�ͣ�	void		MF_Card_LCDView(uchar8	 V_ucType, StrCardParse	*pStr_CardParse)
����������	�忨����Һ������Ļ����ʾ
���������	V_ucType				:��ʾ���͡�ȡֵCType_RemainMoney/CType_IC_Err
			pStr_CardParse->IC_ErrEvent[CO_CE_ErrStatus]:	������Ϣ��
			����Type = CType_IC_Errʱ������
���������
���ز�����
����λ�ã�
��    ע��	ע�����￨���������ȣ�ֱ�ӵ�����ʾģ�������ʾ����
*******************************************************************************/
void		MF_Card_LCDView(uchar8	 V_ucType, StrCardParse	*pStr_CardParse)
{
	Str_Msg_Parameter	Str_MsgParm;
	uchar8				V_ucbuf[12];
	uchar8				V_ucIc_Err_Reg;
	
	Str_MsgParm.DerictAddr = C_Msg_Display;
	Str_MsgParm.SourceAddr = C_Msg_Card;
	Str_MsgParm.Parameter = V_ucbuf;
	
	if(V_ucType == CType_RemainMoney)		/*����Ļ��ʾ������Һ���鿴��ʽ������ʱ������ʾģ��̶�Ϊ10s*/
	{
		V_ucbuf[0] = Pt_DisplayID;
		if(MF_IsOverDraft_Zero() == C_OK)	/*͸֧ȫ0����ʾʣ��*/
		{
			V_ucbuf[1] = 0x01;	
            V_ucbuf[2] = 0x02;
	        V_ucbuf[3] = 0x2C;
	        V_ucbuf[4] = 0x20;
			V_ucbuf[5] = 0xff;	
            V_ucbuf[6] = 0xff;
	        V_ucbuf[7] = 0xff;
	        V_ucbuf[8] = 0xff;				
	        V_ucbuf[9] = 0x00;
		}
		else								/*͸֧��Ϊ0����ʾ͸֧*/
		{
			V_ucbuf[1] = 0x00;	
            V_ucbuf[2] = 0x02;
	        V_ucbuf[3] = 0x2D;
	        V_ucbuf[4] = 0x20;
			V_ucbuf[5] = 0xff;	
            V_ucbuf[6] = 0xff;
	        V_ucbuf[7] = 0xff;
	        V_ucbuf[8] = 0xff;				
	        V_ucbuf[9] = 0x00;
		}
		V_ucbuf[10] = CCDsp_Duration_10sL;
		V_ucbuf[11] = CCDsp_Duration_10sH;

		Str_MsgParm.Length = Pt_DisplayID_Len + 1;
	}
	else	/*����Ļ��ʾ������Ϣ�֣������ַ���ʾ���Ʒ�ʽ,����ʱ��Ҳ���ó�10s*/
	{
		V_ucbuf[0] = Pt_ERRXXDisplay;		/*������ʾ*/
		V_ucIc_Err_Reg = pStr_CardParse->IC_ErrEvent[CO_CE_ErrStatus];
		if(V_ucIc_Err_Reg == C_OK)
		{
			return;
		}
		/*�ô������*/
		if(V_ucIc_Err_Reg < 4) 
		{
			V_ucbuf[1] = 0x31;
		}
		else if(V_ucIc_Err_Reg < 11) 
		{
			V_ucbuf[1] = 0x32;
		}
		else if(V_ucIc_Err_Reg < 14) 
		{
			V_ucbuf[1] = 0x33;
		}
		else if(V_ucIc_Err_Reg < 19) 
		{
			V_ucbuf[1] = 0x34;
		}
		else if(V_ucIc_Err_Reg < 21) 
		{
			V_ucbuf[1] = 0x35;
		}
		else 
		{
			V_ucbuf[1] = 0x36;
		}
		V_ucbuf[2] = CCDsp_Duration_10sL;
		V_ucbuf[3] = CCDsp_Duration_10sH;
		Str_MsgParm.Length = Pt_ERRXXDisplay_Len + 1;
	}
	
	InF_Display_Message(&Str_MsgParm);
}


/*******************************************************************************
����ԭ�ͣ�uchar8	MF_IsOverDraft_Zero(void)
�����������ж�͸֧����Ƿ�Ϊȫ0
�����������
�����������
���ز�����C_OK:ȫ��/C_Error����ȫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	MF_IsOverDraft_Zero(void)
{
	ushort16	V_usDataLen;
	uchar8		V_ucbuf[CLOverDraft_Hex_Cent],V_ucReturnData;
	ulong32		V_ulOverDraft_BCD;
	ushort16	V_usDataEnCode;
	

	V_usDataLen = CLOverDraft_Hex_Cent;
	V_ucReturnData = InF_GetData_ObjectManage(COverDraft_Hex_Cent, V_ucbuf, &V_usDataLen, &V_usDataEnCode);
	if(V_ucReturnData != C_OK)
	{
		return C_Error;
	}

	PF_Buffer4ToUlong32(V_ucbuf, &V_ulOverDraft_BCD, CLOverDraft_Hex_Cent);
	
	if(V_ulOverDraft_BCD == 0)
	{
		return(C_OK);
	}
	else
	{
		return(C_Error);
	}
}


/*******************************************************************************
����ԭ�ͣ�void		MF_WRPre1ErrCardRecord(StrCardParse	*pStr_CardParse)
����������д���һ���쳣�忨��¼
���������StrCardParse	*pStr_CardParse
�����������
���ز�������
����λ�ã��忨�쳣
��    ע���¼���Ԫ���Ǳ�׼�¼���Ԫ
*******************************************************************************/
void		MF_WRPre1ErrCardRecord(StrCardParse	*pStr_CardParse)
{
	uchar8		V_ucDataBuff[300] = {0}, V_ucTemp[4];
	uchar8		V_ucLength;
	ushort16 	V_usOffset = 0, V_usResidualLength, V_usRelateoff;
	uchar8		V_ucEvent_Flag;
	ulong32		V_ulTemp = 0;
	ushort16	V_usDataEnCode, V_usLen;
	
	V_usLen = CLAbnorC_Degree;
	InF_Read_Data(CAbnorC_Degree, V_ucDataBuff, &V_usLen, &V_usDataEnCode);		/*���¼����*/
	/*PF_BCDAddBytes(V_ucDataBuff, (uchar8 *)V_AddOneMin, V_ucDataBuff, P_Data_Length);*/	/*�ۼ�ʱ���1*/
	V_usOffset += 4;
	
	V_usLen = CLDate_Week_Time;
	InF_Read_Data(CDate_Time, &V_ucDataBuff[V_usOffset], &V_usLen, &V_usDataEnCode);		/*���¼�����ʱ�䣬����ʱ��Ϊ00000000000000*/
	V_usOffset += 7;
	V_usOffset += 7;
	V_usOffset += 1;	/*����Դ����*/
	V_usOffset += 1;	/*�¼��ϱ�״̬����*/

	/*�����к�*/
	PF_CopyDataBytes(IC_CardNo, &V_ucDataBuff[V_usOffset], CL_CardNo);
	V_usOffset += CL_CardNo;
	
	/*�忨������Ϣ��*/
	PF_CopyDataBytes(&IC_ErrStatus, &V_ucDataBuff[V_usOffset], CL_CE_ErrStatus);	
	V_usOffset += CL_CE_ErrStatus;
	
	/*�忨��������ͷ*/
	PF_CopyDataBytes(IC_Err7816Header, &V_ucDataBuff[V_usOffset], CL_7816Header);
	V_usOffset += CL_7816Header;
	
	/*�忨������Ӧ״̬*/
	PF_CopyDataBytes(IC_ErrSW1_2, &V_ucDataBuff[V_usOffset], CL_7816_SW);
	V_usOffset += CL_7816_SW;
	V_usResidualLength = 300 - V_usOffset;		/*ʣ��buff����*/
	V_ucEvent_Flag = 0x01;
	V_usRelateoff = V_usOffset;	/*������һ�ε��¼�ͷƫ�Ƶ�ַ������д�ָ���*/

	if(Inf_GetRecordData(&V_ucDataBuff[V_usOffset], &V_usResidualLength, CAbnorC_OADTab, V_ucEvent_Flag) == C_OK)	/*��ȡ����OAD����*/	
	{
		V_usOffset += V_usResidualLength;			/*�����ܳ���*/
	}
	InF_Write_Data(C_Msg_Card, CAbnorC_Note_1, V_ucDataBuff, V_usOffset, C_W_SafeFlag);	/*д�쳣�忨�¼���¼*/

	/*д�ָ�*/
	V_usResidualLength = 300 - V_usRelateoff;
	if(Inf_GetRecordData(&V_ucDataBuff[V_usRelateoff], &V_usResidualLength, CAbnorC_OADTab, 0x02) == C_OK)	/*ȡ��������*/
	{
		V_usOffset += V_usResidualLength;			/*�����ܳ���*/
	}
	InF_Write_Data(C_Msg_Card, (CAbnorC_Note_1 + 1), V_ucDataBuff, V_usRelateoff, C_W_SafeFlag);

	Inf_EventReport_HP(C_AbnorCEventNo, C_Happen_EventReport);	

}

/*******************************************************************************
����ԭ�ͣ�void		MF_Write_IC_ErrEvent(StrCardParse	*pStr_CardParse)
�����������쳣�忨�¼���¼���Ƿ��忨�ܴ���
���������*pStr_CardParse->IC_ErrEvent		:�쳣�忨��¼		
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void		MF_Write_IC_ErrEvent(StrCardParse *pStr_CardParse)
{
	uchar8		V_ucLawlessC_Degree[CLLawlessC_Degree + 1];
	ushort16	V_usDataLen;
	ulong32		V_ulNum = 1;
	ushort16	V_usDataEnCode;
	
	/*�ж��Ƿ���ǰ�ο�	*/
	if( (InF_GetPeripheralStatus(C_CardStatus) != C_Valid) && (IC_ErrStatus == C_IC_NOIN_ERR) )	/*����忨�ź�Ϊ��Ч���ҿ�ͨ�Ŵ����ж�Ϊ��ǰ�ο�*/
	{
		IC_ErrStatus = C_IC_PREIC_ERR;
	}
	
	/*д7816��������ͷ��SW���������´����ڳ�ʼ���������㡣*/
	if( (IC_ErrStatus == C_IC_ESAM_RDWR_ERR) /*���ø���΢������*/
		|| (IC_ErrStatus == C_IC_NOFX_ERR)
		|| (IC_ErrStatus == C_IC_MAC_ERR) 
		|| (IC_ErrStatus == C_IC_NOIN_ERR)
		|| (IC_ErrStatus == C_IC_EXAUTH_ERR) )
	{
		/*Ŀǰ������Ƭͨ�Ŵ��󣬵ײ㷵��FFxx,�����жϵ�����ΪFFXXʱ����¼������ӦΪ0000*/
		if( (C_Security_Null) == (GV_7816CMD.SW1_2 & (C_Security_Null) ) )
		{
			GV_7816CMD.SW1_2 = 0;
		}
		PF_CopyDataBytes(GV_7816CMD.Header, IC_Err7816Header, CL_7816Header);	/*��������ͷ*/
		PF_Ushort16ToBuffer2(IC_ErrSW1_2, &GV_7816CMD.SW1_2);					/*������Ӧ״̬SW*/
	}
		
	/*д�쳣�忨��¼		*/
	MF_WRPre1ErrCardRecord(pStr_CardParse);

	/*д�Ƿ��忨�ܴ���*/
	if( (IC_ErrStatus == C_IC_IC_RST_ERR) || (IC_ErrStatus == C_IC_AUTH_ERR) || (IC_ErrStatus == C_IC_MAC_ERR) )	/*�������������Ƿ��忨bbb-255 3.22*/
	{
		V_usDataLen = CLLawlessC_Degree;
		if(InF_Read_Data(CLawlessC_Degree, V_ucLawlessC_Degree, &V_usDataLen, &V_usDataEnCode) != C_OK)
		{
			V_ulNum = 1;			
		}
		else
		{
			/*PF_BCDAddBytes(LawlessC_Degree, buf, LawlessC_Degree, CLLawlessC_Degree);*/
		
			PF_Buffer4ToUlong32(V_ucLawlessC_Degree, &V_ulNum, 4);
			V_ulNum += 1;
		}
		
		PF_Ulong32ToBuffer4(V_ucLawlessC_Degree, &V_ulNum, 4);
		
		InF_Write_Data(C_Msg_Card, CLawlessC_Degree, V_ucLawlessC_Degree, CLLawlessC_Degree, C_W_SafeFlag);
	}
}


/*******************************************************************************
����ԭ�ͣ�	void		MF_Init_IC_ErrEvent(StrCardParse	*pStr_CardParse)
����������	��ʼ���쳣�忨��¼����
���������	*pStr_CardParse->IC_ErrEvent		:�쳣�忨��¼��ָ��
���������	*pStr_CardParse->IC_ErrEvent		:�쳣�忨��¼
���ز�����	��
����λ�ã�
��    ע��	�忨��¼�����:
			ʱ�̡������ܴ�����ʣ�����ǰ���������й�д
			�����кš�������Ϣ�֡���������ͷ��������Ӧ�ĳ�ʼ��
*******************************************************************************/
void	MF_Init_IC_ErrEvent(StrCardParse	*pStr_CardParse)
{
	uchar8		i;
	ushort16	V_usDataEnCode, V_usLen;

	
	for(i = 0; i < CLAbnorC_Note_1; i++)
	{
		pStr_CardParse->IC_ErrEvent[i] = 0;
	}
	
/*	pStr_CardParse->IC_ErrEvent[CO_CE_ErrStatus] = C_OK;*/
	
	/*��ʱ��,�����忨�����в�ˢ��ʱ��*/
	V_usLen = CLDate_Time;
	InF_Read_Data(CDate_Time, &(pStr_CardParse->IC_ErrEvent[CO_CE_Clcok]), &V_usLen, &V_usDataEnCode);
	
	/*�����кų�ʼ����0xFF*/
	for(i = 0; i < CL_CardNo; i++)
	{
        pStr_CardParse->IC_ErrEvent[CO_CE_CardNo + i] = 0xFF;
	}

}


/*******************************************************************************
����ԭ�ͣ�	void		MF_Card_SendMsgForUpdataParm(uchar8 V_ucParmType,uchar8 V_ucDestMsg)
����������	���Ͳ���������Ϣ
���������	V_ucParmType	:���µĲ������͡�
			ȡֵ		: C_ReWorkTime			ʱ�����
						: C_ReDemand_Cycle		�������ڸ���
						: C_ReMultiRatesParm	ʱ�η��ʵȲ����޸�
						: C_ReSettle_Day1		��1�������޸�
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void		MF_Card_SendMsgForUpdataParm(uchar8 V_ucParmType, uchar8 V_ucDestMsg)
{
	Str_Msg_Parameter	Str_MsgParm;
	uchar8				V_ucbuf[2];
	
	Str_MsgParm.DerictAddr = V_ucDestMsg;
	Str_MsgParm.SourceAddr = C_Msg_Card;
	Str_MsgParm.Parameter = V_ucbuf;
	Str_MsgParm.Length = Pt_ParaMetersChange_Len + 1;
	V_ucbuf[0] = Pt_ParaMetersChange;
	V_ucbuf[1] = V_ucParmType;
	InF_WriteMessege(&Str_MsgParm);	
}


/*******************************************************************************
����ԭ�ͣ�void InF_WriteCardStatus(ushort16 V_usCardFlay)
��������������״̬��д���ݲ�
����������忨״̬�� C_CardStatusOK/C_CardStatusERR/C_CardStatusUnknow
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void InF_WriteCardStatus(ushort16 V_usCardFlay)
{
	uchar8	V_ucbuf[5];

	PF_Ushort16ToBuffer2(V_ucbuf, &V_usCardFlay);
	
	InF_Write_Data(C_Msg_Card, CInset_Card_State, V_ucbuf, CLInset_Card_State, C_W_SafeFlag);
}


/*******************************************************************************
����ԭ�ͣ�void		MF_Card_SendMsgToSettlement(void)
�����������޸ĵ�ǰ�ײ������Ͳ���������Ϣ������ģ��
�����������
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void		MF_Card_SendMsgToSettlement(void)
{
	Str_Msg_Parameter	Str_MsgParm;
	uchar8				V_ucbuf[5];
	
	Str_MsgParm.DerictAddr = C_Msg_SettleAccounts;		/*Ŀ�ĵ�ַΪ����ģ��*/
	Str_MsgParm.SourceAddr = C_Msg_Card;
	Str_MsgParm.Parameter = V_ucbuf;
	Str_MsgParm.Length = Pt_YearCheckDayChange_Len + 1;
	V_ucbuf[0] = Pt_YearCheckDayChange;					/*�޸����������Ϣ*/
	InF_WriteMessege(&Str_MsgParm);	
}



