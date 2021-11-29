/****************************************************************************************
Copyright:	ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:	DataProcess.c
Version:	V1
Date:		2021-10-20
Description:���ݲ��ļ�
Function List:
****************************************************************************************
History1:	��1���޸�
����1.	Date:20211002
		Author:MYM��WJQ��GG
		Modification:
		**********************************************
����2.	Date:
		Author:
		Modification:
		********************************************************************************
History2:	��2���޸�
����1.	Date:
		Author:
		Modification:
		**********************************************
����2.	Date:
		Author:
		Modification:
****************************************************************************************/

#include "Public.h"
#include "DataProcess.h"
#include "Communication.h"
#include "fm33A0xx_flash.h"

extern ConectRequest_Type	Com_Conect;
/**********************************************************************************
����ԭ�ͣ�uchar8 SF_EraseFlashAndWriteEmptySign(ulong32 V_FlashAddr)
��������������V_FlashAddrFlash��Ȼ��д��ҳFlash���4���ֽ�Ϊ�ձ�־0x68��ֻ��Ϊ4��68����Ϊ��ҳFlashΪ��
���������ulong32V_FlashAddr�������Flash��ַ��
����������ޣ�
���ز�����C_OK��C_SafeFlagError
����˵����
���û��ƣ�
��     ע���ڲ��жϰ�ȫ��־
**********************************************************************************/
uchar8 SF_EraseFlashAndWriteEmptySign(ulong32 V_FlashAddr)
{
	uchar8 V_Flash_Empty[4], V_i;

	V_FlashAddr = V_FlashAddr & 0xFFFFF000;			/*ҳ��ַ*/

	for(V_i = 0; V_i < C_Flash_EmptyNum; V_i++)
	{
		V_Flash_Empty[V_i] = C_Flash_Empty68;		/*дFlashΪ�ձ�־��0x68*/
	}

	InF_FlashChipSelect();
	if(C_W_SafeFlag != GV_D_SafeFlag)				/*��ȫ��־��*/
	{
		InF_FlashChipDeselect();					/*�ر�CS*/
		GV_D_SafeFlag = C_Clear_SafeFlag;
		return C_SafeFlagError;
	}
	InF_EraseFlash(V_FlashAddr);

	V_FlashAddr = V_FlashAddr + C_OneFlashPage - C_Flash_EmptyNum;	/*���4���ֽ�Flash��ַ*/
	InF_FlashChipSelect();
	if(C_W_SafeFlag != GV_D_SafeFlag)		/*��ȫ��־��*/
	{
		InF_FlashChipDeselect();		/*�ر�CS*/
		GV_D_SafeFlag = C_Clear_SafeFlag;
		return C_SafeFlagError;
	}
	InF_WriteFlash(V_FlashAddr, &V_Flash_Empty[0], C_Flash_EmptyNum);
	return C_OK;
}
/***********************************************************************************
����ԭ�ͣ�void InF_ReadE2_Flash_Data(uchar8 *PV_Data, uchar8 V_Len, uchar8 V_Sign, ulong32 V_Addr);
���������������ã����ײ�E2��Flash��ַ�������ݣ������Ӷ�RAM����
���������
		uchar8*PV_Data:�����ݻ��棻
		uchar8V_Len�������ݳ��ȣ�
		uchar8V_Sign����E2��Flash��־��01����E2��02����Flash��
		ulong32V_Addr����E2��Flash��ַ��
�����������
���ز������ޣ�
����˵����
���û��ƣ�
��     ע��
**********************************************************************************/
#if (C_NiuDebugReadData)
void InF_ReadE2_Flash_Data(uchar8 *PV_Data, uchar8 V_Len, uchar8 V_Sign, ulong32 V_Addr)
{
	ushort16 V_E2Addr;

	V_E2Addr = (ushort16)V_Addr;

	switch(V_Sign)
	{
			case	C_ReadRamFlay:		/*��RAM*/
			{
				SF_Re_RAM_Data((uchar8 *)V_Addr, V_Len, PV_Data, 0, 0);		/*0,0�˶Ըú�����ڶ���*/
				break;
			}
			case	C_ReadFlashFlay:	/*��Flash*/
			{
				InF_ReadFlash(V_Addr, PV_Data, V_Len);
				break;
			}
			case	C_ReadE2Flay:		/*��E2*/
			{
				InF_ReadE2(V_E2Addr, PV_Data, V_Len);
				break;
			}
			case	C_ReadFRAMFlay:		/*������*/
			{
				InF_ReadFRAM(V_E2Addr, PV_Data, V_Len);
				break;
			}
//			case	C_ReadMCUFlay:		/*��MCU*/
//			{
//				InF_ReadMCU(V_Addr, PV_Data, V_Len);
//				break;
//			}
			default:
				break;
	}
}
#endif

/**********************************************************************************
����ԭ�ͣ�uchar8 InF_Write_RecMeterData(uchar8 Msg_Num, uchar8 *P_Data, uchar8 V_Data_Length,
										uchar8 V_W_Safe_Flag, uchar8 V_Data_Num);
����������д���ݲ�У�����ݽӿں���
���������
		uchar8 Msg_Num����Ϣ�ţ������ж��Ƿ���дȨ�ޣ�
		uchar8 *P_Data���������Ż��棻
		uchar8 V_Data_Length����д���ݳ��ȣ�
		uchar8 V_W_Safe_Flag���궨�壬��д��ȫ��־��
		uchar8 V_Data_Num��дУ��������ţ���У�����ݴ�W2��ַƫ��һһ��Ӧ�����ݲ��ڲ��ж����ֵ����ų�����C_NoAccess��
�����������
���ز�����C_OK��C_IICError��C_DataLenError��C_SafeFlagError��C_NoAccess��
����˵����
���û��ƣ�
��     ע��д���ݲ�ʱ���ã�ע�ⰲȫ��־
**********************************************************************************/
uchar8 InF_Write_RecMeterData(uchar8 Msg_Num, uchar8 *P_Data, uchar8 V_Data_Length, uchar8 V_W_Safe_Flag, uchar8 V_Data_Num)
{
	ushort16 V_3TableE2Addr;
	uchar8 V_Return_Flag;

	GV_D_SafeFlag = C_Clear_SafeFlag;

	if(V_W_Safe_Flag != C_W_SafeFlag)
	{
		return C_SafeFlagError;
	}

	if(C_Msg_Communication != Msg_Num)
	{
		return C_NoAccess;
	}

	if(C_MeterICE2ResLen != V_Data_Length)
	{
		return C_DataLenError;
	}

	GV_D_SafeFlag = GV_D_SafeFlag | C_W_SafeFlag_1;
	if(V_Data_Num >= C_MeterICDataNum_T)
	{
		return C_DataLenError;
	}

	GV_D_SafeFlag = GV_D_SafeFlag | C_W_SafeFlag_2;
	V_3TableE2Addr = E2Addr_MeterIC_St + V_Data_Num * (C_MeterICE2ResLen + C_CRCLen2);		/*Ҫ����E2��ַ*/
	if(V_3TableE2Addr > (E2Addr_MeterIC_End - C_MeterICE2ResLen - C_CRCLen2))				/*E2��ַ����*/
	{
		return C_DataLenError;
	}

	GV_D_SafeFlag = GV_D_SafeFlag | C_W_SafeFlag_3;
	V_Return_Flag = SF_WriteE2Three(V_3TableE2Addr, C_MeterICE2ResLen, P_Data);				/*дE2����*/
	GV_D_SafeFlag = C_Clear_SafeFlag;

	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�ushort16 SF_GetEventDataLen(ushort16 V_TB_E2BakeUp1Addr, ushort16 V_TBLen_E2BakeUp1Addr,
										ulong32 PStr_4aTableAddr1, uchar8 V_Str_4aTableLen)
������������ȡ�¼�OAD�б��Ӧ���ݳ���
���������
		ushort16 V_TB_E2BakeUp1Addr���ɱ�����б�E2��ַ��
		ushort16 V_TBLen_E2BakeUp1Addr���ɱ�����б����E2��ַ��
		ulong32 PStr_4aTableAddr1���̶������б�4����
		uchar8 V_Str_4aTableLen���̶������б�4����ṹ�������
		uchar8 V_Type:
		//#defineC_TolTabDataLenSign1	�̶�������OAD�б���Ӧ�����ܳ���
		//#defineC_FixTabDataLenSign2	�̶�OAD�б���Ӧ�����ܳ���
		//#defineC_TabDataLenSign3		�ɱ�OAD�б���Ӧ�����ܳ���
�����������
���ز�����ushort16�����ݳ��ȣ���E2���������쳣ʱ������ȫFF��0��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
ushort16 SF_GetEventDataLen(ushort16 V_TB_E2BakeUp1Addr, ushort16 V_TBLen_E2BakeUp1Addr, ulong32 PStr_4aTableAddr1, uchar8 V_Str_4aTableLen)
{
	ushort16 V_OADOrder16, V_Data_Length1, V_Data_Length2;
	uchar8 V_Return_Flag;
	uchar8 PV_Data[C_698Event_OADTabLen];
	uchar8 V_Data_Num, V_i;
	Str_4aTable *PStr_4aTableAddr = NULL;

	V_Data_Length1 = 0;
	if(0xFFFFFFFF == PStr_4aTableAddr1)
	{
		return V_Data_Length1;
	}

	PStr_4aTableAddr = (Str_4aTable *)(PStr_4aTableAddr1);

	/*�ɱ��б�*/
	V_Return_Flag = SF_ReadE2Three(V_TBLen_E2BakeUp1Addr, CLVariableAssociatedOADNum, &V_Data_Num);
	if(C_OK != V_Return_Flag)
	{
		return V_Data_Length1;
	}

	if(C_698Event_OADTabDataType * V_Data_Num > C_698Event_OADTabLen)	/*���������ڣ�д����ʱҲ���жϳ���*/
	{
		return V_Data_Length1;
	}

	if(0 != V_Data_Num)
	{
		V_Return_Flag = SF_ReadE2Three(V_TB_E2BakeUp1Addr, (C_698Event_OADTabDataType * V_Data_Num), PV_Data);
		if(C_OK != V_Return_Flag)
		{
			return V_Data_Length1;
		}

		for(V_i = 0; V_i < V_Data_Num; V_i++)
		{
			PF_Buffer2ToUshort16(&PV_Data[C_698Event_OADTabDataType * V_i], &V_OADOrder16);
			V_OADOrder16 &= 0x1FFF;
			if(V_OADOrder16 >= Str_FrozenConvert_Table_Len)
			{
				return 0;	/*�쳣*/
			}

			V_Data_Length1 = V_Data_Length1 + Str_FrozenConvert_Table[V_OADOrder16].V_uc645Length;
		}
	}

	/*�̶��б�*/
	V_Data_Length2 = 0;
	for(V_i = 0; V_i < V_Str_4aTableLen; V_i++)
	{
		V_Data_Length2 += (PStr_4aTableAddr[V_i].V_DataLen & C_EventOutSign);
	}

	return (V_Data_Length1 + V_Data_Length2);
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WriteFlash_DataEventTable(uchar8 *P_Data, ushort16 V_Data_Length,
			Str_3dEventTable *P_Str_3dEventTableAddr, ulong32 V_Data_Id, ushort16 V_3dTable_Line, uchar8 V_Type)
����������дFlash����,698�¼���¼��DI0Ϊ1��ʾ�������ݣ�DIΪ2��ʾ��������
���������
		uchar8 *P_Data:д���ݻ��棻
		ushort16 V_Data_Length��д���ݾ��峤�ȣ�
		Str_3dEventTable *P_Str_3dEventTableAddr����Ӧ4������׵�ַ��
		ulong32 V_Data_Id��DI0-DI3���ݱ�ʶ��
		ushort16 V_3dTable_Line��Ҫ����3d������кţ�
		uchar8 V_Type:���ݴ洢����
�����������
���ز�����C_OK��C_SafeFlagError��C_SPIError,C_IICError��C_NoAccess��C_DataLenError��
����˵����
���û��ƣ�
��     ע��дFlash���ݣ��ڲ�û�п�ҳ����
*********************************************************************************/
/*#define C_TempRAM_Max 512		��ʱ���棬�¼���󳤶�*/
uchar8 SF_WriteFlash_DataEventTable(uchar8 *P_Data, ushort16 V_Data_Length, Str_3dEventTable *P_Str_3dEventTableAddr,
									ulong32 V_Data_Id, ushort16 V_3dTable_Line, uchar8 V_Type)
{
	uchar8 P_Dgree[CLAll_Loss_Vol_Degree];
	ushort16 V_E2Addr;
	ulong32 V_Dgree;
	Str_3dEventTable VStr_3dEventTableAddr;
	ulong32 P_FlashAddr1[2];
	uchar8 V_Return_Flag;
	uchar8 V_EvenSign;
	ushort16 V_Data_TolLength;

	if(V_3dTable_Line >= Str_3dTable_Flash_Len)
	{
		return C_AbnormalError;		/*����������*/
	}

	VStr_3dEventTableAddr = P_Str_3dEventTableAddr[V_3dTable_Line];
	V_EvenSign = (uchar8)(V_Data_Id & 0x000000FF);		/*ȡDI0*/
	if((1 != V_EvenSign) && (2 != V_EvenSign))			/*1�������ݣ�2��������*/
	{
		return C_NoAccess;
	}

	V_E2Addr = VStr_3dEventTableAddr.V_Num_E2BakeUp1Addr;		/*ȡFlash��¼����E2��ַ*/

	V_Return_Flag = SF_ReadE2Three(V_E2Addr, CLAll_Loss_Vol_Degree, &P_Dgree[0]);
	if( (C_OK != V_Return_Flag) && (C_CrcErr_DataZero != V_Return_Flag) )
	{
		return V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&P_Dgree[0], &V_Dgree,4);
	GV_D_SafeFlag = C_W_SafeFlag_2 | GV_D_SafeFlag;				/*�ð�ȫ��־*/

	if(1 == V_EvenSign)		/*Լ��д������DI0Ϊ1*/
	{
		V_Dgree = V_Dgree + 1;
	}

	/*��ȡ�б��Ӧ���ݳ���*/
	V_Data_TolLength = SF_GetEventDataLen(VStr_3dEventTableAddr.V_TB_E2BakeUp1Addr, VStr_3dEventTableAddr.V_TBLen_E2BakeUp1Addr,
											VStr_3dEventTableAddr.PStr_4aTableAddr, VStr_3dEventTableAddr.V_Str_4aTableLen);
	if((0==V_Data_TolLength)||(0xFFFF==V_Data_TolLength))
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_DataLenError;
	}

	if(V_Data_TolLength!=V_Data_Length)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_DataLenError;
	}

	SF_GetFlashAddr(V_Dgree,VStr_3dEventTableAddr.V_StaFlashAddr,V_Data_TolLength,VStr_3dEventTableAddr.V_EndFlashAddr,&P_FlashAddr1[0]);
	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag; 	/*�ð�ȫ��־*/
	/*��Ҫд��Flash��Ȼ�󸲸��ж�д��*/
	P_FlashAddr1[0]=P_FlashAddr1[0]+P_FlashAddr1[1];
	if(P_FlashAddr1[0]>C_Flash_Max_Addr)	/*Flash��ַ�������۲����� */
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_AbnormalError;
	}

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	V_Return_Flag=SF_WriteFlash(P_FlashAddr1[0],&P_Data[0],V_Data_TolLength,V_EvenSign);
	if(C_OK!=V_Return_Flag)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return V_Return_Flag;
	}

	PF_Ulong32ToBuffer4(&P_Dgree[0],&V_Dgree,4);
	if(1==V_EvenSign)	/*Լ��д������DI0Ϊ1*/
	{
		V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLAll_Loss_Vol_Degree,&P_Dgree[0]);	/*дE2��¼����*/
	}
	GV_D_SafeFlag=C_Clear_SafeFlag;
	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WR_E21CRC_Data698(ushort16 V_E2Addr, ushort16 V_DataLen, uchar8 *P_Data)
����������дE21������,��CRC
���������
		ushort16V_E2Addr��д������E2��ַ��
		ushort16V_DataLen��Ҫд�����ݳ���
		uchar8*P_Data��Ҫд�����ݻ���
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��
����˵����
���û��ƣ�
��     ע��д�벻���Ƚ�
*********************************************************************************/
uchar8 SF_WR_E21CRC_Data698(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_Return_Flag;
	uchar8 P_CRC[2];
	ushort16 V_CRC16;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;	/*�ð�ȫ��־*/

	V_CRC16=PF_Cal_CRC(&P_Data[0],V_DataLen);	/*����CRC*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;	/*�ð�ȫ��־*/

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	InF_E2WPEnable();
	if(C_W_SafeFlag!=GV_D_SafeFlag)		/*��ȫ��־��*/
	{
		InF_E2WPDisable();	/*�ر�WP*/
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}
	V_Return_Flag=InF_WriteE2(V_E2Addr,P_Data,V_DataLen);
	InF_E2WPEnable();
	V_Return_Flag=InF_WriteE2((V_E2Addr+V_DataLen),&P_CRC[0],2);	/*дCRC*/

	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 InF_Write_Data(uchar8 Msg_Num, ulong32 V_Data_Id, uchar8 *P_Data, ushort16 V_Data_Length, uchar8 V_W_Safe_Flag);
����������д���ݲ�ӿں���
���������
		uchar8 Msg_Num:��Ϣ�ţ������ж��Ƿ���дȨ�ޣ�
		ulong32 V_Data_Id�����ݱ�ʶ�룻
		uchar8 *P_Data���������Ż��棻
		ushort16 V_Data_Length����д���ݳ��ȣ�
		uchar8 V_W_Safe_Flag���궨�壬��д��ȫ��־��
�����������
���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_SafeFlagError��C_NoAccess��
����˵����
���û��ƣ�
��     ע��д���ݲ�ʱ���ã�ע�ⰲȫ��־
*********************************************************************************/
uchar8 InF_Write_Data(uchar8 Msg_Num,ulong32 V_Data_Id,uchar8 *P_Data,ushort16 V_Data_Length,uchar8 V_W_Safe_Flag)
{
	uchar8 V_Return_Flag,V_WR_Mes;
	ushort16 V_Line,V_3TableE2Addr;
	Str_2Table *PStr_2TableAddr;
	Str_3aTable *PStr_3aTableAddr;
	uchar8 *P_3TableRamAddr;
	Str_3cTable *P_Str_3cTableAddr;
	uchar8 V_DI[4];
	ushort16 V_DataLen;
	Str_3dEventTable *P_Str_3dEventTableAddr;

	GV_D_SafeFlag = C_W_SafeFlag_1; 	/*�ð�ȫ��־,��һ�θ�ֵ������ֱ�Ӹ�ֵ�ķ�ʽ������֮ǰ�д����λ*/

	PF_Ulong32ToBuffer4(&V_DI[0],&V_Data_Id,4);

	V_DataLen=V_Data_Length;

	if(V_W_Safe_Flag!=C_W_SafeFlag)
	{
		return C_SafeFlagError;
	}

	if( (V_Data_Id&0xFFFF0000) == 0xFF860000)	/*����������*/
	{
		V_Return_Flag = SF_Deal_FF86(V_Data_Id, P_Data, V_Data_Length);

		return V_Return_Flag;
	}

	if(0x50==V_DI[3])	/*******698д��������********/
	{
		V_Return_Flag=SF_Write698FreezeData(V_DI[2],Msg_Num,P_Data,V_Data_Length);
		return V_Return_Flag;
	}

	/******************************����Ϊͨ�����ݲ���**********************************************/
	V_Return_Flag=SF_Find1Table_Data(V_DI[3],&V_Line);
	if(V_Return_Flag!=C_OK)
	{
		 return V_Return_Flag;
	}

	V_WR_Mes=C_WR_Data&Msg_Num;		/*д����*/

	if(0x04==V_DI[3])				/*�α�����2���ֱ����⴦�����ӱ�������Ч��*/
	{
		V_Return_Flag=SF_Find2Table_DIParamChild(V_DI[2],&V_Line);
		if(V_Return_Flag!=C_OK)
		{
			return V_Return_Flag;
		}

		PStr_2TableAddr=(Str_2Table *)(Str_2Table_DIParamChild[V_Line].PStr_2TableParamChildAddr);	/*DI2��Ӧ��2�����ַ*/
		V_Return_Flag=SF_Find2Table_Data(V_WR_Mes,V_Data_Id,&V_Data_Length,PStr_2TableAddr,&V_Line,Str_2Table_DIParamChild[V_Line].V_Str_2TableLen);
	}
	else
	{
		PStr_2TableAddr=(Str_2Table * )(Str_1Table_DI3[V_Line].PStr_2TableAddr);	/*DI3��Ӧ��2�����ַ*/
		V_Return_Flag=SF_Find2Table_Data(V_WR_Mes,V_Data_Id,&V_Data_Length,PStr_2TableAddr,&V_Line,Str_1Table_DI3[V_Line].V_Str_2TableLen);
	}

	if(V_Return_Flag!=C_OK)
	{
		return V_Return_Flag;
	}

	switch(PStr_2TableAddr[V_Line].V_DT_Type)   /*DI2-DI0��Ӧ2���������кţ���ͬ���ݴ���ʽ*/
	{
		case DT_Ref_E23_RAMCRC:                   /*��E2����CRC���ݼ�RAM��CRC(д��������ʱ����дRAM�����Ÿ���E2����)*/
		case DT_Ref_E23_RAMCRC_DI0:               /*19��E2����RAM��CRC�����ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
		                                          /*���ݵ�ַ��DI�ж��Ƿ���ȷ�����������״̬�֣��б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
		case DT_W_Ref_E23_RAMCRC_Te:              /*26:дE2 RAM���ݣ�д��ʱģ��һ��д�룬���ݲ��ڲ����������ֿ�д���統ǰ�׷��ʵ�����ݿ�*/
		case DT_Ref_E23_RAMCRC_DI0_2:             /*28��E2����RAM��CRC�����ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��1,DI0=0,1Ҫ����)�������ڲ�����*/
		{                                           /*���ݵ�ַ��DI�ж��Ƿ���ȷ��������ȫʧѹ��������������ã��б��ʱ����Ӧ���ݴ洢��ַ(��ѹ�쳣�жϵ�ѹ��ַ)��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
			PStr_3aTableAddr=(Str_3aTable *)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*ȡ3�����ַ*/
			if((V_Data_Id&0xFFFFFF00)==(CL_Free_OADTab&0xFFFFFF00))/*����OAD��ű�,д���ݲ��ж����ݳ��ȣ����ж�д���ݳ��Ȳ��ܴ�����󳤶�*/
			{
				V_Return_Flag=SF_WR_E23_RAM_Data698(&PStr_3aTableAddr[PStr_2TableAddr[V_Line].V_LineNum],V_Data_Length,P_Data,PStr_2TableAddr[V_Line].V_DT_Type,V_DI[0]);
			}
			else
			{
				V_Return_Flag=SF_WR_E23_RAM_Data(PStr_3aTableAddr,PStr_2TableAddr[V_Line].V_LineNum,V_Data_Length,P_Data,PStr_2TableAddr[V_Line].V_DT_Type,V_DI[0]);
			}
		}break;

		case DT_Ti_E23_RAMCRC:                    /*��E2����CRC���ݼ�RAM��CRC(д��������ʱ��ֻдRAM����ʱдE2����Ҫ�ǵ�ǰ������������)��ע�⣺Ŀǰ698����ɿ�������д���缰RAM���� */
		{
			PStr_3aTableAddr=(Str_3aTable *)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*ȡ3�����ַ*/
			V_Return_Flag=SF_WR_E23_RAM_EnergyData(PStr_3aTableAddr,PStr_2TableAddr[V_Line].V_LineNum,V_Data_Length,P_Data,PStr_2TableAddr[V_Line].V_DT_Type,V_DI[0]);
		}break;

		case DT_E23:                              /*��E2����CRC����*/
		case DT_E23_Clear:                              /*��E2����CRC����*/
		case DT_E23_Hex:                          /*��E2����CRC���ݣ����ݴ洢��ʽΪhex��ʽ(��Ҫ���ۼƴ�������ͨѶ��������ʱ��ת��ΪBCD��ʽ)*/
#if 0
		case DT_E23_En:                           /*16�����������ݣ�����6+2��6+4���ݳ���ʱ���������赥���������ݳ���(����д)���������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��*/
		                                          /*(�б�645���ݳ���Ϊ6+2��������6+4������ʱ���������ݳ��ȵ�����ȡE2��ַ����������1��������������й��ۼ��õ���),д����ʱ�����ݳ����жϵ�����*/
		case DT_E23_En_Clear:                           /*16�����������ݣ�����6+2��6+4���ݳ���ʱ���������赥���������ݳ���(����д)���������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��*/
		                                          /*(�б�645���ݳ���Ϊ6+2��������6+4������ʱ���������ݳ��ȵ�����ȡE2��ַ����������1��������������й��ۼ��õ���),д����ʱ�����ݳ����жϵ�����*/
#endif
		case DT_E23_DI0:                          /*20��E2������E2��ַ˳���У����ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
		                                         /*���ݵ�ַ��DI�ж��Ƿ���ȷ�������ƽ����ա����룬�б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
		case DT_E23_OADTab:                       /*38:��E2�������ж����ݳ���ʱ�����ȡ�ù����б�OAD����*/
		{
			if(DT_E23_OADTab==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				Str_3eTable *PStr_3eTable_2E2=NULL;

				PStr_3eTable_2E2=(Str_3eTable *)(PStr_2TableAddr[V_Line].PStr_3TableAddr);

				if(PStr_2TableAddr[V_Line].V_LineNum>=Str_3eTable_Flash_Len)
				{
					return C_DataLenError;
				}

				V_3TableE2Addr=PStr_3eTable_2E2[PStr_2TableAddr[V_Line].V_LineNum].V_E2BakeUp1Addr_OADTab;
			}
			else
			{
				V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*ȡ3����E2��ַ*/
			}

			if(DT_E23_DI0==PStr_2TableAddr[V_Line].V_DT_Type)    /*E2��ַ����*/
			{
				if(0==V_DI[0])
				{
					return C_IDError;              /*����������*/
				}

				V_3TableE2Addr=V_3TableE2Addr+(V_DI[0]-1)*(V_DataLen+C_CRCLen2);
				if(V_3TableE2Addr>E2_Max_Addr)
				{
					return C_IDError;              /*����������*/
				}
			}

			V_Return_Flag=SF_WR_E23_Data(V_3TableE2Addr,V_Data_Length,P_Data);
		}break;

		case DT_Flash_DI04:                       /*��Flash�����������ݣ�DI0��4λ��ʾ��������4λ��ʾ��ͬ��ʶ��(��ѯ4������)*/
		case DT_Flash_Tol_DI0_DI1:                /*��Flash�����������ݣ�����DI0��ʾ������DI1��ʾ�����ʶ��(��ѯ4������)*/
#if 0
		case DT_Flash_Tol_DI0_DI2:                /*11�� Flash�����������ݣ�����DI0��ʾ������DI2��ʾ�����ʶ��(��ѯ4�����ã���Ҫ�ǵ�����������ABC��������)*/
		case DT_Flash_Tol_DI0_SettEn:              /*12��Flash�����������ݣ�����DI0��ʾ����������DI2��DI1�������ƫ�Ƶ�ַ(�����ѯ4������Ҫ�ǽ������������ABC����������)��*/
		case DT_Flash_Tol_DI0_SettDe:              /*13��Flash�����������ݣ�����DI0��ʾ����������DI2��DI1�������ƫ�Ƶ�ַ(�����ѯ4������Ҫ�ǽ�������������ABC����������)��*/
		case DT_Flash_Tol_DI0_W_Sett_En:           /*14��Flash�����������ݣ�����DI0��ʾ����������ģ��д����ʱһ��д���ݲ㣬���ݲ��ڲ������������������ʱ��ֿ��洢���ñ�ʶ��ֻ֧��д*/
#endif
		case DT_Flash_Tol_DI0:                    /*15�� Flash�����������ݣ�����DI0��ʾ������û�з����ʶ�롣*/
		case DT_Flash_Tol_DI0_DI1Max:             /*27�� Flash�����������ݣ�����DI0��ʾ�������б�2����ʱֻ����1��DI1���ֵ(�����ò���4����ķ�ʽ)���ڲ�������DI��DI���ݴ��ƫ�Ƶ�ַʱ��*/
		{                                      /*OffsetAddr������ü��㷽ʽ����,Ŀǰֻ��У���¼���ø÷�ʽ,������ʱ��DI1=0��*/
			P_Str_3cTableAddr=(Str_3cTable *)PStr_2TableAddr[V_Line].PStr_3TableAddr;
			V_Return_Flag=SF_WriteFlash_Data(P_Data,V_Data_Length,P_Str_3cTableAddr,V_Data_Id,PStr_2TableAddr[V_Line].V_LineNum,PStr_2TableAddr[V_Line].V_DT_Type);
		}break;

		case DT_Flash_698EventTab:		/*37:��OAD�����б��¼���¼����Flash*/
		{
			P_Str_3dEventTableAddr=(Str_3dEventTable *)PStr_2TableAddr[V_Line].PStr_3TableAddr;
			V_Return_Flag=SF_WriteFlash_DataEventTable(P_Data,V_Data_Length,P_Str_3dEventTableAddr,V_Data_Id,PStr_2TableAddr[V_Line].V_LineNum,PStr_2TableAddr[V_Line].V_DT_Type);
		}break;

		case DT_E21:                              /*��E2һ��*/
#if 0
		case DT_E21_En:                           /*17�����������ݣ�����6+2��6+4���ݳ���ʱ���������赥���������ݳ���(����д)���������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��,��Ҫ��Դ�E2 1������*/
			                                        /*(�б�645���ݳ���Ϊ6+2��������6+4������ʱ���������ݳ��ȵ�����ȡE2��ַ����������1--4��������ս���ʱ�估������������й����ۼ��õ���*/
#endif
		case DT_E21_DI0:                          /*22��E2һ�������ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
			                                        /*���ݵ�ַ��DI�ж��Ƿ���ȷ�������Ƶ�1-254�����������ڼ���ʱ�α�ţ��б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
		{
			V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*ȡ3����E2��ַ*/
			/*if((DT_E21_DI0==PStr_2TableAddr[V_Line].V_DT_Type)
				||(DT_E21_DI0_ReadDegree==PStr_2TableAddr[V_Line].V_DT_Type))*/    /*E2��ַ����*/
			if( DT_E21_DI0 == PStr_2TableAddr[V_Line].V_DT_Type )
			{
				if(0==V_DI[0])
				{
					return C_IDError;              /*����������*/
				}

				V_3TableE2Addr=V_3TableE2Addr+(V_DI[0]-1)*V_DataLen;
				if(V_3TableE2Addr>E2_Max_Addr)
				{
					return C_IDError;              /*����������*/
				}
			}

			V_Return_Flag=SF_WR_E21_Data(V_3TableE2Addr,V_Data_Length,P_Data);
		}break;

		case DT_RAM:                              /*��RAM����CRC*/
		case DT_RAM_Time_Data:                    /*��RAM����CRC��������ʱ���жϵ����־��*/
		case DT_RAM_DI0:	                        /*18�����ݴ�RAM����CRC�������ݳ��ȡ�����һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(,ͬһ���ͣ�������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
		                                          /*���ݵ�ַ��DI�ж��Ƿ���ȷ�������Ƶ������״̬��1-7���б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
#if 0
		case DT_RAM_DI1_0:                        /*23�����ݴ�RAM����CRC�������ݳ��ȡ�����һ��(ͬһDI3-DI2��DI0)���б��ʱֻ��DI1���ֵ(,ͬһ����,����DI1=0����������ƫ�Ƶ�ַʱ��Ҫ����)��*/
			                                        /*�����ڲ��������ݵ�ַ��DI�ж��Ƿ���ȷ�������Ʋ���˲ʱ���ʣ��б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI1��Ӧ���ݴ洢��ַ��ע��*/
		case DT_RAM_DI1:	                        /*24�����ݴ�RAM����CRC�������ݳ��ȡ�����һ��(ͬһDI3-DI2��DI0)���б��ʱֻ��DI1���ֵ(,ͬһ���ͣ�������DI1=0)�������ڲ�����*/
#endif
		{                                      /*���ݵ�ַ��DI�ж��Ƿ���ȷ�������Ƶ�ѹ���ݣ��б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI1��Ӧ���ݴ洢��ַ��ע��*/
			P_3TableRamAddr=(uchar8 *)PStr_2TableAddr[V_Line].PStr_3TableAddr;

			if(DT_RAM_DI0==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				if(0==V_DI[0])
				{
					return C_IDError;		/*����������*/
				}
				P_3TableRamAddr=P_3TableRamAddr+(V_DI[0]-1)*V_DataLen;
			}
#if 0
			if(DT_RAM_DI1_0==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				P_3TableRamAddr=P_3TableRamAddr+V_DI[1]*V_DataLen;
			}

			if(DT_RAM_DI1==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				if(0==V_DI[1])
				{
					return C_IDError;		/*����������*/
				}
				P_3TableRamAddr=P_3TableRamAddr+(V_DI[1]-1)*V_DataLen;
			}
#endif
			GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;		/*�ð�ȫ��־*/
			V_Return_Flag=SF_WR_RAM_Data(P_3TableRamAddr,V_Data_Length,P_Data,PStr_2TableAddr[V_Line].V_DT_Type,Msg_Num);
		}break;

		case DT_RAMCRC:                           /*��RAM��CRC*/
		{
			P_3TableRamAddr=(uchar8 *)PStr_2TableAddr[V_Line].PStr_3TableAddr;
			GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;		/*�ð�ȫ��־*/
			V_Return_Flag=SF_WR_RAMCRC_Data(P_3TableRamAddr,V_Data_Length,P_Data);
		}break;

		case DT_E21CRC_DI0:			/*21��E2һ����CRC�����ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
									/*���ݵ�ַ��DI�ж��Ƿ���ȷ���������Զ�ѭ����ʾ��1-99����ʾ���룬�б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
		case DT_E21CRC_MaxLen:		/*40��E2һ����CRC��д��ʱ�жϲ�����������ݳ���*/
		{
			V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;		/*ȡ3����E2��ַ*/

			if(DT_E21CRC_DI0==PStr_2TableAddr[V_Line].V_DT_Type)		/*E2��ַ����*/
			{
				if(0==V_DI[0])
				{
					return C_IDError;	/*����������*/
				}

				V_3TableE2Addr=V_3TableE2Addr+(V_DI[0]-1)*(V_DataLen+C_CRCLen2);

				if(V_3TableE2Addr>E2_Max_Addr)
				{
					return C_IDError;	/*����������*/
				}
			}

			/*д���ݳ��ȴ���255��������д�롢�����жϡ�ֱ��д����������Ȼ���ݲ㻺��̫��*/
			if(DT_E21CRC_MaxLen==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				V_Return_Flag=SF_WR_E21CRC_Data698(V_3TableE2Addr,V_Data_Length,P_Data);
			}
			else
			{
				V_Return_Flag=SF_WR_E21CRC_Data(V_3TableE2Addr,V_Data_Length,P_Data);
			}
		}break;

		case DT_FRAM1CRC:		/*42������һ����CRC*/
		{
			V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;		/*ȡ3���������ַ*/
			V_Return_Flag=SF_WR_FRAM1CRC_Data(V_3TableE2Addr,V_DataLen,P_Data);
		}break;

		default:
			return C_IDError;		/*���Ҵ���*/
	}

	GV_D_SafeFlag=C_Clear_SafeFlag;		/*�尲ȫ��־*/

	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Find2Table_DIParamChild(uchar8 V_Data_Id2, ushort16 *P_Line)
����������2���ֱ��ѯ����,�õ�DI2��Ӧ��2�����к�
���������
		uchar8 V_Data_Id2�����ݱ�ʶ��DI2��
���������
		ushort16 *P_Line������2�����Ӧ�кţ�
���ز�����C_OK��C_IDError��
����˵����
���û��ƣ�
��ע��
*********************************************************************************/
uchar8 SF_Find2Table_DIParamChild(uchar8 V_Data_Id2, ushort16 *P_Line)
{
	ushort16 V_Line;

	for(V_Line=0;V_Line<Str_2Table_DIParamChild_Len;V_Line++)
	{
		if(V_Data_Id2==Str_2Table_DIParamChild[V_Line].V_DI2)
		{
			break;
		}
	}

	if(V_Line==Str_2Table_DIParamChild_Len)
	{
		return C_IDError;
	}
	else
	{
		*P_Line=V_Line;
		return C_OK;
	}
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Find1Table_Data(uchar8 V_Data_Id3, ushort16 *P_Line)
����������1�����ѯ����,�õ�DI3��Ӧ��1�����к�
���������
		uchar8V_Data_Id3�����ݱ�ʶ��DI3��
���������
		ushort16*P_Line������1�����Ӧ�кţ�
���ز�����C_OK��C_IDError��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_Find1Table_Data(uchar8 V_Data_Id3, ushort16 *P_Line)
{
	ushort16 V_Line;

	for(V_Line=0;V_Line<Str_1Table_DI3_Len;V_Line++)
	{
		if(V_Data_Id3==Str_1Table_DI3[V_Line].V_DI3)
		{
			break;
		}
	}

	if(V_Line==Str_1Table_DI3_Len)
	{
		return C_IDError;
	}
	else
	{
		*P_Line=V_Line;
		return C_OK;
	}
}

/*********************************************************************************
����ԭ�ͣ�ushort16 SF_GetOADTabNum(Str_2Table V_Str_2Table)
������������ȡ�����б�OAD����,�ڲ��Ѿ�*2
���������
		Str_2TableV_Str_2Table:�����б�����2����ṹ��
�����������
���ز�����������Ӧ����OAD�б��ȣ��쳣ΪFFFF
����˵����
���û��ƣ�
��     ע���ڲ�����OAD����*����OAD�б��ʽ
*********************************************************************************/
ushort16 SF_GetOADTabNum(Str_2Table V_Str_2Table)
{
	Str_3eTable *PStr_3eTable_2E2=NULL;
	uchar8 V_Return_Flag,V_Data;
	ushort16 V_Data_Length=0xFFFF;

	PStr_3eTable_2E2=(Str_3eTable *)(V_Str_2Table.PStr_3TableAddr);

	if(V_Str_2Table.V_LineNum>=Str_3eTable_Flash_Len)	/*����������*/
	{
		return V_Data_Length;
	}

	V_Return_Flag=SF_ReadE2Three(PStr_3eTable_2E2[V_Str_2Table.V_LineNum].V_E2BakeUp1Addr_OADTabLen,CLAll_Loss_Vol_OADTabLen,&V_Data);
	if(C_OK==V_Return_Flag)
	{
		V_Data_Length=V_Data*C_698Event_OADTabDataType;
	}
	return	V_Data_Length;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Find2Table_Data(uchar8 V_WR_Mes, ulong32 V_Data_Id, ushort16 *P_Data_Length,
									Str_2Table *PStr_2Table, ushort16 *P_Line, ushort16 V_MaxLine)
����������2�����ѯ�������õ�DI2-DI0��Ӧ��2�����к�
���������
		uchar8 V_WR_Mes:��Ϣ�ż���д��־,��������Ϊ������ʾģ��ʱ(���������ݳ���Ϊ6+4)������øú���ǰ����ڽ������⴦��Ϊ��ʾ��Ϣ����
		ulong32 V_Data_Id�����ݱ�ʶ��DI2~DI0��
		ushort16 *P_Data_Length��д����ʱ����ʾ��д���ݳ��ȣ�������ʱ���������ݳ��ȣ���Ϊ�������ʱ���ò���ֵΪģ������
		���ݻ��泤�����ֵ���������ݲ��жϣ��������ݳ��ȣ��Ƿ������������򷵻����ݳ��ȴ���
		Str_2Table *PStr_2Table��1�����ѯ�ж�Ӧ2����ṹ���ַ��
		ushort16 V_MaxLine:��Ӧ2����ṹ�����鳤��
���������
		ushort16 *P_Line������2�����Ӧ�кţ�
		ushort16 *P_Data_Length������ʵ�ʶ����ݳ��ȣ�
���ز�����C_OK��C_IDError��C_DataLenError��C_NoAccess��
����˵����
���û��ƣ�
��     ע���ڲ��ж����ݳ��ȼ���д����
*********************************************************************************/
uchar8 SF_Find2Table_Data(uchar8 V_WR_Mes,ulong32 V_Data_Id,ushort16 *P_Data_Length,Str_2Table *PStr_2Table,ushort16 *P_Line,ushort16 V_MaxLine)
{
	ushort16 V_Line, V_Data_Length, V_Data_LengthTemp;
	uchar8 V_i;

	for(V_Line = 0; V_Line < V_MaxLine; V_Line++)
	{
		if(V_Data_Id == PStr_2Table[V_Line].V_DI)
		{
			break;
		}
		else
		{
			if(DT_Flash_DI04==PStr_2Table[V_Line].V_DT_Type)	/*Flash�����������ݣ�DI0��4λ��ʾ��������4λ��ʾ��ͬ��ʶ��(��ѯ4������)*/
			{
				if(0x00000000==(V_Data_Id&0x0000000F))		/*������Ϊ0*/
				{
					continue;
				}
				if((V_Data_Id&0xFFFFFFF0)==(PStr_2Table[V_Line].V_DI&0xFFFFFFF0))	/*DI0��4λ���Ƚ�*/
				{
					break;
				}
			}
			else
			{
				if( (DT_Flash_Tol_DI0_DI1==PStr_2Table[V_Line].V_DT_Type)/*||(DT_Flash_Tol_DI0_DI2==PStr_2Table[V_Line].V_DT_Type)
					|| (DT_Flash_Tol_DI0_SettEn==PStr_2Table[V_Line].V_DT_Type)||(DT_Flash_Tol_DI0_SettDe==PStr_2Table[V_Line].V_DT_Type)
					|| (DT_Flash_Tol_DI0_W_Sett_En==PStr_2Table[V_Line].V_DT_Type)||(DT_R_Flash_Tol_DI0_DI2_En==PStr_2Table[V_Line].V_DT_Type)*/
					|| (DT_Flash_Tol_DI0==PStr_2Table[V_Line].V_DT_Type) )	/*DI0��ʾ����*/
				{
					if(0x00000000==(V_Data_Id&0x000000FF))		/*������Ϊ0*/
					{
						continue;
					}

					if((V_Data_Id&0xFFFFFF00)==(PStr_2Table[V_Line].V_DI&0xFFFFFF00))	/*DI0���Ƚ�*/
					{
						break;
					}
				}
				else
				{
					if( (DT_RAM_DI0==PStr_2Table[V_Line].V_DT_Type)||(DT_Ref_E23_RAMCRC_DI0==PStr_2Table[V_Line].V_DT_Type)
						|| (DT_E23_DI0==PStr_2Table[V_Line].V_DT_Type)||(DT_E21CRC_DI0==PStr_2Table[V_Line].V_DT_Type)
						|| (DT_E21_DI0==PStr_2Table[V_Line].V_DT_Type)||(DT_Ref_E23_RAMCRC_DI0_2==PStr_2Table[V_Line].V_DT_Type)
						/*||(DT_E21_DI0_ReadDegree==PStr_2Table[V_Line].V_DT_Type)*/ /*ֻ��DI0���ֵ����DI0��Ϊ0*/
						)
					{
						if((V_Data_Id&0xFFFFFF00)==(PStr_2Table[V_Line].V_DI&0xFFFFFF00))	/*DI0���Ƚ�*/
						{
							if((0x00000000!=(V_Data_Id&0x000000FF))	/*DI0��Ϊ�㣬�ҡ����ֵ*/
								&&((V_Data_Id&0x000000FF)<=(PStr_2Table[V_Line].V_DI&0x000000FF)))
							{
								break;
							}
						}
					}
					else
					{
#if 0
						if(DT_RAM_DI1_0==PStr_2Table[V_Line].V_DT_Type)    /*ֻ��DI1���ֵ��DI1����Ϊ0*/
						{
							if((V_Data_Id&0xFFFF00FF)==(PStr_2Table[V_Line].V_DI&0xFFFF00FF))/*DI1���Ƚ�*/
							{
								if((V_Data_Id&0x0000FF00)<=(PStr_2Table[V_Line].V_DI&0x0000FF00))/*DI1��=���ֵ*/
								{
									break;
								}
							}
						}
						else
						{

							if(DT_RAM_DI1==PStr_2Table[V_Line].V_DT_Type)    /*ֻ��DI1���ֵ����DI1��Ϊ0*/
							{
								if((V_Data_Id&0xFFFF00FF)==(PStr_2Table[V_Line].V_DI&0xFFFF00FF))/*DI1���Ƚ�*/
								{
									if(((V_Data_Id&0x0000FF00)<=(PStr_2Table[V_Line].V_DI&0x0000FF00))
										&&(0x00000000!=(V_Data_Id&0x0000FF00)))/*DI1��=���ֵ,��DI1��Ϊ0*/
									{
										break;
									}
								}
							}
							else
							{
#endif
								if(DT_Flash_Tol_DI0_DI1Max==PStr_2Table[V_Line].V_DT_Type) /*ֻ��DI1���ֵ����DI1��Ϊ0,DI0��ʾ�����Ҳ�Ϊ��*/
								{
									if((V_Data_Id&0xFFFF0000)==(PStr_2Table[V_Line].V_DI&0xFFFF0000))	/*DI0��DI1���Ƚ�*/
									{
										if(0x00000000==(V_Data_Id&0x000000FF))		/*������Ϊ0*/
										{
											continue;
										}

										if(((V_Data_Id&0x0000FF00)<=(PStr_2Table[V_Line].V_DI&0x0000FF00))
											&&(0x00000000!=(V_Data_Id&0x0000FF00)))		/*DI1��=���ֵ,��DI1��Ϊ0*/
										{
											break;
										}
									}
								}
								else
								{
									if(DT_Flash_698EventTab==PStr_2Table[V_Line].V_DT_Type)/*���ж�DI 0��������698�¼�����������*/
									{
										if((V_Data_Id&0xFFFFFF00)==(PStr_2Table[V_Line].V_DI&0xFFFFFF00))
										{
											break;
										}
									}
								}
#if 0
							}
						}
#endif
					}
				}
			}
		}
	}

	if(V_Line==V_MaxLine)
	{
		return C_IDError;
	}
	else
	{
		if(V_WR_Mes&0x80)	/*������*/
		{
			if(PStr_2Table[V_Line].V_WR_MesAuth&0x80)/*���������Ƿ�֧�ֶ�*/
			{
#if 0
				if(C_Msg_Display!=(V_WR_Mes&0x7F))                   /*�ж��Ƿ�Ϊ������ʾģ�����������--��������--�����赥������,��֧����ʾ�࣬���ݿ��*/
				{
					V_Data_Length=PStr_2Table[V_Line].V_DataLen;
				}
				else
				{
					switch(PStr_2Table[V_Line].V_DT_Type)
					{
						case DT_Flash_Tol_DI0_SettEn:
						case DT_E23_En:
						case DT_E23_En_Clear:
						case DT_E21_En:
						case DT_R_Flash_Tol_DI0_DI2_En:
						{
							V_Data_Length=PStr_2Table[V_Line].V_DataLen+1;
						}break;

						default:
						{
							V_Data_Length=PStr_2Table[V_Line].V_DataLen;
						}break;
					}
				}
#endif
				V_Data_Length=PStr_2Table[V_Line].V_DataLen;

				if(DT_Flash_698EventTab==PStr_2Table[V_Line].V_DT_Type)		/*���ݳ��������*/
				{
					Str_3dEventTable *P_Str_3dEventTableAddr=NULL;
					ushort16 V_3dEventTableLine;

					P_Str_3dEventTableAddr=(Str_3dEventTable *)PStr_2Table[V_Line].PStr_3TableAddr;

					if(PStr_2Table[V_Line].V_LineNum>=Str_3dTable_Flash_Len)
					{
						return C_DataLenError;
					}

					V_3dEventTableLine=PStr_2Table[V_Line].V_LineNum;
					V_Data_Length=SF_GetEventDataLen(P_Str_3dEventTableAddr[V_3dEventTableLine].V_TB_E2BakeUp1Addr,P_Str_3dEventTableAddr[V_3dEventTableLine].V_TBLen_E2BakeUp1Addr,P_Str_3dEventTableAddr[V_3dEventTableLine].PStr_4aTableAddr,P_Str_3dEventTableAddr[V_3dEventTableLine].V_Str_4aTableLen);
					if((0==V_Data_Length)||(0xFFFF==V_Data_Length))
					{
						return C_DataLenError;
					}
				}
				/*�ж����������Ƿ����*/
				if(V_Data_Length<=(*P_Data_Length))/*����OAD��ű�,������Ҳ�ж����ݳ��ȣ��������������ݳ���*/
				{
					*P_Line=V_Line;

					if(DT_E23_OADTab==PStr_2Table[V_Line].V_DT_Type)      /*38��E2�������ж����ݳ���ʱ�����ȡ�ù����б�OAD����*/
					{
						V_Data_LengthTemp=SF_GetOADTabNum(PStr_2Table[V_Line]);/*��ȡ�����б�OAD����,�ڲ��Ѿ�*2*/
						if(V_Data_LengthTemp>V_Data_Length)/*����������*/
						{
							*P_Data_Length=V_Data_LengthTemp;
							return C_DataLenError;
						}
						else
						{
							V_Data_Length=V_Data_LengthTemp;
						}
					}

					*P_Data_Length=V_Data_Length;	/*�����������ݳ���*/
					return C_OK;
				}
				else	/*�������*/
				{
					*P_Data_Length=V_Data_Length;	/*������������ʵ�ʳ��ȣ����ݽ���Ҫ��20140629*/
					return C_DataLenError;
				}
			}
			else
			{
				return C_NoAccess;
			}
		}
		else	/*д����*/
		{
			if(0x00==(V_WR_Mes&0x7F))	/*��Ϣ��ȫ�㣬��֧��д����*/
			{
				return C_NoAccess;
			}

			*P_Line=V_Line;
#if 0
			switch(PStr_2Table[V_Line].V_DT_Type)          /*�������������ݣ����ݳ��ȵ���*/
			{
				case DT_Flash_Tol_DI0_SettEn:
				case DT_E23_En:                /*Ŀǰ�Ĵ������ܣ�ֻ�и�������֧��д*/
				case DT_E23_En_Clear:
				case DT_E21_En:
				case DT_R_Flash_Tol_DI0_DI2_En:
				{
					V_Data_Length=PStr_2Table[V_Line].V_DataLen+1;
				}break;

				default:
				{
					V_Data_Length=PStr_2Table[V_Line].V_DataLen;
				}break;
			}
#endif
			V_Data_Length=PStr_2Table[V_Line].V_DataLen;

			if(((V_Data_Id&0xFFFFFF00)==(CL_Free_OADTab&0xFFFFFF00))
				||(DT_E23_OADTab==PStr_2Table[V_Line].V_DT_Type)
				||(DT_E21CRC_MaxLen==PStr_2Table[V_Line].V_DT_Type))/*���ᡢ�¼�OAD��ű�,д���ݲ��ж����ݳ��ȣ����ж�д���ݳ��Ȳ��ܴ�����󳤶�*/
			{
				if((*P_Data_Length)>V_Data_Length)
				{
					return C_DataLenError;
				}
			}
			else	/*�������ݣ������ж����ݳ���*/
			{
				if(DT_Flash_698EventTab!=PStr_2Table[V_Line].V_DT_Type)/*698�¼���¼������OAD�б�д�¼���¼���ж����ݳ��ȡ��ھ���дFlash����ʱ�жϳ��ȣ����⸴���ظ��ж�*/
				{
					if(V_Data_Length!=(*P_Data_Length))		/*д���ݳ��ȴ�*/
					{
						return C_DataLenError;
					}
				}
			}

			if(C_WR_All==PStr_2Table[V_Line].V_WR_MesAuth)
			{
				return C_OK;
			}
			else
			{
				if((V_WR_Mes&0x7F)==(PStr_2Table[V_Line].V_WR_MesAuth&0x7F))/*�ж�дȨ��,������Ϣ*/
				{
					return C_OK;
				}
				else
				{
					if(((PStr_2Table[V_Line].V_WR_MesAuth&0x7F)>=C_Com_Msg_Star)
						&&((PStr_2Table[V_Line].V_WR_MesAuth&0x7F)<(C_Com_Msg_Star+C_Com_Msg_Len_Max)))/*�����Ϣ�ж�*/
					{
						V_i=(PStr_2Table[V_Line].V_WR_MesAuth&0x7F)-C_Com_Msg_Star;  /*�����Ϣ����к�*/

						for(V_Line=0;V_Line<C_Com_Msg_Len;V_Line++)              /*�����Ϣ�ڷ�����Ϣ�ж�*/
						{
							if((V_WR_Mes&0x7F)==GP_Com_Msg[V_i][V_Line])
							{
								break;
							}
						}

						if(C_Com_Msg_Len==V_Line)
						{
							return C_NoAccess;
						}
						else
						{
							return C_OK;
						}
					}
					else
					{
						return C_NoAccess;
					}
				}
			}
		}
	}
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_GetMinFreezeTolNum(uchar8 *P_Data, ushort16 V_DataLen, ushort16 *PV_Cyc16)
������������ȡ���Ӷ����ܷ�����������Ӧ�ĸ���������
���������
		uchar8 *P_Data�����Ӷ�������б�
		ushort16 V_DataLen�����Ӷ�������б���
���������
		ushort16 *PV_Cyc16�������ͬ������Ӧ�Ķ������ڣ��뷽��һһ��Ӧ����1�����ھ��Ƿ���0����������
���ز���������1-8���쳣FF��
����˵����
���û��ƣ�
��     ע�����ڲ�ͬ����Ϊ��ͬ����
*********************************************************************************/
uchar8 SF_GetMinFreezeTolNum(uchar8 *P_Data, ushort16 V_DataLen, ushort16 *PV_Cyc16)
{
	uchar8 V_i, V_j, V_k, V_Num = 0xFF;
	ushort16 V_OADOrder16;

	V_j = V_DataLen / C_698Free_OADTabDataType;			/*OAD�б����*/
	PF_Buffer2ToUshort16(&P_Data[2], &PV_Cyc16[0]);		/*��������*/
	V_Num = 1;

	for(V_i=1;V_i<V_j;V_i++)
	{
		PF_Buffer2ToUshort16(&P_Data[C_698Free_OADTabDataType*V_i+2],&V_OADOrder16);
		for(V_k=0;V_k<V_Num;V_k++)
		{
			if(V_OADOrder16==PV_Cyc16[V_k])				/*�ж��Ƿ��Ѿ����������*/
			{
				break;
			}
		}

		if(V_k>=V_Num)			/*�·���*/
		{
			V_Num+=1;
			if(V_Num>8)
			{
				return 0xFF;	/*�쳣*/
			}
			PV_Cyc16[V_Num-1]=V_OADOrder16;
		}
	}

	if(V_Num>8)
	{
		V_Num=0xFF;				/*�쳣*/
	}

	return V_Num;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_GetStr_698FreezeDataTableOrder(ulong32 V_Data_Id_OAD)
������������ȡĳ�ඳ��������Str_698FreezeDataTable����ţ�
���������ulong32 V_Data_Id_OAD��ĳ�ඳ���ʶ�룻
�����������
���ز�����Ҫ���ҵ�ĳ�ඳ����Str_698FreezeDataTable�������ţ��쳣����FF
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_GetStr_698FreezeDataTableOrder(ulong32 V_Data_Id_OAD)
{
	uchar8 V_DI[4], V_i;

	PF_Ulong32ToBuffer4(&V_DI[0], &V_Data_Id_OAD, 4);

	for(V_i=0;V_i<Str_698FreezeDataTable_Len;V_i++)
	{
		if(V_DI[2]==Str_698FreezeDataTable[V_i].V_DI2)
		{
			break;
		}
	}

	if(V_i<Str_698FreezeDataTable_Len)
	{
		return V_i;
	}
	else
	{
		return 0xFF;
	}
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_MinFreezeDefProDistr(uchar8 Vu_MinPro)
�������������Ӷ���Ĭ�ϴ洢��ַ���䡣����8�ַ���
���������uchar8 Vu_MinPro�����Ӷ��᷽�������ڲ��жϺϷ���1--8֮�䣬��������8�ַ�������
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��C_DataLenError��
����˵����
���û��ƣ�
��     ע���ڲ��жϰ�ȫ��־
*********************************************************************************/
uchar8 SF_MinFreezeDefProDistr(uchar8 Vu_MinPro)
{
	ushort16 V_ProNum,V_i;
	uchar8 V_Return_Flag=C_Error;
	ulong32 V_StaFlashAddr,V_EndFlashAddr;
	uchar8 Vu_FlashAddr[64];	/*������ʼ��������ַ��ÿ�ඳ�᷽����ʽΪ��ʼ��ַ+������ַ��8�ַ���ͬһCRC*/
	uchar8 V_Order;

	memset(&Vu_FlashAddr[0],0xFF,64);

	if((0==Vu_MinPro)||(Vu_MinPro>8))
	{
		Vu_MinPro=8;	/*�쳣��8�ַ���*/
	}

	V_ProNum=MinFreezeFlashTol/Vu_MinPro;	/*��������*/
	V_Order=SF_GetStr_698FreezeDataTableOrder(C_RelatedOAD_Min);	/*��ȡĳ�ඳ��������Str_698FreezeDataTable�����*/
	if(V_Order == 0xFF)
	{
		return C_OtherErr_DAR;
	}
	V_StaFlashAddr=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;

	for(V_i=0;V_i<(Vu_MinPro-1);V_i++)	/*ʣ��ռ�ȫ���������һ�ַ���*/
	{
		if((V_StaFlashAddr>Str_698FreezeDataTable[V_Order].V_EndFlashAddr)||(V_StaFlashAddr>C_Flash_Max_Addr))	/*�쳣*/
		{
			return	V_Return_Flag;
		}
		V_EndFlashAddr=V_StaFlashAddr+(V_ProNum-1)*C_OneFlashPage;
		if((V_EndFlashAddr>Str_698FreezeDataTable[V_Order].V_EndFlashAddr)||(V_EndFlashAddr>C_Flash_Max_Addr))	/*�쳣,����������*/
		{
			return	V_Return_Flag;
		}
		PF_Ulong32ToBuffer4(&Vu_FlashAddr[V_i*8],&V_StaFlashAddr,4);
		PF_Ulong32ToBuffer4(&Vu_FlashAddr[V_i*8+4],&V_EndFlashAddr,4);
		V_StaFlashAddr=V_EndFlashAddr+C_OneFlashPage;
	}
	V_EndFlashAddr=Str_698FreezeDataTable[V_Order].V_EndFlashAddr;	/*���һ�ַ��䷽��*/
	PF_Ulong32ToBuffer4(&Vu_FlashAddr[V_i*8],&V_StaFlashAddr,4);
	PF_Ulong32ToBuffer4(&Vu_FlashAddr[V_i*8+4],&V_EndFlashAddr,4);

	V_Return_Flag=SF_WriteE2Three(E2Addr_Min_Free_FlashAddr_Allo,64,&Vu_FlashAddr[0]);	/*д�����ַ*/
	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�ushort16 SF_GetFreezeSaveDeep(uchar8 V_DI2Temp)
������������ȡĳ�ඳ�ᣬ�洢���
���������uchar8 V_DI2Temp:ĳ�ඳ�ᡣ��Ϊ���Ӷ���ʱ����3λ��ʾ��ͬ������
�����������
���ز�����ushort16 V_Data_Deep�����ඳ����ȣ�
����˵����
���û��ƣ�
��     ע���쳣����0���ڻ�ȡ�������ݳ��Ⱥ��������ϸ���
*********************************************************************************/
ushort16 SF_GetFreezeSaveDeep( uchar8 V_DI2Temp )
{
	ushort16 V_Data_Deep;
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADOrder16,V_i;
	uchar8 V_Return_Flag,V_DI2;
	Str_3aTable V_Str_3aTable;

	V_Data_Deep=0;
	V_DI2=(V_DI2Temp&0x1F);		/*ȥ��������*/
	for(V_i=0;V_i<Str_698FreezeDataTable_Len;V_i++)
	{
		if(V_DI2==Str_698FreezeDataTable[V_i].V_DI2)
		{
			break;
		}
	}

	if(V_i<Str_698FreezeDataTable_Len)
	{
		V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;		/*698���᳤�ȡ���������������Str_3aTable�к�*/
		if(V_Order>=Str_3aTable_E23RAM_Len)
		{
			return V_Data_Deep;		/*�쳣*/
		}

		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
		if(C_OK==V_Return_Flag)
		{
			/*��ű�ÿ��OAD���C_698Free_OADTabDataType���ֽ�,Ŀǰ6�ֽڡ�2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/
			V_OADTabLen_T=P_OADTabLen_T[0];
			V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;
			if(V_OADTabLen_T>C_698Free_OADTabLen)		/*���ݳ��Ȱ�ȫ���ж�*/
			{
				return V_Data_Deep;		/*�쳣*/
			}

			V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;	/*698������ű�����Str_3aTable�к�*/
			if(V_Order>=Str_3aTable_E23RAM_Len)
			{
				return V_Data_Deep;		/*�쳣*/
			}

			V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
			V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);		/*��ȡ��������б�*/
			if(C_OK!=V_Return_Flag)
			{
				return V_Data_Deep;		/*�쳣*/
			}

			if(V_DI2==(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16))		/*���Ӷ���*/
			{
				/*��ȡ���Ӷ��᷽���ţ���Ӧ��OAD�����б�����OAD����*/
				V_OADTabLen_T=SF_GetMinFreezeNum_OADTab((V_DI2Temp>>5),&P_DataOAD_NumTab[0],V_OADTabLen_T);
				if(0xFFFF==V_OADTabLen_T)
				{
					return V_Data_Deep;		/*�쳣*/
				}
			}
			else
			{
				V_OADTabLen_T=V_OADTabLen_T/C_698Free_OADTabDataType;
			}

			V_Data_Deep=0;
			for(V_i=0;V_i<V_OADTabLen_T;V_i++)
			{
				PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType*V_i+4],&V_OADOrder16);		/*�����б�洢��ʽ��2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/
				if(V_OADOrder16>V_Data_Deep)
				{
					V_Data_Deep=V_OADOrder16;		/*ȡ���洢�ռ����*/
				}
			}
		}
	}
	return V_Data_Deep;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_MinFreezeProDistr(uchar8 *P_Data, ushort16 V_DataLen)
�������������ݷ��Ӷ�������б����д洢�ռ����
���������
		uchar8 *P_Data�����Ӷ�������б�
		ushort16 V_DataLen�����Ӷ�������б���
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��C_DataLenError��
����˵����
���û��ƣ�
��     ע���ڲ��жϰ�ȫ��־����������һ�£�����Ϊ��ͬһ����
*********************************************************************************/
uchar8 SF_MinFreezeProDistr(uchar8 *P_Data, ushort16 V_DataLen)
{
	uchar8 Vu_TolNum,V_Return_Flag=C_Error;
	ulong32 V_StaFlashAddr,V_EndFlashAddr;
	uchar8 Vu_FlashAddr[64]={0xFF};/*������ʼ��������ַ��ÿ�ඳ�᷽����ʽΪ��ʼ��ַ+������ַ��8�ַ���ͬһCRC*/
	uchar8 V_Order,V_i,V_DI2;
	ushort16 V_Data_Length,V_Data_Num,V_FlashPage;
	ushort16 V_Cyc16[8]={0xFFFF};
	ushort16 V_Data_Deep;

	if(V_DataLen==0)/*û�й����б�,����Ĭ�Ͽռ�*/
	{
		V_Return_Flag=SF_MinFreezeDefProDistr(8);
		return V_Return_Flag;
	}

	Vu_TolNum=SF_GetMinFreezeTolNum(&P_Data[0],V_DataLen,&V_Cyc16[0]);/*��ȡ���Ӷ����ܷ�����*/
	if(Vu_TolNum>8)/*���8�ַ���*/
	{
		return	V_Return_Flag;
	}

	V_Order=SF_GetStr_698FreezeDataTableOrder(C_RelatedOAD_Min);/*��ȡĳ�ඳ��������Str_698FreezeDataTable�����*/
	if(V_Order == 0xFF)
	{
		return C_OtherErr_DAR;
	}

	V_StaFlashAddr=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;
	V_DI2=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);
	for(V_i=0;V_i<Vu_TolNum;V_i++)
	{
		if((V_StaFlashAddr>Str_698FreezeDataTable[V_Order].V_EndFlashAddr)||(V_StaFlashAddr>C_Flash_Max_Addr))/*�쳣*/
		{
			V_Return_Flag=SF_MinFreezeDefProDistr(Vu_TolNum);/*�쳣����ΪĬ�Ϸ���ռ�*/
			return V_Return_Flag;
		}

		V_DI2 &= 0x1F;
		V_DI2 |= (V_i<<5);/*��3λ��ʾ��ͬ�ķ�����*/
		V_Data_Length=SF_JudgeWriteDataLen(V_DI2);/*��ȡ��ͬ�����洢���ݳ���*/
		if(0==V_Data_Length)/*�쳣�ж�*/
		{
			return	V_Return_Flag;
		}

		V_Data_Num=(C_OneFlash_PageNum-C_LoadProfile_RevMode)/V_Data_Length;/*ÿҳ�ɴ洢����*/
		V_Data_Deep=SF_GetFreezeSaveDeep(V_DI2);/*��ȡ��ͬ�����洢���*/
		if(0==V_Data_Deep)
		{
			V_Data_Deep=C_MinFreezeNeedNum;
		}

		V_FlashPage=V_Data_Deep/V_Data_Num+1+2;/*���ඳ����Ҫ�洢ҳ����+1����ҳ��+2Ѳ����*/
		V_EndFlashAddr=V_StaFlashAddr+(V_FlashPage-1)*C_OneFlashPage;
		if((V_EndFlashAddr>Str_698FreezeDataTable[V_Order].V_EndFlashAddr)||(V_EndFlashAddr>C_Flash_Max_Addr))/*�쳣*/
		{
			V_Return_Flag=SF_MinFreezeDefProDistr(Vu_TolNum);/*�쳣����ΪĬ�Ϸ���ռ�*/
			return V_Return_Flag;
		}

		PF_Ulong32ToBuffer4(&Vu_FlashAddr[V_i*8],&V_StaFlashAddr,4);
		PF_Ulong32ToBuffer4(&Vu_FlashAddr[V_i*8+4],&V_EndFlashAddr,4);
		V_StaFlashAddr=V_EndFlashAddr+C_OneFlashPage;
	}

	V_Return_Flag=SF_WriteE2Three(E2Addr_Min_Free_FlashAddr_Allo,64,&Vu_FlashAddr[0]);/*д�����ַ*/
	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WR_E23_RAM_Data698(Str_3aTable *PStr_3aTable_E23RAM, ushort16 V_DataLen,
										uchar8 *P_Data, uchar8 V_DT_Type, uchar8 V_DI)
����������дE2������RAM���ݡ�����698OAD��ű��д������RAM��E2��ַʱ�����ݹ̶���񳤶��ж�
���������
		Str_3aTable *PStr_3aTable_E23RAM:Ҫ����3a����ṹ��Ԫ�ص�ַ��
		ushort16 V_DataLen��Ҫд�����ݳ���
		uchar8 *P_Data��Ҫд�����ݻ���
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��C_DataLenError��
����˵����
���û��ƣ�
��     ע��698����д���ڲ����ݳ��Ȳ����ж�(�ڲ�ѯ2����ʱ�����ж����ݳ���)��Ҳ�����ж��Ƚϣ���Ϊд�����ݳ���̫��������255
*********************************************************************************/
uchar8 SF_WR_E23_RAM_Data698(Str_3aTable *PStr_3aTable_E23RAM, ushort16 V_DataLen, uchar8 *P_Data, uchar8 V_DT_Type, uchar8 V_DI)
{
	ushort16 V_CRC16,V_i,V_Len;
	uchar8 P_CRC[2];
	ushort16 V_E2Addr;
	uchar8 * P_RamAddr=NULL;
	uchar8 V_Return_Flag;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;		/*�ð�ȫ��־*/
	V_Len=V_DataLen;
	P_RamAddr=(*PStr_3aTable_E23RAM).V_RamAddr;
	V_E2Addr=(*PStr_3aTable_E23RAM).V_E2BakeUp1Addr;
	V_CRC16=PF_Cal_CRC(&P_Data[0],V_Len);		/*����CRC*/

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;		/*�ð�ȫ��־*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);
	V_Len=V_Len+C_CRCLen2;		/*����CRC*/

	if(DT_Ref_E23_RAMCRC_DI0==V_DT_Type)		/*��ַ����*/
	{
		if(V_DI<1)
		{
			return C_AbnormalError;
		}

		P_RamAddr=P_RamAddr+(V_DI-1)*(C_698Free_OADTabLen+C_CRCLen2);		/*698 OAD��ű�̶�����*/
		V_E2Addr=V_E2Addr+(V_DI-1)*(C_698Free_OADTabLen+C_CRCLen2);
	}

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}
	else
	{
		for(V_i=0;V_i<V_DataLen;V_i++)		/*RAM ��ֵ*/
		{
			*(P_RamAddr+V_i)= *(P_Data+V_i);
		}
	}

	P_RamAddr[V_DataLen]=P_CRC[0];
	P_RamAddr[V_DataLen+1]=P_CRC[1];

	V_Return_Flag=SF_WriteE2Three698(V_E2Addr,(V_Len-2),&P_Data[0]);		/*дE2��������*/

	if(V_DI==(uchar8)(CMin_Free_OADTab&0x000000FF))		/*�ж��Ƿ���Ӷ���OAD�����б�#define CMin_Free_OADTab   0x04FE1002       *//*���Ӷ���OAD��ű�*/
	{	/*���д洢�ռ����*/
		V_Return_Flag=SF_MinFreezeProDistr(&P_Data[0],V_DataLen);
	}

	GV_D_SafeFlag=C_Clear_SafeFlag;
	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WR_E23_RAM_EnergyData(Str_3aTable *PStr_3aTable_E23RAM, ushort16 V_DataLen,
											uchar8 *P_Data, uchar8 V_DT_Type, uchar8 V_DI)
����������дE2������RAM����.�ò���ֻ���е�ǰ�������ݸ��´���
���������
		Str_3aTable*PStr_3aTable_E23RAM:Ҫ����3a����ṹ���ַ��
		ushort16V_3aTable_Line��Ҫ����3a������кţ�
		ushort16V_DataLen��Ҫд�����ݳ���
		uchar8*P_Data��Ҫд�����ݻ���
		uchar8V_DT_Type��Ҫд����������
		uchar8V_DI:���ڼ������ݾ��Ե�ַ
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��C_DataLenError��
����˵����
���û��ƣ�
��     ע��ֻ���е�ǰ���ܴ���
*********************************************************************************/
uchar8 SF_WR_E23_RAM_EnergyData(Str_3aTable *PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_DI)
{
	ushort16 V_CRC16,V_i;
	uchar8 P_CRC[2],V_Len;
	uchar8 PV_Data[C_RAM_Max];
	ushort16 V_E2Addr;
	uchar8 * P_RamAddr=NULL;
	uchar8 V_Return_Flag;
	ulong64 V_RamEnData,V_E2EnData;
	uchar8 V_Return_Flag1=C_Error;
	long64 V_EnDataAdd;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;	/*�ð�ȫ��־*/

	if(V_3aTable_Line>=Str_3aTable_E23RAM_Len)	/*����������*/
	{
		return C_AbnormalError;
	}

	if((C_RAM_Max<(V_DataLen+2))||(V_DataLen!=C_CurrDataLen5))	/*����ֻ�е�ǰ���������ݣ�5�ֽ�*/
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	V_Len=(uchar8)V_DataLen;

	P_RamAddr=PStr_3aTable_E23RAM[V_3aTable_Line].V_RamAddr;
	V_E2Addr=PStr_3aTable_E23RAM[V_3aTable_Line].V_E2BakeUp1Addr;
	V_Return_Flag=SF_ReadFRAMThree(V_E2Addr,V_DataLen,PV_Data);
	if(C_OK==V_Return_Flag)
	{
		PF_Buffer8ToUlong64(&PV_Data[0],&V_E2EnData,C_CurrDataLen5);
		PF_Buffer8ToUlong64(&P_Data[0],&V_RamEnData,C_CurrDataLen5);

		V_EnDataAdd=V_RamEnData-V_E2EnData;

		if(0==V_EnDataAdd)	/*����Ϊ0*/
		{
			return	C_OK;
		}
		else	/*���������������ж�*/
		{
			switch(V_E2Addr)
			{
				case	E2Addr_SC_Com_Ac_Tol_En_Pul_0:	/*��ǰ�����������õ��������ܻ�д����Ϊ0.����󣬱���ֻ�ж������ĺ�����*/
				case	E2Addr_M_Com_Ac_Tol_En_Pul_0:
				case	E2Addr_Y_Com_Ac_Tol_En_Pul_0:
				{
					if(V_EnDataAdd<C_RAMRefE2En_MaxPluse)
					{
						V_Return_Flag1=C_OK;
					}
				}break;

				case	E2Addr_ChargeBal_Hex_Deal:	/*��ǰʣ���д������С��ԭ���洢����*/
				{
					if(V_DI==(uchar8)(CChargeBal_Hex_Full&0x000000FF))	/*��ֵʱ����ǰʣ������ж����ݵĺ�����*/
					{
						V_Return_Flag1=C_OK;
					}
					else	/*�����ۼ��ж����ݵĺ�����*/
					{
						if(V_EnDataAdd<0)
						{
							V_Return_Flag1=C_OK;
						}
					}
				}break;

				case	E2Addr_OverDraft_Hex_Deal:	/*��ǰ͸֧��д�����ݴ���ԭ���洢����*/
				{
					if(V_DI==(uchar8)(COverDraft_Hex_Full&0x000000FF))	/*��ֵʱ����ǰ͸֧�����ж����ݵĺ�����*/
					{
						V_Return_Flag1=C_OK;
					}
					else	/*�����ۼ��ж����ݵĺ�����*/
					{
						if(V_EnDataAdd>0)
						{
							V_Return_Flag1=C_OK;
						}
					}
				}break;

				default:	/*�����������ݣ������㣬ͬʱС������*/
				{
					if((V_EnDataAdd>0)&&(V_EnDataAdd<C_RAMRefE2En_MaxPluse))
					{
						V_Return_Flag1=C_OK;
					}
				}break;
			}

			GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;	/*�ð�ȫ��־*/

			if(C_OK==V_Return_Flag1)	/*д����ܺ���������������*/
			{
				PF_CopyDataBytes(P_Data,&PV_Data[0],V_Len);
				V_Return_Flag=SF_WriteFRAMThree(V_E2Addr,V_Len,&PV_Data[0]);

				if(C_OK==V_Return_Flag)	/*����RAM����*/
				{
					V_CRC16=PF_Cal_CRC(&PV_Data[0],V_Len);
					PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

					PV_Data[V_Len]=P_CRC[0];
					PV_Data[V_Len+1]=P_CRC[1];
					V_Len=V_Len+C_CRCLen2;

					if(C_W_SafeFlag!=GV_D_SafeFlag)
					{
						return C_SafeFlagError;
					}
					else
					{
						for(V_i=0;V_i<V_Len;V_i++)	/*RAM��ֵ*/
						{
							*(P_RamAddr+V_i) = *(PV_Data+V_i);
						}
					}
				}
			}
		}
	}
	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WR_E23_RAM_Data(Str_3aTable *PStr_3aTable_E23RAM, ushort16 V_DataLen, uchar8 *P_Data,
									uchar8 V_DT_Type, uchar8V_DI)
����������дE2������RAM����
���������
		Str_3aTable *PStr_3aTable_E23RAM:Ҫ����3a����ṹ���ַ��
		ushort16 V_3aTable_Line��Ҫ����3a������кţ�
		ushort16 V_DataLen��Ҫд�����ݳ���
		uchar8 *P_Data��Ҫд�����ݻ���
		uchar8 V_DT_Type��Ҫд����������
		uchar8 V_DI:���ڼ������ݾ��Ե�ַ
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��C_DataLenError��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_WR_E23_RAM_Data(Str_3aTable * PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_DI)
{
	ushort16 V_CRC16,V_i;
	uchar8 P_CRC[C_CRCLen2],V_Len;
	uchar8 PV_Data[C_RAM_Max];
	ushort16 V_E2Addr;
	uchar8 * P_RamAddr=NULL;
	uchar8 V_Return_Flag;
	uchar8 V_j;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;		/*�ð�ȫ��־*/

	if(V_3aTable_Line>=Str_3aTable_E23RAM_Len)		/*����������*/
	{
		return C_AbnormalError;
	}

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	V_Len=(uchar8)V_DataLen;
	P_RamAddr=PStr_3aTable_E23RAM[V_3aTable_Line].V_RamAddr;
	V_E2Addr=PStr_3aTable_E23RAM[V_3aTable_Line].V_E2BakeUp1Addr;

	if(DT_W_Ref_E23_RAMCRC_Te==V_DT_Type)		/*���ʵ��д��������*/
	{
		V_Len=(uchar8)V_DataLen;
		V_Len=V_Len/C_MaxRatesNum;		/*�������ĵ��ܸ����ֿ��洢�����ݽ�ȡ*/

		for(V_j=0;V_j<C_MaxRatesNum;V_j++)
		{
			P_RamAddr=PStr_3aTable_E23RAM[V_3aTable_Line].V_RamAddr;
			V_E2Addr=PStr_3aTable_E23RAM[V_3aTable_Line].V_E2BakeUp1Addr;

			PF_CopyDataBytes(&P_Data[V_j*V_Len],&PV_Data[0],V_Len);
			V_CRC16=PF_Cal_CRC(&PV_Data[0],V_Len);		/*����CRC*/
			GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;		/*�ð�ȫ��־*/
			PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);
			PV_Data[V_Len]=P_CRC[0];
			PV_Data[V_Len+1]=P_CRC[1];
			V_Len=V_Len+C_CRCLen2;

			P_RamAddr=P_RamAddr+V_j*V_Len;		/*����E2��RAM��ַ*/
			V_E2Addr=V_E2Addr+V_j*V_Len;

			if(C_W_SafeFlag!=GV_D_SafeFlag)
			{
				return C_SafeFlagError;
			}
			else
			{
				for(V_i=0;V_i<V_Len;V_i++)		/*RAM ��ֵ*/
				{
					*(P_RamAddr+V_i)= *(PV_Data+V_i);
				}

				V_Return_Flag=SF_WriteE2Three(V_E2Addr,(V_Len-C_CRCLen2),&PV_Data[0]);		/*дE2����*/
			}

			V_Len -= C_CRCLen2;
		}

		GV_D_SafeFlag=C_Clear_SafeFlag;
		return V_Return_Flag;
	}
	else
	{
		PF_CopyDataBytes(P_Data,&PV_Data[0],V_Len);
		V_CRC16=PF_Cal_CRC(&PV_Data[0],V_Len);		/*����CRC*/
		GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;		/*�ð�ȫ��־*/
		PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

		PV_Data[V_Len] = P_CRC[0];
		PV_Data[V_Len+1] = P_CRC[1];
		V_Len = V_Len + C_CRCLen2;

		if(DT_Ref_E23_RAMCRC_DI0 == V_DT_Type)		/*��ַ����*/
		{
			if(V_DI<1)
			{
				return C_AbnormalError;
			}

			P_RamAddr = P_RamAddr+(V_DI-1)*V_Len;
			V_E2Addr = V_E2Addr+(V_DI-1)*V_Len;
		}

		if(DT_Ref_E23_RAMCRC_DI0_2 == V_DT_Type)		/*04FE0202���������DI0=2��ʼ����*/
		{
			if(V_DI<2)
			{
				return C_AbnormalError;
			}

			P_RamAddr=P_RamAddr+(V_DI-2)*V_Len;
			V_E2Addr=V_E2Addr+(V_DI-2)*V_Len;
		}

		if(C_W_SafeFlag!=GV_D_SafeFlag)
		{
			return C_SafeFlagError;
		}
		else
		{
			for(V_i=0;V_i<V_Len;V_i++)		/*RAM ��ֵ*/
			{
				*(P_RamAddr+V_i)= *(PV_Data+V_i);
			}
		}

		if((DT_Ref_E23_RAMCRC==V_DT_Type)
			||(DT_Ref_E23_RAMCRC_DI0==V_DT_Type)
			||(DT_Ref_E23_RAMCRC_DI0_2==V_DT_Type))		/*����E2��������*/
		{
			V_Return_Flag=SF_WriteE2Three(V_E2Addr,(V_Len-C_CRCLen2),&PV_Data[0]);
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}
		else
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_OK;
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WR_E23_Data(ushort16 V_E2Addr, ushort16 V_DataLen, uchar8 *P_Data)
����������дE2��������
���������
		ushort16V_E2Addr��д������E2��ַ��
		ushort16V_DataLen��Ҫд�����ݳ���
		uchar8*P_Data��Ҫд�����ݻ���
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_WR_E23_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_Return_Flag;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;		/*�ð�ȫ��־*/
	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;		/*�ð�ȫ��־*/

	V_Return_Flag=SF_WriteE2Three(V_E2Addr,(uchar8)V_DataLen,P_Data);
	GV_D_SafeFlag=C_Clear_SafeFlag;

	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WriteFRAMThree(ushort16 V_E2Addr, uchar8 V_DataLen, uchar8 *P_Data)
����������д�����������ݣ�ֱ�Ӳ�������,�ڲ�����CRC
���������
		ushort16 V_E2Addr��д�����������ַ��
		uchar8 V_DataLen��Ҫд�����ݳ���,������CRC����
		uchar8 *P_Data��Ҫд�����ݻ���
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��
����˵����
���û��ƣ�
��     ע���ڲ��жϰ�ȫ��־���ⲿ����ǰҪ���㰲ȫ��־������д���ɹ�
*********************************************************************************/
uchar8 SF_WriteFRAMThree(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_i;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 PV_RData[C_RAM_Max];  /*���ڶ��Ƚ�*/
	uchar8 V_Len,P_CRC[C_CRCLen2];
	ushort16 V_CRC16;

	if(C_RAM_Max<(V_DataLen+C_CRCLen2))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	PF_CopyDataBytes(P_Data,&PV_Data[0],V_DataLen);
	V_CRC16=PF_Cal_CRC(&PV_Data[0],V_DataLen);		/*����CRC*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);
	PV_Data[V_DataLen]=P_CRC[0];
	PV_Data[V_DataLen+1]=P_CRC[1];
	V_Len=V_DataLen+C_CRCLen2;

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}
	else
	{
		InF_FRAMWPEnable();		/*����E2 WP*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*��ȫ��־��*/
		{
			InF_FRAMWPDisable();		/*�ر�WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteFRAM(V_E2Addr,&PV_Data[0],(ushort16)V_Len);
		InF_ReadFRAM(V_E2Addr,&PV_RData[0],(ushort16)V_Len);

		for(V_i=0;V_i<V_Len;V_i++)		/*���Ƚ�*/
		{
			if(*(PV_Data+V_i)!=*(PV_RData+V_i))
			{
				break;
			}
		}

		if(V_i!=V_Len)		/*дE2����*/
		{
			return C_IICError;
		}

		InF_FRAMWPEnable();		/*дE2����2*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*��ȫ��־��*/
		{
			InF_FRAMWPDisable();		/*�ر�WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteFRAM(V_E2Addr+FRAM_BackUp2_Space,&PV_Data[0],(ushort16)V_Len);
		InF_ReadFRAM(V_E2Addr+FRAM_BackUp2_Space,&PV_RData[0],(ushort16)V_Len);

		for(V_i=0;V_i<V_Len;V_i++)		/*���Ƚ�*/
		{
			if(*(PV_Data+V_i)!=*(PV_RData+V_i))
			{
				break;
			}
		}

		if(V_i!=V_Len)		/*дE2����*/
		{
			return C_IICError;
		}

		InF_FRAMWPEnable();		/*дE2����3*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*��ȫ��־��*/
		{
			InF_FRAMWPDisable();		/*�ر�WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteFRAM(V_E2Addr+FRAM_BackUp3_Space,&PV_Data[0],(ushort16)V_Len);
		InF_ReadFRAM(V_E2Addr+FRAM_BackUp3_Space,&PV_RData[0],(ushort16)V_Len);

		for(V_i=0;V_i<V_Len;V_i++)		/*���Ƚ�*/
		{
			if(*(PV_Data+V_i)!=*(PV_RData+V_i))
			{
				break;
			}
		}

		if(V_i!=V_Len)		/*дE2����*/
		{
			return C_IICError;
		}
	}

	return C_OK;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WriteE2Three(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
����������дE2�������ݣ�ֱ�Ӳ���E2,�ڲ�����CRC
���������
		ushort16 V_E2Addr��д������E2��ַ��
		uchar8 V_DataLen��Ҫд�����ݳ���,������CRC����
		uchar8 *P_Data��Ҫд�����ݻ���
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��
����˵����
���û��ƣ�
��     ע���ڲ��жϰ�ȫ��־���ⲿ����ǰҪ���㰲ȫ��־������д���ɹ�
*********************************************************************************/
uchar8 SF_WriteE2Three(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_i;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 PV_RData[C_RAM_Max];		/*���ڶ��Ƚ�*/
	uchar8 V_Len,P_CRC[C_CRCLen2];
	ushort16 V_CRC16;

	if(C_RAM_Max<(V_DataLen+C_CRCLen2))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	PF_CopyDataBytes(P_Data,&PV_Data[0],V_DataLen);
	V_CRC16=PF_Cal_CRC(&PV_Data[0],V_DataLen);		/*����CRC*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);
	PV_Data[V_DataLen]=P_CRC[0];
	PV_Data[V_DataLen+1]=P_CRC[1];
	V_Len=V_DataLen+C_CRCLen2;

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}
	else
	{
		InF_E2WPEnable();		/*����E2 WP*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*��ȫ��־��*/
		{
			InF_E2WPDisable();		/*�ر�WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteE2(V_E2Addr,&PV_Data[0],(ushort16)V_Len);
		InF_ReadE2(V_E2Addr,&PV_RData[0],(ushort16)V_Len);

		for(V_i=0;V_i<V_Len;V_i++)		/*���Ƚ�*/
		{
			if(*(PV_Data+V_i)!=*(PV_RData+V_i))
			{
				break;
			}
		}

		if(V_i!=V_Len)		/*дE2����*/
		{
			return C_IICError;
		}

		InF_E2WPEnable();		/*дE2����2*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*��ȫ��־��*/
		{
			InF_E2WPDisable();		/*�ر�WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteE2(V_E2Addr+E2_BackUp2_Space,&PV_Data[0],(ushort16)V_Len);
		InF_ReadE2(V_E2Addr+E2_BackUp2_Space,&PV_RData[0],(ushort16)V_Len);

		for(V_i=0;V_i<V_Len;V_i++)		/*���Ƚ�*/
		{
			if(*(PV_Data+V_i)!=*(PV_RData+V_i))
			{
				break;
			}
		}

		if(V_i!=V_Len)		/*дE2����*/
		{
			return C_IICError;
		}

		InF_E2WPEnable();		/*дE2����3*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*��ȫ��־��*/
		{
			InF_E2WPDisable();		/*�ر�WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteE2(V_E2Addr+E2_BackUp3_Space,&PV_Data[0],(ushort16)V_Len);
		InF_ReadE2(V_E2Addr+E2_BackUp3_Space,&PV_RData[0],(ushort16)V_Len);

		for(V_i=0;V_i<V_Len;V_i++)		/*���Ƚ�*/
		{
			if(*(PV_Data+V_i)!=*(PV_RData+V_i))
			{
				break;
			}
		}

		if(V_i!=V_Len)		/*дE2����*/
		{
			return C_IICError;
		}
	}

	return C_OK;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WriteE2Three698(ushort16 V_E2Addr, ushort16 V_DataLen, uchar8 *P_Data)
����������дE2�������ݣ�ֱ�Ӳ���E2,�ڲ�����CRC
���������
		ushort16 V_E2Addr��д������E2��ַ��
		uchar8 V_DataLen��Ҫд�����ݳ���,������CRC����
		uchar8 *P_Data��Ҫд�����ݻ���
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��
����˵����
���û��ƣ�
��     ע���ڲ��жϰ�ȫ��־���ⲿ����ǰҪ���㰲ȫ��־������д���ɹ�.д�����ݳ��ȴ���255��������д������ж�
*********************************************************************************/
uchar8 SF_WriteE2Three698(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_Return_Flag;
	uchar8 P_CRC[C_CRCLen2];
	ushort16 V_CRC16,V_Len;

	V_CRC16=PF_Cal_CRC(&P_Data[0],V_DataLen);		/*����CRC*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

	V_Len=V_DataLen;

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}
	else
	{
		InF_E2WPEnable();		/*����E2 WP*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*��ȫ��־��*/
		{
			InF_E2WPDisable();		/*�ر�WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		V_Return_Flag=InF_WriteE2(V_E2Addr,&P_Data[0],V_Len);

		InF_E2WPEnable();
		V_Return_Flag=InF_WriteE2((V_E2Addr+V_Len),&P_CRC[0],C_CRCLen2);		/*CRC����д*/

		InF_E2WPEnable();		/*дE2����2*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*��ȫ��־��*/
		{
			InF_E2WPDisable();		/*�ر�WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		V_Return_Flag=InF_WriteE2(V_E2Addr+E2_BackUp2_Space,&P_Data[0],V_Len);

		InF_E2WPEnable();
		V_Return_Flag=InF_WriteE2(V_E2Addr+E2_BackUp2_Space+V_Len,&P_CRC[0],C_CRCLen2);

		InF_E2WPEnable();		/*дE2����3*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*��ȫ��־��*/
		{
			InF_E2WPDisable();		/*�ر�WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		V_Return_Flag=InF_WriteE2(V_E2Addr+E2_BackUp3_Space,&P_Data[0],V_Len);

		InF_E2WPEnable();
		V_Return_Flag=InF_WriteE2(V_E2Addr+E2_BackUp3_Space+V_Len,&P_CRC[0],C_CRCLen2);

		return V_Return_Flag;
	}
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WriteFlash_Data(uchar8 *P_Data,ushort16 V_Data_Length,Str_3cTable *PStr_3cTable,
									ulong32 V_Data_Id, ushort16 V_3cTable_Line, uchar8 V_Type)
����������дFlash����,ֻ����1�Σ�������д�����򷵻���Ȩ��,ͨ��DI0��4λ�ж�
���������
		uchar8 *P_Data:д���ݻ��棻
		uchar8 V_Data_Length��д���ݾ��峤�ȣ�
		Str_3cTable *PStr_3cTable����Ӧ3������׵�ַ��
		ulong32 V_Data_Id��DI0-DI3���ݱ�ʶ��
		ushort16 V_3cTable_Line��Ҫ����3c������кţ�
		uchar8 V_Type:���ݴ洢����
�����������
���ز�����C_OK��C_SafeFlagError��C_SPIError,C_IICError��C_NoAccess��C_DataLenError��
����˵����
���û��ƣ�
��     ע��дFlash���ݣ��ڲ�û�п�ҳ����.��¼��������3�ֽڣ�Ŀǰֻ��У���¼
*********************************************************************************/
uchar8 SF_WriteFlash_Data(uchar8 *P_Data,ushort16 V_Data_Length,Str_3cTable *PStr_3cTable,ulong32 V_Data_Id,ushort16 V_3cTable_Line,uchar8 V_Type)
{
	uchar8 P_Dgree[CLAll_Loss_Vol_Degree];
	ushort16 V_E2Addr,V_OffAddr;
	ulong32 V_Dgree;
	Str_4Table *PStr_4TableAddr=NULL;
	ulong32 P_FlashAddr1[2];
//	ulong32 P_FlashAddr2[2];
	uchar8 V_Return_Flag;
	uchar8 V_ucDataLen_RW;		/*ɽ��˫Э�飬��������ʱ��ʱ�α�̼�¼������Ϊ4�ֽ�*/

	if(V_3cTable_Line>=Str_3cTable_Flash_Len)
	{
		return C_AbnormalError;		/*����������*/
	}

	V_Dgree=(V_Data_Id&0x0000000F);		/*ȡDI��4λ*/
	if(0x00000001!=V_Dgree)		/*����д���ݲ�Ҫ��ֻ����1�Σ�������д*/
	{
		return C_NoAccess;
	}

	V_OffAddr=0xFFFF;		/*�ȸ�ֵ����*/

	V_E2Addr=PStr_3cTable[V_3cTable_Line].V_Num_E2BakeUp1Addr;		/*ȡFlash��¼����E2��ַ*/

	V_ucDataLen_RW = 4;
	V_Return_Flag=SF_ReadE2Three(V_E2Addr,V_ucDataLen_RW,&P_Dgree[0]);

#if 0
	/*ɽ��˫Э�飬����ʱ��ʱ�α�̼�¼������Ϊ4�ֽ�,ʵ��Э��645��3�ֽڣ�698��4�ֽڣ��洢��Ϊ4�ֽ�*/
	if(((V_Data_Id & 0xFFFFFF00) == CProgPT_Degree)		/*ʱ�α�0x033005C1��0x033005D1��0x033005E1��0x033005F1*/
		|| ((V_Data_Id & 0xFFFFFF00) == CProgTZ_CurrentPart_Degree))		/*ʱ����0x0330F601*/
	{
		V_ucDataLen_RW = 4;
		V_Return_Flag=SF_ReadE2Three(V_E2Addr,V_ucDataLen_RW,&P_Dgree[0]);
	}
	else
	{
		V_ucDataLen_RW = 3;
		V_Return_Flag=SF_ReadE2Three(V_E2Addr,V_ucDataLen_RW,&P_Dgree[0]);
		P_Dgree[3]=0;
	}
#endif

	if((C_OK!=V_Return_Flag)&&(C_CrcErr_DataZero!=V_Return_Flag))
	{
		return V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&P_Dgree[0],&V_Dgree,4);
	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;		/*�ð�ȫ��־*/

	PStr_4TableAddr=(Str_4Table *)(PStr_3cTable[V_3cTable_Line].PStr_4TableAddr);		/*ȡ4�����ַ*/
	if(0xFFFFFFFF==((ulong32)PStr_4TableAddr))		/*����+1�ж�,4�����ּ�*/
	{
		V_Dgree=V_Dgree+1;
	}
	else
	{
		V_OffAddr=SF_GetOffAddr(PStr_4TableAddr,V_Data_Id,V_Type,PStr_3cTable[V_3cTable_Line].V_Str_4TableLen);		/*ȡƫ�Ƶ�ַ*/
		if(0==V_OffAddr)		/*ƫ�Ƶ�ַΪ0,���μ�¼�״�д�룬��������*/
		{
			V_Dgree=V_Dgree+1;
		}
		else
		{
			if(0xFFFF==V_OffAddr)		/*���ҳ���*/
			{
				if(_DEBUG)
				{
					/**/
				}
				return C_AbnormalError;		/*������������£��������*/
			}
		}
	}

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;		/*�ð�ȫ��־*/
#if 0
	if(DT_Flash_Tol_DI0_W_Sett_En==V_Type)		/*14��Flash�����������ݣ�����DI0��ʾ����������ģ��д����ʱһ��д���ݲ㣬���ݲ��ڲ������������������ʱ��ֿ��洢*/
	{	/*�������*/
		SF_GetFlashAddr(V_Dgree,PStr_3cTable[V_3cTable_Line].V_StaFlashAddr,SettEn_Data_Len,PStr_3cTable[V_3cTable_Line].V_EndFlashAddr,&P_FlashAddr1[0]);
		SF_GetFlashAddr(V_Dgree,FlashStAddr_SettTime,SettTime_Data_Len,FlashEndAddr_SettTime,&P_FlashAddr2[0]);		/*�����ս���ʱ��*/
	}
	else
	{
#endif
		SF_GetFlashAddr(V_Dgree,PStr_3cTable[V_3cTable_Line].V_StaFlashAddr,PStr_3cTable[V_3cTable_Line].V_DataToalLen,PStr_3cTable[V_3cTable_Line].V_EndFlashAddr,&P_FlashAddr1[0]);
		PStr_4TableAddr=(Str_4Table *)(PStr_3cTable[V_3cTable_Line].PStr_4TableAddr);		/*ȡ4�����ַ*/
		if(0xFFFFFFFF!=((ulong32)PStr_4TableAddr))
		{
			V_OffAddr=SF_GetOffAddr(PStr_4TableAddr,V_Data_Id,V_Type,PStr_3cTable[V_3cTable_Line].V_Str_4TableLen);		/*ȡƫ�Ƶ�ַ*/
			if(0xFFFF==V_OffAddr)		/*���ҳ���*/
			{
				if(_DEBUG)
				{
					/**/
				}
				return C_AbnormalError;		/*������������£��������*/
			}
			P_FlashAddr1[1]=P_FlashAddr1[1]+(ulong32)V_OffAddr;		/*ҳ�ڵ�ַ*/
		}
#if 0
	}
#endif
	P_FlashAddr1[0]=P_FlashAddr1[0]+P_FlashAddr1[1];		/*д�����ݾ��Ե�ַ*/
	if(P_FlashAddr1[0]>C_Flash_Max_Addr)		/*Flash��ַ�������۲����� */
	{
		return C_AbnormalError;
	}

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}
#if 0
	if(DT_Flash_Tol_DI0_W_Sett_En==V_Type)
	{
		V_Return_Flag=SF_WriteFlash(P_FlashAddr1[0],(P_Data+SettTime_Data_Len),SettEn_Data_Len,1);		/*�������*/
		if(C_OK!=V_Return_Flag)
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}

		P_FlashAddr2[0]=P_FlashAddr2[0]+P_FlashAddr2[1];		/*�����ս���ʱ����Ե�ַ*/
		V_Return_Flag=SF_WriteFlash(P_FlashAddr2[0],P_Data,SettTime_Data_Len,1);
	}
	else
	{
		V_Return_Flag=SF_WriteFlash(P_FlashAddr1[0],P_Data,V_Data_Length,1);
	}
#endif

	V_Return_Flag=SF_WriteFlash(P_FlashAddr1[0],P_Data,V_Data_Length,1);

	if(C_OK!=V_Return_Flag)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return V_Return_Flag;
	}

	PF_Ulong32ToBuffer4(&P_Dgree[0],&V_Dgree,4);
	if(0xFFFFFFFF==((ulong32)PStr_4TableAddr))
	{
		V_Return_Flag=SF_WriteE2Three(V_E2Addr,V_ucDataLen_RW,&P_Dgree[0]);		/*дE2��¼����*/
	}
	else
	{
		if(0==V_OffAddr)
		{
			V_Return_Flag=SF_WriteE2Three(V_E2Addr,V_ucDataLen_RW,&P_Dgree[0]);
		}
	}

	GV_D_SafeFlag=C_Clear_SafeFlag;
	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_ReadE2Three_698(ushort16 V_E2Addr, ushort16 V_DataLen, uchar8 *P_Data)
������������E2��������,�ڲ��ж�CRC.698�����ݳ���Ϊushort16
���������
		ushort16 V_E2Addr��������E2��ַ��
		ushort16 V_DataLen�������ݳ���
		uchar8 *P_Data�������ݻ���(������CRC)
�����������
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע�������ݲ���ȷ��Ҳ������������
*********************************************************************************/
uchar8 SF_ReadE2Three_698(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 PV_CRC1[C_CRCLen2],PV_CRC2[C_CRCLen2];
	uchar8 V_ReCRC,V_Return_Flag;
	ushort16 V_CRC16;

	V_Return_Flag=InF_ReadE2(V_E2Addr,&P_Data[0],V_DataLen);     /*��E2��1��*/
	V_Return_Flag=InF_ReadE2((V_E2Addr+V_DataLen),&PV_CRC1[0],C_CRCLen2);     /*��E2��1��CRC*/

	V_CRC16=PF_Cal_CRC(&P_Data[0],V_DataLen);
	PF_Ushort16ToBuffer2(&PV_CRC2[0],&V_CRC16);
	V_ReCRC=C_OK;

	if((PV_CRC1[0]!=PV_CRC2[0])||(PV_CRC1[1]!=PV_CRC2[1]))
	{
		V_ReCRC=C_CRCError;
	}

	if(C_CRCError==V_ReCRC)
	{
		V_Return_Flag=InF_ReadE2(V_E2Addr+E2_BackUp2_Space,&P_Data[0],V_DataLen);     /*��E2��1��*/
		V_Return_Flag=InF_ReadE2((V_E2Addr+V_DataLen+E2_BackUp2_Space),&PV_CRC1[0],C_CRCLen2);     /*��E2��1��CRC*/

		V_CRC16=PF_Cal_CRC(&P_Data[0],V_DataLen);
		PF_Ushort16ToBuffer2(&PV_CRC2[0],&V_CRC16);

		if((PV_CRC1[0]!=PV_CRC2[0])||(PV_CRC1[1]!=PV_CRC2[1]))
		{
			V_ReCRC=C_CRCError;
		}

		if(C_CRCError==V_ReCRC)
		{
			V_Return_Flag=InF_ReadE2(V_E2Addr+E2_BackUp3_Space,&P_Data[0],V_DataLen);     /*��E2��1��*/
			V_Return_Flag=InF_ReadE2((V_E2Addr+V_DataLen+E2_BackUp3_Space),&PV_CRC1[0],C_CRCLen2);     /*��E2��1��CRC*/

			V_CRC16=PF_Cal_CRC(&P_Data[0],V_DataLen);
			PF_Ushort16ToBuffer2(&PV_CRC2[0],&V_CRC16);

			if((PV_CRC1[0]!=PV_CRC2[0])||(PV_CRC1[1]!=PV_CRC2[1]))
			{
				V_ReCRC=C_CRCError;
			}
		}
	}

	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;    /*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;      /*���ܷ���C_CrcErr_DataZero*/
		}
		else
		{
			return C_OK;
		}
	}
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_ReadE2Three_698_AndCRC(ushort16 V_E2Addr, ushort16 V_DataLen, uchar8 *P_Data)
������������E2��������,����CRC.698�����ݳ���Ϊushort16
���������
		ushort16 V_E2Addr��������E2��ַ��
		ushort16 V_DataLen�������ݳ��ȣ�������CRC���ȣ�
		uchar8 *P_Data�������ݻ��棬����CRC
�����������
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע�������ݲ���ȷ��Ҳ�����������ݡ�ע��ú�����SF_ReadE2Three_698����
SF_ReadE2Three_698:�������ݲ�����CRC��SF_ReadE2Three_698_AndCRC���������ݰ���CRC��
*********************************************************************************/
uchar8 SF_ReadE2Three_698_AndCRC(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_ReCRC = C_CRCError,V_Return_Flag = C_OtherErr_DAR;

	V_Return_Flag=InF_ReadE2(V_E2Addr,&P_Data[0],(V_DataLen+C_CRCLen2));     /*��E2��1������CRC*/

	V_ReCRC=PF_Check_CRC(&P_Data[0],(V_DataLen+C_CRCLen2));

	if( (C_OK != V_ReCRC) || (C_OK != V_Return_Flag) )
	{
		V_Return_Flag=InF_ReadE2((V_E2Addr+E2_BackUp2_Space),&P_Data[0],(V_DataLen+C_CRCLen2));     /*��E2��2��*/

		V_ReCRC=PF_Check_CRC(&P_Data[0],(V_DataLen+C_CRCLen2));

		if( (C_OK != V_ReCRC) || (C_OK != V_Return_Flag) )
		{
			V_Return_Flag=InF_ReadE2((V_E2Addr+E2_BackUp3_Space),&P_Data[0],(V_DataLen+C_CRCLen2));     /*��E2��3��*/
			V_ReCRC=PF_Check_CRC(&P_Data[0],(V_DataLen+C_CRCLen2));
		}
		else
		{
			;
		}
	}
	else
	{
		;
	}

	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;    /*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;
		}
		else
		{
			return C_OK;
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_ReadFRAMThree_AndCRC(ushort16 V_E2Addr, uchar8 V_DataLen, uchar8 *P_Data)
������������������������,����CRC
���������
		ushort16 V_E2Addr�������������ַ��
		uchar8 V_DataLen�������ݳ��ȣ�������CRC���ȣ�
		uchar8 *P_Data�������ݻ��棬����CRC
���������
��
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע�������ݲ���ȷ��Ҳ�����������ݡ�ע��ú�����SF_ReadFRAMThree����
SF_ReadFRAMThree:�������ݲ�����CRC��SF_ReadFRAMThree_AndCRC���������ݰ���CRC��
*********************************************************************************/
uchar8 SF_ReadFRAMThree_AndCRC(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_ReCRC = C_CRCError,V_Return_Flag = C_OtherErr_DAR;

	V_Return_Flag=InF_ReadFRAM(V_E2Addr,&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*�������1��*/

	V_ReCRC=PF_Check_CRC(&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

	if( (C_OK != V_ReCRC) || (C_OK != V_Return_Flag) )
	{
		V_Return_Flag=InF_ReadFRAM((V_E2Addr+FRAM_BackUp2_Space),&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*��E2��2��*/
		V_ReCRC=PF_Check_CRC(&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

		if( (C_OK != V_ReCRC) || (C_OK != V_Return_Flag) )
		{
			V_Return_Flag=InF_ReadFRAM((V_E2Addr+FRAM_BackUp3_Space),&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*��E2��3��*/
			V_ReCRC=PF_Check_CRC(&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));
		}
		else
		{
			;
		}
	}
	else
	{
		;
	}

	if(C_OK!=V_Return_Flag)
	{
		return  V_Return_Flag;		/*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;
		}
		else
		{
			return C_OK;
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_ReadFRAMThree(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
������������������������,�ڲ��ж�CRC
���������
		ushort16V_E2Addr�������������ַ��
		uchar8V_DataLen�������ݳ���
		uchar8*P_Data�������ݻ���(������CRC)
�����������
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע�������ݲ���ȷ��Ҳ������������
*********************************************************************************/
uchar8 SF_ReadFRAMThree(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
{
	uchar8 PV_Data[C_RAM_Max];
	uchar8 V_ReCRC = C_CRCError,V_Return_Flag = C_OtherErr_DAR;

	if((V_DataLen+C_CRCLen2)<=C_RAM_Max)
	{
		V_Return_Flag=InF_ReadFRAM(V_E2Addr,&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));     /*�������1��*/
		V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));
		if( (C_OK != V_ReCRC)||(C_OK != V_Return_Flag) )
		{
			V_Return_Flag=InF_ReadFRAM((V_E2Addr+FRAM_BackUp2_Space),&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));     /*�������2��*/
			V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

			if( (C_OK != V_ReCRC)||(C_OK != V_Return_Flag) )
			{
				V_Return_Flag=InF_ReadFRAM((V_E2Addr+FRAM_BackUp3_Space),&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));     /*�������3��*/
				V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));
			}
			else
			{
				;
			}
		}
		else
		{
			;
		}
		PF_CopyDataBytes(&PV_Data[0],P_Data,V_DataLen);
	}
	else
	{
		;
	}

	if(C_OK!=V_Return_Flag)
	{
		return  V_Return_Flag;		/*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;		/*���ܷ���C_CrcErr_DataZero*/
		}
		else
		{
			return C_OK;
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_ReadE2Three_AndCRC(ushort16 V_E2Addr, uchar8 V_DataLen, uchar8 *P_Data)
������������E2��������,����CRC
���������
		ushort16V_E2Addr��������E2��ַ��
		uchar8V_DataLen�������ݳ��ȣ�������CRC���ȣ�
		uchar8*P_Data�������ݻ��棬����CRC
�����������
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע�������ݲ���ȷ��Ҳ�����������ݡ�ע��ú�����SF_ReadE2Three����
SF_ReadE2Three:�������ݲ�����CRC��SF_ReadE2Three_AndCRC���������ݰ���CRC��
*********************************************************************************/
uchar8 SF_ReadE2Three_AndCRC(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_ReCRC = C_CRCError,V_Return_Flag = C_OtherErr_DAR;

	if((V_DataLen+C_CRCLen2)<=C_RAM_Max)
	{
		V_Return_Flag=InF_ReadE2(V_E2Addr,&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*��E2��1��*/
		V_ReCRC=PF_Check_CRC(&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

		if( (C_OK != V_ReCRC)||(C_OK != V_Return_Flag) )
		{
			V_Return_Flag=InF_ReadE2((V_E2Addr+E2_BackUp2_Space),&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*��E2��2��*/
			V_ReCRC=PF_Check_CRC(&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

			if( (C_OK != V_ReCRC)||(C_OK != V_Return_Flag) )
			{
				V_Return_Flag=InF_ReadE2((V_E2Addr+E2_BackUp3_Space),&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*��E2��3��*/
				V_ReCRC=PF_Check_CRC(&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));
			}
		}
	}

	if(C_OK!=V_Return_Flag)
	{
		return  V_Return_Flag;		/*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;
		}
		else
		{
			return C_OK;
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_ReadE2Three(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
������������E2��������,�ڲ��ж�CRC
���������
		ushort16 V_E2Addr��������E2��ַ��
		uchar8 V_DataLen�������ݳ���
		uchar8 *P_Data�������ݻ���(������CRC)
�����������
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע�������ݲ���ȷ��Ҳ������������
*********************************************************************************/
uchar8 SF_ReadE2Three(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
{
	uchar8 PV_Data[C_RAM_Max];
	uchar8 V_ReCRC,V_Return_Flag = C_Error;

	if((V_DataLen+C_CRCLen2)<=C_RAM_Max)
	{
		V_Return_Flag=InF_ReadE2(V_E2Addr,&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*��E2��1��*/

		V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

		if(C_CRCError==V_ReCRC)
		{
			V_Return_Flag=InF_ReadE2(V_E2Addr+E2_BackUp2_Space,&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*��E2��2��*/

			V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

			if(C_CRCError==V_ReCRC)
			{
				V_Return_Flag=InF_ReadE2(V_E2Addr+E2_BackUp3_Space,&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*��E2��3��*/

				V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));
			}
		}

		PF_CopyDataBytes(&PV_Data[0],P_Data,V_DataLen);
	}

	if(C_OK!=V_Return_Flag)
	{
		return  V_Return_Flag;		/*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;		/*���ܷ���C_CrcErr_DataZero*/
		}
		else
		{
			return C_OK;
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�ushort16 SF_GetOffAddr(Str_4Table *PStr_4TableAddr,ulong32 V_Data_Id,uchar8 V_Type,uchar8 V_4Table_Len)
��������������4����ȡƫ�Ƶ�ַ
���������
		Str_4Table*PStr_4TableAddr��4�����ַ��
		ulong32V_Data_Id�����ݱ�ʶ��4������
		uchar8V_Type:���ݴ洢����
		uchar8V_4Table_Len:4����ṹ�����ݳ���
�����������
���ز�����ushort16��ƫ�Ƶ�ַ����ƫ�Ƶ�ַΪ0xFFFFʱ������Ҵ������debug����������ã�
����˵����
���û��ƣ�
��     ע���ڲ����ݲ�ͬ���ݴ洢���ͣ���4����
*********************************************************************************/
ushort16 SF_GetOffAddr(Str_4Table *PStr_4TableAddr,ulong32 V_Data_Id,uchar8 V_Type,uchar8 V_4Table_Len)
{
	uchar8 V_i;
	uchar8 V_DI[4];
	ushort16 V_OffLen;

	V_OffLen=0xFFFF;
	PF_Ulong32ToBuffer4(&V_DI[0],&V_Data_Id,4);

	switch(V_Type)
	{
		case DT_Flash_DI04:		/*��Flash�����������ݣ�DI0��4λ��ʾ��������4λ��ʾ��ͬ��ʶ��(��ѯ4������)*/
		{
			for(V_i=0;V_i<V_4Table_Len;V_i++)
			{
				if((V_DI[0]&0xF0)==(PStr_4TableAddr[V_i].V_DI&0xF0))		/*�Ƚϸ�4λ*/
				{
					break;
				}
			}
		}break;

		case DT_Flash_Tol_DI0_DI1:		/*��Flash�����������ݣ�����DI0��ʾ������DI1��ʾ�����ʶ��(��ѯ4������)*/
		{
			for(V_i=0;V_i<V_4Table_Len;V_i++)
			{
				if(V_DI[1]==PStr_4TableAddr[V_i].V_DI)		/*�Ƚ�DI1*/
				{
					break;
				}
			}
		}break;
#if 0
		case DT_Flash_Tol_DI0_DI2:				/*11�� Flash�����������ݣ�����DI0��ʾ������DI2��ʾ�����ʶ��(��ѯ4�����ã���Ҫ�ǵ�����������ABC��������)*/
		case DT_Flash_Tol_DI0_W_Sett_En:		/*14��Flash�����������ݣ�����DI0��ʾ����������ģ��д����ʱһ��д���ݲ㣬���ݲ��ڲ������������������ʱ��ֿ��洢���ñ�ʶ��ֻ֧��д*/
		case DT_R_Flash_Tol_DI0_DI2_En:			/*25�� Flash�����������ݣ�����DI0��ʾ������DI2��ʾ�����ʶ��(��ѯ4�����ã�������ABC�������ݶ�)��*/
												/*ͬʱ���ݳ��ȼ��������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��*/
		{
			for(V_i=0;V_i<V_4Table_Len;V_i++)
			{
				if(V_DI[2]==PStr_4TableAddr[V_i].V_DI)		/*�Ƚ�DI2*/
				{
					break;
				}
			}
		}break;
#endif
		case DT_Flash_Tol_DI0_DI1Max:		/*27�� Flash�����������ݣ�����DI0��ʾ�������б�2����ʱֻ����1��DI1���ֵ(�����ò���4����ķ�ʽ)���ڲ�������DI��DI���ݴ��ƫ�Ƶ�ַʱ��*/
											/*OffsetAddr������ü��㷽ʽ����,Ŀǰֻ��У���¼���ø÷�ʽ,������ʱ��DI1=0��*/
		{
			if(0x00==V_DI[1])		/*����������*/
			{
				return 0xFFFF;
			}
			else
			{
				V_OffLen=(V_DI[1]-1)*CLRec_Meter_Bef1_Data_254+6;		/*У�����ݣ�����ƫ�Ƶ�ַ*/
				return  V_OffLen;
			}
		}break;

		default:
			return 0xFFFF;		/*���Ҵ���*/
	}

	if(V_i<V_4Table_Len)
	{
		return PStr_4TableAddr[V_i].V_OffAddr;
	}
	else
	{
		return 0xFFFF;
	}
}

/*********************************************************************************
����ԭ�ͣ�void SF_GetFlashAddr(ulong32 V_NumE2,ulong32 V_StartFlashAddr��ushort16 V_NoteDataLength,
								ulong32 V_EndFlashAddr,ulong32 *P_ReturnFlashAddr)
�������������㵱ǰ���ݱ���ҳ��ַ��ҳ�ڵ�ַ
���������
		ulong32 V_NumE2�����ݴ洢�ܴ�����hex��ʽ��
		ulong32 V_StartFlashAddr�����ݴ洢�����׵�ַ��
		ushort16 V_NoteDataLength��������¼�������ݳ���(�Ƿ������ݳ���)��
		ulong32 V_EndFlashAddr�����ݴ�Ž���ҳ��ַ��
���������
		ulong32 *P_ReturnFlashAddr:���ڴ�ŷ���ҳ��ַ��ҳ�ڵ�ַ��P_ReturnFlashAddr[0]:ҳ��ַ��P_ReturnFlashAddr[1]:ҳ�ڵ�ַ��
���ز�������
����˵����
���û��ƣ�
��     ע���ڲ��жϴ����Ƿ�Ϊ�㣬������������£�����Ϊ��
*********************************************************************************/
void SF_GetFlashAddr(ulong32 V_NumE2,ulong32 V_StartFlashAddr,ushort16 V_NoteDataLength,ulong32 V_EndFlashAddr,ulong32 *P_ReturnFlashAddr)
{
	ushort16 V_Page_Agree;
	ulong32 V_Flash_Page;
	uchar8 V_Flash_PageNum;

	P_ReturnFlashAddr[0]=0xFFFFFFFF;
	P_ReturnFlashAddr[1]=0xFFFFFFFF;

	if(0==V_NoteDataLength)
	{
		return;		/*����������*/
	}

	V_Page_Agree=(ushort16)(C_OneFlash_PageNum/V_NoteDataLength);  /*ÿҳ�ɼ�¼���ݴ���*/
	V_Flash_Page=V_EndFlashAddr-V_StartFlashAddr;                  /*�ü�¼Flash�洢ҳ����-1*/
	V_Flash_PageNum=(uchar8)(V_Flash_Page/C_OneFlashPage)+1;       /*�ü�¼Flash�洢ҳ����,C_OneFlashPage:0x00001000*/
	if(0==V_NumE2)
	{
		return;
	}

	P_ReturnFlashAddr[0]=(((V_NumE2-1)/V_Page_Agree)%V_Flash_PageNum)*C_OneFlashPage+V_StartFlashAddr;
	P_ReturnFlashAddr[1]=((V_NumE2-1)%V_Page_Agree)*V_NoteDataLength;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WriteFlash(ulong32 V_FlashAddr,uchar8 *P_Data,ushort16 V_Data_Length)
����������дFlash�������,��д���ַΪÿҳ�׵�ַʱ�������ж���д��Flash���Ƿ�Ϊ��(00)���粻Ϊ�գ���������д�롣����ҳΪ��ʱ��
���4���ֽ�дΪFF(���ڸ�Flash�Ƿ�Ϊ���жϣ���Flash�����ײ��������ӣ�д����ʱ���Ȱ�Ҫд�����ݰ�λȡ����Ȼ��дFlash)
���������
		ulong32 V_FlashAddr��д������Flash��ַ��
		uchar8 *P_Data��д�����ݻ��棻
		ushort16 V_Data_Length��д�����ݳ��ȣ�
		uchar8 V_EvenSign��дFlash����ʱ���Ƿ���Ҫ�жϿ�ҳ����Ҫ��д�¼���¼�������ݣ�����Ҫ�жϿ�ҳ��2������Ҫ�жϿ�ҳ��Ϊ�ղ����жϣ�
							1����Ҫ�жϿ�ҳ��Flash�Ƿ�Ϊ���жϣ�
����������ޣ�
���ز�����C_OK��C_SPIError
����˵����
���û��ƣ�
��     ע��ע��Flash�ײ����ݣ�Ϊȡ�������ݣ�0��1�෴.�ڲ��жϰ�ȫ��־
*********************************************************************************/
uchar8 SF_WriteFlash(ulong32 V_FlashAddr,uchar8 *P_Data,ushort16 V_Data_Length,uchar8 V_EvenSign)
{
	uchar8 V_FlashZero[C_Flash_EmptyNum],V_i;
	ulong32 V_Flash_Page;
	ulong32 V_Flash_PageEmptyAddr;
	uchar8 V_j;
	uchar8 V_Return_Flag;

	V_FlashZero[3]=0x55;           /*��������*/
	V_Flash_Page=0x55;
	V_j=4;/*���Flash�Ƿ�Ϊ��4�Σ���4�β��ܲ����ɹ������˳�����C_SPIError����*/

	V_Flash_Page=V_FlashAddr%C_OneFlashPage;   /*�ж�д������Flash��ַ�Ƿ�Ϊÿҳ�׵�ַ*/
	if((0==V_Flash_Page)&&(V_EvenSign!=2))  /*���ж������Ƿ�Ϊ��.698д�����¼���¼ʱ����֯�������ݣ��ѷ�������ȫ������ķ�ʽ,�ײ�дFFû��Ӱ�죬�¼���¼����һ��д���ݲ�(��������������)��*/
	{																				/*�¼���¼ģ����д��������д������д������־V_EvenSign����Ϊ1��д��������Ϊ2������д��������ʱ�����ж������Ƿ�Ϊ�գ�������д����ʱ���Ѿ��жϹ���*/
		while(V_j--)
		{
			V_Flash_PageEmptyAddr=V_FlashAddr+C_OneFlashPage-C_Flash_EmptyNum;    /*���4���ֽ�Flash��ַ*/
			InF_FlashChipSelect();
			InF_ReadFlash(V_Flash_PageEmptyAddr,&V_FlashZero[0],C_Flash_EmptyNum);

			for(V_i=0;V_i<C_Flash_EmptyNum;V_i++)  /*�ж�Flashҳ�Ƿ�Ϊ��,��������Ϊȫ0����Ϊ��(ע��Flash�����ײ㷴)*/
			{
				if(C_Flash_Empty68!=V_FlashZero[V_i])
				{
					break;
				}
			}

			if(V_i<C_Flash_EmptyNum)       /*��ǰҳFlash��Ϊ�գ�����д68Ϊ�ձ�־*/
			{
				V_Return_Flag=SF_EraseFlashAndWriteEmptySign(V_FlashAddr);
				if(C_OK!=V_Return_Flag)
				{
					GV_D_SafeFlag=C_Clear_SafeFlag;
					return V_Return_Flag;
				}
			}
			else/*��ǰҳΪ��*/
			{
				break;
			}
		}

		if(0==V_j)/*4��Flash������ʧ��,����ʧ�ܲ���*/
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SPIError;
		}
	}

	InF_FlashChipSelect();

	if(C_W_SafeFlag!=GV_D_SafeFlag)  /*��ȫ��־��*/
	{
		InF_FlashChipDeselect();            /*�ر�CS*/
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}

	InF_WriteFlash(V_FlashAddr,P_Data,V_Data_Length);

	V_FlashAddr=V_FlashAddr&0xFFFFF000;
	V_Flash_PageEmptyAddr=V_FlashAddr+C_OneFlashPage-C_Flash_EmptyNum;    /*���4���ֽ�Flash��ַ*/
	InF_FlashChipSelect();
	InF_ReadFlash(V_Flash_PageEmptyAddr,&V_FlashZero[0],C_Flash_EmptyNum);

	for(V_i=0;V_i<C_Flash_EmptyNum;V_i++)  /*�ж�4���ֽ��Ƿ�Ϊ��Ϊ�ձ�־*/
	{
		if(C_Flash_NoEmpty!=V_FlashZero[V_i])
		{
			break;
		}
	}

	if(V_i<C_Flash_EmptyNum)       /*��ǰҳFlash��Ϊ�ձ�־��û����*/
	{
		for(V_i=0;V_i<C_Flash_EmptyNum;V_i++)
		{
			V_FlashZero[V_i]=C_Flash_NoEmpty;     /*дFlash��Ϊ�����ݣ�0xFF*/
		}

		InF_FlashChipSelect();
		if(C_W_SafeFlag!=GV_D_SafeFlag)  /*��ȫ��־��*/
		{
			InF_FlashChipDeselect();            /*�ر�CS*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteFlash(V_Flash_PageEmptyAddr,&V_FlashZero[0],C_Flash_EmptyNum);
	}

	return C_OK;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WR_FRAM1CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
����������д����1������,��CRC
���������
		ushort16V_E2Addr��д�����������ַ��
		ushort16V_DataLen��Ҫд�����ݳ���
		uchar8*P_Data��Ҫд�����ݻ���
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_WR_FRAM1CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_i;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 PV_RData[C_RAM_Max];  /*���ڶ��Ƚ�*/
	uchar8 V_Return_Flag;
	uchar8 V_Len,P_CRC[C_CRCLen2];
	ushort16 V_CRC16;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag; /*�ð�ȫ��־*/

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	V_Len=(uchar8)V_DataLen;
	PF_CopyDataBytes(P_Data,&PV_Data[0],V_Len);
	V_CRC16=PF_Cal_CRC(&PV_Data[0],V_Len);          /*����CRC*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag; /*�ð�ȫ��־*/

	PV_Data[V_Len]=P_CRC[0];
	PV_Data[V_Len+1]=P_CRC[1];

	V_Len=(uchar8)V_DataLen+C_CRCLen2;

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	InF_FRAMWPEnable();

	if(C_W_SafeFlag!=GV_D_SafeFlag)  /*��ȫ��־��*/
	{
		InF_FRAMWPDisable();            /*�ر�WP*/
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}

	V_Return_Flag=InF_WriteFRAM(V_E2Addr,&PV_Data[0],(ushort16)V_Len);

	InF_ReadFRAM(V_E2Addr,&PV_RData[0],(ushort16)V_Len);

	for(V_i=0;V_i<V_Len;V_i++)                      /*���Ƚ�*/
	{
		if(*(PV_Data+V_i)!=*(PV_RData+V_i))
		{
			break;
		}
	}

	if(V_i!=V_Len)                                 /*дE2����*/
	{
		InF_FRAMWPEnable();                                    /*����E2 WP*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)  /*��ȫ��־��*/
		{
			InF_FRAMWPDisable();            /*�ر�WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		V_Return_Flag=InF_WriteFRAM(V_E2Addr,&PV_Data[0],(ushort16)V_Len);
	}

	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WR_E21CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
����������дE21������,��CRC
���������
		ushort16 V_E2Addr��д������E2��ַ��
		ushort16 V_DataLen��Ҫд�����ݳ���
		uchar8 *P_Data��Ҫд�����ݻ���
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��
����˵����
���û��ƣ�
��ע��
*********************************************************************************/
uchar8 SF_WR_E21CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_i;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 PV_RData[C_RAM_Max];  /*���ڶ��Ƚ�*/
	uchar8 V_Return_Flag;
	uchar8 V_Len,P_CRC[C_CRCLen2];
	ushort16 V_CRC16;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag; /*�ð�ȫ��־*/

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	V_Len=(uchar8)V_DataLen;
	PF_CopyDataBytes(P_Data,&PV_Data[0],V_Len);
	V_CRC16=PF_Cal_CRC(&PV_Data[0],V_Len);          /*����CRC*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag; /*�ð�ȫ��־*/

	PV_Data[V_Len]=P_CRC[0];
	PV_Data[V_Len+1]=P_CRC[1];

	V_Len=(uchar8)V_DataLen+C_CRCLen2;

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	InF_E2WPEnable();

	if(C_W_SafeFlag!=GV_D_SafeFlag)  /*��ȫ��־��*/
	{
		InF_E2WPDisable();            /*�ر�WP*/
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}

	V_Return_Flag=InF_WriteE2(V_E2Addr,&PV_Data[0],(ushort16)V_Len);

	InF_ReadE2(V_E2Addr,&PV_RData[0],(ushort16)V_Len);

	for(V_i=0;V_i<V_Len;V_i++)                      /*���Ƚ�*/
	{
		if(*(PV_Data+V_i)!=*(PV_RData+V_i))
		{
			break;
		}
	}

	if(V_i!=V_Len)                                 /*дE2����*/
	{
		InF_E2WPEnable();                                    /*����E2 WP*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)  /*��ȫ��־��*/
		{
			InF_E2WPDisable();            /*�ر�WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		V_Return_Flag=InF_WriteE2(V_E2Addr,&PV_Data[0],(ushort16)V_Len);
	}

	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WR_E21_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
����������дE21������
���������
		ushort16 V_E2Addr��д������E2��ַ��
		ushort16 V_DataLen��Ҫд�����ݳ���
		uchar8 *P_Data��Ҫд�����ݻ���
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_WR_E21_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_Return_Flag;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag; /*�ð�ȫ��־*/
	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag; /*�ð�ȫ��־*/

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;	                                    /*����E2 WP*/
	}

	InF_E2WPEnable();

	if(C_W_SafeFlag!=GV_D_SafeFlag)  /*��ȫ��־��*/
	{
		InF_E2WPDisable();            /*�ر�WP*/
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}

	V_Return_Flag=InF_WriteE2(V_E2Addr,P_Data,V_DataLen);

	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WR_RAM_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 Msg_Num)
����������дRAM���ݣ�����CRC
���������
		uchar8 *P_RamAddr��д������RAM��ַ��
		ushort16 V_DataLen��Ҫд�����ݳ���
		uchar8 *P_Data��Ҫд�����ݻ���
		uchar8 V_DT_Type��Ҫд���������ͣ������ж��Ƿ�дʱ�䣬��ʱ��д�ӿں���
�����������
���ز�����C_OK��C_SafeFlagError��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_WR_RAM_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 Msg_Num)
{
	ushort16 V_i;
	uchar8 V_Return_Flag, V_Temp[CLDate_Week_Time] = {0};

	V_Return_Flag=C_OK;

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag; /*�ð�ȫ��־*/

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	for(V_i=0;V_i<V_DataLen;V_i++)
	{
		*(P_RamAddr+V_i)=*(P_Data+V_i);
	}

	if(DT_RAM_Time_Data==V_DT_Type)
	{
		if(C_Msg_Communication==Msg_Num)  /*ֻ��ͨ��дʱ�䣬��ˢ��Ӳ��RTC*/
		{
			/*������ʱ��Data_Time_sת��ΪYYMMDDWWHHMMSS*/
			PF_Data_Time_s_HEXtoData_Week_Time_BCD(P_Data, &V_Temp[0]);
			V_Return_Flag=InF_WriteRTC(&V_Temp[0],CLDate_Week_Time);
		}
	}

	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_WR_RAMCRC_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data)
����������дRAM���ݣ��ڲ�����CRC
���������
		uchar8*P_RamAddr����������RAM��ַ��
		ushort16V_DataLen��Ҫд�����ݳ��ȣ�������CRC����
		uchar8*P_Data��д�����ݻ���
�����������
���ز�����C_OK��C_SafeFlagError��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_WR_RAMCRC_Data(uchar8 * P_RamAddr,ushort16 V_DataLen,uchar8 * P_Data)
{
	ushort16 V_i,V_CRC16;
	uchar8 P_CRC[C_CRCLen2];

	V_CRC16=PF_Cal_CRC(P_Data,V_DataLen);          /*����CRC*/
	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;      /*�ð�ȫ��־*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	for(V_i=0;V_i<V_DataLen;V_i++)
	{
		*(P_RamAddr+V_i)=*(P_Data+V_i);
	}

	*(P_RamAddr+V_DataLen)=P_CRC[0];
	*(P_RamAddr+V_DataLen+1)=P_CRC[1];

	return C_OK;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 InF_Read_RecMeterData(uchar8 V_Data_Num,uchar8 *P_Data,uchar8 *P_Data_Length)
���������������ݲ�У������ӿں���
���������
		uchar8 V_Data_Num����У��������ţ���У�����ݴ�W2��ַƫ��һһ��Ӧ�����ݲ��ڲ��ж����ֵ����ų�����C_NoAccess
		uchar8 *P_Data���������Ż��棻
		uchar8 *P_Data_Length����Ϊ�������ʱ���ò���ֵΪģ���������ݻ��泤�����ֵ���������ݲ��жϣ��������ݳ��ȣ�
		�Ƿ������������򷵻����ݳ��ȴ��󡣵���Ϊ�������ʱ�����ݲ㷵������ȡ���ݳ��ȡ�
���������
		uchar8 *P_Data_Length�����ݲ㷵������ȡ���ݳ��ȡ�
���ز�����C_OK��C_IICError��C_DataLenError��C_NoAccess��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע��ע�����ݳ��ȣ�
*********************************************************************************/
uchar8 InF_Read_RecMeterData(uchar8 V_Data_Num,uchar8 *P_Data,uchar8 *P_Data_Length)
{
	ushort16 V_3TableE2Addr;
	uchar8 V_Return_Flag;

	if(C_MeterICE2ResLen>(*P_Data_Length))               /*�����ݳ���*/
	{
		return C_DataLenError;
	}
	else
	{
		*P_Data_Length=C_MeterICE2ResLen;
	}

	if(V_Data_Num>=C_MeterICDataNum_T)
	{
		return C_NoAccess;
	}

	V_3TableE2Addr=E2Addr_MeterIC_St+V_Data_Num*(C_MeterICE2ResLen+C_CRCLen2);   /*Ҫ����E2��ַ*/
	if(V_3TableE2Addr>(E2Addr_MeterIC_End-C_MeterICE2ResLen-C_CRCLen2))         /*E2��ַ����*/
	{
		return C_DataLenError;
	}

	V_Return_Flag=SF_ReadE2Three(V_3TableE2Addr,C_MeterICE2ResLen,P_Data);   /*��E2����*/
	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Read_E21CRC_Data698(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
������������E21�����ݣ�
���������
ushort16 V_E2Addr��������E2��ַ��
ushort16 V_DataLen�������ݳ���
���������
uchar8 *P_Data�������ݻ���
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע��ֱ�ӽ������뻺��
*********************************************************************************/
uchar8 SF_Read_E21CRC_Data698(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data)
{
	uchar8 V_Return_Flag;
	uchar8 V_ReCRC;

	V_Return_Flag=InF_ReadE2(V_E2Addr,&P_Data[0],(V_DataLen+C_CRCLen2));
	V_ReCRC=PF_Check_CRC(&P_Data[0],(V_DataLen+C_CRCLen2));

	if(C_OK!=V_Return_Flag)
	{
		return  V_Return_Flag;    /*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;      /*���ܷ���C_CrcErr_DataZero*/
		}
		else
		{
			return C_OK;
		}
	}
}

/*********************************************************************************
����ԭ�ͣ�uchar8 InF_ReadOADTab_Data(ulong32 V_Data_Id,uchar8 *P_Data,ushort16 *P_Data_Length)
���������������ݲ�OAD��ű�(�������ᡢ�¼���¼)������������Ϊ��������б����ݳ��ȿ��ܴ���255��ͨ�ö�������ݳ���Ϊ255
���������
ulong32 V_Data_Id�����ݱ�ʶ�룻
uchar8 *P_Data���������Ż��棻
ushort16 *P_Data_Length����Ϊ�������ʱ�������ݻ����С
���������ushort16 *P_Data_Length�����ݲ㷵������ȡ����ʵ�ʳ��ȡ�
���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_NoAccess��C_CRCError��C_CrcErr_DataZero��
����˵�������Ӷ���ȫģʽ��������3��
���û��ƣ�
��     ע���������б�ʱ�����ݲ��ڲ����ݸù����б��Ӧ��OAD�������Լ������ȡ�Ĺ����б��ȣ�Ϊ����ԭ�����򣬶��������OAD���ǲ��ö��̶��������ݳ��ȣ�
*********************************************************************************/
uchar8 InF_ReadOADTab_Data(ulong32 V_Data_Id,uchar8 *P_Data,ushort16 *P_Data_Length)
{
	uchar8 V_Return_Flag,V_DI[4];
	ulong32 V_DI32;
	Str_3aTable V_Str_3aTable;
	ushort16 V_Data_Length, V_usDataEncode;

	if((*P_Data_Length)==0)/*û�й����б�Ҳ���ܻ��*/
	{
		return C_OK;
	}

	if((CI_Free_OADTab&0xFFFFFF00)==(V_Data_Id&0xFFFFFF00))/*��������ű�*/
	{
		if((*P_Data_Length)>C_698Free_OADTabLen)/*����������*/
		{
			return C_DataLenError;
		}

		V_DI32=V_Data_Id;
		PF_Ulong32ToBuffer4(&V_DI[0],&V_DI32,4);

		if(V_DI[0]==0)
		{
			return C_IDError;
		}

		V_DI[1]=V_DI[0]-1;
		V_DI[1]+=233;			/*233,Str_3aTable_E23RAM����ж�����I_Free_OADTab  ��ʼƫ��*/
		V_Str_3aTable=Str_3aTable_E23RAM[V_DI[1]];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,*P_Data_Length,P_Data);
	}
	else
	{
		if((CSafeModeParaNat3&0xFFFFFF00)==(V_Data_Id&0xFFFFFF00))/*����ȫģʽ����,����3*/
		{
			V_Return_Flag=SF_Read_E21CRC_Data698(E2Addr_SafeModeParaNat3,*P_Data_Length,P_Data);
		}
		else/*�����������б�,����ͨ�ö�*/
		{
			if(*P_Data_Length>255)
			{
				V_Data_Length=255;
			}
			else
			{
				V_Data_Length=*P_Data_Length;
			}

			V_Return_Flag = InF_Read_Data(V_Data_Id, P_Data, &V_Data_Length, &V_usDataEncode);
			*P_Data_Length = V_Data_Length;
		}
	}

	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_ReadCurrentTab_Data(ulong32 V_Data_Id,uchar8 *P_Data,uchar8 *P_Data_Length)
���������������ݲ��¼���ǰ��¼��
���������
		ulong32 V_Data_Id�����ݱ�ʶ�룻
		uchar8 *P_Data ���������Ż��棻
		uchar8 *P_Data_Length����Ϊ�������ʱ���ò���ֵΪģ���������ݻ��泤�����ֵ���������ݲ��жϣ��������ݳ��ȣ�
		�Ƿ������������򷵻����ݳ��ȴ��󡣵���Ϊ�������ʱ�����ݲ㷵������ȡ���ݳ��ȡ�
���������uchar8 *P_Data_Length�����ݲ㷵������ȡ���ݳ��ȡ�
���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_NoAccess��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע���ò�����Ҫ��û���ۼ�ʱ����¼���¼�����ۼ�ʱ��ļ�¼��ֱ�Ӷ��¼���¼ģ��
*********************************************************************************/
uchar8 SF_ReadCurrentTab_Data(ulong32 V_Data_Id, uchar8 *P_Data, ushort16 *P_Data_Length)
{
	uchar8 V_Return_Flag,V_Source[4],V_Line;
	ulong32 V_Gree,P_FlashAddr1[2];
	ushort16 V_DataLen;

	V_Return_Flag=C_OK;

	switch(V_Data_Id)
	{
		case CProgReC_Current:     /*����޹���̼�¼ �����⴦����Դ*/
		{
			V_Return_Flag=SF_ReadE2Three(E2Addr_ProgReC1_Degree,CLProgReC_Degree,&V_Source[0]);
			PF_Buffer4ToUlong32(&V_Source[0],&V_Gree,CLProgReC_Degree);
			if((C_OK==V_Return_Flag)&&(V_Gree>0))
			{
				V_DataLen=SF_GetEventDataLen(E2Addr_ProgReC_OADTab,E2Addr_ProgReC_OADTabLen,((ulong32)&Str_4aTable_AllLossVol[0]),Str_4aTable_AllLossVol_Len);
				if((0==V_DataLen)||(0xFFFF==V_DataLen))
				{
					V_Return_Flag=C_DataLenError;
				}
				else
				{
					SF_GetFlashAddr(V_Gree,FlashStAddr_ProgReC1,V_DataLen,FlashEndAddr_ProgReC1,&P_FlashAddr1[0]);   /*��ȡ��1�ε�ǰ����Flashҳ��ַ��ҳ�ڵ�ַ*/
					P_FlashAddr1[0]+=P_FlashAddr1[1];
					if(P_FlashAddr1[0]<C_Flash_Max_Addr)
					{
						InF_FlashChipSelect();
						InF_ReadFlash((P_FlashAddr1[0]+CLEventNum+CLEventHPTime+CLEventEndTime),&V_Source[0],CLProgReC_Source);    /*����¼����Դ*/
					}
				}
			}

			switch(V_Data_Id&0x000000FF)
			{
				case 0:/*���ϼ�¼*/
				{
					if(* P_Data_Length<CLProgReC_Current)
					{
						V_Return_Flag=C_DataLenError;
					}
					else
					{
						*P_Data_Length=CLProgReC_Current;

						for(V_Line=0;V_Line<CLProgReC_Source;V_Line++)/*����Դ*/
						{
							P_Data[V_Line]=V_Source[V_Line];
						}

						V_Line=CLProgReC_Degree;
						PF_HextoBCDBytes(&V_Gree,&P_Data[CLProgReC_Source],&V_Line);
						memset(&P_Data[CLProgReC_Degree+CLProgReC_Source], C_NotSupportAOD_Data, (CLProgReC - CLProgReC_Degree));
					}
				}break;

				case 1:/*����Դ*/
				{
					if(* P_Data_Length<CLProgReC_Source)
					{
						V_Return_Flag=C_DataLenError;
					}
					else
					{
						*P_Data_Length=CLProgReC_Source;

						for(V_Line=0;V_Line<CLProgReC_Source;V_Line++)
						{
							P_Data[V_Line]=V_Source[V_Line];
						}

						V_Return_Flag=C_OK;
					}
				}break;

				case 2:/*�����������ۼ�ʱ��*/
				{
					if(* P_Data_Length<CLProgReC)
					{
						V_Return_Flag=C_DataLenError;
					}
					else
					{
						*P_Data_Length=CLProgReC;
						V_Line=CLProgReC_Degree;
						PF_HextoBCDBytes(&V_Gree,P_Data,&V_Line);

						for(V_Line=0;V_Line<(CLProgReC-CLProgReC_Degree);V_Line++)
						{
							P_Data[CLProgReC_Degree+V_Line]=C_NotSupportAOD_Data;
						}
					}
				}break;

				default:
				{
					V_Return_Flag=C_AbnormalError;
				}break;
			}
		}break;

		default:/*����Դͨ�ö�ȡ*/
		{
			for(V_Line=0;V_Line<GCStr_EventCurrentTab_Len;V_Line++)
			{
				if((V_Data_Id&0xFFFFFF00)==(GCStr_EventCurrentTab[V_Line].V_OAD&0xFFFFFF00))
				{
					break;
				}
			}

			if(V_Line>=GCStr_EventCurrentTab_Len)
			{
				V_Return_Flag=C_IDError;
			}
			else
			{
				switch(V_Data_Id&0x000000FF)
				{
					case 0:/*���ϼ�¼*/
					{
						if(* P_Data_Length<CLTol_Clear_Current)
						{
							V_Return_Flag=C_DataLenError;
						}
						else
						{
							*P_Data_Length=CLTol_Clear_Current;

							for(V_Line=0;V_Line<CLTol_Clear_Source;V_Line++)
							{
								P_Data[V_Line]=C_NotSupportAOD_Data;/*����ԴҲΪ��*/
							}

							V_Return_Flag=SF_ReadE2Three(GCStr_EventCurrentTab[V_Line].V_Num_E2BakeUp1Addr,CLTol_Clear_Degree,&P_Data[CLTol_Clear_Source]);
							PF_Buffer4ToUlong32(&P_Data[CLTol_Clear_Source],&V_Gree,CLTol_Clear_Degree);

							V_Line=CLTol_Clear_Degree;
							PF_HextoBCDBytes(&V_Gree,&P_Data[CLTol_Clear_Source],&V_Line);

							for(V_Line=0;V_Line<(CLTol_Clear-CLTol_Clear_Degree);V_Line++)/*�ۼ�ʱ��*/
							{
								P_Data[CLTol_Clear_Source+CLTol_Clear_Degree+V_Line]=C_NotSupportAOD_Data;
							}
						}
					}break;

					case 1:/*����Դ*/
					{
						if(* P_Data_Length<CLTol_Clear_Source)
						{
							V_Return_Flag=C_DataLenError;
						}
						else
						{
							*P_Data_Length=CLTol_Clear_Source;

							for(V_Line=0;V_Line<CLTol_Clear_Source;V_Line++)
							{
								P_Data[V_Line]=C_NotSupportAOD_Data;
							}

							V_Return_Flag=C_OK;
						}
					}break;

					case 2:/*�����������ۼ�ʱ��*/
					{
						if(* P_Data_Length<CLTol_Clear)
						{
							V_Return_Flag=C_DataLenError;
						}
						else
						{
							*P_Data_Length=CLTol_Clear;
							V_Return_Flag=SF_ReadE2Three(GCStr_EventCurrentTab[V_Line].V_Num_E2BakeUp1Addr,CLTol_Clear_Degree,P_Data);
							PF_Buffer4ToUlong32(P_Data,&V_Gree,CLTol_Clear_Degree);

							V_Line=CLTol_Clear_Degree;
							PF_HextoBCDBytes(&V_Gree,P_Data,&V_Line);

							for(V_Line=0;V_Line<(CLTol_Clear-CLTol_Clear_Degree);V_Line++)
							{
								P_Data[CLTol_Clear_Degree+V_Line]=C_NotSupportAOD_Data;
							}
						}
					}break;

					default:
					{
						V_Return_Flag=C_AbnormalError;
					}break;
				}
			}
		}break;
	}
	return V_Return_Flag;
}


/*********************************************************************************
����ԭ�ͣ�uchar8 InF_Read_Data(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode)
���������������ݲ�ӿں���,�ú���ֻ��һ����ñ�ӡ���ʵ��Ϊuchar8SF_Read_Data
���������
		ulong32 V_ulData_Id�� ���ݱ�ʶ��
		uchar8 *pV_ucData���������Ż��棻
		uchar8 *pV_usData_Length����Ϊ�������ʱ���ò���ֵΪģ���������ݻ��泤�����ֵ���������ݲ��жϣ��������ݳ��ȣ�
		�Ƿ������������򷵻����ݳ��ȴ��󡣵���Ϊ�������ʱ�����ݲ㷵������ȡ���ݳ��ȡ�
���������uchar8 *pV_usData_Length�����ݲ㷵������ȡ���ݳ��ȣ���ȡ�������������ݳ��ȷ���0
		*pV_ucDataΪ���ݲ��ȡ�������ݣ������ݶ�ȡ����������
���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_NoAccess��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע��ע�����ݳ��ȣ�ͨ�ö����ݽӿں��������ݳ���ΪĬ��645���ȣ��������6+2�����6+4��ΪInF_Read_Data_For_Dis�ӿں���
*********************************************************************************/
uchar8 InF_Read_Data(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode)
{
	uchar8 V_Return_Flag;
	uchar8 V_MesNum;

	if(SF_Read_698SpecialData(V_ulData_Id, pV_ucData, pV_usData_Length, pV_usDataEncode) == C_OK)
	{
		return C_OK;
	}

	V_MesNum = C_Read_Data;
	V_Return_Flag = SF_Read_Data(V_ulData_Id, pV_ucData, pV_usData_Length, V_MesNum, pV_usDataEncode);

	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Read_698SpecialData(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode)
���������������ݲ�ӿں���,�ú���Ϊͨ�ö�����ʾ������ͬ���á�����ʾ�����ݲ㼰ͨ�ö����ݲ㣬Ϊ�ú������˸���ñ�ӡ�
���������
		ulong32 V_ulData_Id �����ݱ�ʶ�룻
		uchar8 *pV_ucData ���������Ż��棻
		uchar8 *pV_usData_Length ����Ϊ�������ʱ���ò���ֵΪģ���������ݻ��泤�����ֵ���������ݲ��жϣ��������ݳ��ȣ�
		�Ƿ������������򷵻����ݳ��ȴ��󡣵���Ϊ�������ʱ�����ݲ㷵������ȡ���ݳ��ȡ�
���������ushort16*P_Data_Length�����ݲ㷵������ȡ���ݳ��ȡ�
���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_NoAccess��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע��ע�����ݳ���.698�ֱ�ʶ���������ݶ�ȡ��
*********************************************************************************/
uchar8 SF_Read_698SpecialData(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode)
{
	uchar8 V_Dataoff, V_Return_Flag, V_MesNum = C_Read_Data;
	uchar8 V_DataBuff[60] = {0};
	ushort16 V_usLen = sizeof(V_DataBuff);
	ushort16 V_usCRC_C, V_usCRC_F;


	V_Dataoff = (uchar8)V_ulData_Id;

	if( ( (V_ulData_Id & 0xFFFFFF00) == CFirst_TZone_Data) || ( (V_ulData_Id & 0xFFFFFF00) == CSec_TZone_Data) )
	{
		if( (V_Dataoff == 0)||(V_Dataoff > 14) )
		{
			return C_IDError;
		}

		if(*pV_usData_Length < 3)
		{
			return C_DataLenError;
		}

		if( (V_ulData_Id & 0xFFFFFF00) == CFirst_TZone_Data)
		{
			V_ulData_Id = CFirst_TZone_Data;
		}
		else
		{
			V_ulData_Id = CSec_TZone_Data;
		}

		V_Return_Flag = SF_Read_Data(V_ulData_Id, V_DataBuff, &V_usLen, V_MesNum, pV_usDataEncode);

		if(V_Return_Flag == C_OK)
		{
			PF_CopyDataBytes( &V_DataBuff[ (V_Dataoff - 1)*3 ], pV_ucData, 3);
			*pV_usData_Length = 3;
		}
	}
	else if( (V_ulData_Id & 0xFFFFFF00) == CMeter_Position)
	{
		if( (V_Dataoff == 0) || ( V_Dataoff > 3 ) )
		{
			return C_IDError;
		}

		if(*pV_usData_Length < 4)
		{
			return C_DataLenError;
		}

		/*V_ulData_Id = CMeter_Position;*/
		V_Return_Flag = SF_Read_Data(CMeter_Position, V_DataBuff, &V_usLen, V_MesNum, pV_usDataEncode);

		if(V_Return_Flag == C_OK)
		{
			PF_CopyDataBytes( &V_DataBuff[ (V_Dataoff - 1) * 4], pV_ucData, 4);
			*pV_usData_Length = 4;
		}
	}
	else if( V_ulData_Id == 0xFF860200)	/*������������ȡ����汾����*/
	{
		V_usCRC_C = PF_Cal_CRC_698( (uchar8 *)C_Software_Featurcode, C_FeaturCode_Len );
		V_usCRC_F = PF_Buffer2ToLong16_698( (uchar8 *)(C_Software_Featurcode + C_FeaturCode_Len) );

		if( V_usCRC_F == V_usCRC_C)
		{
			memcpy(pV_ucData, (uchar8 *)C_EnterBootFlag, C_EnterBootFlag_Len);		/*�������Ϊ�˵���һ�£���C_EnterBootFlag��Ҫ���Ż���*/
			memcpy(pV_ucData, (uchar8 *)C_Software_Featurcode, C_FeaturCode_Len);
			(*pV_usData_Length) = C_FeaturCode_Len;
			V_Return_Flag = C_OK;
		}
		else
		{
			V_Return_Flag = C_Error;
		}
	}
	else
	{
		return C_IDError;
	}

	if(V_Return_Flag != C_OK)
	{
		(*pV_usData_Length) = 0;
	}
	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_JudgeEventAgreeIsYes(uchar8 V_DI0,ushort16 V_E2AgreeAddr)
�����������ж��¼���¼��������DI0���Ƿ���¼���¼Ŀǰ�洢�����������������ܼ�¼�������򷵻�OK�����෵���쳣
���������
		uchar8 V_DI0�����ݱ�ʶ��DI0����������¼������
		ushort16 V_E2AgreeAddr���¼���¼����������E2��ַ��
���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_NoAccess��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_JudgeEventAgreeIsYes(uchar8 V_DI0,ushort16 V_E2AgreeAddr)
{
	uchar8 V_Return_Flag;
	uchar8 P_Dgree[CLAll_Loss_Vol_Degree];
	ulong32 V_Dgree;

	V_Return_Flag=SF_ReadE2Three(V_E2AgreeAddr,CLAll_Loss_Vol_Degree,&P_Dgree[0]);

	if(C_OK!=V_Return_Flag)
	{
		return	V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&P_Dgree[0],&V_Dgree,CLAll_Loss_Vol_Degree);

	if((0==V_DI0)||(V_DI0>V_Dgree))
	{
		return C_NoData;
	}
	else
	{
		return C_OK;
	}
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Read_Data( ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, uchar8 V_MesNum, ushort16 *pV_usDataEncode)
���������������ݲ�ӿں���,�ú���Ϊͨ�ö�����ʾ������ͬ���á�����ʾ�����ݲ㼰ͨ�ö����ݲ㣬Ϊ�ú������˸���ñ�ӡ�
���������
		ulong32  V_ulData_Id �����ݱ�ʶ�룻
		uchar8 *pV_ucData ���������Ż��棻
		uchar8 *pV_usData_Length ����Ϊ�������ʱ���ò���ֵΪģ���������ݻ��泤�����ֵ���������ݲ��жϣ��������ݳ��ȣ�
		�Ƿ������������򷵻����ݳ��ȴ��󡣵���Ϊ�������ʱ�����ݲ㷵������ȡ���ݳ��ȡ�
		uchar8 V_MesNum :��������Ϣ�ţ�����������ͨ�ö���������ʾ������Ϊͨ�ö�ʱ��Ϣ��Ϊ0����ʾ��ʱΪ��ʾNum��
���������ushort16 *pV_usData_Length�����ݲ㷵������ȡ���ݳ��ȡ�
���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_NoAccess��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע��ע�����ݳ���
*********************************************************************************/
uchar8 SF_Read_Data(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, uchar8 V_MesNum, ushort16 *pV_usDataEncode)
{
	uchar8 V_Return_Flag, V_WR_Mes, V_DI[4];
	ushort16 V_Line, V_3TableE2Addr;
	ushort16 V_DataLen;
	Str_2Table *PStr_2TableAddr = NULL;
	Str_3aTable *PStr_3aTableAddr = NULL;
	uchar8 *P_3TableRamAddr = NULL;
	Str_3eTable *PStr_3eTable_2E2 = NULL;

	PF_Ulong32ToBuffer4(&V_DI[0], &V_ulData_Id, 4);
	V_DataLen = (ushort16)(*pV_usData_Length);

	if( (CI_Free_OADTab & 0xFFFFFF00)==(V_ulData_Id & 0xFFFFFF00) )		/*��������ű����ݳ������⡣�ڸò��ֲ�֧�֣������InF_ReadOADTab_Data*/
	{
		(*pV_usData_Length) = 0;
		return C_IDError;
	}
#if _DEBUGFY /*���ٴ�RAM����Ϊʹ�ú궨��,ƴ��ʱȥ��*/
	/****����оƬ�������������ֵ,hex��ʽ��Ŀǰ����ģ����(������),���⴦��****/
	if(CPluse_Most__Lim == V_ulData_Id)
	{
		if( (*pV_usData_Length) < CLPluse_Most__Lim)		/*���ݳ����ж�*/
		{
			(*pV_usData_Length) = 0;
			return C_DataLenError;
		}
		else
		{
			*pV_usData_Length = CLPluse_Most__Lim;
			PF_CopyDataBytes( (uchar8 *)(&GV_C_Pluse_Most__Lim[0]), pV_ucData ,CLPluse_Most__Lim);
			return C_OK;
		}
	}
#endif
	/******************************���¼���¼��ǰ��¼��***class 07******************************/
	if( 0x30000700 == (V_ulData_Id & 0xF000FF00) )
	{
		V_Return_Flag = SF_ReadCurrentTab_Data(V_ulData_Id, pV_ucData, pV_usData_Length);
		if( V_Return_Flag != C_OK)
		{
			(*pV_usData_Length) = 0;
		}
		return V_Return_Flag;
	}

	/*********************************����Ϊ��ͨ������*****************************************/
	V_Return_Flag = SF_Find1Table_Data(V_DI[3], &V_Line);                        /*����1����*/
	if(V_Return_Flag!=C_OK)
	{
		(*pV_usData_Length) = 0;
		return V_Return_Flag;
	}

	V_WR_Mes = V_MesNum;
	if(0x04 == V_DI[3])/*�α�����2���ֱ����⴦�����ӱ�������Ч��*/
	{
		V_Return_Flag = SF_Find2Table_DIParamChild(V_DI[2], &V_Line);
		if(V_Return_Flag != C_OK)
		{
			(*pV_usData_Length) = 0;
			return V_Return_Flag;
		}

		PStr_2TableAddr = (Str_2Table *)(Str_2Table_DIParamChild[V_Line].PStr_2TableParamChildAddr);		/*DI2��Ӧ��2�����ַ*/
		V_Return_Flag = SF_Find2Table_Data(V_WR_Mes, V_ulData_Id, &V_DataLen, PStr_2TableAddr, &V_Line, Str_2Table_DIParamChild[V_Line].V_Str_2TableLen);
	}
	else
	{
		PStr_2TableAddr=(Str_2Table * )(Str_1Table_DI3[V_Line].PStr_2TableAddr);		/*DI3��Ӧ��2�����ַ*/
		V_Return_Flag=SF_Find2Table_Data(V_WR_Mes, V_ulData_Id, &V_DataLen, PStr_2TableAddr, &V_Line, Str_1Table_DI3[V_Line].V_Str_2TableLen);
	}

	*pV_usData_Length = (V_DataLen);

	if(V_Return_Flag != C_OK)
	{
		(*pV_usData_Length) = 0;
		return V_Return_Flag;
	}
	else
	{
		if(0 == (*pV_usData_Length) )/*�������ݳ���Ϊ�㣬Ŀǰֻ�й���OAD��ű���ܻ���ָ����(û��OAD��ű���������Ϊ0)*/
		{
			return V_Return_Flag;
		}
	}

	switch(PStr_2TableAddr[V_Line].V_DT_Type)   /*DI2-DI0��Ӧ2���������кţ���ͬ���ݴ���ʽ*/
	{
		case DT_Ref_E23_RAMCRC:                   /*��E2����CRC���ݼ�RAM��CRC(д��������ʱ����дRAM�����Ÿ���E2����)*/
		case DT_Ti_E23_RAMCRC:                    /*��E2����CRC���ݼ�RAM��CRC(д��������ʱ��ֻдRAM����ʱдE2����Ҫ�ǵ�ǰ������������) */
		case DT_Ref_E23_RAMCRC_DI0:               /*19��E2����RAM��CRC�����ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
		                                          /*���ݵ�ַ��DI�ж��Ƿ���ȷ�����������״̬�֣��б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
		case DT_Ref_E23_RAMCRC_DI0_2:             /*28��E2����RAM��CRC�����ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��1,DI0=0,1Ҫ����)�������ڲ�����*/
		                                           /*���ݵ�ַ��DI�ж��Ƿ���ȷ��������ȫʧѹ��������������ã��б��ʱ����Ӧ���ݴ洢��ַ(��ѹ�쳣�жϵ�ѹ��ַ)��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
		case DT_R_Ref_E23_RAMCRC_Lad:  				    /*39:дE2 RAM���ݣ����ݱ�д��ʱ֧�ּ���д��������ʱ֧�ַֿ��������ݲ��ڲ���������*/
		{
			PStr_3aTableAddr = (Str_3aTable *)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*ȡ3�����ַ*/

			if(DT_Ref_E23_RAMCRC_DI0 == PStr_2TableAddr[V_Line].V_DT_Type)
			{
				if(0==V_DI[0])
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*����������*/
				}
			}

			if( (V_ulData_Id & 0xFFFFFF00) == (CL_Free_OADTab & 0xFFFFFF00) )	/*����OAD��ű�,д���ݲ��ж����ݳ��ȣ����ж�д���ݳ��Ȳ��ܴ�����󳤶�*/
			{
				V_Return_Flag = SF_Re_E23_RAM_Data698(&PStr_3aTableAddr[PStr_2TableAddr[V_Line].V_LineNum], V_DataLen, pV_ucData);
			}
			else
			{
				V_Return_Flag = SF_Re_E23_RAM_Data(PStr_3aTableAddr, PStr_2TableAddr[V_Line].V_LineNum, V_DataLen, pV_ucData, PStr_2TableAddr[V_Line].V_DT_Type, V_DI[0], V_ulData_Id);
			}

			if(CComm_Address == V_ulData_Id)/*ͨ�ŵ�ַ���⴦��û�����ã�Ĭ��Ϊȫ0*/
			{
				uchar8 V_i;
				if(C_OK != V_Return_Flag)/*��ʧ��*/
				{
					for(V_i = 0; V_i < CLComm_Address; V_i++)
					{
						pV_ucData[V_i] = 0x00;
					}
					V_Return_Flag = C_OK;
				}
			}
		}break;

		case DT_E23:                              /*��E2����CRC����*/
		case DT_E23_Clear:                              /*��E2����CRC����*/
		case DT_E23_Hex:                          /*��E2����CRC���ݣ����ݴ洢��ʽΪhex��ʽ(��Ҫ���ۼƴ�������ͨѶ��������ʱ��ת��ΪBCD��ʽ)*/
#if 0
		case DT_E23_En:                           /*16�����������ݣ�����6+2��6+4���ݳ���ʱ���������赥���������ݳ���(����д)���������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��*/
		                                    /*(�б�645���ݳ���Ϊ6+2��������6+4������ʱ���������ݳ��ȵ�����ȡE2��ַ����������1��������������й��ۼ��õ���),д����ʱ�����ݳ����жϵ�����*/
		case DT_E23_En_Clear:                           /*16�����������ݣ�����6+2��6+4���ݳ���ʱ���������赥���������ݳ���(����д)���������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��*/
		                                    /*(�б�645���ݳ���Ϊ6+2��������6+4������ʱ���������ݳ��ȵ�����ȡE2��ַ����������1��������������й��ۼ��õ���),д����ʱ�����ݳ����жϵ�����*/
#endif
		case DT_E23_DI0:                          /*20��E2������E2��ַ˳���У����ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
		                                  /*���ݵ�ַ��DI�ж��Ƿ���ȷ�������ƽ����ա����룬�б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
		case DT_E23_OADTab:               /*38:��E2�������ж����ݳ���ʱ�����ȡ�ù����б�OAD����*/
		{
			if(DT_E23_OADTab==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				PStr_3eTable_2E2 = (Str_3eTable *)(PStr_2TableAddr[V_Line].PStr_3TableAddr);

				if(PStr_2TableAddr[V_Line].V_LineNum>=Str_3eTable_Flash_Len)
				{
					(*pV_usData_Length) = 0;
					return C_DataLenError;
				}

				V_3TableE2Addr=PStr_3eTable_2E2[PStr_2TableAddr[V_Line].V_LineNum].V_E2BakeUp1Addr_OADTab;
			}
			else
			{
				V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*ȡ3����E2��ַ*/
			}

			if(DT_E23_DI0==PStr_2TableAddr[V_Line].V_DT_Type)    /*E2��ַ����*/
			{
				if(0==V_DI[0])
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*����������*/
				}

				V_3TableE2Addr=V_3TableE2Addr+(V_DI[0]-1)*(V_DataLen+C_CRCLen2);
				if(V_3TableE2Addr>E2_Max_Addr)
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*����������*/
				}
			}

			V_Return_Flag=SF_Re_E23_Data(V_3TableE2Addr, V_DataLen, pV_ucData, PStr_2TableAddr[V_Line].V_DT_Type, V_WR_Mes);

			if(CComm_Address == V_ulData_Id)/*ͨ�ŵ�ַ���⴦��û�����ã�Ĭ��Ϊȫ0*/
			{
				uchar8 V_i;
				if(C_OK != V_Return_Flag)/*��ʧ��*/
				{
					for(V_i = 0; V_i < CLComm_Address; V_i++)
					{
						pV_ucData[V_i] = 0x00;
					}
					V_Return_Flag = C_OK;
				}
			}
		}break;

		case DT_Flash_DI04:                       /*��Flash�����������ݣ�DI0��4λ��ʾ��������4λ��ʾ��ͬ��ʶ��(��ѯ4������)*/
		case DT_Flash_Tol_DI0_DI1:                /*��Flash�����������ݣ�����DI0��ʾ������DI1��ʾ�����ʶ��(��ѯ4������)*/
#if 0
		case DT_Flash_Tol_DI0_DI2:                /*11�� Flash�����������ݣ�����DI0��ʾ������DI2��ʾ�����ʶ��(��ѯ4�����ã���Ҫ�ǵ�����������ABC��������)*/
		case DT_Flash_Tol_DI0_SettEn:             /*12��Flash�����������ݣ�����DI0��ʾ����������DI2��DI1�������ƫ�Ƶ�ַ(�����ѯ4������Ҫ�ǽ������������ABC����������)��*/
		case DT_Flash_Tol_DI0_SettDe:             /*13��Flash�����������ݣ�����DI0��ʾ����������DI2��DI1�������ƫ�Ƶ�ַ(�����ѯ4������Ҫ�ǽ�������������ABC����������)��*/
		case DT_Flash_Tol_DI0:                    /*15�� Flash�����������ݣ�����DI0��ʾ������û�з����ʶ�롣*/
		case DT_R_Flash_Tol_DI0_DI2_En:           /*25�� Flash�����������ݣ�����DI0��ʾ������DI2��ʾ�����ʶ��(��ѯ4�����ã�������ABC�������ݶ�)��*/
		                                          /*ͬʱ���ݳ��ȼ��������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��*/
#endif
		case DT_Flash_Tol_DI0_DI1Max:             /*27�� Flash�����������ݣ�����DI0��ʾ�������б�2����ʱֻ����1��DI1���ֵ(�����ò���4����ķ�ʽ)���ڲ�������DI��DI���ݴ��ƫ�Ƶ�ַʱ��*/
		                                      /*OffsetAddr������ü��㷽ʽ����,Ŀǰֻ��У���¼���ø÷�ʽ,������ʱ��DI1=0��*/
		case DT_Flash_698EventTab:     						/*37:��OAD�����б��¼���¼����Flash*/
		{
			V_Return_Flag = SF_ReadFlash_Data(pV_ucData, V_DataLen, PStr_2TableAddr[V_Line].PStr_3TableAddr, V_ulData_Id, PStr_2TableAddr[V_Line].V_LineNum, PStr_2TableAddr[V_Line].V_DT_Type, V_WR_Mes);
		}break;

		case DT_E21:                              /*��E2һ��*/
#if 0
		case DT_E21_En:                           /*17�����������ݣ�����6+2��6+4���ݳ���ʱ���������赥���������ݳ���(����д)���������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��,��Ҫ��Դ�E2 1������*/
		                                          /*(�б�645���ݳ���Ϊ6+2��������6+4������ʱ���������ݳ��ȵ�����ȡE2��ַ����������1--4��������ս���ʱ�估������������й����ۼ��õ���*/
#endif
		case DT_E21_DI0:                          /*22��E2һ�������ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
		{                                        /*���ݵ�ַ��DI�ж��Ƿ���ȷ�������Ƶ�1-254�����������ڼ���ʱ�α�ţ��б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
			V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*ȡ3����E2��ַ*/
#if 0
			if((DT_E21_DI0==PStr_2TableAddr[V_Line].V_DT_Type)
				||(DT_E21_DI0_ReadDegree==PStr_2TableAddr[V_Line].V_DT_Type))    /*E2��ַ����*/
#endif
			if( DT_E21_DI0 == PStr_2TableAddr[V_Line].V_DT_Type )
			{
				if(0==V_DI[0])
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*����������*/
				}

				V_3TableE2Addr=V_3TableE2Addr+(V_DI[0]-1)*V_DataLen;
				if(V_3TableE2Addr>E2_Max_Addr)
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*����������*/
				}
			}

			V_Return_Flag = SF_ReadE21(V_3TableE2Addr, V_DataLen, pV_ucData, PStr_2TableAddr[V_Line].V_DT_Type, V_WR_Mes);
		}break;

		case DT_RAM:                              /*��RAM����CRC*/
		case DT_RAM_Time_Data:                    /*��RAM����CRC��������ʱ���жϵ����־��*/
		case DT_RAM_DI0:	                        /*18�����ݴ�RAM����CRC�������ݳ��ȡ�����һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(,ͬһ���ͣ�������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
		                                          /*���ݵ�ַ��DI�ж��Ƿ���ȷ�������Ƶ������״̬��1-7���б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
#if 0
		case DT_RAM_DI1_0:                        /*23�����ݴ�RAM����CRC�������ݳ��ȡ�����һ��(ͬһDI3-DI2��DI0)���б��ʱֻ��DI1���ֵ(,ͬһ����,����DI1=0����������ƫ�Ƶ�ַʱ��Ҫ����)��*/
		                                        /*�����ڲ��������ݵ�ַ��DI�ж��Ƿ���ȷ�������Ʋ���˲ʱ���ʣ��б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI1��Ӧ���ݴ洢��ַ��ע��*/
		case DT_RAM_DI1:	                        /*24�����ݴ�RAM����CRC�������ݳ��ȡ�����һ��(ͬһDI3-DI2��DI0)���б��ʱֻ��DI1���ֵ(,ͬһ���ͣ�������DI1=0)�������ڲ�����*/
#endif
		{                                      /*���ݵ�ַ��DI�ж��Ƿ���ȷ�������Ƶ�ѹ���ݣ��б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI1��Ӧ���ݴ洢��ַ��ע��*/
			P_3TableRamAddr=(uchar8 *)PStr_2TableAddr[V_Line].PStr_3TableAddr;

			if(DT_RAM_DI0==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				if(0==V_DI[0])
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*����������*/
				}
				P_3TableRamAddr=P_3TableRamAddr+(V_DI[0]-1)*V_DataLen;
			}
#if 0
			if(DT_RAM_DI1_0==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				P_3TableRamAddr=P_3TableRamAddr+V_DI[1]*V_DataLen;
			}

			if(DT_RAM_DI1==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				if(0==V_DI[1])
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*����������*/
				}
				P_3TableRamAddr=P_3TableRamAddr+(V_DI[1]-1)*V_DataLen;
			}
#endif
			V_Return_Flag=SF_Re_RAM_Data(P_3TableRamAddr, V_DataLen, pV_ucData, PStr_2TableAddr[V_Line].V_DT_Type, V_DI[0]);
		}break;

		case DT_RAMCRC:                           /*��RAM��CRC*/
		{
			P_3TableRamAddr=(uchar8 *)PStr_2TableAddr[V_Line].PStr_3TableAddr;
			V_Return_Flag = SF_Re_RAMCRC_Data(P_3TableRamAddr, V_DataLen, pV_ucData);
		}break;

		case DT_E21CRC_DI0:                       /*21��E2һ����CRC�����ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
		{                                        /*���ݵ�ַ��DI�ж��Ƿ���ȷ���������Զ�ѭ����ʾ��1-99����ʾ���룬�б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
			V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*ȡ3����E2��ַ*/

			if(DT_E21CRC_DI0==PStr_2TableAddr[V_Line].V_DT_Type)    /*E2��ַ����*/
			{
				if(0==V_DI[0])
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*����������*/
				}

				V_3TableE2Addr=V_3TableE2Addr+(V_DI[0]-1)*(V_DataLen+C_CRCLen2);
				if(V_3TableE2Addr>E2_Max_Addr)
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*����������*/
				}
			}

			V_Return_Flag = SF_Read_E21CRC_Data(V_3TableE2Addr, V_DataLen, pV_ucData);
		}break;

		case DT_FRAM1CRC:                       /*42������һ����CRC*/
		{
			V_3TableE2Addr = (ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*ȡ3���������ַ*/
			V_Return_Flag = SF_Read_FRAM1CRC_Data(V_3TableE2Addr, V_DataLen, pV_ucData);
		}break;

		default:
			return C_IDError;  /*���Ҵ���*/
	}
	if(V_Return_Flag != C_OK)
	{
		(*pV_usData_Length) = 0;
	}
	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Re_E23_RAM_Data698(Str_3aTable *PStr_3aTable_E23RAM,ushort16 V_DataLen,uchar8 *P_Data)
������������E2������RAM����,���ݲ��ڲ���698������
���������
		Str_3aTable *PStr_3aTable_E23RAM:Ҫ����3a����ṹ��Ԫ�ص�ַ��
		ushort16 V_DataLen��Ҫ�����ݳ���
���������
		uchar8 *P_Data�������ݻ���
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero,C_DataLenError��
����˵����
���û��ƣ�
��ע��
*********************************************************************************/
uchar8 SF_Re_E23_RAM_Data698(Str_3aTable *PStr_3aTable_E23RAM,ushort16 V_DataLen,uchar8 *P_Data)
{
	ushort16 V_i,V_CRC_Flag,V_Len;
	ushort16 V_E2Addr;
	uchar8 *P_RamAddr=NULL;
	uchar8 V_Return_Flag;

	if(V_DataLen==0)/*��Ҫ�ǹ����б�����û�й����б�Ҳ����ok����Ҫ�����ݲ�ȡ�����б��ã��������ģ������ݲ㣬�ڸտ�ʼ�ͷ����ˡ�*/
	{
		return C_OK;
	}

	V_Len=V_DataLen+C_CRCLen2;	                /*����CRC*/
	P_RamAddr=(* PStr_3aTable_E23RAM).V_RamAddr;
	V_E2Addr=(* PStr_3aTable_E23RAM).V_E2BakeUp1Addr;
	V_CRC_Flag=PF_Check_CRC(&P_RamAddr[0],V_Len);/*ȡRAM����*/

	V_Len=V_Len-C_CRCLen2;                                /*ȥ��CRC*/

	if(C_OK==V_CRC_Flag)
	{
		PF_CopyDataBytes_698(&P_RamAddr[0],P_Data,V_Len);
		return C_OK;
	}
	else
	{
		if(C_CrcErr_DataZero==V_CRC_Flag)        /*CRC��������Ϊȫ��*/
		{
			for(V_i=0;V_i<V_Len;V_i++)
			{
				if(0!=P_RamAddr[V_i])
				{
					break;
				}
			}

			if(V_i==V_Len)                        /*������ȷ*/
			{
				PF_CopyDataBytes_698(&P_RamAddr[0],P_Data,V_Len);
				return C_CrcErr_DataZero;         /*����CRC���󣬵�����Ϊȫ��*/
			}
		}
	}

	V_Len=V_DataLen;
	V_Return_Flag=SF_ReadE2Three_698_AndCRC(V_E2Addr,V_Len,&P_RamAddr[0]);/*�������ݴ�CRC*/
	PF_CopyDataBytes_698(&P_RamAddr[0],P_Data,V_Len);

	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Re_E23_RAM_Data(Str_3aTable *PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,
									uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_DI,ulong32 V_Data_Id)
������������E2������RAM����
���������
		Str_3aTable *PStr_3aTable_E23RAM:Ҫ����3a����ṹ���ַ��
		ushort16 V_3aTable_Line��Ҫ����3a������кţ�
		ushort16 V_DataLen��Ҫ�����ݳ���
		uchar8 V_DT_Type:��������
		uchar8 V_DI:����DI�����ڼ���E2��RAM���Ե�ַ
		ulong32 V_Data_Id��DI0-DI3���ݱ�ʶ��
���������uchar8 *P_Data�������ݻ���
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero,C_DataLenError��
����˵����
���û��ƣ�
��     ע���ڲ������������
*********************************************************************************/
uchar8 SF_Re_E23_RAM_Data(Str_3aTable *PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_DI,ulong32 V_Data_Id)
{
	ushort16 V_i,V_CRC_Flag,V_Len;
	uchar8 PV_Data[C_RAM_Max];
	ushort16 V_E2Addr;
	uchar8 *P_RamAddr=NULL;
	uchar8 V_Return_Flag;
	uchar8 V_Return_Flag1;

	if(V_3aTable_Line>=Str_3aTable_E23RAM_Len)   /*����������*/
	{
		return C_AbnormalError;
	}

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	V_Len=V_DataLen+C_CRCLen2;	                /*����CRC*/

	P_RamAddr=PStr_3aTable_E23RAM[V_3aTable_Line].V_RamAddr;
	V_E2Addr=PStr_3aTable_E23RAM[V_3aTable_Line].V_E2BakeUp1Addr;

	if(DT_Ref_E23_RAMCRC_DI0==V_DT_Type)    /*E2��RAM��ַ����*/
	{
		if(V_DI<1)
		{
			return C_AbnormalError;
		}

		V_E2Addr=V_E2Addr+(V_DI-1)*(V_DataLen+C_CRCLen2);
		P_RamAddr=P_RamAddr+(V_DI-1)*(V_DataLen+C_CRCLen2);
	}

	if(DT_Ref_E23_RAMCRC_DI0_2==V_DT_Type)  /*04FE0202���������DI0=2��ʼ����*/
	{
		if(V_DI<2)
		{
			return C_AbnormalError;
		}

		P_RamAddr=P_RamAddr+(V_DI-2)*V_Len;
		V_E2Addr=V_E2Addr+(V_DI-2)*V_Len;
	}

	if(DT_R_Ref_E23_RAMCRC_Lad==V_DT_Type)  /*39:дE2 RAM���ݣ����ݱ�д��ʱ֧�ּ���д��������ʱ֧�ַֿ��������ݲ��ڲ���������*/
	{
		V_Len=CLCurrent_Ladder_Table+C_CRCLen2;	                /*����CRC*/
	}

	for(V_i=0;V_i<V_Len;V_i++)                    /*ȡRAM����*/
	{
		PV_Data[V_i]=*(P_RamAddr+V_i);
	}

	V_CRC_Flag=PF_Check_CRC(&PV_Data[0],V_Len);

	/*****************ʣ�������⴦��ʣ����CRC�������㣬����ȫ�����CRC����Ϊ���ݴ���,20160517********************/
	if(CChargeBal_Hex_Full == V_Data_Id)
	{
		V_Return_Flag1=SF_AllDataZero_Judge(&PV_Data[0],V_Len);/*�����Ƿ�Ϊȫ���жϣ�����CRC*/
		if(C_OK==V_Return_Flag1)
		{
			V_CRC_Flag=C_CRCError;/*ʣ��������ȫ��(����CRC)������������(����ʱ��ʣ����CRC����Ϊ��ȷ)������ΪRAM�����쳣��*/
		}
	}

	V_Len=V_Len-C_CRCLen2;                                /*ȥ��CRC*/
	if(C_OK==V_CRC_Flag)
	{
		if(DT_R_Ref_E23_RAMCRC_Lad==V_DT_Type) /*39:дE2 RAM���ݣ����ݱ�д��ʱ֧�ּ���д��������ʱ֧�ַֿ��������ݲ��ڲ���������*/
		{
			switch(V_Data_Id)
			{
				case CCurrent_Ladder_Table_LadNum:
				case CBackUp_Ladder_Table_LadNum:			/*����ֵ*/
				{
					PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_DataLen);
				}break;

				case CCurrent_Ladder_Table_LadPri:
				case CBackUp_Ladder_Table_LadPri:			/*���ݵ��*/
				{
					if((CLCurrent_Ladder_Table_LadNum+V_DataLen) < C_RAM_Max)
					{
						PF_CopyDataBytes(&PV_Data[CLCurrent_Ladder_Table_LadNum],P_Data,(uchar8)V_DataLen);
					}
				}break;

				case CCurrent_Ladder_Table_LadSett:
				case CBackUp_Ladder_Table_LadSett:			/*���ݽ�����*/
				{
					if((CLCurrent_Ladder_Table_LadNum+CLCurrent_Ladder_Table_LadPri+V_DataLen) < C_RAM_Max)
					{
						PF_CopyDataBytes(&PV_Data[CLCurrent_Ladder_Table_LadNum+CLCurrent_Ladder_Table_LadPri],P_Data,(uchar8)V_DataLen);
					}
				}break;

				default:/*����������*/
					return C_DataLenError;
			}
		}
		else
		{
			PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);
		}
		return C_OK;
	}
	else
	{
		if(C_CrcErr_DataZero==V_CRC_Flag)        /*CRC��������Ϊȫ��*/
		{
			for(V_i=0;V_i<V_Len;V_i++)
			{
				if(0!=PV_Data[V_i])
				{
					break;
				}
			}

			if(V_i==V_Len)                        /*������ȷ*/
			{
				if(DT_R_Ref_E23_RAMCRC_Lad==V_DT_Type)
				{
					V_Len=V_DataLen;
				}

				PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);
				return C_CrcErr_DataZero;         /*����CRC���󣬵�����Ϊȫ��*/
			}
		}
	}

	if(DT_R_Ref_E23_RAMCRC_Lad==V_DT_Type)  /*39:дE2 RAM���ݣ����ݱ�д��ʱ֧�ּ���д��������ʱ֧�ַֿ��������ݲ��ڲ���������*/
	{
		V_Len=CLCurrent_Ladder_Table;
	}
	else
	{
		V_Len=V_DataLen;
	}

	if(V_DT_Type==DT_Ti_E23_RAMCRC)/*��������*/
	{
		V_Return_Flag=SF_ReadFRAMThree_AndCRC(V_E2Addr,(uchar8)V_Len,&PV_Data[0]);/*��ȡ���ݰ���CRC*/
	}
	else/*E2����*/
	{
		V_Return_Flag=SF_ReadE2Three_AndCRC(V_E2Addr,(uchar8)V_Len,&PV_Data[0]);/*��ȡ���ݰ���CRC*/
	}

	if(C_OK==V_Return_Flag)  /*7.24*/
	{
		if(DT_R_Ref_E23_RAMCRC_Lad==V_DT_Type)  /*39:дE2 RAM���ݣ����ݱ�д��ʱ֧�ּ���д��������ʱ֧�ַֿ��������ݲ��ڲ���������*/
		{
			V_Len=CLCurrent_Ladder_Table+C_CRCLen2;
		}
		else
		{
			V_Len=V_DataLen+C_CRCLen2;
		}

		for(V_i=0;V_i<V_Len;V_i++)     /*RAM ��ֵ*/
		{
			*(P_RamAddr+V_i)=PV_Data[V_i];
		}
	}

	V_Len=V_DataLen;

	if(DT_R_Ref_E23_RAMCRC_Lad==V_DT_Type) /*39:дE2 RAM���ݣ����ݱ�д��ʱ֧�ּ���д��������ʱ֧�ַֿ��������ݲ��ڲ���������*/
	{
		switch(V_Data_Id)
		{
			case CCurrent_Ladder_Table_LadNum:
			case CBackUp_Ladder_Table_LadNum:			/*����ֵ*/
			{
				PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_DataLen);
			}break;

			case CCurrent_Ladder_Table_LadPri:
			case CBackUp_Ladder_Table_LadPri:			/*���ݵ��*/
			{
				if((CLCurrent_Ladder_Table_LadNum+V_DataLen)<C_RAM_Max)
				{
					PF_CopyDataBytes(&PV_Data[CLCurrent_Ladder_Table_LadNum],P_Data,(uchar8)V_DataLen);
				}
			}break;

			case CCurrent_Ladder_Table_LadSett:
			case CBackUp_Ladder_Table_LadSett:			/*���ݽ�����*/
			{
				if((CLCurrent_Ladder_Table_LadNum+CLCurrent_Ladder_Table_LadPri+V_DataLen)<C_RAM_Max)
				{
					PF_CopyDataBytes(&PV_Data[CLCurrent_Ladder_Table_LadNum+CLCurrent_Ladder_Table_LadPri],P_Data,(uchar8)V_DataLen);
				}
			}break;

			default:/*����������*/
				return C_DataLenError;
		}
	}
	else
	{
		PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);
	}

	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Read_FRAM1CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
����������������1�����ݣ�����Type���ݴ洢���ͣ��ж����ݸ�ʽ
���������
		ushort16 V_E2Addr�������������ַ��
		ushort16 V_DataLen�������ݳ���
���������uchar8 *P_Data�������ݻ���
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_Read_FRAM1CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_Len;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 V_Return_Flag;
	uchar8 V_ReCRC;

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	V_Len=(uchar8)V_DataLen+C_CRCLen2;

	V_Return_Flag=InF_ReadFRAM(V_E2Addr,&PV_Data[0],(ushort16)V_Len);
	V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)V_Len);

	V_Len=V_Len-C_CRCLen2;
	PF_CopyDataBytes(&PV_Data[0],P_Data,V_Len);

	if(C_OK!=V_Return_Flag)
	{
		return  V_Return_Flag;    /*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;      /*���ܷ���C_CrcErr_DataZero*/
		}
		else
		{
			return C_OK;
		}
	}
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Read_E21CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
������������E21�����ݣ�����Type���ݴ洢���ͣ��ж����ݸ�ʽ
���������
		ushort16 V_E2Addr��������E2��ַ��
		ushort16 V_DataLen�������ݳ���
���������uchar8 *P_Data�������ݻ���
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_Read_E21CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_Len;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 V_Return_Flag;
	uchar8 V_ReCRC;

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		if(_DEBUG)
		{
		  /**/
		}
		return C_DataLenError;
	}

	V_Len=(uchar8)V_DataLen+C_CRCLen2;
	V_Return_Flag=InF_ReadE2(V_E2Addr,&PV_Data[0],(ushort16)V_Len);
	V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)V_Len);

	V_Len=V_Len-C_CRCLen2;
	PF_CopyDataBytes(&PV_Data[0],P_Data,V_Len);

	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;    /*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;      /*���ܷ���C_CrcErr_DataZero*/
		}
		else
		{
			return C_OK;
		}
	}
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Re_E23_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_WR_Mes)
������������E2�������ݣ�����Type���ݴ洢���ͣ��ж����ݸ�ʽ
���������
		ushort16 V_E2Addr��������E2��ַ��
		ushort16 V_DataLen�������ݳ���
		uchar8 V_DT_Type����������
		uchar8 V_WR_Mes:��������Ϣ�ţ�����������ͨ�ö���������ʾ������Ϊͨ�ö�ʱ��Ϣ��Ϊ0����ʾ��ʱΪ��ʾNum��
���������uchar8 *P_Data�������ݻ���
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע����ʾ���������������ݳ����Ѿ�Ϊ6+4������ģ�������������Ϊ6+2�����ݳ��������⴦��
*********************************************************************************/
uchar8 SF_Re_E23_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_WR_Mes)
{
	ushort16 V_Len;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 V_Return_Flag;
	ulong32 V_Hex;

	if(C_RAM_Max<V_DataLen)
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}
#if 0
	if((C_Msg_Display!=(V_WR_Mes&0x7F))&&((DT_E23_En==V_DT_Type)||(DT_E23_En_Clear==V_DT_Type))) /*ͨ�Ŷ�(��ʾ�����������ݳ�����+1)��������--��������--�����赥������,��֧����ʾ�࣬���ݿ��*/

	{
		V_Len=V_DataLen+1;                   /*645���ݳ���+1*/
	}
	else
	{
		V_Len=V_DataLen;
	}
#endif

	V_Len=V_DataLen;

	V_Return_Flag=SF_ReadE2Three(V_E2Addr,(uchar8)V_Len,&PV_Data[0]);

	if(DT_E23_Hex==V_DT_Type)             /*������תBCD��ʽ*/
	{
		V_Len=CLAll_Loss_Vol_Degree;

		if(V_E2Addr == E2Addr_Program_Degree_645) /*645����¼����⴦��*/
		{
			PV_Data[3]=0;
		}

		PF_Buffer4ToUlong32(&PV_Data[0],&V_Hex,(uchar8)V_Len);
		/*PF_HextoBCDBytes(&V_Hex,&PV_Data[0],(uchar8 *)(&V_Len));*/	/*��������Ҫ����hex-bcdת��*/
	}

	V_Len=V_DataLen;
#if 0
	if((C_Msg_Display!=(V_WR_Mes&0x7F))&&((DT_E23_En==V_DT_Type)||(DT_E23_En_Clear==V_DT_Type)))  /*�ж��Ƿ�Ϊ������ʾģ�����������--��������--�����赥������,��֧����ʾ�࣬���ݿ��*/
	{
		PF_CopyDataBytes(&PV_Data[1],P_Data,(uchar8)V_Len);            /*��6+2����*/
	}
	else
	{
		PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);
	}
#endif

	PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);

	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_ReadE21(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_WR_Mes)
������������E21�����ݣ�����Type���ݴ洢���ͣ��ж����ݸ�ʽ
���������
		ushort16 V_E2Addr��������E2��ַ��
		ushort16 V_DataLen�������ݳ���
		uchar8 V_DT_Type����������
		uchar8 V_WR_Mes:��������Ϣ�ţ�����������ͨ�ö���������ʾ������Ϊͨ�ö�ʱ��Ϣ��Ϊ0����ʾ��ʱΪ��ʾNum��
���������
		uchar8 *P_Data�������ݻ���
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע����ʾ���������������ݳ����Ѿ�Ϊ6+4������ģ�������������Ϊ6+2�����ݳ��������⴦��
*********************************************************************************/
uchar8 SF_ReadE21(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_WR_Mes)
{
	ushort16 V_Len;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 V_Return_Flag;
#if 0		/*ԭ��645���ݳ��ȱ�698���ݳ���С1�ֽڣ����ݲ㰴��645���ȴ洢�����л�ʱ�䡢�ڼ��ղ���û��20���������1�ֽ��ж���Ϊ����˳��ͨ�����ȺϷ����ж�*/
	if( ( C_RAM_Max < (V_DataLen + 1) ) || ( V_DataLen > 255 ) )
#endif
	if( ( C_RAM_Max < V_DataLen ) || ( V_DataLen > 255 ) )
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

#if 0	/*�˴�698�Ѳ�ʹ��*/
	if((C_Msg_Display!=(V_WR_Mes&0x7F))&&(DT_E21_En==V_DT_Type))                   /*�ж��Ƿ�Ϊ������ʾģ�����������--��������--�����赥������,��֧����ʾ�࣬���ݿ��*/
	{
		V_Len=V_DataLen+1;                   /*645���ݳ���+1*/
	}
	else
	{
		V_Len=V_DataLen;
	}
#endif

	V_Len=V_DataLen;
	V_Return_Flag=InF_ReadE2(V_E2Addr,&PV_Data[0],V_Len);

#if 0	/*�˴�698�Ѳ�ʹ��*/
	if((C_Msg_Display!=(V_WR_Mes&0x7F))&&(DT_E21_En==V_DT_Type))   /*ͨ�Ŷ������ݵ���*/
	{
		for(V_i=0;V_i<V_DataLen;V_i++)
		{
			if(V_i>=4)   /*����6+2,��Ҫ��������õ���*/
			{
				PV_Data[V_i]=PV_Data[V_i+1];
			}
		}
	}
#endif

	V_Len=V_DataLen;
	PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);

	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_ReadFlash_Data(uchar8 *P_Data,ushort16 V_Data_Length,ulong32 Str_3TableAddr,ulong32 V_Data_Id,
									ushort16 V_3cTable_Line,uchar8 V_Type,uchar8 V_WR_Mes)
������������Flash����
���������
		uchar8 V_Data_Length�������ݾ��峤�ȣ�
		ulong32 Str_3TableAddr����Ӧ3������׵�ַ��
		ulong32 V_Data_Id��DI0-DI3���ݱ�ʶ��
		ushort16 V_3cTable_Line��Ҫ����3c������кţ�
		uchar8 V_Type:���ݴ洢����
		uchar8 V_MesNum:��������Ϣ�ţ�����������ͨ�ö���������ʾ������Ϊͨ�ö�ʱ��Ϣ��Ϊ0����ʾ��ʱΪ��ʾNum��
���������uchar8 *P_Data:�����ݻ��棻
���ز�����C_OK��C_SPIError,C_IICError��C_IDError��C_NoAccess��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_ReadFlash_Data(uchar8 *P_Data,ushort16 V_Data_Length,ulong32 Str_3TableAddr,ulong32 V_Data_Id,ushort16 V_3cTable_Line,uchar8 V_Type,uchar8 V_WR_Mes)
{
	uchar8 P_Dgree[CLAll_Loss_Vol_Degree];
	ushort16 V_E2Addr,V_OffAddr;
	ulong32 V_Dgree;
	Str_4Table *PStr_4TableAddr=NULL;
	ulong32 P_FlashAddr1[2];
	uchar8 V_Return_Flag,V_DI[4];
	ushort16 V_i;

	Str_3cTable Str_3cTableAddr;
	Str_3cTable *PStr_3cTableAddr=NULL;

	Str_3dEventTable Str_3dEventTableAddr;
	Str_3dEventTable *PStr_3dEventTableAddr=NULL;

	if(DT_Flash_698EventTab!=V_Type)	/*˫Э��֮645�¼���¼*/
	{
		if(V_3cTable_Line>=Str_3cTable_Flash_Len)
		{
			return C_AbnormalError;/*����������*/
		}

		PStr_3cTableAddr=(Str_3cTable *)Str_3TableAddr;
		Str_3cTableAddr=PStr_3cTableAddr[V_3cTable_Line];
		V_E2Addr=Str_3cTableAddr.V_Num_E2BakeUp1Addr;    /*ȡFlash��¼����E2��ַ*/
	}
	else	/*698�¼���¼*/
	{
		if(V_3cTable_Line>=Str_3dTable_Flash_Len)
		{
			return C_AbnormalError;/*����������*/
		}

		PStr_3dEventTableAddr=(Str_3dEventTable *)Str_3TableAddr;
		Str_3dEventTableAddr=PStr_3dEventTableAddr[V_3cTable_Line];
		V_E2Addr=Str_3dEventTableAddr.V_Num_E2BakeUp1Addr;    /*ȡFlash��¼����E2��ַ*/
	}

	V_OffAddr=0x0000;
#if 0
	if((V_Data_Id&0xFFFF0000)==(CRec_Meter_Degree&0xFFFF0000))		/*У���¼����������*/
	{
		V_Return_Flag=SF_ReadE2Three(V_E2Addr,3,&P_Dgree[0]);
		P_Dgree[3]=0;
	}
	else
	{
		if(V_E2Addr == E2Addr_Program_Degree_645)
		{
			V_Return_Flag=SF_ReadE2Three(V_E2Addr,CLProgram_Degree_645,&P_Dgree[0]);
			P_Dgree[3]=0;
		}
		else
		{
#endif
			V_Return_Flag=SF_ReadE2Three(V_E2Addr,CLAll_Loss_Vol_Degree,&P_Dgree[0]);
#if 0
		}
	}
#endif
	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&P_Dgree[0],&V_Dgree,CLAll_Loss_Vol_Degree);

	PF_Ulong32ToBuffer4(&V_DI[0],&V_Data_Id,4);

	if(DT_Flash_DI04==V_Type)    /*��Flash�����������ݣ�DI0��4λ��ʾ��������4λ��ʾ��ͬ��ʶ��(��ѯ4������)*/
	{
		V_DI[0]=V_DI[0]&0x0F;
	}

	if(0==V_DI[0])               /*���������ܵ�ǰ��¼�ܴ������ҳ���������0*/
	{
		return C_IDError;
	}

	if(V_DI[0]>V_Dgree)          /*�������ݷ���ȫ��*/
	{
		for(V_i=0;V_i<V_Data_Length;V_i++)
		{
			*(P_Data+V_i)=0x00;
		}
		return C_OK;
	}

	V_Dgree=V_Dgree-V_DI[0]+1;      /*����N�����ݣ������ҵ�ǰ(n-N+1)�ε�ַ*/

	if(DT_Flash_698EventTab!=V_Type)
	{
		SF_GetFlashAddr(V_Dgree,Str_3cTableAddr.V_StaFlashAddr,Str_3cTableAddr.V_DataToalLen,Str_3cTableAddr.V_EndFlashAddr,&P_FlashAddr1[0]);   /*��ȡ��ǰ����Flashҳ��ַ��ҳ�ڵ�ַ*/
	}
	else/*��2�����ѯ�У��Ѽ��������OAD�б��¼�����*/
	{
		SF_GetFlashAddr(V_Dgree,Str_3dEventTableAddr.V_StaFlashAddr,V_Data_Length,Str_3dEventTableAddr.V_EndFlashAddr,&P_FlashAddr1[0]);   /*��ȡ��ǰ����Flashҳ��ַ��ҳ�ڵ�ַ*/
	}

	if(DT_Flash_698EventTab!=V_Type)
	{
		PStr_4TableAddr=(Str_4Table *)(Str_3cTableAddr.PStr_4TableAddr);          /*ȡ4�����ַ*/
		if(0xFFFFFFFF!=((ulong32)PStr_4TableAddr))                             /*�����ʶ��*/
		{
			V_OffAddr=SF_GetOffAddr(PStr_4TableAddr,V_Data_Id,V_Type,Str_3cTableAddr.V_Str_4TableLen);         /*��4����ȡ����ƫ�Ƶ�ַ*/
			if(0xFFFF==V_OffAddr)   /*���ҳ���*/
			{
				return C_AbnormalError;    /*������������£��������*/
			}
		}
	}

	P_FlashAddr1[0]=P_FlashAddr1[0]+P_FlashAddr1[1]+V_OffAddr;                /*ȡ����Flash���Ե�ַ*/
	if(P_FlashAddr1[0]>C_Flash_Max_Addr)	                                    /*Flash��ַ�������۲�����*/
	{
		return C_AbnormalError;
	}

	if(C_Msg_Display==(V_WR_Mes&0x7F))
	{
		InF_FlashChipSelect();
		InF_ReadFlash(P_FlashAddr1[0],P_Data,V_Data_Length);
	}
	else
	{
		InF_FlashChipSelect();
		InF_ReadFlash(P_FlashAddr1[0],P_Data,V_Data_Length);
	}
	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Re_RAM_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_DI0)
������������RAM���ݣ�����CRC
���������
		uchar8 *P_RamAddr��������RAM��ַ��
		ushort16 V_DataLen�������ݳ���
		uchar8 V_DT_Type������������
		uchar8 V_DI0:���ݱ�ʾDI0�����ڶ�ʱ���ʽ�����ж�
���������uchar8 *P_Data�������ݻ���
���ز�����C_OK��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_Re_RAM_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_DI0)
{
	ushort16 V_i;
	uchar8 V_PowerState;
	uchar8 V_Temp[CLDate_Week_Time];	/*ssmmhhwwDDMMYY��ʽ*/

	if(DT_RAM_Time_Data==V_DT_Type)          /*��RAM����CRC��������ʱ���жϵ����־��*/
	{
		/*���ӵ����ж�,�е磬ֱ�Ӷ��ڲ�RAMʱ�䣬û�������ʱ�ӽӿں�����ˢ�����ݲ�*/
		V_PowerState=InF_ReadPowerState();     /*��ȡ��ǰ״̬*/
		if(C_PowerOn!=V_PowerState)
		{
			InF_ReadRTC(V_Temp, CLDate_Week_Time);
			PF_Data_Week_Time_BCDtoData_Time_s_HEX(V_Temp, GV_Date_Time);
		}

		switch(V_DI0)
		{
			case 0x01:    /*YYMMDDWW��*/
			{
				P_Data[0]=PF_Cal_Week_698(&GV_Date_Time[3]);/*YYMMDD���������ܴ�*/

				for(V_i=1;V_i<V_DataLen;V_i++)
				{
					*(P_Data+V_i)=GV_Date_Time[V_i+2];
				}
			}break;

			case 0x02:    /*hhmmss��*/
			case 0x00:    /*YYYYMMDDhhmmss��*/
			case 0xFD:    /*YYMMDDhhmmss��*/
			{
				for(V_i=0;V_i<V_DataLen;V_i++)
				{
					*(P_Data+V_i)=GV_Date_Time[V_i];
				}
			}break;

			default:
				return C_IDError;
		}
	}
	else
	{
		for(V_i=0;V_i<V_DataLen;V_i++)
		{
			*(P_Data+V_i)=*(P_RamAddr+V_i);
		}
	}

	return C_OK;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Re_RAMCRC_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data)
������������RAM���ݣ���CRC
���������
		uchar8 *P_RamAddr��������RAM��ַ��
		ushort16 V_DataLen�������ݳ���
���������uchar8 *P_Data�������ݻ���
���ز�����C_OK��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע��C_CrcErr_DataZeroʱ���ڲ��ж������Ƿ�Ϊȫ�㣬��Ϊȫ���򷵻�C_CRCError���������ݶԴ�����������
*********************************************************************************/
uchar8 SF_Re_RAMCRC_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data)
{
	ushort16 V_i,V_Len;
	uchar8 V_CRC_Flag;
	uchar8 PV_Data[C_RAM_Max];

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		return C_DataLenError;
	}

	V_Len=V_DataLen+C_CRCLen2;                            /*����CRC*/

	for(V_i=0;V_i<V_Len;V_i++)
	{
		PV_Data[V_i]=*(P_RamAddr+V_i);
	}

	V_CRC_Flag=PF_Check_CRC(&PV_Data[0],V_Len);

	V_Len=V_Len-C_CRCLen2;                                /*ȥ��CRC*/
	PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);

	if(C_OK==V_CRC_Flag)
	{
		return C_OK;
	}
	else
	{
		if(C_CrcErr_DataZero==V_CRC_Flag)        /*CRC��������Ϊȫ��*/
		{
			for(V_i=0;V_i<V_Len;V_i++)
			{
				if(0!=PV_Data[V_i])
				{
					break;
				}
			}

			if(V_i==V_Len)                        /*������ȷ*/
			{
				return C_CrcErr_DataZero;         /*����CRC���󣬵�����Ϊȫ��*/
			}
			else
			{
				return C_CRCError;
			}
		}
		else
		{
			return C_CRCError;
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_GetMinFreezePro_E2andFlashAddr(uchar8 V_ProNum,ulong32* P_FlashStAddr_LoadProfile,
			ulong32* P_FlashEndAddr_LoadProfile,ushort16* P_E2Addr_LoadP_Flash_Ear,ushort16* P_E2Addr_LoadP_Flash_Late)
������������ȡ���Ӷ��᷽���Ŷ�Ӧ�ļ�¼�飬��ʼ��������ַ
���������uchar8 V_ProNum:������0--7
���������
		ulong32* P_FlashStAddr_LoadProfile:���ظö��᷽������ʼ��ַ
		ulong32* P_FlashEndAddr_LoadProfile:���ظö��᷽����������ַ
		ushort16* P_E2Addr_LoadP_Flash_Ear:��������1�μ�¼Flash��ַ����E2��ַ
		ushort16* P_E2Addr_LoadP_Flash_Late:���1�μ�¼Flash��ַ����E2��ַ
���ز�����C_OK��C_SPIError��C_DataLenError��C_NoAccess��C_Error(���ݸ�ʽ��)��C_SafeFlagError��C_IICError��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_GetMinFreezePro_E2andFlashAddr(uchar8 V_ProNum,ulong32 *P_FlashStAddr_LoadProfile,ulong32 *P_FlashEndAddr_LoadProfile,ushort16 *P_E2Addr_LoadP_Flash_Ear,ushort16 *P_E2Addr_LoadP_Flash_Late)
{
	uchar8 V_Return_Flag=C_Error;
	uchar8 Vu_FlashAddr[64]={0xFF};

	if(V_ProNum>7)	/*������*/
	{
		return V_Return_Flag;
	}

	V_Return_Flag=SF_ReadE2Three(E2Addr_Min_Free_FlashAddr_Allo,64,&Vu_FlashAddr[0]);	/*��ȡ��ͬ����������ʼ��������ַ*/
	if(C_OK==V_Return_Flag)
	{
		PF_Buffer4ToUlong32(&Vu_FlashAddr[V_ProNum*8],P_FlashStAddr_LoadProfile,4);
		PF_Buffer4ToUlong32(&Vu_FlashAddr[V_ProNum*8+4],P_FlashEndAddr_LoadProfile,4);
	}
	*P_E2Addr_LoadP_Flash_Ear=E2Addr_Min_Free_Flash_Ear1+V_ProNum*12;
	*P_E2Addr_LoadP_Flash_Late=*P_E2Addr_LoadP_Flash_Ear+6;
	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Write698FreezeData(uchar8 V_DI2,uchar8 Message_Num,uchar8 *P_Data,ushort16 V_Data_Length)
����������д�����¼
���������
		uchar8 V_DI2:DI2��ʾĳ�ඳ�����ݣ����Ӷ����3λ��ʾ������
		uchar8 Msg_Num:��Ϣ�ţ������ж��Ƿ���дȨ�ޣ�
		uchar8 *P_Data���������Ż��棻
		ushort16 V_Data_Length����д���ݳ��ȣ�
�����������
���ز�����C_OK��C_SPIError��C_DataLenError��C_NoAccess��C_Error(���ݸ�ʽ��)��C_SafeFlagError��C_IICError��
����˵����
���û��ƣ�
��     ע��ע��д�����ݳ���
*********************************************************************************/
uchar8 SF_Write698FreezeData(uchar8 V_DI2Temp, uchar8 Message_Num, uchar8 *P_Data, ushort16 V_Data_Length)
{
	uchar8 V_i,V_Mode;
	ulong32 V_WR_FlashAddr[2];
	uchar8 V_Return_Flag;
	uchar8 V_FlashAddr8[4],V_DI2;
	ulong32 V_FlashAddrEar;
	ushort16 V_Len;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear;
	ulong32 V_FlashStAddr_LoadProfile,V_FlashEndAddr_LoadProfile;
	ulong32 V_Flash_Page;

	GV_D_SafeFlag=C_Clear_SafeFlag;

	V_DI2=(V_DI2Temp&0x1F);		/*ȥ��������*/

	if(C_Msg_Freeze!=Message_Num)
	{
		return C_NoAccess;
	}

	GV_D_SafeFlag=C_W_SafeFlag_1|GV_D_SafeFlag;

	V_Len=SF_JudgeWriteDataLen(V_DI2Temp);	                     /*����д�������ܳ���*/
	if((V_Data_Length!=V_Len)||(0==V_Len))
	{
		return C_DataLenError;
	}

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;

	for(V_i=0;V_i<Str_698FreezeDataTable_Len;V_i++)
	{
		if(V_DI2==Str_698FreezeDataTable[V_i].V_DI2)
		{
			break;
		}
	}

	if(V_i>=Str_698FreezeDataTable_Len)
	{
		return C_Error;
	}

	V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_i].V_E2AddrLate;
	V_E2Addr_LoadP_Flash_Ear=Str_698FreezeDataTable[V_i].V_E2AddrEar;
	V_FlashStAddr_LoadProfile=Str_698FreezeDataTable[V_i].V_StaFlashAddr;
	V_FlashEndAddr_LoadProfile=Str_698FreezeDataTable[V_i].V_EndFlashAddr;

	if(V_DI2==(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16))/*���Ӷ���,���ݷ����Ż�ȡ����E2��Flash��ַ*/
	{
		V_Return_Flag=SF_GetMinFreezePro_E2andFlashAddr((V_DI2Temp>>5),&V_FlashStAddr_LoadProfile,&V_FlashEndAddr_LoadProfile,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*���ݷ��Ӷ��᷽���ţ���ȡ�÷�������������¼E2��ַ���÷�����ʼ������Flash��ַ*/
		if(C_OK!=V_Return_Flag)
		{
			return V_Return_Flag;
		}
	}

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;

	SF_GetCurrLoadProfileFlashAddr(V_Len,&V_WR_FlashAddr[0],V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear,V_FlashStAddr_LoadProfile,V_FlashEndAddr_LoadProfile);     /*���㵱ǰҪд������Flash��ַ,Ŀǰ�޸�Ϊ�����¼��ַV_WR_FlashAddr[1]*/
	if(V_WR_FlashAddr[1]==0xFFFFFFFF)/*�쳣*/
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_Error;
	}

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}

	V_Flash_Page=V_WR_FlashAddr[0]%C_OneFlashPage;            /*�ж�д������Flash��ַ�Ƿ�Ϊÿҳ�׵�ַ,�Ƿ��ҳ*/
	if(0==V_Flash_Page)/*��ҳFlash��һ��д�룬д68��¼��־*/
	{
		V_Mode=C_Flash_Empty68;
		V_Return_Flag=SF_WriteFlash(V_WR_FlashAddr[0],&V_Mode,1,1);               /**д���¼ģʽ��*/
		if(C_OK!=V_Return_Flag)
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}
	}

	V_Return_Flag=SF_WriteFlash(V_WR_FlashAddr[1],&P_Data[0],V_Len,1);       /**д���¼����*/
	if(C_OK!=V_Return_Flag)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return V_Return_Flag;
	}

	V_Flash_Page=(V_WR_FlashAddr[0]%C_OneFlashPage);            /*�ж�д������Flash��ַ�Ƿ�Ϊÿҳ�׵�ַ,�Ƿ��ҳ*/

	V_Return_Flag = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);         /*ȡ����1����¼Flash��ַ*/
	if(C_OK!=V_Return_Flag)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);

	if((V_FlashStAddr_LoadProfile==V_WR_FlashAddr[0])&&(V_FlashStAddr_LoadProfile==V_FlashAddrEar))            /*���ɼ�¼Flash��ҳ*/
	{
		PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_WR_FlashAddr[1],4);   /*�����¼��1��д��*/
		V_Return_Flag=SF_WriteE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);   /*���������¼Flash��ַ��E2*/
	}

	if(0==V_Flash_Page)   /*��ҳ�����������¼Flash*/
	{
		PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_WR_FlashAddr[0],4);
		V_Return_Flag=SF_WriteE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);   /*���������¼Flash��ַ��E2*/
		SF_EarlistLoadProfileFlashAddrAdjust(V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear,V_FlashStAddr_LoadProfile,V_FlashEndAddr_LoadProfile);                 /*Flash��¼�������¼ҳ��������*/
	}

	GV_D_SafeFlag=C_Clear_SafeFlag;
	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�ushort16 SF_GetMinFreezeNum_OADTab(uchar8 V_ProNum,uchar8 *P_DataOAD_NumTab,ushort16 V_OADTabLen_T)
������������ȡ���Ӷ��᷽���Ŷ�Ӧ��OAD�����б�
���������
		*uchar8 V_ProNum:���Ӷ���ĳ�෽����0--7
		uchar8 *P_DataOAD_NumTab:����Ϊ���Ӷ���OAD�����б�
		ushort16 V_OADTabLen_T:���Ӷ���OAD�����б��ܳ���
���������uchar8 *P_DataOAD_NumTab:���Ϊ���Ӷ��᷽���Ŷ�Ӧ��OAD�����б�
���ز��������Ӷ��᷽���Ŷ�Ӧ�Ĺ����б�OAD�������쳣����0xFFFF
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
ushort16 SF_GetMinFreezeNum_OADTab(uchar8 V_ProNum,uchar8 *P_Data,ushort16 V_DataLen)
{
	ushort16 V_MinOADTabLen_T=0xFFFF;
	uchar8 V_j,V_k,V_m,V_Num;
	ushort16 V_Cyc16[8]={0xFFFF},V_OADOrder16;

	if(V_ProNum>7)
	{
		return V_MinOADTabLen_T;
	}

	V_Num=SF_GetMinFreezeTolNum(P_Data,V_DataLen,&V_Cyc16[0]);/*��ȡ�ܷ���������Ӧ�Ĳ�ͬ��������*/
	if(V_Num>8)/*�쳣*/
	{
		return V_MinOADTabLen_T;
	}

	V_j=V_DataLen/C_698Free_OADTabDataType;/*OAD�б����*/

	V_m=0;
	for(V_k=0;V_k<V_j;V_k++)
	{
		PF_Buffer2ToUshort16(&P_Data[C_698Free_OADTabDataType*V_k+2],&V_OADOrder16);/*��ȡ����OAD����*/
		if(V_Cyc16[V_ProNum]==V_OADOrder16)/*�������,����Ϊ��ͬ����*/
		{
			PF_CopyDataBytes(&P_Data[C_698Free_OADTabDataType*V_k],&P_Data[C_698Free_OADTabDataType*V_m],C_698Free_OADTabDataType);
			V_m++;
		}
	}

	V_MinOADTabLen_T=V_m;

	return V_MinOADTabLen_T;
}

/*********************************************************************************
����ԭ�ͣ�ushort16 SF_JudgeWriteDataLen(uchar8 V_DI2)
��������������ĳ�ඳ�ᣬ��ϸö�OAD����ű�����������¼�����ݳ���(������¼���)
���������uchar8 V_DI2:ĳ�ඳ�᣻��Ϊ���Ӷ���ʱ����3λ��ʾ��ͬ������
���������ushort16 V_Data_Length�����ඳ�����ݳ��ȣ�
���ز������ޣ�
����˵����
���û��ƣ�
��     ע���쳣����0
*********************************************************************************/
ushort16 SF_JudgeWriteDataLen(uchar8 V_DI2Temp)
{
	ushort16 V_Data_Length;
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADOrder16,V_i;
	uchar8 V_Return_Flag,V_DI2;
	Str_3aTable V_Str_3aTable;

	V_Data_Length=0;
	V_DI2=(V_DI2Temp&0x1F);/*ȥ��������*/

	for(V_i=0;V_i<Str_698FreezeDataTable_Len;V_i++)
	{
		if(V_DI2==Str_698FreezeDataTable[V_i].V_DI2)
		{
			break;
		}
	}

	if(V_i<Str_698FreezeDataTable_Len)
	{
		V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;/*698���᳤�ȡ���������������Str_3aTable�к�*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return V_Data_Length;/*�쳣*/
		}

		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
		if(C_OK==V_Return_Flag)
		{
			V_OADTabLen_T=P_OADTabLen_T[0];
			V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*��ű�ÿ��OAD���C_698Free_OADTabDataType���ֽ�,Ŀǰ6�ֽڡ�2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/
			if(V_OADTabLen_T >= C_698Free_OADTabLen)		/*���ݳ��Ȱ�ȫ���ж�*/
			{
				return V_Data_Length;	/*�쳣*/
			}

			V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;/*698������ű�����Str_3aTable�к�*/
			if(V_Order >= Str_3aTable_E23RAM_Len)
			{
				return V_Data_Length;	/*�쳣*/
			}

			V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
			V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);
			if(C_OK!=V_Return_Flag)
			{
				return V_Data_Length;	/*�쳣*/
			}

			if(V_DI2==(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16))/*���Ӷ���*/
			{
				V_OADTabLen_T=SF_GetMinFreezeNum_OADTab((V_DI2Temp>>5),&P_DataOAD_NumTab[0],V_OADTabLen_T);/*��ȡ���Ӷ��᷽���ţ���Ӧ��OAD�����б�����OAD����*/
				if(0xFFFF==V_OADTabLen_T)
				{
					return V_Data_Length;	/*�쳣*/
				}
			}
			else
			{
				V_OADTabLen_T=V_OADTabLen_T/C_698Free_OADTabDataType;
			}

			V_Data_Length=C_698FreeData_SequenceLen4+C_698FreeData_DateLen6;/*698����������ų���+6 YMDhms*/
			for(V_i=0;V_i<V_OADTabLen_T;V_i++)
			{
				PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType*V_i],&V_OADOrder16);
				V_OADOrder16 &= 0x1FFF;
				if(V_OADOrder16 >= Str_FrozenConvert_Table_Len)
				{
					return 0;	/*�쳣*/
				}
				V_Data_Length=V_Data_Length+Str_FrozenConvert_Table[V_OADOrder16].V_uc645Length;
			}
		}
	}

	return V_Data_Length;
}

/*********************************************************************************
����ԭ�ͣ�void SF_GetCurrLoadProfileFlashAddr(ushort16 V_Len,ulong32 *V_W_FlashAddr,ushort16 V_E2Addr_LoadP_Flash_Late,
					ushort16 V_E2Addr_LoadP_Flash_Ear,ulong32 V_FlashStAddr_LoadProfile,ulong32 V_FlashEndAddr_LoadProfile)
�������������㵱ǰҪд��Flash���ݵ�ַ
���������
		ushort16 V_Len��Ҫд�븺�ɼ�¼�鳤�ȣ�
		ushort16 V_E2Addr_LoadP_Flash_Late:Ҫ������¼���1�μ�¼Flash��ַ����E2��ַ
		ushort16 V_E2Addr_LoadP_Flash_Ear:Ҫ������¼����1�μ�¼Flash��ַ����E2��ַ
		ulong32 V_FlashStAddr_LoadProfile:Ҫ������¼Flash��ʼ��ַ
		ulong32 V_FlashEndAddr_LoadProfile:Ҫ������¼Flash������ַ
���������
ulong32 *V_W_FlashAddr����ǰҪд���¼����Flash��ַ��V_W_FlashAddr[1]��Ϊ��¼���ݵ�ַ��V_W_FlashAddr[0]������ҳΪ��1��д��ʱ��
		V_W_FlashAddr[0]��Ϊ��ҳ��ַ���ǵ�һ��д��ʱ����ͬV_W_FlashAddr[1]��

���ز������ޣ�
����˵����
���û��ƣ�
��     ע����V_W_FlashAddr[0]��ΪȫFFʱ��˵�������쳣
*********************************************************************************/
void SF_GetCurrLoadProfileFlashAddr(ushort16 V_Len,ulong32 *V_W_FlashAddr,ushort16 V_E2Addr_LoadP_Flash_Late,ushort16 V_E2Addr_LoadP_Flash_Ear,ulong32 V_FlashStAddr_LoadProfile,ulong32 V_FlashEndAddr_LoadProfile)
{
	uchar8 V_i;
	ulong32 V_FlashAddr32,V_FlashAddr;
	uchar8 V_FlashAddr8[4];
	uchar8 V_Mode[C_LoadProfile_RevMode],V_Date[C_698FreeData_DateLen6];
	uchar8 V_ucReturn;
	ulong32 V_FlashAddr32Temp;

	V_W_FlashAddr[1]=0xFFFFFFFF;
	V_W_FlashAddr[0]=0xFFFFFFFF;

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*ȡ���1����¼Flashҳ��ַ*/
	if(V_ucReturn != C_OK)
	{
		return;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddr32,4);
	V_FlashAddr32&=0xFFFFF000;             /*ҳ��ַת���������ݴ���*/

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);        /*ȡ����1����¼Flashҳ��ַ*/
	if(V_ucReturn != C_OK)
	{
		return;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddr,4);

	if((V_FlashStAddr_LoadProfile==V_FlashAddr)&&(V_FlashAddr32==V_FlashAddr)) /*��1�μ�¼*/
	{
		V_W_FlashAddr[0]=V_FlashStAddr_LoadProfile;
		V_W_FlashAddr[1]=V_FlashStAddr_LoadProfile+C_LoadProfile_RevMode;
		return;
	}

	InF_FlashChipSelect();
	InF_ReadFlash(V_FlashAddr32,&V_Mode[0],C_LoadProfile_RevMode);     /*ȡҳ���Ƿ���ʱ�������־*/
	if(0x68!=V_Mode[C_LoadProfile_RevMode-1]) /*��ҳ�м�¼д�ñ�־Ϊ68����ҳ��¼ʱ���е�������д��68��־��ͬʱ����Ч��¼6�ֽ�YMDhmsдΪFF�����ײ�д0����˵����ҳ��¼ʱ���е���,ȡ��1ҳ*/
	{
		if(V_FlashEndAddr_LoadProfile==V_FlashAddr32)                      /*��ǰҳΪ��¼���1ҳ,����Ϊ��ҳ*/
		{
			V_W_FlashAddr[0]=V_FlashStAddr_LoadProfile;
			V_W_FlashAddr[1]=V_W_FlashAddr[0]+C_LoadProfile_RevMode;
			return;
		}
		else
		{
			V_W_FlashAddr[0]=V_FlashAddr32+C_OneFlashPage;                /*����Ϊ��1ҳ*/
			V_W_FlashAddr[1]=V_W_FlashAddr[0]+C_LoadProfile_RevMode;
			return;
		}
	}

	V_FlashAddr32Temp=C_LoadProfile_RevMode;      /*���1����¼��ҳ��1����¼��ַ*/

	while(V_FlashAddr32Temp<=C_OneFlash_PageNum)/*�ж�ʣ��ռ��Ƿ�����*/
	{
		InF_FlashChipSelect();
		InF_ReadFlash((V_FlashAddr32Temp+V_FlashAddr32),&V_Date[0],C_698FreeData_DateLen6);     /*��ȡÿ����¼ǰ6���ֽڣ�������¼ΪYMDhms*/
		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(0x00!=V_Date[V_i])/*�м�¼����*/
			{
				break;
			}
		}

		if(V_i<C_698FreeData_DateLen6)/*�м�¼����*/
		{
			V_FlashAddr32Temp=V_FlashAddr32Temp+V_Len;/*ȡ������¼��ַ*/
		}
		else/*�ռ�¼*/
		{
			if((V_FlashAddr32Temp+V_Len)<=C_OneFlash_PageNum)
			{
				V_W_FlashAddr[1]=V_FlashAddr32Temp+V_FlashAddr32;
				V_W_FlashAddr[0]=V_W_FlashAddr[1];
				return;
			}
			else
			{
				break;
			}
		}
	}

	if(V_FlashEndAddr_LoadProfile==V_FlashAddr32)/*ʣ��ռ䲻���㣬����Ϊ��1ҳ����ǰҳΪ���ɼ�¼���1ҳ,����Ϊ��ҳ*/
	{
		V_W_FlashAddr[0]=V_FlashStAddr_LoadProfile;
		V_W_FlashAddr[1]=V_W_FlashAddr[0]+C_LoadProfile_RevMode;
		return;
	}
	else
	{
		V_W_FlashAddr[0]=V_FlashAddr32+C_OneFlashPage;                /*����Ϊ��1ҳ*/
		V_W_FlashAddr[1]=V_W_FlashAddr[0]+C_LoadProfile_RevMode;
		return;
	}
}

/*********************************************************************************
����ԭ�ͣ�void SF_EarlistLoadProfileFlashAddrAdjust(ushort16 V_E2Addr_LoadP_Flash_Late,ushort16 V_E2Addr_LoadP_Flash_Ear,
													ulong32 V_FlashStAddr_LoadProfile,ulong32 V_FlashEndAddr_LoadProfile);
�����������������縺�ɼ�¼Flashҳ��ַ
���������
ushort16 V_E2Addr_LoadP_Flash_Late:Ҫ������¼���1�μ�¼Flash��ַ����E2��ַ
ushort16 V_E2Addr_LoadP_Flash_Ear:Ҫ������¼����1�μ�¼Flash��ַ����E2��ַ
ulong32 V_FlashStAddr_LoadProfile:Ҫ������¼Flash��ʼ��ַ
ulong32 V_FlashEndAddr_LoadProfile:Ҫ������¼Flash������ַ
�����������
���ز������ޣ�
����˵����
���û��ƣ�
��     ע������ǰ�����а�ȫ��־����Ѳ�������У����ɼ�¼����ֱ���жϲ���
*********************************************************************************/
void SF_EarlistLoadProfileFlashAddrAdjust(ushort16 V_E2Addr_LoadP_Flash_Late,ushort16 V_E2Addr_LoadP_Flash_Ear,ulong32 V_FlashStAddr_LoadProfile,ulong32 V_FlashEndAddr_LoadProfile)
{
	ulong32 V_FlashAddrLate,V_FlashAddrEar,V_FlashAddr;
	uchar8 V_FlashAddr8[4];
	uchar8 V_ucReturn;

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*ȡ���1����¼Flashҳ��ַ*/
	if(V_ucReturn != C_OK)
	{
		return;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
	V_FlashAddrLate&=0xFFFFF000;             /*ҳ��ַת���������ݴ���*/

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);         /*ȡ����1����¼Flash��ַ*/
	if(V_ucReturn != C_OK)
	{
		return;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);
	if(V_FlashEndAddr_LoadProfile==V_FlashAddrLate)
	{
		if(V_FlashStAddr_LoadProfile==(V_FlashAddrEar-C_LoadProfile_RevMode))    /*Flash���Ե�ַ*/                    /*���������¼Flash��ַ*/
		{
			V_FlashAddrEar=V_FlashAddrEar+C_OneFlashPage;
			PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_FlashAddrEar,4);
			SF_WriteE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);   /*���������¼Flash��ַ��E2*/
		}
	}
	else
	{
		V_FlashAddr=V_FlashAddrEar-V_FlashAddrLate-C_LoadProfile_RevMode;
		if(C_OneFlashPage==V_FlashAddr)                                 /*�������1ҳ��1��ѭ��*/
		{
			if(V_FlashEndAddr_LoadProfile==(V_FlashAddrEar-C_LoadProfile_RevMode))                      /*��ǰҳΪ��¼���1ҳ,����Ϊ��ҳ*/
			{
				V_FlashAddrEar=V_FlashStAddr_LoadProfile+C_LoadProfile_RevMode;      /*Flash���Ե�ַ*/
			}
			else
			{
				V_FlashAddrEar=V_FlashAddrEar+C_OneFlashPage;      /*����Ϊ��1ҳ��Flash���Ե�ַ*/
			}

			PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_FlashAddrEar,4);
			SF_WriteE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);   /*���������¼Flash��ַ��E2*/
		}
	}
}
#if 0
/*********************************************************************************
����ԭ�ͣ�uchar8 InF_Read_Data_For_Dis(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length)
���������������ݲ�ӿں���,ר��������ʾģ�飬�������Ϊ6+4��ͨ�ö����ݽӿں��������ݳ���ΪĬ��645���ȣ�6+2��
���������
ulong32 V_ulData_Id �����ݱ�ʶ�룻
uchar8 *pV_ucData ���������Ż��棻
uchar8 *pV_usData_Length ����Ϊ�������ʱ���ò���ֵΪģ���������ݻ��泤�����ֵ���������ݲ��жϣ��������ݳ��ȣ�
�Ƿ������������򷵻����ݳ��ȴ��󡣵���Ϊ�������ʱ�����ݲ㷵������ȡ���ݳ��ȡ�
���������
ushort16 *pV_usData_Length �����ݲ㷵������ȡ���ݳ��ȡ�
uchar8 *pV_ucData:���������������
���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_NoAccess��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע��ע�����ݳ���,��ͨ��InF_Read_Data������ȣ�ֻ�н��������ͬ����ʾ�������Ϊ4λС��
*********************************************************************************/
uchar8 InF_Read_Data_For_Dis(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length)
{
	uchar8 V_Return_Flag;
	uchar8 V_MesNum;
	ushort16 V_usDataEncode;

	if(SF_Read_698SpecialData(V_ulData_Id, pV_ucData, pV_usData_Length, &V_usDataEncode) == C_OK)
	{
		return C_OK;
	}

	V_MesNum = (C_Read_Data|C_Msg_Display);        /*������ʾ��*/
	V_Return_Flag = SF_Read_Data(V_ulData_Id, pV_ucData, pV_usData_Length, V_MesNum, &V_usDataEncode);

	return V_Return_Flag;
}
#endif
/*********************************************************************************
����ԭ�ͣ�void SF_EEAndRAMCheckAndRecover(ushort16 V_E2BakeUp1Addr,uchar8 *V_RamAddr)
��������:��Ҫ���ݣ�RAM��EE����CRCУ�飬RAM����CRC����ȷ����EE���ݲ�һ��ʱ����EE���ݻָ�RAM
���������V_usE2BakeUp1Addr��EE��ַ��
P_ucRamAddr:RAM��ַ
V_ucDataLen:���ݳ���
�����������
���ز�������
����˵����
���û��ƣ�SF_ImportantDataCheckAndRecover����1���ϵ��ʼ��2�����ݲ�Ѳ��5s
��     ע����Ҫ��������������峣��.
*********************************************************************************/
void SF_EEAndRAMCheckAndRecover(ushort16 V_usE2BakeUp1Addr, uchar8 *P_ucRamAddr, uchar8 V_ucDataLen)
{
	uchar8 V_ucE2DataFlag, V_ucRamDataFlag, V_ucComDataFlag;
	uchar8 PV_E2Data[30];

	if((V_ucDataLen+C_CRCLen2)>30)
	{
		return;
	}

	V_ucE2DataFlag = SF_ReadE2Three_AndCRC(V_usE2BakeUp1Addr, V_ucDataLen, PV_E2Data);
	V_ucRamDataFlag = PF_Check_CRC(P_ucRamAddr, (V_ucDataLen + C_CRCLen2));/*�ж�RAM CRC*/

	if(V_ucRamDataFlag != C_OK)
	{
		if(V_ucE2DataFlag == C_OK)/*EE���ݸ���RAM*/
		{
			PF_CopyDataBytes(PV_E2Data,P_ucRamAddr,(V_ucDataLen + C_CRCLen2));
		}/*else,EE����CRC����ȷ��������*/
	}
	else
	{
		if(V_ucE2DataFlag == C_OK)
		{
			V_ucComDataFlag = PF_Campare_Data(P_ucRamAddr,PV_E2Data,V_ucDataLen);
			if(V_ucComDataFlag != C_Equal)
			{
				PF_CopyDataBytes(PV_E2Data,P_ucRamAddr,(V_ucDataLen + C_CRCLen2));
			}/*else,EE���ݺ�RAM������ͬ��������*/
		}/*else,EE����CRC����ȷ��������*/
	}
}
/**********************************************************************************
����ԭ�ͣ�void SF_ImportantDataCheckAndRecover(void)
��������:��Ҫ����У�鼰�ָ�
�����������
�����������
���ز�������
����˵����
���û��ƣ�1���ϵ��ʼ��2�����ݲ�Ѳ��5s
��     ע����Ҫ��������������峣��
**********************************************************************************/
void SF_ImportantDataCheckAndRecover(void)
{
	/*���峣��*/
	SF_EEAndRAMCheckAndRecover(E2Addr_Pulse_Constant, GV_Pulse_Constant, CLPulse_Constant);
}
/*********************************************************************************
����ԭ�ͣ�void InF_PowerOn_CurrEnergyDeal(void)
�����������ϵ��������ӿں���,���ȵ��á������ж�����������Ϊ׼
�����������
�����������
���ز�������
����˵����
���û��ƣ������ϵ�ʱ����Դ�ȶ������
��ע�����������������RAM�ж��Ƿ���ȣ������(������ʵʱ�洢������RAM����������������)��
�жϵ����Ƿ����Ȼ��д��ÿ���ж�һ���������ж������ĺ����ԡ�
����ʣ���͸֧���ֻ�жϽ���С�ĺ����ԣ�û���ж���ֵ
�����ϵ�İ�ȫ�ԣ��ú�������RAM�������紦����20min��������������E2����
(Ŀǰ��ǰ����ֱ�Ӹ���RAM�����磬������20min���ܱ��洦��)��
����ֻ����RAM����CRC����ȷ�������쳣ʱ����E2����RAM.��E2CRC����ʱ��RAMCRC��ȷҲ������E2
*********************************************************************************/
void InF_PowerOn_CurrEnergyDeal(void)
{
	uchar8 V_E2DataFlag,V_RamDataFlag,V_i,V_j;
	uchar8 PV_E2Data[C_CurrDataLen5];
	ulong64 V_RamEnData,V_E2EnData;
	ushort16 V_CRC16;
	uchar8 PV_CRC8[C_CRCLen2];
	long64 V_EnDataAdd;
	uchar8 V_DataType;

	GV_D_SafeFlag=C_Clear_SafeFlag;
	V_E2DataFlag=C_CRCError;
	V_RamDataFlag=C_CRCError;

	GV_D_SafeFlag=GV_D_SafeFlag|C_W_SafeFlag_1;

	V_j=C_CurrDataLen5+C_CRCLen2;
	for(V_i=0;V_i<C_CurrEnergy_Len;V_i++)
	{
		V_E2DataFlag=SF_ReadFRAMThree((E2Addr_CurrEnergy_St+V_j*V_i),C_CurrDataLen5,&PV_E2Data[0]);   /*��E2����,�ڲ��ж�CRC*/
		V_RamDataFlag=PF_Check_CRC(&GV_CurrEnergyData[V_i][0],(C_CRCLen2+C_CurrDataLen5));          /*�ж�RAM CRC*/
		if((C_OK==V_RamDataFlag)||(C_CrcErr_DataZero==V_RamDataFlag))
		{
			PF_Buffer8ToUlong64(&GV_CurrEnergyData[V_i][0],&V_RamEnData,C_CurrDataLen5);
		}

		GV_D_SafeFlag=GV_D_SafeFlag|C_W_SafeFlag_2;

		if((C_OK==V_E2DataFlag)||(C_CrcErr_DataZero==V_E2DataFlag))
		{
			PF_Buffer8ToUlong64(&PV_E2Data[0],&V_E2EnData,C_CurrDataLen5);
		}

		GV_D_SafeFlag=GV_D_SafeFlag|C_W_SafeFlag_3;

		if((C_OK==V_E2DataFlag)||(C_CrcErr_DataZero==V_E2DataFlag))   /*E2������ȷ*/
		{
			if((C_OK==V_RamDataFlag)||(C_CrcErr_DataZero==V_RamDataFlag))    /*�жϵ��������ĺ�����*/
			{
				V_EnDataAdd=V_RamEnData-V_E2EnData;                           /*��������*/
				if(0==V_EnDataAdd)
				{
					continue;                             /*��������ѭ��*/
				}
				else     /*��������*/
				{
					if(V_i == C_ChargeBal_offset_InGV)   /*ʣ����,����E2>=RAM������==RAM���ݡ�CRC����ȫ�㣬Ҳ��Ϊ���󵥶��ж�*/
					{
						V_DataType=SF_AllDataZero_Judge(&GV_CurrEnergyData[V_i][0],(C_CurrDataLen5+C_CRCLen2));/*�����Ƿ�Ϊȫ���жϣ�����CRC*/
						if((V_EnDataAdd!=0)||(C_OK==V_DataType))       /*RAM�����쳣*/
						{
							V_RamEnData=V_E2EnData;                  /*E2����RAM����*/

							if(C_W_SafeFlag!=GV_D_SafeFlag)
							{
								return;
							}

							PF_Ulong64ToBuffer8(&GV_CurrEnergyData[V_i][0],&V_RamEnData,C_CurrDataLen5);
							V_CRC16=PF_Cal_CRC(&GV_CurrEnergyData[V_i][0],C_CurrDataLen5);          /*����CRC*/
							PF_Ushort16ToBuffer2(&PV_CRC8[0],&V_CRC16);
							GV_CurrEnergyData[V_i][C_CurrDataLen5]=PV_CRC8[0];
							GV_CurrEnergyData[V_i][C_CurrDataLen5+1]=PV_CRC8[1];
						}
					}
					else                           /*���������ݱȽ�*/
					{
						if(V_RamEnData!=V_E2EnData) /*RAM�������������ʵʱˢ�£�����RAM����������������*/
						{
							V_RamEnData=V_E2EnData;                  /*E2����RAM����*/

							if(C_W_SafeFlag!=GV_D_SafeFlag)
							{
								return;
							}

							PF_Ulong64ToBuffer8(&GV_CurrEnergyData[V_i][0],&V_RamEnData,C_CurrDataLen5);
							V_CRC16=PF_Cal_CRC(&GV_CurrEnergyData[V_i][0],C_CurrDataLen5);          /*����CRC*/
							PF_Ushort16ToBuffer2(&PV_CRC8[0],&V_CRC16);
							GV_CurrEnergyData[V_i][C_CurrDataLen5]=PV_CRC8[0];
							GV_CurrEnergyData[V_i][C_CurrDataLen5+1]=PV_CRC8[1];
						}
					}
				}
			}
			else                 /*RAM CRC����E2����RAM*/
			{
				V_RamEnData=V_E2EnData;                  /*E2����RAM����*/

				if(C_W_SafeFlag!=GV_D_SafeFlag)
				{
					return;
				}

				PF_Ulong64ToBuffer8(&GV_CurrEnergyData[V_i][0],&V_RamEnData,C_CurrDataLen5);
				V_CRC16=PF_Cal_CRC(&GV_CurrEnergyData[V_i][0],C_CurrDataLen5);          /*����CRC*/
				PF_Ushort16ToBuffer2(&PV_CRC8[0],&V_CRC16);
				GV_CurrEnergyData[V_i][C_CurrDataLen5]=PV_CRC8[0];
				GV_CurrEnergyData[V_i][C_CurrDataLen5+1]=PV_CRC8[1];
			}
		}
		else                 /*E2���ݴ���*/
		{
			continue;
		}
	}

	SF_Deal_UpdataFlag(C_Updata_Init, PV_E2Data, 0);		/*��ʼ������*/

	GV_D_SafeFlag=C_Clear_SafeFlag;
	/*��Ҫ���ݶ�ʱУ��*/
	SF_ImportantDataCheckAndRecover();
}
/*********************************************************************************
����ԭ�ͣ�void InF_ChangeTime_LoadProfileCover(void)
�����������޸�ʱ�为�ɼ�¼���ǽӿں���,ͨ�ŵ��á�Ŀǰ���ڶ������ݸ��ǣ��������ӡ�Сʱ���ա��¶��ᣬ�ڲ�����
�����������
�����������
���ز�������
����˵����
���û��ƣ���ǰ�޸�ʱ��ʱ��ͨ�ŵ��øýӿں���
��     ע��
*********************************************************************************/
void InF_ChangeTime_LoadProfileCover(void)
{
	ulong32 V_FlashAddrLate,V_FlashAddrEar;
	uchar8 V_FlashAddr8[4],V_Return_Flag,V_i,V_j;
	uchar8 V_Data_TimeSys[C_698FreeData_DateLen6],V_Data_TimeNote[C_698FreeData_DateLen6];
	ulong32 V_FlashAddr,C_FlashStAddr_LoadProfile,C_FlashEndAddr_LoadProfile;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear;
	uchar8 V_DI2,V_ProNum,V_m = 0xFF;

	V_DI2=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);

	V_ProNum=InF_GetMinFreezeTolNum();/*��ȡ���Ӷ����ܷ�����*/
	if(V_ProNum>8)/*1-8*/
	{
		V_ProNum=0;
	}

	for(V_i=0;V_i<(C_698FixTimeFreeze+V_ProNum);V_i++)/*ѭ�������¼��ֻ���ꡢ�¡��ա�ʱ���ָ��ǣ�ע����˳��*/
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;

		if(V_i<C_698FixTimeFreeze)
		{
			V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_i].V_E2AddrLate;
			V_E2Addr_LoadP_Flash_Ear=Str_698FreezeDataTable[V_i].V_E2AddrEar;
			C_FlashStAddr_LoadProfile=Str_698FreezeDataTable[V_i].V_StaFlashAddr;
			if(V_DI2==Str_698FreezeDataTable[V_i].V_DI2)/*���Ӷ���*/
			{
				V_m=V_i;
				continue;
			}
		}
		else/*���Ӷ��ᴦ��*/
		{
			V_Return_Flag=SF_GetMinFreezePro_E2andFlashAddr((V_i-C_698FixTimeFreeze),&C_FlashStAddr_LoadProfile,&C_FlashEndAddr_LoadProfile,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*���ݷ��Ӷ��᷽���ţ���ȡ�÷�������������¼E2��ַ���÷�����ʼ������Flash��ַ*/
			if(C_OK!=V_Return_Flag)
			{
				continue;
			}
		}

		V_Return_Flag=SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*ȡ���1����¼Flashҳ��ַ*/
		PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
		V_FlashAddrLate&=0xFFFFF000;             /*ҳ��ַת���������ݴ���*/

		V_Return_Flag=SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);         /*ȡ����1����¼Flash��ַ*/
		PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);
		if(C_OK!=V_Return_Flag)
		{
			continue;
		}

		GV_D_SafeFlag|=C_W_SafeFlag_1;

		for(V_j=0;V_j<C_698FreeData_DateLen6;V_j++)            /*ȡϵͳ��ǰʱ������,YYYYMMDDhhmmss*/
		{
			V_Data_TimeSys[V_j]=GV_Date_Time[V_j];     /*ȥ��YY*/
		}

		if(C_FlashStAddr_LoadProfile==V_FlashAddrEar)  /*���ඳ�ᣬû�м�¼����*/
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			continue;
		}

		if(V_i>=C_698FixTimeFreeze)/*���Ӷ����¼*/
		{
			V_FlashAddr=SF_GetFixedLoadModeNoteFlashAddr((V_i-C_698FixTimeFreeze),V_m,V_FlashAddrLate);/*��ȡĳҳFlash��¼�����1����¼��Ӧ��Flash��ַ*/
		}
		else
		{
			V_FlashAddr=SF_GetFixedLoadModeNoteFlashAddr(0,V_i,V_FlashAddrLate);/*��ȡĳҳFlash��¼�����1����¼��Ӧ��Flash��ַ�������Ź̶�0����������û�й�ϵ*/
		}

		if(0xFFFFFFFF==V_FlashAddr)
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			continue;	/*��ѯ��һ���¼*/
		}

		GV_D_SafeFlag|=C_W_SafeFlag_2;
		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddr,&V_Data_TimeNote[0],C_698FreeData_DateLen6);

		V_Return_Flag=PF_Campare_Data(&V_Data_TimeNote[0],&V_Data_TimeSys[0],C_698FreeData_DateLen6);
		if(C_GreaterThan!=V_Return_Flag)  /*�ܣ�ʱ�����������*/
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			continue;/*��ѯ��һ���¼*/
		}

		GV_D_SafeFlag|=C_W_SafeFlag_3; /*�ð�ȫ��־*/

		if(C_FlashStAddr_LoadProfile==V_FlashAddrEar)  /*û�м�¼����*/
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			continue;
		}
		else                                                       /*�ж������¼��ʱ��*/
		{
			InF_FlashChipSelect();
			InF_ReadFlash(V_FlashAddrEar,&V_Data_TimeNote[0],C_698FreeData_DateLen6);    /*�������¼ʱ��*/

			V_Return_Flag=PF_Campare_Data(&V_Data_TimeSys[0],&V_Data_TimeNote[0],C_698FreeData_DateLen6);  /*�Ƚ�ʱ���С*/
			if(C_Equal==V_Return_Flag)                              /*���������¼��ʱ��*/
			{
				V_FlashAddrLate=V_FlashAddrEar-C_LoadProfile_RevMode;  /*�����¼Flashҳ��ַ*/
				PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_FlashAddrLate,4);
				SF_WriteE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);/*����E2���1�μ�¼Flashҳ��ַ*/

				if(V_i>=C_698FixTimeFreeze)/*���Ӷ����¼*/
				{
					SF_ChageTime_ChageFlashNote((V_FlashAddrLate+C_LoadProfile_RevMode),V_m,(V_i-C_698FixTimeFreeze));      /*�ӵ�2����¼�鿪ʼ��Ч,����Flash��¼ģʽ�ּ���¼*/
				}
				else
				{
					SF_ChageTime_ChageFlashNote((V_FlashAddrLate+C_LoadProfile_RevMode),V_i,0);
				}
			}
			else
			{
				if(C_LessThan==V_Return_Flag)    /*V_Data_TimeSys<V_Data_TimeNote���������¼ʱ��,Flash��¼����Ϊ��ʼ״̬*/
				{
					V_FlashAddrLate=C_FlashStAddr_LoadProfile;
					PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_FlashAddrLate,4);
					SF_WriteE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);
					V_FlashAddrEar=C_FlashStAddr_LoadProfile;
					PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_FlashAddrEar,4);
					SF_WriteE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);
				}
				else                             /*���ַ�����*/
				{
					if(V_i>=C_698FixTimeFreeze)/*���Ӷ����¼*/
					{
						V_FlashAddrLate=SF_LoadDichotomyFlashData((V_i-C_698FixTimeFreeze),V_m,&V_Data_TimeSys[0],V_FlashAddrEar,V_FlashAddrLate,C_LoadDichotomyFindBefore);
					}
					else
					{
						V_FlashAddrLate=SF_LoadDichotomyFlashData(0,V_i,&V_Data_TimeSys[0],V_FlashAddrEar,V_FlashAddrLate,C_LoadDichotomyFindBefore);
					}

					if(0xFFFFFFFF==V_FlashAddrLate)  /*�Ƿ��������Ҳ����r�g�{��ӛ䛔��������õ���*/
					{
						GV_D_SafeFlag=C_Clear_SafeFlag;
						continue;
					}

					V_FlashAddr=V_FlashAddrLate&0xFFFFF000;
					PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_FlashAddr,4);
					SF_WriteE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);

					if(V_i>=C_698FixTimeFreeze)/*���Ӷ����¼*/
					{
						SF_ChageTime_ChageFlashNote(V_FlashAddrLate,V_m,(V_i-C_698FixTimeFreeze));
					}
					else
					{
						SF_ChageTime_ChageFlashNote(V_FlashAddrLate,V_i,0);
					}
				}
			}
		}
	}

	GV_D_SafeFlag=C_Clear_SafeFlag;
}
/*********************************************************************************
����ԭ�ͣ�void SF_ChageTime_ChageFlashNote(ulong32 V_FlashAddr,uchar8 V_Order,uchar8 V_ProNum)
�����������޸�ʱ�����Flash��¼�������޸�ʱ���־����¼ʱ��YMDhm�޸�ΪFF���ײ�Ϊȫ0��
���������uchar8 V_Order��ĳ�ඳ��������Str_698FreezeDataTable����ţ�
		ulong32 V_FlashAddr:Ҫ����Flash��¼���Ե�ַ����һ����¼Ϊ��Ч����
		uchar8 V_ProNum�����Ӷ����÷�����
�����������
���ز�������
����˵����
���û��ƣ�
��     ע�����������ð�ȫ��־
*********************************************************************************/
void SF_ChageTime_ChageFlashNote(ulong32 V_FlashAddr,uchar8 V_Order,uchar8 V_ProNum)
{
	uchar8 V_i,V_DI2,P_Data[C_698FreeData_DateLen6],V_DI2Temp;
	ulong32 V_FlashAddr32;
	ushort16 V_DataLen,V_DataLenOff;

	if(V_Order>=Str_698FreezeDataTable_Len)/*�쳣�ж�*/
	{
		return;
	}

	V_DI2=Str_698FreezeDataTable[V_Order].V_DI2;

	V_DI2Temp=(V_DI2&0x1F);
	V_DI2Temp |= (V_ProNum<<5);
	V_DataLen=SF_JudgeWriteDataLen(V_DI2Temp);
	if(V_DataLen==0)/*�쳣�ж�*/
	{
		return;
	}

	V_DataLenOff=(ushort16)(V_FlashAddr%C_OneFlashPage);/*ҳ�ڵ�ַƫ��*/
	V_DataLenOff+=2*V_DataLen;/*ȷ����һ����Ч*/
	if(V_DataLenOff<=C_OneFlash_PageNum)
	{
		V_FlashAddr32=V_FlashAddr&0xFFFFF000;/*ҳ��ַ*/
		P_Data[0]=C_Flash_NoEmpty;
		if(GV_D_SafeFlag==C_W_SafeFlag)
		{
			InF_FlashChipSelect();
			InF_WriteFlash(V_FlashAddr32,&P_Data[0],1);/*д1�ֽ�ʱ�������־��Ӧ�ò�дFF���ײ�Ϊ00*/

			V_FlashAddr32=V_FlashAddr+V_DataLen;
			for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
			{
				P_Data[V_i]=C_Flash_NoEmpty;
			}
			InF_FlashChipSelect();
			InF_WriteFlash(V_FlashAddr32,&P_Data[0],C_698FreeData_DateLen6);/*д��1��YMDhmsΪ��Ӧ�ò�дFF���ײ�Ϊ00*/
		}
	}
}

/*********************************************************************************
����ԭ�ͣ�ulong32 SF_GetFixedLoadModeNoteFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr)
��������������ĳҳFlash���1����Ч��¼�ľ����ַ
���������uchar8 V_ProNum�����Ӷ����÷�����
		uchar8 V_Order��ĳ�ඳ��������Str_698FreezeDataTable����ţ�
		ulong32 V_FindFlashAddr����Ҫ����Flash��¼ҳ��ַ��
�����������
���ز�����ulong32 ���ظü�¼���ڸ�ҳFlash��¼�еľ����ַ,�����ݷǷ�ʱ����0xFFFFFFFF��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
ulong32 SF_GetFixedLoadModeNoteFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr)
{
	uchar8 V_i,V_FlashAddr8[4],V_ucReturn,V_DI2,V_Sign;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_DataLen,V_Len,V_NumTemp;
	uchar8 P_Data[C_698FreeData_DateLen6],P_Sign[C_LoadProfile_RevMode];
	ulong32 V_FlashAddr32,V_FlashAddrLate;
	uchar8 V_DI2Temp;

	V_FlashAddr32=0xFFFFFFFF;

	if(V_Order>=Str_698FreezeDataTable_Len)/*�쳣�ж�*/
	{
		return V_FlashAddr32;
	}

	V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_Order].V_E2AddrLate;
	V_DI2=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);
	if(V_DI2==Str_698FreezeDataTable[V_Order].V_DI2)/*���Ӷ���*/
	{
		V_E2Addr_LoadP_Flash_Late=E2Addr_Min_Free_Flash_Ear1+V_ProNum*12+6;/*����������¼Flash��E2��ַ*/
	}

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*ȡ���1����¼Flashҳ��ַ*/
	if(V_ucReturn != C_OK)
	{
		return V_FlashAddr32;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
	V_FlashAddrLate&=0xFFFFF000;             /*ҳ��ַת���������ݴ���*/

	V_DI2=Str_698FreezeDataTable[V_Order].V_DI2;
	V_DI2Temp=(V_DI2&0x1F);
	V_DI2Temp |= (V_ProNum<<5);
	V_DataLen=SF_JudgeWriteDataLen(V_DI2Temp);
	if(V_DataLen==0)/*�쳣�ж�*/
	{
		return V_FlashAddr32;
	}

	V_FlashAddr32=V_FindFlashAddr+C_LoadProfile_RevMode;
	V_Sign=0;
	if(V_FindFlashAddr==V_FlashAddrLate)/*���ҳ*/
	{
		for(V_Len=0;V_Len<(C_OneFlash_PageNum-C_LoadProfile_RevMode-C_698FreeData_DateLen6);)
		{
			InF_FlashChipSelect();
			InF_ReadFlash(V_FlashAddr32,&P_Data[0],C_698FreeData_DateLen6);    /*YMDhms*/

			for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
			{
				if(C_Flash_Empty!=P_Data[V_i])/*�ж������Ƿ�Ϊȫ�㣬���ײ�ΪFF��û��д������*/
				{
					break;
				}
			}

			if(V_i>=C_698FreeData_DateLen6)/*����ȫ��*/
			{
				V_Sign=C_Flash_Empty68;
			}

			for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
			{
				if(C_Flash_NoEmpty!=P_Data[V_i])/*�ж������Ƿ�ΪȫFF�����ײ�Ϊ00��˵����ʱ�����*/
				{
					break;
				}
			}

			if(V_i>=C_698FreeData_DateLen6)/*����ȫFF*/
			{
				V_Sign=C_Flash_Empty68;
			}

			if(C_Flash_Empty68==V_Sign)
			{
				break;
			}

			V_Len+=V_DataLen;
			V_FlashAddr32+=V_DataLen;
		}

		V_FlashAddr32-=V_DataLen;
	}
	else
	{
		InF_FlashChipSelect();
		InF_ReadFlash((V_FlashAddr32-C_LoadProfile_RevMode),&P_Sign[0],C_LoadProfile_RevMode);    /*���޸�ʱ���־��*/
		if(0x68==P_Sign[0])/*��ҳ�м�¼д�ñ�־Ϊ68����ҳ��¼ʱ���е�������д��68��־��ͬʱ����Ч��¼5�ֽ�YMDhmдΪFF�����ײ�д0����˵����ҳ��¼ʱ���е���,ȡ��1ҳ*/
		{
			V_NumTemp=(C_OneFlash_PageNum-C_LoadProfile_RevMode)/V_DataLen;/*ÿҳ��¼����*/
			V_FlashAddr32+=(V_NumTemp-1)*V_DataLen;
		}
		else/*��ʱ�����*/
		{
			for(V_Len=0;V_Len<(C_OneFlash_PageNum-C_LoadProfile_RevMode-C_698FreeData_DateLen6);)
			{
				InF_FlashChipSelect();
				InF_ReadFlash(V_FlashAddr32,&P_Data[0],C_698FreeData_DateLen6);    /*YMDhms*/

				for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
				{
					if(C_Flash_NoEmpty!=P_Data[V_i])/*�ж������Ƿ�ΪȫFF�����ײ�Ϊ00��˵����ʱ�����*/
					{
						break;
					}
				}

				if(V_i>=C_698FreeData_DateLen6)/*����ȫFF*/
				{
					V_Sign=C_Flash_Empty68;
				}

				if(C_Flash_Empty68==V_Sign)
				{
					break;
				}

				V_Len+=V_DataLen;
				V_FlashAddr32+=V_DataLen;
			}

			V_FlashAddr32-=V_DataLen;
		}
	}

	return V_FlashAddr32;
}
/*********************************************************************************
����ԭ�ͣ�ulong32 SF_FindOneFlashPageGiveTimeFlashAddr(uchar8 V_ProNum, uchar8 V_Order, ulong32 V_FindFlashAddr,
														uchar8 *P_FixTime, uchar8 V_LoadDichotomyFindWay)
��������������1ҳFlash��¼(�����ס�β��¼)�������������ʱ���Flash��¼ģʽ�ֵ�ַ����¼ʱ�����ڵ��ڸ���ʱ��
���������
		uchar8 V_ProNum�����Ӷ����÷�����
		uchar8 V_Order��ĳ�ඳ��������Str_698FreezeDataTable����ţ�
		uchar8 *P_FixTime����Ҫ���ҵĹ̶����䣻
		ulong32 V_FindFlashAddr����Ҫ����Flashҳ��ַ��
		uchar8 V_LoadDichotomyFindWay��2�ַ����ҷ�ʽ����
		C_LoadDichotomyFindBefore 0x55��ʾ2�ַ���ʱ����ǰ���ң���Ҫ����ʱ����ǰ����
		C_LoadDichotomyFindAfter 0xAA��ʾ2�ַ���ʱ��������ң���Ҫ���ڳ������ɼ�¼����ʱ��
�����������
���ز�����
		ulong32 �����������ʱ���Flash��¼��ַ,�����ݷǷ�ʱ����0xFFFFFFFF��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
ulong32 SF_FindOneFlashPageGiveTimeFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr,uchar8 *P_FixTime,uchar8 V_LoadDichotomyFindWay)
{
	uchar8 V_i;
	ulong32 V_FlashAddr;
	uchar8 V_EarNoteTime[C_698FreeData_DateLen6],V_LateNoteTime[C_698FreeData_DateLen6];
	uchar8 V_CompareSign,V_DI2,V_Sign;
	ushort16 V_DataLen,V_Len;
	uchar8 V_DI2Temp;

	V_FindFlashAddr=V_FindFlashAddr&0xFFFFF000; /*ҳ��ַת���������ݴ���*/
	V_FlashAddr=0xFFFFFFFF;
	V_FlashAddr=SF_GetFixedLoadModeNoteFlashAddr(V_ProNum,V_Order,V_FindFlashAddr);/*��ȡĳҳFlash��¼�����1����Ч��¼��Ӧ��Flash��ַ*/
	if(0xFFFFFFFF==V_FlashAddr)
	{
		return V_FlashAddr;
	}

	InF_FlashChipSelect();
	InF_ReadFlash((V_FindFlashAddr+C_LoadProfile_RevMode),&V_EarNoteTime[0],C_698FreeData_DateLen6);

	InF_FlashChipSelect();
	InF_ReadFlash(V_FlashAddr,&V_LateNoteTime[0],C_698FreeData_DateLen6);

	/***************************�������硢���һ��****************************/
	V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
	if(C_Equal==V_CompareSign)
	{
		return (V_FindFlashAddr+C_LoadProfile_RevMode);  /*��1����¼*/
	}
	else
	{
		if(C_GreaterThan==V_CompareSign)/*���ڸ�Flash��¼����ʱ��*/
		{
			if(C_LoadDichotomyFindAfter==V_LoadDichotomyFindWay)  /*��ʾ2�ַ���ʱ����ǰ���ң���Ҫ���ڳ������ɼ�¼����ʱ��*/
			{
				return (V_FindFlashAddr+C_LoadProfile_RevMode);  /*��1����¼*/
			}    /*��ǰ���ҵ��øú���ǰ�Ѵ���*/
			else
			{
				return 0xFFFFFFFF;
			}
		}
	}

	V_CompareSign=PF_Campare_Data(&V_LateNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
	if(C_Equal==V_CompareSign)
	{
		return V_FlashAddr;
	}
	else
	{
		if(C_LessThan==V_CompareSign)/*���ڸ�Flash��¼���ʱ��*/
		{
			if(C_LoadDichotomyFindAfter==V_LoadDichotomyFindWay)  /*��ʾ2�ַ���ʱ��������ң���Ҫ���ڳ������ɼ�¼����ʱ��*/
			{
				return 0xFFFFFFFF;
			}
			else   /*��ǰ����*/
			{
				return V_FlashAddr;
			}
		}
	}

	V_DI2=Str_698FreezeDataTable[V_Order].V_DI2;
	V_DI2Temp=(V_DI2&0x1F);
	V_DI2Temp |= (V_ProNum<<5);
	V_DataLen=SF_JudgeWriteDataLen(V_DI2Temp);
	if(V_DataLen==0)/*�쳣�ж�*/
	{
		return 0xFFFFFFFF;
	}

	V_FlashAddr=V_FindFlashAddr+C_LoadProfile_RevMode+V_DataLen;
	/************�����м�****��ʱ�����***********/
	V_Sign=0;
	for(V_Len=V_DataLen;V_Len<=(C_OneFlash_PageNum-C_LoadProfile_RevMode-V_DataLen);)
	{
		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddr,&V_EarNoteTime[0],C_698FreeData_DateLen6);    /*YMDhms*/

		V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
		if((C_GreaterThan==V_CompareSign)||(C_Equal==V_CompareSign))   /*��¼ʱ�����ڻ���ڹ̶�ʱ��*/
		{
			break;
		}

		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(C_Flash_Empty!=V_EarNoteTime[V_i])/*�ж������Ƿ�Ϊȫ�㣬���ײ�ΪFF��û��д������*/
			{
				break;
			}
		}

		if(V_i>=C_698FreeData_DateLen6)/*����ȫ��*/
		{
			V_Sign=C_Flash_Empty68;
		}

		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(C_Flash_NoEmpty!=V_EarNoteTime[V_i])/*�ж������Ƿ�ΪȫFF�����ײ�Ϊ00��˵����ʱ�����*/
			{
				break;
			}
		}

		if(V_i>=C_698FreeData_DateLen6)/*����ȫFF*/
		{
			V_Sign=C_Flash_Empty68;
		}

		if(C_Flash_Empty68==V_Sign)
		{
			break;
		}

		V_Len+=V_DataLen;
		V_FlashAddr+=V_DataLen;
	}

	if((V_Len>(C_OneFlash_PageNum-C_LoadProfile_RevMode-V_DataLen))||(C_Flash_Empty68==V_Sign))
	{
		return 0xFFFFFFFF;  /*���ݲ�����*/
	}
	else
	{
		if(C_Equal==V_CompareSign)
		{
			return V_FlashAddr;
		}
		else
		{
			if(C_LoadDichotomyFindBefore==V_LoadDichotomyFindWay)  /*��ʾ2�ַ���ʱ����ǰ����*/
			{
				return (V_FlashAddr-V_DataLen);   /*ǰ1���¼*/
			}
			else/*��ʾ2�ַ���ʱ��������ң���Ҫ���ڳ������ɼ�¼����ʱ��*/
			{
				return V_FlashAddr;
			}
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�ulong32 SF_LoadDichotomyFixedFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,
												ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
��������������2�ַ�,���Ҽ���ĳ�̶�Flash�飬����ʱ�������ļ�¼ģʽ�ֵ�ַ,����Ч�����1����¼ģʽ�ֵ�ַ,��¼ʱ�����ڵ��ڸ���ʱ��
���������
		uchar8 V_ProNum�����Ӷ����÷�����
		uchar8 V_Order��ĳ�ඳ��������Str_698FreezeDataTable����ţ�
		uchar8 *P_FixTime����Ҫ���ҵĹ̶����䣻
		ulong32 V_FlashAddrEar����ѯ��Flash��ʼҳ��ַ,�Ǿ��Ե�ַ��
		ulong32 V_FlashAddrLate����ѯ��Flash����ҳ��ַ��V_FlashAddrEar<V_FlashAddrLate
		uchar8 V_LoadDichotomyFindWay��2�ַ����ҷ�ʽ����
		C_LoadDichotomyFindBefore 0x55��ʾ2�ַ���ʱ����ǰ���ң���Ҫ����ʱ����ǰ����
		C_LoadDichotomyFindAfter 0xAA��ʾ2�ַ���ʱ��������ң���Ҫ���ڳ������ɼ�¼����ʱ��
�����������
���ز�����
		ulong32 ���ؼ�¼����ģʽ��Flash��ַ,�����ݷǷ�ʱ����0xFFFFFFFF��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
ulong32 SF_LoadDichotomyFixedFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
{
	ulong32 V_FlashAddr;
	uchar8 V_EarNoteTime[C_698FreeData_DateLen6],V_LateNoteTime[C_698FreeData_DateLen6];
	uchar8 V_CompareSign;
	ulong32 V_FlashAddrMin,V_FlashAddrMax,V_FlashAddrMid;

	V_FlashAddr=0xFFFFFFFF;

	V_FlashAddr=SF_GetFixedLoadModeNoteFlashAddr(V_ProNum,V_Order,V_FlashAddrLate);/*��ȡ���ҳFlash��¼�����1����Ч��¼��Ӧ��Flash��ַ*/
	if(0xFFFFFFFF==V_FlashAddr)
	{
		return V_FlashAddr;
	}

	InF_FlashChipSelect();
	InF_ReadFlash((V_FlashAddrEar+C_LoadProfile_RevMode),&V_EarNoteTime[0],C_698FreeData_DateLen6); /*��ȡ�����¼ҳ����1����¼ʱ��*/

	InF_FlashChipSelect();
	InF_ReadFlash(V_FlashAddr,&V_LateNoteTime[0],C_698FreeData_DateLen6); /*��ȡ�����¼ҳ�����1����¼ʱ��*/

	/*****************���������1�顢������1��****************************/
	V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
	if(C_Equal==V_CompareSign)
	{
		return (V_FlashAddrEar+C_LoadProfile_RevMode);
	}
	else
	{
		if(C_GreaterThan==V_CompareSign)/*���ڸ�Flash��¼����ʱ��*/
		{
			if(C_LoadDichotomyFindAfter==V_LoadDichotomyFindWay)  /*ʱ��������ң���Ҫ���ڳ������ɼ�¼����ʱ��*/
			{
				return (V_FlashAddrEar+C_LoadProfile_RevMode);
			}    /*��ǰ���ҵ��øú���ǰ�Ѵ���*/
			else
			{
				return 0xFFFFFFFF;
			}
		}
	}

	V_CompareSign=PF_Campare_Data(&V_LateNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
	if(C_Equal==V_CompareSign)
	{
		return V_FlashAddr;  /*���ɼ�¼ģʽ�ֵ�ַ*/
	}
	else
	{
		if(C_LessThan==V_CompareSign)/*���ڸ�Flash��¼���ʱ��*/
		{
			if(C_LoadDichotomyFindAfter==V_LoadDichotomyFindWay)  /*��ʾ2�ַ���ʱ��������ң���Ҫ���ڳ������ɼ�¼����ʱ��*/
			{
				return 0xFFFFFFFF;
			}
			else   /*��ǰ����*/
			{
				return V_FlashAddr;
			}
		}
	}

	/************�����м�****��ҳFlash��¼,2�ַ�***********/
	V_FlashAddrMin=V_FlashAddrEar;
	V_FlashAddrMax=V_FlashAddrLate;

	while(V_FlashAddrMin<=V_FlashAddrMax)  /*2�ַ�,V_FlashAddrMin...V_FlashAddrMid...V_FlashAddrMax*/
	{
		V_FlashAddrMid=(V_FlashAddrMin+V_FlashAddrMax)/2;
		V_FlashAddrMid=V_FlashAddrMid-V_FlashAddrMid%C_OneFlashPage;  /*2�ַ�ҳ��ַ*/

		V_FlashAddrMid=SF_GetFixedLoadModeNoteFlashAddr(V_ProNum,V_Order,V_FlashAddrMid);/*��ȡ��ҳFlash��¼�����1���̶�ģʽ�ּ�¼��Ӧ��Flash��ַ*/
		if(0xFFFFFFFF==V_FlashAddrMid)
		{
			return 0xFFFFFFFF;
		}

		V_FlashAddr=V_FlashAddrMid;
		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddrMid,&V_EarNoteTime[0],C_698FreeData_DateLen6); /*��ȡ�м�Flashҳ�����1�����ɼ�¼ʱ��*/

		V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
		if(C_Equal==V_CompareSign)
		{
			return (V_FlashAddrMid);
		}
		else  /*V_FlashAddrMin...V_FlashAddrMid...V_FlashAddrMax*/
		{
			if(C_LessThan==V_CompareSign)/*���ڸ�Flash��¼���1���¼ʱ�䣬��ȡ(V_FlashAddrMid+C_OneFlashPage)��1ҳ...V_FlashAddrMax*/
			{
				V_FlashAddrMid=V_FlashAddrMid-V_FlashAddrMid%C_OneFlashPage;  /*ҳ��ַ*/
				V_FlashAddrMin=V_FlashAddrMid+C_OneFlashPage;

				if(C_LoadDichotomyFindBefore==V_LoadDichotomyFindWay)  /*��ʾ2�ַ���ʱ����ǰ����;�����SF_FindOneFlashPageGiveTimeFlashAddr�д���*/
				{
					InF_FlashChipSelect();
					InF_ReadFlash((V_FlashAddrMin+C_LoadProfile_RevMode),&V_EarNoteTime[0],C_698FreeData_DateLen6);  /*����1ҳ�����¼ʱ��*/

					V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
					if(C_GreaterThan==V_CompareSign)  /*���ڸ�Flash��¼���ʱ��*/
					{
						return V_FlashAddr;   /*����ǰҳ�����Ҽ�¼ģʽ��Flash��ַ*/
					}
				}
			}
			else  /*���ڸ�Flash��¼���1���¼ʱ�䣬��ȡV_FlashAddrMin...V_FlashAddrMid��ҳ*/
			{
				V_FlashAddrMid=V_FlashAddrMid-V_FlashAddrMid%C_OneFlashPage;  /*ҳ��ַ*/
				V_FlashAddrMax=V_FlashAddrMid;
			}
			/**********************2�ַ������ҵ������ҳ*********************/
			if((C_OneFlashPage==(V_FlashAddrMax-V_FlashAddrMin))||(V_FlashAddrMax==V_FlashAddrMin))
			{
				if(C_LoadDichotomyFindAfter==V_LoadDichotomyFindWay)  /*ʱ��������ң���Ҫ���ڳ������ɼ�¼����ʱ��*/
				{
					V_FlashAddr=SF_FindOneFlashPageGiveTimeFlashAddr(V_ProNum,V_Order,V_FlashAddrMin,P_FixTime,V_LoadDichotomyFindWay);  /*����1ҳFlash��¼(�����ס�β��¼)������  */
					if((0xFFFFFFFF==V_FlashAddr)&&(V_FlashAddrMax!=V_FlashAddrMin))  /*��������1ҳ*/
					{
						V_FlashAddr=SF_FindOneFlashPageGiveTimeFlashAddr(V_ProNum,V_Order,V_FlashAddrMax,P_FixTime,V_LoadDichotomyFindWay);
					}
				}
				else           /*��ǰ����*/
				{
					V_FlashAddr=SF_FindOneFlashPageGiveTimeFlashAddr(V_ProNum,V_Order,V_FlashAddrMax,P_FixTime,V_LoadDichotomyFindWay);  /*����1ҳFlash��¼(�����ס�β��¼)������  */
					if((0xFFFFFFFF==V_FlashAddr)&&(V_FlashAddrMax!=V_FlashAddrMin))  /*��������1ҳ*/
					{
						V_FlashAddr=SF_FindOneFlashPageGiveTimeFlashAddr(V_ProNum,V_Order,V_FlashAddrMin,P_FixTime,V_LoadDichotomyFindWay);
					}
				}
				return V_FlashAddr;
			}
		}
	}
	return V_FlashAddr;
}
/*********************************************************************************
����ԭ�ͣ�ulong32 SF_AbsFindOneFlashPageGiveTimeFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr,
														uchar8 *P_FixTime,uchar8 V_LoadDichotomyFindWay)
��������������1ҳFlash��¼(�����ס�β��¼)�������������ʱ���Flash��¼ģʽ�ֵ�ַ����¼ʱ�����ڵ��ڸ���ʱ��
���������
		uchar8 V_ProNum�����Ӷ����÷�����
		uchar8 V_Order��ĳ�ඳ��������Str_698FreezeDataTable����ţ�
		uchar8 *P_FixTime����Ҫ���ҵĹ̶����䣻
		ulong32 V_FindFlashAddr����Ҫ����Flash��¼��һ�����Ե�ַ(��ҳ�Ļ���Ϊ��ҳ��1����¼��ַ)��
		uchar8 V_LoadDichotomyFindWay��2�ַ����ҷ�ʽ����
		C_LoadDichotomyFindBefore 0x55��ʾ2�ַ���ʱ����ǰ���ң���Ҫ����ʱ����ǰ����
		C_LoadDichotomyFindAfter 0xAA��ʾ2�ַ���ʱ��������ң���Ҫ���ڳ������ɼ�¼����ʱ��
�����������
���ز�����
		ulong32 �����������ʱ���Flash��¼��ַ,�����ݷǷ�ʱ����0xFFFFFFFF��
����˵����
���û��ƣ�
��     ע���ú����ڲ�ֻ֧��C_LoadDichotomyFindAfter0xAAʱ���������
*********************************************************************************/
ulong32 SF_AbsFindOneFlashPageGiveTimeFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr,uchar8 *P_FixTime,uchar8 V_LoadDichotomyFindWay)
{
	uchar8 V_i;
	ulong32 V_FlashAddr,V_FlashAddrEnd;
	uchar8 V_EarNoteTime[C_698FreeData_DateLen6];
	uchar8 V_CompareSign,V_DI2,V_Sign;
	ushort16 V_DataLen;
	uchar8 V_DI2Temp;

	V_FlashAddrEnd=V_FindFlashAddr&0xFFFFF000; /*ҳ��ַת���������ݴ���*/
	V_FlashAddr=V_FindFlashAddr;

	V_DI2=Str_698FreezeDataTable[V_Order].V_DI2;
	V_DI2Temp=(V_DI2&0x1F);
	V_DI2Temp |= (V_ProNum<<5);
	V_DataLen=SF_JudgeWriteDataLen(V_DI2Temp);
	if(V_DataLen==0)/*�쳣�ж�*/
	{
		return 0xFFFFFFFF;
	}

	V_FlashAddrEnd=V_FlashAddrEnd+C_OneFlashPage-C_Flash_EmptyNum-C_698FreeData_DateLen6;

	/************�����м�****��ʱ�����***********/
	V_Sign=0;
	for(;V_FlashAddr<V_FlashAddrEnd;)
	{
		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddr,&V_EarNoteTime[0],C_698FreeData_DateLen6);    /*YMDhms*/

		V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
		if((C_GreaterThan==V_CompareSign)||(C_Equal==V_CompareSign))   /*��¼ʱ�����ڻ���ڹ̶�ʱ��*/
		{
			break;
		}

		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(C_Flash_Empty!=V_EarNoteTime[V_i])/*�ж������Ƿ�Ϊȫ�㣬���ײ�ΪFF��û��д������*/
			{
				break;
			}
		}

		if(V_i>=C_698FreeData_DateLen6)/*����ȫ��*/
		{
			V_Sign=C_Flash_Empty68;
		}

		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(C_Flash_NoEmpty!=V_EarNoteTime[V_i])/*�ж������Ƿ�ΪȫFF�����ײ�Ϊ00��s˵����ʱ�����*/
			{
				break;
			}
		}

		if(V_i>=C_698FreeData_DateLen6)/*����ȫFF*/
		{
			V_Sign=C_Flash_Empty68;
		}

		if(C_Flash_Empty68==V_Sign)
		{
			break;
		}

		V_FlashAddr+=V_DataLen;
	}

	if((V_FlashAddr>=V_FlashAddrEnd)||(C_Flash_Empty68==V_Sign))
	{
		return 0xFFFFFFFF;  /*���ݲ�����*/
	}
	else
	{
		return V_FlashAddr;
	}
}
/*********************************************************************************
����ԭ�ͣ�ulong32 SF_TraversalSearchFixedFlashData(uchar8 V_ProNum, uchar8 V_Order, uchar8 *P_FixTime, ulong32 V_FlashAddrEar,
													ulong32 V_FlashAddrLate, uchar8 V_LoadDichotomyFindWay)
������������������,���Ҽ���ĳ�̶�Flash�飬����ʱ�������ļ�¼ģʽ�ֵ�ַ,����Ч�����1����¼ģʽ�ֵ�ַ,��¼ʱ�����ڵ��ڸ���ʱ��
���������uchar8 V_ProNum�����Ӷ����÷�����
		uchar8 V_Order��ĳ�ඳ��������Str_698FreezeDataTable����ţ�
		uchar8 *P_FixTime����Ҫ���ҵĹ̶����䣻
		ulong32 V_FlashAddrEar����ѯ��Flash��ʼҳ��һ����¼���Ե�ַ��
		ulong32 V_FlashAddrLate����ѯ��Flash����ҳ��ַ��V_FlashAddrEar<V_FlashAddrLate
		uchar8 V_LoadDichotomyFindWay��2�ַ����ҷ�ʽ��Ŀǰû����
		C_LoadDichotomyFindBefore 0x55��ʾ2�ַ���ʱ����ǰ���ң���Ҫ����ʱ����ǰ����
		C_LoadDichotomyFindAfter 0xAA��ʾ2�ַ���ʱ��������ң���Ҫ���ڳ������ɼ�¼����ʱ��
�����������
���ز�����ulong32 ���ؼ�¼����ģʽ��Flash��ַ,�����ݷǷ�ʱ������ȫ0xFFFFFFFF��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
ulong32 SF_TraversalSearchFixedFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
{
	ulong32 V_FlashAddr;
	uchar8 V_LateNoteTime[C_698FreeData_DateLen6];
	uchar8 V_CompareSign;
	ulong32 V_FlashAddrTemp;

	V_FlashAddr=0xFFFFFFFF;
	V_FlashAddrTemp=V_FlashAddrEar&0xFFFFF000;
	for(;V_FlashAddrTemp<=V_FlashAddrLate;)
	{
		if((GV_ReadLoadFlashAddr32&0xFFFFF000)!=V_FlashAddrTemp)/*��ʼֵ���ҳ�жϣ�����ʱ�����������ʱ�䳤���ظ�����*/
		{
			V_FlashAddr=SF_GetFixedLoadModeNoteFlashAddr(V_ProNum,V_Order,V_FlashAddrTemp);/*��ȡ���ҳFlash��¼�����1����Ч��¼��Ӧ��Flash��ַ*/
			GV_ReadLoadFlashAddr32=V_FlashAddr;
		}
		else
		{
			V_FlashAddr=GV_ReadLoadFlashAddr32;
		}

		if(0xFFFFFFFF==V_FlashAddr)
		{
			return V_FlashAddr;
		}

		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddr,&V_LateNoteTime[0],C_698FreeData_DateLen6); /*��ȡ�����¼ҳ�����1����¼ʱ��*/

		V_CompareSign=PF_Campare_Data(&V_LateNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
		if(C_Equal==V_CompareSign)
		{
			return V_FlashAddr;  /*���ɼ�¼ģʽ�ֵ�ַ*/
		}
		else
		{
			if(C_GreaterThan==V_CompareSign)/*���ڸ�Flash��¼���ʱ��*/
			{
				break;
			}
			else
			{
				V_FlashAddrTemp+=C_OneFlashPage;
			}
		}
	}

	if(V_FlashAddrTemp<=V_FlashAddrLate)/*���ҵ������¼ʱ��ļ�¼ҳ��ַ*/
	{
		if(V_FlashAddrTemp==(V_FlashAddrEar&0xFFFFF000))/*ͬһҳ*/
		{
			V_FlashAddrTemp=V_FlashAddrEar;
		}
		else
		{
			V_FlashAddrTemp+=C_LoadProfile_RevMode;/*��ҳ��¼��1����ַ*/
		}
		V_FlashAddr=SF_AbsFindOneFlashPageGiveTimeFlashAddr(V_ProNum,V_Order,V_FlashAddrTemp,P_FixTime,V_LoadDichotomyFindWay);  /*����1ҳFlash��¼(�����ס�β��¼)������  */
	}
	else
	{
		return 0xFFFFFFFF;
	}

	return V_FlashAddr;
}
/*********************************************************************************
����ԭ�ͣ�ulong32 SF_TraversalSearchFlashData(ulong32 C_FlashStAddr_LoadProfile,ulong32 C_FlashEndAddr_LoadProfile,
uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
���������������������㵱ǰʱ��Flash��ַ����Flash��ַΪFlash�����������ļ�¼ģʽ�ֵ�ַ,����Ч�����1����¼ģʽ�ֵ�ַ
���������
		ulong32 C_FlashStAddr_LoadProfile���ö����¼����ռ���ʼ��ַ��
		ulong32 C_FlashEndAddr_LoadProfile���ö����¼����ռ������ַ��
		uchar8 V_ProNum�����Ӷ����÷�����
		uchar8 V_Order��ĳ�ඳ��������Str_698FreezeDataTable�����
		uchar8 *P_FixTime����Ҫ���ҵĹ̶����䣻
		ulong32 V_FlashAddrEar����ѯ��Flash��һ����¼��ַ��
		ulong32 V_FlashAddrLate����ѯ��Flash����ҳ��ַ��
		uchar8 V_LoadDichotomyFindWay��2�ַ����ҷ�ʽ�����ڸ÷�����û���жϣ����������
		C_LoadDichotomyFindBefore 0x55��ʾ2�ַ���ʱ����ǰ���ң���Ҫ����ʱ����ǰ����
		C_LoadDichotomyFindAfter 0xAA��ʾ2�ַ���ʱ��������ң���Ҫ���ڳ������ɼ�¼����ʱ��
�����������
���ز�����ulong32 ���ؼ�¼����ģʽ��Flash��ַ(698Ϊ����ʱ��Ҫ��ļ�¼��ַ),�����ݷǷ�ʱ����0xFFFFFFFF��
����˵����
���û��ƣ�
��     ע��FlashST---Ear...Late---FlashEnd;Ear...Late---FlashEnd;FlashST...Late---Ear...FlashEnd;
		����---��ʾ��Ч���ݣ�����ͬһҳ
*********************************************************************************/
ulong32 SF_TraversalSearchFlashData(ulong32 C_FlashStAddr_LoadProfile,ulong32 C_FlashEndAddr_LoadProfile,uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
{
	ulong32 V_FlashAddrFind;

	V_FlashAddrFind=0xFFFFFFFF;
	if((V_FlashAddrLate<C_FlashStAddr_LoadProfile)||(V_FlashAddrLate>(C_FlashEndAddr_LoadProfile+C_OneFlashPage))
		||(V_FlashAddrEar<C_FlashStAddr_LoadProfile)||(V_FlashAddrEar>(C_FlashEndAddr_LoadProfile+C_OneFlashPage)))/*���۲�����*/
	{
		return V_FlashAddrFind;
	}

	if(V_FlashAddrLate>=(V_FlashAddrEar&0xFFFFF000))/*FlashST---Ear...Late---FlashEnd; Ear...Late---FlashEnd;*/
	{
		V_FlashAddrFind=SF_TraversalSearchFixedFlashData(V_ProNum,V_Order,P_FixTime,V_FlashAddrEar,V_FlashAddrLate,V_LoadDichotomyFindWay);
	}
	else/* FlashST...Late---Ear...FlashEnd*/
	{
		V_FlashAddrFind=SF_TraversalSearchFixedFlashData(V_ProNum,V_Order,P_FixTime,V_FlashAddrEar,C_FlashEndAddr_LoadProfile,V_LoadDichotomyFindWay);/*Ear...FlashEnd*/
		if(0xFFFFFFFF==V_FlashAddrFind)
		{
			V_FlashAddrFind=SF_TraversalSearchFixedFlashData(V_ProNum,V_Order,P_FixTime,(C_FlashStAddr_LoadProfile+C_LoadProfile_RevMode),V_FlashAddrLate,V_LoadDichotomyFindWay);/* FlashST...Late*/
		}
	}

	return V_FlashAddrFind;
}

/*********************************************************************************
����ԭ�ͣ�ulong32 SF_LoadDichotomyFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,
											ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
��������������2�ַ�,�������㵱ǰʱ��Flash��ַ����Flash��ַΪFlash�����������ļ�¼ģʽ�ֵ�ַ,����Ч�����1����¼ģʽ�ֵ�ַ
���������uchar8 V_ProNum�����Ӷ����÷�����
		uchar8 V_Order��ĳ�ඳ��������Str_698FreezeDataTable�����
		uchar8 *P_FixTime����Ҫ���ҵĹ̶����䣻
		ulong32 V_FlashAddrEar����ѯ��Flash��ʼҳ��ַ�����Ե�ַ����1����¼��ַ��
		ulong32 V_FlashAddrLate����ѯ��Flash����ҳ��ַ��
		uchar8 V_LoadDichotomyFindWay��2�ַ����ҷ�ʽ����
		C_LoadDichotomyFindBefore 0x55��ʾ2�ַ���ʱ����ǰ���ң���Ҫ����ʱ����ǰ����
		C_LoadDichotomyFindAfter 0xAA��ʾ2�ַ���ʱ��������ң���Ҫ���ڳ������ɼ�¼����ʱ��
�����������
���ز�����ulong32 ���ؼ�¼����ģʽ��Flash��ַ(698Ϊ����ʱ��Ҫ��ļ�¼��ַ),�����ݷǷ�ʱ����0xFFFFFFFF��
����˵�������øú�����ѯǰ����¼���ͷ��β�Ѿ��жϴ����
���û��ƣ�
��     ע��FlashST---Ear...Late---FlashEnd;Ear...Late---FlashEnd;FlashST...Late---Ear...FlashEnd;
		����---��ʾ��Ч���ݣ�����ͬһҳ
*********************************************************************************/
ulong32 SF_LoadDichotomyFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
{
	ulong32 V_FlashAddrFind;
	uchar8 V_EarNoteTime[C_698FreeData_DateLen6],V_CompareSign;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear;
	ulong32 C_FlashStAddr_LoadProfile,C_FlashEndAddr_LoadProfile;
	uchar8 V_DI2,V_Return_Flag;

	C_FlashStAddr_LoadProfile=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;
	C_FlashEndAddr_LoadProfile=Str_698FreezeDataTable[V_Order].V_EndFlashAddr;

	V_DI2=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);
	if(V_DI2==Str_698FreezeDataTable[V_Order].V_DI2)/*���Ӷ���*/
	{
		V_Return_Flag=SF_GetMinFreezePro_E2andFlashAddr(V_ProNum,&C_FlashStAddr_LoadProfile,&C_FlashEndAddr_LoadProfile,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*���ݷ��Ӷ��᷽���ţ���ȡ�÷�������������¼E2��ַ���÷�����ʼ������Flash��ַ*/
		if(C_OK!=V_Return_Flag)
		{
			return 0xFFFFFFFF;
		}
	}

	V_FlashAddrFind=0xFFFFFFFF;
	if((V_FlashAddrLate<C_FlashStAddr_LoadProfile)||(V_FlashAddrLate>(C_FlashEndAddr_LoadProfile+C_OneFlashPage))
		||(V_FlashAddrEar<C_FlashStAddr_LoadProfile)||(V_FlashAddrEar>(C_FlashEndAddr_LoadProfile+C_OneFlashPage)))  /*���۲�����*/
	{
		return V_FlashAddrFind;
	}

	if((V_FlashAddrLate/C_OneFlashPage)==(V_FlashAddrEar/C_OneFlashPage))	/*ͬһҳFlash*/
	{
		if(C_LoadDichotomyFindBefore==V_LoadDichotomyFindWay)  /*��ʾ2�ַ���ʱ����ǰ����;�����SF_FindOneFlashPageGiveTimeFlashAddr�д���*/
		{
			InF_FlashChipSelect();
			InF_ReadFlash((V_FlashAddrEar+C_LoadStartSignLength),&V_EarNoteTime[0],C_698FreeData_DateLen6);  /*�������¼ʱ��*/

			V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
			if(C_GreaterThan==V_CompareSign)  /*���������¼ʱ��*/
			{
				return 0xFFFFFFFF;   /*����������*/
			}
		}

		V_FlashAddrFind=SF_FindOneFlashPageGiveTimeFlashAddr(V_ProNum,V_Order,V_FlashAddrLate,P_FixTime,V_LoadDichotomyFindWay);/*����1ҳFlash��¼���������ʱ���Flash��¼ģʽ�ֵ�ַ����¼ʱ�����ڵ��ڸ���ʱ��*/
	}
	else	/*��ҳFlash*/
	{
		if(V_FlashAddrLate>V_FlashAddrEar)/*FlashST---Ear...Late---FlashEnd; Ear...Late---FlashEnd;*/
		{
			V_FlashAddrFind=SF_LoadDichotomyFixedFlashData(V_ProNum,V_Order,P_FixTime,(V_FlashAddrEar-C_LoadProfile_RevMode),V_FlashAddrLate,V_LoadDichotomyFindWay);
		}
		else   /* FlashST...Late---Ear...FlashEnd*/
		{
			if(C_LoadDichotomyFindBefore==V_LoadDichotomyFindWay)
			{
				V_FlashAddrFind=SF_LoadDichotomyFixedFlashData(V_ProNum,V_Order,P_FixTime,C_FlashStAddr_LoadProfile,V_FlashAddrLate,V_LoadDichotomyFindWay);/* FlashST...Late*/
				if(0xFFFFFFFF==V_FlashAddrFind)
				{
					V_FlashAddrFind=SF_LoadDichotomyFixedFlashData(V_ProNum,V_Order,P_FixTime,(V_FlashAddrEar-C_LoadProfile_RevMode),C_FlashEndAddr_LoadProfile,V_LoadDichotomyFindWay);/*Ear...FlashEnd*/
				}
			}
			else
			{
				V_FlashAddrFind=SF_LoadDichotomyFixedFlashData(V_ProNum,V_Order,P_FixTime,(V_FlashAddrEar-C_LoadProfile_RevMode),C_FlashEndAddr_LoadProfile,V_LoadDichotomyFindWay);/*Ear...FlashEnd*/
				if(0xFFFFFFFF==V_FlashAddrFind)
				{
					V_FlashAddrFind=SF_LoadDichotomyFixedFlashData(V_ProNum,V_Order,P_FixTime,C_FlashStAddr_LoadProfile,V_FlashAddrLate,V_LoadDichotomyFindWay);/* FlashST...Late*/
				}
			}
		}
	}

	return V_FlashAddrFind;
}

/*********************************************************************************
����ԭ�ͣ�ulong32 SF_GetFlashAddrLateRecodTolNum(ushort16 *V_NumTempTol,ushort16 V_DataLen,ulong32 V_FlashAddrLate)
���������������¼ҳ������¼������������
���������ushort16 *V_NumTempTol����Ϊ�������ʱ����ʾ��ʣ�����������Ϊ���������ʾͨ�����β��Һ�ʣ�������
		ushort16 V_DataLen��ÿ����¼���ݳ���
		ulong32 V_FlashAddrLate�������¼Flashҳ��ַ
���������ushort16 *V_NumTempTol
���ز�������������������ʱ����������������Flash��ַ����ʱ*V_NumTempTolΪ0��������������ʱ������ȫFF
����˵����
���û��ƣ�
��     ע���ú���ͨ�����ҵõ�����
*********************************************************************************/
ulong32 SF_GetFlashAddrLateRecodTolNum(ushort16 *V_NumTempTol,ushort16 V_DataLen,ulong32 V_FlashAddrLate)
{
	ulong32 V_FlashAddr32;
	ushort16 V_Len,V_NumTemp;
	uchar8 P_Data[C_698FreeData_DateLen6],V_Sign,V_i;

	V_FlashAddr32=0xFFFFFFFF;

	if((*V_NumTempTol)==0)/*����������*/
	{
		return V_FlashAddr32;
	}

	V_FlashAddr32=V_FlashAddrLate&0xFFFFF000; /*ҳ��ַת���������ݴ���*/
	V_FlashAddr32=V_FlashAddr32+C_LoadProfile_RevMode;

	V_Sign=0;
	V_NumTemp=0;
	for(V_Len=0;V_Len<(C_OneFlash_PageNum-C_LoadProfile_RevMode-C_698FreeData_DateLen6);)
	{
		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddr32,&P_Data[0],C_698FreeData_DateLen6);    /*YMDhms*/

		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(C_Flash_Empty!=P_Data[V_i])/*�ж������Ƿ�Ϊȫ�㣬���ײ�ΪFF��û��д������*/
			{
				break;
			}
		}

		if(V_i>=C_698FreeData_DateLen6)/*����ȫ��*/
		{
			V_Sign=C_Flash_Empty68;
		}

		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(C_Flash_NoEmpty!=P_Data[V_i])/*�ж������Ƿ�ΪȫFF�����ײ�Ϊ00��˵����ʱ�����*/
			{
				break;
			}
		}

		if(V_i>=C_698FreeData_DateLen6)/*����ȫFF*/
		{
			V_Sign=C_Flash_Empty68;
		}

		if(C_Flash_Empty68!=V_Sign)
		{
			V_NumTemp+=1;/*����+1*/
		}
		else
		{
			break;
		}

		V_Len+=V_DataLen;
		V_FlashAddr32+=V_DataLen;
	}

	if((*V_NumTempTol)<=V_NumTemp)/*��������Ҫ��*/
	{
		V_FlashAddr32=V_FlashAddr32-(* V_NumTempTol)*V_DataLen;
		*V_NumTempTol=0;
	}
	else
	{
		*V_NumTempTol-=V_NumTemp;
		V_FlashAddr32=0xFFFFFFFF;
	}
	return V_FlashAddr32;
}
/*********************************************************************************
����ԭ�ͣ�ulong32 SF_GetFlashAddrRecodTolNum(ushort16 *V_NumTempTol,ushort16 V_DataLen,ulong32 V_FlashAddr)
����������ĳҳFLash������¼������������
���������ushort16 *V_NumTempTol����Ϊ�������ʱ����ʾ��ʣ�����������Ϊ���������ʾͨ�����β��Һ�ʣ�������
		ushort16 V_DataLen��ÿ����¼���ݳ���
		ulong32 V_FlashAddr���账���Flashҳ��ַ
���������ushort16 *V_NumTempTol
���ز�������������������ʱ����������������Flash��ַ����ʱ*V_NumTempTolΪ0��������������ʱ������ȫFF
����˵����
���û��ƣ�
��     ע���ú�����Ҫͨ������õ�����
***********************************************************************************/
ulong32 SF_GetFlashAddrRecodTolNum(ushort16 *V_NumTempTol,ushort16 V_DataLen,ulong32 V_FlashAddr)
{
	ulong32 V_FlashAddr32;
	ushort16 V_Len,V_NumTemp;
	uchar8 P_Data[C_698FreeData_DateLen6],V_Sign,V_i;
	uchar8 P_Sign[C_LoadProfile_RevMode];

	V_FlashAddr32=0xFFFFFFFF;

	if((*V_NumTempTol)==0)/*����������*/
	{
		return V_FlashAddr32;
	}

	V_FlashAddr32=V_FlashAddr&0xFFFFF000; /*ҳ��ַת���������ݴ���*/
	V_FlashAddr32=V_FlashAddr32+C_LoadProfile_RevMode;

	V_Sign=0;
	V_NumTemp=0;

	InF_FlashChipSelect();
	InF_ReadFlash((V_FlashAddr32-C_LoadProfile_RevMode),&P_Sign[0],C_LoadProfile_RevMode);    /*���޸�ʱ���־��*/

	if(0x68==P_Sign[0])/*��ҳ�м�¼д�ñ�־Ϊ68����ҳ��¼ʱ���е�������д��68��־��ͬʱ����Ч��¼5�ֽ�YMDhmдΪFF�����ײ�д0����˵����ҳ��¼ʱ���е���,ȡ��1ҳ*/
	{
		V_NumTemp=(C_OneFlash_PageNum-C_LoadProfile_RevMode)/V_DataLen;/*ÿҳ��¼����*/
		V_FlashAddr32+=V_NumTemp*V_DataLen;
	}
	else/*��ʱ�����*/
	{
		for(V_Len=0;V_Len<(C_OneFlash_PageNum-C_LoadProfile_RevMode-C_698FreeData_DateLen6);)
		{
			InF_FlashChipSelect();
			InF_ReadFlash(V_FlashAddr32,&P_Data[0],C_698FreeData_DateLen6);    /*YMDhms*/

			for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
			{
				if(C_Flash_NoEmpty!=P_Data[V_i])/*�ж������Ƿ�ΪȫFF�����ײ�Ϊ00��s˵����ʱ�����*/
				{
					break;
				}
			}

			if(V_i>=C_698FreeData_DateLen6)/*����ȫFF*/
			{
				V_Sign=C_Flash_Empty68;
			}

			if(C_Flash_Empty68!=V_Sign)
			{
				V_NumTemp+=1;/*����+1*/
			}
			else
			{
				break;
			}

			V_Len+=V_DataLen;
			V_FlashAddr32+=V_DataLen;
		}
	}

	if((*V_NumTempTol)<=V_NumTemp)/*��������Ҫ��*/
	{
		V_FlashAddr32=V_FlashAddr32-(* V_NumTempTol)*V_DataLen;
		*V_NumTempTol=0;
	}
	else
	{
		*V_NumTempTol-=V_NumTemp;
		V_FlashAddr32=0xFFFFFFFF;
	}

	return V_FlashAddr32;
}
/*********************************************************************************
����ԭ�ͣ�ulong32 SF_GetFlashAddrSatisfyNum(uchar8 V_ProNum,uchar8 V_Order,ushort16 V_Num)
������������ȡ���������ĳ�ඳ������Flash��ַ
���������uchar8 V_ProNum�����Ӷ����÷����š��Ƿ��Ӷ��ᣬ����ڷ�����Ϊȫ��
		uchar8 V_Order��ĳ�ඳ��������Str_698FreezeDataTable�����
		ushort16 V_Num����������
�����������
���ز�����ulong32�������Ҫ���Flash��ַ���쳣Ϊ0xFFFFFFFF
����˵����
���û��ƣ�
��     ע��FlashST---Ear...Late---FlashEnd(ʱ����������);Ear...Late---FlashEnd;FlashST...Late---Ear...FlashEnd
*********************************************************************************/
ulong32 SF_GetFlashAddrSatisfyNum(uchar8 V_ProNum,uchar8 V_Order,ushort16 V_Num)
{
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear,V_DataLen,V_NumTempTol;
	ulong32 V_FlashStAddr_LoadProfile,V_FlashEndAddr_LoadProfile,V_FlashAddr32Temp,V_FlashAddr32;
	uchar8 V_DI2,V_ucReturn,V_FlashAddr8[4];
	ulong32 V_FlashAddrLate,V_FlashAddrEar;
	uchar8 V_DI2Temp;

	V_FlashAddr32Temp=0xFFFFFFFF;

	if(V_Order>=Str_698FreezeDataTable_Len)/*�쳣�ж�*/
	{
		return V_FlashAddr32Temp;
	}

	V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_Order].V_E2AddrLate;
	V_E2Addr_LoadP_Flash_Ear=Str_698FreezeDataTable[V_Order].V_E2AddrEar;
	V_FlashStAddr_LoadProfile=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;
	V_FlashEndAddr_LoadProfile=Str_698FreezeDataTable[V_Order].V_EndFlashAddr;
	V_DI2=Str_698FreezeDataTable[V_Order].V_DI2;
	V_DI2Temp=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);

	if(V_DI2Temp==V_DI2)/*���Ӷ���*/
	{
		V_ucReturn=SF_GetMinFreezePro_E2andFlashAddr(V_ProNum,&V_FlashStAddr_LoadProfile,&V_FlashEndAddr_LoadProfile,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*���ݷ��Ӷ��᷽���ţ���ȡ�÷�������������¼E2��ַ���÷�����ʼ������Flash��ַ*/
		if(C_OK!=V_ucReturn)
		{
			return V_FlashAddr32Temp;
		}
	}

	V_DI2Temp=(V_DI2&0x1F);/*���ӷ����ţ��Ƿ��Ӷ���÷����ţ����Ϊ0*/
	V_DI2Temp |= (V_ProNum<<5);
	V_DataLen=SF_JudgeWriteDataLen(V_DI2Temp);
	if(0==V_DataLen)/*�쳣�ж�*/
	{
		return V_FlashAddr32Temp;
	}

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*ȡ���1����¼Flashҳ��ַ*/
	if(V_ucReturn != C_OK)
	{
		return V_FlashAddr32Temp;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
	V_FlashAddrLate&=0xFFFFF000;             /*ҳ��ַת���������ݴ���*/

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);         /*ȡ����1����¼Flash��ַ*/
	if(V_ucReturn != C_OK)
	{
		return	V_FlashAddr32Temp;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);

	if(V_FlashAddrEar==V_FlashAddrLate)/*û�ж�������*/
	{
		return	V_FlashAddr32Temp;
	}

	V_NumTempTol=V_Num;

	if(V_FlashAddrLate>=(V_FlashAddrEar-C_LoadProfile_RevMode))/*FlashST---Ear...Late---FlashEnd; Ear...Late---FlashEnd;*/
	{
		V_FlashAddr32=V_FlashAddrLate;
		while(V_FlashAddr32>=(V_FlashAddrEar-C_LoadProfile_RevMode))
		{
			if(V_FlashAddr32==V_FlashAddrLate)
			{
				V_FlashAddr32Temp=SF_GetFlashAddrLateRecodTolNum(&V_NumTempTol,V_DataLen,V_FlashAddr32);
			}
			else
			{
				V_FlashAddr32Temp=SF_GetFlashAddrRecodTolNum(&V_NumTempTol,V_DataLen,V_FlashAddr32);
			}

			if((0==V_NumTempTol)&&(0xFFFFFFFF!=V_FlashAddr32Temp))/*�ҵ��������������*/
			{
				break;
			}

			if(V_FlashAddr32>=C_OneFlashPage)/*����V_FlashAddr32��ַΪ���жϣ����ҵ�ͷ*/
			{
				V_FlashAddr32=V_FlashAddr32-C_OneFlashPage;
			}
			else
			{
				break;
			}
		}
	}
	else /*FlashST...Late---Ear...FlashEnd*/
	{
		V_FlashAddr32=V_FlashAddrLate;
		while(V_FlashAddr32>=V_FlashStAddr_LoadProfile)
		{
			if(V_FlashAddr32==V_FlashAddrLate)
			{
				V_FlashAddr32Temp=SF_GetFlashAddrLateRecodTolNum(&V_NumTempTol,V_DataLen,V_FlashAddr32);
			}
			else
			{
				V_FlashAddr32Temp=SF_GetFlashAddrRecodTolNum(&V_NumTempTol,V_DataLen,V_FlashAddr32);
			}

			if((0==V_NumTempTol)&&(0xFFFFFFFF!=V_FlashAddr32Temp))/*�ҵ��������������*/
			{
				break;
			}

			if(V_FlashAddr32>=C_OneFlashPage)/*����V_FlashAddr32��ַΪ���жϣ����ҵ�ͷ*/
			{
				V_FlashAddr32=V_FlashAddr32-C_OneFlashPage;
			}
			else
			{
				break;
			}
		}

		if((0!=V_NumTempTol)&&(0xFFFFFFFF==V_FlashAddr32Temp))/*û���ҵ��������������*/
		{
			V_FlashAddr32=V_FlashEndAddr_LoadProfile;
			while(V_FlashAddr32>=(V_FlashAddrEar-C_LoadProfile_RevMode))
			{
				V_FlashAddr32Temp=SF_GetFlashAddrRecodTolNum(&V_NumTempTol,V_DataLen,V_FlashAddr32);

				if((0==V_NumTempTol)&&(0xFFFFFFFF!=V_FlashAddr32Temp))/*�ҵ��������������*/
				{
					break;
				}

				if(V_FlashAddr32>=C_OneFlashPage)/*����V_FlashAddr32��ַΪ���жϣ����ҵ�ͷ*/
				{
					V_FlashAddr32=V_FlashAddr32-C_OneFlashPage;
				}
				else
				{
					break;
				}
			}
		}
	}
	return V_FlashAddr32Temp;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetFrozenDataLen(ushort16 V_ucLineNum)
������������ȡ�������ݵĳ���
���������V_ucLineNum��Str_FrozenConvert_Table[]���к�
������������ݵĳ���
���ز�����
����λ�ã�
��     ע����� Str_FrozenConvert_Table���ҵ����ݵĳ���
		���ʵ��ܸ������õķ�����Ӧ��
*******************************************************************************/
uchar8 SF_GetFrozenDataLen(ushort16 V_ucLineNum)
{
	uchar8 V_ucDataLen, V_ucNum;

	V_ucNum = InF_RateNumChangeToHex();
	if(Str_FrozenConvert_Table[V_ucLineNum].V_uc698RateNumMethod == C_NeedRateNum_FF)
	{
		V_ucNum += 1;/*��+���ʣ��ȷ�������һ��*/
		V_ucDataLen = V_ucNum * (Str_FrozenConvert_Table[V_ucLineNum + 1].V_uc645Length); /*���Str_FrozenConvert_Table˳����������ݿ� ���ܣ����ʣ������÷�������ݳ��ȼ���*/
	}
	else if(Str_FrozenConvert_Table[V_ucLineNum].V_uc698RateNumMethod == C_NeedRateNumPrice_FF)
	{
		V_ucDataLen = V_ucNum * (Str_FrozenConvert_Table[V_ucLineNum + 1].V_uc645Length); /*���Str_FrozenConvert_Table˳����������ݿ� ���ܣ����ʣ������÷�������ݳ��ȼ���*/
	}
	else
	{
		V_ucDataLen = Str_FrozenConvert_Table[V_ucLineNum].V_uc645Length; /*���Str_FrozenConvert_Table������*/
	}
	return V_ucDataLen;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_FrozenData_JudgeRateNum(ushort16 V_ucLineNum, ulong32 V_ulOAD)
�����������жϵ�����ȡ�ķ��ʵ��ܡ��������ʵ�۵����ݷ�����û�г������õķ�����
���������V_ucLineNum��Str_FrozenConvert_Table[]���к�;V_ulOAD:��ȡ��ROAD
���������
���ز���������������C_Error,û�г���C_OK
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_FrozenData_JudgeRateNum(ushort16 V_ucLineNum, ulong32 V_ulOAD)
{
	uchar8 V_ucNum, V_ucReturn = C_OK;
	uchar8 V_ucData[4];

	PF_Ulong32ToBuffer4(V_ucData, &V_ulOAD, 4);

	V_ucNum = InF_RateNumChangeToHex();

	if(Str_FrozenConvert_Table[V_ucLineNum].V_uc698RateNumMethod == C_NeedRateNum)
	{
		V_ucNum += 1;				/*��+���ʣ��ȷ�������һ��*/
		if(V_ucData[0] > V_ucNum)	/*DI0Ϊ����*/
		{
			V_ucReturn = C_Error;
		}
	}
	else if(Str_FrozenConvert_Table[V_ucLineNum].V_uc698RateNumMethod == C_NeedRateNumPrice)
	{
		if(V_ucData[0] > V_ucNum)
		{
			V_ucReturn = C_Error;
		}
	}
	else
	{
		V_ucReturn = C_OK;
	}

	return V_ucReturn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_OrganData(ulong32 *P_Data_Id_OAD,uchar8 V_ProNum,uchar8 V_i,ushort16 *P_TotalLen,ushort16 *P_Length,
						ulong32 V_FindFlashAddr,uchar8 *P_Data,ushort16 V_DataLen,uchar8 *pV_FreezeTimeBuf,uchar8 V_Mode)
��������������OAD��ű���֯���������ݡ���֧�ֵ�OAD����1�ֽ�C_NotSupportAOD_DataBB 0xBB��
		��ģ��д��¼ʱ�������ݲ����������0xAA C_NotSupportAOD_Data������
���������uchar8 V_ProNum�����Ӷ����÷�����
		uchar8 V_Order��ĳ�ඳ��������Str_698FreezeDataTable�����
		ulong32 *P_Data_Id_OAD��ĳ�ඳ��������Str_698FreezeDataTable����š��������Զ�ӦOAD˳�򣬵�����OADΪFFFFFFFF���ʾ��������¼��ȡ��¼OAD����
		uchar8 V_Order��ĳ�ඳ��������Str_698FreezeDataTable�����
		ushort16 *P_TotalLen����Ϊ����Ϊ����֯�����ܳ��ȣ��������������֯���ݳ��Ⱥ���ܳ���
		ushort16 *P_Length����Ϊ����Ϊʣ�໺�泤�ȣ��������������֯���ݳ��Ⱥ�ʣ�໺���ܳ���
		ulong32 V_FindFlashAddr��������¼����Flash��ַ;
		uchar8 *P_Data��������¼���ݴ�Ż���,�ֽڲ��ö����ݴ������Ļ���;
		ushort16 V_DataLen:���������¼�ܳ��ȣ��ж��á�
���������uchar8 *pV_FreezeTimeBuf���������n��������ʱ�䣬ͨ�Ŷ�����֡�ж��ã�
���ز�����C_OK��C_IICError��C_Error��C_DataLenError��C_IDError��C_NoData
����λ�ã�
��     ע���ڲ�����ֵע��C_NotSupportAOD_DataBB��C_NotSupportAOD_DataCC
*******************************************************************************/
uchar8 SF_OrganData(ulong32 * P_Data_Id_OAD,uchar8 V_ProNum,uchar8 V_i,ushort16 * P_TotalLen,ushort16 * P_Length,ulong32 V_FindFlashAddr,uchar8 * P_Data,ushort16 V_DataLen,uchar8 * pV_FreezeTimeBuf,uchar8 V_Mode)
{
	ushort16 V_Data_Length,V_Data_LengthOff,V_Data_LengthOffnei;
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADOrder16,V_j,V_k,V_EventSign;
	uchar8 V_Return_Flag,V_ucAAFlag=0;
	Str_3aTable V_Str_3aTable;
	ulong32 V_FlashAddr;
	ushort16 V_TotalLen;
	ushort16 V_Length;
	uchar8 V_Date1[C_698FreeData_DateLen6];
	uchar8 V_ucFrozenConver645Len;
	uchar8 V_ucRateNumJudge = C_RateNumOK;
	uchar8 V_ucEnergy02Flag = 0;
	ulong32 V_ulSaveOAD;
	uchar8 V_ucEnergyNum;
	uchar8 V_uci, V_ucEnergyChgeLen = 0, V_ucResultEnergyChgeLen = 0;
	uchar8 V_DI2Temp;
	uchar8 V_OADNum = 0, V_NullNum = 0, V_NullNumCC = 0, V_ucAAFlagTemp;
	uchar8 V_TimeNum = 0;   /*����OAD�У������Ķ���ʱ�估��ŵĸ���*/
	ushort16 V_jTemp = 0;
	uchar8 V_DataLenTemp, V_Data_LengthOffTemp = 0, i;
	ulong64 V_ulEnergyData = 0;

	V_TotalLen = *P_TotalLen;
	V_Length = *P_Length;

	if(V_i >= Str_698FreezeDataTable_Len)   /*�쳣�ж�*/
	{
		return C_Error;
	}

	V_Order = Str_698FreezeDataTable[V_i].V_LineNumLen_T;       /*698���᳤�ȡ���������������Str_3aTable�к�*/
	if(V_Order >= Str_3aTable_E23RAM_Len)
	{
		return C_Error;        /*�쳣*/
	}

	V_Data_Length = 0;
	V_Str_3aTable = Str_3aTable_E23RAM[V_Order];

	V_Return_Flag = SF_Re_E23_RAM_Data698(&V_Str_3aTable, CLI_Free_OADTabLen_T, &P_OADTabLen_T[0]);
	if(C_OK == V_Return_Flag)
	{
		V_OADTabLen_T = P_OADTabLen_T[0];
		V_OADTabLen_T = V_OADTabLen_T * C_698Free_OADTabDataType;    /*��ű�ÿ��OAD���C_698Free_OADTabDataType���ֽ�,Ŀǰ6�ֽڡ�2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/
		if(V_OADTabLen_T > C_698Free_OADTabLen)                      /*���ݳ��Ȱ�ȫ���ж�*/
		{
			return C_Error;    /*�쳣*/
		}

		V_Order = Str_698FreezeDataTable[V_i].V_LineNumTab;          /*698������ű�����Str_3aTable�к�*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return 	C_Error;    /*�쳣*/
		}

		V_Str_3aTable = Str_3aTable_E23RAM[V_Order];
		V_Return_Flag = SF_Re_E23_RAM_Data698(&V_Str_3aTable, V_OADTabLen_T, &P_DataOAD_NumTab[0]);
		if(C_OK != V_Return_Flag)
		{
			return C_Error;    /*�쳣*/
		}

		V_DI2Temp = (uchar8)((C_RelatedOAD_Min & 0x00FF0000) >> 16);    /*���Ӷ���*/
		if(V_DI2Temp == (Str_698FreezeDataTable[V_i].V_DI2))
		{
			V_OADTabLen_T = SF_GetMinFreezeNum_OADTab(V_ProNum,&P_DataOAD_NumTab[0],V_OADTabLen_T);     /*��ȡ���Ӷ��᷽���ţ���Ӧ��OAD�����б�����OAD����*/
			if(0xFFFF == V_OADTabLen_T)
			{
				return C_Error;    /*�쳣*/
			}
		}
		else
		{
			V_OADTabLen_T = V_OADTabLen_T / C_698Free_OADTabDataType;           /*��ű�ÿ��OAD���C_698Free_OADTabDataType���ֽ�,Ŀǰ6�ֽڡ�2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/
		}

		V_Data_Length = 0;					/*�޸Ĳ��̶���������+���*/
		V_Data_LengthOff = V_Data_Length;   /*��¼����ƫ��*/

		while( 0xFFFFFFFF != (*P_Data_Id_OAD) )
		{
			/*��ѯ����ʱ�估��š����ַ��Ӷ��ἰ��������*/
			V_jTemp = 0;
			V_ucAAFlagTemp = 0x55;
            V_Data_LengthOffTemp = 0;
            switch( *P_Data_Id_OAD )
            {
                case CFreeTime:     /*����ʱ��*/
                {
                    V_ucAAFlagTemp = 0xAA;
                    V_DataLenTemp = C_698FreeData_DateLen6;
                    V_TimeNum++;

                }break;
                case CFreeNum:      /*�������*/
                {
                    V_ucAAFlagTemp = 0xAA;
                    V_DataLenTemp = C_698FreeData_SequenceLen4;
                    V_TimeNum++;
                    V_Data_LengthOffTemp = C_698FreeData_DateLen6;      /*�����¼�洢��ʽΪʱ������+���*/

                }break;
                default:
                {
                    V_jTemp = 2;
                }break;

            }

            if( V_ucAAFlagTemp == 0xAA )
            {
                if( (*P_Length) >= V_DataLenTemp )
                {
                    V_FlashAddr = V_FindFlashAddr + V_Data_LengthOffTemp;
                    InF_FlashChipSelect();
                    InF_ReadFlash(V_FlashAddr, &P_Data[V_Data_Length], V_DataLenTemp);    /*����¼����*/
                    (*P_Length) -= V_DataLenTemp;
                    V_Data_Length += V_DataLenTemp;
                    V_ucAAFlag = 0x68;
                }
                else
                {
                    return 	C_DataLenError;
                }
            }

			/*��ѯ�����б�*/
			V_j = 0;
			if ( ( V_ucAAFlagTemp !=0xAA ) && ( V_OADTabLen_T <= C_FreezeMAXRelatedOAD ) )   /*����ʱ�䡢��ţ��鲻�������Ų�ѯ�����б�*/
			{
				V_Data_LengthOff = (C_698FreeData_SequenceLen4 + C_698FreeData_DateLen6);
				V_ucAAFlag = 0;

				for(    ; V_j < V_OADTabLen_T; V_j++)
				{
					PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType * V_j], &V_OADOrder16);
					V_EventSign = (V_OADOrder16 & 0xE000);    /*����698 OAD��DI1��3λ��ʾ��ͬ���ԣ�����Ʒ�ʽ�й�*/
					V_OADOrder16 &= 0x1FFF;
					if(V_OADOrder16 >= Str_FrozenConvert_Table_Len)
					{
						return 	C_Error;    /*�쳣������������*/
					}

                    V_ucEnergy02Flag = 0;
                    if ( ( (*P_Data_Id_OAD) & 0xFF000F00 ) == 0x00000200 )    /*��ȡ����02���Ե���*/
                    {
                        V_ucEnergy02Flag = C_ReadRelated02Energy;

                        if( ( ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD ) & 0x00000F00 ) == 0x00000400 )  /*�洢����04���Ե���*/
                        {
                            V_ucEnergy02Flag |= C_SaveRelated04Energy;
                            V_ulSaveOAD = (Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD & 0xFFFF00FF) | 0x00000200;
                            if ( ( *P_Data_Id_OAD ) == ( V_ulSaveOAD | V_EventSign ) )
                            {
                                V_ucEnergy02Flag |= C_EnergyPlanSame;
                            }
                        }
                    }   /*else��ʼ���Ѹ�ֵ0*/

					if ( ( (*P_Data_Id_OAD) == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD | V_EventSign ) )         /*����OAD���*/
                      || ( V_ucEnergy02Flag == ( C_ReadRelated02Energy | C_SaveRelated04Energy | C_EnergyPlanSame ) ) )  /*��04���Ե��ܣ���02���Զ�*/
					{
                        if( SF_FrozenData_JudgeRateNum(V_OADOrder16, *P_Data_Id_OAD) == C_Error )
                        {
                            V_ucRateNumJudge = C_RateNumError;
                            break;
                        }  /*������δ������Ӧ��*/

                        V_ucFrozenConver645Len = SF_GetFrozenDataLen(V_OADOrder16);
						if( (*P_Length) >= V_ucFrozenConver645Len )
						{
                            V_FlashAddr = V_FindFlashAddr + V_Data_LengthOff;
							InF_FlashChipSelect();
							InF_ReadFlash(V_FlashAddr, &P_Data[V_Data_Length], V_ucFrozenConver645Len);    /*����¼����*/
                            /*��02���Ե��ܣ��洢Ϊ4ΪС�����ܣ�����ת��*/
                            if( V_ucEnergy02Flag == ( C_ReadRelated02Energy | C_SaveRelated04Energy | C_EnergyPlanSame ) )  /*��04���Ե��ܣ���02���Զ�*/
                            {
                                V_ucEnergyNum = V_ucFrozenConver645Len / C_AccurateEnergyCommLen;
                                V_ucEnergyChgeLen = 0;
                                V_ucResultEnergyChgeLen = 0;
                                for(V_uci = 0; V_uci < V_ucEnergyNum; V_uci++)
                                {
									V_ulEnergyData = 0;
									if( (P_Data[V_Data_Length + V_ucEnergyChgeLen] & 0x80) == 0x80)
									{
										for(i = C_AccurateEnergyCommLen; i < 8; i++)
										{
											V_ulEnergyData <<= 8;
											V_ulEnergyData |= 0xFF;
										}
										for(i = 0; i < C_AccurateEnergyCommLen; i++)
										{
											V_ulEnergyData <<= 8;
											V_ulEnergyData |= P_Data[V_Data_Length + V_ucEnergyChgeLen + i];
										}
										V_ulEnergyData = (~V_ulEnergyData) + 1;
									}
									else
									{
										for(i = 0; i < C_AccurateEnergyCommLen; i++)
										{
											V_ulEnergyData <<= 8;
											V_ulEnergyData |= P_Data[V_Data_Length + V_ucEnergyChgeLen + i];
										}
									}
									V_ulEnergyData /= 100;
									if( (P_Data[V_Data_Length + V_ucEnergyChgeLen] & 0x80) == 0x80)
									{
										V_ulEnergyData = (~V_ulEnergyData) + 1;
									}
									PF_Ulong64ToBuffer8_698(&P_Data[V_Data_Length + V_ucResultEnergyChgeLen], &V_ulEnergyData, C_EnergyCommLen);
                                    /*memcpy( &P_Data[V_Data_Length + V_ucResultEnergyChgeLen], &P_Data[V_Data_Length + 1 + V_ucEnergyChgeLen], C_EnergyCommLen);*/
                                    V_ucEnergyChgeLen += C_AccurateEnergyCommLen;
                                    V_ucResultEnergyChgeLen += C_EnergyCommLen;
                                }
                                V_ucFrozenConver645Len = V_ucResultEnergyChgeLen;
                            }

							(*P_Length) -= V_ucFrozenConver645Len;
							V_Data_Length += V_ucFrozenConver645Len;
							V_ucAAFlag = 0x68;
							break;
						}
						else
						{
							return 	C_DataLenError;
						}
					}
					else
					{
						if( C_array == Str_FrozenConvert_Table[V_OADOrder16].V_uc698Type )    /*�����ʽOAD,��ѯ�Ƿ�Ϊ��OAD*/
						{
							V_Data_LengthOffnei = 0;

							for( V_k = 0;    ; V_k++ )
							{
								if( ( V_OADOrder16 + V_k + 1 ) >= Str_FrozenConvert_Table_Len )
								{
									return 	C_Error;        /*�쳣������������*/
								}

								if ( ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD & 0xFFFFFF00 )
                                  == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD & 0xFFFFFF00 ) )
								{
                                    V_ucEnergy02Flag = 0;
                                    if ( ( (*P_Data_Id_OAD) & 0xFF000F00 ) == 0x00000200 )    /*��ȡ����02���Ե���*/
                                    {
                                        V_ucEnergy02Flag = C_ReadRelated02Energy;

                                        if( ( ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD ) & 0x00000F00 ) == 0x00000400 )  /*�洢����04���Ե���*/
                                        {
                                            V_ucEnergy02Flag |= C_SaveRelated04Energy;
                                            V_ulSaveOAD = ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD & 0xFFFF00FF ) | 0x00000200;
                                            if ( ( *P_Data_Id_OAD ) == ( V_ulSaveOAD | V_EventSign ) )    /*�����Ƿ���ͬ*/
                                            {
                                                V_ucEnergy02Flag |= C_EnergyPlanSame;
                                            }
                                        }
                                    }   /*else��ʼ���Ѹ�ֵ0*/

									if ( ( (*P_Data_Id_OAD) == ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD | V_EventSign ) )
                                      || ( V_ucEnergy02Flag == ( C_ReadRelated02Energy | C_SaveRelated04Energy | C_EnergyPlanSame ) ) )
									{
                                        if( SF_FrozenData_JudgeRateNum((V_OADOrder16 + V_k + 1), *P_Data_Id_OAD) == C_Error )
                                        {
                                             V_ucRateNumJudge = C_RateNumError;
                                             break;
                                        }    /*������δ������Ӧ��*/

                                        V_ucFrozenConver645Len = SF_GetFrozenDataLen(V_OADOrder16 + V_k + 1);
										if( (*P_Length) >= V_ucFrozenConver645Len )
										{
											V_FlashAddr = V_FindFlashAddr + V_Data_LengthOff + V_Data_LengthOffnei;
											InF_FlashChipSelect();
											InF_ReadFlash(V_FlashAddr,&P_Data[V_Data_Length], V_ucFrozenConver645Len);    /*����¼����*/

                                            /*��02���Ե��ܣ��洢Ϊ4ΪС�����ܣ�����ת��*/
                                            if( V_ucEnergy02Flag == ( C_ReadRelated02Energy | C_SaveRelated04Energy | C_EnergyPlanSame ) )  /*��04���Ե��ܣ���02���Զ�*/
                                            {
												V_ucEnergyNum = V_ucFrozenConver645Len / C_AccurateEnergyCommLen;
												V_ucEnergyChgeLen = 0;
												V_ucResultEnergyChgeLen = 0;
												for(V_uci = 0; V_uci < V_ucEnergyNum; V_uci++)
												{
													V_ulEnergyData = 0;
													if( (P_Data[V_Data_Length + V_ucEnergyChgeLen] & 0x80) == 0x80)
													{
														for(i = C_AccurateEnergyCommLen; i < 8; i++)
														{
															V_ulEnergyData <<= 8;
															V_ulEnergyData |= 0xFF;
														}
														for(i = 0; i < C_AccurateEnergyCommLen; i++)
														{
															V_ulEnergyData <<= 8;
															V_ulEnergyData |= P_Data[V_Data_Length + V_ucEnergyChgeLen + i];
														}
														V_ulEnergyData = (~V_ulEnergyData) + 1;
													}
													else
													{
														for(i = 0; i < C_AccurateEnergyCommLen; i++)
														{
															V_ulEnergyData <<= 8;
															V_ulEnergyData |= P_Data[V_Data_Length + V_ucEnergyChgeLen + i];
														}
													}
													V_ulEnergyData /= 100;
													if( (P_Data[V_Data_Length + V_ucEnergyChgeLen] & 0x80) == 0x80)
													{
														V_ulEnergyData = (~V_ulEnergyData) + 1;
													}
													PF_Ulong64ToBuffer8_698(&P_Data[V_Data_Length + V_ucResultEnergyChgeLen], &V_ulEnergyData, C_EnergyCommLen);
													/*memcpy( &P_Data[V_Data_Length + V_ucResultEnergyChgeLen], &P_Data[V_Data_Length + 1 + V_ucEnergyChgeLen], C_EnergyCommLen);*/
													V_ucEnergyChgeLen += C_AccurateEnergyCommLen;
													V_ucResultEnergyChgeLen += C_EnergyCommLen;
												}
#if 0		/*ԭ��BCD��ֱ����λ*/
                                                V_ucEnergyNum = V_ucFrozenConver645Len / C_AccurateEnergyCommLen;
                                                V_ucEnergyChgeLen = 0;
                                                V_ucResultEnergyChgeLen = 0;
                                                for(V_uci = 0; V_uci < V_ucEnergyNum; V_uci++)
                                                {
                                                    memcpy( &P_Data[V_Data_Length + V_ucResultEnergyChgeLen], &P_Data[V_Data_Length + 1 + V_ucEnergyChgeLen], C_EnergyCommLen);
                                                    V_ucEnergyChgeLen += C_AccurateEnergyCommLen;
                                                    V_ucResultEnergyChgeLen += C_EnergyCommLen;
                                                }
#endif
                                                V_ucFrozenConver645Len = V_ucResultEnergyChgeLen;
                                            }

											(*P_Length) -= V_ucFrozenConver645Len;
											V_Data_Length += V_ucFrozenConver645Len;
											V_ucAAFlag = 0x68;
											break;
										}
										else
										{
											return 	C_DataLenError;
										}
									}
									else
									{
										V_Data_LengthOffnei+=Str_FrozenConvert_Table[V_OADOrder16+V_k+1].V_uc645Length;
									}
								}
								else
								{
									break;
								}
							}
							if(V_ucAAFlag == 0x68)
							{
								break;
							}
						}
					}
					V_Data_LengthOff += Str_FrozenConvert_Table[V_OADOrder16].V_uc645Length;          /*����ƫ��*/
				}
			}

			V_jTemp += V_j;

			if( ( V_jTemp >= ( V_OADTabLen_T + 2 ) ) || ( V_ucRateNumJudge == C_RateNumError ) )    /*�����ڲ�1�ֽ�0*/
			{
				if( V_ucAAFlag != 0x68 )
				{
					if((* P_Length) >= 1)
					{
						P_Data[V_Data_Length] = C_NotSupportAOD_DataBB;    /*����¼����*/
						(*P_Length) -= 1;
						V_Data_Length += 1;
						V_NullNum++;
						V_NullNumCC++;
					}
					else
					{
						return 	C_DataLenError;
					}
				}
			}
			P_Data_Id_OAD++;
			V_OADNum++;
		}

		if(V_DI2Temp == (Str_698FreezeDataTable[V_i].V_DI2))    /*�жϷ��Ӷ���*/
		{
			V_OADNum -= V_TimeNum;    /*�����ж������ڡ���ţ���ȥ����OAD�ж���Ч��*/
		}

		if(V_NullNumCC >= V_OADNum)   /*���е���ѡOADȫ���鲻���������ж���*/
		{
            if( (V_DI2Temp == (Str_698FreezeDataTable[V_i].V_DI2) ) && (0 != V_TimeNum))    /*���Ӷ���������OAD�а������ڻ����+���������б��в�����OAD.�������������if�жϲ�����*/
            {
                V_Return_Flag = C_OK;
                (*P_TotalLen) += V_Data_Length;
                InF_FlashChipSelect();
                InF_ReadFlash(V_FindFlashAddr, &V_Date1[0], C_698FreeData_DateLen6);        /*����¼����*/
                InF_WriteFreezeTimeToBufer(pV_FreezeTimeBuf, &V_Date1[0], V_Mode);
            }
            else
            {
                V_Return_Flag = C_NotSupportAOD_DataCC;
                *P_TotalLen = V_TotalLen;
                *P_Length = V_Length;
            }
            return V_Return_Flag;
		}
		else
		{
			if(V_NullNum >= V_OADNum)   /*������ֲ�ͬ�������ݣ������淶�涨��û����Ч��OAD����*/
			{
                V_Return_Flag = C_NotSupportAOD_DataBB;
                *P_TotalLen = V_TotalLen;
                *P_Length = V_Length;
                return V_Return_Flag;
			}
		}
	}
	else
	{
		return V_Return_Flag;
	}

	InF_FlashChipSelect();
	InF_ReadFlash(V_FindFlashAddr,&V_Date1[0], C_698FreeData_DateLen6);    /*����¼����*/
	InF_WriteFreezeTimeToBufer(pV_FreezeTimeBuf, &V_Date1[0], V_Mode);
	(*P_TotalLen) += V_Data_Length;
	return C_OK;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Find2EventTable_Data(ulong32 V_Data_Id,Str_2Table *PStr_2Table,ushort16 *P_Line,ushort16 V_MaxLine)
����������2�����ѯ�������õ�DI2-DI0��Ӧ��2�����к�
���������ulong32 V_Data_Id�����ݱ�ʶ��DI2~DI0��
		Str_2Table *PStr_2Table��1�����ѯ�ж�Ӧ2����ṹ���ַ��
		ushort16 V_MaxLine:��Ӧ2����ṹ�����鳤��
���������ushort16 *P_Line������2�����Ӧ�кţ�
���ز�����C_OK��C_IDError��C_DataLenError��C_NoAccess��
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_Find2EventTable_Data(ulong32 V_Data_Id,Str_2Table *PStr_2Table,ushort16 *P_Line,ushort16 V_MaxLine)
{
	ushort16 V_Line;

	for(V_Line=0;V_Line<V_MaxLine;V_Line++)
	{
		if(V_Data_Id==PStr_2Table[V_Line].V_DI)
		{
			break;
		}
		else
		{
			if(DT_Flash_DI04==PStr_2Table[V_Line].V_DT_Type)/*Flash�����������ݣ�DI0��4λ��ʾ��������4λ��ʾ��ͬ��ʶ��(��ѯ4������)*/
			{
				if(0x00000000==(V_Data_Id&0x0000000F))  /*������Ϊ0*/
				{
					continue;
				}

				if((V_Data_Id&0xFFFFFFF0)==(PStr_2Table[V_Line].V_DI&0xFFFFFFF0)) /*DI0��4λ���Ƚ�*/
				{
					break;
				}
			}
			else
			{
				if( (DT_Flash_Tol_DI0_DI1==PStr_2Table[V_Line].V_DT_Type)/*||(DT_Flash_Tol_DI0_DI2==PStr_2Table[V_Line].V_DT_Type)
					|| (DT_Flash_Tol_DI0_SettEn==PStr_2Table[V_Line].V_DT_Type)||(DT_Flash_Tol_DI0_SettDe==PStr_2Table[V_Line].V_DT_Type)
					|| (DT_Flash_Tol_DI0_W_Sett_En==PStr_2Table[V_Line].V_DT_Type)||(DT_R_Flash_Tol_DI0_DI2_En==PStr_2Table[V_Line].V_DT_Type)*/
					|| (DT_Flash_Tol_DI0==PStr_2Table[V_Line].V_DT_Type) )  /*DI0��ʾ����*/
				{
					if(0x00000000==(V_Data_Id&0x000000FF))  /*������Ϊ0*/
					{
						continue;
					}

					if((V_Data_Id&0xFFFFFF00)==(PStr_2Table[V_Line].V_DI&0xFFFFFF00)) /*DI0���Ƚ�*/
					{
						break;
					}
				}
				else
				{
					if((DT_RAM_DI0==PStr_2Table[V_Line].V_DT_Type)||(DT_Ref_E23_RAMCRC_DI0==PStr_2Table[V_Line].V_DT_Type)
						||(DT_E23_DI0==PStr_2Table[V_Line].V_DT_Type)||(DT_E21CRC_DI0==PStr_2Table[V_Line].V_DT_Type)
						||(DT_E21_DI0==PStr_2Table[V_Line].V_DT_Type)||(DT_Ref_E23_RAMCRC_DI0_2==PStr_2Table[V_Line].V_DT_Type))  /*ֻ��DI0���ֵ����DI0��Ϊ0*/
					{
						if((V_Data_Id&0xFFFFFF00)==(PStr_2Table[V_Line].V_DI&0xFFFFFF00))/*DI0���Ƚ�*/
						{
							if((0x00000000!=(V_Data_Id&0x000000FF))                    /*DI0��Ϊ�㣬�ҡ����ֵ*/
								&&((V_Data_Id&0x000000FF)<=(PStr_2Table[V_Line].V_DI&0x000000FF)))
							{
								break;
							}
						}
					}
					else
					{
#if 0
						if(DT_RAM_DI1_0==PStr_2Table[V_Line].V_DT_Type)    /*ֻ��DI1���ֵ��DI1����Ϊ0*/
						{
							if((V_Data_Id&0xFFFF00FF)==(PStr_2Table[V_Line].V_DI&0xFFFF00FF))/*DI1���Ƚ�*/
							{
								if((V_Data_Id&0x0000FF00)<=(PStr_2Table[V_Line].V_DI&0x0000FF00))/*DI1��=���ֵ*/
								{
									break;
								}
							}
						}
						else
						{

							if(DT_RAM_DI1==PStr_2Table[V_Line].V_DT_Type)    /*ֻ��DI1���ֵ����DI1��Ϊ0*/
							{
								if((V_Data_Id&0xFFFF00FF)==(PStr_2Table[V_Line].V_DI&0xFFFF00FF))/*DI1���Ƚ�*/
								{
									if(((V_Data_Id&0x0000FF00)<=(PStr_2Table[V_Line].V_DI&0x0000FF00))
										&&(0x00000000!=(V_Data_Id&0x0000FF00)))/*DI1��=���ֵ,��DI1��Ϊ0*/
									{
										break;
									}
								}
							}
							else
							{
#endif
								if(DT_Flash_Tol_DI0_DI1Max==PStr_2Table[V_Line].V_DT_Type) /*ֻ��DI1���ֵ����DI1��Ϊ0,DI0��ʾ�����Ҳ�Ϊ��*/
								{
									if((V_Data_Id&0xFFFF0000)==(PStr_2Table[V_Line].V_DI&0xFFFF0000))/*DI0��DI1���Ƚ�*/
									{
										if(0x00000000==(V_Data_Id&0x000000FF))  /*������Ϊ0*/
										{
											continue;
										}

										if(((V_Data_Id&0x0000FF00)<=(PStr_2Table[V_Line].V_DI&0x0000FF00))
											&&(0x00000000!=(V_Data_Id&0x0000FF00)))/*DI1��=���ֵ,��DI1��Ϊ0*/
										{
											break;
										}
									}
								}
								else
								{	/*���ж�DI 0��������698�¼�����������*/
									if(DT_Flash_698EventTab==PStr_2Table[V_Line].V_DT_Type)
									{
										if((V_Data_Id&0xFFFFFF00)==(PStr_2Table[V_Line].V_DI&0xFFFFFF00))
										{
											break;
										}
									}
								}
#if 0
							}
						}
#endif
					}
				}
			}
		}
	}

	if(V_Line==V_MaxLine)
	{
		return C_IDError;
	}
	else
	{
		*P_Line=V_Line;
		return C_OK;
	}
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_OrganEventData(ulong32 *P_Data_Id_OAD,ulong32 P_Str_3EventTableAddr,ushort16 *P_TotalLen,
					ushort16 *P_Length,ulong32 V_FindFlashAddr,uchar8 *P_Data,uchar8 V_DT_Type,ushort16 V_3EventTableLen)
��������������OAD��ű���֯���������ݡ���֧�ֵ�OAD����1�ֽ�C_NotSupportAOD_Data
���������ulong32 *P_Data_Id_OAD����������OAD�б��������Զ�ӦOAD˳�򣬵�����OADΪFFFFFFFF���ʾ��������¼��ȡ��¼OAD����
		ulong32 P_Str_3EventTableAddr��3�����׵�ַ
		ushort16 *P_TotalLen����Ϊ����Ϊ����֯�����ܳ��ȣ��������������֯���ݳ��Ⱥ���ܳ��ȣ����ܳ���Ϊ�������������ܳ��ȣ�
		ushort16 *P_Length����Ϊ����Ϊʣ�໺�泤�ȣ��������������֯���ݳ��Ⱥ�ʣ�໺���ܳ���
		ulong32 V_FindFlashAddr��������¼����Flash��ַ;
		uchar8 *P_Data��������¼���ݴ�Ż���,ֱ�Ӳ��ö����ݴ������Ļ���;
		uchar8 V_DT_Type������������������ʲô4����;
		ushort16 V_3EventTableLen:3���������
�����������
���ز�����C_OK��C_IICError��C_Error��C_DataLenError��C_IDError��C_NoData
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_OrganEventData(ulong32 *P_Data_Id_OAD, ulong32 P_Str_3EventTableAddr, ushort16 *P_TotalLen, ushort16 *P_Length, ulong32 V_FindFlashAddr, uchar8 *P_Data, uchar8 V_DT_Type, ushort16 V_3EventTableLen)
{
	ushort16 V_Data_Length, V_Data_LengthOff, V_Data_LengthOffnei;
	uchar8 P_DataOAD_NumTab[C_698Event_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_OADTabLen_T, V_OADOrder16, V_k, V_EventSign;
	uchar8 V_Return_Flag, V_j, V_ucAAFlag=0;
	ulong32 V_FlashAddr;
	Str_4aTable * PStr_4aTable=NULL;
	uchar8 V_Sign = 0;
	Str_3dEventTable *P_Str_3dEventTableAddr=NULL;
	Str_3cTable *P_Str_3cTable_Flash=NULL;
	uchar8 V_Str_4aTableLen;
	Str_3dEventTable V_Str_3dEventTableAddr;
	Str_3cTable  V_Str_3cTable_Flash;
    uchar8 V_ucRateNumJudge, V_ucFrozenConver645Len;
    uchar8 V_DataTemp[ProgCrc_O + C_CRCLen2] = {0};
    ulong32 V_ulOAD;
    uchar8 V_ucDataFlag;

	V_Data_Length = 0;
	if(DT_Flash_698EventTab==V_DT_Type)     /*�й����б�*/
	{
		P_Str_3dEventTableAddr = (Str_3dEventTable *)P_Str_3EventTableAddr;
		V_Str_3dEventTableAddr = P_Str_3dEventTableAddr[V_3EventTableLen];

		V_Return_Flag = SF_ReadE2Three(V_Str_3dEventTableAddr.V_TBLen_E2BakeUp1Addr, 1, &P_OADTabLen_T[0]);
		if(C_OK == V_Return_Flag)
		{
			V_Sign |= C_W_SafeFlag_1;
			V_OADTabLen_T = P_OADTabLen_T[0] * C_698Event_OADTabDataType;   /*��ű�ÿ��OAD��������ֽ�*/
			if(V_OADTabLen_T>C_698Event_OADTabLen)  /*���ݳ��Ȱ�ȫ���ж�*/
			{
				return 	C_Error;    /*�쳣*/
			}
			V_Return_Flag = SF_ReadE2Three(V_Str_3dEventTableAddr.V_TB_E2BakeUp1Addr, V_OADTabLen_T, P_DataOAD_NumTab);
			if(C_OK == V_Return_Flag)
			{
				V_Sign |= C_W_SafeFlag_2;
			}
			if(0 != V_OADTabLen_T)    /*�й����б�*/
			{
				V_Sign |= C_W_SafeFlag_3;
			}
		}

		if(0xFFFFFFFF == V_Str_3dEventTableAddr.PStr_4aTableAddr)   /*û��4���ֱ��������Ѵ����ú���ֻ�����зּ�������*/
		{
			return C_Error;
		}
		PStr_4aTable = (Str_4aTable *)(V_Str_3dEventTableAddr.PStr_4aTableAddr);
		V_Str_4aTableLen = V_Str_3dEventTableAddr.V_Str_4aTableLen;
	}
	else
	{
		P_Str_3cTable_Flash = (Str_3cTable *)P_Str_3EventTableAddr;
		V_Str_3cTable_Flash = P_Str_3cTable_Flash[V_3EventTableLen];
		PStr_4aTable = (Str_4aTable *)(V_Str_3cTable_Flash.PStr_4TableAddr);
		V_Str_4aTableLen = V_Str_3cTable_Flash.V_Str_4TableLen;
	}

    V_ulOAD = P_Data_Id_OAD[0];
	P_Data_Id_OAD++;

	while(0xFFFFFFFF != (*P_Data_Id_OAD) )
	{
		V_Data_LengthOff = 0;
		V_ucAAFlag = 0;

		for( V_j = 0; V_j < V_Str_4aTableLen; V_j++)
		{
			if( PStr_4aTable[V_j].V_OAD == *P_Data_Id_OAD )
			{
				if( (*P_Length) >= (PStr_4aTable[V_j].V_DataLen & C_EventOutSign))
				{
					if(0xFFFFFFFF == V_FindFlashAddr)   /*����������*/
					{
                        memset(&P_Data[V_Data_Length], 0x00, (PStr_4aTable[V_j].V_DataLen & C_EventOutSign));
					}
					else
					{
						V_FlashAddr = V_FindFlashAddr + V_Data_LengthOff;
						InF_FlashChipSelect();
						InF_ReadFlash(V_FlashAddr, &P_Data[V_Data_Length], (PStr_4aTable[V_j].V_DataLen & C_EventOutSign));    /*����¼����*/
					}

                    if( V_ulOAD == CProgram_Note_1)
                    {
                        V_ucDataFlag = InF_RD_ProgRecordReg(CProgram_Note_1, V_DataTemp);
                        if(V_ucDataFlag == C_OK)
                        {
                            if( *P_Data_Id_OAD == CProgOADGather )
                            {
                                memcpy(&P_Data[V_Data_Length], &V_DataTemp[ProgDI_O], (PStr_4aTable[V_j].V_DataLen & C_EventOutSign));
                            }
                            else if( *P_Data_Id_OAD == CEventEndTime )
                            {
                                memcpy(&P_Data[V_Data_Length], &V_DataTemp[ProgEndTime], (PStr_4aTable[V_j].V_DataLen & C_EventOutSign));
                            }
                            else
                            {
                                ; /*else����Ҫ�滻����*/
                            }
                        }   /*else����Ҫ�滻����*/
                    }

					(*P_Length) -= (PStr_4aTable[V_j].V_DataLen & C_EventOutSign);
					V_Data_Length += (PStr_4aTable[V_j].V_DataLen & C_EventOutSign);

					V_ucAAFlag = 0x68;
					break;
				}
				else
				{
					return 	C_DataLenError;
				}
			}
			else
			{
				V_Data_LengthOff += (PStr_4aTable[V_j].V_DataLen & C_EventOutSign);
			}
		}
		if( V_ucAAFlag == 0x68 )        /*�Ѿ����ҵ���������һ��*/
		{
			P_Data_Id_OAD++;
			continue;
		}

		if( V_Sign == C_W_SafeFlag )    /*�й����б�*/
		{
			for( V_j = 0; V_j < P_OADTabLen_T[0]; V_j++)
			{
				PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Event_OADTabDataType * V_j], &V_OADOrder16);
				V_EventSign=(V_OADOrder16 & 0xE000);    /*�¼�������������־������Ʒ�ʽ�й�*/
				V_OADOrder16 &= 0x1FFF;
				if(V_OADOrder16 >= Str_FrozenConvert_Table_Len)
				{
					return 	C_Error;        /*�쳣������������*/
				}

				if( (*P_Data_Id_OAD) == (Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD|V_EventSign))   /*����OAD���*/
				{
                    if( SF_FrozenData_JudgeRateNum(V_OADOrder16, *P_Data_Id_OAD) == C_Error )
                    {
                        V_ucRateNumJudge = C_RateNumError;
                        break;
                    }   /*������δ������Ӧ��*/

                    V_ucFrozenConver645Len = SF_GetFrozenDataLen(V_OADOrder16);

					if( (* P_Length) >= V_ucFrozenConver645Len )
					{
						if( 0xFFFFFFFF == V_FindFlashAddr )     /*����������*/
						{
                            memset(&P_Data[V_Data_Length], 0x00, V_ucFrozenConver645Len);
						}
						else
						{
							V_FlashAddr = V_FindFlashAddr + V_Data_LengthOff;
							InF_FlashChipSelect();
							InF_ReadFlash(V_FlashAddr, &P_Data[V_Data_Length], V_ucFrozenConver645Len);    /*����¼����*/
						}

						(* P_Length) -= V_ucFrozenConver645Len;
						V_Data_Length += V_ucFrozenConver645Len;
						V_ucAAFlag = 0x68;
						break;
					}
					else
					{
						return 	C_DataLenError;
					}
				}
				else
				{
					if(C_array == Str_FrozenConvert_Table[V_OADOrder16].V_uc698Type)        /*�����ʽOAD,��ѯ�Ƿ�Ϊ��OAD*/
					{
						V_Data_LengthOffnei = 0;

						for(V_k = 0;    ; V_k++)
						{
							if((V_OADOrder16 + V_k + 1) >= Str_FrozenConvert_Table_Len)
							{
								return 	C_Error;    /*�쳣������������*/
							}

							if ( ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD & 0xFFFFFF00)
                              == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD & 0xFFFFFF00))
							{
								if( (*P_Data_Id_OAD) == ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD | V_EventSign ) )
								{
                                    if(SF_FrozenData_JudgeRateNum((V_OADOrder16 + V_k + 1), *P_Data_Id_OAD) == C_Error)
                                    {
                                         V_ucRateNumJudge = C_RateNumError;
                                         break;
                                     }  /*������δ������Ӧ��*/

                                    V_ucFrozenConver645Len = SF_GetFrozenDataLen(V_OADOrder16 + V_k + 1);

									if( (*P_Length) >= V_ucFrozenConver645Len )
									{
										if(0xFFFFFFFF == V_FindFlashAddr)   /*�����������ڼ�¼����*/
										{
                                            memset(&P_Data[V_Data_Length], 0x00, V_ucFrozenConver645Len);
										}
										else
										{
											V_FlashAddr=V_FindFlashAddr+V_Data_LengthOff + V_Data_LengthOffnei;
											InF_FlashChipSelect();
											InF_ReadFlash(V_FlashAddr, &P_Data[V_Data_Length], V_ucFrozenConver645Len);    /*����¼����*/
										}

										(* P_Length) -= V_ucFrozenConver645Len;
										V_Data_Length += V_ucFrozenConver645Len;
										V_ucAAFlag = 0x68;
										break;
									}
									else
									{
										return 	C_DataLenError;
									}
								}
								else
								{
									V_Data_LengthOffnei += Str_FrozenConvert_Table[V_OADOrder16+V_k+1].V_uc645Length;
								}
							}
							else
							{
								break;
							}
						}
						if(V_ucAAFlag == 0x68)
						{
							break;
						}
					}
				}
				V_Data_LengthOff += Str_FrozenConvert_Table[V_OADOrder16].V_uc645Length;    /*����ƫ��*/
			}
			if(V_ucAAFlag == 0x68)      /*�Ѿ����ҵ���������һ��*/
			{
				P_Data_Id_OAD++;
				continue;
			}
		}

		if((V_ucAAFlag != 0x68) || (V_ucRateNumJudge == C_RateNumError))    /*�����ڲ�1�ֽ�C_NotSupportAOD_Data*/
		{
			if((* P_Length) >= 1)
			{
				P_Data[V_Data_Length] = C_NotSupportAOD_DataBB;    /*����¼����*/
				(* P_Length) -= 1;
				V_Data_Length += 1;
			}
			else
			{
				return 	C_DataLenError;
			}
		}
		P_Data_Id_OAD++;
	}

	(*P_TotalLen) += V_Data_Length;
	return C_OK;
}

/*********************************************************************************
����ԭ�ͣ�void SF_Initial_GVStrNextEventData(void)
������������ʼ��GV_Str_NextLoadTime�ṹ�壬CRC�쳣������
�����������
�����������
���ز�������
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
void SF_Initial_GVStrNextLoadTime(void)
{
	GV_FreezeLastNum[0]=0xFF;
	GV_FreezeLastNum[1]=0xFF;
	GV_FreezeLastNum[2]=0xFF;
}

/*********************************************************************************
����ԭ�ͣ�void SF_Initial_GVStrNextEventData(void)
������������ʼ��GV_Str_NextEvent�ṹ�壬CRC�쳣������
�����������
�����������
���ز�������
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
void SF_Initial_GVStrNextEventData(void)
{
	GV_Str_NextEvent.PV_Str_2Table=NULL;
	GV_Str_NextEvent.V_NextSign=0;
	GV_Str_NextEvent.V_LastNum=0;
	GV_Str_NextEvent.V_CRC16=0xFFFF;	/*��ʼ��CRC����*/

	SF_Initial_GVStrNextLoadTime();
}

/******************************************************************************************************************************************************************
����ԭ�ͣ�uchar8  InF_ReadEventData(ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,uchar8 * V_NextSign,
								ushort16 * P_Data_Length,uchar8 V_timeFlash)
�������������¼���¼�ӿں�������������1��2��9������2Ϊ��ʼ�������ڼ����ݣ�����Ϊ0���������ݸ��ݴ����OAD˳��
���������ulong32 *P_Data_Id_OAD�����ݱ�ʶOAD����һ��OAD��ʾ��ȡ�������ͣ�
		����300D0201����ʾ��ȡȫʧѹ�¼������1�ֽ�00��ʾ��ʾ�����ڶ�ȡ����00��ʾ��ȡ��XX�μ�¼����ʱ*P_FixTime��V_BlockNum��Ч.
		����OAD˳��Ϊ�������Զ�ӦOAD˳�򣬵�����OADΪFFFFFFFF���ʾ��������¼��ȡ��¼OAD����(�����̶��б�)��
		uchar8 *P_FixTime������ʱ���¼�飬12���ֽڡ���ʱ�����䳭����ǰ6���ֽڱ�ʾ��ʼʱ�䣬��6���ֽڱ�ʾ����ʱ�䣬ʱ���ʽssmmhhDDMMYY
		���̶�ʱ�䳭��ʱ��ǰ6���ֽ����6���ֽ���ͬ����ʱ������������֡ʱ��ǰ6���ֽ�Ϊ��һ���¼ʱ�䡣
		uchar8 *V_NextSign����Ϊ�����������֡��ʶ��Bit5--Bit4��ʾ�Ƿ�Ϊ����֡��������Ϊ1ʱ��ʾΪ����֡��������1ʱ��ʾ���״γ�����
		ushort16 *V_Length�������ݻ�������󳤶ȣ�
		uchar8 V_timeFlash:��ʾ����ʱ�䳭���¼���¼ʱ���Ǹ��ݷ���ʱ�䡢���ǽ���ʱ�䡣AA��ʾ����ʱ�䣬��������Ϊ����ʱ��
���������uchar8 *P_FixTime����Ϊ�������ʱ�����к���֡ʱ��������һ����¼���¼ʱ��(ǰ6���ֽ�)��
		ushort16 *V_Length����������ʵ�ʳ��ȣ�
		uchar8 *P_Data�������ݴ�Ż��棻
		uchar8 *V_NextSign����Ϊ�����������֡��ʶ��
		Bit5-Bit4��ʾ�Ƿ�Ϊ����֡��������Ϊ1ʱ��ʾΪ����֡��������1ʱ��ʾ���״γ�����
		Bit0-Bit3��ʾ�����������ݰ������¼���¼����(���10��).
		Bit7-Bit6:��ʾ���̶�ʱ������䳭�����ݣ����������Ƿ�������1����¼
		1����ʾ�������ݰ������1����¼��0����ʾ�������ݲ��������1����¼�������¼���¼���1������¼���¼�ӿں���
		(�簲ʱ���������ڼ����ݲ�����Ϊ0)�������̶�ʱ������䳭�������1����¼����Ϊ�������ݵ����1����ʱ���ǰ����顣
���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_NoData��C_Error
����λ�ã�
��     ע�������̶�ʱ�䳭��ʱ����������Ϊ���ʱ������ݡ�
		��ʱ�����䳭��ʱ����1��ʱ�������Ϊ��ʼʱ����������1��ʱ������ݣ�
		�޸�ʱ�䣺���̶�ʱ�䳭��ʱ���������1������ʱ��Ҫ������ݡ�
		�����䳭���������������������(�����޸�ʱ���ж������Ļ�)��
		��ʾ���濪��
***********************************************************************************************************************************************/
uchar8 InF_ReadEventData(ulong32 *P_Data_Id_OAD, uchar8 *P_FixTime, uchar8 *P_Data, uchar8 *V_NextSign, ushort16 *P_Data_Length, uchar8 V_timeFlash)
{
	uchar8 V_Return_Flag, V_DI[4], V_NextEvent[8], V_LastNum;
	ushort16 V_Line, V_DataEventTolLen, V_E2Addr, V_TotalLen;
	Str_2Table *PStr_2TableAddr=NULL;
	Str_2Table *PStr_2TableAddr1=NULL;

	uchar8 P_Dgree[CLAll_Loss_Vol_Degree], V_Num, V_NumMax, V_CompareSign, V_CompareSign1, V_NextSign1 = C_NoNextSign;
	ulong32 V_Dgree, V_Temp32, P_FlashAddr1[2];

	Str_3cTable Str_3cTableAddr;
	Str_3cTable *PStr_3cTableAddr = NULL;

	Str_3dEventTable Str_3dEventTableAddr;
	Str_3dEventTable *PStr_3dEventTableAddr = NULL;
	ushort16 V_CRC16;
	ushort16 V_3dEventTableLine;
	uchar8 V_698Event_MaxNum;  /*����¼����*/
	uchar8 V_Num1;
	uchar8 V_CompareSign2;

	V_Temp32=(ulong32)GV_Str_NextEvent.PV_Str_2Table;
	PF_Ulong32ToBuffer4(&V_NextEvent[0], &V_Temp32, 4);
	V_NextEvent[4] = GV_Str_NextEvent.V_NextSign;
	V_NextEvent[5] = GV_Str_NextEvent.V_LastNum;
	V_CRC16 = GV_Str_NextEvent.V_CRC16;

	PF_Ushort16ToBuffer2(&V_NextEvent[6], &V_CRC16);

	V_Return_Flag = PF_Check_CRC(&V_NextEvent[0], 8);    			/*����֡����ȫ�ֱ���*/

	PF_Ulong32ToBuffer4(&V_DI[0], &P_Data_Id_OAD[0], 4);
    if ( ( V_Return_Flag == C_OK )
      && ( GV_Str_NextEvent.V_NextSign == C_NextSign )
      && ( GV_Str_NextEvent.V_LastNum < C_698Event_MaxNum )
      && ( C_NextSign == ((*V_NextSign) & C_NextSign_Judge ) ) )	/*����֡����*/
    {
        PStr_2TableAddr1 = GV_Str_NextEvent.PV_Str_2Table;
        V_LastNum = GV_Str_NextEvent.V_LastNum;          			/*��n�μ�¼���ñ������ڸ�ֵʱ���ж�GV_Str_NextEvent.V_LastNum���1*/
    }
    else															/*�Ǻ���֡��ȫ�ֱ����жϴ��������²��Ҳ���*/
    {
        SF_Initial_GVStrNextEventData();			 				/*��ʼ��CRC����,û�к���֡*/

        V_LastNum = V_DI[0];										/*�����Ϊ0*/

        V_Return_Flag = SF_Find1Table_Data(V_DI[3], &V_Line);		/*����1����*/

        if(V_Return_Flag != C_OK)
        {
             return V_Return_Flag;
        }

        PStr_2TableAddr = (Str_2Table * )(Str_1Table_DI3[V_Line].PStr_2TableAddr);         /*DI3��Ӧ��2�����ַ*/

        V_Return_Flag = SF_Find2EventTable_Data(P_Data_Id_OAD[0], PStr_2TableAddr,&V_Line, Str_1Table_DI3[V_Line].V_Str_2TableLen);

        if(V_Return_Flag!=C_OK)
        {
             return V_Return_Flag;
        }

        PStr_2TableAddr1 = &PStr_2TableAddr[V_Line];
    }

    if(DT_Flash_698EventTab == PStr_2TableAddr1->V_DT_Type)     /*���ݳ��������*/
    {
        PStr_3dEventTableAddr = (Str_3dEventTable *)(PStr_2TableAddr1->PStr_3TableAddr);

        if(PStr_2TableAddr1->V_LineNum >= Str_3dTable_Flash_Len)
        {
            return C_DataLenError;
        }
        V_3dEventTableLine = PStr_2TableAddr1->V_LineNum;
        V_DataEventTolLen = SF_GetEventDataLen(PStr_3dEventTableAddr[V_3dEventTableLine].V_TB_E2BakeUp1Addr, PStr_3dEventTableAddr[V_3dEventTableLine].V_TBLen_E2BakeUp1Addr, PStr_3dEventTableAddr[V_3dEventTableLine].PStr_4aTableAddr, PStr_3dEventTableAddr[V_3dEventTableLine].V_Str_4aTableLen);        /*3C���̶������б����ݳ��ȹ̶�*/

        if ( ( 0 == V_DataEventTolLen ) || ( 0xFFFF == V_DataEventTolLen ) )
        {
            return C_DataLenError;
        }

        Str_3dEventTableAddr = PStr_3dEventTableAddr[V_3dEventTableLine];
        V_E2Addr = Str_3dEventTableAddr.V_Num_E2BakeUp1Addr;    /*ȡFlash��¼����E2��ַ*/
    }
    else
    {
        V_DataEventTolLen = PStr_2TableAddr1->V_DataLen;
        if(PStr_2TableAddr1->V_LineNum >= Str_3cTable_Flash_Len)
        {
            return C_AbnormalError;    /*����������*/
        }
        PStr_3cTableAddr = (Str_3cTable *)(PStr_2TableAddr1->PStr_3TableAddr);
        Str_3cTableAddr = PStr_3cTableAddr[PStr_2TableAddr1->V_LineNum];
        V_E2Addr = Str_3cTableAddr.V_Num_E2BakeUp1Addr;    /*ȡFlash��¼����E2��ַ*/
    }

    V_Return_Flag = SF_ReadE2Three(V_E2Addr, CLAll_Loss_Vol_Degree, &P_Dgree[0]);
    if(C_OK != V_Return_Flag)
    {
        return C_IICError;
    }

    PF_Buffer4ToUlong32(&P_Dgree[0], &V_Dgree, CLAll_Loss_Vol_Degree);

    if ( ( 0 == V_Dgree ) || ( V_LastNum > V_Dgree ) )  /*�����Ϊ0,û�м�¼����ͳһ����C_NoData*/
    {
        * V_NextSign = 0;
        SF_Initial_GVStrNextEventData();			/*��ʼ��CRC����,û�к���֡*/
        return C_NoData;
    }

    if( 0xAA == V_timeFlash )     /*�������Խ���ʱ�䳭�����ݣ��жϸ��¼��Ƿ��н���ʱ�䣬����û�У��򷵻�C_NoData*/
    {
        if(C_OK == InF_JudgeNoEndTimeEvent(P_Data_Id_OAD[0]) )
        {
            SF_Initial_GVStrNextEventData();	   /*��ʼ��CRC����,û�к���֡*/
            return C_NoData;
        }
    }

    if ( ( P_Data_Id_OAD[0] & 0xFFFFFF00 ) == (CProgKD_Note_1 & 0xFFFFFF00))					/*��Կ����*/
    {
        V_698Event_MaxNum = C_698Key_UpdateEvent_MaxNum;										/*��Կ����2��*/
    }
    else if ( ( ( P_Data_Id_OAD[0] & 0xFFFFFF00 ) == ( CBroadcastTime_Note_1 & 0xFFFFFF00 ) )	/*�㲥Уʱ*/
           || ( ( P_Data_Id_OAD[0] & 0xFFFFFF00 ) == ( CPow_Down_Note_1 & 0xFFFFFF00 ) ) )		/*�����¼*/
    {
        V_698Event_MaxNum = C_698Event_MaxNum100;												/*�㲥Уʱ�͵���100��*/
    }
    else
    {
        V_698Event_MaxNum = C_698Event_MaxNum;													/*�����¼���¼10��*/
    }

    if( 0 == V_DI[0] )      /*��ʱ�䳭������*/
    {
        V_CompareSign = PF_Campare_Data(&P_FixTime[0],&P_FixTime[CLDate_Time],CLDate_Time);
        if(C_GreaterThan == V_CompareSign)
        {
            return C_NoData;    /*����������*/
        }

        if(V_Dgree > V_698Event_MaxNum)     /*��¼��������C_698Event_MaxNum����ã���C_698Event_MaxNum��������*/
        {
            V_NumMax = V_698Event_MaxNum;
        }
        else
        {
            V_NumMax = V_Dgree;
        }

        V_Num1 = V_NumMax;
        if ( ( V_LastNum < V_NumMax ) && ( 0 != V_LastNum ) )    /*����֡����*/
        {
            V_Num1 = V_LastNum;
        }

        *V_NextSign = 0;
        V_TotalLen = 0;
        V_Return_Flag = C_NoData;       /*������Ϊû������*/

        if(C_Equal == V_CompareSign)    /*�̶�ʱ�䳭��*/
        {
            V_Num = 1;
            SF_Initial_GVStrNextEventData();			/*��ʼ��CRC����,û�к���֡*/

            for(    ; V_Num <= V_NumMax; V_Num++)      /*�����1�β��𣬴Ӻ���ǰ�顣ȡ���ʱ���*/
            {
                V_Temp32 = V_Dgree - V_Num + 1;          /*����N�����ݣ������ҵ�ǰ(n-N+1)�ε�ַ*/

                if(DT_Flash_698EventTab != PStr_2TableAddr1->V_DT_Type)
                {
                      SF_GetFlashAddr(V_Temp32,Str_3cTableAddr.V_StaFlashAddr, V_DataEventTolLen, Str_3cTableAddr.V_EndFlashAddr, &P_FlashAddr1[0]);   /*��ȡ��ǰ����Flashҳ��ַ��ҳ�ڵ�ַ*/
                }
                else
                {
                      SF_GetFlashAddr(V_Temp32,Str_3dEventTableAddr.V_StaFlashAddr, V_DataEventTolLen, Str_3dEventTableAddr.V_EndFlashAddr, &P_FlashAddr1[0]);   /*��ȡ��ǰ����Flashҳ��ַ��ҳ�ڵ�ַ*/
                }

                P_FlashAddr1[0] += P_FlashAddr1[1];

                if(P_FlashAddr1[0] > C_Flash_Max_Addr)
                {
                    return C_Error;     /*����������*/
                }

                InF_FlashChipSelect();
                if(V_timeFlash == 0xAA)  /*���ݽ���ʱ�����*/
                {
                    InF_ReadFlash((P_FlashAddr1[0] + CLAll_Loss_Vol_Degree + CLEventHPTime), &V_NextEvent[0], CLDate_Time);    /*����¼��������ʱ��*/
                }
                else        /*����Ϊ����ʱ�����*/
                {
                    InF_ReadFlash((P_FlashAddr1[0] + CLAll_Loss_Vol_Degree), &V_NextEvent[0], CLDate_Time);    /*����¼��������ʱ��*/
                }

                V_CompareSign1 = PF_Campare_Data(&V_NextEvent[0], &P_FixTime[0], CLDate_Time);
                if(C_Equal != V_CompareSign1)
                {
                    continue;
                }
                else
                {
                    if(0xFFFFFFFF == P_Data_Id_OAD[1])    /*���г���*/
                    {
                        if(V_DataEventTolLen > (* P_Data_Length))
                        {
                            return C_DataLenError;
                        }
                        InF_FlashChipSelect();
                        InF_ReadFlash(P_FlashAddr1[0], P_Data, V_DataEventTolLen);      /*��ȡ��¼����*/
                        V_Return_Flag = C_OK;
                        V_TotalLen = V_DataEventTolLen;
                    }
                    else
                    {
                        V_Return_Flag = SF_OrganEventData(&P_Data_Id_OAD[0], PStr_2TableAddr1->PStr_3TableAddr, &V_TotalLen,P_Data_Length, P_FlashAddr1[0], P_Data,PStr_2TableAddr1->V_DT_Type, PStr_2TableAddr1->V_LineNum);    /*��֯��¼����*/
                    }
                    break;
                }
            }
            if(C_OK == V_Return_Flag)
            {
                *V_NextSign += 1;
                if(1 == V_Num)    /*���1�μ�¼*/
                {
                    *V_NextSign |= C_NextSign_Last;
                }
                *P_Data_Length = V_TotalLen;
            }
            return V_Return_Flag;
        }
        else    /*���䳭��*/
        {

#if 0
            for(    ; V_Num <= V_NumMax; V_Num++)    /*�����1�β��𣬴Ӻ���ǰ�顣ȡ���ʱ���*/
#endif

            for(    ; V_Num1 > 0; V_Num1--)          /*������β��𣬴�ǰ������ҡ�*/
            {
                V_Temp32 = V_Dgree - V_Num1 + 1;     /*����N�����ݣ������ҵ�ǰ(n-N+1)�ε�ַ*/

                if(DT_Flash_698EventTab != PStr_2TableAddr1->V_DT_Type)
                {
                      SF_GetFlashAddr(V_Temp32, Str_3cTableAddr.V_StaFlashAddr, V_DataEventTolLen, Str_3cTableAddr.V_EndFlashAddr, &P_FlashAddr1[0]);   /*��ȡ��ǰ����Flashҳ��ַ��ҳ�ڵ�ַ*/
                }
                else
                {
                      SF_GetFlashAddr(V_Temp32,Str_3dEventTableAddr.V_StaFlashAddr, V_DataEventTolLen, Str_3dEventTableAddr.V_EndFlashAddr, &P_FlashAddr1[0]);   /*��ȡ��ǰ����Flashҳ��ַ��ҳ�ڵ�ַ*/
                }
                P_FlashAddr1[0] += P_FlashAddr1[1];

                if(P_FlashAddr1[0] > C_Flash_Max_Addr)
                {
                    SF_Initial_GVStrNextEventData();			/*��ʼ��CRC����,û�к���֡*/
                    return C_Error;         /*����������*/
                }

                InF_FlashChipSelect();

                if(V_timeFlash == 0xAA)   /*���ݽ���ʱ�����*/
                {
                    InF_ReadFlash((P_FlashAddr1[0] + CLAll_Loss_Vol_Degree + CLEventHPTime), &V_NextEvent[0], CLDate_Time);    /*����¼��������ʱ��*/
                }
                else        /*����Ϊ����ʱ�����*/
                {
                    InF_ReadFlash((P_FlashAddr1[0] + CLAll_Loss_Vol_Degree), &V_NextEvent[0], CLDate_Time);    /*����¼��������ʱ��*/
                }

                V_CompareSign2 = PF_Campare_Data(&V_NextEvent[0], &P_FixTime[CLDate_Time], CLDate_Time);    /*�ȽϽ�ֹʱ��*/
                V_CompareSign1 = PF_Campare_Data(&V_NextEvent[0], &P_FixTime[0], CLDate_Time);    /*��ʼʱ��*/

                if ( ( C_LessThan == V_CompareSign2 )
                  && ( C_LessThan != V_CompareSign1 ) )     /*��Ч���ݣ�ǰ�պ�*/
                {
                    if( 0xFFFFFFFF == P_Data_Id_OAD[1] )    /*���г�������1�����ȣ�������������Ҫ��*/
                    {
                        if( V_DataEventTolLen > (* P_Data_Length) )
                        {
                            V_NextSign1 = C_NextSign;        /*����֡*/
                            V_Return_Flag=C_DataLenError;
                            break;
                        }
                        *P_Data_Length -= V_DataEventTolLen;
                        InF_FlashChipSelect();
                        InF_ReadFlash(P_FlashAddr1[0], &P_Data[V_TotalLen], V_DataEventTolLen);   /*��ȡ��¼����*/

                        V_TotalLen += V_DataEventTolLen;
                        V_Return_Flag = C_OK;
                    }
                    else
                    {
                        V_Return_Flag = SF_OrganEventData(&P_Data_Id_OAD[0], PStr_2TableAddr1->PStr_3TableAddr, &V_TotalLen, P_Data_Length,P_FlashAddr1[0], &P_Data[V_TotalLen], PStr_2TableAddr1->V_DT_Type, PStr_2TableAddr1->V_LineNum);         /*��֯��¼����*/
                        if(C_OK != V_Return_Flag)
                        {
                            if(C_DataLenError == V_Return_Flag)     /*���Ȳ���*/
                            {
                                V_NextSign1 = C_NextSign;           /*����֡*/
                            }
                            else
                            {
                                V_NextSign1 = C_NoNextSign;
                            }
                            break;
                        }
                    }
                    if(C_OK == V_Return_Flag)
                    {
                        if( 1 == V_Num1 )   /*���1�μ�¼*/
                        {
                            *V_NextSign |= C_NextSign_Last;
                        }
                        *V_NextSign += 1;
                    }
                }

            }
            *P_Data_Length = V_TotalLen;
            *V_NextSign |= V_NextSign1;         /*����֡����*/

            if(C_OK!=V_Return_Flag)
            {
                if(C_NextSign == V_NextSign1)   /*�к���֡*/
                {
                    GV_Str_NextEvent.PV_Str_2Table = PStr_2TableAddr1;    /*ȫ�ֱ�������*/
                    GV_Str_NextEvent.V_NextSign = C_NextSign;
                    GV_Str_NextEvent.V_LastNum = V_Num1;
                    V_Temp32 = (ulong32)GV_Str_NextEvent.PV_Str_2Table;
                    PF_Ulong32ToBuffer4(&V_NextEvent[0], &V_Temp32, 4);
                    V_NextEvent[4] = GV_Str_NextEvent.V_NextSign;
                    V_NextEvent[5] = GV_Str_NextEvent.V_LastNum;
                    GV_Str_NextEvent.V_CRC16 = PF_Cal_CRC(&V_NextEvent[0], 6);
                }
            }

            if(C_NextSign != V_NextSign1)   /*û�к���֡*/
            {
                SF_Initial_GVStrNextEventData();			/*��ʼ��CRC����,û�к���֡*/
            }

            if(0 != V_TotalLen)             /*�м�¼����*/
            {
                return C_OK;
            }
            else
            {
                return C_NoData;
            }
        }
    }
    else    /*��������������*/
    {
        if(V_DI[0] > V_698Event_MaxNum)	      /*��������������,����ͳһ��ֵ*/
        {
            return C_NoData;
        }

        V_Temp32 = V_Dgree - V_DI[0] + 1;      /*����N�����ݣ������ҵ�ǰ(n-N+1)�ε�ַ����ʼ�Ѿ��ж�DI��V_Dgree��С*/

        if(DT_Flash_698EventTab != PStr_2TableAddr1->V_DT_Type)
        {
              SF_GetFlashAddr(V_Temp32, Str_3cTableAddr.V_StaFlashAddr, V_DataEventTolLen, Str_3cTableAddr.V_EndFlashAddr, &P_FlashAddr1[0]);   /*��ȡ��ǰ����Flashҳ��ַ��ҳ�ڵ�ַ*/
        }
        else
        {
              SF_GetFlashAddr(V_Temp32, Str_3dEventTableAddr.V_StaFlashAddr, V_DataEventTolLen, Str_3dEventTableAddr.V_EndFlashAddr, &P_FlashAddr1[0]);   /*��ȡ��ǰ����Flashҳ��ַ��ҳ�ڵ�ַ*/
        }

        if(P_FlashAddr1[0] > C_Flash_Max_Addr)
        {
            return C_Error;         /*����������*/
        }

        P_FlashAddr1[0] += P_FlashAddr1[1];
        if( 0xFFFFFFFF == P_Data_Id_OAD[1] )   /*���г���*/
        {
            if(V_DataEventTolLen>(* P_Data_Length))
            {
                return C_DataLenError;
            }
            InF_FlashChipSelect();
            InF_ReadFlash(P_FlashAddr1[0],P_Data,V_DataEventTolLen);    /*��ȡ��¼����*/
            V_TotalLen=V_DataEventTolLen;
            V_Return_Flag=C_OK;
        }
        else
        {
            V_TotalLen = 0;
            V_Return_Flag = SF_OrganEventData(&P_Data_Id_OAD[0], PStr_2TableAddr1->PStr_3TableAddr, &V_TotalLen, P_Data_Length, P_FlashAddr1[0], P_Data, PStr_2TableAddr1->V_DT_Type, PStr_2TableAddr1->V_LineNum);     /*��֯��¼����*/
        }

        *P_Data_Length = V_TotalLen;
        (*V_NextSign) = 1;
        if(0x01 == V_DI[0])    /*��ǰ��¼*/
        {
            *V_NextSign |= C_NextSign_Last;
        }
        SF_Initial_GVStrNextEventData();			/*��ʼ��CRC����,û�к���֡*/
        return V_Return_Flag;
    }
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_GetFreezeIntervalTime(ulong32 V_Data_Id_OAD,uchar8 *P_StarTime,uchar8 *P_EndTime,ulong32 *P_SubTime)
�������������ݲ�ͬ�ඳ�ᣬ����P_EndTime��P_StarTime���ʱ�䣬�ꡢ�¡��ա�ʱ���֣�ͬʱ�ж��¼�ʱ�������Ƿ����(����Ӷ��ᣬ���ж����Ƿ����)��
���������ulong32 V_Data_Id_OAD��ĳ�ඳ��OAD
uchar8 *P_StarTime�����������Ϊ��ʼʱ�䣬��ʽΪssmmhhDDMMYY
uchar8 *P_EndTime�����������Ϊ��ʼʱ�䣬��ʽΪssmmhhDDMMYY
���������ulong32 *P_SubTime��P_EndTime��P_StarTime���ʱ�䣬���ݸ�ʽΪhex�룻�쳣ֵΪFFFFFFFF��
���ز�����C_Equal,C_GreaterThan��C_LessThan
����˵����
���û��ƣ�
��     ע��P_EndTime�������P_StarTime
*********************************************************************************/
uchar8 SF_GetFreezeIntervalTime(ulong32 V_Data_Id_OAD,uchar8 *P_StarTime,uchar8 *P_EndTime,ulong32 *P_SubTime)
{
	uchar8 V_Return_Flag;
	uchar8 V_Return_Flag1;
	ulong32 V_ultemp;

	V_Return_Flag=PF_Campare_Data(P_StarTime,P_EndTime,CLDate_Time);
	if(C_LessThan!=V_Return_Flag)
	{
		*P_SubTime=0xFFFFFFFF;/*���������ڣ�P_EndTime�������P_StarTime*/
		return V_Return_Flag;
	}

	V_Return_Flag=C_LessThan;
	switch(V_Data_Id_OAD&0x00FF0000)
	{
		case(C_RelatedOAD_Min&0x00FF0000):   /*���Ӷ���*/
		{
			if(P_StarTime[0]==P_EndTime[0])/*�����*/
			{
				V_Return_Flag=C_Equal;
			}
			V_Return_Flag1=PF_TimeSub_Min_698(P_StarTime,P_EndTime,P_SubTime);
			if(C_TIMEERR==V_Return_Flag1)
			{
				*P_SubTime=0xFFFFFFFF;
			}
		}break;

		case(C_RelatedOAD_Hour&0x00FF0000):   /*Сʱ����*/
		{
			if( (P_StarTime[1] == P_EndTime[1] ) && ( P_StarTime[2] == P_EndTime[2] ) )/*���ӡ������*/
			{
				V_Return_Flag=C_Equal;
			}
			V_Return_Flag1=PF_TimeSub_Hour_698(P_StarTime,P_EndTime,P_SubTime);
			if(C_TIMEERR==V_Return_Flag1)
			{
				*P_SubTime=0xFFFFFFFF;
			}
		}break;

		case(C_RelatedOAD_Day&0x00FF0000):   /*�ն���*/
		{
			V_Return_Flag=PF_Campare_Data(&P_StarTime[1],&P_EndTime[1],3);/*�ж�ʱ����*/

			V_Return_Flag1=PF_TimeSub_Day_698(P_StarTime,P_EndTime,&V_ultemp);
			if(C_TIMEERR == V_Return_Flag1)
			{
				*P_SubTime = 0xFFFFFFFF;
			}
			else
			{
				*P_SubTime = V_ultemp;
			}
		}break;

		case(C_RelatedOAD_Month&0x00FF0000):   /*�¶���*/
		{
			V_Return_Flag=PF_Campare_Data(P_StarTime,P_EndTime,4);/*�ж���ʱ����*/
			uchar8 V_tempYear;
			ushort16 V_tempHex1,V_tempHex2;

			//V_tempHex1 = PF_BCDtoHexOneByte(P_EndTime[5]);
			//V_tempHex2 = PF_BCDtoHexOneByte(P_StarTime[5]);
			PF_Buffer2ToUshort16(&P_EndTime[5], &V_tempHex1);
			PF_Buffer2ToUshort16(&P_StarTime[5], &V_tempHex2);

			V_tempYear = V_tempHex1-V_tempHex2;		/*�꣬�������ж�ʱ���С�������ܳ���С��*/
			*P_SubTime = V_tempYear*12;

			//V_tempHex1 = PF_BCDtoHexOneByte(P_EndTime[4]);
			//V_tempHex2 = PF_BCDtoHexOneByte(P_StarTime[4]);

			//*P_SubTime=*P_SubTime+V_tempHex1-V_tempHex2;/*��*/
			*P_SubTime = *P_SubTime + P_EndTime[4] - P_StarTime[4];/*��*/
			if(C_GreaterThan==V_Return_Flag)
			{
				*P_SubTime-=1;
			}

			V_Return_Flag1=PF_DataTimeActive_698(P_StarTime, C_DT_Start_ss, CLDate_Time);
			if((C_OK!=V_Return_Flag1)||(C_OK!=PF_DataTimeActive_698(P_EndTime, C_DT_Start_ss, CLDate_Time)))
			{
				*P_SubTime=0xFFFFFFFF;
			}
		}break;

//		case(C_RelatedOAD_Year&0x00FF0000):/*�궳��*/
//		{
//			V_Return_Flag=PF_Campare_Data(P_StarTime,P_EndTime,5);/*�ж�����ʱ����*/
//			uchar8 V_tempYear;
//			uchar8 V_tempHex1,V_tempHex2;
//
//			V_tempHex1=(P_EndTime[5]>>4)*10+(P_EndTime[5]&0x0F) ;/* ת��Ϊ16����*/
//			V_tempHex2=(P_StarTime[5]>>4)*10+(P_StarTime[5]&0x0F) ;/* ת��Ϊ16����*/
//
//			V_tempYear=V_tempHex1-V_tempHex2;/*�꣬�������ж�ʱ���С�������ܳ���С��*/
//			*P_SubTime=V_tempYear;
//
//			if(C_GreaterThan==V_Return_Flag)
//			{
//				*P_SubTime-=1;
//			}
//
//			V_Return_Flag1=PF_DataTimeActive(P_StarTime,C_DT_Start_ss,6);
//			if((C_OK!=V_Return_Flag1)||(C_OK!=PF_DataTimeActive(P_EndTime,C_DT_Start_ss,6)))
//			{
//				* P_SubTime=0xFFFFFFFF;
//			}
//		}
//		break;

		default:
			*P_SubTime=0xFFFFFFFF;
	}
	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_GetFreezeStartTime(ulong32 V_Data_Id_OAD,uchar8 *P_StarTime,ushort16 V_IntervalTime)
��������������ĳ���ᡢ��ʼʱ�䡢���ʱ�䣬�õ�����ʱ��
���������ulong32 V_Data_Id_OAD��ĳ�ඳ��OAD
		uchar8 *P_StarTime����Ϊ���������Ϊ��ʼʱ�䣬��ʽΪmmhhDDMMYY
		ushort16 V_IntervalTime��������ڣ�hex��ʽ����λ����ĳ�ඳ�ᶨ�壻
���������uchar8 *P_StarTime����Ϊ���������Ϊ���������ʼʱ�䣬��ʽΪmmhhDDMMYY
���ز�����C_OK,C_Error(�곬2099��,�򴥷��ඳ��)
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
/*�����ж��·�����*/
/*const uchar8 C_MonthNum1[12]={31,28,31,30,31,30,31,31,30,31,30,31};*/

uchar8 SF_GetFreezeStartTime(ulong32 V_Data_Id_OAD, uchar8 *P_ucSourceTime, ulong32 V_ulAddMins)
{
#if 1
	uchar8 V_Return_Flag = C_OK, V_ucDay;
	ulong32 V_ulSec_Temp = 0;
	uchar8 V_ucTimeBuff[CLDate_Time] = {0};
	ushort16 V_usYear;


	if( (C_RelatedOAD_Min & 0x00FF0000) == (V_Data_Id_OAD & 0x00FF0000) )		/*���Ӷ���*/
	{
		memcpy(&V_ucTimeBuff[C_DT_Start_mm], &P_ucSourceTime[C_DT_Start_mm], (CLDate_Time - C_DT_Start_mm) );
		V_ulSec_Temp = PF_DateTime_to_Second(P_ucSourceTime);
		V_ulSec_Temp += V_ulAddMins*60;
	}
	else if( (C_RelatedOAD_Hour & 0x00FF0000) == (V_Data_Id_OAD & 0x00FF0000) )	/*Сʱ����*/
	{
		memcpy(&V_ucTimeBuff[C_DT_Start_hh], &P_ucSourceTime[C_DT_Start_hh], (CLDate_Time - C_DT_Start_hh) );
		V_ulSec_Temp = PF_DateTime_to_Second(P_ucSourceTime);
		V_ulSec_Temp += V_ulAddMins*60*60;
	}
	else if( (C_RelatedOAD_Day & 0x00FF0000) == (V_Data_Id_OAD & 0x00FF0000) )	/*�ն���*/
	{
		memcpy(&V_ucTimeBuff[C_DT_Start_DD], &P_ucSourceTime[C_DT_Start_DD], (CLDate_Time - C_DT_Start_DD) );
		V_ulSec_Temp = PF_DateTime_to_Second(P_ucSourceTime);
		V_ulSec_Temp += V_ulAddMins*60*60*24;
	}
	else if( (C_RelatedOAD_Month & 0x00FF0000) == (V_Data_Id_OAD & 0x00FF0000) )	/*�¶���*/
	{
		memcpy(&V_ucTimeBuff[C_DT_Start_MM], &P_ucSourceTime[C_DT_Start_MM], (CLDate_Time - C_DT_Start_MM) );
		V_ucDay = PF_BCDtoHexOneByte(Day[V_ucTimeBuff[C_DT_Start_MM] ] );
		if(V_ucTimeBuff[C_DT_Start_MM] == 2)
		{
			PF_Buffer2ToUshort16(&P_ucSourceTime[C_DT_Start_NN], &V_usYear);
			if(PF_Is_Leap_Year(V_usYear) == 1)
			{
				V_ucDay += 1;
			}
		}
		V_ulSec_Temp = PF_DateTime_to_Second(P_ucSourceTime);
		V_ulSec_Temp += V_ulAddMins*60*60*24*V_ucDay;
	}
	else
	{
		V_Return_Flag = C_Error;
	}

	if(V_Return_Flag == C_OK)
	{
		PF_Second_to_dateTime(V_ulSec_Temp, P_ucSourceTime);
	}
	return V_Return_Flag;
#endif
#if 0
	uchar8 V_Return_Flag = C_OK;
	uchar8 V_ucTemp = 0, V_ucMthTemp = 0;
	uchar8 V_ucTimeBuff[CLDate_Time] = {0};
	ulong32 V_ulCalTemp = 0,V_ulTemp = 0,V_ulYearTemp = 0;
	ulong64 V_ulCalTemp64 = 0;
	uchar8 V_ucDataBuff[8] = {0};
	uchar8 i = 0,V_ucMonCycle = 0;
	ushort16 V_usDayCal = 0,V_usMonCal = 0,V_usYearCal = 0, V_usTemp = 0;

	V_ucTimeBuff[C_DT_Start_ss] = P_ucSourceTime[C_DT_Start_ss]; /*��ֵ��*/

	switch(V_Data_Id_OAD & 0x00FF0000)
	{
		case(C_RelatedOAD_Min & 0x00FF0000):	/*���Ӷ���*/
		{
			V_ucTemp = P_ucSourceTime[C_DT_Start_mm];

			V_ulCalTemp64 = V_ulAddMins + V_ucTemp;	/*�ӷ��ӿ�ʼ�ۼ�*/
			if(V_ulCalTemp64 > 0x0100000000)
			{
				V_ulCalTemp64 = 0x00000000FFFFFFFF;
			}

			PF_Ulong64ToBuffer8(V_ucDataBuff, &V_ulCalTemp64, 8);
			PF_Buffer4ToUlong32(V_ucDataBuff, &V_ulCalTemp, 4);

			V_ulTemp = V_ulCalTemp % 60;
			PF_Ulong32ToBuffer4(&V_ucTemp, &V_ulTemp, 1);
			V_ucTimeBuff[C_DT_Start_mm] = V_ucTemp;	/*��ֵ����*/

			V_ulAddMins = V_ulCalTemp / 60;
		}	/*�˴�����Ҫbreak����ΪҪ��������Сʱ���ա��¡���*/

		case(C_RelatedOAD_Hour & 0x00FF0000):	/*Сʱ����*/
		{
			if( (V_Data_Id_OAD & 0x00FF0000) == (C_RelatedOAD_Hour & 0x00FF0000) )	/*����Сʱ���ᣬ���Ӳ�����*/
			{
				V_ucTimeBuff[C_DT_Start_mm] = P_ucSourceTime[C_DT_Start_mm];
			}

			V_ucTemp = P_ucSourceTime[C_DT_Start_hh];

			V_ulAddMins += V_ucTemp;	/*�ۼ�Сʱ*/
			V_ulTemp = V_ulAddMins % 24;
			PF_Ulong32ToBuffer4(&V_ucTemp, &V_ulTemp, 1);
			V_ucTimeBuff[C_DT_Start_hh] = V_ucTemp;	/*��ֵСʱ*/

			V_ulAddMins = V_ulAddMins / 24;
		}	/*�˴�����Ҫbreak����ΪҪ���������ա��¡���*/

		case(C_RelatedOAD_Day & 0x00FF0000):	/*�ն���*/
		{
			if( (V_Data_Id_OAD & 0x00FF0000) == (C_RelatedOAD_Day & 0x00FF0000) )	/*�����ն��ᣬ���ӡ�Сʱ������*/
			{
				V_ucTimeBuff[0] = P_ucSourceTime[0];
				V_ucTimeBuff[1] = P_ucSourceTime[1];
				V_ucTimeBuff[2] = P_ucSourceTime[2];
			}

			V_ucTemp = P_ucSourceTime[C_DT_Start_DD];
			V_ulAddMins += V_ucTemp;	/*�ۼ���*/

			if(P_ucSourceTime[C_DT_Start_MM] == 2)	/*2�����ж�����*/
			{
				PF_Buffer2ToUshort16(&P_ucSourceTime[C_DT_Start_NN], &V_usTemp);	/*�������ǰ��,Ĭ��Ϊ20XX��*/
				V_ulYearTemp = (ulong32)V_usTemp;

				if( ( (V_ulYearTemp % 4) == 0 ) )	/*20XX��ֻҪ��4������������*/
				{
					V_ucMthTemp = 29;
				}
				else
				{
					V_ucMthTemp = 28;
				}
			}
			else
			{
				V_ucMthTemp = C_MonthNum[P_ucSourceTime[C_DT_Start_MM] - 1];
			}

			if(V_ulAddMins > V_ucMthTemp)
			{
				V_ucMonCycle = V_ucTemp;

				for( i = 1; ; i ++ )
				{
					if( (V_ucMonCycle + (i-1) - 1) == C_MonTwoOffset)	/*2��*/
					{
						PF_Buffer2ToUshort16(&P_ucSourceTime[C_DT_Start_NN], &V_usTemp);	/*�������ǰ��,Ĭ��Ϊ20XX��*/

						V_ulYearTemp = (ulong32)V_usTemp;	/*�������ǰ��,Ĭ��Ϊ20XX��*/

						if( ( (V_ulYearTemp % 4) == 0 ) )	/*20XX��ֻҪ��4������������*/
						{
							V_usDayCal += 29;
						}
						else
						{
							V_usDayCal += 28;
						}
					}
					else
					{
						V_usDayCal += C_MonthNum[V_ucMonCycle + (i-1) - 1];
					}

					if(V_usDayCal >= V_ulAddMins )
					{
						V_usMonCal += i;	/*�½�λ*/
						break;
					}

					if( (V_ucMonCycle + (i-1) - 1) == C_NovOffset)
					{
						V_usYearCal ++;		/*���λ*/
						i = 0;
						V_ucMonCycle = 1;	/*��1�����¿�ʼ����*/
					}

					if( (V_usMonCal >= C_MonMaxLim) || (V_usYearCal >= C_YearMaxLim) )	/*��ֹ��ѭ��*/
					{
						break;
					}
				}

				V_ulTemp = V_ulAddMins - (V_usDayCal - C_MonthNum[V_ucMonCycle + (i-1) - 1]);	/*��ǰ��*/

				if(V_usYearCal >= 1)
				{
					V_ulAddMins = (12 - V_ucTemp) + ( (V_usYearCal - 1) * 12 ) + V_usMonCal;
				}
				else
				{
					V_ulAddMins = V_usMonCal - 1;	/*�½�λʱ������i��1ѭ���������1*/
				}
			}
			else
			{
				V_ulTemp = V_ulAddMins;
				V_ulAddMins = 0;
			}

			V_ucTimeBuff[C_DT_Start_DD] = V_ucTemp;	/*��ֵ��*/
		}	/*�˴�����Ҫbreak����ΪҪ���������¡���*/

		case(C_RelatedOAD_Month & 0x00FF0000):		/*�¶���*/
		{
			if( (V_Data_Id_OAD & 0x00FF0000) == (C_RelatedOAD_Month & 0x00FF0000) )	/*�����¶��ᣬ�ա����ӡ�Сʱ������*/
			{
				V_ucTimeBuff[0] = P_ucSourceTime[0];
				V_ucTimeBuff[1] = P_ucSourceTime[1];
				V_ucTimeBuff[2] = P_ucSourceTime[2];
			}

			V_ucTemp = P_ucSourceTime[C_DT_Start_MM];

			V_ulAddMins += V_ucTemp;	/*�ۼ���*/
			if( 0 == (V_ulAddMins % 12) )	/*��ǰ��������*/
			{
				V_ulTemp = 12;
				if(V_ulAddMins >= 12)	/*���λ*/
				{
					V_ulAddMins = (V_ulAddMins / 12) - 1;
				}
				else
				{
					V_ulAddMins /= 12;
				}
			}
			else
			{
				V_ulTemp = V_ulAddMins % 12;
				V_ulAddMins /= 12;
			}

			PF_Ulong32ToBuffer4(&V_ucTemp, &V_ulTemp, 1);
			V_ucTimeBuff[C_DT_Start_MM] = V_ucTemp;	/*��ֵ��*/
		}	/*�˴�����Ҫbreak����ΪҪ����������*/

		case(C_RelatedOAD_Year & 0x00FF0000):	/*�궳��*/
		{
			if( (V_Data_Id_OAD & 0x00FF0000) == (C_RelatedOAD_Year & 0x00FF0000) )	/*�����궳�ᣬ�¡��ա����ӡ�Сʱ������*/
			{
				V_ucTimeBuff[0] = P_ucSourceTime[0];
				V_ucTimeBuff[1] = P_ucSourceTime[1];
				V_ucTimeBuff[2] = P_ucSourceTime[2];
				V_ucTimeBuff[3] = P_ucSourceTime[3];
				V_ucTimeBuff[4] = P_ucSourceTime[4];
			}

			PF_Buffer2ToUshort16(&P_ucSourceTime[C_DT_Start_NN], &V_usTemp);	/*�������ǰ��,Ĭ��Ϊ20XX��*/

			V_usTemp += (ushort16)V_ulAddMins;
			if(V_usTemp > 2099)	/*���쳣����BCDΪ99��*/
			{
				V_Return_Flag = C_Error;
			}

			PF_Ushort16ToBuffer2(&V_ucTimeBuff[C_DT_Start_NN], &V_usTemp);	/*��ֵ��*/
		}break;

		default:
		{
			V_Return_Flag = C_Error;
		}break;
	}

	PF_CopyDataBytes(V_ucTimeBuff, P_ucSourceTime, CLDate_Time);	/*���ۼӺ�ʱ�䴫��Ŀ���ַ*/

	return V_Return_Flag;
#endif
}
/*********************************************************************************
����ԭ�ͣ�ulong32 SF_JudgeFreezeFlashAddrValid(ulong32 V_FindFlashAddr)
�����������ж϶�������Flash��ַ�Ƿ���Ч�����ݶ������ݴ洢�����������޸������򶳽�����ǰ5�ֽ������޸�ΪȫFF(�ײ�Ϊȫ0)������Ϊ��ַ��Ч
���������ulong32 V_FindFlashAddr�����ж�Flash��¼��ַ
�����������
���ز�����ulong32����Ч�򷵻�V_FindFlashAddr����Ч����ȫFF
����˵����
���û��ƣ�
��     ע������ʱ���������ü�¼5�ֽ������޸�Ϊ
*********************************************************************************/
ulong32 SF_JudgeFreezeFlashAddrValid(ulong32 V_FindFlashAddr)
{
	uchar8 V_FindTime[C_698FreeData_DateLen6],V_i,V_Return_Flag;

	InF_FlashChipSelect();
	InF_ReadFlash(V_FindFlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*����¼��������ʱ��*/

	for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
	{
		if(C_Flash_NoEmpty!=V_FindTime[V_i])/*�ж������Ƿ�ΪȫFF�����ײ�Ϊ00��˵����ʱ�����*/
		{
			break;
		}
	}

	if(V_i>=C_698FreeData_DateLen6)/*����ȫFF*/
	{
		return 0xFFFFFFFF;
	}
	else
	{
		V_Return_Flag=PF_DataTimeActive_698(&V_FindTime[0],C_DT_Start_ss,C_698FreeData_DateLen6);/*�ж�ʱ��Ϸ��ԣ�ȥ���ײ�û�м�¼���ݣ���ȫ00����*/
		if(C_OK==V_Return_Flag)
		{
			return V_FindFlashAddr;
		}
		else
		{
			return 0xFFFFFFFF;
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�ulong32 SF_FindNextFreezeFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr,
											ulong32 V_FlashAddrLate,ulong32 V_FlashAddrEar,ushort16 V_DataLen)
������������ȡ���������¼��Flash��ַ��
���������uchar8 V_ProNum�����Ӷ����÷�����
		uchar8 V_Order��Str_698FreezeDataTable�������
		ulong32 V_FindFlashAddr�����������¼��ַ
		ulong32 V_FlashAddrLate�������¼Flashҳ��ַ
		ulong32 V_FlashAddrEar������1�����ɼ�¼��ַ�����Ե�ַ������ҳ��1����¼��ַ
		ushort16 V_DataLen�����������¼�����ܳ���
�����������
���ز�����ulong32���������¼Flash��ַ���쳣����ȫFF
����˵����
���û��ƣ�
��     ע��FlashST---Ear...Late---FlashEnd;Ear...Late---FlashEnd;FlashST...Late---Ear...FlashEnd;
		����---��ʾ��Ч���ݣ�����ͬһҳ
*********************************************************************************/
ulong32 SF_FindNextFreezeFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr,ulong32 V_FlashAddrLate,ulong32 V_FlashAddrEar,ushort16 V_DataLen)
{
	uchar8 V_FindTime[C_698FreeData_DateLen6],V_i;
	ushort16 V_OffLen;
	ulong32 V_FlashAddr,V_Return_Flag;

	V_FlashAddr=0xFFFFFFFF;
	if((V_FlashAddrLate&0xFFFFF000)==(V_FlashAddrEar&0xFFFFF000))/*ͬһҳ*/
	{
		V_FindFlashAddr+=V_DataLen;/*������¼��ַ*/
		if((V_FindFlashAddr<(V_FlashAddrLate+C_OneFlashPage))&&(V_FindFlashAddr>V_FlashAddrEar))/*Flash�������ж�*/
		{
			V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FindFlashAddr);
		}
		else
		{
			V_FlashAddr=0xFFFFFFFF;
		}
	}
	else
	{
		if(V_FlashAddrLate>V_FlashAddrEar)/*FlashST---Ear...Late---FlashEnd; Ear...Late---FlashEnd;*/
		{
			V_OffLen=V_FindFlashAddr%C_OneFlashPage;/*ҳ��ƫ�ƣ�������������¼���ݳ��ȣ�*/
			V_OffLen+=(2*V_DataLen);									/* +2*V_DataLen����������¼���ȼ�������Ҫ���ҵļ�¼����*/

			if(V_OffLen<=C_OneFlash_PageNum)/*û�п�ҳ*/
			{
				V_FlashAddr=V_FindFlashAddr+V_DataLen;

				InF_FlashChipSelect();
				InF_ReadFlash(V_FlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*����¼��������ʱ��*/

				for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
				{
					if(C_Flash_NoEmpty!=V_FindTime[V_i])/*�ж������Ƿ�ΪȫFF�����ײ�Ϊ00��˵����ʱ�����*/
					{
						break;
					}
				}

				if(V_i>=C_698FreeData_DateLen6)/*����ȫFF,ȡ��ҳ��¼���ݵ�ַ*/
				{
					V_FlashAddr=(V_FindFlashAddr&0xFFFFF000)+C_OneFlashPage+C_LoadProfile_RevMode;
					if(V_FlashAddr>(V_FlashAddrLate+C_OneFlashPage))
					{
						V_FlashAddr=0xFFFFFFFF;
					}
					else
					{
						V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FlashAddr);
					}
				}
			}
			else
			{
				V_FlashAddr=(V_FindFlashAddr&0xFFFFF000)+C_OneFlashPage+C_LoadProfile_RevMode;
				if(V_FlashAddr>(V_FlashAddrLate+C_OneFlashPage))
				{
					V_FlashAddr=0xFFFFFFFF;
				}
				else
				{
					V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FlashAddr);
				}
			}
		}
		else/*FlashST...Late---Ear...FlashEnd;*/
		{
			ulong32 V_StaFlashAddr,V_EndFlashAddr;
			uchar8 V_DI2;

			V_StaFlashAddr=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;
			V_EndFlashAddr=Str_698FreezeDataTable[V_Order].V_EndFlashAddr;

			V_DI2=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);
			if(V_DI2==Str_698FreezeDataTable[V_Order].V_DI2)/*���Ӷ���*/
			{
				ushort16 V_E2Addr_LoadP_Flash_Ear,V_E2Addr_LoadP_Flash_Late;
				V_Return_Flag=SF_GetMinFreezePro_E2andFlashAddr(V_ProNum,&V_StaFlashAddr,&V_EndFlashAddr,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*���ݷ��Ӷ��᷽���ţ���ȡ�÷�������������¼E2��ַ���÷�����ʼ������Flash��ַ*/
				if(C_OK!=V_Return_Flag)
				{
					return 0xFFFFFFFF;
				}
			}

			if((V_FindFlashAddr>=V_FlashAddrEar)&&(V_FindFlashAddr<(V_EndFlashAddr+C_OneFlashPage)))/*Ear...FlashEnd*/
			{
				V_OffLen=V_FindFlashAddr%C_OneFlashPage;/*ҳ��ƫ�ƣ�������������¼���ݳ��ȣ�*/
				V_OffLen+=(2*V_DataLen);									/* +2*V_DataLen����������¼���ȼ�������Ҫ���ҵļ�¼����*/

				if(V_OffLen<=C_OneFlash_PageNum)/*û�п�ҳ*/
				{
					V_FlashAddr=V_FindFlashAddr+V_DataLen;

					InF_FlashChipSelect();
					InF_ReadFlash(V_FlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*����¼��������ʱ��*/

					for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
					{
						if(C_Flash_NoEmpty!=V_FindTime[V_i])/*�ж������Ƿ�ΪȫFF�����ײ�Ϊ00��˵����ʱ�����*/
						{
							break;
						}
					}

					if(V_i>=C_698FreeData_DateLen6)/*����ȫFF,ȡ��ҳ��¼���ݵ�ַ*/
					{
						V_FlashAddr=(V_FindFlashAddr&0xFFFFF000)+C_OneFlashPage+C_LoadProfile_RevMode;
						if(V_FlashAddr>(V_EndFlashAddr+C_OneFlashPage))
						{
							V_FlashAddr=V_StaFlashAddr+C_LoadProfile_RevMode;/*��ҳ��ַ*/
						}
						V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FlashAddr);
					}
				}
				else
				{
					V_FlashAddr=(V_FindFlashAddr&0xFFFFF000)+C_OneFlashPage+C_LoadProfile_RevMode;
					if(V_FlashAddr>(V_EndFlashAddr+C_OneFlashPage))
					{
						V_FlashAddr=V_StaFlashAddr+C_LoadProfile_RevMode;
					}

					V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FlashAddr);
				}
			}
			else/*FlashST...Late*/
			{
				V_OffLen=V_FindFlashAddr%C_OneFlashPage;/*ҳ��ƫ�ƣ�������������¼���ݳ��ȣ�*/
				V_OffLen+=(2*V_DataLen);									/* +2*V_DataLen����������¼���ȼ�������Ҫ���ҵļ�¼����*/

				if(V_OffLen<=C_OneFlash_PageNum)/*û�п�ҳ*/
				{
					V_FlashAddr=V_FindFlashAddr+V_DataLen;

					InF_FlashChipSelect();
					InF_ReadFlash(V_FlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*����¼��������ʱ��*/

					for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
					{
						if(C_Flash_NoEmpty!=V_FindTime[V_i])/*�ж������Ƿ�ΪȫFF�����ײ�Ϊ00��˵����ʱ�����*/
						{
							break;
						}
					}

					if(V_i>=C_698FreeData_DateLen6)/*����ȫFF,ȡ��ҳ��¼���ݵ�ַ*/
					{
						V_FlashAddr=(V_FindFlashAddr&0xFFFFF000)+C_OneFlashPage+C_LoadProfile_RevMode;
						if(V_FlashAddr>(V_FlashAddrLate+C_OneFlashPage))
						{
							V_FlashAddr=0xFFFFFFFF;
						}
						else
						{
							V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FlashAddr);
						}
					}
				}
				else
				{
					V_FlashAddr=(V_FindFlashAddr&0xFFFFF000)+C_OneFlashPage+C_LoadProfile_RevMode;
					if(V_FlashAddr>(V_FlashAddrLate+C_OneFlashPage))
					{
						V_FlashAddr=0xFFFFFFFF;
					}
					else
					{
						V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FlashAddr);
					}
				}
			}
		}
	}

	if(0xFFFFFFFF!=V_FlashAddr)
	{
		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*����¼��������ʱ��*/
		V_Return_Flag=PF_DataTimeActive_698(&V_FindTime[0],C_DT_Start_ss,C_698FreeData_DateLen6);/*�ж�ʱ��Ϸ��ԣ�ȥ���ײ�û�м�¼���ݣ���ȫ00����*/
		if(C_OK!=V_Return_Flag)
		{
			V_FlashAddr=0xFFFFFFFF;
		}
	}

	return V_FlashAddr;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_JudgeFreezeProjectAgree(uchar8 V_i)
�����������жϸ��ඳ���У����᷽���Ƿ�һ��
���������uchar8 V_i����ͬ���᷽����ţ����ݱ�ʶOAD��
�����������
���ز�����C_OK(���᷽��һ��)��C_Error
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_JudgeFreezeProjectAgree(uchar8 V_i)
{
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADOrder16,V_j,V_Mode;
	uchar8 V_Return_Flag,V_Return_Flag1=C_Error;
	Str_3aTable V_Str_3aTable;

	if(V_i>=Str_698FreezeDataTable_Len)/*�쳣�ж�*/
	{
		return V_Return_Flag1;
	}

	V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;/*698���᳤�ȡ���������������Str_3aTable�к�*/
	if(V_Order >= Str_3aTable_E23RAM_Len)
	{
		return 	V_Return_Flag1;/*�쳣*/
	}

	V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
	V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
	if(C_OK==V_Return_Flag)
	{
		V_OADTabLen_T=P_OADTabLen_T[0];
		V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*��ű�ÿ��OAD���C_698Free_OADTabDataType���ֽ�,Ŀǰ6�ֽڡ�2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/
		if(V_OADTabLen_T>C_698Free_OADTabLen)/*���ݳ��Ȱ�ȫ���ж�*/
		{
			return 	V_Return_Flag1;		/*�쳣*/
		}

		V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;/*698������ű�����Str_3aTable�к�*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return 	V_Return_Flag1;		/*�쳣*/
		}

		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);
		if(C_OK!=V_Return_Flag)
		{
			return 	V_Return_Flag1;		/*�쳣*/
		}

		V_OADTabLen_T=V_OADTabLen_T/C_698Free_OADTabDataType;
		PF_Buffer2ToUshort16(&P_DataOAD_NumTab[2],&V_OADOrder16);/*��������*/
		V_Mode=V_OADOrder16;					/*ȡ��ͬ����ģʽ����*/
		for(V_j=1;V_j<V_OADTabLen_T;V_j++)
		{
			PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType*V_j+2],&V_OADOrder16);
			if(V_Mode!=V_OADOrder16)
			{
				break;
			}
		}

		if(V_j>=V_OADTabLen_T)/*����ģʽ��ͬ*/
		{
			V_Return_Flag1=C_OK;
		}
	}

	return V_Return_Flag1;
}
/******************************************************************************************
����ԭ�ͣ�uchar8 SF_JudgeReadCycSame(uchar8 V_ProNum,uchar8 V_i,ushort16 V_IntervalTime,ushort16 *P_usFreezCyc))
�����������жϳ��������붳�������Ƿ�һ��
���������uchar8 V_ProNum�����Ӷ����÷�����
		uchar8 V_i����ͬ���᷽����ţ����ݱ�ʶOAD��
		ushort16 V_IntervalTime���������ڣ�
�����������
���ز�����0xAA���ض�������һ�¡�0x55��һ��
����˵����
���û��ƣ�1����ȡ��������2���ж����������Ƿ�һ��
��     ע��
*********************************************************************************/
uchar8 SF_JudgeReadCycSame(uchar8 V_ProNum,uchar8 V_i,ushort16 V_IntervalTime)
{
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADCyc16;
	uchar8 V_Return_Flag,V_Return_Flag1=0x55;
	Str_3aTable V_Str_3aTable;
	uchar8 V_DI;

	if(V_i>=Str_698FreezeDataTable_Len)/*�쳣�ж�*/
	{
		return	V_Return_Flag1;
	}

	V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;/*698���᳤�ȡ���������������Str_3aTable�к�*/
	if(V_Order >= Str_3aTable_E23RAM_Len)
	{
		return 	V_Return_Flag1;/*�쳣*/
	}

	V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
	V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
	if(C_OK==V_Return_Flag)
	{
		V_OADTabLen_T=P_OADTabLen_T[0];
		V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*��ű�ÿ��OAD���C_698Free_OADTabDataType���ֽ�,Ŀǰ6�ֽڡ�2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/
		if(V_OADTabLen_T>=C_698Free_OADTabLen)/*���ݳ��Ȱ�ȫ���ж�*/
		{
			return 	V_Return_Flag1;/*�쳣*/
		}
		V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;/*698������ű�����Str_3aTable�к�*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return 	V_Return_Flag1;/*�쳣*/
		}
		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);
		if(C_OK!=V_Return_Flag)
		{
			return 	V_Return_Flag1;/*�쳣*/
		}
		V_DI=(uchar8)(C_RelatedOAD_Min>>16);
		if(Str_698FreezeDataTable[V_i].V_DI2==V_DI)/*�жϷ��Ӷ���*/
		{
			V_OADTabLen_T=SF_GetMinFreezeNum_OADTab(V_ProNum,&P_DataOAD_NumTab[0],V_OADTabLen_T);/*��ȡ���Ӷ��᷽���ţ���Ӧ��OAD�����б�����OAD����*/
			if(0xFFFF==V_OADTabLen_T)
			{
				return 	V_Return_Flag1;/*�쳣*/
			}
		}

		PF_Buffer2ToUshort16(&P_DataOAD_NumTab[2],&V_OADCyc16);
		if(V_OADCyc16==V_IntervalTime)					/*���������ж�*/
		{
			V_Return_Flag1=0xAA;
		}
	}

	return V_Return_Flag1;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_GetTolMinFreeze_OADTab(uchar8 *P_DataOAD_NumTab,ushort16 *V_Length)
��������*��ȡ���Ӷ�����OAD�����б�
���������uchar8 *V_Length�������ݻ�������󳤶ȣ�
���������uchar8 *P_DataOAD_NumTab�������Ŷ�Ӧ��OAD�����б�����.
		uchar8 *V_Length����������ʵ�ʳ��ȣ�
���ز�����C_OK,C_Error
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_GetTolMinFreeze_OADTab(uchar8 *P_DataOAD_NumTab,ushort16 *V_Length)
{
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T;
	uchar8 V_Return_Flag=C_Error;
	Str_3aTable V_Str_3aTable;
	uchar8 V_i;

	if(*V_Length<C_698Free_OADTabLen)/*�����������ж�*/
	{
		return V_Return_Flag;
	}

	V_i=SF_GetStr_698FreezeDataTableOrder(C_RelatedOAD_Min);/*��ȡĳ�ඳ��������Str_698FreezeDataTable�����*/
	if(V_i>=Str_698FreezeDataTable_Len)/*�쳣�ж�*/
	{
		return V_Return_Flag;
	}

	V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;/*698���᳤�ȡ���������������Str_3aTable�к�*/
	if(V_Order >= Str_3aTable_E23RAM_Len)
	{
		return V_Return_Flag;/*�쳣*/
	}

	V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
	V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
	if(C_OK==V_Return_Flag)
	{
		V_OADTabLen_T=P_OADTabLen_T[0];
		V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*��ű�ÿ��OAD���C_698Free_OADTabDataType���ֽ�,Ŀǰ6�ֽڡ�2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/
		if(V_OADTabLen_T>C_698Free_OADTabLen)/*���ݳ��Ȱ�ȫ���ж�*/
		{
			return C_Error;/*�쳣*/
		}

		V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;/*698������ű�����Str_3aTable�к�*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return C_Error;/*�쳣*/
		}

		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);
		if(C_OK!=V_Return_Flag)
		{
			return C_Error;/*�쳣*/
		}

		*V_Length=V_OADTabLen_T;
	}

	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 InF_GetMinFreezeTolNum(void)
������������ȡ���Ӷ����ܷ�������
�����������
����������ޣ�
���ز�������������1---8���쳣FF
����˵����
���û��ƣ�
��     ע�����ݷ���OAD�б�õ�������������ͬ����������Ϊ�ǲ�ͬ����
*********************************************************************************/
uchar8 InF_GetMinFreezeTolNum(void)
{
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	ushort16 V_OADTabLen_T=C_698Free_OADTabLen;
	uchar8 V_Return_Flag;
	uchar8 V_ProNum=0xFF;
	ushort16 V_Cyc16[8]={0xFFFF};

	V_Return_Flag=SF_GetTolMinFreeze_OADTab(P_DataOAD_NumTab,&V_OADTabLen_T);
	if(C_OK==V_Return_Flag)
	{
		V_ProNum=SF_GetMinFreezeTolNum(&P_DataOAD_NumTab[0],V_OADTabLen_T,&V_Cyc16[0]);
	}
	return V_ProNum;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 InF_GetMinFreezeNum_OADTab(uchar8 V_ProNum,uchar8 *P_DataOAD_NumTab,ushort16 *P_Length)
������������ȡ���Ӷ��᷽���Ŷ�Ӧ��OAD�����б�
���������uchar8 V_ProNum�����Ӷ��᷽����(��0��ʼ)�����ܳ����ܷ�����-1,0--7
		uchar8 *P_Length�������ݻ�������󳤶ȣ�
���������uchar8 *P_DataOAD_NumTab�������Ŷ�Ӧ��OAD�����б�����.
		uchar8 *P_Length����������ʵ�ʳ��ȣ�
���ز�����C_OK,C_Error
����˵����
���û��ƣ�
��     ע�����Ӷ��᷽���Ŵ�0��ʼ�����ܳ����ܷ������������ڲ����жϷ����ŵĺ�����
*********************************************************************************/
uchar8 InF_GetMinFreezeNum_OADTab(uchar8 V_ProNum,uchar8 *P_DataOAD_NumTab,ushort16 *P_Length)
{
	ushort16 V_OADTabLen_T;
	uchar8 V_Return_Flag=C_Error;

	if(V_ProNum>7)/*0--7*/
	{
		return V_Return_Flag;
	}

	if(*P_Length<C_698Free_OADTabLen)/*�����������ж�*/
	{
		return V_Return_Flag;
	}

	V_Return_Flag=SF_GetTolMinFreeze_OADTab(P_DataOAD_NumTab,P_Length);/*��ȡ���Ӷ����ܹ����б�*/
	if(C_OK==V_Return_Flag)
	{
		V_OADTabLen_T=SF_GetMinFreezeNum_OADTab(V_ProNum,&P_DataOAD_NumTab[0],*P_Length);/*��ȡ���Ӷ��᷽���ţ���Ӧ��OAD�����б�����OAD����*/
		if(0xFFFF==V_OADTabLen_T)/*�쳣*/
		{
			V_Return_Flag=C_Error;
		}
		else
		{
			*P_Length=V_OADTabLen_T*C_698Free_OADTabDataType;
		}
	}

	return V_Return_Flag;
}
/*******************************************************************************
����ԭ�ͣ�ulong32 SF_FindMinFreezeFirstVolidOAD(ulong32 *P_Data_Id_OAD)
�������������ݷ��Ӷ���OAD�����б����ҵ�1����Ч��OAD
���������ulong32 *P_Data_Id_OAD��OAD����
���������ReturnFlag��698��������
���ز�����ulong32���ڵ�OAD�����粻���ڷ���0xFFFFFFFF,�쳣����0xFFFFFFFE
����λ�ã�
��     ע��
*******************************************************************************/
ulong32 SF_FindMinFreezeFirstVolidOAD(ulong32 *P_Data_Id_OAD)
{
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADOrder16,V_j,V_k,V_EventSign;
	uchar8 V_Return_Flag,V_ucAAFlag=0;
	Str_3aTable V_Str_3aTable;
	ulong32 V_OADNum = 0xFFFFFFFF;
	uchar8 V_i;
	ulong32 V_ulOAD;

	V_i=SF_GetStr_698FreezeDataTableOrder(C_RelatedOAD_Min);/*��ȡĳ�ඳ��������Str_698FreezeDataTable�����*/
	if(V_i>=Str_698FreezeDataTable_Len)/*�쳣�ж�*/
	{
		return	V_OADNum;
	}

	V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;/*698���᳤�ȡ���������������Str_3aTable�к�*/
	if(V_Order >= Str_3aTable_E23RAM_Len)
	{
		return 	V_OADNum;/*�쳣*/
	}

	V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
	V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
	if(C_OK==V_Return_Flag)
	{
		V_OADTabLen_T=P_OADTabLen_T[0];
		V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*��ű�ÿ��OAD���C_698Free_OADTabDataType���ֽ�,Ŀǰ6�ֽڡ�2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/
		if(V_OADTabLen_T>C_698Free_OADTabLen)/*���ݳ��Ȱ�ȫ���ж�*/
		{
			return 	V_OADNum;/*�쳣*/
		}
		V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;/*698������ű�����Str_3aTable�к�*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return 	V_OADNum;/*�쳣*/
		}
		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);
		if(C_OK!=V_Return_Flag)
		{
			return 	V_OADNum;/*�쳣*/
		}
		V_OADTabLen_T=V_OADTabLen_T/C_698Free_OADTabDataType;	/*��ű�ÿ��OAD���C_698Free_OADTabDataType���ֽ�,Ŀǰ6�ֽڡ�2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/

		while(0xFFFFFFFF!=(*P_Data_Id_OAD))
		{
			/*��ѯ�����б�*/
			V_j=0;
			V_ucAAFlag = 0;
			for(;V_j<V_OADTabLen_T;V_j++)
			{
				PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType*V_j],&V_OADOrder16);
				V_EventSign=(V_OADOrder16&0xE000);/*����698 OAD��DI1��3λ��ʾ��ͬ���ԣ�����Ʒ�ʽ�й�*/
				V_OADOrder16 &= 0x1FFF;
				if(V_OADOrder16 >= Str_FrozenConvert_Table_Len)
				{
					return 	V_OADNum;/*�쳣������������*/
				}
                if( ( (*P_Data_Id_OAD) & 0xFF000000 ) == 0x00000000 )		/*������*/
                {
                    if( ( (*P_Data_Id_OAD) & 0x00000F00 ) == 0x00000400 )	/*�߾��ȵ���*/
                    {
                        V_ulOAD = ( ( (*P_Data_Id_OAD) & 0xFFFFF0FF ) | 0x00000200 );
                    }
                    else if( ( (*P_Data_Id_OAD) & 0x00000F00 ) == 0x00000200 )
                    {
                        V_ulOAD = ( ( (*P_Data_Id_OAD) & 0xFFFFF0FF ) | 0x00000400 );
                    }
                    else
                    {
                        V_ulOAD = (*P_Data_Id_OAD);
                    }
                }
                else
                {
                    V_ulOAD = (*P_Data_Id_OAD);
                }
				if( ( (*P_Data_Id_OAD) == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD | V_EventSign ) )			/*����OAD���*/
                 || ( V_ulOAD == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD | V_EventSign ) ) )
				{
					V_ucAAFlag = 0x68;
					break;
				}
				else
				{
					if(C_array==Str_FrozenConvert_Table[V_OADOrder16].V_uc698Type)/*�����ʽOAD,��ѯ�Ƿ�Ϊ��OAD*/
					{
						for(V_k=0;;V_k++)
						{
							if((Str_FrozenConvert_Table[V_OADOrder16+V_k+1].V_ulOAD&0xFFFFFF00)==
							   (Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD&0xFFFFFF00))
							{
								if( ( (* P_Data_Id_OAD) == ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD | V_EventSign ) )
                                 || ( V_ulOAD == ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD | V_EventSign ) ) )
								{
									V_ucAAFlag = 0x68;
									break;
								}
							}
							else
							{
								break;
							}
						}
						if(V_ucAAFlag == 0x68)
						{
							break;
						}
					}
				}
			}
			if(V_ucAAFlag == 0x68)/*����OAD*/
			{
				V_OADNum=*P_Data_Id_OAD;
				break;
			}
			P_Data_Id_OAD++;
		}
	}
	return V_OADNum;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetMinFreezeProNum(ulong32 V_Data_Id_OAD, uchar8 *pV_Cycle)
�����������жϸ�OADΪ���Ӷ���ķ����ţ�0-7
���������ulong32 V_Data_Id_OAD�����Ӷ��ᣬ��Ҫ��ȡ����OAD
���������
���ز�����������0-7���쳣Ϊ0xFF������OAD�����ڷ���0xFE
����λ�ã�
��     ע��
*******************************************************************************/
uchar8 SF_GetMinFreezeProNum(ulong32 V_Data_Id_OAD, uchar8 *pV_Cycle)
{
	uchar8 V_ProNum=0xFF;
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADOrder16,V_i,V_k,V_EventSign;
	uchar8 V_Return_Flag;
	Str_3aTable V_Str_3aTable;
	ulong32 V_ulOAD;

	V_i=SF_GetStr_698FreezeDataTableOrder(C_RelatedOAD_Min);/*��ȡĳ�ඳ��������Str_698FreezeDataTable�����*/
	if(V_i<Str_698FreezeDataTable_Len)
	{
		V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;/*698���᳤�ȡ���������������Str_3aTable�к�*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return 	V_ProNum;/*�쳣*/
		}
		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
		if(C_OK==V_Return_Flag)
		{
			V_OADTabLen_T=P_OADTabLen_T[0];
			V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*��ű�ÿ��OAD���C_698Free_OADTabDataType���ֽ�,Ŀǰ6�ֽڡ�2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/
			if(V_OADTabLen_T>C_698Free_OADTabLen)/*���ݳ��Ȱ�ȫ���ж�*/
			{
				return V_ProNum;/*�쳣*/
			}
			V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;/*698������ű�����Str_3aTable�к�*/
			if(V_Order >= Str_3aTable_E23RAM_Len)
			{
				return V_ProNum;/*�쳣*/
			}
			V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
			V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);
			if(C_OK!=V_Return_Flag)
			{
				return V_ProNum;/*�쳣*/
			}

			V_OADTabLen_T=V_OADTabLen_T/C_698Free_OADTabDataType;
			uchar8 V_SignTemp=0x55;
			for(V_i=0;V_i<V_OADTabLen_T;V_i++)
			{
				PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType*V_i],&V_OADOrder16);
				V_EventSign=(V_OADOrder16&0xE000);					/*����698 OAD��DI1��3λ��ʾ��ͬ���ԣ�����Ʒ�ʽ�й�*/
				V_OADOrder16 &= 0x1FFF;
				if(V_OADOrder16>=Str_FrozenConvert_Table_Len)
				{
					return 	V_ProNum;								/*�쳣*/
				}
				/************************************************************************************/
				/*��Ϊ�ѿ���������*/
				/*����������ܣ����÷���2����ѡ����ʱ��͵��ܣ����ܲ��Ƕ����б��е����ݣ����붳������ͬ���ڣ�Ӧ��Ϊ����ʱ��+NULL��*/
                if((V_Data_Id_OAD & 0xFF000000) == 0x00000000)		/*������*/
                {
                    if((V_Data_Id_OAD & 0x00000F00) == 0x00000400)	/*�߾��ȵ���*/
                    {
                        V_ulOAD = ((V_Data_Id_OAD & 0xFFFFF0FF)| 0x00000200);
                    }
                    else if((V_Data_Id_OAD & 0x00000F00) == 0x00000200)
                    {
                        V_ulOAD = ((V_Data_Id_OAD & 0xFFFFF0FF)| 0x00000400);
                    }
                    else
                    {
                        V_ulOAD = V_Data_Id_OAD;
                    }
                }
                else
                {
                    V_ulOAD = V_Data_Id_OAD;
                }
				/************************************************************************************/
				if( ( V_Data_Id_OAD == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD | V_EventSign ) )	/*����OAD���*/
                 || ( V_ulOAD == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD | V_EventSign ) ) )
				{
					V_SignTemp=0xAA;
					break;
				}
				else
				{
					if(C_array==Str_FrozenConvert_Table[V_OADOrder16].V_uc698Type)				/*�����ʽOAD,��ѯ�Ƿ�Ϊ��OAD*/
					{
						for(V_k=0;;V_k++)
						{
							if((Str_FrozenConvert_Table[V_OADOrder16+V_k+1].V_ulOAD&0xFFFFFF00)
								 ==(Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD&0xFFFFFF00))
							{
								if((V_Data_Id_OAD ==(Str_FrozenConvert_Table[V_OADOrder16+V_k+1].V_ulOAD|V_EventSign))
                                   || (V_ulOAD ==(Str_FrozenConvert_Table[V_OADOrder16+V_k+1].V_ulOAD|V_EventSign)))
								{
									V_SignTemp=0xAA;
									break;
								}
							}
							else
							{
								break;
							}
						}
						if(V_SignTemp==0xAA)
						{
							break;
						}
					}
				}
			}
			if((V_SignTemp==0xAA)&&(V_i<V_OADTabLen_T))	/*���ҵ�����OAD*/
			{
				ushort16 V_Cyc16[8]={0xFFFF};
				V_k=SF_GetMinFreezeTolNum(&P_DataOAD_NumTab[0],(V_OADTabLen_T*C_698Free_OADTabDataType),&V_Cyc16[0]);/*��ȡ���Ӷ��᷽���ż���ͬ�Ķ�������*/
				if((V_k<9)&&(V_k>0))/*��������1--8*/
				{
					PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType*V_i+2],&V_OADOrder16);/*��������*/
					while(V_k)
					{
						if(V_Cyc16[V_k-1]==V_OADOrder16)/*�������*/
						{
							break;
						}
						V_k--;
					}
					if(V_k>0)
					{
						V_ProNum=V_k-1;
					}
				}
			}
			else
			{
				V_ProNum=0xFE;/*OAD�����б�����*/
			}
		}
	}
    *pV_Cycle = V_OADOrder16;
	return V_ProNum;
}
/*******************************************************************************
����ԭ�ͣ�uchar8   SF_GetMinFreezePro_E2Addr(ulong32 V_Data_Id_OAD, ushort16 *P_E2Addr_LoadP_Flash_Ear, ushort16 *P_E2Addr_LoadP_Flash_Late)
������������ȡ���Ӷ���ĳ�෽����Ӧ��¼�����硢���Flash��E2��ַ
���������ulong32 V_Data_Id_OAD�����Ӷ��ᣬ��Ҫ��ȡ����OAD
���������ushort16 *P_E2Addr_LoadP_Flash_Ear:���ظö��᷽��������Flash��¼��E2��ַ
		ushort16 *P_E2Addr_LoadP_Flash_Late:���ظö��᷽�������Flash��¼��E2��ַ
���ز�����C_OK��C_SPIError��C_DataLenError��C_NoAccess��C_Error(���ݸ�ʽ��)��C_SafeFlagError��C_IICError��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetMinFreezePro_E2Addr(ulong32 V_Data_Id_OAD, ushort16 *P_E2Addr_LoadP_Flash_Ear, ushort16 *P_E2Addr_LoadP_Flash_Late)
{
	uchar8 V_ProNum, V_Return_Flag = C_Error, V_Cycle = 15;

	V_ProNum = SF_GetMinFreezeProNum(V_Data_Id_OAD, &V_Cycle);		/*��ȡ���Ӷ��᷽���ţ��쳣����0xFF,������OAD����0xFE*/
	if(V_ProNum < 8)	/*8�ַ�����������0--7*/
	{
		*P_E2Addr_LoadP_Flash_Ear = E2Addr_Min_Free_Flash_Ear1 + V_ProNum * 12;
		*P_E2Addr_LoadP_Flash_Late = *P_E2Addr_LoadP_Flash_Ear + 6;
		V_Return_Flag = C_OK;
	}
	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�void InF_WriteFreezeData(uchar8 V_Num)
����������ͨ��ģ����ã�����ͨ��д��δ����Ĵ���
���������uchar8 V_Num���������ݲ㶳�����ݷ�������-ͨ���ܱ��������
�����������
���ز�������
����˵��������ͨ�ŷ�д��û�б��������(���ݲ㶳�����ݷ�������-ͨ���ܱ��������)�����ڷ����ڶ��ᣬʱ�䲻����
���û��ƣ�
��     ע���ú����ڲ����ж�д��������ܴ��ڷ������Զ������������糬���򲻸������ݲ��ڲ�ȫ�ִ���GV_FreezeLastNum
		�ú�������ԭ��ͨ�ų��������ڶ���ʱ���������ݲ㷵��5������(���ݲ��ڲ�GV_FreezeLastNum���¼�Ѿ����ҵ�������)��ʵ��ͨ�ű���4����
		ͨ�Ŷ�����֡ʱ���ͻ�������ݲ��Ѿ����ض�ͨ��û�б������ݣ����������
*********************************************************************************/
void InF_WriteFreezeData(uchar8 V_Num)
{
	ushort16 V_CRC16;

	if(V_Num>C_NextLoadTime_MaxNum)/*������������*/
	{
		return;
	}
	if(C_OK==PF_Check_CRC(&GV_FreezeLastNum[0],3))
	{
		GV_FreezeLastNum[0] += V_Num;
		V_CRC16=PF_Cal_CRC(&GV_FreezeLastNum[0],1);/*�����ϴβ��ҵ��ڼ���*/
		PF_Ushort16ToBuffer2(&GV_FreezeLastNum[1],&V_CRC16);
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8  InF_ReadFreezeData(ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,ushort16 * V_BlockNum,
									ushort16 * V_Length,ushort16 V_IntervalTime,uchar8 * pV_FreezeTimeBuf,uchar8 V_Mode)
�������������������ݽӿں�����ͨ�ŵ��ã��������ݸ��ݴ����OAD˳��
���������ulong32 *P_Data_Id_OAD�����ݱ�ʶOAD����һ��OAD��ʾ��ȡ�������ͣ�����50000200����ʾ��ȡ˲ʱ���ᣬ���2�ֽ�00��ʾ��ʾ�����ڶ�ȡ��
					��00��ʾ��ȡ��XX�μ�¼����ʱ* P_FixTime��V_IntervalTime��V_BlockNum��Ч.
					����OAD˳��Ϊ�������Զ�ӦOAD˳�򣬵�����OADΪFFFFFFFF���ʾ��������¼��ȡ��¼OAD����
		uchar8 *P_FixTime������ʱ���¼�飬12���ֽڡ���ʱ�����䳭����ǰ6���ֽڱ�ʾ��ʼʱ�䣬��6���ֽڱ�ʾ����ʱ�䣬ʱ���ʽssmmhhDDMMYY
							���̶�ʱ�䳭��ʱ��ֻ��ǰ6���ֽ���Ч����ʱ������������֡ʱ��ǰ6���ֽ�Ϊ��һ���¼ʱ�䡣
		ushort16 *V_BlockNum�����������Ŀǰ���̶�ʱ�䳭��������Ϊ1����ʱ�����䳭����������Ϊ��1��
		uchar8 *V_Length�������ݻ�������󳤶ȣ�
		ushort16 V_IntervalTime�����ʱ�䣬16������ʽ����λ����
���������uchar8 *P_FixTime����Ϊ�������ʱ�����к���֡ʱ��������һ����¼���¼ʱ��(ǰ6���ֽ�)(��¼���������֣����ƽ����ն��ᣬ����֡��������֡ʱ��)������ͨѶģ�������֡�á�
		ushort16 *V_BlockNum��Ŀǰ���ڳ����ã�bit0-1��ʾ�Ƿ��к���֡�����к���֡���ط�0��(Ŀǰ�̶�Ϊ2)���޺���֡����0,���к���֡���ط�0�����޺���֡����0
							bit2--15����ʾ���γ������ؼ�¼�����ݿ���
		uchar8 *V_Length����������ʵ�ʳ��ȣ�
		uchar8 *P_Data�������ݴ�Ż��棻
		uchar8 *pV_FreezeTimeBuf���������n��������ʱ�䣬ͨ�Ŷ�����֡�ж��ã�
���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_NoData��C_Error
����λ�ã�
��     ע�������̶�ʱ�䳭��ʱ����������Ϊ���ʱ������ݡ���ʱ�����䳭��ʱ����1��ʱ�������Ϊ��ʼʱ����������1��ʱ�������,
		����ʱ�������Ϊ���������ĵ�1��ʱ��+������ڣ����ʱ�������
*******************************************************************************/
uchar8 InF_ReadFreezeData(ulong32 *P_Data_Id_OAD,uchar8 *P_FixTime,uchar8 *P_Data,ushort16 *V_BlockNum,ushort16 *V_Length,ushort16 V_IntervalTime,uchar8 *pV_FreezeTimeBuf,uchar8 V_Mode)
{
	uchar8 V_DI[4],V_Return_Flag;
	uchar8 V_FlashAddr8[4];
	ulong32 V_FlashAddrLate,V_FlashAddrEar,V_FindFlashAddr,V_FlashAddr32;
	ushort16 V_TotalLen,V_Num;
	uchar8 V_Order;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear;
	uchar8 V_StarTime[C_698FreeData_DateLen6],V_FindTime[C_698FreeData_DateLen6],V_CompareSign,V_CompareSign_STEnd;
	uchar8 V_ucCompareFlag;
	ushort16 V_usCountCycle=0;
	uchar8 V_ucJudgeCycleBuf[C_698FreeData_DateLen6];
	uchar8 V_AddLen, V_Cycle = 15;

	if(V_Mode == C_645Mode)
	{
		V_AddLen = 5;
	}
	else
	{
		V_AddLen = 0;
	}

	GV_ReadLoadFlashAddr32=0xFFFFFFFF;/*ÿ�γ��������³�ʼ���ñ�������Ҫ�����޸�ʱ�串���ã������ظ����ң���߱�����ѯ����Ч��*/
	PF_Ulong32ToBuffer4(&V_DI[0],&P_Data_Id_OAD[0],4);
	if((C_RelatedOAD_Immid&0xFF000000)!=(P_Data_Id_OAD[0]&0xFF000000))/*�Ƕ����¼*/
	{
		return C_IDError;
	}

	if((P_Data_Id_OAD[0]&0xFFFF0000)==(C_RelatedOAD_Min&0xFFFF0000))/*���Ӷ���*/
	{
		ulong32 *P_Data_Id_OADTemp=&P_Data_Id_OAD[1];
		uchar8 V_temp=0x55;
		while(*P_Data_Id_OADTemp!=0xFFFFFFFF)/*ѭ���ж�OAD�б�*/
		{
			if((*P_Data_Id_OADTemp!=CFreeTime)&&(*P_Data_Id_OADTemp!=CFreeNum))/*���Ӷ��᲻����������ʱ������*/
			{
				V_temp=0xAA;
				break;
			}
			P_Data_Id_OADTemp++;
		}
		if(V_temp==0x55)
		{
			return C_RWForbid_DAR;
		}
	}

	V_Order=SF_GetStr_698FreezeDataTableOrder(P_Data_Id_OAD[0]);/*��ȡĳ�ඳ��������Str_698FreezeDataTable�����*/
	if(0xFF==V_Order)
	{
		return C_IDError;
	}
	if((*V_Length)==0)
	{
		return C_DataLenError;
	}

	V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_Order].V_E2AddrLate;
	V_E2Addr_LoadP_Flash_Ear=Str_698FreezeDataTable[V_Order].V_E2AddrEar;

	ulong32 V_VolidOADTemp = 0xFFFFFFFF;
	if((P_Data_Id_OAD[0]&0xFFFF0000)==(C_RelatedOAD_Min&0xFFFF0000))/*���Ӷ���*/
	{
		V_VolidOADTemp=SF_FindMinFreezeFirstVolidOAD(&P_Data_Id_OAD[1]);/*���ݹ����б���ҵ�һ����Ч��AOD���������б��д��ڵ�OAD��*/
		if(0xFFFFFFFF==V_VolidOADTemp)
		{
			return C_NoData;
		}

		V_Return_Flag=SF_GetMinFreezePro_E2Addr(V_VolidOADTemp,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*���ݸ�����OAD�жϷ����ţ���ȡ���Ӷ��ᣬĳ������Ӧ�����硢�����¼��E2��ַ*/
		if(C_OK!=V_Return_Flag)
		{
			return V_Return_Flag;
		}
	}

	V_Return_Flag = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*ȡ���1����¼Flashҳ��ַ*/
	if(V_Return_Flag != C_OK)
	{
		return	V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
	V_FlashAddrLate&=0xFFFFF000;             /*ҳ��ַת���������ݴ���*/

	V_Return_Flag = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);        /*ȡ����1����¼Flashҳ��ַ*/
	if(V_Return_Flag != C_OK)
	{
		return	V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);

	if(V_FlashAddrEar==V_FlashAddrLate)	/*û�м�¼����*/
	{
		return	C_NoData;
	}

	ushort16 V_DataLen;/*ÿ�������¼���ݳ���*/
	uchar8 V_ProNum = 0,V_DI2Temp;
	V_DI2Temp=V_DI[2];
	if((P_Data_Id_OAD[0]&0xFFFF0000)==(C_RelatedOAD_Min&0xFFFF0000))/*���Ӷ���*/
	{
		V_ProNum = SF_GetMinFreezeProNum(V_VolidOADTemp, &V_Cycle);			/*��ȡ���Ӷ��᷽���ţ��쳣����0xFF*/
		if(V_ProNum>8)/*������0--7*/
		{
			return C_NoData;
		}
		else
		{
			V_DI2Temp=(V_DI[2]&0x1F);/*���ӷ�����*/
			V_DI2Temp |= (V_ProNum<<5);
		}
	}

	V_DataLen=SF_JudgeWriteDataLen(V_DI2Temp);
	if(0==V_DataLen)/*�쳣�ж�*/
	{
		return	C_Error;
	}

	V_TotalLen=0;   /*��N�鸺�ɼ�¼ʱ�����ڼ�¼�����ݳ���*/
	V_Num=V_DI[0];
	uchar8 V_MaxNum;

	switch((*P_Data_Id_OAD&0xFFFF0000))
	{
		case	(C_RelatedOAD_Immid&0xFFFF0000):   /*����ʱ�䲻����*/
			V_MaxNum=C_FreezeImmid_MaxNum;
			break;
		case	(C_RelatedOAD_Settle&0xFFFF0000):
			V_MaxNum=C_NextLoadTime_MaxNum;
			break;
		case	(C_RelatedOAD_YSettle&0xFFFF0000):
			V_MaxNum=C_YSettleFreeze_MaxNum;
			break;
		case	(C_RelatedOAD_TimeZone&0xFFFF0000):
		case	(C_RelatedOAD_TimeRegion&0xFFFF0000):
		case	(C_RelatedOAD_RateTalbe&0xFFFF0000):
		case	(C_RelatedOAD_StepTable&0xFFFF0000):
			V_MaxNum=C_FreezeTimeZone_MaxNum;
			break;
		default:
			V_MaxNum=0xFF;
	}

	if(0xFF!=V_MaxNum)/*�������Զ���*/
	{
		if(V_Num>V_MaxNum)/*�������Զ�������������*/
		{
			return C_NoData;
		}
	}

	if(0==V_Num)/*��ʱ�䳭������*/
	{
		switch((*P_Data_Id_OAD&0xFFFF0000))
		{
			case	(C_RelatedOAD_Immid&0xFFFF0000):   /*����ʱ�䲻����*/
			case	(C_RelatedOAD_Settle&0xFFFF0000):
			case	(C_RelatedOAD_TimeZone&0xFFFF0000):
			case	(C_RelatedOAD_TimeRegion&0xFFFF0000):
			case	(C_RelatedOAD_RateTalbe&0xFFFF0000):
			case	(C_RelatedOAD_StepTable&0xFFFF0000):
			case	(C_RelatedOAD_YSettle&0xFFFF0000):
			{
				uchar8 V_Num2,V_Num1;

				V_Num1=1;/*Ĭ�ϴ���1��ʼ*/
				V_Num2=V_MaxNum;
				if(((*V_BlockNum)&C_FreezeNextSignFlag)==C_FreezeNextSign)/*�к���֡*/
				{
					if(C_OK==PF_Check_CRC(&GV_FreezeLastNum[0],3))
					{
						if(GV_FreezeLastNum[0]<=V_MaxNum)/*����������*/
						{
							V_Num2=GV_FreezeLastNum[0];/*����֡*/
						}
					}
				}
				else
				{
					SF_Initial_GVStrNextLoadTime();/*��ʼ������֡ȫ�ֱ���*/
				}

				if((*V_BlockNum) == 1)/*���̶�ʱ��,ʱ��������*/
				{
					V_Return_Flag = C_NoData;
					for(;V_Num1<=V_MaxNum;V_Num1++)/*���������*/
					{
						V_FindFlashAddr=SF_GetFlashAddrSatisfyNum(0,V_Order,V_Num1);/*��ȡ�������Ҫ��ļ�¼Flash��ַ,�����ڶ��᷽������0*/
						if(0xFFFFFFFF==V_FindFlashAddr)/*����������*/
						{
							break;
						}
						else
						{
							InF_FlashChipSelect();
							InF_ReadFlash(V_FindFlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*����¼��������ʱ��,�ж���ʼʱ��*/
							V_CompareSign=PF_Campare_Data(&V_FindTime[0],&P_FixTime[0],C_698FreeData_DateLen6);
							if(C_Equal==V_CompareSign)
							{
								V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],0,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,P_Data,V_DataLen,pV_FreezeTimeBuf,V_Mode);	/*��֯����*/
								break;
							}
						}
					}

					if(C_OK==V_Return_Flag)
					{
						(*V_BlockNum) = 1;
						(*V_BlockNum)<<=2;
						*V_Length=V_TotalLen;
					}
					else
					{
						if((V_Return_Flag==C_NotSupportAOD_DataBB)||(V_Return_Flag==C_NotSupportAOD_DataCC))
						{
							V_Return_Flag=C_NoData;
						}
					}

					SF_Initial_GVStrNextLoadTime();/*��ʼ������֡ȫ�ֱ���*/
					return V_Return_Flag;
				}
				else/*�������,�Ƕ������������Ǳ�������*/
				{
					uchar8 V_CompareSign1;
					V_Return_Flag=C_NoData;
					(*V_BlockNum) =0;
					for(;V_Num2>0;V_Num2--)/*�������*/
					{
						V_FindFlashAddr=SF_GetFlashAddrSatisfyNum(0,V_Order,V_Num2);/*��ȡ�������Ҫ��ļ�¼Flash��ַ*/
						if(0xFFFFFFFF==V_FindFlashAddr)/*û���������Ҫ���¼*/
						{
							continue;/*������ǰ����飬�϶��ܲ鵽�������Ҫ�����ݡ�*/
						}
						else
						{
							InF_FlashChipSelect();
							InF_ReadFlash(V_FindFlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*����¼��������ʱ��,�ж���ʼʱ��*/
							V_CompareSign=PF_Campare_Data(&V_FindTime[0],&P_FixTime[0],C_698FreeData_DateLen6);
							V_CompareSign1=PF_Campare_Data(&V_FindTime[0],&P_FixTime[C_698FreeData_DateLen6],C_698FreeData_DateLen6);
							if((C_LessThan!=V_CompareSign)&&(C_LessThan==V_CompareSign1))/*��Ч����*/
							{
								V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],0,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,&P_Data[V_TotalLen],V_DataLen,pV_FreezeTimeBuf,V_Mode);/*��֯����*/
								if(C_OK!=V_Return_Flag)
								{
									break;
								}
								else
								{
									(*V_BlockNum)++;
								}
							}
						}
					}

					*V_Length=V_TotalLen;
					(*V_BlockNum)<<=2;
					if((C_DataLenError==V_Return_Flag)&&(V_TotalLen!=0))/*����֡*/
					{
						ushort16 V_CRC16;
						GV_FreezeLastNum[0]=V_Num2;
						V_CRC16=PF_Cal_CRC(&GV_FreezeLastNum[0],1);/*�����ϴβ��ҵ��ڼ���*/
						PF_Ushort16ToBuffer2(&GV_FreezeLastNum[1],&V_CRC16);
						(*V_BlockNum)|=0x0002;
						V_Return_Flag=C_OK;
					}
					else/*�޺���֡*/
					{
						if((V_Return_Flag==C_NotSupportAOD_DataBB)||(V_Return_Flag==C_NotSupportAOD_DataCC))
						{
							V_Return_Flag=C_NoData;
						}
						SF_Initial_GVStrNextLoadTime();
					}

					return V_Return_Flag;
				}
			}break;

			default:  /*ʱ�串�Ƕ������ݳ���*/
			{
				PF_CopyDataBytes(&P_FixTime[0],&V_StarTime[0],C_698FreeData_DateLen6);

				/****************************��1����Ч���ݵ����***************************/
				V_FlashAddr32=V_FlashAddrEar;
				if(V_Mode == C_698EarLoadMode)
				{
					InF_ReadE2_Flash_Data(P_FixTime,C_698FreeData_DateLen6,C_ReadFlashFlay,V_FlashAddrEar);
					return V_Mode;
				}
				else if(V_Mode == C_698AheadTimeMode)
				{
					V_FindFlashAddr=SF_LoadDichotomyFlashData(V_ProNum,V_Order,&V_StarTime[0],V_FlashAddr32,V_FlashAddrLate,C_LoadDichotomyFindBefore);/*����2�ַ���������ʱ��Ҫ��ĸ��ɼ�¼*/
					if(V_FindFlashAddr==0xFFFFFFFF)
					{
						return C_NoData;
					}

					InF_FlashChipSelect();
					InF_ReadFlash(V_FindFlashAddr,&V_StarTime[0],C_698FreeData_DateLen6);    /*����¼��������ʱ��,�ж���ʼʱ��*/

					V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],V_ProNum,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,P_Data+V_AddLen,V_DataLen,pV_FreezeTimeBuf,V_Mode);/*��֯����*/
					if(C_NotSupportAOD_DataCC==V_Return_Flag)/*������������ѡOAD���ڹ����б��ж�û�С���Ҫ�������ڶ��᳭��������ѭ������ʱ�����*/
					{
						return C_NoData;
					}

					memcpy(pV_FreezeTimeBuf,V_StarTime,6);

					return V_Mode;
				}

				V_FindFlashAddr=SF_LoadDichotomyFlashData(V_ProNum,V_Order,&V_StarTime[0],V_FlashAddr32,V_FlashAddrLate,C_LoadDichotomyFindAfter);/*����2�ַ���������ʱ��Ҫ��ĸ��ɼ�¼*/
				if(V_FindFlashAddr==0xFFFFFFFF)
				{
					return C_NoData;
				}

				InF_FlashChipSelect();
				InF_ReadFlash(V_FindFlashAddr,&V_StarTime[0],C_698FreeData_DateLen6);    /*����¼��������ʱ��,�ж���ʼʱ��*/
				V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],V_ProNum,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,P_Data+V_AddLen,V_DataLen,pV_FreezeTimeBuf,V_Mode);/*��֯����*/
				if(V_Mode == C_645Mode)
				{
					memcpy(P_Data,pV_FreezeTimeBuf+2,5);
				}

				if(C_NotSupportAOD_DataCC==V_Return_Flag)/*������������ѡOAD���ڹ����б��ж�û�С���Ҫ�������ڶ��᳭��������ѭ������ʱ�����*/
				{
					return C_NoData;
				}

				if(C_OK!=V_Return_Flag)
				{
					if(V_Return_Flag==C_NotSupportAOD_DataBB)/*�����BB����У����.ѭ�����ҵ�1����Ч��¼���ݡ�ʱ���Ƿ����㣬�������жϡ�*/
					{
						ushort16 V_j=0;

						while(1)/*���ҵ�һ����Ч��¼��*/
						{
							if(V_j>120)
							{
								return C_NoData;/*��ȫ���ж����������ڣ�1min�������Ƚϴ�Ĵ洢�������ʱ�������ʱ��ϳ���*/
							}

							V_FindFlashAddr=SF_FindNextFreezeFlashAddr(V_ProNum,V_Order,V_FindFlashAddr,V_FlashAddrLate,V_FlashAddrEar,V_DataLen);/*��������������������¼��ַ*/
							if(V_FindFlashAddr==0xFFFFFFFF)
							{
								return C_NoData;
							}

							InF_FlashChipSelect();
							InF_ReadFlash(V_FindFlashAddr,&V_StarTime[0],C_698FreeData_DateLen6);    /*����¼��������ʱ��,�ж���ʼʱ��*/
							V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],V_ProNum,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,P_Data,V_DataLen,pV_FreezeTimeBuf,V_Mode);/*��֯����*/

							if(C_OK==V_Return_Flag)/*��Ч����*/
							{
								break;
							}
							else
							{
								if(V_Return_Flag!=C_NotSupportAOD_DataBB)/*�����BB����У����*/
								{
									return V_Return_Flag;/*�쳣*/
								}
							}

							V_j++;
						}
					}
					else
					{
						return V_Return_Flag;/*�쳣*/
					}
				}
				/*****************�����Ѿ����ҵ���Ч��¼�㣬ʱ���Ƿ����㣬�������ж�****************/
				PF_CopyDataBytes(&V_StarTime[0],&V_FindTime[0],C_698FreeData_DateLen6);
				V_CompareSign=PF_Campare_Data(&V_FindTime[0],&P_FixTime[0],C_698FreeData_DateLen6);/*�Ƚ���ʼʱ��*/

				if((*V_BlockNum)==1)/*���̶�ʱ��,ʱ��������*/
				{
						if(V_Return_Flag==C_NotSupportAOD_DataBB)/*���������ܳ��ָ����*/
						{
							return C_NoData;
						}
						else
						{
							(* V_BlockNum) = 1;
							(* V_BlockNum)<<=2;
							*V_Length=V_TotalLen;
							return C_OK;
						}
				}
				else/*��ʱ�����䳭��*/
				{
					V_CompareSign_STEnd=PF_Campare_Data(&V_FindTime[0],&P_FixTime[C_698FreeData_DateLen6],C_698FreeData_DateLen6);/*�жϽ���ʱ�䣬�뿪ʼ�ж�*/

					(*V_BlockNum) =0;
					GV_ReadRecordNum=0;
					if((C_LessThan==V_CompareSign)||(C_LessThan!=V_CompareSign_STEnd))/*�����䳭������1����ʱ�䣬����������賭��ʱ��,��С�ڽ�ֹʱ�䣨������=�������䳭��*/
					{
						return C_NoData;
					}
					else
					{
						uchar8 V_Read_Flag=0x55,V_Break120=0x55;
						V_Read_Flag=SF_JudgeReadCycSame(V_ProNum,V_Order,V_IntervalTime);/*�жϳ��������붳�������Ƿ�һ��*/
						if((V_IntervalTime==0)||(V_IntervalTime==1)||(V_Read_Flag==0xAA))/*��������*/
						{
							while(1)
							{
								if(V_Return_Flag!=C_NotSupportAOD_DataBB)/*��Ч����*/
								{
									(*V_BlockNum)++;
								}

								GV_ReadRecordNum++;
								V_FindFlashAddr=SF_FindNextFreezeFlashAddr(V_ProNum,V_Order,V_FindFlashAddr,V_FlashAddrLate,V_FlashAddrEar,V_DataLen);/*��������������������¼��ַ*/
								if(0xFFFFFFFF==V_FindFlashAddr)
								{
									V_Break120=0xAA;/*�ǳ�120��break*/
									break;
								}

								InF_FlashChipSelect();
								InF_ReadFlash(V_FindFlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*����¼��������ʱ��*/
								V_CompareSign=PF_Campare_Data(&V_FindTime[0],&P_FixTime[C_698FreeData_DateLen6],C_698FreeData_DateLen6);
								if((C_GreaterThan==V_CompareSign)||(C_Equal==V_CompareSign))/*������ֹʱ��,�޺���֡*/
								{
									V_Break120=0xAA;/*�ǳ�120��break*/
									break;
								}

								if((*V_BlockNum)>126)/*��ֹ����ʱ���������1024��(���䳭��ʱ��϶̣��ò����޸�Ϊ1024)���򰴺���֡����*/
								{
									V_Break120=0xBB;
									break;
								}

								V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],V_ProNum,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,&P_Data[V_TotalLen+V_AddLen],V_DataLen,pV_FreezeTimeBuf,V_Mode);/*��֯����*/
								if((C_OK!=V_Return_Flag)&&(V_Return_Flag!=C_NotSupportAOD_DataBB))
								{
									break;
								}
							}
						}
						else/*����ʱ��*/
						{
							V_FlashAddr32=V_FindFlashAddr;/*��1����¼��ַ*/
							if(V_Return_Flag!=C_NotSupportAOD_DataBB)
							{
								(* V_BlockNum)++;
								GV_ReadRecordNum++;
							}

							uchar8 V_tempTime[C_698FreeData_DateLen6];
							ulong32 V_SubTime=0xFFFFFFFF;
							ulong32 V_IntervalNum;
							uchar8 V_UnderTimeJudge;

							PF_CopyDataBytes(&V_FindTime[0],&V_tempTime[0],C_698FreeData_DateLen6);/*��Ч��ʼʱ��*/

							ulong32 C_FlashStAddr_LoadProfileTemp,C_FlashEndAddr_LoadProfileTemp;
							if((P_Data_Id_OAD[0]&0xFFFF0000)==(C_RelatedOAD_Min&0xFFFF0000))/*���Ӷ���*/
							{
								ushort16 V_E2Addr_LoadP_Flash_EarTemp,V_E2Addr_LoadP_Flash_LateTemp;
								SF_GetMinFreezePro_E2andFlashAddr(V_ProNum,&C_FlashStAddr_LoadProfileTemp,&C_FlashEndAddr_LoadProfileTemp,&V_E2Addr_LoadP_Flash_EarTemp,&V_E2Addr_LoadP_Flash_LateTemp);/*���ݷ��Ӷ��᷽���ţ���ȡ�÷�������������¼E2��ַ���÷�����ʼ������Flash��ַ*/
							}
							else
							{
								C_FlashStAddr_LoadProfileTemp=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;
								C_FlashEndAddr_LoadProfileTemp=Str_698FreezeDataTable[V_Order].V_EndFlashAddr;
							}

							PF_CopyDataBytes(&V_FindTime[0],&V_ucJudgeCycleBuf[0],C_698FreeData_DateLen6);/*��1����Ч��ʼʱ��*/

							while(1)/*��1����������ȡ*/
							{
								/*���Ӽ�����ڣ�������ʼ������ʱ���ж�*/
								PF_CopyDataBytes(&V_FindTime[0],&V_StarTime[0],C_698FreeData_DateLen6);/*����Ч��ʱ��㿪ʼ*/
								V_Return_Flag=SF_GetFreezeStartTime(P_Data_Id_OAD[0],&V_StarTime[0],V_IntervalTime);/*���ݼ����ĳ�ඳ�ᣬ��ȡ��ʼʱ��*/
								if(C_OK!=V_Return_Flag)/*���������ڣ������Ƕ��������ඳ�ᣬ���ƽ����ա��л�����*/
								{
									V_Break120=0xAA;/*�ǳ�120��break*/
									break;
								}

								V_ucCompareFlag = PF_Campare_Data(&V_StarTime[0],&V_ucJudgeCycleBuf[0],C_698FreeData_DateLen6);
								if(V_ucCompareFlag == C_LessThan) /*��ֹʱ����Ҵ���*/
								{
									V_Break120=0xAA;/*�ǳ�120��break*/
									break;
								}

								V_FindFlashAddr=SF_TraversalSearchFlashData(C_FlashStAddr_LoadProfileTemp,C_FlashEndAddr_LoadProfileTemp,V_ProNum,V_Order,&V_StarTime[0],V_FlashAddr32,V_FlashAddrLate,C_LoadDichotomyFindAfter);/*���ݱ�����������ʱ��Ҫ��ĸ��ɼ�¼*/
								if(V_FindFlashAddr==0xFFFFFFFF)
								{
									V_Break120=0xAA;/*�ǳ�120��break*/
									break;
								}

								InF_FlashChipSelect();
								InF_ReadFlash(V_FindFlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*����¼��������ʱ��*/

								V_CompareSign_STEnd=PF_Campare_Data(&V_FindTime[0],&P_FixTime[C_698FreeData_DateLen6],C_698FreeData_DateLen6);
								if((C_GreaterThan==V_CompareSign_STEnd)||(C_Equal==V_CompareSign_STEnd))/*������ֹʱ��,�޺���֡*/
								{
									V_Break120=0xAA;/*�ǳ�120��break*/
									break;
								}

								V_UnderTimeJudge=SF_GetFreezeIntervalTime(P_Data_Id_OAD[0],&V_tempTime[0],&V_FindTime[0],&V_SubTime);/*ĳ�ඳ�ᣬ���Ҽ�¼ʱ������Ч��¼ʱ�䣬���*/
								if(V_SubTime==0xFFFFFFFF)/*����������*/
								{
									V_Break120=0xAA;/*�ǳ�120��break*/
									break;
								}

								if((0==(V_SubTime%V_IntervalTime))&&(V_UnderTimeJudge==C_Equal))/*�����������¼�ʱ����ȫ��ȣ����������ڲ�������*/
								{
									PF_CopyDataBytes(&V_FindTime[0],&V_tempTime[0],C_698FreeData_DateLen6);/*��Ч��ʼʱ��*/
									V_usCountCycle = 0;
									if((* V_BlockNum)>69)/*��ֹ����ʱ���������120�����򰴺���֡����*/
									{
										V_Break120=0xBB;
										break;
									}

									V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],V_ProNum,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,&P_Data[V_TotalLen + V_AddLen],V_DataLen,pV_FreezeTimeBuf,V_Mode);/*��֯����*/
									if((C_OK!=V_Return_Flag)&&(V_Return_Flag!=C_NotSupportAOD_DataBB))/*ͬ���ж�*/
									{
										break;
									}
									else if(V_Return_Flag!=C_NotSupportAOD_DataBB)/*��Ч����*/
									{
										(*V_BlockNum)++;
										GV_ReadRecordNum++;
									}
								}
								else/*������ʼʱ�䣬���Ҽ�¼ʱ��ģ������һ�����ڼ�¼ʱ���*/
								{
									V_IntervalNum=V_SubTime/V_IntervalTime;
									V_IntervalNum=V_IntervalNum*V_IntervalTime;/*�����ڸ���*/
									PF_CopyDataBytes(&V_FindTime[0],&V_ucJudgeCycleBuf[0],C_698FreeData_DateLen6);
									PF_CopyDataBytes(&V_tempTime[0],&V_FindTime[0],C_698FreeData_DateLen6);/*��Ч��ʼʱ��*/
									SF_GetFreezeStartTime(P_Data_Id_OAD[0],&V_FindTime[0],V_IntervalNum);/*���ݼ����ĳ�ඳ�ᣬ��ȡ��ʼʱ�䡣����һ�����ڵ���ʼ����ʼ����*/
									V_usCountCycle++;
								}

								V_FlashAddr32=V_FindFlashAddr;/*��1����¼��ַ*/

								if(V_usCountCycle > C_CycleTimes) /*����2��ѯ1500����Ȼû����Ч��*/
								{
									V_Break120=0xAA;/*�ǳ�120��break*/
									break;
								}
							}
						}

						*V_Length=V_TotalLen;
						(*V_BlockNum)<<=2;/*��¼����*/
						if(V_TotalLen!=0)/*������*/
						{
							if((C_DataLenError==V_Return_Flag)||(V_Break120==0xBB))/*����֡*/
							{
								PF_CopyDataBytes(&V_FindTime[0],&P_FixTime[0],C_698FreeData_DateLen6);
								(* V_BlockNum)|=0x0002;
							}
							V_Return_Flag=C_OK;
						}
						else
						{
							if(C_NotSupportAOD_DataBB==V_Return_Flag)
							{
								V_Return_Flag=C_NoData;
							}
						}
						return V_Return_Flag;
					}
				}
			}
		}
	}
	else    /*��������������*/
	{
		ushort16 V_j=0;
		ushort16 V_k,V_tempLen,V_i=0;
		V_k = V_Num;
		switch((*P_Data_Id_OAD&0xFFFF0000))/*���ַ��Ӷ��ᣬ���ܻ��в�ͬ����*/
		{
			case (C_RelatedOAD_Min&0x00000000):   /*���в�����Ŀǰ���Ӷ���ֶ��ӷ������������ַ��Ӷ���*/
			{
				break;
			}
			default:/*��������Ŀǰ�����ڣ���ͬ���᷽������*/
			{
				if(V_k==0)/*����������*/
				{
					return C_NoData;
				}
				else
				{
					V_i=V_k-1;/*ֻ��ͬ1���᷽���ſ��ԣ���ֻҪ���ᣬ������Ч���ݡ�*/
				}
				break;
			}
		}

		V_tempLen=* V_Length;
		while(1) /*��Ҫ�Ƿ��Ӷ���,������������OAD������ͬ����ǰ���Ҵ�����ʹ��Ч����*/
		{
			V_j++;
			V_FindFlashAddr=SF_GetFlashAddrSatisfyNum(V_ProNum,V_Order,V_Num);/*��ȡ�������Ҫ��ļ�¼Flash��ַ*/
			if((0xFFFFFFFF==V_FindFlashAddr)||(V_j>121))/*V_j>121,������120��*/
			{
				return C_NoData;
			}

			V_TotalLen=0;
			*V_Length=V_tempLen;/*��������ÿ����Ч����1��*/
			V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],V_ProNum,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,P_Data,V_DataLen,pV_FreezeTimeBuf,V_Mode);/*��֯��¼����*/
			if(C_NotSupportAOD_DataCC==V_Return_Flag)/*������������ѡOAD���ڹ����б��ж�û�С���Ҫ�������ڶ��᳭��������ѭ������ʱ�����*/
			{
				return C_NoData;
			}

			if(V_Return_Flag!=C_NotSupportAOD_DataBB)
			{
				V_i++;	/*��Ч���ݼ�¼����*/
				if(V_k==V_i)
				{
					break;
				}
			}

			V_Num++;
		}

		(*V_BlockNum) = 1;
		(*V_BlockNum)<<=2;
		*V_Length=V_TotalLen;

		return V_Return_Flag;
	}
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_GetCurrentFlashPageModeNum(ulong32 V_FlashAddr)
������������ȡ��ǰFlash��¼ҳ����Ч�ĸ��ɼ�¼����
���������ulong32 V_FlashAddr����Ҫ���ҵ�Flash��¼ҳ��ַ��
�����������
���ز�����uchar8ʵ�ʼ�¼��Ч������FF�쳣��������ΪFF
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_GetCurrentFlashPageModeNum(ulong32 V_FlashAddr)
{
	uchar8 V_i=0xFF;
	uchar8 V_Mode1[C_LoadProfile_RevMode];

	if(V_FlashAddr%C_OneFlashPage)/*��ҳ��ַ*/
	{
		return V_i;
	}

	InF_FlashChipSelect();
	InF_ReadFlash(V_FlashAddr,&V_Mode1[0],C_LoadProfile_RevMode);

	for(V_i=0;V_i<C_LoadProfile_RevMode;V_i++)
	{
		if((C_Flash_NoEmpty==V_Mode1[V_i])||(C_Flash_Empty==V_Mode1[V_i]))  /*�ײ�Ϊȫ0��˵�����ɼ�¼ʱ�������,��V_I��Ч ��ײ�û�м�¼*/
		{
			break;
		}
	}

	if(0x00==V_i)/*����������*/
	{
		V_i=0xFF;
	}

	return V_i;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_GetSatisfyFlashPageAndModeOffSet698(ulong32 V_FlashSTAddr,ulong32 V_FlashEndAddr,ulong32 *V_FindFlashPageAddr,
														ushort16 V_BlockNum,ushort16 *V_BlockTolNum)
��������*��ȡ�����¼����Ҫ��ĸ��ɼ�¼Flashҳ��ַ��ģʽ��ƫ�ơ�ע�⺯���Ӻ���ǰ����
���������ulong32 V_FlashSTAddr����Ҫ���ҵ�Flash��¼��ʼҳ��ַ��
		ulong32 V_FlashEndAddr����Ҫ���ҵ�Flash��¼����ҳ��ַ��
		ushort16 V_BlockNum����Ҫ���ϵڼ��μ�¼
		ushort16 *V_BlockTolNum��Ŀǰ�Ѿ����ҵļ�¼������
���������ulong32 *V_FindFlashPageAddr�����������ĸ��ɼ�¼ҳ��ַ��
		ushort16 *V_BlockTolNum��Ŀǰ�Ѿ����ҵļ�¼������
���ز�����uchar8 ����������ģʽ��ƫ�ƻ�FFû����������
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_GetSatisfyFlashPageAndModeOffSet698(ulong32 V_FlashSTAddr,ulong32 V_FlashEndAddr,ulong32 *V_FindFlashPageAddr,ushort16 V_BlockNum,ushort16 *V_BlockTolNum)
{
	ushort16 V_ModeTNum;
	uchar8 V_ModeNum;
	ulong32 V_FlashAddr;

	V_FlashSTAddr&=0xFFFFF000;             /*ҳ��ַת���������ݴ���*/
	V_FlashEndAddr&=0xFFFFF000;
	V_FlashAddr=V_FlashEndAddr;
	if(V_FlashSTAddr>V_FlashEndAddr)
	{
		V_FlashAddr=V_FlashSTAddr;
		V_FlashSTAddr=V_FlashEndAddr;
		V_FlashEndAddr=V_FlashAddr;
	}

	V_ModeTNum=*V_BlockTolNum;
	for(V_FlashAddr=V_FlashEndAddr;V_FlashAddr>=V_FlashSTAddr;)/*�Ӻ���ǰ��*/
	{
		V_ModeNum=SF_GetCurrentFlashPageModeNum(V_FlashAddr);
		if(0xFF==V_ModeNum)
		{
			return 0xFF;
		}

		V_ModeTNum+=V_ModeNum;
		if(V_ModeTNum>=V_BlockNum)
		{
			break;
		}
		else
		{
			V_FlashAddr-=C_OneFlashPage;
		}
	}

	*V_BlockTolNum=V_ModeTNum;/*Ŀǰ�Ѳ�ѯ��¼������*/
	if(V_FlashAddr<V_FlashSTAddr)/*û���������Ҫ��*/
	{
		return 0xFF;
	}
	else
	{
		V_ModeNum=V_ModeTNum-V_BlockNum;/*����������ǰ��¼����ģʽ��ƫ��*/
		*V_FindFlashPageAddr=V_FlashAddr;/*�����¼������Flashҳ��ַ*/
	}

	if(V_ModeNum>=C_LoadProfile_RevMode)/*����������*/
	{
		return 0xFF;
	}
	else
	{
		return V_ModeNum;
	}
}

/*********************************************************************************
����ԭ�ͣ�uchar8 InF_ReadLaterFreezeNum(ulong32 V_Data_Id,uchar8 *P_Data,uchar8 *V_Length)
������������ĳ�ඳ���¼�����һ�μ�¼��ţ�����ģ�����
���������ulong32 V_Data_Id�����ݱ�ʶ����ĳ�ඳ��OAD��DI2��3λ��ʾ���Ӷ��᷽����
		uchar8 *V_Length�������ݻ�������󳤶ȣ�
���������uchar8 *V_Length����������ʵ�ʳ��ȣ�
		uchar8 *P_Data�������ݴ�Ż��棬û�м�¼ʱ��������0��
���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_NoData
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 InF_ReadLaterFreezeNum(ulong32 V_Data_Id1,uchar8 *P_Data,uchar8 *V_Length)
{
	uchar8 V_DI[4],V_Return_Flag;
	uchar8 V_FlashAddr8[4];
	ulong32 V_FlashAddrLate,V_FlashAddrEar,C_FlashStAddr_LoadProfile,V_FindFlashAddr;
	uchar8 V_i,V_Order,V_ProNum;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear;
	ulong32 V_Data_Id,C_FlashEndAddr_LoadProfile;

	V_ProNum=(uchar8)((V_Data_Id1&0x00E00000)>>21);/*��ȡ���Ӷ��᷽����*/
	V_Data_Id=(V_Data_Id1&0xFF1FFFFF);/*ȥ�����ӷ��������*/
	PF_Ulong32ToBuffer4(&V_DI[0],&V_Data_Id,4);
	if((C_RelatedOAD_Immid&0xFF000000)!=(V_Data_Id&0xFF000000))/*�Ƕ����¼*/
	{
		return C_IDError;
	}

	if(*V_Length<4)
	{
		return C_DataLenError;
	}

	V_Order=SF_GetStr_698FreezeDataTableOrder(V_Data_Id);/*��ȡĳ�ඳ��������Str_698FreezeDataTable�����*/
	if(0xFF==V_Order)
	{
		return C_IDError;
	}

	V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_Order].V_E2AddrLate;
	V_E2Addr_LoadP_Flash_Ear=Str_698FreezeDataTable[V_Order].V_E2AddrEar;
	C_FlashStAddr_LoadProfile=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;

	if(V_Data_Id==C_RelatedOAD_Min)/*���Ӷ���*/
	{
		V_Return_Flag=SF_GetMinFreezePro_E2andFlashAddr(V_ProNum,&C_FlashStAddr_LoadProfile,&C_FlashEndAddr_LoadProfile,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*���ݷ��Ӷ��᷽���ţ���ȡ�÷�������������¼E2��ַ���÷�����ʼ������Flash��ַ*/
		if(C_OK!=V_Return_Flag)
		{
			return C_Error;
		}
	}

	V_Return_Flag=SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*ȡ���1����¼Flashҳ��ַ*/
	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
	V_FlashAddrLate&=0xFFFFF000;             /*ҳ��ַת���������ݴ���*/

	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;
	}

	V_Return_Flag=SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);         /*ȡ����1����¼Flash��ַ*/
	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);

	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;
	}

	if((V_FlashAddrLate==V_FlashAddrEar)&&(V_FlashAddrLate==C_FlashStAddr_LoadProfile))  /*û�м�¼���ݣ����ش���Ϊ0*/
	{
		for(V_i=0;V_i<4;V_i++)
		{
			P_Data[V_i]=0;
		}
		*V_Length=4;
		return C_OK;
	}

	V_FindFlashAddr=SF_GetFixedLoadModeNoteFlashAddr(V_ProNum,V_Order,V_FlashAddrLate);
	if(0xFFFFFFFF!=V_FindFlashAddr)
	{
		InF_FlashChipSelect();
		InF_ReadFlash((V_FindFlashAddr+C_698FreeData_DateLen6),&P_Data[0],4);
		PF_Buffer4ToUlong32(&P_Data[0], &C_FlashEndAddr_LoadProfile, 4);		/*��flash��ȡ�ļ�¼���*/
		C_FlashEndAddr_LoadProfile += 1;
		PF_Ulong32ToBuffer4(&P_Data[0], &C_FlashEndAddr_LoadProfile, 4);		/*��¼��ż�1*/
		*V_Length=4;
	}

	return C_OK;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 InF_Total_Clear(uchar8 Msg_Num,uchar8 V_CurrentState,uchar8 C_Safe_Flag)
�����������������,ͨ�ŵ���
���������uchar8 Msg_Num��������Ϣ�ţ�
		uchar8 V_CurrentState�����ܱ�ǰ״̬�����ڡ����⣻
		ȡֵ��C_FactoryInType0x01�����ڣ�C_FactoryOutType0x02������
		uchar8 C_Safe_Flag��C_ClearMeterSafeFlag0x86���尲ȫ��־��
�����������
���ز�����C_OK��C_IICError��C_SPIError��C_NoAccess��C_SafeFlagError
����˵����
���û��ƣ�
��     ע�����㣬����У�����ݡ�ֻ��InF_RecMeterNote_Clear��У�����ݣ�ͨ��У��������á�
*********************************************************************************/
uchar8 InF_Total_Clear(uchar8 Msg_Num,uchar8 V_CurrentState,uchar8 C_Safe_Flag )
{
	uchar8 V_Return_Flag,V_i;

	GV_D_ClearSafeFlag=C_Clear_SafeFlag;
	GV_D_ClearSafeFlag=GV_D_ClearSafeFlag|C_DataClearMeterSafeFlag_1;
	GV_D_SafeFlag=GV_D_SafeFlag|C_ClearMeterSafeFlag_1;

	if(C_Msg_Communication!=Msg_Num)
	{
		return C_NoAccess;
	}

	GV_D_ClearSafeFlag=GV_D_ClearSafeFlag|C_DataClearMeterSafeFlag_2;
	GV_D_SafeFlag=GV_D_SafeFlag|C_ClearMeterSafeFlag_2;

	if(C_ClearMeterSafeFlag!=C_Safe_Flag)
	{
		GV_D_ClearSafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}

	GV_D_ClearSafeFlag=GV_D_ClearSafeFlag|C_DataClearMeterSafeFlag_3;
	GV_D_SafeFlag=GV_D_SafeFlag|C_ClearMeterSafeFlag_3;

	if(C_DataClearMeterSafeFlag==GV_D_ClearSafeFlag)  /*�������ڲ��ֱ��жϰ�ȫ��־*/
	{

		V_Return_Flag=SF_Clear_Engry(GV_D_SafeFlag);  /*���㣬���ɹ����������²�����*/
		if(C_OK!=V_Return_Flag)
		{
			GV_D_ClearSafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}

		V_Return_Flag = SF_Clear_Parm(GV_D_SafeFlag);                           /*���㣬���ɹ����������²�����*/
        if(C_OK != V_Return_Flag)
		{
			GV_D_ClearSafeFlag = C_Clear_SafeFlag;
			return V_Return_Flag;
		}
		V_Return_Flag = SF_Clear_Custom(GV_D_SafeFlag);                         /*���㣬���ɹ����������²�����*/
		if(C_OK != V_Return_Flag)
		{
			GV_D_ClearSafeFlag = C_Clear_SafeFlag;
			return V_Return_Flag;
			}

		V_Return_Flag=InF_Demand_Clear(C_Msg_Communication,C_W_SafeFlag);/*����ͨ�ŵ�����������ӿں���*/
		if(C_OK!=V_Return_Flag)
		{
			GV_D_ClearSafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}

		V_Return_Flag=SF_Clear_Freeze(GV_D_SafeFlag,0xFF);
		if(C_OK!=V_Return_Flag)
		{
			GV_D_ClearSafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}

		V_Return_Flag=SF_Clear_Event(GV_D_SafeFlag);
		if(C_OK!=V_Return_Flag)
		{
			GV_D_ClearSafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}

		V_Return_Flag=SF_Clear_Other(GV_D_SafeFlag);
		if(C_OK!=V_Return_Flag)
		{
			GV_D_ClearSafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}

		if(C_FactoryInType==V_CurrentState)
		{
			uchar8 V_Buff[CLTol_Clear_Degree];

			memset(&V_Buff[0],0x00,CLTol_Clear_Degree);		/*��ʼ��Ϊȫ��*/
			V_Return_Flag=SF_WriteE2Three(E2Addr_Tol_Clear_Degree,CLTol_Clear_Degree,&V_Buff[0]);	/*���������ܴ���*/

			memset(&V_Buff[0],0x00,CLBatt_Work_Time);	/*��ʼ��Ϊȫ��*/
			V_Return_Flag=SF_WriteE2Three(E2Addr_Batt_Work_Time,CLBatt_Work_Time,&V_Buff[0]); /*���ڲ���ع���ʱ�䣬����20141104�����Ҫ�������峧�ⲻ��*/
		}

		/*�帺�ɼ�¼����*/
		ushort16	V_usDataCRC;

		for(V_i=0;V_i<CLLoadWriteNum;V_i++)
		{
			GV_LoadWriteNum[V_i]=0;
		}

		V_usDataCRC = PF_Cal_CRC(GV_LoadWriteNum,CLLoadWriteNum);
		PF_Ushort16ToBuffer2(&GV_LoadWriteNum[CLLoadWriteNum],&V_usDataCRC);

		GV_D_SafeFlag=C_Clear_SafeFlag;

		GV_D_ClearSafeFlag=C_Clear_SafeFlag;

		return V_Return_Flag;
	}
	else
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		GV_D_ClearSafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}
}

/*******************************************************************************
����ԭ�ͣ�void InF_Clear_Engry_BorrowPoint( )
��������������ܽ�λλ��
�����������
�����������
���ز�������
����λ�ã����������
��    ע����RAM��E2������
*******************************************************************************/
void InF_Clear_Engry_BorrowPoint( )
{
	ushort16 V_usCRC16;

	GV_DisplayBorrowPoint[0] = 0;

	V_usCRC16 = PF_Cal_CRC(&GV_DisplayBorrowPoint[0], CLDisplayBorrowPoint);
	PF_Ushort16ToBuffer2(&GV_DisplayBorrowPoint[CLDisplayBorrowPoint], &V_usCRC16);

	GV_DisplayBorrowPoint_RecFlag[0] = 0;

	V_usCRC16 = PF_Cal_CRC(&GV_DisplayBorrowPoint_RecFlag[0], CLDisplayBorrowPoint_RecFlag);
	PF_Ushort16ToBuffer2(&GV_DisplayBorrowPoint_RecFlag[CLDisplayBorrowPoint_RecFlag], &V_usCRC16);
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Clear_Engry(uchar8 V_D_SafeFlag)
��������������������ݣ��ڲ��жϰ�ȫ��־
���������uchar8 V_D_SafeFlag:���㰲ȫ��־��C_ClearMeterSafeFlag��0x86
�����������
���ز�����C_OK��C_IICError��C_SafeFlagError
����λ�ã��ú�����InF_RelayAct�ӿں�������
��    ע�������硢E2�е�������
*******************************************************************************/
uchar8 SF_Clear_Engry(uchar8 V_D_SafeFlag)
{
	uchar8   V_Return_Flag = C_OtherErr_DAR;
	ushort16 V_CRC16, V_j, V_E2Addr;
	uchar8   V_Buff[10];
	uchar8   *P_RamAddr = NULL;
	uchar8   V_DataLen;

	if(C_ClearMeterSafeFlag != V_D_SafeFlag)
	{
		return C_NoAccess;
	}

	memset(&V_Buff[0], 0x00, 10);       /*��ʼ��Ϊȫ��*/

	/*�������������ݣ�������ǰ�����࣬�����ַ��һ��*/
	for(V_j = 0; V_j < Str_2Table_DIEn_Len; V_j++)
	{

		if((Str_2Table_DIEn[V_j].V_DT_Type) & NeedClearDataSign)    /*����������*/
		{
			memset(&V_Buff[0], 0x00, 10);               /*��ʼ��Ϊȫ��*/

			if(Str_2Table_DIEn[V_j].V_DataLen > 8)
			{
				return C_Error;     /*����������*/
			}

			V_DataLen = (uchar8)(Str_2Table_DIEn[V_j].V_DataLen);

			switch(Str_2Table_DIEn[V_j].V_DT_Type)
			{
				case	DT_Ti_E23_RAMCRC:
				{
					if(Str_2Table_DIEn[V_j].V_LineNum > Str_3aTable_E23RAM_Len)
					{
						return C_Error;     /*����������*/
					}

					if(V_DataLen <= 8)
					{
						V_E2Addr = Str_3aTable_E23RAM[Str_2Table_DIEn[V_j].V_LineNum].V_E2BakeUp1Addr;
						P_RamAddr = Str_3aTable_E23RAM[Str_2Table_DIEn[V_j].V_LineNum].V_RamAddr;
						V_Return_Flag = SF_WriteFRAMThree(V_E2Addr, V_DataLen, &V_Buff[0]);
						if(C_OK == V_Return_Flag)
						{
							V_CRC16 = PF_Cal_CRC(&V_Buff[0], V_DataLen);
							PF_Ushort16ToBuffer2(&V_Buff[V_DataLen], &V_CRC16);
							PF_CopyDataBytes(&V_Buff[0], P_RamAddr, (V_DataLen + C_CRCLen2));
						}
					}
					else
					{
						return C_Error;     /*����������*/
					}
				}break;
#if 0
				case	DT_E23_En_Clear:
#endif
				case	DT_E23_Clear:
				{
					V_E2Addr = (ushort16)Str_2Table_DIEn[V_j].PStr_3TableAddr;
#if 0
					if( Str_2Table_DIEn[V_j].V_DT_Type == DT_E23_En_Clear )     /*������ݳ��������ݴ洢ʵ�ʳ��Ȳ�ͬ,�洢���ݳ��ȶ�1�ֽ�*/
					{
						V_DataLen += 1;
					}
#endif
					V_Return_Flag = SF_WriteE2Three(V_E2Addr, V_DataLen, &V_Buff[0]);
				}break;

				default:
				{
					break;
				}
			}
		}
	}

	/*��E2 1������,������ս���ʱ�估�������������й����ۼ��õ���*/
	if(C_OK == V_Return_Flag)    /*E2���㲻�ɹ����������²�����*/
	{
		uchar8 V_Buff1[CLY_Com_Ac_En_FF];

		memset(&V_Buff1[0], 0x00, CLY_Com_Ac_En_FF);  /*��ʼ��Ϊȫ��*/

		InF_E2WPEnable();
		if(C_W_SafeFlag != GV_D_SafeFlag)             /*��ȫ��־��*/
		{
			InF_E2WPDisable();        /*�ر�WP*/
			GV_D_SafeFlag = C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		V_Return_Flag = InF_WriteE2(E2Addr_Y_Com_Ac_Tol_En_St, &V_Buff1[0], CLY_Com_Ac_En_FF);

		InF_Clear_Engry_BorrowPoint( );
	}

	/*�����ۼƹ�����*/
	if(C_OK == V_Return_Flag)
	{
		uchar8 V_temp[CLBuyCurr_TMoney];              /*�����ۼƹ�����*/
		memset(&V_temp[0], 0x00, CLBuyCurr_TMoney);   /*��ʼ��Ϊȫ��*/
		V_Return_Flag = SF_WriteE2Three(E2Addr_BuyCurr_TMoney, CLBuyCurr_TMoney, &V_temp[0]);
	}

	return V_Return_Flag;
}


/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Clear_Parm(uchar8 V_D_SafeFlag)
������������α��������ݣ��ڲ��жϰ�ȫ��־
���������uchar8 V_D_SafeFlag�����㰲ȫ��־��C_ClearMeterSafeFlag��0x68
���������RAM��ַ��GV_CurrEnergyData[45/46/43/44]��FRAM��ַ��651/658/637/644
���ز�����C_NoAccess��C_Error��C_OK��C_IICError
����λ�ã��ú���Ŀǰ����InF_Total_Clear�ӿں�������
��    ע���ú�������SF_Clear_Engry�����޸ģ�wjq211108
*******************************************************************************/
uchar8 SF_Clear_Parm(uchar8 V_D_SafeFlag)
{
    uchar8 V_ucBuff[10], V_ucj, V_ucDataLen, V_ucReturn_Flag = C_OtherErr_DAR;
    uchar8 *p_ucRamAddr = NULL;
    ushort16 V_usE2Addr, V_usCRC16;

    if(C_ClearMeterSafeFlag != V_D_SafeFlag)                                    /*�жϰ�ȫ��־*/
    {
        return C_NoAccess;
    }

    memset(&V_ucBuff[0], 0x00, 10);                                             /*��ʼ��Ϊȫ��*/

    for(V_ucj = 0; V_ucj < Str_2Table_DIEvent20_Len; V_ucj++)                   /*ѭ�������α����������Ŀǰʵ��ֻ����4��*/
    {
        if((Str_2Table_DIEvent20[V_ucj].V_DT_Type) & NeedClearDataSign)         /*����������*/
        {
            memset(&V_ucBuff[0], 0x00, 10);
            if(Str_2Table_DIEvent20[V_ucj].V_DataLen > 8)                       /*���������С����*/
            {
                return C_Error;                                                 /*����������*/
            }

            V_ucDataLen = (uchar8)(Str_2Table_DIEvent20[V_ucj].V_DataLen);      /*ȡ���󳤶�*/

			switch(Str_2Table_DIEvent20[V_ucj].V_DT_Type)
			{
                case DT_Ti_E23_RAMCRC:
                {
                    if(Str_2Table_DIEvent20[V_ucj].V_LineNum > Str_3aTable_E23RAM_Len)
					{
						return C_Error;                                         /*����������*/
					}

					if(V_ucDataLen <= 8)
					{
						V_usE2Addr = Str_3aTable_E23RAM[Str_2Table_DIEvent20[V_ucj].V_LineNum].V_E2BakeUp1Addr;
						p_ucRamAddr = Str_3aTable_E23RAM[Str_2Table_DIEvent20[V_ucj].V_LineNum].V_RamAddr;
						V_ucReturn_Flag = SF_WriteFRAMThree(V_usE2Addr, V_ucDataLen, &V_ucBuff[0]);
                        /*ע�⣺��ǰδ�������м�ĳ������дE2ʧ�ܵ����211108*/
						if(C_OK == V_ucReturn_Flag)
						{
							V_usCRC16 = PF_Cal_CRC(&V_ucBuff[0], V_ucDataLen);
							PF_Ushort16ToBuffer2(&V_ucBuff[V_ucDataLen], &V_usCRC16);
							PF_CopyDataBytes(&V_ucBuff[0], p_ucRamAddr, (V_ucDataLen + C_CRCLen2));
						}
					}
					else
					{
                        return C_Error;                                         /*����������*/
					}
				} break;

                /*ע�⣺����ķ�֧��δʹ�ã����������������ٴε���ȷ��211108*/
#if 0
				case DT_E23_En_Clear:
#endif
				case DT_E23_Clear:
				{
					V_usE2Addr = (ushort16)Str_2Table_DIEvent20[V_ucj].PStr_3TableAddr;
#if 0
					if(Str_2Table_DIEvent20[V_ucj].V_DT_Type == DT_E23_En_Clear)/*������ݳ��������ݴ洢ʵ�ʳ��Ȳ�ͬ,�洢���ݳ��ȶ�1�ֽ�*/
					{
						V_ucDataLen += 1;
					}
#endif
					V_ucReturn_Flag = SF_WriteE2Three(V_usE2Addr, V_ucDataLen, &V_ucBuff[0]);
				} break;

				default:
				{
					break;
				}
			}
        }

        if(Str_2Table_DIEvent20[V_ucj].V_DI == CY_Com_Ac_Tol_En_0)
        {
            break;                                                              /*��ߺ���ִ��Ч��*/
        }
    }

    return V_ucReturn_Flag;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Clear_Custom(uchar8 V_D_SafeFlag)
���������������������ݣ��ڲ��жϰ�ȫ��־
���������uchar8 V_D_SafeFlag�����㰲ȫ��־��C_ClearMeterSafeFlag��0x68
���������E2��ַ��651/658/637/644
���ز�����C_NoAccess��C_Error��C_OK��C_IICError
����λ�ã��ú���Ŀǰ����InF_Total_Clear�ӿں�������
��    ע���ú�������SF_Clear_Engry�����޸ģ�wjq211108
*******************************************************************************/
uchar8 SF_Clear_Custom(uchar8 V_D_SafeFlag)
{
    uchar8 V_ucBuff[10], V_ucj, V_ucDataLen, V_ucReturn_Flag = C_OtherErr_DAR;
    uchar8 *p_ucRamAddr = NULL;
    ushort16 V_usE2Addr, V_usCRC16;

    if(C_ClearMeterSafeFlag != V_D_SafeFlag)
    {
        return C_NoAccess;
    }

    memset(&V_ucBuff[0], 0x00, 10);                                             /*��ʼ��Ϊȫ��*/

    for(V_ucj = 0; V_ucj < Str_2Table_DIParameterFF_Len; V_ucj++)               /*ѭ�����������������Ŀǰʵ��ֻ����4��*/
    {
        if((Str_2Table_DIParameterFF[V_ucj].V_DT_Type) & NeedClearDataSign)     /*����������*/
        {
            memset(&V_ucBuff[0], 0x00, 10);
            if(Str_2Table_DIParameterFF[V_ucj].V_DataLen > 8)                   /*���������С����*/
            {
                return C_Error;                                                 /*����������*/
            }

            V_ucDataLen = (uchar8)(Str_2Table_DIParameterFF[V_ucj].V_DataLen);

			switch(Str_2Table_DIParameterFF[V_ucj].V_DT_Type)
			{
                /*ע�⣺����ķ�֧��δʹ�ã����������������ٴε���ȷ��211108*/
                case DT_Ti_E23_RAMCRC:
                {
                    if(Str_2Table_DIParameterFF[V_ucj].V_LineNum > Str_3aTable_E23RAM_Len)
					{
						return C_Error;                                         /*����������*/
					}

					if(V_ucDataLen <= 8)
					{
						V_usE2Addr = Str_3aTable_E23RAM[Str_2Table_DIParameterFF[V_ucj].V_LineNum].V_E2BakeUp1Addr;
						p_ucRamAddr = Str_3aTable_E23RAM[Str_2Table_DIParameterFF[V_ucj].V_LineNum].V_RamAddr;
						V_ucReturn_Flag = SF_WriteFRAMThree(V_usE2Addr, V_ucDataLen, &V_ucBuff[0]);
						if(C_OK == V_ucReturn_Flag)
						{
							V_usCRC16 = PF_Cal_CRC(&V_ucBuff[0], V_ucDataLen);
							PF_Ushort16ToBuffer2(&V_ucBuff[V_ucDataLen], &V_usCRC16);
							PF_CopyDataBytes(&V_ucBuff[0], p_ucRamAddr, (V_ucDataLen + C_CRCLen2));
						}
					}
					else
					{
                        return C_Error;                                         /*����������*/
					}
				} break;
                /*ע�⣺�����һ��������δʹ�ã����������������ٴε���ȷ��211108*/
#if 0
                case DT_E23_En_Clear:
#endif
				case DT_E23_Clear:
				{
					V_usE2Addr = (ushort16)Str_2Table_DIParameterFF[V_ucj].PStr_3TableAddr;
#if 0
					if(Str_2Table_DIParameterFF[V_ucj].V_DT_Type == DT_E23_En_Clear)/*������ݳ��������ݴ洢ʵ�ʳ��Ȳ�ͬ,�洢���ݳ��ȶ�1�ֽ�*/
					{
						V_ucDataLen += 1;
					}
#endif
					/*ע�⣺��ǰδ�������м�ĳ������дE2ʧ�ܵ����211108*/
					V_ucReturn_Flag = SF_WriteE2Three(V_usE2Addr, V_ucDataLen, &V_ucBuff[0]);
				} break;

				default:
				{
					break;
				}
			}
        }

        if(Str_2Table_DIParameterFF[V_ucj].V_DI == CM_Rev_Ac_Tol_En_Pul_1)
        {
            break;                                                              /*��ߺ���ִ��Ч��*/
        }
    }

    return V_ucReturn_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Clear_Event(uchar8 V_D_SafeFlag)
���������������¼������ݣ��ڲ��жϰ�ȫ��־
���������uchar8 V_D_SafeFlag:���㰲ȫ��־��C_ClearMeterSafeFlag��0x86
�����������
���ز�����C_OK��C_IICError��C_SafeFlagError
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_Clear_Event(uchar8 V_D_SafeFlag)
{
	uchar8 V_Return_Flag;
	uchar8 V_Buff[CLEven_Clear_Degree];

	if(C_ClearMeterSafeFlag!=V_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	V_Return_Flag=InF_EventNote_Clear(C_Msg_Communication,0xFFFFFFFF,C_W_SafeFlag);	/*�¼������㣬�����ṩͨ���¼�����ӿں���*/
	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;
	}

	memset(&V_Buff[0],0x00,CLEven_Clear_Degree);	/*��ʼ��Ϊȫ��*/
	V_Return_Flag=SF_WriteE2Three(E2Addr_Even_Clear_Degree,CLEven_Clear_Degree,&V_Buff[0]);	/*���¼������¼*/

	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Clear_MinFreeze(uchar8 V_D_SafeFlag)
��������������Ӷ��������ݣ��ڲ��жϰ�ȫ��־
���������uchar8 V_D_SafeFlag:���㰲ȫ��־��C_ClearMeterSafeFlag��0x86
�����������
���ز�����C_OK��C_IICError��C_SafeFlagError
����˵����
���û��ƣ�
��     ע��698�����������㣬E2�洢���������Flash��ַ��������ΪFlash��¼��ҳ��ַ,
		�м�¼ʱ��V_E2AddrEar����1����¼�׵�ַ(���Ե�ַ��ǰ��Ϊ��־��)��V_E2AddrLateΪ���1����¼ҳ��ַ
		�������Flash��ʼ��������ַ��ʧ�ܣ�û�����ù����б���û�з����ַ���������Ĭ��ƽ�����䡣
*********************************************************************************/
uchar8 SF_Clear_MinFreeze(uchar8 V_D_SafeFlag)
{
	uchar8 V_ProNum,V_Return_Flag,V_i;
	uchar8 Vu_FlashAddr[64]={0xFF};

	if(C_ClearMeterSafeFlag!=V_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	V_ProNum=InF_GetMinFreezeTolNum();	/*��ȡ���Ӷ����ܷ�����,1--8*/
	if(V_ProNum>8)	/*û�����ù������б�����ò����쳣*/
	{
		V_ProNum=8;	/*Ĭ��Ϊ8�ַ�����������õ�*/
		V_Return_Flag=SF_MinFreezeDefProDistr(8);
		if(C_OK!=V_Return_Flag)
		{
			return V_Return_Flag;
		}
	}

	V_Return_Flag=SF_ReadE2Three(E2Addr_Min_Free_FlashAddr_Allo,64,&Vu_FlashAddr[0]);	/*��ȡ��ͬ����������ʼ��������ַ*/
	if(C_OK!=V_Return_Flag)	/*����Ĭ�Ϸ����ַ��û�����ù������б�����*/
	{
		V_Return_Flag=SF_MinFreezeDefProDistr(8);
		if(C_OK!=V_Return_Flag)
		{
			return V_Return_Flag;
		}
		V_Return_Flag=SF_ReadE2Three(E2Addr_Min_Free_FlashAddr_Allo,64,&Vu_FlashAddr[0]);	/*��ȡ��ͬ����������ʼ��������ַ*/
	}

	if(C_OK==V_Return_Flag)
	{
		for(V_i=0;V_i<V_ProNum;V_i++)
		{
			V_Return_Flag=SF_WriteE2Three((E2Addr_Min_Free_Flash_Ear1+V_i*12),4,&Vu_FlashAddr[V_i*8]);	/*12\6\8,���E2�洢��ʽ	������Ϊ�����¼��ַ�����޼�¼����*/
			V_Return_Flag=SF_WriteE2Three((E2Addr_Min_Free_Flash_Ear1+V_i*12+6),4,&Vu_FlashAddr[V_i*8]);
		}
	}

	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Clear_Freeze(uchar8 V_D_SafeFlag)
�����������嶳�������ݣ��ڲ��жϰ�ȫ��־
���������uchar8 V_D_SafeFlag:���㰲ȫ��־��C_ClearMeterSafeFlag��0x86
�����������
���ز�����C_OK��C_IICError��C_SafeFlagError
����˵����
���û��ƣ�
��     ע��698�����������㣬E2�洢���������Flash��ַ��������ΪFlash��¼��ҳ��ַ,
		�м�¼ʱ��V_E2AddrEar����1����¼�׵�ַ(���Ե�ַ��ǰ��Ϊ��־��)��V_E2AddrLateΪ���1����¼ҳ��ַ
*********************************************************************************/
uchar8 SF_Clear_Freeze(uchar8 V_D_SafeFlag,uchar8 V_OIB)
{
	uchar8 V_Return_Flag=C_Error,V_i;
	uchar8 P_Data[4];
	ulong32 V_FlashAddr;

	if(C_ClearMeterSafeFlag!=V_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	GV_D_SafeFlag = V_D_SafeFlag;

	if(V_OIB == 0xFF)
	{
		for(V_i=0;V_i<Str_698FreezeDataTable_Len;V_i++)
		{

			V_FlashAddr=Str_698FreezeDataTable[V_i].V_StaFlashAddr;
			PF_Ulong32ToBuffer4(&P_Data[0],& V_FlashAddr,4);
			V_Return_Flag=SF_WriteE2Three(Str_698FreezeDataTable[V_i].V_E2AddrEar,4,&P_Data[0]);
			V_Return_Flag=SF_WriteE2Three(Str_698FreezeDataTable[V_i].V_E2AddrLate,4,&P_Data[0]);
		}

		V_Return_Flag=SF_Clear_MinFreeze(GV_D_SafeFlag);/*����Ӷ���*/
	}
	else
	{
		uchar8 V_DI2Temp;

		V_DI2Temp=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);

		for(V_i=0;V_i<Str_698FreezeDataTable_Len;V_i++)
		{

			if(V_OIB == Str_698FreezeDataTable[V_i].V_DI2)
			{
				if(V_OIB==V_DI2Temp)/*���Ӷ���*/
				{
					V_Return_Flag=SF_Clear_MinFreeze(GV_D_SafeFlag);/*����Ӷ���*/
				}
				else
				{
					V_FlashAddr=Str_698FreezeDataTable[V_i].V_StaFlashAddr;
					PF_Ulong32ToBuffer4(&P_Data[0],& V_FlashAddr,4);
					V_Return_Flag=SF_WriteE2Three(Str_698FreezeDataTable[V_i].V_E2AddrEar,4,&P_Data[0]);
					V_Return_Flag=SF_WriteE2Three(Str_698FreezeDataTable[V_i].V_E2AddrLate,4,&P_Data[0]);
				}
				break;
			}
		}
	}

	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_Clear_Other(uchar8 V_D_SafeFlag)
���������������������ݣ��ڲ��жϰ�ȫ��־
���������uchar8 V_D_SafeFlag:���㰲ȫ��־��C_ClearMeterSafeFlag��0x86
�����������
���ز�����C_OK��C_IICError��C_SafeFlagError
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_Clear_Other(uchar8 V_D_SafeFlag)
{
	uchar8 V_i=C_OK;
	ushort16 V_j,V_CRC16;

	if(C_ClearMeterSafeFlag!=V_D_SafeFlag)
	{
		return C_SafeFlagError;
	}
	else
	{
		/*�嵱ǰ��ѹ�ϸ���������ݣ���1�࣬����ȫ��*/
		for(V_i=0;V_i<4;V_i++)
		{
			for(V_j=0;V_j<CLVol_Per_Pass_M;V_j++)
			{
				GV_CurrMVolPerPass[V_i][V_j]=0x00;
			}

			V_CRC16=PF_Cal_CRC(&GV_CurrMVolPerPass[V_i][0],CLVol_Per_Pass_M);
			PF_Ushort16ToBuffer2(&GV_CurrMVolPerPass[V_i][CLVol_Per_Pass_M],&V_CRC16);
		}

		for(V_i=0;V_i<CLVol_PassTime_M;V_i++)		/*���ѹ�ϸ�ʱ�䣬����*/
		{
			GV_Voltage_PassTime[V_i]=0x00;
		}
		V_CRC16=PF_Cal_CRC(&GV_Voltage_PassTime[0],CLVol_PassTime_M);
		PF_Ushort16ToBuffer2(&GV_Voltage_PassTime[CLVol_PassTime_M],&V_CRC16);

		for(V_i=0;V_i<CLCurrMon_Vol_Pass_Time;V_i++)		/*�屾���ܵ�ѹ�ϸ�ʱ�䣬02800024*/
		{
			GV_CurrMon_Vol_Pass_Time[V_i]=0x00;
		}

		for(V_i=0;V_i<4;V_i++)		/*���յ�ѹ�ϸ���������ݣ���1�࣬����ȫ��*/
		{
			for(V_j=0;V_j<CLVol_Per_Pass_D;V_j++)
			{
				GV_CurrDVolPerPass[V_i][V_j]=0x00;
			}
			V_CRC16=PF_Cal_CRC(&GV_CurrDVolPerPass[V_i][0],CLVol_Per_Pass_D);
			PF_Ushort16ToBuffer2(&GV_CurrDVolPerPass[V_i][CLVol_Per_Pass_D],&V_CRC16);
		}

#if 0
		for(V_i=0;V_i<CLVol_PassTime_D;V_i++)	/*���յ�ѹ�ϸ�ʱ�䣬����*/
		{
			GV_Voltage_PassTime_D[V_i]=0x00;
		}
		V_CRC16=PF_Cal_CRC(&GV_Voltage_PassTime_D[0],CLVol_PassTime_D);
		PF_Ushort16ToBuffer2(&GV_Voltage_PassTime_D[CLVol_PassTime_D],&V_CRC16);
#endif
		return C_OK;
	}
}
/*********************************************************************************
����ԭ�ͣ�uchar8 InF_EventNote_Clear(uchar8 Msg_Num,ulong32 V_Data_Id,uchar8 C_Safe_Flag)
�����������¼���¼���㣬ͨ�ŵ���
���������uchar8 Msg_Num��������Ϣ�ţ�
		ulong32 V_Data_Id�����ݱ�ʶ
		uchar8 C_Safe_Flag�����尲ȫ��־��ȡֵΪC_ClearMeterSafeFlag=0x86��
�����������
���ز�����C_OK��C_IICError��C_NoAccess��C_SafeFlagError,C_IDError
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 InF_EventNote_Clear(uchar8 Msg_Num,ulong32 V_Data_Id,uchar8 C_Safe_Flag)
{
	uchar8 V_Return_Flag,V_DI,V_i;
	uchar8 V_ClearSign,V_DataLen;
	ushort16 V_j,V_E2Addr;
	uchar8 V_Buff[40];

	memset(&V_Buff[0],0x00,40);		/*��ʼ��Ϊȫ��*/

	if(C_Msg_Communication!=Msg_Num)
	{
		return C_NoAccess;
	}

	if(C_W_SafeFlag!=C_Safe_Flag)
	{
		return C_SafeFlagError;
	}
	else
	{
		V_ClearSign=C_ClearMeterSafeFlag;
		GV_D_SafeFlag=C_ClearMeterSafeFlag;
	}

	V_DI=(uchar8)V_Data_Id;
	if(0xFF!=V_DI)
	{
		return C_IDError;
	}

	if(0xFFFFFFFF==V_Data_Id)
	{
		if(C_ClearMeterSafeFlag==V_ClearSign)
		{
			for(V_j=0;V_j<(Str_EvenTableE2_Len-2);V_j++)	/*����,�������¼������¼,У���¼����*/
			{

				memset(&V_Buff[0],0x00,40);		/*��ʼ��Ϊȫ��*/

				if((Str_EvenTableE2[V_j].V_DI)!=(CSoft_I_J_Prog_Degree|EventDI))	/*ȥ����I_J��¼*/
				{
					V_E2Addr=Str_EvenTableE2[V_j].V_E2AddrEnd-Str_EvenTableE2[V_j].V_E2AddrSt;
					V_DataLen=CLBuyCurr_Degree+C_CRCLen2;	/*�ۼ�ʱ�估��������4�ֽ�,���4�ֽڣ�����ĸò��ִ���*/
					if(V_E2Addr==V_DataLen)
					{
						V_E2Addr=Str_EvenTableE2[V_j].V_E2AddrSt;
						V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLBuyCurr_Degree,&V_Buff[0]);
					}
					else
					{
						if(V_E2Addr==(2*V_DataLen))/*�ۼ�ʱ�估��������4�ֽ�,���4�ֽڣ�����ĸò��ִ���*/
						{
							V_E2Addr=Str_EvenTableE2[V_j].V_E2AddrSt;
							V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLBuyCurr_Degree,&V_Buff[0]);
							V_E2Addr+=V_DataLen;
							V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLBuyCurr_Degree,&V_Buff[0]);
						}
						else
						{
							return C_Error;/*����������*/
						}
					}
				}

				if(C_OK!=V_Return_Flag)
				{
					return V_Return_Flag;
				}
			}

			/***********************��IJ********************************/
			V_Return_Flag=SF_WriteE2Three(E2Addr_Soft_I_J_Prog_1,CLSoft_I_J_Prog_1,&V_Buff[0]);
			V_Return_Flag=SF_WriteE2Three(E2Addr_Soft_I_J_Prog_2,CLSoft_I_J_Prog_2,&V_Buff[0]);

			V_Return_Flag=SF_WriteE2Three(E2Addr_ProgReC1,CLProgReC1_Degree,&V_Buff[0]);	/*������޹�1������޹�2�ܴ���*/
			V_Return_Flag=SF_WriteE2Three(E2Addr_ProgReC2,CLProgReC2_Degree,&V_Buff[0]);

			/*ɽ��˫Э�����ӣ�645ʱ�α��̼�¼��ʱ�����̼�¼����*/
			V_Return_Flag=SF_WriteE2Three(E2Addr_ProgPT_CurrentPart_Degree,CLProgPT_CurrentPart_Degree,&V_Buff[0]);
			V_Return_Flag=SF_WriteE2Three(E2Addr_ProgTZ_CurrentPart_Degree,CLProgTZ_CurrentPart_Degree,&V_Buff[0]);
			V_Return_Flag=SF_WriteE2Three(E2Addr_Program_Degree_645,CLProgram_Degree_645,&V_Buff[0]);	/*645��̼�¼*/

			return V_Return_Flag;
		}
		else
		{
			return C_SafeFlagError;
		}
	}

	for(V_i=0;V_i<Str_EvenTableE2_Len;V_i++)	/*�����¼�����*/
	{
		if(V_Data_Id==Str_EvenTableE2[V_i].V_DI)
		{
			break;
		}
	}

	if(Str_EvenTableE2_Len==V_i)
	{
		 return C_IDError;
	}

	memset(&V_Buff[0],0x00,40);		/*��ʼ��Ϊȫ��*/

	V_E2Addr=Str_EvenTableE2[V_i].V_E2AddrEnd-Str_EvenTableE2[V_i].V_E2AddrSt;
	V_DataLen=CLBuyCurr_Degree+C_CRCLen2;		/*�ۼ�ʱ�估��������4�ֽ�,���4�ֽڣ�����ĸò��ִ���*/
	if(V_E2Addr==V_DataLen)
	{
		V_E2Addr=Str_EvenTableE2[V_i].V_E2AddrSt;
		V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLBuyCurr_Degree,&V_Buff[0]);
	}
	else
	{
		if(V_E2Addr==(2*V_DataLen))		/*�ۼ�ʱ�估��������4�ֽ�,���4�ֽڣ�����ĸò��ִ���*/
		{
			V_E2Addr=Str_EvenTableE2[V_i].V_E2AddrSt;
			V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLBuyCurr_Degree,&V_Buff[0]);
			V_E2Addr+=V_DataLen;
			V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLBuyCurr_Degree,&V_Buff[0]);
		}
		else
		{
			return C_Error;		/*����������*/
		}
	}

	if(V_Data_Id==(CProgReC_Degree|EventDI))	/*����޹�*/
	{
		V_Return_Flag=SF_WriteE2Three(E2Addr_ProgReC1,CLProgReC1_Degree,&V_Buff[0]);	/*������޹�1������޹�2�ܴ���*/
		V_Return_Flag=SF_WriteE2Three(E2Addr_ProgReC2,CLProgReC2_Degree,&V_Buff[0]);
	}

	/*ɽ��˫Э�����ӣ�698��ʱ��/ʱ�����̼�¼ɾ����ͬʱɾ��645�洢���¼���¼*/
	memset(&V_Buff[0],0x00,40);/*��ʼ��Ϊȫ��*/

	if(V_Data_Id==(CProgPT_Degree|EventDI))
	{
		V_Return_Flag=SF_WriteE2Three(E2Addr_ProgPT_CurrentPart_Degree,CLProgPT_CurrentPart_Degree,&V_Buff[0]);
	}

	if(V_Data_Id==(CProgTZ_Degree|EventDI))
	{
		V_Return_Flag=SF_WriteE2Three(E2Addr_ProgTZ_CurrentPart_Degree,CLProgTZ_CurrentPart_Degree,&V_Buff[0]);
	}

	if(V_Data_Id==(CProgram_Degree|EventDI))/*645��̼�¼*/
	{
		V_Return_Flag=SF_WriteE2Three(E2Addr_Program_Degree_645,CLProgram_Degree_645,&V_Buff[0]);
	}

	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 InF_EventNumFind(ulong32 V_Data_Id)
�����������������ݱ�ʾ�����¼���¼�ţ����¼���¼��ͨ��ģ����
���������ulong32 V_Data_Id�����ݱ�ʶ
�����������
���ز�����uchar8��EventNum,C_IDError
����˵�����¼���¼ģ�飬���ڻ�ȡNum�ţ�ͨ��ģ�������жϱ�ʶ���Ƿ���ȷ
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 InF_EventNumFind(ulong32 V_Data_Id)
{
	uchar8 V_i,V_DI;

	V_DI=(uchar8)V_Data_Id;
	if(0xFF!=V_DI)
	{
		return C_IDError;
	}

	for(V_i=0;V_i<Str_EvenTableE2_Len;V_i++)
	{
		if(V_Data_Id==Str_EvenTableE2[V_i].V_DI)
		{
			break;
		}
	}

	if(Str_EvenTableE2_Len==V_i)
	{
		return C_IDError;
	}
	else
	{
		return Str_EvenTableE2[V_i].V_EventNum;
	}
}
/*********************************************************************************
����ԭ�ͣ�uchar8 InF_RecMeterNote_Clear(uchar8 Msg_Num,uchar8 C_Safe_Flag)
����������ͨ�ŵ���,��У���¼�����ݲ��ڲ���У���¼����ָ��
���������uchar8 Msg_Num��������Ϣ�ţ�
		uchar8 C_Safe_Flag�����尲ȫ��־��0x68��
�����������
���ز�����C_OK��C_IICError��C_NoAccess��C_SafeFlagError
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 InF_RecMeterNote_Clear(uchar8 Msg_Num,uchar8 C_Safe_Flag)
{
	uchar8 V_Return_Flag;
	uchar8 V_Buff[3];

	memset(&V_Buff[0],0x00,3);/*��ʼ��Ϊȫ��*/

	if(C_Msg_Communication!=Msg_Num)
	{
		return C_NoAccess;
	}

	if(C_W_SafeFlag!=C_Safe_Flag)
	{
		return C_SafeFlagError;
	}

	GV_D_SafeFlag=C_Safe_Flag;
	V_Return_Flag=SF_WriteE2Three(E2Addr_Rec_Meter_Degree,3,&V_Buff[0]);

	GV_D_SafeFlag=C_Clear_SafeFlag;

	return V_Return_Flag;
}

/*********************************************************************************
����ԭ�ͣ�uchar8 InF_Demand_Clear(uchar8 Msg_Num,uchar8 C_Safe_Flag)
������������������,ͨ�š��������
���������uchar8 Msg_Num��������Ϣ�ţ�
		uchar8 C_Safe_Flag�����尲ȫ��־��0x68��
�����������
���ز�����C_OK��C_IICError��C_NoAccess��C_SafeFlagError
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 InF_Demand_Clear(uchar8 Msg_Num, uchar8 C_Safe_Flag)
{
	uchar8 V_Return_Flag = C_OtherErr_DAR,V_i;
	ushort16 V_j,V_E2Addr;
	uchar8 V_Buff[CLRev_Ac_Tol_De_0];
	uchar8 V_DataLen;

	memset(&V_Buff[0],0x00,CLRev_Ac_Tol_De_0);/*��ʼ��Ϊȫ��*/

	if((C_Msg_Communication!=Msg_Num)&&(C_Msg_SettleAccounts!=Msg_Num))
	{
		return C_NoAccess;
	}

	if(C_W_SafeFlag!=C_Safe_Flag)
	{
		return C_SafeFlagError;
	}

	GV_D_SafeFlag=C_ClearMeterSafeFlag;

	/*������Ϣ��ͨ�Ŷ�ֻ�嵱ǰ�����������е�ǰ�С��޹���������������������ʱ�����������*/
	if(C_W_SafeFlag==C_Safe_Flag)
	{
		for(V_j=0;V_j<(Str_2Table_DIDe10_Len);V_j++)/*�嵱ǰ����*/
		{

			memset(&V_Buff[0],0x00,CLRev_Ac_Tol_De_0);/*��ʼ��Ϊȫ��*/

			if((Str_2Table_DIDe10[V_j].V_DT_Type)&NeedClearDataSign)/*����������*/
			{
				if(Str_2Table_DIDe10[V_j].V_DataLen>CLRev_Ac_Tol_De_0)
				{
					return C_Error;/*����������*/
				}

				V_DataLen=(uchar8)(Str_2Table_DIDe10[V_j].V_DataLen);
				V_E2Addr=(ushort16)Str_2Table_DIDe10[V_j].PStr_3TableAddr;
				V_Return_Flag=SF_WriteE2Three(V_E2Addr,V_DataLen,&V_Buff[0]);
			}

			if(C_OK!=V_Return_Flag)
			{
				return V_Return_Flag;
			}
		}

		for(V_i=0;V_i<CLCurr_AcDemand;V_i++)
		{
			GV_Curr_AcDemand[V_i]=0;	/*��ǰ�й�����*/
			GV_Curr_ReDemand[V_i]=0;	/*��ǰ�޹�����*/
		}
	}
	else
	{
		return C_SafeFlagError;
	}

	return V_Return_Flag;
}
/*********************************************************************************
����ԭ�ͣ�void Data_CruiseCheck_Message(Str_Msg_Parameter *P_Msg_Parameter)
�������������ݲ�Ѳ�����򣬵���ÿ5s���������ô�����.��ʱ20min(���ݵ���5s�ۼ�)��RAM��ǰ��������E2������ESAM͸֧��ʣ���
		ͬʱѲ��Flash�Ƿ�Ϊ�գ�ÿ��Ѳ��һ���������飬��ǰ����RAM���ݣ�CRC�Ƿ�������������E2����RAM��ÿ�μ��1��
���������Str_Msg_Parameter *P_Msg_Parameter:��Ϣ�����ṹ��
�����������
���ز�������
����˵����
���û��ƣ�
��     ע��Ŀǰ��ǰ���ܴ����磬���ö�ʱ20min���档�����ּ��RAM���ܻ��Ǵ���
*********************************************************************************/
void Data_CruiseCheck_Message(Str_Msg_Parameter *P_Msg_Parameter)
{
	ulong32 V_FlashAddr;
	uchar8 V_FlashZero[C_Flash_EmptyNum],V_i;
	uchar8 V_Return_Flag;
	uchar8 V_DataLen;
	uchar8 Vuc_Buff_FramEnergy[C_CurrDataLen5+C_CRCLen2];
	ushort16 Vus_EneryE2Addr;

	V_DataLen=C_CurrDataLen5+C_CRCLen2;      /*�����е�ǰ�������ݳ���*/

	GV_D_SafeFlag=C_Clear_SafeFlag;                 /*Ѳ�찲ȫ��־����*/
	GV_D_ClearSafeFlag=C_Clear_SafeFlag;

	if(C_PowerOn!=(*P_Msg_Parameter).PowerFlag)      /*����ֱ���˳�*/
	{
		return;
	}

	GV_D_SafeFlag|=C_W_SafeFlag_1;

	if(C_Msg_Dispatch!=(*P_Msg_Parameter).SourceAddr)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;                 /*Ѳ�찲ȫ��־����*/
		return;
	}

	GV_D_SafeFlag|=C_W_SafeFlag_2;

	if(GV_CruiseCheck_RAMNum<C_CurrEnergy_Len)      /*Ѳ�쵱ǰ����RAM CRC*/
	{
		Vus_EneryE2Addr=GV_CruiseCheck_RAMNum*V_DataLen;
		Vus_EneryE2Addr=Vus_EneryE2Addr+E2Addr_CurrEnergy_St;
		V_Return_Flag=SF_ReadFRAMThree_AndCRC(Vus_EneryE2Addr,C_CurrDataLen5,&Vuc_Buff_FramEnergy[0]);   /*�����統ǰ�������ݰ���CRC*/
		if(C_OK == V_Return_Flag)
		{
			if(C_Equal != PF_Campare_Data(&Vuc_Buff_FramEnergy[0],&GV_CurrEnergyData[GV_CruiseCheck_RAMNum][0],(C_CurrDataLen5+C_CRCLen2)))
			{
				PF_CopyDataBytes(&Vuc_Buff_FramEnergy[0],&GV_CurrEnergyData[GV_CruiseCheck_RAMNum][0],(C_CurrDataLen5+C_CRCLen2));/*����CRC*/
			}
		}

		GV_CruiseCheck_RAMNum++;
	}
	else
	{
		GV_CruiseCheck_RAMNum=0;
	}

	GV_D_SafeFlag|=C_W_SafeFlag_3;

	GV_20min_Num++;
	if(GV_20min_Num>=C_GV_20min_Num)
	{
		GV_20min_Num=0;
		SF_UpdateE2CurrEnergy();
	}

	/*��Ҫ���ݶ�ʱУ��*/
	SF_ImportantDataCheckAndRecover();

	if(GV_CruiseCheck_FlashNum<(Str_3cTable_Flash_Len+Str_3dTable_Flash_Len))           /*Ѳ��Flash���*/
	{
		V_FlashAddr=SF_FindEvenFlashPage();

		GV_CruiseCheck_FlashNum++;

		if(0xFFFFFFFF==V_FlashAddr)                               /*��ǰҳ��¼�����������������,��ż��¼����12�Σ����β�ѯ����*/
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;                 /*Ѳ�찲ȫ��־����*/
			return;
		}
	}
	else                                                        /*���Ѳ�츺�ɼ�¼,698�޸�Ϊ��������*/
	{
		V_FlashAddr=SF_FindLoadProfileFlashPage();   /*��¼��ҳ����ʱ���Ѿ�����E2�м�¼ģʽ�֣��ô����ô��������ڲ�GV_CruiseCheck_FlashNum����ֵ*/
		if(0xFFFFFFFF==V_FlashAddr)
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;                 /*Ѳ�찲ȫ��־����*/
			return;
		}
	}

	V_FlashAddr=V_FlashAddr+C_OneFlashPage-C_Flash_EmptyNum;    /*���4���ֽ�Flash��ַ*/
	if(V_FlashAddr>=C_Flash_Max_Addr)                           /*���۲�����*/
	{
		GV_CruiseCheck_FlashNum=0;/*FlashѲ��4����*/
		GV_D_SafeFlag=C_Clear_SafeFlag;                 /*Ѳ�찲ȫ��־����*/
		return;
	}

	InF_FlashChipSelect();
	InF_ReadFlash(V_FlashAddr,&V_FlashZero[0],C_Flash_EmptyNum);
	for(V_i=0;V_i<C_Flash_EmptyNum;V_i++)  /*�ж�Flashҳ�Ƿ�Ϊ��,�ձ�־68*/
	{
		if(C_Flash_Empty68!=V_FlashZero[V_i])
		{
			break;
		}
	}

	if(V_i<C_Flash_EmptyNum)       /*��ǰҳFlash��Ϊ��*/
	{
		SF_EraseFlashAndWriteEmptySign(V_FlashAddr);
	}

	GV_D_SafeFlag=C_Clear_SafeFlag;                 /*Ѳ�찲ȫ��־����*/
}

/*********************************************************************************
����ԭ�ͣ�void SF_UpdateE2CurrEnergy(void)
������������ʱˢ��E2���ܣ�ESAM����,Ŀǰ��20min����Ѳ������л�У��RAMCRC���ڸò��ֲ��ж�CRC��
		ͬʱ�Ե������״̬��1��3������ͽ���ˢ��
�����������
�����������
���ز�������
����˵����
���û��ƣ�
��     ע���ڲ��жϵ��������ĺ����ԣ������ȶ����ж��Ƿ���ȣ���д��ķ�ʽ��
		����ʣ���͸֧���ֻ�жϽ���С�ĺ����ԣ�û���ж���ֵ.���������ð�ȫ��־
		����ĸú���Ϊ�ⲿ�������ã���ͨ�ŵ������InF_RAMDataRecoverFromE2����ֹ���������쳣��
		���³���ǰ�����ûָ�������øú������������
*********************************************************************************/
void SF_UpdateE2CurrEnergy(void)
{
	uchar8 PV_E2Data[C_CurrDataLen5];
	uchar8 V_E2DataFlag;
	uchar8 C_Meter_Work_State3, V_StateBuff;
	ushort16 V_usDataLen, V_usDataEncode;

	if(C_Meter_Type == C_L_SmartMeter)
	{
		C_Meter_Work_State3 = 0x02;
	}
	else
	{
		C_Meter_Work_State3 = 0x00;
	}

	GV_Meter_Work_State[2][1] = GV_Meter_Work_State[2][1] & 0xF0;					/*�������״̬��3*/
	GV_Meter_Work_State[2][1] = GV_Meter_Work_State[2][1] | C_Meter_Work_State3;

	V_StateBuff = (uchar8)(C_Meter_Work_State1);
	GV_Meter_Work_State[0][0] = GV_Meter_Work_State[0][0] & V_StateBuff;			/*�������״̬��1*/
	V_StateBuff = (uchar8)(C_Meter_Work_State1 >> 8);
	GV_Meter_Work_State[0][1] = GV_Meter_Work_State[0][1] & V_StateBuff;

	V_StateBuff = (uchar8)(C_Meter_Work_State2);
	GV_Meter_Work_State[1][0] = GV_Meter_Work_State[1][0] & V_StateBuff;			/*�������״̬��2*/
	V_StateBuff = (uchar8)(C_Meter_Work_State2 >> 8);
	GV_Meter_Work_State[1][1] = GV_Meter_Work_State[1][1] & V_StateBuff;

	V_StateBuff = (uchar8)(C_Meter_Work_State4);
	GV_Meter_Work_State[3][0] = GV_Meter_Work_State[3][0] & V_StateBuff;			/*�������״̬��4*/
	V_StateBuff = (uchar8)(C_Meter_Work_State4>>8);
	GV_Meter_Work_State[3][1] = GV_Meter_Work_State[3][1] & V_StateBuff;

	V_StateBuff = (uchar8)(C_Meter_Work_State5);
	GV_Meter_Work_State[4][0] = GV_Meter_Work_State[4][0] & V_StateBuff;			/*�������״̬��5*/
	V_StateBuff = (uchar8)(C_Meter_Work_State5 >> 8);
	GV_Meter_Work_State[4][1] = GV_Meter_Work_State[4][1] & V_StateBuff;

	V_StateBuff = (uchar8)(C_Meter_Work_State6);
	GV_Meter_Work_State[5][0] = GV_Meter_Work_State[5][0] & V_StateBuff;			/*�������״̬��6*/
	V_StateBuff = (uchar8)(C_Meter_Work_State6 >> 8);
	GV_Meter_Work_State[5][1] = GV_Meter_Work_State[5][1] & V_StateBuff;

	V_StateBuff = (uchar8)(C_Meter_Work_State7);
	GV_Meter_Work_State[6][0] = GV_Meter_Work_State[6][0] & V_StateBuff;			/*�������״̬��7*/
	V_StateBuff = (uchar8)(C_Meter_Work_State7 >> 8);
	GV_Meter_Work_State[6][1] = GV_Meter_Work_State[6][1] & V_StateBuff;

	V_StateBuff = C_HardError;
	GV_HardError_State[0] = GV_HardError_State[0] & V_StateBuff;

	/*******************����ESAMʣ��������ӿں���*****************************/
	V_usDataLen = CLChargeBal_Hex_Cent;
	V_E2DataFlag = InF_GetData_ObjectManage(CChargeBal_Hex_Cent, &PV_E2Data[0], &V_usDataLen, &V_usDataEncode);		/*������ģ��ӿں�������ȡ��ǰʣ����hex��ʽ*/
	if( C_OK == V_E2DataFlag )     						/*����������*/
	{
		if( C_W_SafeFlag == GV_D_SafeFlag )
		{
			if( C_OK == InF_IS_UpdateMInEsamTimer() )	/*�ж��Ƿ����ˢ��ESAM������15min��Χ�ڣ�����ˢ��*/
			{                                    		/*bbb��׼�涨������ESAMǮ���ļ����ʱ�䲻ӦС��15min*/
				InF_S_UpdataChargeBalInESAM( &PV_E2Data[0] );
			}
		}
	}

	if(C_ESAMPower == C_ESAMPower_Close)				/*�ϵ��ESAM��Դ��ֻ�����ã��������������á�*/
	{
		if( (Com_Conect.ConectOverTime==0)
			&& (Com_Conect.ConectOverTime_termal == 0)
			&& (JudgeTimerExceed10min(&IR_AuthT) != C_TimerEnable)
			&& (JudgeTimerExceed10min(&ID_AuthT_T) != C_TimerEnable) )
		{
			InF_Deactivation_7816_Esam();				/*ͣ��ESAM*/
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�ulong32 SF_FindEvenFlashPage(void)
����������������Ѳ���Flashҳ
�����������
�����������
���ز�����ulong32����Ѳ���Flashҳ��ַ������ż��¼��������12��ʱ������ȫFF
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
ulong32 SF_FindEvenFlashPage(void)
{
	uchar8 P_Dgree[CLAll_Loss_Vol_Degree];
	Str_3cTable PStr_3cTable_Flash;
	ulong32 V_Dgree,V_FlashAddr;
	uchar8 V_Flash_Page,V_Flash_PageNum;
	ushort16 V_FlashPrePageNum,V_Page_Agree;
	Str_3dEventTable PStr_3dTable_Flash;
	uchar8 V_Num;
	ushort16 V_Num_E2BakeUp1Addr,V_DataToalLen;
	ulong32 V_StaFlashAddr,V_EndFlashAddr;

	if(GV_CruiseCheck_FlashNum>=Str_3cTable_Flash_Len)  /*������3d���*/
	{
		V_Num=GV_CruiseCheck_FlashNum-Str_3cTable_Flash_Len;
		if(V_Num>=Str_3dTable_Flash_Len)/*����������*/
		{
			GV_CruiseCheck_FlashNum=0;/*FlashѲ��*/
			return 0xFFFFFFFF;
		}
		else/*4d���*/
		{
			PStr_3dTable_Flash=Str_3d698EventTable_Flash[V_Num];
			V_Num_E2BakeUp1Addr=PStr_3dTable_Flash.V_Num_E2BakeUp1Addr;
			V_StaFlashAddr=PStr_3dTable_Flash.V_StaFlashAddr;
			V_EndFlashAddr=PStr_3dTable_Flash.V_EndFlashAddr;
			V_DataToalLen=SF_GetEventDataLen(PStr_3dTable_Flash.V_TB_E2BakeUp1Addr,PStr_3dTable_Flash.V_TBLen_E2BakeUp1Addr,PStr_3dTable_Flash.PStr_4aTableAddr,PStr_3dTable_Flash.V_Str_4aTableLen);/*��ȡ��¼���ݳ���*/
			if((0==V_DataToalLen)||(0xFFFF==V_DataToalLen))/*�쳣���*/
			{
				return	0xFFFFFFFF;
			}
		}
	}
	else
	{
		PStr_3cTable_Flash=Str_3cTable_Flash[GV_CruiseCheck_FlashNum];
		V_Num_E2BakeUp1Addr=PStr_3cTable_Flash.V_Num_E2BakeUp1Addr;
		V_StaFlashAddr=PStr_3cTable_Flash.V_StaFlashAddr;
		V_EndFlashAddr=PStr_3cTable_Flash.V_EndFlashAddr;
		V_DataToalLen=PStr_3cTable_Flash.V_DataToalLen;
	}

	if(SF_ReadE2Three(V_Num_E2BakeUp1Addr,CLAll_Loss_Vol_Degree,&P_Dgree[0]) != C_OK)
	{
		return 0xFFFFFFFF;
	}

	if(V_Num_E2BakeUp1Addr == E2Addr_Program_Degree_645)
	{
		P_Dgree[3] =0;
	}
	PF_Buffer4ToUlong32(&P_Dgree[0],&V_Dgree,4);

	if(0==V_Dgree)                  /*��ǰ��¼����Ϊ0���򷵻�Flash��¼��ַ��ҳ*/
	{
		return V_StaFlashAddr;
	}
	else
	{
		if((0==V_DataToalLen)||(0xFFFF==V_DataToalLen))/*�쳣���*/
		{
			return	0xFFFFFFFF;
		}

		V_Flash_Page=(uchar8)((V_EndFlashAddr-V_StaFlashAddr)/C_OneFlashPage);  /*ȡFlash��¼ҳ*/
		V_FlashPrePageNum=(ushort16)(V_Dgree%(C_OneFlash_PageNum/V_DataToalLen));                            /*��żҳFlash���棬��ǰҳ��¼����*/

		if(1==V_Flash_Page)        /*��żҳ*/
		{
			if((0!=V_FlashPrePageNum)&&(V_FlashPrePageNum<C_FlashEvenOEEPageNum))   /*��ǰҳ��¼����12�Σ�����ѯ��������һҳ,ȡ������ҳ�Ѿ�����������û�а���*/
			{
				return 0xFFFFFFFF;
			}
		}

		V_Page_Agree=(ushort16)(C_OneFlash_PageNum/V_DataToalLen);  /*ÿҳ�ɼ�¼���ݴ���*/
		V_Flash_PageNum=V_Flash_Page+1;                   /*�ü�¼Flash�洢ҳ����,C_OneFlashPage:0x00001000*/
		V_FlashAddr=(((V_Dgree-1)/V_Page_Agree)%V_Flash_PageNum)*C_OneFlashPage+V_StaFlashAddr;  /*��ǰ��¼������Flashҳ��ַ*/
		if(V_FlashAddr==V_EndFlashAddr)          /*Flash��¼βҳ*/
		{
			V_FlashAddr=V_StaFlashAddr;          /*������ҳ��ַ*/
			return V_FlashAddr;
		}
		else
		{
			return (V_FlashAddr+C_OneFlashPage);	                    /*������ҳ��ַ*/
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�ulong32 SF_FindLoadProfileFlashPage(void)
�������������Ҹ��ɼ�¼��Ѳ���Flashҳ
�����������
�����������
���ز�����ulong32����Ѳ���Flashҳ��ַ
����˵����
���û��ƣ�
��     ע��Ŀǰ�޸�Ϊ�����¼
*********************************************************************************/
ulong32 SF_FindLoadProfileFlashPage(void)
{
	ulong32 V_FlashAddrLate,V_FlashAddrEar;
	uchar8 V_FlashAddr8[4];
	uchar8 V_i;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear;
	ulong32 V_FlashStAddr_LoadProfile,V_FlashEndAddr_LoadProfile;
	uchar8 V_ProNum,V_DI2,V_Return_Flag;

	V_ProNum=InF_GetMinFreezeTolNum();/*��ȡ���Ӷ����ܷ�����,1--8*/
	if(V_ProNum>8)
	{
		V_ProNum=0;
	}

	V_DI2=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);
	if(GV_CruiseCheck_FlashNum<(Str_3cTable_Flash_Len+Str_3dTable_Flash_Len))/*����������*/
	{
		return 0xFFFFFFFF;
	}

	V_i=GV_CruiseCheck_FlashNum-(Str_3cTable_Flash_Len+Str_3dTable_Flash_Len);
	if(V_i>=(Str_698FreezeDataTable_Len+V_ProNum))/*�����������е���ֻ�ǰ�ȫ���ж�*/
	{
		GV_CruiseCheck_FlashNum=0;/*FlashѲ��4����*/
		return 0xFFFFFFFF;
	}
	else
	{
		GV_CruiseCheck_FlashNum++;
		if(GV_CruiseCheck_FlashNum>=(Str_3cTable_Flash_Len+Str_698FreezeDataTable_Len+V_ProNum+Str_3dTable_Flash_Len))/*���ӷ��Ӷ��᲻ͬ����*/
		{
			GV_CruiseCheck_FlashNum=0;/*FlashѲ��4����*/
		}

		if(V_i<Str_698FreezeDataTable_Len)/*�����Ӷ���������������*/
		{
			V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_i].V_E2AddrLate;
			V_E2Addr_LoadP_Flash_Ear=Str_698FreezeDataTable[V_i].V_E2AddrEar;
			V_FlashStAddr_LoadProfile=Str_698FreezeDataTable[V_i].V_StaFlashAddr;
			V_FlashEndAddr_LoadProfile=Str_698FreezeDataTable[V_i].V_EndFlashAddr;
			if(V_DI2==Str_698FreezeDataTable[V_i].V_DI2)/*���Ӷ���	*/
			{
				return 0xFFFFFFFF;
			}
		}
		else/*���Ӷ��᷽��*/
		{
			V_Return_Flag=SF_GetMinFreezePro_E2andFlashAddr((V_i-Str_698FreezeDataTable_Len),&V_FlashStAddr_LoadProfile,&V_FlashEndAddr_LoadProfile,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*���ݷ��Ӷ��᷽���ţ���ȡ�÷�������������¼E2��ַ���÷�����ʼ������Flash��ַ*/
			if(C_OK!=V_Return_Flag)
			{
				return 0xFFFFFFFF;
			}
		}

		if(SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]) != C_OK)        /*ȡ���1����¼Flashҳ��ַ*/
		{
			return 0xFFFFFFFF;
		}
		PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
		V_FlashAddrLate&=0xFFFFF000;             /*ҳ��ַת���������ݴ���*/

		SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);         /*ȡ����1����¼Flash��ַ*/
		PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);

		if((V_FlashStAddr_LoadProfile==V_FlashAddrEar)                       /*û�и��ɼ�¼���ݣ����Ե�ַ*/
			||(V_FlashEndAddr_LoadProfile==V_FlashAddrLate))                   /*���ɼ�¼���1ҳ*/
		{
			return V_FlashStAddr_LoadProfile;
		}
		else
		{
			return (V_FlashAddrLate+C_OneFlashPage);
		}
	}
}

/*********************************************************************************
����ԭ�ͣ�void InF_Initial_Data(void)
������������ʼ�����ݲ���������ȵ���.�������ݲ�д�̶�ֵ����
�����������
�����������
���ز�������
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
void InF_Initial_Data(void)
{
	uchar8 C_Meter_Work_State3;
	uchar8 V_StateBuff;

	GV_D_SafeFlag=C_Clear_SafeFlag;
	GV_20min_Num=C_GV_19min_50s_Num;/*�ϵ��ʼ��Ϊ19min50s��10s��(Ѳ��������20min��ʱ)����SF_UpdateE2CurrEnergy����Ҫ����ˢ��ESAMǮ���ļ�*/
	GV_CruiseCheck_FlashNum=0;/*FlashѲ��4����*/
	GV_CruiseCheck_RAMNum=0;
	GV_D_ClearSafeFlag=C_Clear_SafeFlag;


	GV_D_SafeFlag=C_Clear_SafeFlag;

	/*�������״̬��3,����ͺ� ��ʼ����Bit0 ��Bit1;״̬��1��bit1*/
	if(C_Meter_Type==C_L_SmartMeter)
	{
		C_Meter_Work_State3=0x02;
	}
	else
	{
		C_Meter_Work_State3=0x00;
	}

	GV_Meter_Work_State[2][1]=GV_Meter_Work_State[2][1]&0xF0;                  /*�������״̬��3*/
	GV_Meter_Work_State[2][1]=GV_Meter_Work_State[2][1]|C_Meter_Work_State3;

	V_StateBuff=(uchar8)(C_Meter_Work_State1);
	GV_Meter_Work_State[0][0]=GV_Meter_Work_State[0][0]&V_StateBuff;                  /*�������״̬��1*/
	V_StateBuff=(uchar8)(C_Meter_Work_State1>>8);
	GV_Meter_Work_State[0][1]=GV_Meter_Work_State[0][1]&V_StateBuff;

	V_StateBuff=(uchar8)(C_Meter_Work_State2);
	GV_Meter_Work_State[1][0]=GV_Meter_Work_State[1][0]&V_StateBuff;                  /*�������״̬��2*/
	V_StateBuff=(uchar8)(C_Meter_Work_State2>>8);
	GV_Meter_Work_State[1][1]=GV_Meter_Work_State[1][1]&V_StateBuff;

	V_StateBuff=(uchar8)(C_Meter_Work_State4);
	GV_Meter_Work_State[3][0]=GV_Meter_Work_State[3][0]&V_StateBuff;                  /*�������״̬��4*/
	V_StateBuff=(uchar8)(C_Meter_Work_State4>>8);
	GV_Meter_Work_State[3][1]=GV_Meter_Work_State[3][1]&V_StateBuff;

	V_StateBuff=(uchar8)(C_Meter_Work_State5);
	GV_Meter_Work_State[4][0]=GV_Meter_Work_State[4][0]&V_StateBuff;                  /*�������״̬��5*/
	V_StateBuff=(uchar8)(C_Meter_Work_State5>>8);
	GV_Meter_Work_State[4][1]=GV_Meter_Work_State[4][1]&V_StateBuff;

	V_StateBuff=(uchar8)(C_Meter_Work_State6);
	GV_Meter_Work_State[5][0]=GV_Meter_Work_State[5][0]&V_StateBuff;                  /*�������״̬��6*/
	V_StateBuff=(uchar8)(C_Meter_Work_State6>>8);
	GV_Meter_Work_State[5][1]=GV_Meter_Work_State[5][1]&V_StateBuff;

	V_StateBuff=(uchar8)(C_Meter_Work_State7);
	GV_Meter_Work_State[6][0]=GV_Meter_Work_State[6][0]&V_StateBuff;                  /*�������״̬��7*/
	V_StateBuff=(uchar8)(C_Meter_Work_State7>>8);
	GV_Meter_Work_State[6][1]=GV_Meter_Work_State[6][1]&V_StateBuff;

	V_StateBuff=C_HardError;
	GV_HardError_State[0]=GV_HardError_State[0]&V_StateBuff;

	GV_ReadLoadFlashAddr32=0xFFFFFFFF;     /*14�淶���ɼ�¼ģ�飬����������*/
	GV_ReadLoadFlashAddr32Ear=0xFFFFFFFF;
	GV_ReadLoadFlashAddr32Late=0xFFFFFFFF;
	GV_SecLoadModeNum=0xFF;

	SF_Initial_GVStrNextEventData();			/*��ʼ��CRC���󣬳����¼���¼����֡��*/
}
/*********************************************************************************
����ԭ�ͣ�void InF_RAMDataRecoverFromE2(void)
�������������RAM��CRCE2������������(ȫ�ֱ���Str_3aTable_E23RAM������)������E2���ݶ�RAM���ݽ��лָ���
�����������
�����������
���ز�������
����˵����
���û��ƣ�
��     ע����Ҫ������ȫ�ֱ���ʱ�����±��룬RAM���ݿ��ܻ���(RAM��ַ������CMP�����ļ����Կ�������CRC��ȷ)��
		�ú������ڲ���E2���ݣ����¸���RAM����,�������������ݡ�
		��ͨ��ģ�鴥������.������Ŀ��������ȫ0������ΪCRC���󣬲���Ҫ���ݻָ���
*********************************************************************************/
void InF_RAMDataRecoverFromE2(void)
{
	ushort16 V_i;
	uchar8 V_j;
	uchar8 V_Return_Flag,V_DataNum;
	ushort16 V_E2Addr,V_DataLen;
	uchar8 *P_RamAddr=NULL;
	Str_3aTable V_Str_3aTable;
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_OADTabLen_T;

	for(V_i=95;V_i<Str_3aTable_E23RAM_Len;V_i++)/*ע��ò��ֲ�����Str_3aTable_E23RAM���һһ��Ӧ,ȥ����������б�*/
	{
		if((V_i>=233)&&(V_i<=243))/*ȥ����������б�OADTab*/
		{
			continue;
		}

		P_RamAddr=Str_3aTable_E23RAM[V_i].V_RamAddr;
		V_E2Addr=Str_3aTable_E23RAM[V_i].V_E2BakeUp1Addr;
		V_DataLen=Str_3aTable_E23RAM[V_i].V_DataLen;
		V_DataNum=Str_3aTable_E23RAM[V_i].V_DataNum;

		for(V_j=0;V_j<V_DataNum;V_j++)
		{
			P_RamAddr=Str_3aTable_E23RAM[V_i].V_RamAddr;
			V_E2Addr=Str_3aTable_E23RAM[V_i].V_E2BakeUp1Addr;

			V_E2Addr=V_E2Addr+V_j*(V_DataLen+C_CRCLen2);
			P_RamAddr=P_RamAddr+V_j*(V_DataLen+C_CRCLen2);

			V_Return_Flag=SF_ReadE2Three_698_AndCRC(V_E2Addr,V_DataLen,P_RamAddr);
		}
	}

	/******************OAD��ű����ݻָ�*************************/
	for(V_i=0;V_i<11;V_i++)
	{
		V_Str_3aTable=Str_3aTable_E23RAM[V_i+221];/*Free_OADTabLen_T,��ű���*/
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
		if(C_OK==V_Return_Flag)
		{
			V_OADTabLen_T=P_OADTabLen_T[0];
			V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*��ű�ÿ��OAD���C_698Free_OADTabDataType���ֽ�,Ŀǰ6�ֽڡ�2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/
			if(V_OADTabLen_T>C_698Free_OADTabLen)/*���ݳ��Ȱ�ȫ���ж�*/
			{
				return;/*�쳣*/
			}

			V_DataLen=V_OADTabLen_T;
			V_DataNum=Str_3aTable_E23RAM[V_i+233].V_DataNum;
			for(V_j=0;V_j<V_DataNum;V_j++)
			{
				P_RamAddr=Str_3aTable_E23RAM[V_i+233].V_RamAddr;
				V_E2Addr=Str_3aTable_E23RAM[V_i+233].V_E2BakeUp1Addr;

				V_E2Addr=V_E2Addr+V_j*(C_698Free_OADTabLen+C_CRCLen2);
				P_RamAddr=P_RamAddr+V_j*(C_698Free_OADTabLen+C_CRCLen2);

				V_Return_Flag=SF_ReadE2Three_698_AndCRC(V_E2Addr,V_DataLen,P_RamAddr);/*�������ݳ��ȸ���ʵ�����ݳ���*/
			}
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�uchar8 SF_AllDataZero_Judge(uchar8 *P_Data,uchar8 V_DataLen)
�����������ж������Ƿ�Ϊȫ��
���������uchar8 *P_Data:���ж����ݣ�uchar8 V_DataLen�����ж����ݳ���
�����������
���ز�����uchar8��C_OK:���ж�����Ϊȫ0��C_Error�����ж����ݲ�Ϊȫ0
����˵����
���û��ƣ�
��     ע��
*********************************************************************************/
uchar8 SF_AllDataZero_Judge(uchar8 *P_Data, uchar8 V_DataLen)
{
	uchar8 V_i;
	uchar8 V_Return_Flag;

	V_Return_Flag=C_OK;
	for(V_i=0;V_i<V_DataLen;V_i++)
	{
		if(P_Data[V_i]!=0)
		{
			break;
		}
	}
	if(V_i<V_DataLen)
	{
		V_Return_Flag=C_Error;
	}

	return V_Return_Flag;
}

uchar8 InF_ReadLoadData(ulong32 V_Data_Id,uchar8 *P_FixTime,uchar8 *P_Data,uchar8 *V_BlockNum,uchar8 *V_Length,uchar8 V_ReadSign)
{
	return C_OK;
}
uchar8 InF_ReadLastTimeLoadData(ulong32 V_Data_Id,uchar8 *P_FixTime,uchar8 *P_Data,uchar8 *V_BlockNum,uchar8 *V_Length)
{
	return C_OK;
}
/*********************************************************************************
����ԭ�ͣ�void InF_Get_Comm_Address(uchar8 *pV_ucComm_Address,uchar8 V_ucAddr_Type)
������������ȡͨ�ŵ�ַ
���������pV_ucComm_Address����ͨ�ŵ�ַ�����׵�ַ��������СΪͨ�ŵ�ַ�������
		V_ucAddr_TypeΪ��ַ���ͣ�0x00������ַ��0x10ͨ���ַ��0x20���ַ��0x30�㲥��ַ
���������*pV_ucComm_Addressͨ�ŵ�ַ
���ز�������
����˵����
���û��ƣ���ͨ�Ž�������ͨ�ŵ�ַ�жϵ�ʱ�򣬿��ٻ�ȡͨ�ŵ�ַ��
*********************************************************************************/
void InF_Get_Comm_Address(uchar8 *pV_ucComm_Address,uchar8 V_ucAddr_Type)
{
	uchar8 i;

//	if(V_ucAddr_Type == 0x80)	/*�鲥�����ݲ�Ŀǰû���鲥��ַ����ʱ��������*/
//	{
//		for(i=0;i<CLComm_Address;i++)
//		{
//			pV_ucComm_Address[i] = GV_MulticastAddr[i];
//		}
//	}
//	else
	if(V_ucAddr_Type == 0xC0)	/*�㲥*/
	{
		for(i=0;i<CLComm_Address;i++)
		{
			pV_ucComm_Address[i] = 0xAA;
		}
	}
	else
	{
		for(i=0;i<CLComm_Address;i++)
		{
			pV_ucComm_Address[i] = GV_Comm_Address[i];
		}
	}
}
/*********************************************************************************
����ԭ�ͣ�void InF_Check_Comm_Address(void)
����������У��RAM�е�ͨ�ŵ�ַ�Ƿ���ȷ
���������
�����������
���ز�����
����˵����
���û��ƣ���ͨ�Ŷ�ʱ�����ж�ʱ����
*********************************************************************************/
void InF_Check_Comm_Address(void)
{
	ushort16 V_usLen = CLComm_Address, V_usDataEncode;
	uchar8 V_ucDataTemp[8] = {0};

//	if(V_ucAddr_Type == 0x80)	//�鲥�����ݲ�Ŀǰû���鲥��ַ����ʱ��������
//	{
//		if(PF_Check_CRC(GV_MulticastAddr,CLComm_Address+2) != C_OK)
//		{
//			InF_Read_Data(CMulticastAddr,GV_MulticastAddr,&V_ucLen);
//		}
//	}
//	else
	{
		if(PF_Check_CRC(GV_Comm_Address, (CLComm_Address + C_CRCLen2) ) != C_OK)
		{
			InF_Read_Data(CComm_Address, GV_Comm_Address, &V_usLen, &V_usDataEncode);
		}
		else if(PF_Campare_Data(V_ucDataTemp, GV_Comm_Address, (CLComm_Address + C_CRCLen2) ) == C_OK)
		{
			memset(GV_Comm_Address, 0xFF, (CLComm_Address + C_CRCLen2) );		/*ͨ�ŵ�ַ��CRCΪȫ0�������´�EE��ȡͨ�ŵ�ַ*/
			InF_Read_Data(CComm_Address, GV_Comm_Address, &V_usLen, &V_usDataEncode);
		}
	}
}
/**************����΢RTC��У�ӿں���********************/
/*********************************************************************************
����ԭ�ͣ�uchar8 InF_ReadE2ThreeRTC(unsignedchar Page,unsignedchar Inpage,unsignedchar *P_Data,unsignedchar V_DataLen)
������������E2��������,�ڲ��ж�CRC
���������unsignedchar Page��unsignedchar Inpage����Ӧ����΢��E2�����ַת����
		uchar8 V_DataLen�������ݳ���
		uchar8 *P_Data�������ݻ���(������CRC)
�����������
���ز�����C_OK��C_IICError��C_CRCError��C_CrcErr_DataZero��
����˵����
���û��ƣ�
��     ע�������ݲ���ȷ��Ҳ������������
*********************************************************************************/
uchar8 InF_ReadE2ThreeRTC(ushort16 Page ,ushort16 Inpage, unsigned char *P_Data, unsigned char V_DataLen )
{
	uchar8 V_Read_Flag;
	ushort16 V_E2Addr;

	V_Read_Flag=C_OK;
	if((Page==ee_temperature_page)&&(Inpage==ee_temperature_inpage))/*����΢RTC��У�̶���ַ�ж�,�¶Ȳ���ϵ���洢*/
	{
		V_E2Addr=E2Addr_temperatureAddr;
	}
	else
	{
		if((Page==ee_ptatvalue_page)&&(Inpage==ee_ptatvalue_inpage))/*���²��,ADC*/
		{
			V_E2Addr=E2Addr_ptatvalueAddr;
		}
		else
		{
			if((Page==ee_ptatvalue_lt_page)&&(Inpage==ee_ptatvalue_lt_inpage))/*���²��,ADC*/
			{
				V_E2Addr=E2Addr_ptatvalue_ltAddr;
			}
			else
			{
				if((Page==ee_ptatvalue_ht_page)&&(Inpage==ee_ptatvalue_ht_inpage))/*���²��,ADC*/
				{
					V_E2Addr=E2Addr_ptatvalue_htAddr;
				}
				else
				{
					if((Page==ee_trimvalue_page)&&(Inpage==ee_trimvalue_inpage))/*���²��,����ֵ*/
					{
						V_E2Addr=E2Addr_trimvalueAddr;
					}
					else
					{
						if((Page==ee_trimvalue_lt_page)&&(Inpage==ee_trimvalue_lt_inpage))/*���²��,����ֵ*/
						{
							V_E2Addr=E2Addr_trimvalue_ltAddr;
						}
						else
						{
							if((Page==ee_trimvalue_ht_page)&&(Inpage==ee_trimvalue_ht_inpage))/*���²��,����ֵ*/
							{
								V_E2Addr=E2Addr_trimvalue_htAddr;
							}
							else
							{
								if((Page==ee_rtcadj_time_page)&&(Inpage==ee_rtcadjtime_inpage))/*д���¶����Уֵʱʱ���¼ҳ��ַ(ʼ�ղ���)*/
								{
									V_E2Addr=E2Addr_rtcadj_timeAddr;
								}
								else
								{
									V_Read_Flag=C_Error;
								}
							}
						}
					}
				}
			}
		}
	}

	if (V_Read_Flag!=C_Error)
	{
		V_Read_Flag=SF_ReadE2Three(V_E2Addr,V_DataLen,P_Data);
	}

	return V_Read_Flag;
}

uchar8 Verify_para(unsigned char Page ,unsigned char Inpage, unsigned char *Buf, unsigned char Len )/*һ�ж�����У�麯��*/
{
	if( PF_Check_CRC( Buf, (Len + C_CRCLen2) ) == C_OK ) return 0;	/*ram����crc��ȷ*/

	if( InF_ReadE2ThreeRTC( Page, Inpage, Buf, Len ) == C_OK )
	{
		return 0;/*�Ѿ�������ee���ָ�*/
	}
	else
	{
		return 1;
	}
}

/*********************************************************************************
����ԭ�ͣ�uchar8 InF_WriteE2ThreeRTC(unsigned int Page,uint08 inpage,uint08 *Buf,uint08 Len)
����������дE2��������
���������unsigned char Page��unsigned char Inpage����Ӧ����΢��E2�����ַת����
		uchar8 V_DataLen��Ҫд�����ݳ���
		uchar8 *P_Data��Ҫд�����ݻ���
�����������
���ز�����C_OK��C_SafeFlagError��C_IICError��
����˵����
���û��ƣ�
��     ע��
***********************************************************************************/
uchar8 InF_WriteE2ThreeRTC(ushort16 Page, ushort16 Inpage, uchar8 *P_Data, uchar8 V_DataLen )
{
	uchar8 V_Read_Flag;
	ushort16 V_E2Addr;

	V_Read_Flag=C_OK;
	if((Page==ee_temperature_page)&&(Inpage==ee_temperature_inpage))/*����΢RTC��У�̶���ַ�ж�,�¶Ȳ���ϵ���洢*/
	{
		V_E2Addr=E2Addr_temperatureAddr;
	}
	else
	{
		if((Page==ee_ptatvalue_page)&&(Inpage==ee_ptatvalue_inpage))/*���²��,ADC*/
		{
			V_E2Addr=E2Addr_ptatvalueAddr;
		}
		else
		{
			if((Page==ee_ptatvalue_lt_page)&&(Inpage==ee_ptatvalue_lt_inpage))/*���²��,ADC*/
			{
				V_E2Addr=E2Addr_ptatvalue_ltAddr;
			}
			else
			{
				if((Page==ee_ptatvalue_ht_page)&&(Inpage==ee_ptatvalue_ht_inpage))/*���²��,ADC*/
				{
					V_E2Addr=E2Addr_ptatvalue_htAddr;
				}
				else
				{
					if((Page==ee_trimvalue_page)&&(Inpage==ee_trimvalue_inpage))/*���²��,����ֵ*/
					{
						V_E2Addr=E2Addr_trimvalueAddr;
					}
					else
					{
						if((Page==ee_trimvalue_lt_page)&&(Inpage==ee_trimvalue_lt_inpage))/*���²��,����ֵ*/
						{
							V_E2Addr=E2Addr_trimvalue_ltAddr;
						}
						else
						{
							if((Page==ee_trimvalue_ht_page)&&(Inpage==ee_trimvalue_ht_inpage))/*���²��,����ֵ*/
							{
								V_E2Addr=E2Addr_trimvalue_htAddr;
							}
							else
							{
								if((Page==ee_rtcadj_time_page)&&(Inpage==ee_rtcadjtime_inpage))/*д���¶����Уֵʱʱ���¼ҳ��ַ(ʼ�ղ���)*/
								{
									V_E2Addr=E2Addr_rtcadj_timeAddr;
								}
								else
								{
									V_Read_Flag=C_Error;
								}
							}
						}
					}
				}
			}
		}
	}

	if (V_Read_Flag!=C_Error)
	{
		GV_D_SafeFlag|=C_W_SafeFlag_1; /*�ð�ȫ��־*/
		V_Read_Flag=SF_WR_E23_Data(V_E2Addr,V_DataLen,P_Data);
	}

	return V_Read_Flag;
}

/****************************************************************************
*����ԭ�� 	SF_EraseCodeFlash_Sector
*��������	����codeflash��һ������
*�������	V_ulAddInSector�����������׵�ַ
*������� 	��
*���ز���	��
*ȫ�ֱ���
*������ע	���ﲻ���ж���ַ�����ȵȵĺϷ��ԣ��ڵ��øú���ǰ�Ѿ������˺Ϸ����ж�
****************************************************************************/
void SF_EraseCodeFlash_Sector(ulong32 V_ulAddInSector)
{
	InF_Enable_Flash_CLK();
	FLASH_Erase_Sector(V_ulAddInSector);	/*������ַ���ڵ���������512�ֽ�*/
	InF_Disable_Flash_CLK();				/*Flash��д������ʱ��ʹ�ܣ�����͹�*/
}

/****************************************************************************
*����ԭ�� 	SF_WriteCodeFlash
*��������	д���ݵ�codeflash
*�������	V_CodeFlashAdd��д��codeflash��ַ��pV_ucDataIn��д�����ݻ��������ַ������ֽ�
*			V_usDataInLen��Ҫд�����ݳ���
*������� 	��
*���ز���	��
*ȫ�ֱ���
*������ע	���ﲻ���ж���ַ�����ȵȵĺϷ��ԣ��ڵ��øú���ǰ�Ѿ������˺Ϸ����ж�
****************************************************************************/
void SF_WriteCodeFlash(ulong32 V_ulCodeFlashAdd, uchar8 *pV_ucDataIn, ushort16 V_usDataInLen)
{
	InF_Enable_Flash_CLK();
	FLASH_Prog_ByteString(V_ulCodeFlashAdd, pV_ucDataIn, V_usDataInLen);	/*����д���ݵ�codeflash*/
	InF_Disable_Flash_CLK();												/*Flash��д������ʱ��ʹ�ܣ�����͹�*/
}
#if 0
/****************************************************************************
*����ԭ�� 	SF_EraseCodeFlash_Block
*��������	����codeflash��һ��block
*�������	V_ulAddInBlock���������׵�ַ
*������� 	��
*���ز���	��
*ȫ�ֱ���
*������ע	���ﲻ���ж���ַ�����ȵȵĺϷ��ԣ��ڵ��øú���ǰ�Ѿ������˺Ϸ����ж�
****************************************************************************/
void SF_EraseCodeFlash_Block(ulong32 V_ulAddInBlock)
{
	InF_Enable_Flash_CLK();
	FLASH_Erase_Block(V_ulAddInBlock);	/*������ַ���ڵ���������512*16�ֽ�*/
	InF_Disable_Flash_CLK();			/*Flash��д������ʱ��ʹ�ܣ�����͹�*/
}
#endif
/****************************************************************************
*����ԭ�� 	SF_Write_UpdataFlag
*��������	д������־��codeflash
*�������	pV_ucDataΪ������־�������ݻ����׵�ַ��V_usLengthΪ���ݳ���
*������� 	��
*���ز���	��
*ȫ�ֱ���
*������ע	���ﲻ���ж���ַ�����ȵȵĺϷ��ԣ��ڵ��øú���ǰ�Ѿ������˺Ϸ����ж�
****************************************************************************/
uchar8 SF_Write_UpdataFlag(uchar8 * pV_ucData, ushort16 V_usLength)
{
	uchar8 V_ucReturn = C_Error;
	uchar8 V_ucSafedArea_Data[C_SafedArea_Size];
	ushort16 V_usCRC_C = 0;
	ulong32 V_ulSafeArea_Addr;

	V_ulSafeArea_Addr = C_SafedArea_StardAddr;

	memcpy(V_ucSafedArea_Data, (uchar8 *)V_ulSafeArea_Addr, C_SafedArea_Size);		/*���ȱ���codeflash���ݵ���ʱ����*/

	memcpy(&V_ucSafedArea_Data[C_EnterBootFlag_Offset], pV_ucData, V_usLength);		/*����������־����ʱ����*/

	V_usCRC_C = PF_Cal_CRC_698(&V_ucSafedArea_Data[C_EnterBootFlag_Offset], V_usLength);		/*CRC16*/
	PF_Ushort16ToBuffer2(&V_ucSafedArea_Data[C_EnterBootFlag_Offset + V_usLength], &V_usCRC_C);

	if(PF_Campare_Data_698(V_ucSafedArea_Data, (uchar8 *)V_ulSafeArea_Addr, C_EnterBootFlag_Offset) != C_Equal)		/**/
	{
		memcpy(V_ucSafedArea_Data, (uchar8 *)V_ulSafeArea_Addr, C_EnterBootFlag_Offset);
	}

	if(PF_Campare_Data_698(&V_ucSafedArea_Data[C_EnterBootFlag_Offset + V_usLength + 2],
		( (uchar8 *)(V_ulSafeArea_Addr + C_EnterBootFlag_Offset + V_usLength + 2) ),
		(C_SafedArea_Size - (C_EnterBootFlag_Offset + V_usLength + 2) ) ) != C_Equal)
	{
		memcpy(&V_ucSafedArea_Data[C_EnterBootFlag_Offset + V_usLength + 2],
		( (uchar8 *)V_ulSafeArea_Addr + C_EnterBootFlag_Offset + V_usLength + 2),
		(C_SafedArea_Size - (C_EnterBootFlag_Offset + V_usLength + 2) ) );
	}

	/******************������������ͬʱд���µ�����**********************/
	if( GV_D_SafeFlag == C_W_SafeFlag)
	{
		SF_EraseCodeFlash_Sector(V_ulSafeArea_Addr);
		SF_WriteCodeFlash(V_ulSafeArea_Addr, V_ucSafedArea_Data, C_SafedArea_Size);
	}
	if(PF_Campare_Data_698(V_ucSafedArea_Data, (uchar8 *)V_ulSafeArea_Addr, (ushort16)C_SafedArea_Size) == C_Equal)		/*�ȶ�д��ǰ�������Ƿ�һ��*/
	{
		V_ucReturn = C_OK;
	}

	return V_ucReturn;
}

const uchar8 C_EnterBootloader_Flag[8] = {0x68, 0x86, 0x9A, 0xDB, 0x00, 0x00, 0x00, 0x00};	/*�̶�����������λ��־*/
/****************************************************************************
*����ԭ�� 	SF_Deal_FF86
*��������	������������
*�������	V_Data_IdΪOAD��P_DataΪ���ݻ����׵�ַ��V_Data_LengthΪ���ݳ���
*������� 	��
*���ز���	��
*ȫ�ֱ���
*������ע	���ﲻ���ж���ַ�����ȵȵĺϷ��ԣ��ڵ��øú���ǰ�Ѿ������˺Ϸ����ж�
****************************************************************************/
uchar8 SF_Deal_FF86(ulong32 V_Data_Id,uchar8 * P_Data,ushort16 V_Data_Length)
{
	uchar8 V_ucReturn = C_Error, V_ucActionNO = 0;
	uchar8 V_ucDataTemp[C_3DES_DataLen + C_CRCLen2],i;

	if(V_Data_Length == C_3DES_DataLen)
	{
		V_ucActionNO = (uchar8)(V_Data_Id >> 8);

		for(i = 0; i < C_3DES_DataLen; i++)									/*�����ݵߵ�һ�£���ͨ���н���ͳһ����ʱ�Ѹߵ��ֽڽ����˵ߵ�*/
		{
			V_ucDataTemp[i] = P_Data[C_3DES_DataLen - i - 1];
		}

		PF_3DES_Decode(V_ucDataTemp, V_ucDataTemp, (uchar8 *)C_3DES_Key1, (uchar8 *)C_3DES_Key2, (uchar8 *)C_3DES_Key3);	/*��������*/

		if(V_ucActionNO == 128)												/*�ж���֤�Ƿ���ȷ*/
		{
			if(PF_Campare_Data(V_ucDataTemp, (uchar8 *)C_3DES_FixedData, C_3DES_DataLen) == C_Equal)
			{
				V_ucReturn = SF_Deal_UpdataFlag( (uchar8)C_Enter_UpdataFlag, V_ucDataTemp, V_Data_Length);	/*������������״̬��*/
			}
			else
			{
				SF_Deal_UpdataFlag( (uchar8)C_Updata_Init, V_ucDataTemp, V_Data_Length);					/*������ʼ����������״̬��*/
			}
		}
		else if(V_ucActionNO == 129)										/*д����������־��codeflash*/
		{
			GV_D_SafeFlag |= C_W_SafeFlag_2;
			V_ucReturn = SF_Deal_UpdataFlag( (uchar8)C_WriteFlag_OK, V_ucDataTemp, V_Data_Length);		/*������������״̬��*/
		}
		else if(V_ucActionNO == 130)										/*�ж�����������־�Ƿ���ȷ*/
		{
			GV_D_SafeFlag |= C_W_SafeFlag_2;
			if(PF_Campare_Data(V_ucDataTemp, (uchar8 *)C_EnterBootloader_Flag, C_3DES_DataLen) == C_Equal)
			{
				V_ucReturn = SF_Deal_UpdataFlag( (uchar8)C_ResetFlag_OK, V_ucDataTemp, V_Data_Length);
			}
			else
			{
				SF_Deal_UpdataFlag( (uchar8)C_Updata_Init, V_ucDataTemp, V_Data_Length);					/*������ʼ����������״̬��*/
			}
		}
		else
		{
			;
		}
	}
	else
	{
		SF_Deal_UpdataFlag( (uchar8)C_Updata_Init, V_ucDataTemp, V_Data_Length);							/*������ʼ����������״̬��*/
		V_ucReturn = C_DataLenError;
	}
	GV_D_SafeFlag = 0;
	return V_ucReturn;
}


/****************************************************************************
*����ԭ�� 	SF_Deal_UpdataFlag
*��������	������������״̬��
*�������	V_ucOperationFlag: C_Clear_Status���־��C_Start_UpdataMode��������ģʽ��
*			C_Version_OK�汾��ȷ
*������� 	��
*���ز���	C_OK��ʾCRC��ȷ
*			C_Error��ʾCRC���ԣ���������²�����Ӧ�����Ƿ�֡����ֱ�Ӹ�λ����
*ȫ�ֱ���
*������ע�����У��CRC������ֱ�ӽ���־����
****************************************************************************/
uchar8 SF_Deal_UpdataFlag(uchar8 V_ucOperationFlag, uchar8 *pV_ucData, ushort16 V_usDataIn_Len)
{
	uchar8 V_ucReturn = C_CRCError;
	ushort16 V_usCRC16_C, V_usCRC16_F;
	ulong32 V_ulControlFlag = 0;

	V_usCRC16_C = PF_Cal_CRC_698(&SStr_UpdataFlag.ControlFlag[0], (C_Str_UpdataFlag_Len - C_CRCLen2) );	/*CRC16*/
	V_usCRC16_F = PF_Buffer2ToLong16_698(&SStr_UpdataFlag.ucCRC[0]);							/*����CRC*/
	if(V_usCRC16_C == V_usCRC16_F)
	{
		switch(V_ucOperationFlag)
		{
			case C_Enter_UpdataFlag:
			{
				V_ulControlFlag = C_UpdataFlag_OKFlag;											/*ȡ��־*/
				PF_Ulong32ToBuffer4_698(&SStr_UpdataFlag.ControlFlag[0], &V_ulControlFlag, 4);
				SStr_UpdataFlag.FlowFlag = C_Enter_UpdataFlag;
				SStr_UpdataFlag.OverTimer = C_OverTimer_10s;
				V_ucReturn = C_OK;
				break;
			}
			case C_WriteFlag_OK:
			{
				GV_D_SafeFlag |= C_W_SafeFlag_3;
				V_ulControlFlag = PF_Buffer4ToUlong32_698(&SStr_UpdataFlag.ControlFlag[0]);		/*ȡ��־*/
				if( (V_ulControlFlag == C_UpdataFlag_OKFlag) && (SStr_UpdataFlag.FlowFlag == C_Enter_UpdataFlag) )
				{
					V_ucReturn = SF_Write_UpdataFlag(pV_ucData, V_usDataIn_Len);				/*����codeflash�е�������־*/
					if(V_ucReturn == C_OK)
					{
						SStr_UpdataFlag.FlowFlag = C_WriteFlag_OK;
						SStr_UpdataFlag.OverTimer = C_OverTimer_10s;
					}
					else
					{
						memset(&SStr_UpdataFlag.ControlFlag[0], 0, 4);
						SStr_UpdataFlag.FlowFlag = C_Updata_Init;
						SStr_UpdataFlag.OverTimer = 0;
						V_ucReturn = C_Error;													/*д��־ʧ��*/
					}
				}
				else
				{
					memset(&SStr_UpdataFlag.ControlFlag[0], 0, 4);
					SStr_UpdataFlag.FlowFlag = C_Updata_Init;
					SStr_UpdataFlag.OverTimer = 0;
					V_ucReturn = C_Error;						/*δ��������ģʽ*/
				}
				break;
			}
			case C_ResetFlag_OK:
			{
				GV_D_SafeFlag |= C_W_SafeFlag_3;
				V_ulControlFlag = PF_Buffer4ToUlong32_698(&SStr_UpdataFlag.ControlFlag[0]);		/*ȡ��־*/
				if( (V_ulControlFlag == C_UpdataFlag_OKFlag) && (SStr_UpdataFlag.FlowFlag == C_WriteFlag_OK)
					&&(GV_D_SafeFlag == C_W_SafeFlag) )			/*��ȫ��־�ж�*/
				{
					SStr_UpdataFlag.FlowFlag = C_ResetFlag_OK;
					SStr_UpdataFlag.OverTimer = C_OverTimer_2s;
					V_ucReturn = C_OK;
				}
				else
				{
					memset(&SStr_UpdataFlag.ControlFlag[0], 0, 4);
					SStr_UpdataFlag.FlowFlag = C_Updata_Init;
					SStr_UpdataFlag.OverTimer = 0;
					V_ucReturn = C_Error;						/*δ��������ģʽ*/
				}
				break;
			}
			case C_TimerDecrease:
			{
				V_ulControlFlag = PF_Buffer4ToUlong32_698(&SStr_UpdataFlag.ControlFlag[0]);		/*ȡ��־*/
				if(V_ulControlFlag == C_UpdataFlag_OKFlag)
				{
					if(SStr_UpdataFlag.OverTimer > 0)
					{
						SStr_UpdataFlag.OverTimer--;
						if(SStr_UpdataFlag.OverTimer == 0)
						{
							if(SStr_UpdataFlag.FlowFlag == C_ResetFlag_OK)
							{
								InF_Reset_MCU();					/*������λ*/
							}
							else									/*������ʱ��ʱ����״̬�ָ�����ʼ״̬*/
							{
								memset(&SStr_UpdataFlag.ControlFlag[0], 0, 4);
								SStr_UpdataFlag.FlowFlag = C_Updata_Init;
								SStr_UpdataFlag.OverTimer = 0;
								V_ucReturn = C_OK;
							}
						}
					}
				}
				else
				{
					memset(&SStr_UpdataFlag.ControlFlag[0], 0, 4);
					SStr_UpdataFlag.FlowFlag = C_Updata_Init;
					SStr_UpdataFlag.OverTimer = 0;
					V_ucReturn = C_Error;						/*δ��������ģʽ*/
				}
				break;
			}
			default:	/*����*/
			{
				memset(&SStr_UpdataFlag.ControlFlag[0], 0, 4);
				SStr_UpdataFlag.FlowFlag = C_Updata_Init;
				SStr_UpdataFlag.OverTimer = 0;
				V_ucReturn = C_OK;
				break;
			}
		}
	}

	/************************************************/
	V_usCRC16_C = PF_Cal_CRC_698(&SStr_UpdataFlag.ControlFlag[0], (C_Str_UpdataFlag_Len - C_CRCLen2) );		/*CRC16*/
	PF_Ushort16ToBuffer2_698(&SStr_UpdataFlag.ucCRC[0], &V_usCRC16_C);

	return V_ucReturn;
}

/****************************************************************************
*����ԭ�� 	DataProcess_External_Message
*��������	����������ʱ����ÿ���ӵ���һ��
*�������	P_Msg_Parameterָ����Ϣ�����ṹ���ַ
*			��Ϣ�ţ�C_Msg_DataProcess_External
*������� 	��
*���ز���	��
*ȫ�ֱ���
*������ע��	�ú������û���5ms��ʱ��1000ms��������RTC����仯��Ϣ
****************************************************************************/
void  DataProcess_External_Message(Str_Msg_Parameter * P_Msg_Parameter)
{
	uchar8 V_ucTemp[2];

	memcpy(V_ucTemp, (uchar8 *)C_Software_Featurcode, 2);
	SF_Deal_UpdataFlag(C_TimerDecrease, V_ucTemp, 0);
}

/**********************************************************************************
����ԭ�ͣ� uchar8 InF_GetData_ObjectManage(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf,
					ushort16 *pV_usDataLen, uchar8 *pV_ucDataEncode)
���������� �ú���Ϊ���������ṩ�Ķ�ȡ��ͨ���ԵĽӿں���

�������������V_ulOADΪ��������֧�ֵ�OAD
			Ŀǰ����Э��Ҫ��֧��OAD������OAD������OAD�������µ���չ��������ֽ�ΪFF
			pV_ucDataBufΪ����ȡ���ݴ�Ż����׵�ַ
			*pV_usDataLen����Ϊ������󳤶ȣ�����ȡ���ݳ��ȳ��������泤��ʱ���ش���
			pV_ucDataEncode���ڴ�Ÿ����Զ�Ӧ�������͵Ļ����׵�ַ��������ͨ����ͨ��ֻ��1������

��������� 	*pV_ucDataBufΪ��ȡ�Ļ������ݣ��û������ݼ�ʹӦ�����Ҳ���ܱ��ĵ���Ϊ�˼�����ʱ����
				���ݲ�ֱ�ӽ��������뻺�棩
			*pV_usDataLenΪʵ�ʶ�ȡ���ݳ��ȣ���ȡ����ʱ�ó������ݲ㸳ֵ0
			*pV_ucDataEncodeΪ�����Զ�Ӧ���ڲ����룬ÿ������ֱ�ӷ�Ӧ���Ӧ��698���뷽ʽ

���ز����� 	����C_OK��ʾ���ݶ�ȡ�ɹ�����ʱ����ֱ����*pV_ucDataBuf�����ж�Ӧ*pV_usDataLen�ֽ�
				���ȵ�����
			����������ʾ����������ͣ����������ݲ�����

���û��ƣ�	ģ���ȡ����ģ���������ʱ���ã�����ȡģ���ڲ���������ֱ�ӵ������ݲ����ݽӿ�
��    ע��
**********************************************************************************/
uchar8 InF_GetData_ObjectManage(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
{
	uchar8 V_ucReturn = C_Error;

	if( ( (V_ulOAD & 0xFF000000) == 0x00000000)				/*��ǰ����*/
		|| (V_ulOAD == CChargeBal_Hex_Cent)					/*ʣ����*/
		|| (V_ulOAD == COverDraft_Hex_Cent)					/*͸֧���*/
		|| (V_ulOAD == CM_Com_Ac_Tol_En_0)					/*�¶��õ���*/
		|| (V_ulOAD == CY_Com_Ac_Tol_En_0)					/*�����õ���*/
		)
	{
		V_ucReturn = InF_Get_EnergyModule(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
	}
	else if( (V_ulOAD & 0xFF000000) == 0x10000000)
	{
		V_ucReturn = InF_Get_DemandModule(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
	}
	else if( ( (V_ulOAD & 0xFFFF0000) == 0x20010000 )		/*����*/
			|| ( (V_ulOAD & 0xFFFF0000) == 0x20070000 )		/*һ����ƽ���й�����*/
			|| ( (V_ulOAD & 0xFFFF0000) == 0x20080000 )		/*һ����ƽ���޹�����*/
			)
	{
		V_ucReturn = InF_Get_MeterICModule(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
	}
	else if( ( (V_ulOAD & 0xFFFF0000) == 0xF1000000)		/*ESAM�ӿ���*/
			|| (V_ulOAD == CPurchasePowTime)				/*�������*/
			)
	{
		V_ucReturn = InF_Get_SafeModule(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
	}
	else if( ( (V_ulOAD & 0xFFFF0000) == 0xF2050000 )
			|| ( (V_ulOAD & 0xFFFF0000) == 0x80000000 )
			|| ( (V_ulOAD & 0xFFFF0000) == 0x80010000 )
			)
	{
		V_ucReturn = InF_Get_RelayModule(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
	}
	else
	{
		V_ucReturn = InF_Read_Data(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
	}

	return V_ucReturn;
}

/**********************************************************************************
����ԭ�ͣ� uchar8 InF_SetData_ObjectManage(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf,
					ushort16 V_usDataLen, uchar8 *pV_ucDataEncode)
����������д���ݲ�ӿں���
���������
		uchar8 V_usMsg_Num:��Ϣ�ţ������ж��Ƿ���дȨ�ޣ�
		ulong32 V_ulOAD�����ݱ�ʶ�룻
		uchar8 *pV_ucDataBuf���������Ż��棻
		ushort16 V_usDataLen����д���ݳ��ȣ�
		uchar8 V_W_Safe_Flag���궨�壬��д��ȫ��־��

�����������

���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_SafeFlagError��C_NoAccess��

���û��ƣ�

��     ע��д���ݲ�ʱ���ã�ע�ⰲȫ��־
**********************************************************************************/
uchar8 InF_SetData_ObjectManage(uchar8 V_usMsg_Num, ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 V_usDataLen, uchar8 V_W_Safe_Flag)
{
	uchar8 V_ucReturn = C_Error;

	V_ucReturn = InF_Write_Data(V_usMsg_Num, V_ulOAD, pV_ucDataBuf, V_usDataLen, V_W_Safe_Flag);

	return V_ucReturn;
}

/**********************************************************************************
����ԭ�ͣ� InF_GetData_Record_DataBase(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf,
					ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)

���������� �ú���Ϊ���ݲ��ṩ�Ķ�ȡ��¼�����ݵĽӿں�����֧�ַ���1��2��9��ȡ�������ȡ��ʽ
			������ڲ�����pStr_Read->pV_ucRST���뷽������

�������������pStr_ReadΪ��¼�����ݲ����ṹ���ַ������������ȡ��¼OAD������OAD����ȡ����
			pV_ucDataBufΪ����ȡ���ݴ�Ż����׵�ַ
			*pV_usDataLen����Ϊ������󳤶ȣ�����ȡ���ݳ��ȳ��������泤��ʱ���ش���
			pV_ucSupplementaryInformationΪ���ظ���������Ϣ�����׵�ַ
			*pV_usSIDataLen����Ϊ����������󻺴�

��������� 	*pV_ucDataBufΪ��ȡ�Ļ������ݣ��û������ݼ�ʹӦ�����Ҳ���ܱ��ĵ���Ϊ�˼�����ʱ����
				���ݲ�ֱ�ӽ��������뻺�棩
			*pV_usDataLenΪʵ�ʶ�ȡ���ݳ��ȣ���ȡ����ʱ�ó������ݲ㸳ֵ0
			*pV_ucDataEncodeΪ�����Զ�Ӧ���ڲ����룬ÿ������ֱ�ӷ�Ӧ���Ӧ��698���뷽ʽ

���ز����� 	����C_OK��ʾ���ݶ�ȡ�ɹ�����ʱ����ֱ����*pV_ucDataBuf�����ж�Ӧ*pV_usDataLen�ֽ�
				���ȵ�����
			����������ʾ����������ͣ����������ݲ�����

���û��ƣ�	ģ���ȡ����ģ���������ʱ���ã�����ȡģ���ڲ���������ֱ�ӵ������ݲ����ݽӿ�
��    ע��
**********************************************************************************/
uchar8 InF_GetData_Record_DataBase(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
{
	uchar8 V_ucReturn = C_Error, V_timeFlash, V_NextSign, V_ucMode = C_698Mode;
	ushort16 V_usBlockNum = 1, V_usIntervalTime = 0;
	ulong32 V_ulOAD_RST;

	if( (pStr_Read->pV_ucRST[C_RST_Method_O] == 1)
		|| (pStr_Read->pV_ucRST[C_RST_Method_O] == 2) )
	{
		PF_Buffer4ToUlong32( &pStr_Read->pV_ucRST[C_RST_OADOrNum_O], &V_ulOAD_RST, 4);
		if( ( (V_ulOAD_RST == CFreeTime ) && ( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x50000000) )
			|| ( (V_ulOAD_RST == CEventHPTime ) && ( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x30000000) ) )
		{
			V_timeFlash = 0x00;
		}
		else if( V_ulOAD_RST == CEventEndTime )
		{
			V_timeFlash = 0xAA;
		}
		else
		{
			return V_ucReturn;
		}
		if(pStr_Read->pV_ucRST[C_RST_Method_O] == 2)		/*ȡ��ȡ���*/
		{
			PF_Buffer2ToUshort16(&pStr_Read->pV_ucRST[C_RST_TIInter_O], &V_usIntervalTime);
			V_usBlockNum = 0;
		}
	}
	else if(pStr_Read->pV_ucRST[C_RST_Method_O] == 9)
	{
		pStr_Read->pV_ulROAD[0] = ( (pStr_Read->pV_ulROAD[0]&0xFFFFFF00) | pStr_Read->pV_ucRST[C_RST_OADOrNum_O]);		/*��ȡ��N�˼�¼*/
	}
	else
	{
		return V_ucReturn;
	}
	if( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x30000000)			/*��ȡ�¼���¼*/
	{
		V_ucReturn = InF_ReadEventData(pStr_Read->pV_ulROAD, &pStr_Read->pV_ucRST[C_RST_Timer1_O], pV_ucDataBuf, &V_NextSign,  pV_usDataLen, V_timeFlash);
	}
	else if( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x50000000)		/*��ȡ�����¼*/
	{
		V_ucReturn = InF_ReadFreezeData(pStr_Read->pV_ulROAD, &pStr_Read->pV_ucRST[C_RST_Timer1_O], pV_ucDataBuf, &V_usBlockNum, pV_usDataLen, V_usIntervalTime, (uchar8 *)pStr_SuppInfo->pV_usEncode, V_ucMode);
	}
	else
	{
		V_ucReturn = C_ObjectUndefine_DAR;
	}

	if(V_ucReturn == C_OK)
	{
		if( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x30000000)
		{
			pStr_SuppInfo->V_ucNxtFrame = ( (V_NextSign >> 4) & 0x03);		/*����֡��־*/
			pStr_SuppInfo->V_ucFrameNum = ( V_NextSign & 0x0F);				/*��¼����*/
			pStr_SuppInfo->V_ucLastFlag = ( (V_NextSign >> 6) & 0x03);		/*�Ƿ�������һ��*/
		}
		else
		{
			pStr_SuppInfo->V_ucNxtFrame = ( (uchar8)(V_usBlockNum  & 0x03) );		/*����֡��־*/
			pStr_SuppInfo->V_ucFrameNum = ( (uchar8)(V_usBlockNum >> 2) );			/*��¼����*/
		}
	}
	return V_ucReturn;
}


/**********************************************************************************
����ԭ�ͣ� InF_GetData_Record(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf,
					ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)

���������� �ú���Ϊ���ݲ��ṩ�Ķ�ȡ��¼�����ݵĽӿں�����֧�ַ���1��2��9��ȡ�������ȡ��ʽ
			������ڲ�����pStr_Read->pV_ucRST���뷽������

�������������pStr_ReadΪ��¼�����ݲ����ṹ���ַ������������ȡ��¼OAD������OAD����ȡ����
			pV_ucDataBufΪ����ȡ���ݴ�Ż����׵�ַ
			*pV_usDataLen����Ϊ������󳤶ȣ�����ȡ���ݳ��ȳ��������泤��ʱ���ش���
			pV_ucSupplementaryInformationΪ���ظ���������Ϣ�����׵�ַ
			*pV_usSIDataLen����Ϊ����������󻺴�

��������� 	*pV_ucDataBufΪ��ȡ�Ļ������ݣ��û������ݼ�ʹӦ�����Ҳ���ܱ��ĵ���Ϊ�˼�����ʱ����
				���ݲ�ֱ�ӽ��������뻺�棩
			*pV_usDataLenΪʵ�ʶ�ȡ���ݳ��ȣ���ȡ����ʱ�ó������ݲ㸳ֵ0
			*pV_ucDataEncodeΪ�����Զ�Ӧ���ڲ����룬ÿ������ֱ�ӷ�Ӧ���Ӧ��698���뷽ʽ

���ز����� 	����C_OK��ʾ���ݶ�ȡ�ɹ�����ʱ����ֱ����*pV_ucDataBuf�����ж�Ӧ*pV_usDataLen�ֽ�
				���ȵ�����
			����������ʾ����������ͣ����������ݲ�����

���û��ƣ�	ģ���ȡ����ģ���������ʱ���ã�����ȡģ���ڲ���������ֱ�ӵ������ݲ����ݽӿ�
��    ע��
**********************************************************************************/
uchar8 InF_GetData_Record(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
{
	uchar8 V_ucReturn;

	if( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x30000000)			/*��ȡ�¼���¼*/
	{
		V_ucReturn = InF_Get_EventModule(pStr_Read, pV_ucDataBuf, pV_usDataLen, pStr_SuppInfo);
	}
	else if( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x50000000)		/*��ȡ�����¼*/
	{
		V_ucReturn = InF_GetData_Record_DataBase(pStr_Read, pV_ucDataBuf, pV_usDataLen, pStr_SuppInfo);
	}
	else
	{
		V_ucReturn = C_ObjectUndefine_DAR;
	}

	return V_ucReturn;
}




