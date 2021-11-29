
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     Message.h
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__Message_H
#define	__Message_H

#include "Public.h"


///*通信协议结构:0x68 数据长度 源消息号 目的消息号 数据域 CS 0x16；*///
typedef struct
{
	uchar8	Start;	///*帧头：0x68*///
	uchar8	Len;	///*帧长：Len之后、CS之前所有数据长度*///
	uchar8	SourceAddr;	///*源消息号*///
	uchar8	DerictAddr;	///*目的消息号*///
	uchar8	*Parameter;	///*数据域，长度不定*///
	uchar8	CS;	///*校验和：从L到CS前所有数据累加和对256取模*///
	uchar8	End;	///*结束符：0x16*///
}Str_Msg_DataFrame_Type;

#define C_MsgFrame_Start	0x68
#define C_MsgFrame_End		0x16
#define C_NoEnoughMsgSpace	0xFF	///*消息队列空间不足*///

#define	C_InitMsg			0		///*上电初始化为0*///

///********macro for 消息********///
///********macro 消息队列********///
#define	C_MsgForDispatchLen			50		///*读消息时将消息数据暂存的缓冲区长度，供各个模块用*///
#define	C_MsgQueue1Len				1024		///*消息队1列长度*///
#define	C_MsgQueue2Len				2048	///*消息队2列长度*///
#define	C_MsgFrameStart				0x68	///*消息参数帧起始符*///
#define	C_MsgFrameEnd				0x16	///*消息参数帧结束符*///




#endif

