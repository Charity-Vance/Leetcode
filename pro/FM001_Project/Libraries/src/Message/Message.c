
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     Message.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   ��ʱ�������ļ�
///*Function List: 
///*****************************************************************************************///
///*History1:      ��1���޸�
///*����1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*����2. Date:
///*   	   Author:
///*       Modification:
		///*********************************************************************************///
///*History2:      ��2���޸�
///*����1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*����2. Date:
///*   	   Author:
///*       Modification:
///*****************************************************************************************///


#include "Public.h"
#include "Message.h"
#include "Dispatch.h"


static	uchar8	SV_MsgDerictData[C_MsgForDispatchLen];	///*����Ϣʱ����Ϣ�����ݴ棬��Ŀ����Ϣģ����*///

///*����1����Ϣ��500msͨ�š���ʾ�����л����������ݶ�Ϊ200�ֽڣ�C_MsgQueue1Len��*///
typedef struct
{
	ushort16	SV_Msg1RdPtr;	///*����Ϣָ��*///
	ushort16	SV_Msg1WrPtr;	///*д��Ϣָ��*///
	uchar8		SV_Msg1Buffer[C_MsgQueue1Len];	///*��Ϣbuffer*///
}Str_MsgQueue1_Type;

///*����2����Ϣ���������е���Ϣ�����л����������ݶ�Ϊ2048�ֽڣ�C_ MsgQueue2Len��*///
typedef struct
{
	ushort16	SV_Msg2RdPtr;	///*����Ϣָ��*///
	ushort16	SV_Msg2WrPtr;	///*д��Ϣָ��*///
	uchar8		SV_Msg2Buffer[C_MsgQueue2Len];	///*��Ϣbuffer*///
}Str_MsgQueue2_Type;

#if(_DEBUG)
Str_MsgQueue1_Type Str_MsgQueue1;
Str_MsgQueue2_Type Str_MsgQueue2 @".DataProcessADDR";
#else
static Str_MsgQueue1_Type Str_MsgQueue1;
static Str_MsgQueue2_Type Str_MsgQueue2 @".DataProcessADDR";
#endif


const uchar8 Table_FirstMsgQueue[]=
{
	C_Msg_Communication,			///*ͨ����Ϣ*///
	C_Msg_Display,					///*��ʾ��Ϣ*///
	C_Msg_Dispatch					///*������Ϣ:��RTC*///
};
#define C_Table_FirstMsgQueue_Len  (sizeof(Table_FirstMsgQueue))

///***********************************************************************************///
///*Function���ж���Ϣ�Ƿ�Ϊ��1������Ϣ*///
///*Description��*///
///*Input:Table_FirstMsgQueue:��1��Ϣ���б��:ͨ��/��ʾ/��RTC*///
///*      C_Table_FirstMsgQueue_Len:��񳤶�(����ѭ���жϴ���)*///
///*Output����*///
///*return:��1������ϢΪC_First_Squeue,��2������ϢΪC_Second_Squeue*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///***********************************************************************************///
uchar8 SF_JudgeMessageQueue(uchar8 DerictMsgNo)
{
	uchar8 i;
	
	for(i=0;i<C_Table_FirstMsgQueue_Len;i++)
	{
		if(DerictMsgNo == Table_FirstMsgQueue[i])
		{
			return C_First_Squeue;
		}
	}
	return C_Second_Squeue;
}
///***********************************************************************************///
///*Function����ʼ����Ϣ����*///
///*Description��*///
///*Input����*///
///*Output����*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///***********************************************************************************///
void InF_InitMessage(void)
{
	ushort16 i;
	
	Str_MsgQueue1.SV_Msg1RdPtr = C_InitMsg;
	Str_MsgQueue1.SV_Msg1WrPtr = C_InitMsg;
	for(i=0;i<C_MsgQueue1Len;i++)
	{
		Str_MsgQueue1.SV_Msg1Buffer[i] = C_InitMsg;
	}
	
	Str_MsgQueue2.SV_Msg2RdPtr = C_InitMsg;
	Str_MsgQueue2.SV_Msg2WrPtr = C_InitMsg;
	for(i=0;i<C_MsgQueue2Len;i++)
	{
		Str_MsgQueue2.SV_Msg2Buffer[i] = C_InitMsg;
	}
	
	for(i=0;i<C_MsgForDispatchLen;i++)
	{
		SV_MsgDerictData[i] = C_InitMsg;
	}
	
}

///***********************************************************************************///
///*Function��SF_CalMessagePtr(ushort16 V_usCurrentRdPtr,ushort16 V_usCurrentPtr,ushort16 V_ucAddLen,ushort16 V_usMaxLen)*///
///*Description���жϴ�дָ�뿪ʼ����д���ֽ���*///
///*Input��V_usCurrentRdPtr��ǰ��ָ�룬V_usCurrentPtr��ǰдָ�룬V_ucAddLen��Ϣ���ȣ�V_usMaxLenΪ�����г���*///
///*Output�����������ʣ�����д���ֽ�����C_NoEnoughMsgSpace��ʾ��Ϣ��������*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///*Author:zhiyong.gu*///
///***********************************************************************************///
ushort16 SF_CalMessagePtr(ushort16 V_usCurrentRdPtr,ushort16 V_usCurrentPtr,ushort16 V_ucAddLen,ushort16 V_usMaxLen)
{
	ushort16 V_usLen;
	
	V_usLen = V_ucAddLen;
	if(V_usCurrentRdPtr > V_usCurrentPtr)
	{
		if((V_usCurrentPtr + V_ucAddLen) > V_usCurrentRdPtr)	///*���ζ����в�����дһ����Ϣ�����������ֱ�ӷ���0*///
		{
			return C_NoEnoughMsgSpace;
		}
	}
	else
	{
		if((V_usCurrentPtr + V_ucAddLen) > V_usMaxLen)
		{
			V_usLen = (V_usMaxLen - V_usCurrentPtr);
			if((V_ucAddLen-V_usLen) > V_usCurrentRdPtr)
			{
				V_usLen = C_NoEnoughMsgSpace;
			}
		}
		else
		{
			 V_usLen = V_ucAddLen;
		}
	}
	return V_usLen;
}
///**************************************************************************************************///
///*Function��void InF_ReadMessegeDerictAddr(Str_Msg_Parameter *V_Msg,uchar8 V_ucMessageSqueueNum)	*///
///*Description������Ϣ��������Ϣ�����ṹ�����														*///
///*Input��V_Msg�����ṹ��ָ���ַ																	*///
//*			V_ucMessageSqueueNum��Ϣ���кţ�C_First_Squeue��ʾ��һ����Ϣ����						*///
///*			C_Second_Squeue��ʾ�ڶ�����Ϣ����													*///
///*Output��*V_MsgΪ����Ϣ�����ж�������Ϣ															*///
///*return:C_OK��ʾ����Ϣȡ����C_Error��ʾû����Ϣȡ�������ڵ������͹�����Ϣ���еĴ���			*///
///*Calls��																							*///
///*Called By�������ȶ�ȡ��Ϣ����																	*///
///*Influence��																						*///
///*Tips��																							*///
///*Others��																						*///
///*Author:zhiyong.gu																				*///
///**************************************************************************************************///
uchar8 InF_ReadMessegeDerictAddr(Str_Msg_Parameter *V_Msg,uchar8 V_ucMessageSqueueNum)
{
	ushort16 *P_usMsgRdPtr;
	ushort16 *P_usMsgWRPtr;
	uchar8 *P_ucMsgBuffer;
	ushort16 V_usBufferMaxLen,i;
	uchar8 V_ucMsgLen;
	uchar8 V_ucCS=0;
	
//	for(V_ucMsgLen=0;V_ucMsgLen<C_MsgForDispatchLen;V_ucMsgLen++)	///*���ȴ����Ϣ����������*///
//	{
//		SV_MsgDerictData[V_ucMsgLen] = 0;
//	}
	
	if(V_ucMessageSqueueNum == C_First_Squeue) ///*ͨ�ź���ʾ���ö���1���������ö���2*///
	{
		P_usMsgRdPtr = &Str_MsgQueue1.SV_Msg1RdPtr;
		P_usMsgWRPtr = &Str_MsgQueue1.SV_Msg1WrPtr;
		P_ucMsgBuffer = Str_MsgQueue1.SV_Msg1Buffer;
		V_usBufferMaxLen = C_MsgQueue1Len;
	}
	else
	{
		P_usMsgRdPtr = &Str_MsgQueue2.SV_Msg2RdPtr;
		P_usMsgWRPtr = &Str_MsgQueue2.SV_Msg2WrPtr;
		P_ucMsgBuffer = Str_MsgQueue2.SV_Msg2Buffer;
		V_usBufferMaxLen = C_MsgQueue2Len;
	}
///****************�����ж�дָ��Ϸ����ж�******************///
	if((*P_usMsgRdPtr >= V_usBufferMaxLen)||(*P_usMsgWRPtr >= V_usBufferMaxLen))
	{
		*P_usMsgRdPtr = 0;
		*P_usMsgWRPtr = 0;
	}
	
	V_Msg->DerictAddr = C_NULL;
	V_Msg->Parameter = SV_MsgDerictData;
	
	if(*P_usMsgRdPtr == *P_usMsgWRPtr)	///*��Ϣ������Ϊ��*///
	{
		return C_Error;
	}
	if(*P_usMsgRdPtr != *P_usMsgWRPtr)	///*��Ϣ�����в�Ϊ��*///
	{
		if(*P_usMsgRdPtr < *P_usMsgWRPtr)
		{
			i = *P_usMsgRdPtr;
			while(i<*P_usMsgWRPtr)
			{
				if(P_ucMsgBuffer[i] == C_MsgFrame_Start)
				{
					*P_usMsgRdPtr = i;
					break;
				}
				P_ucMsgBuffer[i] = 0;
				i++;
			}
			if(i >= *P_usMsgWRPtr)
			{
				*P_usMsgRdPtr = *P_usMsgWRPtr;
				return C_Error;
			}
		}
		else
		{
			i = *P_usMsgRdPtr;
			while(i<V_usBufferMaxLen)
			{
				if(P_ucMsgBuffer[i] == C_MsgFrame_Start)
				{
					*P_usMsgRdPtr = i;
					break;
				}
				P_ucMsgBuffer[i] = 0;
				i++;
			}
			if(i >= V_usBufferMaxLen)
			{
				i = 0;
				while(i<(*P_usMsgWRPtr))
				{
					if(P_ucMsgBuffer[i] == C_MsgFrame_Start)
					{
						*P_usMsgRdPtr = i;
						break;
					}
					P_ucMsgBuffer[i] = 0;
					i++;
				}
				if(i >= *P_usMsgWRPtr)
				{
					*P_usMsgRdPtr = *P_usMsgWRPtr;
					return C_Error;
				}
			}
		}
	}
///******************�����ж�CS�Ƿ���ȷ*************************///
///******************�����ȡ��Ϣ���ݣ�����������Ϣ����������*******************************///
	V_ucCS += P_ucMsgBuffer[*P_usMsgRdPtr];
	P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
	(*P_usMsgRdPtr)++;
	if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
	{
		(*P_usMsgRdPtr) = 0;
	}
	
	V_ucMsgLen = P_ucMsgBuffer[*P_usMsgRdPtr];	///*ȡ�����Ϣ�ĳ���*///
	V_ucCS += P_ucMsgBuffer[*P_usMsgRdPtr];
	P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
	if(V_ucMsgLen <= 4)	///*���Ȳ���ֱ���˳�:Դ��ַ��Ŀ�ĵ�ַ��CS��������*///
	{
		return C_Error;
	}
	V_ucMsgLen -= 4;
	V_Msg->Length = V_ucMsgLen;		///*��Ϣ����*///
	(*P_usMsgRdPtr)++;
	if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
	{
		(*P_usMsgRdPtr) = 0;
	}
	if(V_Msg->Length > C_MsgForDispatchLen)	///*���ȴ�����Ϣ���buffer��󳤶ȷ��ش���*///
	{
		return C_Error;
	}
	
	V_Msg->SourceAddr = P_ucMsgBuffer[*P_usMsgRdPtr];
	V_ucCS += P_ucMsgBuffer[*P_usMsgRdPtr];
	P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
	(*P_usMsgRdPtr)++;
	if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
	{
		(*P_usMsgRdPtr) = 0;
	}
	
	V_Msg->DerictAddr = P_ucMsgBuffer[*P_usMsgRdPtr];
	V_ucCS += P_ucMsgBuffer[*P_usMsgRdPtr];
	P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
	(*P_usMsgRdPtr)++;
	if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
	{
		(*P_usMsgRdPtr) = 0;
	}
	
//	V_Msg->Parameter = SV_MsgDerictData;
	for(i=0;i<V_Msg->Length;i++)
	{
		V_Msg->Parameter[i] = P_ucMsgBuffer[*P_usMsgRdPtr];
		V_ucCS += P_ucMsgBuffer[*P_usMsgRdPtr];
		P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
		(*P_usMsgRdPtr)++;
		if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
		{
			(*P_usMsgRdPtr) = 0;
		}
	}
	
	if(V_ucCS != P_ucMsgBuffer[*P_usMsgRdPtr])
	{
		P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
		(*P_usMsgRdPtr)++;	///*��������Ϣָ��*///
		if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
		{
			(*P_usMsgRdPtr) = 0;
		}
		return C_Error;	///*CS���ԣ�ֱ��Ӧ�����*///
	}
	P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
	(*P_usMsgRdPtr)++;	///*��������Ϣָ��*///
	if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
	{
		(*P_usMsgRdPtr) = 0;
	}
	
	if(P_ucMsgBuffer[*P_usMsgRdPtr] != C_MsgFrameEnd)
	{
		P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
		(*P_usMsgRdPtr)++;	///*��������Ϣָ��*///
		if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
		{
			(*P_usMsgRdPtr) = 0;
		}
		return C_Error;	///*���������ԣ�ֱ��Ӧ�����*///
	}
	P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
	(*P_usMsgRdPtr)++;	///*��������Ϣָ��*///
	if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
	{
		(*P_usMsgRdPtr) = 0;
	}
	V_Msg->PowerFlag = InF_ReadPowerState();
	
	return  C_OK;
}

///**************************************************************///
///*Function��void InF_WriteMessege(Str_Msg_Parameter *V_Msg)	*///
///*Description��������Ϣģ����Ҫ���͵���Ϣ����������Ϣ����		*///
///*Input��V_Msg������Ϣ�ṹ���ַ								*///
///*Output�����ṹ������Ϣ����д����Ϣ����						*///
///*Calls��														*///
///*Called By��������Ҫ������Ϣ��ģ��							*///
///*Influence����Ϣ���м���ָ��									*///
///*Tips��ͨ�ź���ʾ���ڵ�һ����Ϣ���У������ڵڶ�����Ϣ����	*///
///*Others������ģ�鷢����Ϣ��ʱ����Ҫ֪������Ϣ�����Ǹ�����	*///
///*Author:zhiyong.gu											*///
///**************************************************************///
void InF_WriteMessege(Str_Msg_Parameter *V_Msg)
{
	ushort16 *P_usMsgRdPtr;
	ushort16 *P_usMsgWRPtr;
	uchar8 *P_ucMsgBuffer;
	ushort16 V_usBufferMaxLen,V_usWriteLen,V_usLen,i;
	uchar8 V_ucBuffer[C_MsgForDispatchLen+6];
	uchar8 V_ucCS = 0,j;
///*****************д�������ȴ���buffer��󳤶�ֱ�ӷ���*********************///
	if(V_Msg->Length > C_MsgForDispatchLen)
	{
		return;
	}
///*****************��ֵ�̶�����*****************///
	V_ucBuffer[0] = C_MsgFrame_Start;
	V_ucBuffer[1] = V_Msg->Length + 4;
	V_ucBuffer[2] = V_Msg->SourceAddr;
	V_ucBuffer[3] = V_Msg->DerictAddr;
	PF_CopyDataBytes(V_Msg->Parameter,&V_ucBuffer[4],V_Msg->Length);
	for(j=0;j<V_ucBuffer[1];j++)
	{
		V_ucCS += V_ucBuffer[j];
	}
	V_ucBuffer[V_Msg->Length+4] = V_ucCS;
	V_ucBuffer[V_Msg->Length+5] = C_MsgFrame_End;
///*****************���ݲ�ͬ����ȡ��ͬ��ַ***************///
	//if((V_Msg->DerictAddr == C_Msg_Communication)||(V_Msg->DerictAddr == C_Msg_Display)) ///*ͨ����ʾ���ö���1���������ö���2*///
	if( C_First_Squeue == SF_JudgeMessageQueue(V_Msg->DerictAddr) )	///*�ж��Ƿ�Ϊ��1������Ϣ*///
	{
		P_usMsgRdPtr = &Str_MsgQueue1.SV_Msg1RdPtr;
		P_usMsgWRPtr = &Str_MsgQueue1.SV_Msg1WrPtr;
		P_ucMsgBuffer = Str_MsgQueue1.SV_Msg1Buffer;
		V_usBufferMaxLen = C_MsgQueue1Len;
	}
	else
	{
		P_usMsgRdPtr = &Str_MsgQueue2.SV_Msg2RdPtr;
		P_usMsgWRPtr = &Str_MsgQueue2.SV_Msg2WrPtr;
		P_ucMsgBuffer = Str_MsgQueue2.SV_Msg2Buffer;
		V_usBufferMaxLen = C_MsgQueue2Len;
	}
///****************�����ж�дָ��Ϸ����ж�******************///
	if((*P_usMsgRdPtr >= V_usBufferMaxLen)||(*P_usMsgWRPtr >= V_usBufferMaxLen))
	{
		*P_usMsgRdPtr = 0;
		*P_usMsgWRPtr = 0;
	}
///********************��Ϣд�����**************************///
	V_usWriteLen = SF_CalMessagePtr(*P_usMsgRdPtr,*P_usMsgWRPtr,(V_ucBuffer[1]+2),V_usBufferMaxLen);
	if(V_usWriteLen == C_NoEnoughMsgSpace)	///*��Ϣ��������򽫸���Ϣ����*///
	{
		return;
	}
	///**********�ж��Ƿ���Ҫѭ����ͷ��ʼд************///
	if(V_usWriteLen == (V_ucBuffer[1]+2))
	{
		V_usLen = 0;
	}
	else
	{
		V_usLen = (V_ucBuffer[1]+2) - V_usWriteLen;
	}
	j=0;
	for(i=V_usWriteLen;i>0;i--)
	{
		P_ucMsgBuffer[*P_usMsgWRPtr] = V_ucBuffer[j];
		*P_usMsgWRPtr += 1;
		if((*P_usMsgWRPtr) >= V_usBufferMaxLen)
		{
			(*P_usMsgWRPtr) = 0;
		}
		j++;
	}
	if(V_usLen != 0)		///*��Ҫѭ��д*///
	{
		*P_usMsgWRPtr = 0;
		for(i=V_usLen;i>0;i--)
		{
			P_ucMsgBuffer[*P_usMsgWRPtr] = V_ucBuffer[j];
			*P_usMsgWRPtr += 1;
			if((*P_usMsgWRPtr) >= V_usBufferMaxLen)
			{
				(*P_usMsgWRPtr) = 0;
			}
			j++;
		}
	}
}





