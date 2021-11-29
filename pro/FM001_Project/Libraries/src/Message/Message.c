
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     Message.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   定时器处理文件
///*Function List: 
///*****************************************************************************************///
///*History1:      第1次修改
///*内容1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*内容2. Date:
///*   	   Author:
///*       Modification:
		///*********************************************************************************///
///*History2:      第2次修改
///*内容1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*内容2. Date:
///*   	   Author:
///*       Modification:
///*****************************************************************************************///


#include "Public.h"
#include "Message.h"
#include "Dispatch.h"


static	uchar8	SV_MsgDerictData[C_MsgForDispatchLen];	///*读消息时将消息数据暂存，供目的消息模块用*///

///*队列1的消息：500ms通信、显示，队列缓冲区长度暂定为200字节（C_MsgQueue1Len）*///
typedef struct
{
	ushort16	SV_Msg1RdPtr;	///*读消息指针*///
	ushort16	SV_Msg1WrPtr;	///*写消息指针*///
	uchar8		SV_Msg1Buffer[C_MsgQueue1Len];	///*消息buffer*///
}Str_MsgQueue1_Type;

///*队列2的消息：其余所有的消息，队列缓冲区长度暂定为2048字节（C_ MsgQueue2Len）*///
typedef struct
{
	ushort16	SV_Msg2RdPtr;	///*读消息指针*///
	ushort16	SV_Msg2WrPtr;	///*写消息指针*///
	uchar8		SV_Msg2Buffer[C_MsgQueue2Len];	///*消息buffer*///
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
	C_Msg_Communication,			///*通信消息*///
	C_Msg_Display,					///*显示消息*///
	C_Msg_Dispatch					///*调度消息:读RTC*///
};
#define C_Table_FirstMsgQueue_Len  (sizeof(Table_FirstMsgQueue))

///***********************************************************************************///
///*Function：判断消息是否为第1队列消息*///
///*Description：*///
///*Input:Table_FirstMsgQueue:第1消息队列表格:通信/显示/读RTC*///
///*      C_Table_FirstMsgQueue_Len:表格长度(用于循环判断次数)*///
///*Output：无*///
///*return:第1队列消息为C_First_Squeue,第2队列消息为C_Second_Squeue*///
///*Influence：*///
///*Tips：*///
///*Others：*///
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
///*Function：初始化消息队列*///
///*Description：*///
///*Input：无*///
///*Output：无*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
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
///*Function：SF_CalMessagePtr(ushort16 V_usCurrentRdPtr,ushort16 V_usCurrentPtr,ushort16 V_ucAddLen,ushort16 V_usMaxLen)*///
///*Description：判断从写指针开始还能写的字节数*///
///*Input：V_usCurrentRdPtr当前读指针，V_usCurrentPtr当前写指针，V_ucAddLen消息长度，V_usMaxLen为最大队列长度*///
///*Output：输出队列中剩余可以写的字节数，C_NoEnoughMsgSpace表示消息队列已满*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///*Author:zhiyong.gu*///
///***********************************************************************************///
ushort16 SF_CalMessagePtr(ushort16 V_usCurrentRdPtr,ushort16 V_usCurrentPtr,ushort16 V_ucAddLen,ushort16 V_usMaxLen)
{
	ushort16 V_usLen;
	
	V_usLen = V_ucAddLen;
	if(V_usCurrentRdPtr > V_usCurrentPtr)
	{
		if((V_usCurrentPtr + V_ucAddLen) > V_usCurrentRdPtr)	///*环形队列中不足以写一条消息，这种情况下直接返回0*///
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
///*Function：void InF_ReadMessegeDerictAddr(Str_Msg_Parameter *V_Msg,uchar8 V_ucMessageSqueueNum)	*///
///*Description：将消息队列中信息参数结构体读出														*///
///*Input：V_Msg参数结构体指向地址																	*///
//*			V_ucMessageSqueueNum消息队列号，C_First_Squeue表示第一个消息队列						*///
///*			C_Second_Squeue表示第二个消息队列													*///
///*Output：*V_Msg为从消息队列中读出的消息															*///
///*return:C_OK表示有消息取出，C_Error表示没有消息取出，用于掉电进入低功耗消息队列的处理			*///
///*Calls：																							*///
///*Called By：主调度读取消息调用																	*///
///*Influence：																						*///
///*Tips：																							*///
///*Others：																						*///
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
	
//	for(V_ucMsgLen=0;V_ucMsgLen<C_MsgForDispatchLen;V_ucMsgLen++)	///*首先存放消息缓冲区清零*///
//	{
//		SV_MsgDerictData[V_ucMsgLen] = 0;
//	}
	
	if(V_ucMessageSqueueNum == C_First_Squeue) ///*通信和显示采用队列1，其他采用队列2*///
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
///****************队列中读写指针合法性判断******************///
	if((*P_usMsgRdPtr >= V_usBufferMaxLen)||(*P_usMsgWRPtr >= V_usBufferMaxLen))
	{
		*P_usMsgRdPtr = 0;
		*P_usMsgWRPtr = 0;
	}
	
	V_Msg->DerictAddr = C_NULL;
	V_Msg->Parameter = SV_MsgDerictData;
	
	if(*P_usMsgRdPtr == *P_usMsgWRPtr)	///*消息队列中为空*///
	{
		return C_Error;
	}
	if(*P_usMsgRdPtr != *P_usMsgWRPtr)	///*消息队列中不为空*///
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
///******************下面判断CS是否正确*************************///
///******************下面读取消息内容，并读后请消息队列中数据*******************************///
	V_ucCS += P_ucMsgBuffer[*P_usMsgRdPtr];
	P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
	(*P_usMsgRdPtr)++;
	if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
	{
		(*P_usMsgRdPtr) = 0;
	}
	
	V_ucMsgLen = P_ucMsgBuffer[*P_usMsgRdPtr];	///*取这个消息的长度*///
	V_ucCS += P_ucMsgBuffer[*P_usMsgRdPtr];
	P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
	if(V_ucMsgLen <= 4)	///*长度不对直接退出:源地址、目的地址、CS及结束符*///
	{
		return C_Error;
	}
	V_ucMsgLen -= 4;
	V_Msg->Length = V_ucMsgLen;		///*消息长度*///
	(*P_usMsgRdPtr)++;
	if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
	{
		(*P_usMsgRdPtr) = 0;
	}
	if(V_Msg->Length > C_MsgForDispatchLen)	///*长度大于消息存放buffer最大长度返回错误*///
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
		(*P_usMsgRdPtr)++;	///*调整读消息指针*///
		if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
		{
			(*P_usMsgRdPtr) = 0;
		}
		return C_Error;	///*CS不对，直接应答错误*///
	}
	P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
	(*P_usMsgRdPtr)++;	///*调整读消息指针*///
	if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
	{
		(*P_usMsgRdPtr) = 0;
	}
	
	if(P_ucMsgBuffer[*P_usMsgRdPtr] != C_MsgFrameEnd)
	{
		P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
		(*P_usMsgRdPtr)++;	///*调整读消息指针*///
		if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
		{
			(*P_usMsgRdPtr) = 0;
		}
		return C_Error;	///*结束符不对，直接应答错误*///
	}
	P_ucMsgBuffer[*P_usMsgRdPtr] = 0;
	(*P_usMsgRdPtr)++;	///*调整读消息指针*///
	if((*P_usMsgRdPtr) >= V_usBufferMaxLen)
	{
		(*P_usMsgRdPtr) = 0;
	}
	V_Msg->PowerFlag = InF_ReadPowerState();
	
	return  C_OK;
}

///**************************************************************///
///*Function：void InF_WriteMessege(Str_Msg_Parameter *V_Msg)	*///
///*Description：将各消息模块需要发送的信息参数加入消息队列		*///
///*Input：V_Msg发送消息结构体地址								*///
///*Output：将结构体中消息内容写入消息队列						*///
///*Calls：														*///
///*Called By：各个需要发送消息的模块							*///
///*Influence：消息队列及其指针									*///
///*Tips：通信和显示处于第一个消息队列，其他在第二个消息队列	*///
///*Others：各个模块发送消息的时候不需要知道该消息处于那个队列	*///
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
///*****************写参数长度大于buffer最大长度直接返回*********************///
	if(V_Msg->Length > C_MsgForDispatchLen)
	{
		return;
	}
///*****************赋值固定参数*****************///
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
///*****************根据不同队列取不同地址***************///
	//if((V_Msg->DerictAddr == C_Msg_Communication)||(V_Msg->DerictAddr == C_Msg_Display)) ///*通信显示采用队列1，其他采用队列2*///
	if( C_First_Squeue == SF_JudgeMessageQueue(V_Msg->DerictAddr) )	///*判断是否为第1队列消息*///
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
///****************队列中读写指针合法性判断******************///
	if((*P_usMsgRdPtr >= V_usBufferMaxLen)||(*P_usMsgWRPtr >= V_usBufferMaxLen))
	{
		*P_usMsgRdPtr = 0;
		*P_usMsgWRPtr = 0;
	}
///********************消息写入队列**************************///
	V_usWriteLen = SF_CalMessagePtr(*P_usMsgRdPtr,*P_usMsgWRPtr,(V_ucBuffer[1]+2),V_usBufferMaxLen);
	if(V_usWriteLen == C_NoEnoughMsgSpace)	///*消息队列溢出则将该消息丢掉*///
	{
		return;
	}
	///**********判断是否需要循环从头开始写************///
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
	if(V_usLen != 0)		///*需要循环写*///
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





