
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     Message.h
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__Message_H
#define	__Message_H

#include "Public.h"


///*ͨ��Э��ṹ:0x68 ���ݳ��� Դ��Ϣ�� Ŀ����Ϣ�� ������ CS 0x16��*///
typedef struct
{
	uchar8	Start;	///*֡ͷ��0x68*///
	uchar8	Len;	///*֡����Len֮��CS֮ǰ�������ݳ���*///
	uchar8	SourceAddr;	///*Դ��Ϣ��*///
	uchar8	DerictAddr;	///*Ŀ����Ϣ��*///
	uchar8	*Parameter;	///*�����򣬳��Ȳ���*///
	uchar8	CS;	///*У��ͣ���L��CSǰ���������ۼӺͶ�256ȡģ*///
	uchar8	End;	///*��������0x16*///
}Str_Msg_DataFrame_Type;

#define C_MsgFrame_Start	0x68
#define C_MsgFrame_End		0x16
#define C_NoEnoughMsgSpace	0xFF	///*��Ϣ���пռ䲻��*///

#define	C_InitMsg			0		///*�ϵ��ʼ��Ϊ0*///

///********macro for ��Ϣ********///
///********macro ��Ϣ����********///
#define	C_MsgForDispatchLen			50		///*����Ϣʱ����Ϣ�����ݴ�Ļ��������ȣ�������ģ����*///
#define	C_MsgQueue1Len				1024		///*��Ϣ��1�г���*///
#define	C_MsgQueue2Len				2048	///*��Ϣ��2�г���*///
#define	C_MsgFrameStart				0x68	///*��Ϣ����֡��ʼ��*///
#define	C_MsgFrameEnd				0x16	///*��Ϣ����֡������*///




#endif

