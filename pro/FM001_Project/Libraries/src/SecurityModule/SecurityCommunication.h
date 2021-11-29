/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     SecurityCommunication.h
Version:       V1
Author:        jiangzs
Date:          2014-3-31
Description:   ��ȫͨ��ͷ�ļ�
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

#ifndef	__SecurityCommunication_H
#define	__SecurityCommunication_H

#define	CLen_S_BufMaxLen					196
/*������*/
#define		C_Duration_Alway		0xFFFF



/************  �����ǰ�ȫģ�鷵�ز�������************************************/
#define		C_MacLen					4				/*Mac����*/
#define		C_PPNumOff					4				/*����Ǯ���ļ��й������ƫ��*/
#define		C_CustomerNumOff			(4 + 4)			/*����Ǯ���ļ��пͻ����ƫ��*/
#define		C_MacOff					(4 + 4 + 6)		/*����Ǯ���ļ���Macƫ��*/

#define		C_HaveOpenAnAccount			0x68			/*���ڿ���״̬*/
#define		C_HaveNoOpenAnAccount		0x00			/*����δ����״̬*/
#define		C_Judge_Method				0x01			/*�жϷ���*/
#define		C_Set_Method				0x02			/*���÷���*/
#define		C_O_LOpenAnAccount			1				/*���ؿ���״̬��02FE0501�е�ƫ��*/
#define		C_O_ROpenAnAccount			0				/*Զ�̿���״̬��02FE0501�е�ƫ��*/


#define		C_Judge_Method_R 			0x01			/*Ϊ�ж�Զ�̿���״̬*/
#define		C_Set_Method_R 				0x02			/*Ϊ����Զ�̿���״̬*/
#define		C_Judge_Method_L 			0x10			/*Ϊ�жϱ��ؿ���״̬*/
#define		C_Set_Method_L 				0x11			/*Ϊ�����ؿ���״̬*/


/************ �����֤��� ********************************************************/
#define		CDI_Auth					0x070000FF	/*�����֤���ݱ�ʶ��*/

#define		CL_Auth_CiphertextK1		8			/*����1����*/
#define		CL_Auth_Rand1				8			/*���������*/
#define		CL_Auth_Dis_factor			8
#define		CL_Auth_Rand1_SoftCam		16

#define		CLen_Rand2					4
#define		CLen_ESAMNo					8			/*ESAM���кų���*/
#define		CLen_AuthPTime				2

#define		C_Auth_O_CiphertextK1		0			/*�����֤����������1��ƫ��*/
#define		C_Auth_O_Rand1				CL_Auth_CiphertextK1
													/*8: �����֤�����������1ƫ��*/
#define		C_Auth_O_Dis_factor			(C_Auth_O_Rand1 + CL_Auth_Rand1)
													/*16: �����֤�����з�ɢ����ƫ��*/
#define		C_Authentication_Len		24			
													/*24: �����֤�·����ݳ���*/
#define		C_R_Authentication_Len		14
													/*14: �����֤�������ݳ���*/
#define		C_R_Auth_O_Rand2			0			/*��Ӧ�����������2ƫ��*/
#define		C_R_Auth_O_ESAMNo			CLen_Rand2	/*��Ӧ������ESAM���кŵ�ƫ��*/
#define		C_R_Auth_O_AuthPTime		(C_R_Auth_O_ESAMNo + CLen_ESAMNo)
													/*��Ӧ�����������֤��Чʱ��ƫ��*/
/***********�����֤ʧЧ���***************************************************/
#define		CDI_Auth_Invaliad			0x07000201	/*�����֤ʧЧ���ݱ�ʶ��*/
#define		CDI_Auth_InvaliadFF			0x070002FF	/*�����֤ʧЧ���ݱ�ʶ��*/

//CLCustomer_Num
//CLChargeBal_Hex_Cent
#define		CL_PurchasingE_Num			0x04			/*������������ݳ���*/
//CLKey_State

#define		C_AInvR_O_CustomerNo		0x00			/*�ͻ������ƫ��*/
#define		C_AInvR_O_ChargeB_B			CLCustomer_Num	
														/*ʣ�����ƫ��*/
#define		C_AInvR_O_PE_Num			(C_AInvR_O_ChargeB_B + CLChargeBal_Hex_Cent)
														/*���������ƫ��*/
#define		C_AInvR_O_Key_State			(C_AInvR_O_PE_Num + CL_PurchasingE_Num)
														/*��Կ״̬��ƫ��*/
/************* ���������֤��Чʱ�����************************************/
#define		CDI_CPTime					0x070001FF		/*���������֤��Чʱ����ʶ��*/
#define		C_CPTime_O					0x00			/*�����֤��Чʱ��ƫ��*/
#define		C_CPTime_O_Mac				CLen_AuthPTime	/*Mac��ƫ��*/
/************* ������֤�������************************************************/
#define		CDI_IRCReq					0xF1000B00		/*������֤�����ʶ��*/
#define		CL_Rand1					8
#define		CDI_IRCReq_645				0x078003FF		/*645������֤�����ʶ��*/


#define		CL_RIRCReq_Rand2			8				/*������֤�����������2�ĳ���*/
#define		CL_IRReq_Response			(CLMeter_Num_645 + CLen_ESAMNo + CL_Auth_CiphertextK1 + CL_RIRCReq_Rand2) /*698����645���8�ֽڸ�Ϊ6�ֽ�*/
														/*������֤������Ӧ����*/
#define		C_RIRCReq_O_M_Num			0				/*������֤����Ӧ�����б��ƫ��*/
#define		C_RIRCReq_O_ESAMNo			(C_RIRCReq_O_M_Num + CLMeter_Num)
														/*������֤����Ӧ������ESAMNoƫ��*/
#define		C_RIRCReq_O_RandK1			(C_RIRCReq_O_ESAMNo + CLen_ESAMNo)
														/*������֤����Ӧ������K1 ƫ��*/
#define		C_RIRCReq_O_Rand2			(C_RIRCReq_O_RandK1 + CL_Auth_CiphertextK1)
														/*������֤����Ӧ������Rand2 ƫ��*/
//698����645Э����,645Э�����������ƫ��
#define		C_RIRCReq_O_M_Num_645		0				/*������֤����Ӧ�����б��ƫ��*/
#define		C_RIRCReq_O_ESAMNo_645		(C_RIRCReq_O_M_Num + CLMeter_Num_645)
														/*������֤����Ӧ������ESAMNoƫ��*/
#define		C_RIRCReq_O_RandK1_645		(C_RIRCReq_O_ESAMNo_645 + CLen_ESAMNo)
														/*������֤����Ӧ������K1 ƫ��*/
#define		C_RIRCReq_O_Rand2_645		(C_RIRCReq_O_RandK1_645 + CL_Auth_CiphertextK1)
														/*������֤����Ӧ������Rand2 ƫ��*/
/************* ������֤���*******************************************************/
#define		CDI_IR_ExtAuth				0xF1000C00		/*������֤���ݱ�ʶ��*/
#define		CL_Auth_CiphertextK2		8				/*�����2���ܺ�ĳ���*/
#define		CDI_IR_ExtAuth_645			0x070003FF		/*645������֤���ݱ�ʶ��*/

///************* ��Կ�������*******************************************************///
#define		C_Max_KeyNum				CLTemp_Key_StateFF		/*�����Կ����*/
#define		C_Default_KeyNum			20						/*����������20����Կ*/
#define		CDI_UpdataKey				0x070301FF				/*��Կ���������ʶ��*/

#define		CMsg_ReUpdataKey			0x68			/*���½�����Կ���±�־*/
#define		CMsg_Null					00				/*����Ϣ��־*/

#define		C_MaxKeyNum					4				/*һ��Mac ��֤���4����Կ*/
#define		CL_KeyInfo					4				/*��Կ��Ϣ����Ϊ4*/
#define		CL_Key						32				/*��Կ����*/

#define		CL_KeyWithInfo_1			36
#define		CL_KeyWithInfo_2			72
#define		CL_KeyWithInfo_3			108
#define		CL_KeyWithInfo_4			144

#define		C_UpKey_O_1					0				/*��1����Կƫ�Ƶ�ַ,��������*/
#define		C_UpKey_O_2					(C_UpKey_O_1 + CL_KeyWithInfo_1)


#define		CUpKey_O_Mac_1				(C_UpKey_O_1 + CL_KeyWithInfo_1)



#define		C_UpKey_O_KeyNum_1			35				/*��1����Կ��������ƫ�Ƶ�ַ����������*/


#define		C_UpKey_O_KeyNo_1			33				/*��1����Կ�ı��,��������*/

#define		CInfo_TestKey				0				/*����Կ��Ϣ��״̬��ʾΪ������Կ*/
#define		CInfo_OfficialKey			1				/*����Կ��Ϣ��״̬��ʾΪ��ʽ��Կ*/

#define		C_UpKey_O_KeyState_1		32				/* ��1����Կ��״̬����������*/
#define		C_UpKey_O_Key_1				0				/*��1����Կλ��*/

/************* ״̬��ѯ���*******************************************************/
#define		CDI_GetStatus				0x078102FF		/*״̬��ѯ*/
#define		CDI_GetStatus01				0x07810201


#define		CL_GetStatusR				26

#define		C_GetS_O_ChgBlHC			0				/*���ζ���ʣ����/Mac/�������/�ͻ����/��Կ״̬ƫ��*/
#define		C_GetS_O_ChgBlHC_Mac		(C_GetS_O_ChgBlHC + CLChargeBal_Hex_Cent)
#define		C_GetS_O_PC_Num				(C_GetS_O_ChgBlHC_Mac + C_MacLen)
#define		C_GetS_O_PC_Num_Mac			(C_GetS_O_PC_Num + CL_PurchasingE_Num)
#define		C_GetS_O_C_Num				(C_GetS_O_PC_Num_Mac + C_MacLen)
#define		C_GetS_O_Key_State			(C_GetS_O_C_Num + CLCustomer_Num)

/************* ���ݻس����*******************************************************/
/*����Ϊ�س���ʶ��ƫ�ơ��ֱ�Ϊ���ĳ��ȣ���Ե�ַ���ļ���ʶ��Ŀ¼*/
#define		CDI_GetData					0x078001FF
#define		CDI_GetData01				0x07800101
#define		C_DExc_O_Ld					0		
#define		C_DExc_O_Offset				2
#define		C_DExc_O_FileNo				4
#define		C_DExc_O_Dir				6

#define		CL_FileDataCode				8		/*�ļ���ʶ�ĳ���*/

//��Ӧ���ݵ�ƫ��
#define		C_DExcR_O_FDC				0		/*��Ӧ�����ļ���ʶ*/
#define		C_DExcR_O_Data				(C_DExcR_O_FDC + CL_FileDataCode)
												/*���������ļ����ݿ�ʼƫ��*/

#define		C_DExcR_O_ChgBlHC			(C_DExcR_O_FDC + CL_FileDataCode)
												/*�س�Ǯ���ļ�ʱʣ���ʼ��ƫ��*/
#define		C_DExcR_O_PC_Num			(C_DExcR_O_ChgBlHC + CLChargeBal_Hex_Cent + C_MacLen)
												/*�س�Ǯ���ļ�ʱ���������ʼ��ƫ��*/
/************* ��������дESAM�ļ����*******************************************************/
#define		C_WESAM_O_FileNo			0
#define		CL_FileNO					1
#define		C_WESAM_O_Offset			(C_WESAM_O_FileNo + CL_FileNO)
#define		CL_Offset					2
#define		C_WESAM_O_Data				(C_WESAM_O_Offset + CL_Offset)


/***********����ȶ�***************************************************************/
#define		CDI_CMPSoft					0x078002FF
#define		CL_SoftwareCampare_Data		0x40

/***********���Ĵ�MacдESAM��Ϣ�ļ�*******************************************/
#define		CDI_WR_PlainTextMAC			0x070004FF

/***********���Ĵ�MacдESAM��Ϣ�ļ�*******************************************/
#define		CDI_WR_CipherTextMAC		0x070005FF

/***********Զ��Ǯ����ʼ����֤***********************************************/
#define		CDI_Init_Money				0x070103FF
#define		C_Init_MoneyDataLen			16					/*��ʼ��Ǯ������Ч���ݳ���*/
//����Ϊ�������������ƫ��
#define		C_InitM_O_ChgBlHC			0					/*ʣ����+Mac1��ʼ��ƫ��*/
#define		C_InitM_O_PC_Num			8					/*�������+Mac2��ʼ��ƫ��*/

/***********Զ�̿�������ֵ****************************************************/
#define		CDI_ROpenAnAccount			0x070101FF			/*Զ�̿���*/
#define		CDI_RChgBL					0x070102FF			/*Զ�̳�ֵ*/

#define		C_OpenChgBL_Len				(CLChargeBal_Hex_Cent + CL_PurchasingE_Num + C_MacLen + CLCustomer_Num + C_MacLen)
/*����Ϊ2�����������ƫ��(��ʽ��ͬ)*/
#define		C_ROAACB_O_ChgBlHC			0					/*��ֵ���*/
#define		C_ROAACB_O_PC_Num			4					/*�������*/
#define		C_ROAACB_O_Mac1				8
#define		C_ROAACB_O_CNum				12					/*�ͻ����*/

/************����Ϊ�ļ����ƶ���*************************************************/
#define	C_F_MainDir			0xDF01
#define	C_F_MF				0x3F00
/*ESAM���ļ���*/
#define	C_F_MasterKey		0						/*������Կ�ļ�*/
#define	C_F_MeterNO			1						/*����ļ�*/
#define	C_F_Purse			1						/*Ǯ���ļ�*/
#define	C_F_SafeID			3						/*��ȫ��ʶ�ļ�*/
#define	C_F_ParmInf			4						/*������Ϣ�ļ���ʶ��*/
#define	C_F_ElePrice		5						/*��ǰ����ļ���ʶ��*/
#define	C_F_ElePriceBak		6						/*�����׵���ļ���ʶ��*/
#define	C_F_OpInfo			7						/*������Ϣ�ļ�*/


#define	C_F_LKeyState		5						/*������Կ״̬�ļ�*/

#define	C_F_ParmUpdata_1	0x09					/*���������ļ�1*/
#define	C_F_ParmUpdata_2	0x10
#define	C_F_ParmUpdata_3	0x11
#define	C_F_ParmUpdata_4	0x12
#define	C_F_ParmUpdata_5	0x13

#define	C_F_ReturnFile		0x0C					/*�˷��ļ���������*/

#define	C_F_MeterClear		0x14					/*�����ļ�*/
#define	C_F_D_E_Clear		0x17					/*���塢�¼������ļ�*/
#define	C_F_RemoteCtr		0x08					/*Զ�̿�������*/

//698����645���ļ�����
#define	C_F_RemoteCtr_Dou645		0x82			/*Զ�̿�������*/
#define	C_F_MeterClear_Dou645		0x84			/*�����ļ�*/
#define	C_F_D_E_Clear_Dou645		0x85			/*���塢�¼������ļ�*/

/************����Ϊ�Ϳ���صĶ���**********************************************/
/*********�忨������Һ������Ļ����ʾ**************************************/
#define		CType_RemainMoney		1				/*�忨Һ����ʾʣ�����*/
#define		CType_IC_Err			2				/*�忨Һ����ʾErr*/
#define		CCDsp_Duration_Alway	0xFFFF			/*�忨��ʾʱ�䳣��*/
#define		CCDsp_Duration_10s		0x000A
#define		CCDsp_Duration_10sL		0x0A			/*10s��λ*/
#define		CCDsp_Duration_10sH		0x00

#define		CCDsp_Duration_60s		60				/*����60s*/

/**********����������д������***********************************************/
#define		C_IC_VLOW_ERR			1			/*��Ƶ�ѹ����176V(80%Un)*/
#define		C_IC_ESAM_RDWR_ERR		2			/*����ESAM����*/
#define		C_IC_ESAM_RST_ERR		3			/*ESAM��λ����*/
#define		C_IC_IC_RST_ERR			4			/*��Ƭ��λ����:���忨�����Ƭ*/
#define		C_IC_AUTH_ERR			5			/*�����֤����(ͨ�ųɹ������Ĳ�ƥ��)*/
#define		C_IC_EXAUTH_ERR			6			/*�ⲿ�����֤����(ͨ�ųɹ�����֤��ͨ��)*/
#define		C_IC_NOFX_ERR			7			/*δ���еĿ�Ƭ(����Ƭʱ����6B00)*/
#define		C_IC_TYPE_ERR			8			/*�����ʹ���*/
#define		C_IC_KER_ERR			9			/*��Ƭ����δ��Ȩ����Կ״̬��Ϊ��Կ�ǲ����Ԥ�ƿ�*/
#define		C_IC_MAC_ERR			10			/*MACУ�����(6988)*/
#define		C_IC_ID_ERR				11			/*��Ų�һ��*/
#define		C_IC_HUHAO_ERR			12			/*�ͻ���Ų�һ��*/
#define		C_IC_SERIAL_ERR			13			/*����Ų�һ��*/
#define		C_IC_FORMAT_ERR			14			/*��Ƭ�ļ���ʽ���Ϸ�*/
#define		C_IC_NOOPEN_ERR			15			/*���翨����δ�������*/
#define		C_IC_NOOPEN2_ERR		16			/*��������δ�������*/
#define		C_IC_TIMES_ERR			17			/*�����������*/
#define		C_IC_NONULL_ERR			18			/*�û�����д��Ϣ�ļ���Ϊ��*/
#define		C_IC_NOIN_ERR			19			/*������ƬͨѶ����(��д��Ƭʧ��)*/
#define		C_IC_PREIC_ERR			20			/*��ǰ�ο�*/
#define		C_IC_OVERMAX_ERR		21			/*ʣ����ڻ�*/

/*********�쳣�忨��¼�г��ȼ�ƫ��*****************************************/
#define		CL_CardNo				CL_UserCardNo		/*�����кų���*/
#define		CL_CE_ErrStatus			1					/*������Ϣ��*/
#define		CL_7816Header			5					/*7816����ͷ����*/
#define		CL_7816_SW				2					/*7816��Ӧ����*/
#define		CL_PPNum_BCD_2			2


#define		CO_CE_Clcok				0x00										/*����ʱ��*/
#define		CO_CE_CardNo			(CO_CE_Clcok + CLDate_Time)					/*�����к�*/
#define		CO_CE_ErrStatus			(CO_CE_CardNo + CL_CardNo)					/*������Ϣ��*/
#define		CO_CE_7816Header		(CO_CE_ErrStatus + CL_CE_ErrStatus)			/*����ʱ�쳣7816����ͷ*/
#define		CO_CE_ErrSW1_2			(CO_CE_7816Header + CL_7816Header)			/*������Ӧ*/
/*#define		CO_CE_PNum				(CO_CE_ErrSW1_2+CL_7816_SW)	*/			/*�������*/
/*#define		CO_CE_RMoney			(CO_CE_PNum+CL_PPNum_BCD_2)	*/			/*ʣ����*/
/*#define		CO_CE_PAEnergy			(CO_CE_RMoney+CLChargeBal_BCD)*/		/*�����й�*/
/*#define		CO_CE_NAEnergy			(CO_CE_PAEnergy+CLPos_Ac_Tol_En_0)*/	/*�����й�*/

/*********����/�û���Ԥ�ƿ�ָ���ļ��еĺ�******************************/
#define		C_FC_INS				0x01			/*����Ԥ�ÿ�ָ���ļ�/�û����в�����Ϣ�ļ�*/
													/*ָ���ļ�����ȥ��ǰ4�ֽںͺ�2�ֽ�*/
#define		CL_PresetCardCMD		26				/*����Ԥ�ÿ�ָ���ļ����ݳ���*/
#define		CL_UserCardCMD			39				/*�û���ָ���ļ����ݳ���*/

#define		C_UserCardCommand		1				/*�û���ָ��*/
#define		C_PresetCardCommand		6				/*����Ԥ�ÿ�ָ��*/
#define		C_OpenCard				1				/*�û�������Ϊ������*/
#define		C_PPCard				2				/*�û�������Ϊ���翨*/
#define		C_SupplementCard		3				/*�û�������Ϊ����*/

#define		CL_INS_Len				2				/*ָ���ļ��ļ�����*/


#define	CLRatio_Curr_Tran_Esam		3				/*��ѹ���������������698��һ��*/
#define	CLRatio_Vol_Tran_Esam		3
#define	CLChange_Ladder_Esam		5				/*�л�ʱ����698��һ��*/
#define	CLChange_Rate_Esam			5
#define	CLMeter_Num_Esam			6


#define		CO_INS_Start			0x00								/*��ʼ�ֽ�68*/
#define		CO_INS_CMD				(CO_INS_Start + 1)					/*������*/
#define		CO_INS_Len				(CO_INS_CMD + 1)					/*����*/
/*����1�ֽ�*/
#define		CO_INS_UpdataPFlag		(CO_INS_Len + CL_INS_Len + 1)		/*�������±�־*/
/*����4�ֽ�*/
#define		CO_INS_ChgRate			(CO_INS_UpdataPFlag + 1 + 4)		/* 2�׷��ʵ���л�ʱ��*/

#define		CO_INS_Bak_3			(CO_INS_ChgRate + 5)				/*��3������*/
#define		CO_INS_AlarmM1			(CO_INS_Bak_3 + 1)					/*�������1*/
#define		CO_INS_AlarmM2			(CO_INS_AlarmM1 + CLAlam1_Money)
#define		CO_INS_Ratio_CT			(CO_INS_AlarmM2 + CLAlam2_Money)	/*�������������*/
#define		CO_INS_Ratio_VT			(CO_INS_Ratio_CT + CLRatio_Curr_Tran_Esam)

/*���ϣ�����Ԥ�ÿ����û���������һ�¡����·ֱ�Ϊ����Ԥ�ÿ�/�û�����󼸸������
����Ԥ�ÿ����������*/
#define		CO_INS_PreSetC_CS		(CO_INS_Ratio_VT + CLRatio_Vol_Tran_Esam)	/*����Ԥ�ÿ�cs*/
#define		CO_INS_PreSetC_End		(CO_INS_PreSetC_CS + 1)						/*����Ԥ�ÿ�������*/
/*�û������������*/
#define		CO_INS_UseC_MeterNum	(CO_INS_Ratio_VT + CLRatio_Vol_Tran_Esam)	/*���*/
#define		CO_INS_UseC_CustNum		(CO_INS_UseC_MeterNum + 6)					/*�ͻ����*/
#define		CO_INS_UseC_Type		(CO_INS_UseC_CustNum + CLCustomer_Num)		/*�û�������*/
#define		CO_INS_UseC_CS			(CO_INS_UseC_Type + 1)						/*�û���CS*/
#define		CO_INS_UseC_End			(CO_INS_UseC_CS + 1)						/*�û���������*/
/*��ע1:�����±��÷��ʵ��ʱ��Ӧͬʱ����2���л�ʱ��
��ע2:�����±��ý��ݵ��ʱ��Ӧͬʱ����2���л�ʱ��
��ע3:������������־ʱ��ָ������� 1��������� 2��������������ȡ���ѹ��������ȣ�*/

/**********����Ԥ�ÿ��е�Ǯ���ļ�******************************************/
#define	C_FC_MoneyInPSC					0x02				/*����Ԥ�ÿ���Ǯ���ļ�*/

#define	C_FC_Price_InPSC_InUse			0x03				/*����Ԥ�ÿ��е�ǰ�׵���ļ�*/
#define	C_FC_PriceBak_InPSC_InUse		0x04				/*����Ԥ�ÿ��б����׵���ļ�*/


#define		CO_PSCM_PPMoney				00					/*Ԥ�ý��ƫ��*/
#define		CO_PSCM_PPNum				(CO_PSCM_PPMoney + CL_PurchasingE_Num)	/*�������ƫ��*/
/**********�û����е�Ǯ���ļ�*************************************************/
#define		C_FC_MoneyInUseCard			0x02
#define		CO_UC_PPMoney				00					/*������ƫ��*/
/**********�û����еķ�д�ļ�*************************************************/
#define		C_FC_WRBackInUseCard		0x05
///*********����������صĺ�*****************************************************///
//�������±�־
#define		C_UPType_CurRate			0x01								/*���µ�ǰ���ʵ��*/
#define		C_UPType_BakRate			0x02								/*���±����׷��ʵ��*/
#define		C_UPType_CurLadder			0x04								/*���µ�ǰ�׽��ݵ��*/
#define		C_UPType_BakLadder			0x08								/*���±����׽��ݵ��*/
#define		C_UPType_Other				0x80								/*����������־*/
#define		C_UPType_ChgRateClock		0x20								/*���׷��ʵ���л�ʱ��*/
/*#define		C_UPType_ChgLadderClock	0x40*/								/*���׽����л�ʱ��*/

/*6��������ȼ���ʽ*/
/*	C_UPType_Other	1�ֽڱ��ñ������1��2+��ѹ���������������+MAC   ��19���ֽ�*/
/*	C_UPType_CurRate 	4�ֽ�(68 CMD Len1 Len2)��ǰ���ʵ��+Mac����136*/
/*	C_UPType_BakRate	4�ֽ�(68 CMD Len1 Len2)���÷��ʵ��+Mac����136*/
/*	C_UPType_ChgRateClock		2�׷��ʵ���л�ʱ��+Mac����9�ֽ�*/
/*	C_UPType_CurLadder	��ǰ�׵��+Mac����68�ֽ�*/
/*	C_UPType_BakLadder		�����׵��+�л�ʱ��+Mac����73�ֽ�*/
#define		CL_UPType_CurRate		136								/*���µ�ǰ���ʵ��*/
#define		CL_UPType_BakRate		136								/*���±����׷��ʵ��*/
#define		CL_UPType_CurLadder		68								/*���µ�ǰ�׽��ݵ��*/
#define		CL_UPType_BakLadder		73								/*���±����׽��ݵ��*/
#define		CL_UPType_Other			19								/*����������־*/
#define		CL_UPType_ChgRateClock	9								/*���׷��ʵ���л�ʱ��*/
/*#define		CL_UPType_ChgRateladderClock	9	*/				/*���׽��ݵ���л�ʱ��*/
/*������������ʱ������ƫ��*/
#define		CO_UPOther_Alam1		1								/*���������б������1*/
#define		CO_UPOther_Alam2		(CO_UPOther_Alam1 + CLAlam1_Money)
#define		CO_UPOther_Ratio_CT		(CO_UPOther_Alam2 + CLAlam2_Money)	/*�������������*/
#define		CO_UPOther_Ratio_VT		(CO_UPOther_Ratio_CT + 3)

/*���±����׽���ʱ�����һ���л�ʱ���ƫ��*/
/*6������ֵ(4�ֽ�)+7�����ݵ��(4�ֽ�)+4�������(3�ֽ�)*/
#define		CO_UPLadderChgClock		(6 * 4 + 7 * 4 + 4 * 3)
/*���·��ʵ��ʱ����Ч���ݴӵ�4�ֽڿ�ʼ*/
#define		CO_UPRate				4

/*********�������ͼ���������**************************************************/
typedef	struct
{
	uchar8	Header[CL_7816Header];					/*С��ģʽ*/
	ushort16	SW1_2;
}Str7816HeaderSW;
extern Str7816HeaderSW	GV_7816CMD;		

typedef	struct
{
	uchar8	CardType;										/*��Ƭ����*/
	uchar8	UserCardType;									/*�û�������*/
	uchar8	UpdateFlag;										/*�������±�־*/
	uchar8	UserCardNull;									/*��д�ļ��Ƿ�Ϊ�ձ�־=C_OK:Null,C_ErrorΪ�ǿ�*/
	uchar8	CardNoEqualFlag;								/*����һ�±�־��*/
	ushort16	PreMoneyClock;								/*����ǰʣ������ʾ��ʼʱ��*/
	ulong32	PPMoney;										/*�������Ǯ����ʼ��ʱԤ�ý��*/
	ulong32	PPNum;											/*�������*/
	uchar8	UPType_CurRate[CL_UPType_CurRate];				/*��ǰ�׵��*/
	uchar8	UPType_BakRate[CL_UPType_BakRate];				/*�����׵��*/
	uchar8	UPType_CurLadder[CL_UPType_CurLadder];			/*��ǰ����*/
	uchar8	UPType_BakLadder[CL_UPType_BakLadder];			/*�����׽���*/
	uchar8	UPType_Other[CL_UPType_Other];					/*��������*/
	uchar8	UPType_ChgRateClock[CL_UPType_ChgRateClock];	/*�����л�ʱ��*/
/*	uchar8	UPType_ChgLadderClock[CL_UPType_ChgRateladderClock];*/	/*�����л�ʱ��	*/
	uchar8	UPType_CustNum[CLCustomer_Num+C_MacLen];		/*�ͻ����*/
	
	uchar8	IC_File[CLen_S_BufMaxLen];						/*��Ƭ�ļ����������ݴ档*/
															/*��ʱ���壬���������*/
	uchar8	IC_ErrEvent[CLAbnorC_Note_1];					/*�쳣�忨�¼���¼��С��ģʽ*/
}StrCardParse;										
/*��ע1:���Ͻṹ���г�IC_File֮�⣬�����������ݾ�����С��ģʽ
IC_File���������,������ĺ���ע�͡�*/

typedef struct
{
	uchar8		V_ucClientNum[8];		/* �ͻ����*/
	uchar8		V_ucOpenFlag;			/* 0������1��ֵ��2�˷�*/
	ulong32		V_ulMoney;				/* ������/Ԥ�ý��(aǮ����ʼ������)*/
	ulong32		V_ulBuyMoneyTime;		/* �������*/
	uchar8		V_CanRecharge;
}MoneyClient_Type;
extern MoneyClient_Type	MoneyClient_Table;					/*�ݴ���Ҫд���ݲ����*/

typedef struct
{
	ulong32 Money;				/* ����ǰ���*/
	ulong32 TouzhiMoney;		/* ����ǰ͸֧���*/
	ulong32 Num;				/* ����ǰ�ۼƴ���*/
}BuyMoneyRecord_Type;
extern BuyMoneyRecord_Type	BuyMoneyRecord_Table;			/*�ݴ湺���¼����*/

typedef struct
{
	ushort16 FreezeTimer;		/*˲ʱ���ᶨʱ��*/
	ushort16 V_CRC16;	
}Str_FreezeTimerTable;
extern Str_FreezeTimerTable FreezeTimerTable;

/**************StrCardParse������д********************************************/
/*IC_File������ݴ����Ԥ�ÿ�Ǯ���ļ���д
��ʽΪԤ�ý��+Mac1+�������+Mac2��Ϊ��˸�ʽ�ݴ�*/
#define		IC_InitM_PPMoney	&pStr_CardParse->IC_File[C_InitM_O_ChgBlHC]	
#define		IC_InitM_PPNum		&pStr_CardParse->IC_File[C_InitM_O_PC_Num]
/*IC_File��Ǯ���ļ�����д*/
/*��ʽΪԤ�ý��+�������+Mac�����*/
#define		IC_PPMoney			&pStr_CardParse->IC_File[0]
#define		IC_PPNum			&pStr_CardParse->IC_File[4]
#define		IC_PPMac			&pStr_CardParse->IC_File[8]
/*IC_File������ݴ�ָ���ļ�ʱ��д*/
#define		IC_INS_Start		pStr_CardParse->IC_File[CO_INS_Start]
#define		IC_INS_CMD			pStr_CardParse->IC_File[CO_INS_CMD]	
#define		IC_INS_Len			&pStr_CardParse->IC_File[CO_INS_Len]	
#define		IC_INS_UpdataPFlag	pStr_CardParse->IC_File[CO_INS_UpdataPFlag]	
#define		IC_INS_ChgRate		&pStr_CardParse->IC_File[CO_INS_ChgRate]
#define		IC_INS_AlarmM1		&pStr_CardParse->IC_File[CO_INS_AlarmM1]
#define		IC_INS_AlarmM2		&pStr_CardParse->IC_File[CO_INS_AlarmM2]	
#define		IC_INS_Ratio_CT		&pStr_CardParse->IC_File[CO_INS_Ratio_CT]	
#define		IC_INS_Ratio_VT		&pStr_CardParse->IC_File[CO_INS_Ratio_VT]

#define		IC_INS_PreSetC_CS	pStr_CardParse->IC_File[CO_INS_PreSetC_CS]	
#define		IC_INS_PreSetC_End	pStr_CardParse->IC_File[CO_INS_PreSetC_End]	

#define		IC_INS_UseC_MeterNum	&pStr_CardParse->IC_File[CO_INS_UseC_MeterNum]
#define		IC_INS_UseC_CustNum		&pStr_CardParse->IC_File[CO_INS_UseC_CustNum]	
#define		IC_INS_UseC_Type		pStr_CardParse->IC_File[CO_INS_UseC_Type]	
#define		IC_INS_UseC_CS			pStr_CardParse->IC_File[CO_INS_UseC_CS]	
#define		IC_INS_UseC_End			pStr_CardParse->IC_File[CO_INS_UseC_End]

/*�쳣�忨��¼����д*/
#define		IC_ErrStatus		pStr_CardParse->IC_ErrEvent[CO_CE_ErrStatus]
#define		IC_CardNo			&(pStr_CardParse->IC_ErrEvent[CO_CE_CardNo])
#define		IC_Err7816Header	&(pStr_CardParse->IC_ErrEvent[CO_CE_7816Header])
#define		IC_ErrSW1_2			&(pStr_CardParse->IC_ErrEvent[CO_CE_ErrSW1_2])
	

#define Plain_MAC 	0x11 		/*����+mac����*/
#define Secret 		0xA6 		/*����*/
#define Secret_MAC 	0xa7 		/*����+mac����*/

#define Master_Address 	0xA0 	/*��վ��ַ*/
#define Termal_Address 	0x00	/*�ն˵�ַ*/

/*********** ����Ϊ����ӿں���***********************************************/

/*��ȫ��֤*/
extern	ushort16	InF_S_Authentication(uchar8 *pV_ucData, uchar8 *pV_ucLen);	
/*�����֤ʧЧ*/
extern	ushort16  InF_S_Certification_Invaliad(uchar8 *pV_ucData,uchar8 *pV_ucLen);
/*�����֤ʧЧʱ��*/
extern	ushort16	InF_S_WriteCertificationTime(uchar8	*pV_ucData);
/*������֤����*/
extern	ushort16  InF_S_IRCertification_Request(uchar8 *pV_ucData,uchar8 *pLen,uchar8 BufMaxLen);
/*������֤*/
extern	ushort16  InF_S_IRCertification_Instruction(uchar8 *pV_ucData);
/*��ԿMac��֤*/
extern	ushort16  InF_S_Key_V_Mac(uchar8 *pV_ucData,uchar8 DataLen,uchar8 *pV_ucMsgReupdataKey,uchar8 *pV_ucKeyNum);
/*��Կ��װ*/
extern	ushort16  InF_S_Key_Update (uchar8 *pV_ucData, uchar8 KeyNO);
/*��Կ״̬����*/
extern	ushort16  InF_S_UpdateState (void);
/*��ȡESAM����Կ״̬*/
extern	ushort16  InF_S_ReadKeyStateInESAM(uchar8 *pV_ucData,uchar8 *pV_ucDataLen);
/*״̬��ѯ*/
extern	ushort16  InF_S_GetStatus(uchar8 *pV_ucData, uchar8 *pV_ucLen);
/*���ݻس�*/
extern	ushort16  InF_S_DataExcerption(uchar8 *pV_ucData,uchar8 *pV_ucDataLen);
/*�ж��Ƿ�Ϊ1�����*/
extern	uchar8	InF_S_Is_ParmPlainTextMAC(ulong32	V_ulDI,	uchar8 	*pV_ucDataLen);
/* 1�����Mac��֤��ESAM��Ӧ����д*/
extern	ushort16  InF_S_WritePara_PlainTextMAC(ulong32 V_ulDI,uchar8 *pV_ucData,uchar8 V_ucDataLen);
extern	ushort16  InF_S_WriteCustermerNumMAC(ulong32 V_ulDI,uchar8 *pV_ucData,uchar8 V_ucDataLen);

/* 2���������*/
extern	ushort16  InF_S_WritePara_CipherTextMAC(ulong32 V_ucDI,uchar8 *pV_ucData,uchar8 *pV_ucLength);
/*������*/
extern	ushort16  InF_S_MeterClear( uchar8 *pV_ucData,uchar8 *pV_ucLength);
extern	ushort16  InF_S_DemandClear( uchar8 *pV_ucData,uchar8 *pV_ucLength);
extern	ushort16  InF_S_EventClear( uchar8 *pV_ucData,uchar8 *pV_ucLength);
/*���Ĵ�MacдESAM*/
extern	ushort16	InF_S_WriteESAMPara_PlainTextMAC(uchar8 *pV_ucData,uchar8 V_Length);
/*���Ĵ�MacдESAM*/
extern	ushort16  InF_S_WriteESAMPara_CipherTextMAC (uchar8 *pV_ucData,uchar8 V_Length);
/*��ȡ���ݲ���Կ������*/
extern	uchar8	InF_Get_Key_Tol_Num(void);
/*Զ�̸��ɿ��ؿ���*/
extern	ushort16  InF_S_ControlCommand( uchar8 *pV_ucData,uchar8 *pV_ucLength);
/*дԶ���˷��ļ������������˷ѽ��+Mac*/
extern	ushort16	InF_S_WR_ReturnFile(uchar8 *pV_ucData,uchar8 V_ucLength);
extern	ushort16	InF_S_OPMoneyFile_Return(uchar8 *pV_ucData);
/***************���º���Ϊ��ȫģ���ṩ�ı��ر�ӿں���*********************/
/*Զ�̳�ʼ��Ǯ��*/
extern	ushort16	InF_S_InitMoney(uchar8 V_ucSrcMsg,uchar8 *pV_ucData);
/*��ȡESAM�й������*/
#if (_DEBUG_LX)
extern	ushort16	InF_S_GetPPNum(ulong32	*pV_ulPPNum);
#endif
/*��ESAMǮ���ļ����г�ֵMac��֤����ֵ����*/
extern	ushort16	InF_S_Purchase(uchar8	*pV_ucData);


/***************���º���Ϊ��ȫģ���ṩ�Ŀ�����ӿں���*********************/

/*�Կ������临λ*/
extern	uchar8	InF_S_ColdRestCard(uchar8	*pV_ucCardNo);
/*�ļ�ѡ��*/
extern	uchar8	InF_S_SelectFile(uchar8 V_ucCH, ushort16 V_usFileName);
/*����Mac���������ļ�*/
extern	uchar8	InF_SC_RDBinFileNoMac(uchar8 V_ucCH,uchar8 V_ucFileNo,uchar8 V_ucParmOffset,ushort16 V_usParmLen,uchar8 *pV_ucData);
/*�ж��ļ���ʽ*/
extern	uchar8	InF_SC_Judge_CardFile(uchar8	*pV_ucFile);
/*�����ⲿ��֤*/
extern	uchar8	InF_SC_L_Auth(uchar8 *pV_ucIC_CardNo);
/*��ESAM����4�ֽ������*/
extern	uchar8	InF_SC_GenerateRandToCalMac(uchar8	V_ucCH, uchar8 V_ucLength);
/*��Mac��ȡ����Ԥ�ÿ�/�û���Ǯ���ļ�*/
extern	uchar8	InF_SC_Get_MFile_Card(StrCardParse	*pStr_CardParse);
/*��Mac��д������(ESAM)һ�����������������ݵߵ���*/
extern	uchar8	InF_SC_Backup_With_Mac(uchar8	V_ucType, uchar8 *pV_ucData);
extern	uchar8	InF_SC_BackupW_With_Mac(uchar8 	V_ucType, uchar8 *pV_ucData);
extern	void	InF_BackupData_Reversal(uchar8 	V_ucType, uchar8 *pV_ucData);

/*�ⲿ��֤*/
extern	uchar8	InF_SC_CardExtAuth(uchar8	*pV_ucCardNo);
/*����ж�*/
extern	uchar8	InF_SC_Meter_Num_OK(uchar8	*pV_ucMeterNum);
/*��д�ļ�Ϊ���ж�*/
extern	uchar8	InF_SC_Is_UserCardNull(uchar8	*pV_ucFlag);
/*��Mac��ȡ�û����еĿͻ����*/
extern	uchar8	InF_SC_GetCustNumWithMac_UseCard(uchar8 *pV_ucCustNum);
extern	void		Updata_ESAM_OpParm(uchar8	V_ucMsgNum);
extern	uchar8	InF_SC_WR_UCReturnFile(uchar8 *pV_ucCardNo);
/***************���º���Ϊͨ��ģ���ṩ�ģ���������ģ����ú���********/
/*ˢ��״̬��3�п���״̬*/
extern	void		InF_UpdateAccountStateInMeterStatus3(void);
/*д��1�ι����¼*/
extern	void		InF_WRPre1PowerPurchaseRecord(ulong32 V_ulBuyMoney,uchar8 C_SafeFlag,uchar8 Flag);
/*����Զ�̡����ؿ�����־*/
extern	uchar8	InF_DealWith_L_R_OAAFlag(uchar8	Method,uchar8	Value);
/*�Ƚ����ݲ�Ŀͻ����*/
extern	uchar8	InF_Compare_CustomerNum(uchar8		*pCustomerNum);
extern	ushort16		InF_V_CustomerNumWithEsam(uchar8		*pCustomerNum);
extern	uchar8	Is_AllOfficialKey(void);

/*�жϹ������,��ֵ���*/
#define	C_PC_Num_Equal				0xFE			/* ����������*/
#define	C_Can_EPurchase 			0xFD			/*���������1�����û�г��ڻ�*/
#define	C_MeterPC_Num_Large			0xFC			/*���ڹ��������*/
extern	ushort16		InF_Judge_ChgBal_PC_Num(ulong32	V_ChgBal,ulong32 V_PC_Num);
/*��ɳ�ֵ����*/
extern	void		InF_PurchaseDL(ulong32	PPMoney,uchar8	V_SafeFlag);


#define C_CardStatusOK		0x0001		/*�忨�ɹ�*/
#define C_CardStatusERR		0x0002		/*�忨ʧ��*/
#define	C_CardStatusUnknow	0x0000		/*δ֪*/
extern	void InF_WriteCardStatus(ushort16 V_usCardFlay);
extern	uchar8 Is_AllOfficialKey(void);
extern	void Comm_SendMsgToDisp(uchar8 DispSign,uchar8	DispMode,ushort16 Duration);
#define C_ReadESAM_698	0x00
#define C_ActionESAM_698	0x01


/*ESAM�����궨��*/
#define	C_ReadEsam_698   	0	/*��esam����*/
#define	C_ActionEsam_698   	1	/*����esam*/


#define		C_demand					254		/*�����������*/
#define		C_demand_Com				253		/*����޹������������,�з���*/

/*Ӧ�����ӷ��ش������ͺ궨��*/
#define     C_PasswordErr_DAR			1	/* �������*/
#define     C_SymmDecodeErr_DAR			2	/* �Գƽ��ܴ��� */
#define     C_DissymmDecodeErr_DAR		3	/* �ǶԳƽ��ܴ��� */
#define     C_SignErr_DAR				4	/* ǩ������ */
#define     C_VersionErr_DAR			5	/* Э��汾��ƥ��*/
#define     C_ESAMCommFault_DAR			6	/* ESAMͨ�Ź���*/

#define		C_StateOfOfficialKey		CInfo_OfficialKey
#define		C_StateOfTestKey			CInfo_TestKey

#define	C_SPTNumAdd					0x01			/*SPT����*/
#define	C_JudgeSPTVariable			0x02			/*SPT�ж�*/
#define	C_InitSPTVariable			0x03			/*��ʼ��SPT����*/

//#define	C_Init_TimerExceed10min	0x01			/*��ʼ���ķ���*/
#define		C_Set_TimerExceed10min	0x02			/*���÷���*/
#define		C_Dec_TimerExceed10min	0x03			/*�ۼ�1�ķ���*/
#define		C_Sub_TimerExceed10min	0x04			/*�ۼ�ָ��ֵ�ķ���*/

#define	C_IRAuthTime_L	30
#define	C_IRAuthTime_H	0x00				/*������֤30����*/

#define C_Remain_termal   0xF1001502		/*�����ն�ʣ��ʱ��*/
/*#define C_Remain_termal_Item   0xA4*/		/*����*/

#define	C_SID_P1P2_01		0x01	/*������ս�ỰʱЧ����*/
#define	C_SID_P1P2_04		0x04	/*�����ն˻ỰʱЧ����*/
#define	C_SID_P1P2_05		0x05	/*�����ն˵�ַ*/
#define	C_SID_P1P2_06		0x06	/*�����ն˹㲥������*/
#define	C_SID_P1P2_07		0x07	/*���������֤���ñ�־*/


extern  uchar8  INF_S_ActionEsam_698(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen,uchar8 V_ucClientAddr);
extern	uchar8 	InF_S_Authentication_698(uchar8 *pV_ucData, ushort16* V_usLen,uchar8 V_ucClientAddr);

extern	uchar8  INF_S_Encrypt_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucSecurityMode, uchar8 V_ucEncryptMode, uchar8 *pV_ucRN_Data, uchar8 *pV_ucMAC_Data, uchar8 V_ucClientAddr);
extern	uchar8	INF_S_Decrypt_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucSecurityMode, uchar8 *pV_ucSID_Data);

extern uchar8	InF_JudgeKeyStatus(void);
extern uchar8	Is_Buf_AllZero(uchar8	*pData,uchar8	DataLen);
extern uchar8	Comm_DealwithSPTVariable(uchar8 method);
extern void		DealWith_IR_Auth_Timer(uchar8 Method,uchar8 *pVTimer);
extern void DataReversed(ulong32 V_ulReversedMethod, uchar8 *pV_ucData, uchar8 V_ucR_ItemNum);
extern	void	DealWith_ID_Auth_T_Timer(uchar8 Method,uchar8 *pVTimer);
#endif

