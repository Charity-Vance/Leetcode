/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Comm_698.h
Version:       V1
Author:        jiangzs
Date:          2016-8-21
Description:   通信处理、解析文件
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:   20210928
   	   Author: lzy
       Modification:单三相统一平台
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
#ifndef	__Comm_698_H
#define	__Comm_698_H

#include	"Public.h"
#include	"communication.h"
#include	"DI_698.h"
#include	"Public_Code.h"

typedef struct
{
	uchar8	Len;			/* 安全数据长度*/
	uchar8	*Data;			/* 安全数据缓存*/
}SecurityData_Type;

typedef struct
{
	uchar8	Len;			/* 安全MAC 数据长度*/
	uchar8	*MAC;			/* 安全数据缓存*/
}SecurityMAC_Type;

typedef struct
{
	uchar8	SecurityAPDUType;			/* 安全类型*/
	SecurityData_Type	*SecurityData;	/* 安全数据缓存*/
	uchar8	SecurityMACType;			/*安全类型验证类型*/
	SecurityMAC_Type	*SecurityMAC;	/* 验证数据缓存*/
}Security_APDU_Type;

typedef struct
{
	uchar8	PIID;						/* PIID*/
	ulong32	*OAD;						/* OAD*/
}GetReqNormal_Type;

typedef struct
{
	uchar8	PIID;						/* PIID*/
	uchar8	OADNum;						/* OAD个数*/
	ulong32	*OAD;						/* OAD缓存首地址*/
}GetReqNormalList_Type;



typedef struct
{
	ulong32	OAD;						/* 对象标识*/
	uchar8	*Data;						/* 对象数值*/
}SelectType1_Type;

typedef struct
{
	ulong32	OAD;						/* 对象标识*/
	uchar8	*StartData;					/* 起始值*/
	uchar8	*EndData;					/* 结束值*/
	uchar8	*InternalData;				/* 间隔值*/
}SelectType2_Type;

typedef struct
{
	uchar8				SelectNum;		/* 选择对象个数*/
	SelectType2_Type	*SelectType2;	/* 选择方法首地址*/
}SelectType3_Type;

typedef struct
{
	uchar8	RecordNum;					/*上第n条记录*/
}SelectType9_Type;

typedef struct
{
	uchar8	SelectType;					/* 选择方法*/
	uchar8	*RSDData;					/* RSD选择对应方法数据*/
}RSD_Type;

typedef struct
{
	ulong32	*OAD;						/* 记录对象标识*/
	uchar8	RelationOADNum;				/* 关联对象属性个数*/
	ulong32	*RelationOAD;				/* 关联对象属性标识首地址*/
}RelationOAD_Type;

typedef struct
{
	ulong32				*OAD;			/* 记录对象标识*/
	RelationOAD_Type	*RelatOAD;		/* 关联属性列表首地址*/
}ROAD_Type;

typedef struct
{
	uchar8	CSDType;					/* CSD类型*/
	uchar8	*CSDData;					/* CSD缓存首地址*/
}CSD_Type;

typedef struct
{
	uchar8		CSDNum;					/* CSD个数*/
	CSD_Type	*CSD;					/* CSD缓存首地址*/
}RCSD_Type;


typedef struct
{
	ulong32		OAD;					/* OAD*/
	RSD_Type	RSD;					/* RSD*/
	RCSD_Type	RCSD;					/* RCSD*/
}GetRecord_Type;

typedef struct
{
	uchar8			PIID;				/* PIID*/
	GetRecord_Type	*GetRecord;			/* OAD*/
}GetReqRecord_Type;

typedef struct
{
	uchar8			PIID;				/* PIID*/
	uchar8			GetRecordNum;		/* GetRecord个数*/
	GetRecord_Type	*GetRecord;			/* OAD缓存首地址*/
}GetReqRecordList_Type;

typedef struct
{
	uchar8		PIID;					/* PIID*/
	ushort16	GetRecordNum;			/* 已接收的正确帧序号*/
}GetReqNext_Type;

typedef struct
{
	uchar8	GetAPDUType;				/* 读取服务类型*/
	uchar8	*GetAPDUTData;				/* 读取服务数据*/
}Get_APDU_Type;

typedef struct
{
	uchar8	SetAPDUType;				/* 读取服务类型*/
	uchar8	*SetAPDUTData;				/* 读取服务数据*/
}Set_APDU_Type;


typedef struct
{
	ulong32	OAD;						/* OAD*/
	uchar8	*Data;						/* Data*/
}SetData_Type;

typedef struct
{
	uchar8			PIID;				/* PIID*/
	SetData_Type	*SetData;			/*设置数据*/
}SetReqNormal_Type;

typedef struct
{
	uchar8			PIID;				/* PIID*/
	uchar8			OADNum;				/* OAD个数*/
	SetData_Type	*SetData;			/* 设置数据缓存首地址*/
}SetReqNormalList_Type;

typedef struct
{
	ulong32	SetOAD;						/* 设置数据OAD*/
	uchar8	*Data;						/* Data*/
	ulong32	GetOAD;						/* 读取数据对象属性*/
	uchar8	DelayTime;					/* 延时读取时间*/
}SetGetData_Type;

typedef struct
{
	uchar8			PIID;				/* PIID*/
	uchar8			OADNum;				/* OAD个数*/
	SetGetData_Type	*SetGetData;		/* 设置数据缓存首地址*/
}SetGetReqNormalList_Type;



#define	C_ClientStart_DIR					0x00				/*客户端发起*/
#define	C_ServerStart_DIR					0x80				/*服务器发起*/
#define	C_ClientStart_PRM					0x40				/*客户端发起*/
#define	C_Scramble_Flag						0x08				/*扰码标志位，1表示有扰码，0表示没有扰码*/
                                    		            		
#define	C_ProtocolConformance_Len			8					/*协议一致性长度*/
#define	C_FunctionConformance_Len			16					/*功能一致性长度*/
#define	C_TxRxMaxLen_Len					2					/*APDU长度*/
#define	C_ConectStruct_Len					48					/*安全连接类型结构体长度*/
                                                        		
                                                        		
#define	C_ClientTxMaxLen					512					/*客户机发送帧最大尺寸512*/
/********* 698数据暂存结构体************/           			
ConectRequest_Type	Com_Conect;									/*通信应用连接结构体*/
uchar8	GV_ComConect_Timer;										/*S*/
uchar8	GV_GEsam_500Timer;										/*ESAM 500ms调度用*/
uchar8	GV_GEsam_1min;			    							/*1分钟定时器*/
#define	C_NullSecyrityConnect				0x00				/*公共连接*/
#define	C_PasswordSecurityConnect			0x01				/*一般密码*/
#define	C_SymmetrySecurityConnect			0x02				/*对称密钥*/
#define	C_SignatureSecurityConnect			0x03				/*数字签名*/

const uchar8 Str_ConnRightType[4] = {0x08, 0x04, 0x02, 0x01};	/*应用连接对应的权限,明文可以用任何权限操作*/
const uchar8 Str_ESafeTransType[4] = {0x00, 0x04, 0x04, 0x00};	/*明文安全传输对应的权限*/
const uchar8 Str_CSafeTransType[4] = {0x01, 0x00, 0x00, 0x02};	/*密文安全传输对应的权限*/


#define C_AddrTpyeBits						0xC0				/*地址类型对应位*/
#define C_LogicAddrBits						0x30				/*逻辑地址类型对应位*/
#define C_AddrLenBits						0x0F				/*SA地址长度对应位*/
                        					            		
#define C_AddrTypePtoP						0x00				/*单播地址*/
#define C_AddrTypePtoX						0x40				/*通配地址*/
#define C_AddrTypePtoM						0x80				/*组播地址*/
#define C_AddrTypePtoAll					0xC0				/*广播地址*/

#define C_SECURITY_Request					0x10				/*安全传输*/
#define C_CONNECT_Request					0x02				/*应用连接*/
#define C_RELEASE_Request					0x03				/*断开应用连接*/
#define C_GET_Request						0x05				/*读数据请求*/
#define C_SET_Request						0x06				/*写数据请求*/
//#define C_ACTION_Request					0x07				/*操作请求*/
#define C_REPORT_Response					0x08				/*上报应答*/
#define C_PROXY_Request						0x09				/*代理请求*/
                                			            		
#define C_Default_Request					0x6E				/*异常响应服务*/


#define C_SETNormal_Request					0x01						/*设置一个对象属性*/
#define C_SETNormalList_Request				0x02						/*设置多个对象属性*/
#define C_SETGETNormalList_Request			0x03						/*设置后读取读取多个对象属性*/
                                    		
#define C_ACTIONNormal_Request				C_SETNormal_Request			/*操作一个对象属性*/
#define C_ACTIONNormalList_Request			C_SETNormalList_Request		/*操作多个对象属性*/
#define C_ACTIONGETList_Request				C_SETGETNormalList_Request	/*操作后读取读取多个对象属性*/
         

/*2020标准主动上报2005*/
#define C_07EventReportTypeAttribute		11							/*07类事件，上报方式属性*/
#define C_24EventReportTypeAttribute		15							/*24类事件，上报方式属性*/
#define C_ReportAddListClear				0x01						/*新增事件列表清零*/
#define C_FollowStatusClear					0x02						/*跟随上报状态字清零*/
#define C_ListEventNo						0xFF						/*整个列表清掉时，发0xFF*/
#define C_ExceptPowerFailListEventNo		0xFE						/*整个列表清掉时，除了掉电和新增事件。发0xFE*/

#define C_REPORTNormalList_Request			0x01						/*上报对象属性*/
#define C_REPORTRecordList_Request			0x02						/*上报事件类对象属性*/
#define C_REPORTData_Request				0x03						/*上报透明数据*/
#define C_REPORTListMaxLen					C_ModuleMaxLen-47			/*47=4（FE）+21(安全及组帧)+19(RN+MAX)+3(校验+16)*/
#define C_CodeOADlen						0x05						/*OAD编码长度，5个字节*/
#define C_ReportOTimer						10							/*主动上报延时确认时间，1S一次，目前是10s*/
#define C_ReportOTimer1s					1							/*掉电发生主动上报延时确认时间，1S。*/
#define	C_SPI_500ms							25000						/*接收超时：50ms,2us基准*/
#define C_ReportMaxDealNum					2							/*500ms判一次主动上报是否还在发送，最多支持2.5S*/ 

#define C_ESAMF1000300  					0xF1000300					/*ESAM数据读取，方法操作*/

#define	C_ESAMAction_NO1					0x01						/*ESAM复位*/
#define	C_ESAMAction_NO2					0x02						/*ESAM执行*/
#define	C_ESAMAction_NO3					0x03						/*ESAM操作*/
#define	C_ESAMAction_NO4					0x04						/*ESAM数据更新*/
#define	C_ESAMAction_NO5					0x05						/*协商失效*/

#define	C_ESAMAction_NO6					0x06						/*ESAM钱包操作*/
#define	C_ESAMAction_NO7					0x07						/*ESAM密钥更新*/
#define	C_ESAMAction_NOA					0x0A						/*ESAM钱包初始化*/
#define	C_ESAMAction_NOB					0x0B						/*红外认证请求*/
#define	C_ESAMAction_NOC					0x0C						/*红外认证*/
#define	C_ESAMAction_NO9					0x09						/*设置协商时效*/

#define	C_GETNormal_Request_Off				0x03						/*data起始地址*/


#define	C_ForbidenRW						0x03						/*拒绝读写*/
#define	C_FrameNoErr						14							/*帧序号错*/

#define	C_GetResponseOK						0x01						/*读数据正确应答*/
#define	C_GetResponseERR					0x00						/*读数据异常应答*/
#define	C_LastFrameErr						0x00						/*不是末帧标志*/
#define	C_LastFrameOK						0x01						/*末帧标志*/
#define	C_TimeTagOn							0x68						/*有时间标签标识*/
#define C_TimeTagInvalid					0x20						/*时间标签无效*/
#define	C_ServiceType_Err					0x89						/*服务类型不匹配*/

#define C_MaxReadListNum					0x14						/*ReadList命令最大支持OAD个数*/

#define	C_APDUDecode_Fault					0x01						/*APDU无法解析*/
#define	C_ServiceType_Fault					0x02						/*服务不支持*/
#define	C_Service_OtherFault				0xFF						/*其他错误*/

#define	C_Read_Flag3000						0x01						/*3000读取*/
#define	C_Read_FlagNor						0x00						/*正常读取*/
#define C_EnCodeMaxLen						100							/*帧头帧尾+时间标签+跟随上报+RN+密文最大长度预留*/

typedef struct
{
	ulong32		WtOI;							/*写OI*/
	uchar8		Wt_Result;						/*写操作结果*/
	ushort16	DataLen;						/*写操作数据长度*/
	uchar8		*Wt_Data;						/*写数据数据首地址*/
}WtOI_Rt_T;


typedef struct
{
	uchar8		PIID;							/*PIID*/
	uchar8		RWOI_Num;						/*读写的OI个数*/
	RdOI_Para_T	Rd_OI[C_MaxReadListNum];		
	WtOI_Rt_T	Wt_OI[C_MaxReadListNum];		
	ulong32		W_R_DelayTime;					/*写数据后延时读取时间，如果有多个写操作，读取延时取最大延时*/
	uchar8		ServiceFlag_Second;				/*第二级服务类型：读一个对象属性、读取多个对象属性、读取一个记录对象、读取多个记录对象、读取后续数据*/
	uchar8		ServiceFlag_First;				/*第一级服务类型：读一个对象属性、读取多个对象属性、读取一个记录对象、读取多个记录对象、读取后续数据*/
	uchar8		Current_FrameNO;				/*当前帧序号*/
	uchar8		ChannelNo;						/*通道号*/
	uchar8		Next_OINO;						/*下一个读取的OI序号*/
	uchar8		ResponedNum;					/*已经应答的OAD个数*/
	uchar8		HaveEncodeNum;					/*已经应答的OAD个数*/
	uchar8		ResponedRelationNum;			/*已经应答的关联对象属性个数*/
	uchar8		TimeTag[9+3];					/*时间标签，第一个字节为0x68表示是否有时间标签，否则为无时间标签*/
	uchar8		EndFrame;						/*应用层末帧标志*/
	ushort16	FrameNUM;						/*应用层分帧序号*/
	uchar8		LastServiceFlag_Second;			/*后续帧保留的上一帧服务类型*/
	uchar8		CurrentOADEnd;					/*当前oad后续帧标志*/			
	uchar8		firstRNSICBit;					/*首帧权限所占bit位*/
	uchar8		lastRNSICBit;					/*后续帧权限所占bit位*/
}Str_Comm_698_RW;
static Str_Comm_698_RW  SV_RS485_1_698RWParm @".DataProcessADDR";
static Str_Comm_698_RW  SV_RS485_2_698RWParm @".DataProcessADDR";
static Str_Comm_698_RW  SV_IR_698RWParm @".DataProcessADDR";
static Str_Comm_698_RW  SV_Module_698RWParm @".DataProcessADDR";

/*****************************698.45相关***********************************************/
#define	C_Len								0x80
#define	C_Num								0x40
#define	C_Type								0x20

typedef  struct
{
	uchar8 	DataType;								/*数据类型*/
	uchar8 	DataLen;								/*下级类型表格号*/
}Str_DataTpye_Type;

#define	C_SPECIAL1							0xF1	/*特殊处理方法1*/
#define	C_SPECIAL2							0xF2	/*特殊处理方法2*/
#define	C_SPECIAL3							0xF3	/*特殊处理方法3*/
#define	C_SPECIAL4							0xF4	/*特殊处理方法4*/
#define	C_SPECIAL5							0xF5	/*特殊处理方法5*/
#define	C_SPECIAL6							0xF6	/*特殊处理方法6*/
#define	C_SPECIAL7							0xF7	/*特殊处理方法7*/
const Str_DataTpye_Type	Str_DataTpye[] =
{//数据类型，				后续编码特点
	{C_array,					C_Len|C_Num|C_Type},	/*[1]*/
	{C_structure,				C_NULL},				/*[2]*/
	{C_bool,					1},						/*[3]*/
	{C_bit_string,				C_Len},					/*[4]*/
	{C_double_long,				4},						/*[5]*/
	{C_double_long_unsigned,	4},						/*[6]*/
	{C_octet_string,			C_Len},					/*[9]*/
	{C_visible_string,			C_Len},					/*[10]*/
	{C_UTF8_string,				C_Len},					/*[12]*/
	{C_integer,					1},						/*[15]*/
	{C_long,					2},						/*[16]*/
	{C_unsigned,				1},						/*[17]*/
	{C_long_unsigned,			1},						/*[18]*/
	{C_long64,					8},						/*[20]*/
	{C_long64_unsigned,			8},						/*[21]*/
	{C_enum,					1},						/*[22]*/
	{C_float32,					4},						/*[23]*/
	{C_float64,					8},						/*[24]*/
	{C_date_time,				10},					/*[25]*/
	{C_date,					5},						/*[26]*/
	{C_time,					3},						/*[27]*/
	{C_OI,						2},						/*[80]*/
	{C_OAD,						4},						/*[81]*/
	{C_ROAD,					C_SPECIAL1},			/*[82]*/
	{C_OMD,						4},						/*[83]*/
	{C_TI,						3},						/*[84]*/
//	{C_TSA,						C_Len},					/*[85]*/
	{C_MAC,						C_Len},					/*[86]*/
	{C_RN,						C_Len},					/*[87]*/
	{C_Region,					C_SPECIAL2},			/*[88]*/
	{C_Scaler_Unit,				2},						/*[89]*/
	{C_RSD,						C_SPECIAL3},			/*[90]*/
	{C_CSD,						C_SPECIAL4},			/*[91]*/
	{C_SID,						C_SPECIAL5},			/*[93]*/
	{C_SID_MAC,					C_SPECIAL6},			/*[94]*/
	{C_COMDCB,					C_SPECIAL7},			/*[95]*/
	{C_RCSD,					C_Num|C_Type},			/*[96]*/
};
#define C_DataTypeTable1_Len			23

			
const uchar8 DataTypeTable1[C_DataTypeTable1_Len][2] = 
{
	C_bool,						CL_bool					,						/*[3]*/
	C_double_long,				CL_double_long		    ,						/*[5]*/
	C_double_long_unsigned,		CL_double_long_unsigned ,						/*[6]*/
	C_integer,					CL_integer				,						/*[15]*/
	C_long,						CL_long					,						/*[16]*/
	C_unsigned,					CL_unsigned				,						/*[17]*/
	C_long_unsigned,			CL_long_unsigned		,						/*[18]*/
	C_long64	,				CL_long64			    ,						/*[20]*/
	C_long64_unsigned,			CL_long64_unsigned		,						/*[21]*/
	C_enum,						CL_enum				    ,						/*[22]*/
	C_float32,					CL_float32			    ,						/*[23]*/
	C_float64,					CL_float64				,						/*[24]*/
	C_date_time,				CL_date_time			,						/*[25]*/
	C_date,						CL_date				    ,						/*[26]*/
	C_time,						CL_time				    ,						/*[27]*/
	C_date_time_s,				CL_date_time_s		    ,						/*[28]*/
	C_OI,						CL_OI					,						/*[80]*/
	C_OAD,						CL_OAD				    ,						/*[81]*/
	C_OMD,						CL_OMD				    ,						/*[83]*/
	C_TI,						CL_TI				    ,						/*[84]*/
  	C_Scaler_Unit	,			CL_Scaler_Unit	        ,						/*[89]*/
	C_CSD,						CL_CSD				    ,						/*[91]*/
	C_COMDCB,					CL_COMDCB               ,						/*[95]*/
	//C_NULL,					0,						/*[95]*/
};                                          			 
const uchar8 DataTypeTable2[17][2]=         			 
{                                           			 
	C_array,					0,						/*[1]*/
	C_structure,				0,						/*[2]*/
	C_bit_string,				0,						/*[4]*/
	C_octet_string,				0,						/*[9]*/
	C_visible_string,			0,						/*[10]*/
	C_UTF8_string	,			0,						/*[12]*/
	C_ROAD,						0,						/*[82]*/
	C_TSA,						0,						/*[85]*/
	C_MAC,						0,						/*[86]*/
  	C_RN,			     		0,						/*[87]*/
  	C_Region,					0,						/*[88]*/
	C_RSD,						0,						/*[90]*/
	C_CSD,						0,						/*[91]*/
	C_SID,						0,						/*[93]*/
	C_SID_MAC,              	0,						/*[94]*/
	C_COMDCB,              		0,						/*[95]*/
	C_RCSD,                    	0,						/*[96]*/
};                                                       
/*类宏定义*/
#define	C_Energy_Class						1 				/* 电能量 */
#define	C_Demand_Class						2 				/* 需量 */
#define	C_Variable_Class					3 				/* 分相变量 */
#define	C_Power_Class						4 				/* 功率 */
#define	C_DateVariables_Class				6 				/* 数据变量 */
#define	C_Event_Class						7 				/* 事件记录*/
#define	C_Parameter_Class					8 				/* 参数变量 */
#define	C_Freeze_Class						9 				/* 冻结*/
#define	C_Display_Class						17				/* 显示 */
#define	C_DeviceIO_Class					19				/* 设备接口类 */
#define	C_Esam_Class						21				/* ESAM */
#define	C_InputAndOutput_Class				22				/* 电能量 */
#define	C_SplitPhaseEvent_Class				24				/* 分相事件记录 */

#define C_Event_2Attri						2				/*7类的属性2*/
#define C_SplitPhaseEvent_6Attri			6				/*24类的属性6*/
#define C_SplitPhaseEvent_7Attri			7				/*24类的属性7*/
#define C_SplitPhaseEvent_8Attri			8				/*24类的属性8*/
#define C_SplitPhaseEvent_9Attri			9				/*24类的属性9*/

/*下级表格序号宏定义*/
#define	C_Energy_TableNum					1				/* 电能量 */
#define	C_Demand_TableNum					2				/* 最大需量 */
#define	C_Variable_TableNum					3				/* 瞬时量 */
#define	C_Power_TableNum					4				/* 功率 */
#define	C_DateVariables_TableNum			5				/* 电能量 */
#define	C_Event_TableNum					6				/* 事件记录 */
#define	C_Parameter_TableNum				7				/* 参变量 */
#define	C_Freeze_TableNum					8				/* 冻结 */
#define	C_Display_TableNum					9				/* 显示 */
#define	C_Esam_TableNum						10				/* ESAM相关 */
#define	C_InputAndOutput_TableNum			11				/* 输入输出接口 */
#define	C_SplitPhaseEvent_TableNum			12				/* 分相事件记录 */

#define	C_DerictOIBClass					1				/* 直接根据OIB确定645对应数据标识码，二级表格中包含对象所属类 */
#define	C_DerictOIBNoClass					2				/* 直接根据OIB确定645对应数据标识码，二级表格中不包含对象所属类，可以直接由1级表格得到对象所属类*/
#define	C_ThirdTable						3				/* 不能由二级表格得到具体对象，只能对应某个大的对象，具体关联对象表示对应下级表格 */


#define	C_EnergyOIA							0x00			/* 电能量 */
#define	C_DemandOIA							0x10			/* 需量 */
#define	C_VariableOIA20						0x20			/* 瞬时量 */
#define	C_VariableOIA21						0x21			/* 瞬时量 */
#define	C_ParameterOIA40					0x40			/* 参变量 */
#define	C_ParameterOIA41					0x41			/* 参变量 */
#define	C_ParameterOIA43					0x43			/* 参变量 */
#define	C_PasswordrOIA44					0x44			/* 参变量 */
#define	C_PasswordrOIA45					0x45			/* 参变量 */
#define	C_EventRecordOIA					0x30			/* 事件记录 */
#define	C_FrozeRecordOIA					0x50			/* 冻结记录 */
#define	C_ESAMActionOIA						0xF1			/* ESAM操作相关 */
#define	C_ContralOIA						0x80			/* 控制操作相关 */
#define	C_ApplianceInOutOIA					0xF2			/* 输入输出设备相关 */
#define	C_DisplayOIA						0xF3			/* 显示 */
#define C_ReportList						0x33			/*跟随上报事件列表*/
#define C_FileTransferOIA					0xF0			/*文件传输*/
#define C_ExternalOIA						0xFF			/*扩展对象OIA=0xFF*/
                                			
#define	C_Qua4_EnOIB						0x80			/* 第4象限无功电能 */
#define	C_EnergyOIB_Tol						0x00			/* 合相电能判断，排除分相（bit0-bit3）*/
#define	C_CQua4_EnOIB						0x83			/* C相第4象限无功电能 */
//*公共属性 定义
#define	C_Nature1_Name						0x01			/*属性1，逻辑名*/
//*电能属性 定义
#define	C_Nature2_Energy					0x02			/*电能属性2，总及费率电能*/
#define	C_Nature3_EnergyUnit				0x03			/*电能属性3，换算及单位*/
#define	C_Nature4_PreEnergy					0x04			/*电能属性4，总及费率精确电能*/
#define	C_Nature5_PreEnergyUnit				0x05			/*电能属性5，高精度换算及单位*/
#define	C_Nature6_LastNumPulse				0x06			/*电能属性6，脉冲尾数*/
#define	C_Nature7_LastNumPulseUnit			0x07			/*电能属性7，脉冲尾数换算及单位*/
//*需量属性 定义
#define	C_Nature2_Demand					0x02			/*最大需量属性2，总及费率最大需量*/
#define	C_Nature3_DemandUnit				0x03			/*最大需量属性3，换算及单位*/
//*模组版本信息索引 定义
#define	C_Offset0_FactoryInf				0x00			/*模组列表索引0，模组逻辑地址*/
#define	C_Offset1_FactoryInf				0x01			/*模组列表索引1，模组逻辑地址*/
#define	C_Offset7_FactoryInf				0x07			/*模组列表索引7，厂商扩展信息*/


//*常数10000
#define	C_CPulse_Constant10000				10000			/*常数10000*/
                                			            	
#define	C_DisplayNumMax						99				/*显示最大屏数*/
#define	C_DisplayDICal						0x00000001		/*数据标识判断用*/
#define	C_DisplayDI2_offset					4				/*带关联OAD时，第二个OAD的偏移*/
#define	C_OADLen							4				/*OAD长度4字节*/

//写通信规约列表数据偏移
#define C_Meter_CommPro_DataOff00			0x00			/*数据偏移位置00*/
#define C_Meter_CommPro_DataOff02			0x02			/*数据偏移位置02*/
#define C_TypeLen_Len						0x01			/*类型+长度中，长度的长度1字节*/

/*双协议增加*/
#define C_NoNeedSet645ReportMode			0x00			/*不需要设置645主动上报模式字*/
#define C_NeedSet645ReportMode				0x68			/*需要设置645主动上报模式字*/



#define	C_TableIDDisvaliable				0x86			/*下级表格中的标识码无效*/
#define	C_TableIDValiable					0x65			/*下级表格中的标识码有效*/
#define	C_ClassNum24All						0x80			/*下级表格中的标识码无效*/
#define C_MaxDataTypeNum					13				/*类型最大个数*/

typedef  struct
{
	ulong32						V_ucOAD;						/*oad首标识码*/
	ushort16					Unit_Scale[C_MaxDataTypeNum];
	ushort16					DataLen_645[C_MaxDataTypeNum];	/*645数据长度*/
	Str_DI0_DataType_PaTable	*NextClassNO;					/*下级类型表格地址*/
	uchar8						DataType[C_MaxDataTypeNum];		/*数据类型*/
	uchar8						NextClassNum;					/*下级类型个数*/
	uchar8						IDFlay;							/*是否需要下级表格中标识码标志*/
	uchar8						IDNO;							/*事件记录类24，当前记录数对应645次数标志*/
	uchar8						DataLen_698[C_MaxDataTypeNum];	/*改长度只针对数据长度不固定的数据类型*/
	uchar8						MAXRecordTimes;					/*最大记录次数，一般事件记录最大次数为10，当该次数为0表示没有限制*/
    uchar8						TZone_Data[CLFirst_TZone_Data];	/*时区表暂存数据*/
	//uchar8	PointNum;										/*小数点个数，高半字节为698小数点个数，低半字节为645小数点*/
}Str_Type645DI_Class;											/*属性映射表格实现698到645通信规约标识码的映射*/

#define Str_Type645DI_ClassLen	sizeof(Str_Type645DI_Class)		/*结构体长度*/


typedef  struct
{
	uchar8	OIA;												/*OIA*/
	uchar8	SecondType;											/*下级表格类型*/
	uchar8	TableNum;											/*下级表格序号*/
	uchar8	ClassType;											/*所属类号*/
}Str_698SwitchTo645Table_First;									/*属性映射表格实现698到645通信规约标识码的映射*/



typedef  struct
{
	uchar8 OIB;													/*OIB*/
	//uchar8 DI2;												/*DI2*/
	uchar8 MaxNum;												/*bit0-bit6数组最大个数,bit7=0表示无符号，bit7=1表有符号*/
	uchar8 Unit_Energy;											/*单位代号*/
	uchar8 Unit_Demand;											/*单位代号*/
}Str_OIB_DI2_EnergyTable;										/*电量、需量的映射*/
const Str_OIB_DI2_EnergyTable GV_Str_OIB_DI2_EnergyTable[] = 
{/*OIB   	MaxNum  Unit_En	Unit_De */
	{0x00,	0x8D,	33,		C_NULL},							/*组合有功*/
	{0x10,	0x0D,	33,		28},								/*正向有功*/
	{0x11,	1,		33,		28},								/*A相正向有功*/
	{0x12,	1,		33,		28},								/*B相正向有功*/
	{0x13,	1,		33,		28},								/*C相正向有功*/
	{0x20,	0x0D,	33,		28},								/*反向有功*/
	{0x21,	1,		33,		28},								/*A相反向有功*/
	{0x22,	1,		33,		28},								/*B相反向有功*/
	{0x23,	1,		33,		28},								/*C相反向有功*/
	{0x30,	0x8D,	35,		32},								/*组合无功1*/
	{0x31,	0x81,	35,		32},								/*A相组合无功1*/
	{0x32,	0x81,	35,		32},								/*B相组合无功1*/
	{0x33,	0x81,	35,		32},								/*C相组合无功1*/
	{0x40,	0x8D,	35,		32},								/*组合无功2*/
	{0x41,	0x81,	35,		32},								/*A相组合无功2*/
	{0x42,	0x81,	35,		32},								/*B相组合无功2*/
	{0x43,	0x81,	35,		32},								/*C相组合无功2*/
	{0x50,	0x0D,	35,		32},								/*第一象限无功*/
	{0x51,	1,		35,		32},								/*A相第一象限无功*/
	{0x52,	1,		35,		32},								/*B相第一象限无功*/
	{0x53,	1,		35,		32},								/*C相第一象限无功*/
	{0x60,	0x0D,	35,		32},								/*第二象限无功*/
	{0x61,	1,		35,		32},								/*A相第二象限无功*/
	{0x62,	1,		35,		32},								/*B相第二象限无功*/
	{0x63,	1,		35,		32},								/*C相第二象限无功*/
	{0x70,	0x0D,	35,		32},								/*第三象限无功*/
	{0x71,	1,		35,		32},								/*A相第三象限无功*/
	{0x72,	1,		35,		32},								/*B相第三象限无功*/
	{0x73,	1,		35,		32},								/*C相第三象限无功*/
	{0x80,	0x0D,	35,		32},								/*第四象限无功*/
	{0x81,	1,		35,		32},								/*A相第四象限无功*/
	{0x82,	1,		35,		32},								/*B相第四象限无功*/
	{0x83,	1,		35,		32},								/*C相第四象限无功*/
};
#define	GV_Str_OIB_DI2_EnergyTableLen	( sizeof(GV_Str_OIB_DI2_EnergyTable) / sizeof(Str_OIB_DI2_EnergyTable) )

#define	C_WithOutSign						0x7F				/*去掉GV_Str_OIB_DI2_EnergyTable[].MaxNum中的符号，取数值*/

typedef  struct
{
	uchar8 OIB;													/*OIB*/
	uchar8 ClassType;											/*所属类号*/
	uchar8 DataType;											/*数据类型*/
	uchar8 MaxNum;												/*数组最大个数*/
	uchar8 Unit;												/*单位代号*/
	char8 Conversion;											/*换算*/
}Str_OIB_DI2_VariableTable;										/*电压电流功率的映射*/

const Str_OIB_DI2_VariableTable GV_Str_OIB_DI2_VariableTable01[] = 
{   /*OIB   	ClassType				dataType				MaxNum	Unit	Conversion*/
	{0x00,	C_Variable_Class,		C_long_unsigned,			3,		38,		-1},		/*电压*/
	{0x01,	C_Variable_Class,		C_double_long,				3,		36,		-3},		/*电流*/
	{0x02,	C_Variable_Class,		C_long_unsigned,			3,		8,		-1},		/*电压相角*/
	{0x03,	C_Variable_Class,		C_long_unsigned,			3,		8,		-1},		/*电压电流相角*/
	{0x04,	C_Power_Class,			C_double_long,				4,		27,		-1},		/*有功功率*/
	{0x05,	C_Power_Class,			C_double_long,				4,		31,		-1},		/*无功功率*/
	{0x06,	C_Power_Class,			C_double_long,				4,		29,		-1},		/*视在功率*/
	{0x07,	C_Power_Class,			C_double_long,				4,		27,		-1},		/*一分钟平均功率*/
	{0x08,	C_Power_Class,			C_double_long,				4,		31,		-1},		/*一分钟平均功率*/
	{0x0A,	C_Power_Class,			C_long,						4,		255,	-3},		/*功率因数*/
	{0x0F,	C_DateVariables_Class,	C_long_unsigned,			1,		47,		-2},		/*电网频率*/
	{0x10,	C_DateVariables_Class,	C_long,						1,		9,		-1},		/*表内温度*/
	{0x11,	C_DateVariables_Class,	C_long_unsigned,			1,		38,		-2},		/*时钟电池电压*/
	{0x12,	C_DateVariables_Class,	C_long_unsigned,			1,		38,		-2},		/*停电抄表电池电压*/
	{0x13,	C_DateVariables_Class,	C_double_long_unsigned,		1,		6,		C_NULL},	/*时钟电池工作时间*/
	{0x14,	C_DateVariables_Class,	C_bit_string,				7,		255,	C_NULL},	/*电表运行状态字*/
	{0x17,	C_DateVariables_Class,	C_double_long,				1,		28,		-4},		/*当前有功需量*/
	{0x18,	C_DateVariables_Class,	C_double_long,				1,		32,		-4},		/*当前无功需量*/
                                                            	
#if 0                                                       	
	{0x19,	C_DateVariables_Class,	C_double_long,				1,		30,		-4},		/*当前视在需量*/
#endif                                                      	                    		
                                                            	                    		
	{0x1A,	C_DateVariables_Class,	C_double_long_unsigned,		1,		54,		-4},		/*当前电价*/
	{0x1B,	C_DateVariables_Class,	C_double_long_unsigned,		1,		54,		-4},		/*当前费率电价*/
	{0x1C,	C_DateVariables_Class,	C_double_long_unsigned,		1,		54,		-4},		/*当前阶梯电价*/
	{0x2C,	C_Parameter_Class,		C_double_long_unsigned,		2,		254,	-2},		/*当前钱包文件*/
	{0x2D,	C_DateVariables_Class,	C_double_long_unsigned,		1,		10,		-2},		/*当前透支金额*/
	{0x2E,	C_DateVariables_Class,	C_double_long_unsigned,		1,		10,		-2},		/*累计购电金额*/
	{0x40,	C_DateVariables_Class,	C_bit_string,				1,		255,	C_NULL},	/*控制命令执行状态字*/
	{0x41,	C_DateVariables_Class,	C_bit_string,				1,		255,	C_NULL},	/*控制命令错误状态字*/
	{0x42,	C_DateVariables_Class,	C_bit_string,				1,		255,	C_NULL},	/*控制命令执行状态字*/
	{0x31,	C_DateVariables_Class,	C_double_long_unsigned,		1,		33,		-2},		/*月度用电量*/
	{0x32,	C_DateVariables_Class,	C_double_long_unsigned,		1,		33,		-2},		/*阶梯结算用电量*/
    {0x15,  C_DateVariables_Class,  C_bit_string,				1,		255,	C_NULL},	/*电表运行状态字8*/
};
#define GV_Str_OIB_DI2_VariableTable01Len ( sizeof(GV_Str_OIB_DI2_VariableTable01) / sizeof(Str_OIB_DI2_VariableTable) )

const Str_OIB_DI2_VariableTable GV_Str_OIB_DI2_VariableTable02[] = 
{/*OIB   	ClassType				dataType					MaxNum	Unit	Conversion*/
	{0x31,	C_DateVariables_Class,	C_structure,				2,		0xFF,		C_NULL},/*A相电压合格率*/
	{0x32,	C_DateVariables_Class,	C_structure,				2,		0xFF,		C_NULL},/*B相电压合格率*/
	{0x33,	C_DateVariables_Class,	C_structure,				2,		0xFF,		C_NULL},/*C相电压合格率*/
};
#define GV_Str_OIB_DI2_VariableTable02Len ( sizeof(GV_Str_OIB_DI2_VariableTable02) / sizeof(Str_OIB_DI2_VariableTable) )



const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_VolRateTable[] = 						/*电压合格率*/
{/*	DataType */
	{C_structure,					0x85,					0},
	{C_double_long_unsigned,		CLPer_Pass_MonitorTime,	CLPer_Pass_MonitorTime},		/*电压监测时间*/
	{C_long_unsigned,				CLPer_Pass_PassRate,	CLPer_Pass_PassRate},			/*电压合格率*/
	{C_long_unsigned,				CLPer_Pass_OverRate,	CLPer_Pass_OverRate},			/*电压超限率*/
	{C_double_long_unsigned,		CLPer_Pass_OverUpTime,	CLPer_Pass_OverUpTime},			/*电压超上限时间*/
	{C_double_long_unsigned,		CLPer_Pass_OverLowTime,	CLPer_Pass_OverLowTime}			/*电压超下限时间*/
};
#define GV_Str_DI0_DataType_VolRateTableLen ( sizeof(GV_Str_DI0_DataType_VolRateTable) / sizeof(Str_DI0_DataType_PaTable) )


/*数据类型序号宏定义*/
#define C_MeterPosition_DataTypeNum					1					/*电能表位置信息:经度、纬度、高度*/
#define C_LCDParamete_DataTypeNum					2					/*LCD参数*/
#define C_ZoneTime_DataTypeNum						3					/*时区时段数*/
#define	C_Holidy_DataTypeNum						4					/*公共假日*/
#define	C_Zone_DataTypeNum							5					/*当前套时区表*/
#define	C_Time_DataTypeNum							7					/*当前套时段表*/
#define	C_SettleDay_DataTypeNum						9					/*结算日*/
#define	C_VoltageOKPara								10					/*电压合格率参数*/
#define	C_Display_DataTypeNum						6					/*显示项*/
#define	C_DisplayNum_DataTypeNum					8					/*显示屏数*/
#define	C_AlarmLimit_DataTypeNum					11					/*报警金额*/
#define	C_OtherLimit_DataTypeNum					12					/*其他报警*/
#define	C_Fate_DataTypeNum							13					/*当前套费率电价*/
#define	C_Ladder_DataTypeNum						14					/*当前套阶梯*/
#define	C_BroadTime_DataTypeNum						15					/*广播校时参数*/
#define	C_FactoryInfTypeNum							16					/*模组版本信息参数*/
#define	C_Meter_CommProNum							17					/*通信规约*/


typedef  struct
{
	uchar8 OIB;							/*OIB*/
	//uchar8	DI2;					/*DI2*/
	//ushort16	DI1DI0;					/*DI1DI0*/
	uchar8 Unit;						/*单位代号*/
	char8 Conversion;					/*换算*/
	uchar8 DataType;					/*数据类型*/
	uchar8 NxtDataTypeNum;				/*下级数据类型序号*/

}Str_OIB_DI2_ParameterTable01;			/*参数的映射*/

const Str_OIB_DI2_ParameterTable01 GV_Str_OIB_DI2_ParameterTable01[] =
{/*OIB   	Unit		Conversion		DataType				NxtDataTypeNum	*/
	{0x00,	C_NULL,		C_NULL,			C_date_time_s,			C_NULL},						/*日期时间*/
	{0x01,	C_NULL,		C_NULL,			C_octet_string,			C_NULL}, 						/*通信地址*/
	{0x02,	C_NULL,		C_NULL,			C_octet_string,			C_NULL},						/*表号*/
	{0x03,	C_NULL,		C_NULL,			C_octet_string,			C_NULL},						/*客户编号*/
	{0x04,	C_NULL,		C_NULL,			C_structure,			C_MeterPosition_DataTypeNum},	/*设备地理位置*/
//	{0x05,	C_NULL,		C_NULL,			C_array,				C_GroupAddress_DataTypeNum},	/*组地址*/
	{0x07,	7,			C_NULL,			C_structure,			C_LCDParamete_DataTypeNum},		/*LCD参数*/
	{0x08,	C_NULL,		C_NULL,			C_date_time_s,			C_NULL},						/*两套时区表切换时间*/
	{0x09,	C_NULL,		C_NULL,			C_date_time_s,			C_NULL},						/*两套日时段表切换时间*/
	{0x0A,	C_NULL,		C_NULL,			C_date_time_s,			C_NULL},						/*两套分时费率切换时间*/
	{0x0B,	C_NULL,		C_NULL,			C_date_time_s,			C_NULL},						/*两套阶梯电价切换时间*/
	{0x0C,	C_NULL,		C_NULL,			C_structure,			C_ZoneTime_DataTypeNum},		/*时区时段数*/
	{0x0D,	C_NULL,		C_NULL,			C_unsigned,				C_NULL},						/*阶梯数*/
//	{0x0F,	C_NULL,		C_NULL,			C_unsigned,				C_NULL},						/*密钥总条数*/
	{0x10,	C_NULL,		C_NULL,			C_unsigned,				C_NULL},						/*计量单元数*/
	{0x11,	C_NULL,		C_NULL,			C_array,				C_Holidy_DataTypeNum},			/*公共假日表*/
	{0x12,	C_NULL,		C_NULL,			C_bit_string,			C_NULL},						/*周休日特征字*/
	{0x13,	C_NULL,		C_NULL,			C_unsigned,				C_NULL},						/*周休日采用的日时段表号*/
	{0x14,	C_NULL,		C_NULL,			C_array,				C_Zone_DataTypeNum},			/*当前套时区表*/
	{0x15,	C_NULL,		C_NULL,			C_array,				C_Zone_DataTypeNum},			/*备用套时区表*/
	{0x16,	C_NULL,		C_NULL,			C_array,				C_Time_DataTypeNum},			/*当前套日时段表*/
	{0x17,	C_NULL,		C_NULL,			C_array,				C_Time_DataTypeNum},			/*备用套日时段表*/
	{0x18,	C_NULL,		C_NULL,			C_array,				C_Fate_DataTypeNum},			/*当前套费率电价*/
	{0x19,	C_NULL,		C_NULL,			C_array,				C_Fate_DataTypeNum},			/*备用套费率电价*/
	{0x1A,	C_NULL,		C_NULL,			C_structure,			C_Ladder_DataTypeNum},			/*当前套阶梯电价*/
	{0x1B,	C_NULL,		C_NULL,			C_structure,			C_Ladder_DataTypeNum},			/*备用套阶梯电价*/
	{0x1C,	C_NULL,		C_NULL,			C_double_long_unsigned,	C_NULL},						/*电流互感器变比*/
	{0x1D,	C_NULL,		C_NULL,			C_double_long_unsigned,	C_NULL},						/*电压互感器变比*/
	{0x1E,	C_NULL,		C_NULL,			C_structure,			C_AlarmLimit_DataTypeNum},		/*报警金额限值*/
	{0x1F,	C_NULL,		C_NULL,			C_structure,			C_OtherLimit_DataTypeNum},		/*其他金额限值*/
	{0x22,	C_NULL,		C_NULL,			C_bit_string,			C_NULL},						/*插卡状态字*/
//	{0x23,	C_NULL,		C_NULL,			C_long_unsigned,		C_NULL},						/*认证有效时长*/
	{0x30,	38,			-2,				C_structure,			C_VoltageOKPara},				/*电压合格参数*/
	{0x31,	C_NULL,		C_NULL,			C_array,				C_FactoryInfTypeNum},			/*模组版本信息*/
};
#define GV_Str_OIB_DI2_ParameterTable01Len ( sizeof(GV_Str_OIB_DI2_ParameterTable01) / sizeof(Str_OIB_DI2_ParameterTable01) )

const Str_OIB_DI2_ParameterTable01 GV_Str_OIB_DI2_ParameterTable02[] =
{/*OIB   	Unit		Conversion			DataType				NxtDataTypeNum */
	{0x00,	6,			0,			C_unsigned,					C_NULL},						/*最大需量周期*/
	{0x01,	6,			0,			C_unsigned,					C_NULL},						/*滑差时间*/
	{0x02,	56,			0,			C_unsigned,					C_NULL},						/*校表脉冲宽度*/
	{0x03,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*资产管理编码*/
	{0x04,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*额定电压*/
	{0x05,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*额定电流/基本电流*/
	{0x06,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*最大电流*/
	{0x07,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*有功准确度等级*/
	{0x08,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*无功准确度等级*/
	{0x09,	254,		0,			C_double_long_unsigned,		C_NULL},						/*电能表有功常数*/
	{0x0A,	254,		0,			C_double_long_unsigned,		C_NULL},						/*电能表无功常数*/
	{0x0B,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*电能表型号*/
	{0x10,	C_NULL,		C_NULL,		C_bit_string,				C_NULL},						/*电表运行特征字1*/
	{0x11,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*软件备案号*/
	{0x12,	C_NULL,		C_NULL,		C_bit_string,				C_NULL},						/*有功组合方式特征字*/
	{0x13,	C_NULL,		C_NULL,		C_bit_string,				C_NULL},						/*无功组合方式1特征字*/
	{0x14,	C_NULL,		C_NULL,		C_bit_string,				C_NULL},						/*无功组合方式2特征字*/
	{0x16,	C_NULL,		C_NULL,		C_array,					C_SettleDay_DataTypeNum},		/*结算日*/

};
#define GV_Str_OIB_DI2_ParameterTable02Len ( sizeof(GV_Str_OIB_DI2_ParameterTable02) / sizeof(Str_OIB_DI2_ParameterTable01) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_DisplayNum[] =								/*显示屏数*/
{/*DI0	DataType	*/                                              							
	{C_unsigned,	0x01,	1},																	/*当前总对象数*/
	{C_unsigned,	0x01,	1},																	/*允许最大对象数*/
};
#define GV_Str_DI0_DataType_DisplayNumLen ( sizeof(GV_Str_DI0_DataType_DisplayNum) / sizeof(Str_DI0_DataType_PaTable) )
const Str_DI0_DataType_PaTable C_DemandTpyeTable[] =
{
	{C_double_long,				4,	4},		{C_date_time_s,	7,	7},
	{C_double_long_unsigned,	4,	4},		{C_date_time_s,	7,	7}
};
#define C_DemandTpyeTable_Len ( sizeof(C_DemandTpyeTable) / sizeof(C_DemandTpyeTable[0]) )


const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_MPPaTable[] =			/*位置信息*/
{/*	DataType	*/
	//{C_structure,				0x84,	0},
	{C_enum,					0x01,	0},
	{C_unsigned,				0x01,	0},
	{C_unsigned,				0x01,	0},
	{C_unsigned,				0x01,	4},
};
#define GV_Str_DI0_DataType_MPPaTableLen (sizeof(GV_Str_DI0_DataType_MPPaTable)/sizeof(Str_DI0_DataType_PaTable))

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_MPPaTable01[]=			/*位置信息*/
{/*	DataType	*/
	//{C_structure,				0x84,	0},
	{C_enum,					0x01,	0},
	{C_unsigned,				0x01,	0},
	{C_unsigned,				0x01,	0},
	{C_unsigned,				0x01,	4},
};
#define GV_Str_DI0_DataType_MPPaTable01Len ( sizeof(GV_Str_DI0_DataType_MPPaTable01) / sizeof(Str_DI0_DataType_PaTable) )


const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_LCDPaTable[] =			/*LCD参数*/
{/*DataType	*/                                                          	
	{17,	0x01,	1},														/*上电全显时间*/
	{18,	0x02,	2},														/*背光点亮时间*/
	{18,	0x02,	2},														/*显示查看背光点亮时间*/
	{18,	0x02,	2},														/*无电按键屏幕驻留时间*/
	{17,	0x01,	1},														/*显示电能小数位数*/
	{17,	0x01,	1},														/*显示功率小数位数*/
	{17,	0x01,	1},														/*液晶①②字样意义*/
};
#define GV_Str_DI0_DataType_LCDPaTableLen ( sizeof(GV_Str_DI0_DataType_LCDPaTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_VoltageOKPara[] =		/*电压合格率参数*/
{/*	DataType	*/                                                      	
	{C_long_unsigned,	0x02,	2},											/*电压考核上限*/
	{C_long_unsigned,	0x02,	2},											/*电压考核下限*/
	{C_long_unsigned,	0x02,	2},											/*电压合格上限*/
	{C_long_unsigned,	0x02,	2},											/*电压合格下限*/
};
#define GV_Str_DI0_DataType_VoltageOKParaLen ( sizeof(GV_Str_DI0_DataType_VoltageOKPara) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_ZTPaTable[] =			/*时区时段数*/
{/*	DataType	*/                                                      	
	{C_unsigned,	0x01,	1},												/*年时区数*/
	{C_unsigned,	0x01,	1},												/*日时段表数*/
	{C_unsigned,	0x01,	1},												/*日时段数*/
	{C_unsigned,	0x01,	1},												/*费率数*/
	{C_unsigned,	0x01,	1},												/*公共假日数*/
};
#define GV_Str_DI0_DataType_ZTPaTableLen ( sizeof(GV_Str_DI0_DataType_ZTPaTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_HPaTable[] =				/*公共假日，DI0此处只列01，转换时特殊处理*/
{/*	DataType	*/                                                      	
	{C_date,		0x05,	5},												/*公共假日中的日期*/
	{C_unsigned,	0x01,	1},												/*公共假日中的日时段表号*/

};
#define GV_Str_DI0_DataType_HPaTableLen ( sizeof(GV_Str_DI0_DataType_HPaTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_ZPaTable[] =				/*时区表*/
{/*	DataType		*/                                                  	
	{C_unsigned,	0x01,	1},												/*时区表中的月*/
	{C_unsigned,	0x01,	1},												/*时区表中的日*/
	{C_unsigned,	0x01,	1},												/*时区表中的日时段表号*/
};
#define GV_Str_DI0_DataType_ZPaTableLen ( sizeof(GV_Str_DI0_DataType_ZPaTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_AlarmLimitTable[] =		/*费率表*/
{/*	DataType	*/                                                      	
	{C_double_long_unsigned,	4,	4},										/*报警金额限值1*/
	{C_double_long_unsigned,	4,	4},										/*报警金额限值2*/
};
#define GV_Str_DI0_DataType_AlarmLimitLen ( sizeof(GV_Str_DI0_DataType_AlarmLimitTable) / sizeof(Str_DI0_DataType_PaTable) )
const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_OtherLimitTable[] =		/*费率表*/
{/*	DataType	*/                                                      	
	{C_double_long_unsigned,	4,	4},										/*透支金额限值*/
	{C_double_long_unsigned,	4,	4},										/*囤积金额限值*/
	{C_double_long_unsigned,	4,	4},										/*合闸允许金额限值*/
};
#define GV_Str_DI0_DataType_OtherLimitLen (sizeof(GV_Str_DI0_DataType_OtherLimitTable)/sizeof(Str_DI0_DataType_PaTable))

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_LadderTable[] =			/*阶梯表*/
{/*	DataType	*/                                                      	
	{C_array,	6,	4},														/*阶梯值*/
	{C_array,	7,	4},														/*阶梯电价*/
	{C_array,	4,	3},														/*阶梯结算日*/
};
#define GV_Str_DI0_DataType_LadderLen ( sizeof(GV_Str_DI0_DataType_LadderTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_BroadTimePaTable[] =		/*广播校时参数*/
{/*	DataType	*/                                                      	
	{C_long_unsigned,	2,	2},												/*广播校时偏差最小值*/
	{C_long_unsigned,	2,	2},												/*广播校时偏差最大值*/
};
#define GV_Str_DI0_DataType_BroadTimePaLen ( sizeof(GV_Str_DI0_DataType_BroadTimePaTable) / sizeof(Str_DI0_DataType_PaTable) )


const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_FateTable[] =			/*费率表*/
{/*	DataType	*/                                                      	
	{C_double_long_unsigned,	4,	4},										/*费率1*/
	{C_double_long_unsigned,	4,	4},										/*费率2*/
	{C_double_long_unsigned,	4,	4},										/*费率3*/
	{C_double_long_unsigned,	4,	4},										/*费率4*/
	{C_double_long_unsigned,	4,	4},										/*费率5*/
	{C_double_long_unsigned,	4,	4},										/*费率6*/
	{C_double_long_unsigned,	4,	4},										/*费率7*/
	{C_double_long_unsigned,	4,	4},										/*费率8*/
	{C_double_long_unsigned,	4,	4},										/*费率9*/
	{C_double_long_unsigned,	4,	4},										/*费率10*/
	{C_double_long_unsigned,	4,	4},										/*费率11*/
	{C_double_long_unsigned,	4,	4},										/*费率12*/
};
#define GV_Str_DI0_DataType_FateLen ( sizeof(GV_Str_DI0_DataType_FateTable) / sizeof(Str_DI0_DataType_PaTable) )



const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_TPaTable[] =				/*日时段表，DI0此处只列01，转换时特殊处理*/
{/*	DataType	*/                                                      	
	{C_array,		0x8F,	0},                                         	
	{C_structure,	0x83,	0},                                         	
	{C_unsigned,	0x01,	1},												/*日时段表中的时*/
	{C_unsigned,	0x01,	1},												/*日时段表中的分*/
	{C_unsigned,	0x01,	1},												/*日时段表中的费率号*/
};
#define GV_Str_DI0_DataType_TPaTableLen ( sizeof(GV_Str_DI0_DataType_TPaTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_SDPaTable[] =			/*每月结算日，DI0此处只列01，转换时特殊处理*/
{/*	DataType	*/                                                      	
	{C_unsigned,	0x01,	1},												/*结算日中的日*/
	{C_unsigned,	0x01,	1},												/*结算日中的时*/
};
#define GV_Str_DI0_DataType_SDPaTableLen ( sizeof(GV_Str_DI0_DataType_SDPaTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_CommProTable[] =			/*通信规约*/
{
	{C_visible_string,	CLMeter_CommPro1,	CLMeter_CommPro1},				/*通信规约列表1*/	
	{C_visible_string,	CLMeter_CommPro2,	CLMeter_CommPro2},				/*通信规约列表2*/	
};

#define GV_Str_DI0_DataType_CommProTableLen ( sizeof(GV_Str_DI0_DataType_CommProTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_FactoryPaTable[] =		/*厂家信息*/
{/*DataType	*/                                                          	
	{C_visible_string,	0x04,	4},											/*厂家编号*/
	{C_visible_string,	0x04,	4},											/*软件版本号*/
	{C_visible_string,	0x06,	6},											/*软件生产日期*/
	{C_visible_string,	0x04,	4},											/*硬件版本号*/
	{C_visible_string,	0x06,	6},											/*硬件生产日期*/
	{C_visible_string,	0x08,	8},											/*厂家扩展信息*/
};
#define GV_Str_DI0_DataType_FactoryPaTableLen ( sizeof(GV_Str_DI0_DataType_FactoryPaTable) / sizeof(Str_DI0_DataType_PaTable) )

typedef  struct
{
	uchar8	Temp;															/*属性*/
	uchar8	DataType;														/*数据类型*/
}Str_DataType_PaTable;														/*数据类型/属性对应*/
const Str_DataType_PaTable GV_Str_DataType_4300PaTable[] =					/**/
{/*Temp		DataType */
	{0x02,		C_visible_string},											/*设备描述符*/
	{0x03,		C_structure		},											/*版本信息*/
	{0x04,		C_date_time_s	},											/*生产日期*/
	{0x05,		C_array			},											/*子设备列表*/
	{0x06,		C_array			},											/*支持规约列表*/
	{0x07,		C_bool			},											/*允许跟对上报*/
	{0x08,		C_bool			},											/*允许主动上报*/
	{0x09,		C_bool			},											/*允许与主站通话*/
	{0x0A,		C_array			},											/*上报通道*/
};
#define GV_Str_DataType_4300PaTableLen ( sizeof(GV_Str_DataType_4300PaTable) / sizeof(Str_DataType_PaTable) )
typedef  struct
{
	ulong32	P_DataType;														/*数据类型*/
	uchar8	DataTypeNum;													/*数据类型序号*/
	uchar8	DataNum;														/*结构体数据项个数*/
}Str_Num_DataType_PaTable;													/*数据类型序号/数据类型的映射*/
const Str_Num_DataType_PaTable GV_Str_Num_DataType_PaTable[] =				/**/
{/*DataTypeNum	P_DataType	*/
	{(ulong32)(&GV_Str_DI0_DataType_MPPaTable[0]),				C_MeterPosition_DataTypeNum,		GV_Str_DI0_DataType_MPPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_LCDPaTable[0]),				C_LCDParamete_DataTypeNum,			GV_Str_DI0_DataType_LCDPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_ZTPaTable[0]),				C_ZoneTime_DataTypeNum,				GV_Str_DI0_DataType_ZTPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_HPaTable[0]),				C_Holidy_DataTypeNum,				GV_Str_DI0_DataType_HPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_ZPaTable[0]),				C_Zone_DataTypeNum,					GV_Str_DI0_DataType_ZPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_TPaTable[0]),				C_Time_DataTypeNum,					GV_Str_DI0_DataType_TPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_SDPaTable[0]),				C_SettleDay_DataTypeNum,			GV_Str_DI0_DataType_SDPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_VoltageOKPara[0]),			C_VoltageOKPara,					GV_Str_DI0_DataType_VoltageOKParaLen},
	{(ulong32)(&GV_Str_DI0_DataType_DisplayNum[0]),				C_DisplayNum_DataTypeNum,			GV_Str_DI0_DataType_DisplayNumLen},
	//{(ulong32)(&GV_Str_DI0_DataType_Display[0]),				C_Display_DataTypeNum,				GV_Str_DI0_DataType_DisplayLen},
	{(ulong32)(&GV_Str_DI0_DataType_AlarmLimitTable[0]),		C_AlarmLimit_DataTypeNum,			GV_Str_DI0_DataType_AlarmLimitLen},
	{(ulong32)(&GV_Str_DI0_DataType_OtherLimitTable[0]),		C_OtherLimit_DataTypeNum,			GV_Str_DI0_DataType_OtherLimitLen},
	{(ulong32)(&GV_Str_DI0_DataType_FateTable[0]),				C_Fate_DataTypeNum,					GV_Str_DI0_DataType_FateLen},
	{(ulong32)(&GV_Str_DI0_DataType_LadderTable[0]),			C_Ladder_DataTypeNum,				GV_Str_DI0_DataType_LadderLen},
	{(ulong32)(&GV_Str_DI0_DataType_BroadTimePaTable[0]),		C_BroadTime_DataTypeNum,			GV_Str_DI0_DataType_BroadTimePaLen},
	{(ulong32)(&GV_Str_DI0_DataType_CommProTable[0]),			C_Meter_CommProNum,					GV_Str_DI0_DataType_CommProTableLen},

};
#define GV_Str_Num_DataType_PaTableLen ( sizeof(GV_Str_Num_DataType_PaTable) / sizeof(Str_Num_DataType_PaTable) )

/*****************************事件记录、冻结二级表格***********************************************/
typedef  struct
{
	uchar8	DataTpye698;													/*698数据类型*/
	uchar8	Len645;															/*645数据长度*/
}Str_EventPara_Type;														/*事件记录配置参数结构体*/

const	Str_EventPara_Type	LossVol_ParaTable[4] =
{
	{ C_long_unsigned,	2},													/*电压触发上限*/
	{ C_long_unsigned,	2},													/*电压恢复下限*/
	{ C_double_long,	4},													/*电流触发下限*/
	{ C_unsigned,		1},													/*判定延时时间*/
};																			/*电能表失压事件*/

const	Str_EventPara_Type	AllLossVol_ParaTable[1] =
{
	{C_unsigned,		1},													/*判定延时时间*/
};																			/*电能表全失压事件*/
const	Str_EventPara_Type	LowVol_ParaTable[2] =
{
	{C_long_unsigned,	2},													/*电压触发上限*/
	{C_unsigned,		1},													/*判定延时时间*/
};																			/*电能表欠压事件*/

const	Str_EventPara_Type	OverVol_ParaTable[2]=
{
	{C_long_unsigned,	2},													/*电压触发上限*/
	{C_unsigned,		1},													/*判定延时时间*/
};																			/*电能表过压事件*/

const	Str_EventPara_Type	BreakVol_ParaTable[3] =
{
	{C_long_unsigned,	2},													/*电压触发下限*/
	{C_double_long,		4},													/*电流触发上限*/
	{C_unsigned,		1},													/*判定延时时间*/
};																			/*电能断相事件*/
const	Str_EventPara_Type	PowerOff_ParaTable[1] =
{
	{C_unsigned,			1},												/*判定延时时间*/
};																			/*掉电事件*/
const	Str_EventPara_Type	ReversedVoltage_ParaTable[1] =
{
	{C_unsigned,			1},												/*判定延时时间*/
};																			/*电压逆相序事件*/
const	Str_EventPara_Type	ReversedCurrent_ParaTable[1] =
{
	{C_unsigned,			1},												/*判定延时时间*/
};																			/*电流逆相序事件*/
const	Str_EventPara_Type	LossCurr_ParaTable[4] =
{
	{C_long_unsigned,	2},													/*电压触发下限*/
	{C_double_long,		4},													/*电流触发上限*/
	{C_double_long,		4},													/*电流恢复下限*/
	{C_unsigned,		1},													/*判定延时时间*/
};																			/*电能表失流事件*/

const	Str_EventPara_Type	OverCurr_ParaTable[2] =
{
	{C_double_long,	4},														/*电流触发上限*/
	{C_unsigned,	1},														/*判定延时时间*/
};																			/*电能表过流事件*/

const	Str_EventPara_Type	BreakCurr_ParaTable[3] =
{
	{C_long_unsigned,	2},													/*电压触发下限*/
	{C_double_long,		4},													/*电流触发上限*/
	{C_unsigned,		1},													/*判定延时时间*/
};																			/*电能表断流事件*/

const	Str_EventPara_Type	OverLo_ParaTable[2]=
{
	{C_double_long,	4},														/*有功功率触发下限*/
	{C_unsigned,	1},														/*判定延时时间*/
};																			/*电能表过载事件*/

const	Str_EventPara_Type	PosDeOver_ParaTable[2] =
{
	{C_double_long_unsigned,	4},											/*有功功率触发下限*/
	{C_unsigned,				1},											/*判定延时时间*/
};																			/*电能表正向有功需量超限事件*/

const	Str_EventPara_Type	ReDeOver_ParaTable[2] =
{
	{C_double_long_unsigned,	4},											/*无功功率触发下限*/
	{C_unsigned,				1},											/*判定延时时间*/

};

const	Str_EventPara_Type	TrendRev_ParaTable[2] =
{
	{C_double_long,	4},														/*有功功率触发下限*/
	{C_unsigned,	1},														/*判定延时时间*/
};																			/*电能表潮流反向事件*/

const	Str_EventPara_Type	PowerRev_ParaTable[2] =
{
	{C_double_long,	4},														/*有功功率触发下限*/
	{C_unsigned,	1},														/*判定延时时间*/
};																			/*电能表功率反向事件*/
const	Str_EventPara_Type	NoBalVol_ParaTable[2] =
{
	{C_long,		2},														/*不平衡率限值*/
	{C_unsigned,	1},														/*判定延时时间*/
};																			/*电能表电压不平衡事件*/

const	Str_EventPara_Type	NoBalCurr_ParaTable[2] =
{
	{C_long,		2},														/*不平衡率限值*/
	{C_unsigned,	1},														/*判定延时时间*/
};																			/*电能表电流不平衡事件*/

const	Str_EventPara_Type	SevNoBalCurr_ParaTable[2] =
{
	{C_long,		2},														/*不平衡率限值*/
	{C_unsigned,	1},														/*判定延时时间*/
};																			/*电能表电流严重不平衡事件*/

const	Str_EventPara_Type	PFactorTOver_ParaTable[2] =
{
	{C_long,		2},														/*功率因数超下限阀值*/
	{C_unsigned,	1},														/*判定延时时间*/
};																			/*电能表功率因数超下限事件*/

const	Str_EventPara_Type	NeutralCurrentAbnormal_ParaTable[3] =
{
	{C_double_long,		4},													/*电流触发下限阈值*/
	{C_long_unsigned,	2},													/*零线电流不平衡限值*/
	{C_unsigned,		1},													/*判定延时时间*/
                            												
};																			/*电能表零线电流异常事件*/

/*****************************事件记录三级表格***********************************************/        

/*class7 当前记录表结构体*/
const	Str_DI0_DataType_PaTable	Event_Class7_CurrentRecTable[4] =
{	/*	datatype					data698	data645len	*/
	{C_NULL,					0x01,		1},
	{C_structure,				0x02,		0},
	{C_double_long_unsigned,	0x04,		4},
	{C_double_long_unsigned,	0x04,		4}
};
/*class24 当前记录表结构体*/
const	Str_DI0_DataType_PaTable	Event_Class24_CurrentRecTable[2] =
{	/*di1, 	datatype					data698	data645len	*/
	{C_double_long_unsigned,	0x04,		4},
	{C_double_long_unsigned,	0x04,		4}
};
/*class7 时间状态记录表结构体*/
const	Str_DI0_DataType_PaTable	Event_Class7_10AttriTable[4]=
{	/*datatype					data698	data645len	*/
	{C_NULL,				0x01,		1},
	{C_structure,			0x02,		0},
	{C_date_time_s,			0x54,		7},									/*事件发生时刻*/
	{C_date_time_s,			0x55,		7}									/*事件结束时刻*/
};
/*class24 时间状态记录表结构体*/
const	Str_DI0_DataType_PaTable	Event_Class24_14AttriTable[2]=
{	/*di1, 	datatype					data698	data645len	*/
	{C_date_time_s,			0x54,		7},									/*事件发生时刻*/
	{C_date_time_s,			0x55,		7}									/*事件结束时刻*/
};

/******************************冻结三级表格**********************************************/        

/*1:瞬时冻结、月结算、时区表切换、日时段表切换、费率电价切换、阶梯切换*/
/*PS:1、分钟冻结的无功需量、电压、电流、有功功率、功率因数暂时不写*/
/*   2、日冻结的剩余金额、购电次数及透支金额不做*/
#define C_Bit0 0x01
#define C_Bit1 0x02
#define C_Bit2 0x04
#define C_Bit3 0x08
#define C_Bit4 0x10
#define C_Bit5 0x20
#define C_Bit6 0x40
#define C_Bit7 0x80


typedef struct
{
	uchar8	OIB;															/*OIB*/
	uchar8	TypeClass;														/*bit7  bit6，bit7=0表示645对应di为DI3，1表示di2di1，bit6=1表示Di2Di1两个均有效*/
	uchar8	ConfParaNum;													/*配置结构体个数*/
	uchar8	RelatedOINo;													/*关联对象属性列表*/
	ulong32	ConfParaTableAddr;												/*配置参数结构体首地址*/
	ulong32	RecordNum;          											
	ulong32	RelatedOAD;														/*关联对象OAD*/
	ulong32	RelatedOAD_T;													/*关联对象个数*/
}Str_Event_OIB1;

/*RelatedOINo==0xFF表示,没有关联属性，关联到表格 EventAttriNO[11]*/
const Str_Event_OIB1	Event_OIBTable[] =
{/*		OIB							TpyeClass					ParaNum	RelatedOINo	ParameterTable						RecordNum   			RelatedOAD					RelatedOAD_T	*/
	{CLoss_Vol_OIB,					C_SplitPhaseEvent_Class,		4,		0,		(ulong32)LossVol_ParaTable,					CLossA_Vol_Degree,				CLoss_Vol_OADTab,				CLoss_Vol_OADTabLen},				/*698-失压*/
	{CLow_Vol_OIB,					C_SplitPhaseEvent_Class,		2,		0,		(ulong32)LowVol_ParaTable,					CLowA_Vol_Degree,				CLow_Vol_OADTab,				CLow_Vol_OADTabLen},				/*698-欠压*/
	{COver_Vol_OIB,					C_SplitPhaseEvent_Class,		2,		0,		(ulong32)OverVol_ParaTable,					COverA_Vol_Degree,				COver_Vol_OADTab,				COver_Vol_OADTabLen},				/*698-过压*/
	{CBreak_Vol_OIB,				C_SplitPhaseEvent_Class,		3,		0,		(ulong32)BreakVol_ParaTable,				CBreakA_Vol_Degree,				CBreak_Vol_OADTab,				CBreak_Vol_OADTabLen},				/*698-断相*/
	{CLoss_Curr_OIB,				C_SplitPhaseEvent_Class,		4,		1,		(ulong32)LossCurr_ParaTable,				CLossA_Curr_Degree,				CLoss_Curr_OADTab,				CLoss_Curr_OADTabLen},				/*698-失流*/
	{COver_Curr_OIB,				C_SplitPhaseEvent_Class,		2,		1,		(ulong32)OverCurr_ParaTable,				COverA_Curr_Degree,				COver_Curr_OADTab,				COver_Curr_OADTabLen},				/*698-过流*/
	{CBreak_Curr_OIB,				C_SplitPhaseEvent_Class,		3,		1,		(ulong32)BreakCurr_ParaTable,				CBreakA_Curr_Degree,			CBreak_Curr_OADTab,				CBreak_Curr_OADTabLen},				/*698-断流*/
	{CTrend_Rev_OIB,				C_SplitPhaseEvent_Class,		2,		2,		(ulong32)TrendRev_ParaTable,				CPowerT_Rev_Degree,				CPower_Rev_OADTab,				CPower_Rev_OADTabLen},				/*698-潮流反向*/
	{COver_Lo_OIB,					C_SplitPhaseEvent_Class,		2,		2,		(ulong32)OverLo_ParaTable,					COverA_Lo_Degree,				COver_Lo_OADTab,				COver_Lo_OADTabLen},				/*698-过载*/
	{CPos_De_Over_OIB,				C_Event_Class,					2,		20,		(ulong32)PosDeOver_ParaTable,				CPos_Ac_De_Over_Degree,			CPos_Ac_De_Over_OADTab,			CPos_Ac_De_Over_OADTabLen},			/*698-电能表正向有功需量超限事件*/
	{CRe_De_Over_OIB,				C_Event_Class,					2,		21,		(ulong32)PosDeOver_ParaTable,				CRev_Ac_De_Over_Degree,			CRev_Ac_De_Over_OADTab,			CRev_Ac_De_Over_OADTabLen},			/*698-电能表反向有功需量超限事件*/
	{CRe_ReDe_Over_OIB,				C_SplitPhaseEvent_Class,		2,		22,		(ulong32)ReDeOver_ParaTable,				CQua1_Re_De_Over_Degree,		CQua_Re_De_Over_OADTab,			CQua_Re_De_Over_OADTabLen},			/*698-电能表无功需量超限事件*/
	{CPFactorT_Over_OIB,			C_SplitPhaseEvent_Class,		2,		10,		(ulong32)PFactorTOver_ParaTable,			CPFactorT_Over_Degree,			CPFactorT_Over_OADTab,			CPFactorT_Over_OADTabLen},			/*698-电能表功率因数超下限事件*/
	{CAll_Loss_Vol_OIB,				C_Event_Class,					1,		19,		0,											CAll_Loss_Vol_Degree,			CAll_Loss_Vol_OADTab,			CAll_Loss_Vol_OADTabLen},			/*698-电能表全失压事件*/
	{CAux_Pow_Down_OIB,				C_Event_Class,					1,		18,		0,											CAux_Pow_Down_Degree,			CAux_Pow_Down_OADTab,			CAux_Pow_Down_OADTabLen},			/*698-电能表辅助电源失电事件*/
	{CRevPS_Vol_OIB,				C_Event_Class,					1,		29,		(ulong32)ReversedVoltage_ParaTable,			CRevPS_Vol_Degree,				CRevPS_Vol_OADTab,				CRevPS_Vol_OADTabLen},				/*698-电能表电压逆相序事件*/
	{CRevPS_Curr_OIB,				C_Event_Class,					1,		29,		(ulong32)ReversedCurrent_ParaTable,			CRevPS_Curr_Degree,				CRevPS_Curr_OADTab,				CRevPS_Curr_OADTabLen},				/*698-电能表电流逆相序事件*/
	{CPow_Down_OIB,					C_Event_Class,					1,		18,		0,											CPow_Down_Degree,				CPow_Down_OADTab,				CPow_Down_OADTabLen},				/*698-电能表掉电事件*/
	{CProgram_OIB,					C_Event_Class,					0,		28,		0,											CProgram_Degree,				CProgram_OADTab,				CProgram_OADTabLen},				/*698-电能表编程事件*/
	{CTol_Clear_OIB,				C_Event_Class,					0,		8,		0,											CTol_Clear_Degree,				CTol_Clear_OADTab,				CTol_Clear_OADTabLen},				/*698-电能表清零事件*/
	{CDe_Clear_OIB,					C_Event_Class,					0,		9,		0,											CDe_Clear_Degree,				CDe_Clear_OADTab,				CDe_Clear_OADTabLen},				/*698-电能表需量清零事件*/
	{CEven_Clear_OIB,				C_Event_Class,					0,		28,		0,											CEven_Clear_Degree,				CEven_Clear_OADTab,				CEven_Clear_OADTabLen},				/*698-电能表事件清零事件*/
	{CAdjTime_OIB,					C_Event_Class,					0,		11,		0,											CAdjTime_Degree,				CAdjTime_OADTab,				CAdjTime_OADTabLen},				/*698-电能表校时事件*/
	{CProgPT_OIB,					C_Event_Class,					0,		12,		0,											CProgPT_Degree,					CProgPT_OADTab,					CProgPT_OADTabLen},					/*698-电能表时段表编程事件*/
	{CProgTZ_OIB,					C_Event_Class,					0,		13,		0,											CProgTZ_Degree,					CProgTZ_OADTab,					CProgTZ_OADTabLen},					/*698-电能表时区表编程事件*/
	{CProgWRe_OIB,					C_Event_Class,					0,		14,		0,											CProgWRe_Degree,				CProgWRe_OADTab,				CProgWRe_OADTabLen},				/*698-电能表周休日编程事件*/
	{CProgSettD_OIB,				C_Event_Class,					0,		15,		0,											CProgSettD_Degree,				CProgSettD_OADTab,				CProgSettD_OADTabLen},				/*698-电能表结算日编程事件*/
	{COpenW_OIB,					C_Event_Class,					0,		4,		0,											COpenW_Degree,					COpenW_OADTab,					COpenW_OADTabLen},					/*698-电能表开盖事件*/
	{COpenCW_OIB,					C_Event_Class,					0,		4,		0,											COpenCW_Degree,					COpenCW_OADTab,					COpenCW_OADTabLen},					/*698-电能表开端钮盖事件*/
	{CNoBal_Vol_OIB,				C_Event_Class,					2,		3,		(ulong32)NoBalVol_ParaTable,				CNoBal_Vol_Degree,				CNoBal_Vol_OADTab,				CNoBal_Vol_OADTabLen},				/*698-电能表电压不平衡事件*/
	{CNoBal_Curr_OIB,				C_Event_Class,					2,		3,		(ulong32)NoBalCurr_ParaTable,				CNoBal_Curr_Degree,				CNoBal_Curr_OADTab,				CNoBal_Curr_OADTabLen},				/*698-电能表电流不平衡事件*/
	{CRelayOpen_OIB,				C_Event_Class,					0,		5,		0,											CRelayOpen_Degree,				CRelayOpen_OADTab,				CRelayOpen_OADTabLen},				/*698-电能表跳闸事件*/
	{CRelayClose_OIB,				C_Event_Class,					0,		5,		0,											CRelayClose_Degree,				CRelayClose_OADTab,				CRelayClose_OADTabLen},				/*698-电能表合闸事件*/
	{CProgHol_OIB,					C_Event_Class,					0,		28,		0,											CProgHol_Degree,				CProgHol_OADTab,				CProgHol_OADTabLen},				/*698-电能表节假日编程事件*/
	{CProgAcC_OIB,					C_Event_Class,					0,		16,		0,											CProgAcC_Degree,				CProgAcC_OADTab,				CProgAcC_OADTabLen},				/*698-电能表有功组合方式编程事件*/
	{CProgReC_OIB,					C_Event_Class,					0,		17,		0,											CProgReC_Degree,				CProgReC_OADTab,				CProgReC_OADTabLen},				/*698-电能表无功组合方式编程事件*/
	{CProgTPara_OIB,				C_Event_Class,					0,		28,		0,											CProgTPara_Degree,				CProgTPara_OADTab,				CProgTPara_OADTabLen},				/*698-电能表费率参数表编程事件*/
	{CProgLad_OIB,					C_Event_Class,					0,		28,		0,											CProgLad_Degree,				CProgLad_OADTab,				CProgLad_OADTabLen},				/*698-电能表阶梯表编程事件*/
	{CKey_Update_OIB,				C_Event_Class,					0,		27,		0,											CProgKD_Degree,					CProgKD_OADTab,					CProgKD_OADTabLen},					/*698-电能表密钥更新事件*/
	{CAbnorC_OIB,					C_Event_Class,					0,		28,		0,											CAbnorC_Degree,					CAbnorC_OADTab,					CAbnorC_OADTabLen},					/*698-电能表异常插卡事件*/
	{CBuyCurr_OIB,					C_Event_Class,					0,		28,		0,											CBuyCurr_Degree,				CBuyCurr_OADTab,				CBuyCurr_OADTabLen},				/*698-电能表购电事件*/
	{CReturn_M_OIB,					C_Event_Class,					0,		28,		0,											CReturn_M_Degree,				CReturn_M_OADTab,				CReturn_M_OADTabLen},				/*698-电能表退费事件*/
	{CConM_OIB,						C_Event_Class,					0,		6,		0,											CConM_Degree,					CConM_OADTab,					CConM_OADTabLen	},					/*698-电能表恒定磁场干扰事件*/
	{CRelayFa_OIB,					C_Event_Class,					0,		26,		0,											CRelayFa_Degree,				CRelayFa_OADTab,				CRelayFa_OADTabLen},				/*698-电能表负荷开关误动作事件*/
	{CPowerFa_OIB,					C_Event_Class,					0,		7,		0,											CPowerFa_Degree,				CPowerFa_OADTab,				CPowerFa_OADTabLen},				/*698-电能表电源异常事件*/
	{CSevNoBal_Curr_OIB,			C_Event_Class,					2,		3,		(ulong32)SevNoBalCurr_ParaTable,			CSevNoBal_Curr_Degree,			CSevNoBal_Curr_OADTab,			CSevNoBal_Curr_OADTabLen},			/*698-电能表电流严重不平衡事件*/
	{CClock_FaultState_OIB,			C_Event_Class,					1,		28,		0,											CClockFa_Degree,				CClockFa_OADTab,				CClockFa_OADTabLen},				/*698-电能表时钟故障事件*/
	{CMeteringChipFault_OIB,		C_Event_Class,					1,		28,		(ulong32)ReversedVoltage_ParaTable,			CMeterFa_Degree,				CMeterFa_OADTab,				CMeterFa_OADTabLen},				/*698-电能表计量芯片故障事件*/
	{CBroadcastTime_OIB,			C_Event_Class,					0,		11,		0,											CBroadcastTime_Degree,			CBroadcastTime_OADTab,			CBroadcastTime_OADTabLen},			/*698-电能表广播校时事件*/
	{CNeutralCurrentAbnormal_OIB,	C_Event_Class,					3,		2,		(ulong32)NeutralCurrentAbnormal_ParaTable,	CNeutralCurrentAbnormal_Degree,	CNeutralCurrentAbnormal_OADTab,	CNeutralCurrentAbnormal_OADTabLen},	/*698-电能表零线电流异常事件*/
};
#define	C_Event_OIBTableLen	( sizeof(Event_OIBTable) / sizeof(Event_OIBTable[0]) )


const	Str_DI0_DataType_PaTable	PosDeOver_SpecificData[] =
{
	{C_double_long_unsigned,	4,	CL_double_long_unsigned},
	{C_date_time_s,				8,	CL_date_time_s},
};
#define	PosDeOver_SpecificDataLen ( sizeof(PosDeOver_SpecificData) / sizeof(PosDeOver_SpecificData[0]) )

const	Str_DI0_DataType_PaTable	Program_SpecificData[]=
{
	{C_array,	0,	0},
	{0x01,		0,	0},
	{C_OAD,		CL_OAD,		CL_OAD},
};
#define	Program_SpecificDataLen ( sizeof(Program_SpecificData) / sizeof(Program_SpecificData[0]) )

const	Str_DI0_DataType_PaTable	Even_Clear_SpecificData[] =
{
	{C_array,	0,	0},
	{0x01,		0,	0},
	{C_OMD,		CL_OMD,	CL_OMD},
};
#define	Even_Clear_SpecificDataLen ( sizeof(Even_Clear_SpecificData) / sizeof(Even_Clear_SpecificData[0]) )

const	Str_DI0_DataType_PaTable	ProgPT_SpecificData[] =
{
	{C_OAD,			CL_OAD,			CL_OAD},
	{C_array,		0,				0},
	{14,			0,				0},
	{C_structure,	0,				0},
	{3,				0,				0},
	{C_unsigned,	CL_unsigned,	CL_unsigned},
	{C_unsigned,	CL_unsigned,	CL_unsigned},
	{C_unsigned,	CL_unsigned,	CL_unsigned},
};
#define	ProgPT_SpecificDataLen ( sizeof(ProgPT_SpecificData) / sizeof(ProgPT_SpecificData[0]) )

const	Str_DI0_DataType_PaTable	ProgHol_SpecificData[] =
{
	{C_OAD,			CL_OAD,			CL_OAD},
	{C_structure,	0,				0},
	{2,				0,				0},
	{C_date,		CL_date,		CL_date},
	{C_unsigned,	CL_unsigned,	CL_unsigned},
};
#define	ProgHol_SpecificDataLen ( sizeof(ProgHol_SpecificData)/sizeof(ProgHol_SpecificData[0]) )

const	Str_DI0_DataType_PaTable	ProgReturnMoney_SpecificData[] =
{
	{C_double_long_unsigned,			CL_double_long_unsigned,	CL_double_long_unsigned},
};
#define	ProgReturnMoney_SpecificDataLen ( sizeof(ProgReturnMoney_SpecificData) / sizeof(ProgReturnMoney_SpecificData[0]) )
const	Str_DI0_DataType_PaTable	ProgErrCard_SpecificData[]=
{
	{C_octet_string,	8,					8},
	{C_unsigned,		CL_unsigned,		CL_unsigned},
	{C_octet_string,	5,					5},
	{C_long_unsigned,	CL_long_unsigned,	CL_long_unsigned},
};
#define	ProgErrCard_SpecificDataLen ( sizeof(ProgErrCard_SpecificData) / sizeof(ProgErrCard_SpecificData[0]) )


const	Str_DI0_DataType_PaTable	ProgLadder_SpecificData[] =
{
	{C_structure,				0,	0},
	{3,							0,	0},
	{C_array,					0,	0},
	{6,							0,	0},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_array,					0,	0},
	{7,							0,	0},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_array,					0,	0},
	{4,							0,	0},
	{C_structure,				0,	0},
	{3,							0,	0},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_structure,				0,	0},
	{3,							0,	0},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_structure,				0,	0},
	{3,							0,	0},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_structure,				0,	0},
	{3,							0,	0},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
};
#define	ProgLadder_SpecificDataLen ( sizeof(ProgLadder_SpecificData) / sizeof(ProgLadder_SpecificData[0]) )

typedef struct
{
	ulong32	SpecificDataTableAddr;								/*特殊数据结构体首地址*/
	ulong32	SpecificOADTableAddr;								/*特殊数据OAD首地址*/
	uchar8	OIB;												/*OIB*/
	uchar8	TableLenth;
	uchar8	OADTableLenth;
}Str_Event_SpecificData;
#if 1
typedef struct
{
	ulong32	SpecialOAD;											/*特殊数据结构体首地址*/
	uchar8	DataLen;											/*数据长度*/
	uchar8  LineNo;												/*在编码中的行号*/
}Str_Event_SingleSpecificData;

const Str_Event_SingleSpecificData PosDeOver_SpecificOAD[2] =				/*需量超限事件记录单元*/
{
	C_OverDemandRenew_Demand,			CLCurr_AcDemand,		0,	
	C_OverDemandRenew_HapTime,			CL_date_time_s,			1,
};
const Str_Event_SingleSpecificData Program_SpecificOAD[1] =					/*编程事件记录单元*/
{
	CProgram_OADList,					CL_OAD * CProgOADNum,	0
};
const Str_Event_SingleSpecificData Even_Clear_SpecificOAD[1] =				/*时段表编程事件记录单元*/
{
	CEventClear_OADList,				CL_OAD,					0
};
const Str_Event_SingleSpecificData ProgPT_SpecificOAD[2] =					/*时段表编程事件记录单元*/
{
	CRWTimeTable_OAD,					CL_OAD,					0,
	CRWTimeTable_ForwardData,			CLFirst_TZone_1PT_Data,	1
};
const Str_Event_SingleSpecificData ProgHol_SpecificOAD[2] =					/*节假日编程事件记录单元*/
{
	C_RWHoliday_OAD,					CL_OAD,					0,
	CRWHoliday_ForwardData,				CLHolidy_PT_Table1,		1
};
const Str_Event_SingleSpecificData ProgReturnMoney_SpecificOAD[1] =			/*退费事件记录单元*/
{
	CReturnMoney_Charge,				CLAlam1_Money,			0
};
const Str_Event_SingleSpecificData ProgErrCard_SpecificOAD[4] =				/*异常插卡事件记录单元*/
{
	CAbnormalCard_CareNo,				CLAbnormalCard_CareNo,				0,
	CAbnormalCard_ErrorStatus,			CLAbnormalCard_ErrorStatus,			1,
	CAbnormalCard_OrderHead,			CLAbnormalCard_OrderHead,			2,
	CAbnormalCard_ErrorRespondStatus,	CLAbnormalCard_ErrorRespondStatus,	3
};
#endif

const Str_Event_SpecificData	Event_SpecificData[] =
{/* ParameterTable				        	 ParameterOAD				        	OIB															*/
	{(ulong32)PosDeOver_SpecificData,		(ulong32)PosDeOver_SpecificOAD,			CPos_De_Over_OIB,	PosDeOver_SpecificDataLen,			0x02},	/*698-电能表正向有功需量超限事件*/
	{(ulong32)PosDeOver_SpecificData,		(ulong32)PosDeOver_SpecificOAD,			CRe_De_Over_OIB,	PosDeOver_SpecificDataLen,			0x02},	/*698-电能表反向有功需量超限事件*/
	{(ulong32)PosDeOver_SpecificData,		(ulong32)PosDeOver_SpecificOAD,			CRe_ReDe_Over_OIB,	PosDeOver_SpecificDataLen,			0x02},	/*698-电能表无功需量超限事件*/
	{(ulong32)Program_SpecificData,			(ulong32)Program_SpecificOAD,			CProgram_OIB,		Program_SpecificDataLen	,			1},		/*698-电能表编程事件*/
	{(ulong32)Even_Clear_SpecificData,		(ulong32)Even_Clear_SpecificOAD,		CEven_Clear_OIB,	Even_Clear_SpecificDataLen,			1},		/*698-电能表清零事件*/
	{(ulong32)ProgPT_SpecificData,			(ulong32)ProgPT_SpecificOAD,			CProgPT_OIB,		ProgPT_SpecificDataLen	,			2},		/*698-电能表时段表编程事件*/
	{(ulong32)ProgHol_SpecificData,			(ulong32)ProgHol_SpecificOAD,			CProgHol_OIB,		ProgHol_SpecificDataLen	,			2},		/*698-电能表节假日编程事件*/
	{(ulong32)ProgReturnMoney_SpecificData,	(ulong32)ProgReturnMoney_SpecificOAD,	CReturn_M_OIB,		ProgReturnMoney_SpecificDataLen	,	1},		/*698-退费事件*/
	{(ulong32)ProgErrCard_SpecificData,		(ulong32)ProgErrCard_SpecificOAD,		CAbnorC_OIB,		ProgErrCard_SpecificDataLen	,		4},		/*698-异常插卡事件*/

};
#define	C_Event_SpecificDataLen ( sizeof(Event_SpecificData) / sizeof(Event_SpecificData[0]) )

typedef struct
{
	ulong32		RelatedOAD;										/*关联对象OAD*/
	ulong32		RelatedOAD_T;									/*关联对象冻结周期及次数*/
	ulong32		RelatedOADAddr;									/*关联对象OAD地址*/
	ushort16	MaxFrozenNum;									/*最大记录条数*/
	uchar8		RelatedOAD_Num;									/*关联对象默认个数*/
	uchar8		OIB;											/*冻结记录OAD*/
}Str_Event_OIB2;



typedef struct
{
	ulong32 V_OADFlagL;
	ulong32 V_OADFlagH;
	ushort16 V_CRC;
}Str_RelatedOAD_Type;


/*RelatedOINo==0xFF表示,没有*/
const ulong32 C_RelatedOAD_Immid_Init[] =						/*瞬时冻结、约定冻结*/
{
	0x00000001,													/*冻结周期*/
	0x00100200,													/*正向有功电能总及费率*/
	0x00200200,													/*反向有功电能总及费率*/
	0x00300200,													/*组合无功1电能总及费率*/
	0x00400200,													/*组合无功2电能总及费率*/
	0x00500200,													/*1象限无功电能总及费率*/
	0x00600200,													/*2象限无功电能总及费率*/
	0x00700200,													/*3象限无功电能总及费率*/
	0x00800200,													/*4象限无功电能总及费率*/
	0x10100200,													/*正向有功最大需量总及费率*/
	0x10200200,													/*反向有功最大需量总及费率*/
	0x20040200,													/*有功功率合相及分相*/
	0x20050200,													/*无功功率合相及分相*/
};
#define	C_RelatedOAD_Immid_InitLen       ( sizeof(C_RelatedOAD_Immid_Init) / sizeof(C_RelatedOAD_Immid_Init[0]) )

const ulong32 C_RelatedOAD_Min_Init[] =							/*分钟冻结*/
{
	0x0000000F,													/*冻结周期*/
	0x00100201,													/*正向有功电能总*/
	0x00200201,													/*反向有功电能总*/
	0x00500201,													/*1象限无功电能总*/
	0x00600201,													/*2象限无功电能总*/
	0x00700201,													/*3象限无功电能总*/
	0x00800201,													/*4象限无功电能总*/
	0x20170200,													/*正向有功需量*/
	0x20180200,													/*反向有功需量*/
	0x20000200,													/*电压三相*/
	0x20010200,													/*电流三相*/
	0x20040200,													/*有功功率合相及分相*/
	0x200A0200,													/*功率因数合相及分相*/
};
#define	C_RelatedOAD_Min_InitLen       ( sizeof(C_RelatedOAD_Min_Init) / sizeof(C_RelatedOAD_Min_Init[0]) )

const ulong32 C_RelatedOAD_Hour_Init[] =						/*小时冻结*/
{
	0x00000001,													/*冻结周期*/
	0x00100201,													/*正向有功电能总*/
	0x00200201,													/*反向有功电能总*/
};
#define	C_RelatedOAD_Hour_InitLen       ( sizeof(C_RelatedOAD_Hour_Init) / sizeof(C_RelatedOAD_Hour_Init[0]) )

const ulong32 C_RelatedOAD_Day_Init[]=							/*日冻结*/
{
	0x00000001,													/*冻结周期*/
	0x00100200,													/*正向有功电能总及费率*/
	0x00200200,													/*反向有功电能总及费率*/
	0x00300200,													/*组合无功1电能总及费率*/
	0x00400200,													/*组合无功2电能总及费率*/
	0x00500200,													/*1象限无功电能总及费率*/
	0x00600200,													/*2象限无功电能总及费率*/
	0x00700200,													/*3象限无功电能总及费率*/
	0x00800200,													/*4象限无功电能总及费率*/
	0x10100200,													/*正向有功最大需量总及费率*/
	0x10200200,													/*反向有功最大需量总及费率*/
	0x20040200,													/*有功功率合相及分相*/
	0x20050200,													/*无功功率合相及分相*/
	0x202C0200,													/*剩余金额及购电次数*/
	0x202D0200,													/*透支金额*/
               													
	0x21310201,													/*A相日电压合格率*/
	0x21320201,													/*B相日电压合格率*/
	0x21330201,													/*C相日电压合格率*/
};
#define	C_RelatedOAD_Day_InitLen       ( sizeof(C_RelatedOAD_Day_Init) / sizeof(C_RelatedOAD_Day_Init[0]) )

const ulong32 C_RelatedOAD_Settle_Init[]=						/*结算日冻结*/
{
	0x00000001,													/*冻结周期*/
	0x00000200,													/*组合有功电能总及费率*/
	0x00100200,													/*正向有功电能总及费率*/
	0x00110200,													/*A相正向有功电能*/
	0x00120200,													/*B相正向有功电能*/
	0x00130200,													/*C相正向有功电能*/
	0x00200200,													/*反向有功电能总及费率*/
	0x00200201,													/*A相反向有功电能*/
	0x00200202,													/*B相反向有功电能*/
	0x00200203,													/*C相反向有功电能*/
	0x00300200,													/*组合无功1电能总及费率*/
	0x00310200,													/*A相组合无功1电能*/
	0x00320200,													/*B相组合无功1电能*/
	0x00330200,													/*C相组合无功1电能*/
	0x00400200,													/*组合无功2电能总及费率*/
	0x00400201,													/*A相组合无功2电能*/
	0x00400202,													/*B相组合无功2电能*/
	0x00400203,													/*C相组合无功2电能*/
	0x00500200,													/*1象限无功电能总及费率*/
	0x00510200,													/*A相1象限无功电能*/
	0x00520200,													/*B相1象限无功电能*/
	0x00530200,													/*C相1象限无功电能*/
	0x00600200,													/*2象限无功电能总及费率*/
	0x00610200,													/*A相2象限无功电能*/
	0x00620200,													/*B相2象限无功电能*/
	0x00630200,													/*C相2象限无功电能*/
	0x00700200,													/*3象限无功电能总及费率*/
	0x00710200,													/*A相3象限无功电能*/
	0x00720200,													/*B相3象限无功电能*/
	0x00730200,													/*C相3象限无功电能*/
	0x00800200,													/*4象限无功电能总及费率*/
	0x00810200,													/*A相4象限无功电能*/
	0x00820200,													/*B相4象限无功电能*/
	0x00830200,													/*C相4象限无功电能*/
	0x20310200,													/*结算周期用电量*/
	0x10100200,													/*正向有功最大需量总及费率*/
	0x10200200,													/*反向有功最大需量总及费率*/
	0x10300200,													/*组合无功1最大需量总及费率*/
	0x10400200,													/*组合无功2最大需量总及费率*/
	0x10500200,													/*1象限无功最大需量总及费率*/
	0x10600200,													/*2象限无功最大需量总及费率*/
	0x10700200,													/*3象限无功最大需量总及费率*/
	0x10800200,													/*4象限无功最大需量总及费率*/

};
#define	C_RelatedOAD_Settle_InitLen       ( sizeof(C_RelatedOAD_Settle_Init) / sizeof(C_RelatedOAD_Settle_Init[0]) )

const ulong32 C_RelatedOAD_Month_Init[] =						/*月冻结*/
{
	0x00000001,													/*冻结周期*/
	0x00000200,													/*组合有功电能总及费率*/
	0x00100200,													/*正向有功电能总及费率*/
	0x00110200,													/*A相正向有功电能*/
	0x00120200,													/*B相正向有功电能*/
	0x00130200,													/*C相正向有功电能*/
	0x00200200,													/*反向有功电能总及费率*/
	0x00210200,													/*A相反向有功电能*/
	0x00220200,													/*B相反向有功电能*/
	0x00230200,													/*C相反向有功电能*/
	0x00300201,													/*组合无功1电能总及费率*/
	0x00400200,													/*组合无功2电能总及费率*/
	0x00500200,													/*1象限无功电能总及费率*/
	0x00510200,													/*A相1象限无功电能*/
	0x00520200,													/*B相1象限无功电能*/
	0x00530200,													/*C相1象限无功电能*/
	0x00600200,													/*2象限无功电能总及费率*/
	0x00610200,													/*A相2象限无功电能*/
	0x00620200,													/*B相2象限无功电能*/
	0x00630200,													/*C相2象限无功电能*/
	0x00700200,													/*3象限无功电能总及费率*/
	0x00710200,													/*A相3象限无功电能*/
	0x00720200,													/*B相3象限无功电能*/
	0x00730200,													/*C相3象限无功电能*/
	0x00800200,													/*4象限无功电能总及费率*/
	0x00810200,													/*A相4象限无功电能*/
	0x00820200,													/*B相4象限无功电能*/
	0x00830200,													/*C相4象限无功电能*/
	0x00900200,													/*正向视在电能总及费率*/
	0x00910200,													/*A相视在有功电能*/
	0x00920200,													/*B相视在有功电能*/
	0x00930200,													/*C相视在有功电能*/
	0x00A00200,													/*反向视在电能总及费率*/
	0x00A10200,													/*A相反向视在电能*/
	0x00A20200,													/*B相反向视在电能*/
	0x00A30200,													/*C相反向视在电能*/
	0x20310200,													/*月度用电量*/
	0x10100200,													/*正向有功最大需量总及费率*/
	0x10200200,													/*反向有功最大需量总及费率*/

	0x21310202,													/*A相月电压合格率*/
	0x21320202,													/*B相月电压合格率*/
	0x21330202,													/*C相月电压合格率*/
};
#define	C_RelatedOAD_Month_InitLen       ( sizeof(C_RelatedOAD_Month_Init) / sizeof(C_RelatedOAD_Month_Init[0]) )

const ulong32 C_RelatedOAD_Year_Init[] =						/*年阶梯结算日冻结*/
{
	0x00000001,													/*冻结周期*/
	0x20320200,													/*结算周期用电量*/
};
#define	C_RelatedOAD_Year_InitLen       ( sizeof(C_RelatedOAD_Year_Init) / sizeof(C_RelatedOAD_Year_Init[0]) )

const ulong32 FreezeChangeTable[][2] =
{
	{C_Fre_PosAcTolEn,				0x05000100},				/*0x00,	冻结时刻正向有功总电能*/
	{C_Fre_RevAcTolEn,				0x05000200},				/*0x01,	冻结时刻反向有功总电能*/
	{C_Fre_ComRe1TolEn,				0x05000300},				/*0x02,	冻结时刻组合无功1总电能*/
	{C_Fre_ComRe2TolEn,				0x05000400},				/*0x03,	冻结时刻组合无功2总电能*/
                                                				
	{C_Fre_TQuadrant1En,			0x05000500},				/*0x10,	冻结时刻第一象限无功总电能*/
	{C_Fre_TQuadrant2En,			0x05000600},				/*0x11,	冻结时刻第二象限无功总电能*/
	{C_Fre_TQuadrant3En,			0x05000700},				/*0x12,	冻结时刻第三象限无功总电能*/
	{C_Fre_TQuadrant4En,			0x05000800},				/*0x13,	冻结时刻第四象限无功总电能*/
                                                				
	{C_Fre_PosAc_DeTime,			0x05000900},				/*0x20,	正向有功最大需量及发生时间*/
	{C_Fre_RevAc_DeTime,			0x05000A00},				/*0x21,	反向有功最大需量及发生时间*/
                                                				
	{C_Fre_Active_Power,			0x05001000},				/*0x2C,	冻结时刻有功功率*/
	{C_Fre_ReActiveT_Power,			0x05001000},				/*0x2D,	冻结时刻无功功率*/

};
#define	C_FreezeChangeTable_Len	  ( sizeof(FreezeChangeTable) / sizeof(FreezeChangeTable[0]) )


const Str_Event_OIB2	Freeze_OIBTable[] =
{  //关联对象属性标识码			OAD个数,							默认关联对象地址,		存储深度		默认关联对象个数			,冻结记录OAD
	{CI_Free_OADTab,		CI_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Immid_Init,	3,		C_RelatedOAD_Immid_InitLen	,0x00},			/*698-瞬时冻结*/
	{CMin_Free_OADTab,		CMin_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Min_Init,		351,	C_RelatedOAD_Min_InitLen	,0x02},			/*698-分钟冻结*//*原300天MaxFrozenNum为288(28800条),改为365天后为35040条,暂改为351,实际该内容程序没用到*/
	{CH_Free_OADTab,		CH_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Hour_Init,	254,	C_RelatedOAD_Hour_InitLen	,0x03},			/*698-小时冻结*/
	{CD_Free_OADTab,		CD_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Day_Init,		365,	C_RelatedOAD_Day_InitLen	,0x04},			/*698-日冻结*/
	{CSett_Free_OADTab,		CSett_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Settle_Init,	12,		C_RelatedOAD_Settle_InitLen	,0x05},			/*698-结算日冻结*/
	{CM_Free_OADTab,		CM_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Month_Init,	24,		C_RelatedOAD_Month_InitLen	,0x06},			/*698-月冻结*/
	{CYSettle_Free_OADTab,	CYSettle_Free_OADTabLen_T,	(ulong32)C_RelatedOAD_Year_Init,	4,		C_RelatedOAD_Year_InitLen	,0x11},			/*698-年冻结*/
	{CTZ_Free_OADTab,		CTZ_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Immid_Init,	2,		C_RelatedOAD_Immid_InitLen	,0x08},			/*698-时区表切换冻结*/
	{CPT_Free_OADTab,		CPT_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Immid_Init,	2,		C_RelatedOAD_Immid_InitLen	,0x09},			/*698-日时段表切换冻结*/
	{CR_Free_OADTab,		CR_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Immid_Init,	2,		C_RelatedOAD_Immid_InitLen	,0x0A},			/*698-费率电价切换冻结*/
	{CL_Free_OADTab,		CL_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Immid_Init,	2,		C_RelatedOAD_Immid_InitLen	,0x0B},			/*698-阶梯切换冻结*/
};
#define	C_Freeze_OIBTableLen       ( sizeof(Freeze_OIBTable) / sizeof(Freeze_OIBTable[0]) )

/*************************安全模式字表格结构体*********/
typedef struct
{
	ushort16	DI;											/*标识码*/
	ushort16	Mode;										/*模式字*/
}Str_Safe_Type1;
typedef struct
{
	ushort16	DI;											/*标识码*/
	ushort16	DefaultDI;									/*标识码*/
	ushort16	Mode;										/*模式字*/
}Str_Safe_Type2;

#define	C_Read							0x01				/*读取*/
#define	C_SetUp							0x02				/*设置*/
#define	C_Operation						0x04				/*操作*/

//#define	C_Read_PlainText				0x8000			/*读取-明文*/
#define	C_Read_PlainText				0xF000				/*读取-明文*/
#define	C_Read_PlainTextMac				0x4000				/*读取-明文+MAC*/
#define	C_Read_CipherText				0x2000				/*读取-密文*/
#define	C_Read_CipherTextMac			0x1000				/*读取-密文+MAC*/

//#define	C_SetUp_PlainText			    0x0800			/*设置-明文*/
#define	C_SetUp_PlainText				0x0F00				/*设置-明文*/
#define	C_SetUp_PlainTextMac			0x0400				/*设置-明文+MAC*/
#define	C_SetUp_CipherText				0x0200				/*设置-密文*/
#define	C_SetUp_CipherTextMac			0x0100				/*设置-密文+MAC*/

//#define	C_Operation_PlainText			0x0080			/*操作-明文*/
#define	C_Operation_PlainText			0x00F0				/*操作-明文*/
#define	C_Operation_PlainText_Only		0x0080				/*操作-纯明文*/
#define	C_Operation_PlainTextMac		0x0040				/*操作-明文+MAC*/
#define	C_Operation_CipherText			0x0020				/*操作-密文*/
#define	C_Operation_CipherTextMac		0x0010				/*操作-密文+MAC*/
const	Str_Safe_Type1	GV_SafeModeParameters1[]=
{
	{CWalletFile_698,				C_Read_PlainText																			},					/*698-当前钱包文件*/
	{CDrive_Report_698,				C_Read_PlainTextMac																			},					/*698-电能表主动上报*/
#if 0                                                                                                                       	  					
	{CDate_Week_698,				C_Read_PlainText|C_SetUp_CipherTextMac|C_Operation_PlainText								},					/*日期时间*/
#endif                                                                                                                              				
	{CDate_Week_698,				C_Read_PlainText|C_SetUp_CipherTextMac|C_Operation_PlainText_Only|C_Operation_CipherTextMac	},					/*日期时间*/
	{CComm_Address_698,				C_Read_PlainText|C_SetUp_CipherTextMac														},					/*通信地址*/
	{CMeter_Num_698,				C_Read_PlainText|C_SetUp_PlainTextMac														},					/*表号*/
	{CCustomer_Num_698,				C_Read_PlainTextMac|C_SetUp_PlainTextMac													},					/*客户编号*/
	{CSoftw_Record_Number_698,		C_Read_PlainText|C_SetUp_CipherTextMac														},					/*软件备案号*/
	{CFrameTransmission_698,		C_Read_PlainText|C_SetUp_CipherTextMac|C_Operation_CipherTextMac							},					/*分帧传输*/
	{CBlockTransmission_698,		C_Read_PlainText|C_SetUp_CipherText|C_Operation_CipherText									},					/*分块传输*/
	{CExtTransmission_698,			C_Read_PlainText|C_SetUp_PlainText|C_Operation_PlainText									},					/*扩展传输*/
	{CESAM_698,						C_Read_PlainText|C_SetUp_PlainTextMac|C_Operation_CipherTextMac								},					/*ESAM*/
	{CSafeModeParameters_698,		C_Read_PlainText|C_SetUp_CipherTextMac|C_Operation_CipherText								},					/*安全模式参数*/
	{0x5000,						C_Read_PlainTextMac|C_SetUp_CipherTextMac|C_Operation_PlainTextMac							},					/*698-瞬时冻结*/
	{CM_Com_Ac_Tol_En_698,			C_Read_PlainText																			},					/*698-月度用电量*/
	{CStep_Com_Ac_Tol_En_698,		C_Read_PlainText																			},					/*698-阶梯结算用电量*/
	{CExtern_OIFF86_698,			C_Read_PlainText|C_Operation_PlainText														},					/*698-自扩对象FF86，仅支持扩展方法明文方法*/
};
#define	GV_SafeModeParameters1Len (sizeof(GV_SafeModeParameters1)/sizeof(Str_Safe_Type1))
const Str_Safe_Type2 GV_SafeModeParameters2[]=
{
	{0x0fff,	0x0fff,		C_Read_PlainText													},													/*698-当前电能*/
	{0x1fff,	0x0fff,		C_Read_PlainTextMac													},													/*698-最大需量*/
	{0x2fff,	0x0fff,		C_Read_PlainTextMac|C_SetUp_CipherTextMac|C_Operation_PlainTextMac|C_Operation_CipherText|C_Operation_CipherTextMac},	/*698-变量*/
	{0x3fff,	0x0fff,		C_Read_PlainTextMac|C_SetUp_CipherTextMac|C_Operation_CipherTextMac	},													/*698-事件*/
	{0x4fff,	0x0fff,		C_Read_PlainTextMac|C_SetUp_CipherTextMac|C_Operation_CipherTextMac	},													/*698-参变量*/
//	{0x50ff,	0x00ff,		C_Read_PlainTextMac|C_SetUp_CipherTextMac							},													/*698-冻结*/
	{0x50ff,	0x00ff,		C_Read_PlainTextMac|C_SetUp_CipherTextMac|C_Operation_CipherTextMac	},													/*698-冻结*/
	{0x60ff,	0x00ff,		C_Read_PlainText|C_SetUp_PlainText|C_Operation_PlainText			},													/*698-采集监控*/
	{0x70ff,	0x00ff,		C_Read_PlainText|C_Operation_PlainText								},													/*698-集合*/
	{0x80ff,	0x00ff,		C_Read_PlainTextMac|C_SetUp_CipherTextMac|C_Operation_CipherTextMac	},													/*698-控制*/
	{0xF2ff,	0x00ff,		C_Read_PlainText|C_SetUp_PlainText|C_Operation_PlainText			},													/*698-输入输出设备*/
	{0xFFff,	0x00ff,		C_Read_PlainText|C_SetUp_PlainText|C_Operation_PlainText			},													/*698-自定义*/
};
#define	GV_SafeModeParameters2Len (sizeof(GV_SafeModeParameters2)/sizeof(Str_Safe_Type2))


//*************************************类定义*********************************************
#define	C_Static			0x00								/*静态*/
#define	C_Dynamic			0x01								/*动态*/
typedef struct                                          		
{                                                       		
	uchar8		Conversion;										/*换算*/
	uchar8		Unit;											/*单位*/
}Str_ConandUnit;                                        		
                                                        		
                                                        		
typedef struct                                          		
{                                                       		
	uchar8	Err_645;											/*645错误定义*/
	uchar8	Err_698;											/*698错误定义*/
}Str_698And645_ErrSwich;
const Str_698And645_ErrSwich GV_698And645_ErrSwich[] =
{
	{C_RateNum_OV,			C_RateNum_OV_DAR		},			/*费率数超*/
	{C_PeriodNum_OV,		C_PeriodNum_OV_DAR		},			/*日时段数超*/
	{C_SeasonNum_OV,		C_SeasonNum_OV_DAR		},			/*年时区数超*/
	{C_Baud_NotModified,	C_Baud_NotModified_DAR	},			/*通信速率不能更改*/
	{C_Unauthorized,		C_RWForbid_DAR  		},			/*未授权/密码错*/
	{C_No_Request_data,		C_ObjectNotExist_DAR	},			/*无请求数据  -698对象不存在*/
	{C_OtherErr,			C_OtherErr_DAR			},			/*其他错误*/
//	{C_OK,					C_OK_DAR				},			/*成功*/
	{C_IDError,				C_ObjectNotExist_DAR	},			/*数据标识错   */
	{C_NoAccess,			C_Unauthorized_DAR		},			/*无权限     */
	{C_SERR_FWAddressErr,	C_FWAddressErr_DAR		},			/* 地址异常 */
	{C_ObjectTypeErr_DAR,	C_ObjectTypeErr_DAR		},			/* 接口类错误 */
};
#define	GV_698And645_ErrSwichLen ( sizeof(GV_698And645_ErrSwich) / sizeof(Str_698And645_ErrSwich) )

#define	C_ESAMLCError						0x23				/*ESAM的LC错误*/

/*单个645标识码对应的最大显示屏数*/
#define	C_DemandDispScreenNum				3 					/*最大需量*/
#define	C_TZoneDispScreenNum				14					/*时段表*/
                                                    								
#define	C_WriteEventRecord					0x68				/*写事件记录*/
#define	C_ReadDate							0x86				/*读数据写数据层*/
#define	C_NeedWriteEventRecord				0xAA				/*写总的编程记录*/
#define	C_NotWriteEventRecord				0x55				/*不写总的编程记录*/


/*事件清零标识码对应*/
typedef struct
{
	uchar8	V_OIB;
	ulong32 V_DI;												/*事件记录数据标示**/
}Str_EvenClearTable;
//#define C_EventDI 0x000000FF

const Str_EvenClearTable  Str_EvenClearTable698To645[]=               /*不包含电表清零记录及事件清零记录，类似DI1有分项标识码事件，分项事件清零时该标识码为FF，即块操作*/
{//	OIB
	{CLoss_Vol_OIB,						(CLossAVol_FF_1|C_EventDI)},					/*698-失压*/
	{CLow_Vol_OIB,						(CLowAVol_FF_1|C_EventDI)},						/*698-欠压*/
	{COver_Vol_OIB,						(COverAVol_FF_1|C_EventDI)},					/*698-过压*/
	{CBreak_Vol_OIB,					(CBreakAVol_FF_1|C_EventDI)},					/*698-断相*/
	{CLoss_Curr_OIB,					(CLossACurr_FF_1|C_EventDI)},					/*698-失流*/
	{COver_Curr_OIB,					(COverACurr_FF_1|C_EventDI)},					/*698-过流*/
	{CBreak_Curr_OIB,					(CBreakACurr_FF_1|C_EventDI)},					/*698-断流*/
//	{CTrend_Rev_OIB,					(CTrend_Rev_Note_1|C_EventDI)},					/*698-潮流反向*/
	{CTrend_Rev_OIB,					(CPowerTRev_FF_1|C_EventDI)},					/*698-功率反向*/        
	{COver_Lo_OIB,						(COverALo_FF_1|C_EventDI)},						/*698-过载*/
	{CPos_De_Over_OIB,					(CPos_Ac_De_Over_Note_1|C_EventDI)},			/*698-电能表正向有功需量超限事件*/
	{CRe_De_Over_OIB,					(CRev_Ac_De_Over_Note_1|C_EventDI)},			/*698-电能表反向有功需量超限事件*/
	{CRe_ReDe_Over_OIB,					(CQua1_Re_De_Over_Note_1|C_EventDI)},			/*698-电能表无功需量超限事件*/
	{CPFactorT_Over_OIB,				(CPFactorT_FF_1|C_EventDI)},					/*698-电能表功率因数超下限事件*/
	{CAll_Loss_Vol_OIB,					(CAll_Loss_Vol|C_EventDI)},						/*698-电能表全失压事件*/
	{CAux_Pow_Down_OIB,					(CAux_Pow_Down|C_EventDI)},						/*698-电能表辅助电源失电事件*/
	{CRevPS_Vol_OIB,					(CRevPSVol_FF_1|C_EventDI)},					/*698-电能表电压逆相序事件*/
	{CRevPS_Curr_OIB,					(CRevPSCurr_FF_1|C_EventDI)},					/*698-电能表电流逆相序事件*/
	{CPow_Down_OIB,						(CPow_Down_Degree|C_EventDI)},					/*698-电能表掉电事件*/
	{CProgram_OIB,						(CProgram_Degree|C_EventDI)},					/*698-电能表编程事件*/
	{CTol_Clear_OIB,					(CTol_Clear_Degree|C_EventDI)},					/*698-电能表清零事件*/
	{CDe_Clear_OIB,						(CDe_Clear_Degree|C_EventDI)},					/*698-电能表需量清零事件*/
	{CEven_Clear_OIB,					(CEven_Clear_Degree|C_EventDI)},				/*698-电能表事件清零事件*/
	{CAdjTime_OIB,						(CAdjTime_Degree|C_EventDI)},					/*698-电能表校时事件*/
	{CProgPT_OIB,						(CProgPT_Degree|C_EventDI)},					/*698-电能表时段表编程事件*/
	{CProgTZ_OIB,						(CProgTZ_Degree|C_EventDI)},					/*698-电能表时区表编程事件*/
	{CProgWRe_OIB,						(CProgWRe_Degree|C_EventDI)},					/*698-电能表周休日编程事件*/
	{CProgSettD_OIB,					(CProgSettD_Degree|C_EventDI)},					/*698-电能表结算日编程事件*/
	{COpenW_OIB,						(COpenW_Degree|C_EventDI)},						/*698-电能表开盖事件*/
	{COpenCW_OIB,						(COpenCW_Degree|C_EventDI)},					/*698-电能表开端钮盖事件*/
	{CNoBal_Vol_OIB,					(CNoBalVol_FF_1|C_EventDI)},					/*698-电能表电压不平衡事件*/
	{CNoBal_Curr_OIB,					(CNoBalCurr_FF_1|C_EventDI)},					/*698-电能表电流不平衡事件*/
	{CRelayOpen_OIB,					(CRelayOpen_FF_1|C_EventDI)},					/*698-电能表跳闸事件*/
	{CRelayClose_OIB,					(CRelayClose_FF_1|C_EventDI)},					/*698-电能表合闸事件*/
	{CProgHol_OIB,						(CProgHol_Degree|C_EventDI)},					/*698-电能表节假日编程事件*/
	{CProgAcC_OIB,						(CProgAcC_Degree|C_EventDI)},					/*698-电能表有功组合方式编程事件*/
	{CProgReC_OIB,						(CProgReC_Degree|C_EventDI)},					/*698-电能表无功组合方式编程事件*/
	{CProgTPara_OIB,					(CProgTPara_Degree|C_EventDI)},					/*698-电能表费率参数表编程事件*/
	{CProgLad_OIB,						(CProgLad_Degree|C_EventDI)},					/*698-电能表阶梯表编程事件*/
	{CKey_Update_OIB,					(CProgKD_Degree|C_EventDI)},					/*698-电能表密钥更新事件*/
	{CAbnorC_OIB,						(CAbnorC_Degree|C_EventDI)},					/*698-电能表异常插卡事件*/
	{CBuyCurr_OIB,						(CBuyCurr_FF_Note_1|C_EventDI)},				/*698-电能表购电事件*/
	{CReturn_M_OIB,						(CReturn_M_Degree|C_EventDI)},					/*698-电能表退费事件*/
	{CConM_OIB,							(CConM_Degree|C_EventDI)},						/*698-电能表恒定磁场干扰事件*/
	{CRelayFa_OIB,						(CRelayFa_Degree|C_EventDI)},					/*698-电能表负荷开关误动作事件*/
	{CPowerFa_OIB,						(CPowerFa_Degree|C_EventDI)},					/*698-电能表电源异常事件*/
	{CSevNoBal_Curr_OIB,				(CSevNoBalCurr_FF_1|C_EventDI)},				/*698-电能表电流严重不平衡事件*/
	{CClock_FaultState_OIB,				(CClockFa|C_EventDI)},							/*698-电能表时钟故障事件*/
	{CMeteringChipFault_OIB,			(CMeterFa|C_EventDI)},							/*698-电能表计量芯片故障事件*/
	{CBroadcastTime_OIB,				(CBroadcastTime_Degree|C_EventDI)},				/*698-电能表广播校时事件*/
    {CNeutralCurrentAbnormal_OIB,		(CNeutralCurrentAbnormal_Note_1|C_EventDI)},	/*698-电能表零线电流异常事件*/
};
#define Str_EvenClearTable698To645_Len  ( sizeof(Str_EvenClearTable698To645) / sizeof(Str_EvenClearTable) )
extern uchar8 SF_DriveReportSet_Change (uchar8 Type, uchar8 *pData, uchar8 DataLenth );



#define	C_CleanOtherEvent				0x68
#define	C_JustAddECleanNo				0x86
#define	C_EventMAXRelatedOAD			60

ulong32	SV_ReadAfterSetTimer;

typedef struct
{
	uchar8	EventNo;											/*事件号*/
	uchar8	WriteBit;											/*写状态字位*/
}Str_OtherEventMapping_Type;

#define	C_EndTimeOffset					(1 + 7)					/*类7 时间状态记录表，结束时间偏移*/

uchar8	SF_ReadAfterSetForPerDI( uchar8 *P_ucData, ulong32 V_ulDI, uchar8 V_ucDILen );
uchar8	SF_Read_TZone_PTReg( uchar8 *P_ucData, ulong32	LimitDI, ulong32	V_ulDI );
uchar8 Action_Service_PerOI( Str_Comm_698_RW *pV_698RWPara, Str_Comm_645 *pV_645Frame );
void Action_Service_MultiOI( Str_Comm_698_RW *pV_698RWPara, Str_Comm_645 *pV_645Frame );
uchar8 ActionRd_Service_MultiOI( Str_Comm_698_RW *pV_698RWPara, uchar8 *pV_DataBuf, uchar8 V_BufLen, uchar8 *pV_NextFrFlag, Str_Comm_645 *pV_645Frame );
void SF_DemandClear( void );
void	SF_MeterInit( void );
void	SF_MeterClear( Str_Comm_645 *pV_645Frame );
uchar8 SF_EventClear( Str_Comm_645 *pV_645Frame, ulong32 V_ulOAD );
uchar8 SF_FreezingOrder_C16( Str_Comm_645 *pV_645Frame );
uchar8	SF_BroadcastSetClock( Str_Comm_645 *pV_645Frame );
void SF_CombDataTo645Type_W( uchar8 *P_698Data, Str_Comm_645 *pV_645Frame, uchar8 V_Len_645 );
uchar8 SF_SetParm( Str_Comm_645 *pV_645Frame, ulong32 V_ulLastDI, ulong32 V_ulNextDI, uchar8 V_WriteEventFlag, ulong32 V_ulProgOAD, uchar8 OperationFlag );
void		Have_IPEvent_Prog_698( ulong32 V_ulProgOAD, ulong32 V_ulProgTimesOAD, Str_Comm_645 *pV_645Frame );
uchar8 SF_ActionPerOI( Str_Comm_698_RW *pV_698RWPara, Str_Comm_645 *pV_645Frame, uchar8 V_ucOINum );
uchar8 SF_SetPerOI( Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum, Str_Comm_645 *pV_645Frame );
uchar8	SF_ReadAfterSet( Str_Comm_698_RW *pV_698Frame, Str_Comm_645 *pV_645Frame );
uchar8 SF_SetDispPerOI( Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum, Str_Comm_645 *pV_645Frame );
uchar8 SF_GetAPDU_BpsRead( ulong32 V_OAD, uchar8 *P_DataBuf );
uchar8 SF_GetAPDU_ApplianceInOutRead( RdOI_Para_T V_OAD, uchar8 *P_DataBuf, uchar8 V_ucOff, ushort16 *P_DataOff );
ushort16	SF_DataExchangeTo645_BasicData( uchar8 *pV_698data, uchar8 *pV_645data, uchar8 V_ucLen698, uchar8 *V_ucLen645 );

uchar8 SF_FreezeOADRead( RdOI_Para_T V_OAD, uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 V_TimeOADFlay, uchar8 *pV_ArrayNum );
uchar8 SF_JugeRelayOAD( Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum );
uchar8 SF_GetAPDU_DISPRead( RdOI_Para_T V_OAD, uchar8 *P_DataBuf, ushort16 V_ucOff, ushort16 *P_DataOff );
void OneByteReverse( uchar8 *pV_Sourcedata );
uchar8 Comm_SoftwareCampare_698( WtOI_Rt_T V_OAD, uchar8 *V_ucBuff, ushort16 *V_Len );
void SF_GetPow_Down_Time( uchar8 *P_DataBuf );
uchar8 SF_SetHolidyPerOI( Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum, Str_Comm_645 *pV_645Frame );
uchar8 SF_GetAPDU_HolidyRead( RdOI_Para_T *V_OAD, uchar8 *P_DataBuf, ushort16 V_ucOff, uchar8 V_DINum, ushort16 *P_DataOff );
uchar8 SF_EventOADRead( RdOI_Para_T V_OAD, uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 V_TimeOADFlay, uchar8 *pV_ArrayNum );
uchar8 SF_EventClear_698( ulong32 V_ulOAD, Str_Comm_645 *pV_645Frame, uchar8 V_ProgFlag );
uchar8	JudgeMeterType( ulong32 V_ulOAD );
uchar8	SF_Judge_SetServiceRight( ushort16 V_OI, ushort16 *V_ulMode );
ushort16	SF_DataExchangeTo698_BasicData( uchar8 *pV_698data, uchar8 *pV_645data, uchar8 V_ucLen698, uchar8 V_ucLen645 );
uchar8 SF_Judge_OINature( Str_Comm_698_RW *pV_698RWPara, Str_Type645DI_Class *P_DIFor645, uchar8 *P_645DINum, uchar8 OperationMode );
void CommMSg_StartTxd_698( uchar8 CommNo );
uchar8 SF_LocalAndRemoteMeterDiJudge( ulong32 V_Di );
uchar8 SF_JugeSameOI( ushort16 V_ulOI );
uchar8 InF_Display_JudgeIDActive( ulong32 V_ulCodeID, ulong32 V_ulRelatedCodeID, uchar8 V_ucScreenNum );
uchar8 SF_JudgeSameRealatedOAD( uchar8 *P_RealatedOADTab, uchar8 *P_AddOAD, uchar8 V_ucRealatedOADNum, uchar8 V_ucOIFlag );
uchar8 SF_JudgeSameRealatedOADCycle (uchar8 *P_RealatedOADTab,uchar8 *P_AddOAD,uchar8 V_ucRealatedOADNum,uchar8 V_ucOIFlag);
uchar8 SF_JudgeSameRealatedOADStoreNum( uchar8 *P_RealatedOADTab, uchar8 *P_AddOAD, uchar8 V_ucRealatedOADNum, uchar8 V_ucOIFlag );
uchar8 SF_JudgeAllAA( uchar8 *P_DataBuf, uchar8 P_DataLen );
uchar8 SF_GetChannelVaild( uchar8 V_usChannel );
void SF_Encode_VolRates( Struct_FrozenConvert_Type *pStr_Encode, uchar8 *pDataBuf, uchar8 *pData645Buf, ushort16 *pV_DataOff, ushort16 *pV_DataOff645 );
uchar8 SF_Judge_Para( Str_Comm_698_RW *pV_698RWPara, Str_Type645DI_Class *V_DIFor645, uchar8 V_uc645DINum, uchar8 V_ucOINum );
uchar8 SF_PrograReactivePowerState( ulong32 V_Data_Id_OAD, uchar8 *P_DataBuf, ushort16 *V_Len );
void RELEASE_Service_Deal( uchar8 Client_Addr );
void SF_GetCommChanelCurrentLen( uchar8	V_ucChanelNo );
uchar8 SF_DataLen_AXDR_Encode( uchar8 *pV_DataBuf,ushort16 V_DataLen );
void SF_OverAPDU_DealWith( uchar8 *pV_return, ushort16 *pV_DataOff, ushort16 V_LastDataOff, uchar8 *pV_NextTimeNew, uchar8 *pV_NextTimeOld );
void SF_RenewRelayControlStutas( void );
void SF_DeletReport( uchar8 channel, uchar8 EventNo );
uchar8 InF_RateNumChangeToHex( void );
extern void SF_SetRTCErrState( uchar8 V_ucRTCFlag );
extern uchar8 Inf_ReadEventLast_N( ulong32 * P_Data_Id_OAD, uchar8 * P_FixTime, uchar8 * P_Data, uchar8 * V_NextSign, ushort16 * P_Data_Length, uchar8 V_timeFlash );

/*2020标准主动上报2005*/
void Inf_DeletReport( uchar8 channel, uchar8 EventNo );


void Inf_DealReportNum( uchar8 *p_EventNo, uchar8 Len );
ushort16 Inf_Comm_REPORTFlag( void );
uchar8 Inf_Comm_REPORTFlagClear( uchar8 ClearMode );

uchar8 Is_ID_Comm_ResponseErr_698( Str_Comm_645 * pV_698Frame, Str_Comm_698_RW *pV_698RWPara );

void SF_Event_Relay_JudgeAll00( ulong32 V_ulOAD, uchar8 *p_VFlag );

///698兼容645协议，标识码表格转换
#define C_FreezNumHig							0x01							/*冻结序号高位偏移*/
#define C_FreezCycleLow							0x02							/*冻结周期低位偏移*/
#define C_FreezCycleHig							0x03							/*冻结周期高位偏移*/
///698兼容645增加                                                           	
#define		C_MinFreez							1								/*Freeze_OIBTable表格中分钟冻结位置*/
#define		C_RelatedOADTabLen					6								/*关联列表存储格式：2字节序号+2字节冻结周期+2字节存储深度*/
                                                                            	
#define		C_TolLoss_CurrOffsetA				0								/*698数据中全失压A相电流值数据偏移*/
#define		C_TolLoss_CurrOffsetB				3								/*698数据中全失压B相电流值数据偏移*/
#define		C_TolLoss_CurrOffsetC				6								/*698数据中全失压C相电流值数据偏移*/
#define		C_TolLoss_CurrOffsetASign			(C_TolLoss_CurrOffsetA + 2)		/*698数据中全失压A相电流值符号位偏移*/
#define		C_TolLoss_CurrOffsetBSign			(C_TolLoss_CurrOffsetB + 2)		/*698数据中全失压B相电流值符号位偏移*/
#define		C_TolLoss_CurrOffsetCSign			(C_TolLoss_CurrOffsetC + 2)		/*698数据中全失压C相电流值符号位偏移*/



#define		C_RelayFa_State_Offset				5								/*698数据中负荷开关误动作时负荷开关状态数据偏移位置*/
#define		C_MeterStatus_Relay_Offset			3								/*698确认跟随上报状态字，跳合闸所在字节在通信中的偏移*/
#define		C_MeterStatus_Offset				2								/*698确认跟随上报状态字，在字节在通信中的偏移 */
#define		C_MeterStatus_EventNum				4								/*跟随上报状态字需处理的事件个数（目前只支持跳闸、合闸+停抄电池欠压和时钟电池欠压）	*/
#define		C_BitNum0							0								/*字节计算起始	*/
#define		C_MeterStatus_RelayWord_Offset		1								/*698中跳合闸在跟随上报状态字中的所在字节	*/

#define		C_PTNum_Offset						19								/*时段表编程记录中，写的是第几套时段表，所在的位置，即401702XX，XX的位置*/
#define		C_PTData_Offset						23								/*时段表编程记录中，数据所在的位置*/
#define		C_PTProgEventNum					4								/*时段表事件记录，645协议数据存储时，数据块中存储时段表的个数*/
#define		C_TZData_offset_645					6								/*时区表事件记录，645协议，数据所在位置*/


typedef struct
{
	ulong32	RelateOAD_645;														/*关联属性列表的OAD，按645读取顺序*/
	uchar8  ReadFlag;															/*是否需要进行分相读取的标志*/
	uchar8  DataLen;															/*数据长度	*/
}Str_EventChange_Table2;


typedef struct
{
	ulong32	DI;																	/*645DI*/
	uchar8	OIB;																/*OIB,698标识码*/
	uchar8	Nature;																/*Nature,698标识码*/
	ulong32	PStr_EventChange_Table2;											/*结构体首地址*/
	uchar8	TableLen;															/*对应2级表格总个数*/
}Str_EventChange_Table1;


#define C_ReadDeal_A							0x01							/*需要读取后处理数据，如电压、电流, A相,(功率、功率因数、安时数对应总)  */
#define C_ReadDeal_B							0x02							/*需要读取后处理数据，如电压、电流, B相,(功率、功率因数、安时数对应A)*/
#define C_ReadDeal_C							0x03							/*需要读取后处理数据，如电压、电流, C相,(功率、功率因数、安时数对应B)*/
#define C_ReadDeal_D							0x04							/*(功率、功率因数、安时数对应C)*/
#define C_ReadDeal_E							0x05							/*全失压电流值处理*/
#define C_ReadDeal_F							0x06							/*负荷开关误动作时状态处理*/
#define C_ReadDeal_G							0x07							/*时区表编程数据处理*/
#define C_NormalRead							0x00							/*不需要读取后处理数据，如电能*/
                                                            					
#define C_EventHappen							0x00002000						/*事件发生时刻*/
#define C_EventHappening						0x00006000						/*事件发生期间*/
#define C_EventEnd								0x00008000						/*事件结束时刻*/
#define C_OADNum								0x03 							/*OAD个数 ，1个个读取，0：事件的OAD；1：关联的OAD；2:全FFFFFFFF*/


/*表格顺序请勿随意调整*/
const Str_EventChange_Table2 EventTable2_RelateOAD0405[] =  /**********过流/失流关联属性列表***************/
{
/*对应的698关联属性列表                  索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻	645   6字节*/                                      	
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	正向有功总电能*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	反向有功总电能*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	组合无功1总电能*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	组合无功2总电能*/   
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A相正向有功电能*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A相反向有功电能*/   
	{C_HP_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00312201	A相组合无功1总电能*/
	{C_HP_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00412201	A相组合无功2总电能*/
	{(CPhaseFF_Volage|C_EventHappen),		C_ReadDeal_A,				CLPhaseA_Volage},					/*0x20002200	*/
	{(CPhaseFF_Curr|C_EventHappen),			C_ReadDeal_A,				CLPhaseA_Curr},						/*0x20012200	*/
	{(CInstantFF_AcPow|C_EventHappen),		C_ReadDeal_B,				CLInstantA_AcPow},					/*0x20042200	*/
	{(CInstantFF_RePow|C_EventHappen),		C_ReadDeal_B,				CLInstantA_AcPow},					/*0x20052200	*/
	{(CPhaseFF_PowerFactor|C_EventHappen),	C_ReadDeal_B,				CLPhaseA_PowerFactor},				/*0x200A2200	*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B相正向有功电能*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B相反向有功电能*/   
	{C_HP_BComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00322200	B相组合无功1总电能*/
	{C_HP_BComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00422200	B相组合无功2总电能*/
	{(CPhaseFF_Volage|C_EventHappen),		C_ReadDeal_B,				CLPhaseA_Volage},					/*0x20002200	*/
	{(CPhaseFF_Curr|C_EventHappen),			C_ReadDeal_B,				CLPhaseA_Curr},						/*0x20012200	*/
	{(CInstantFF_AcPow|C_EventHappen),		C_ReadDeal_C,				CLInstantA_AcPow},					/*0x20042200                       */
	{(CInstantFF_RePow|C_EventHappen),		C_ReadDeal_C,				CLInstantA_AcPow},					/*0x20052200	*/
	{(CPhaseFF_PowerFactor|C_EventHappen),	C_ReadDeal_C,				CLPhaseA_PowerFactor},				/*0x200A2200	*/
	{C_HP_CPosAcEn ,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C相正向有功电能*/   
	{C_HP_CRevAcEn ,						C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C相反向有功电能*/   
	{C_HP_CComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00330200	C相组合无功1总电能*/
	{C_HP_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C相组合无功2总电能*/
	{(CPhaseFF_Volage|C_EventHappen),		C_ReadDeal_C,				CLPhaseA_Volage},					/*0x20002200	*/
	{(CPhaseFF_Curr|C_EventHappen),			C_ReadDeal_C,				CLPhaseA_Curr},						/*0x20012200	*/
	{(CInstantFF_AcPow|C_EventHappen),		C_ReadDeal_D,				CLInstantA_AcPow},					/*0x20042200	*/
	{(CInstantFF_RePow|C_EventHappen),		C_ReadDeal_D,				CLInstantA_AcPow},					/*0x20052200	*/
	{(CPhaseFF_PowerFactor|C_EventHappen),	C_ReadDeal_D,				CLPhaseA_PowerFactor},				/*0x200A2200	*/
	{(CEventEndTime),						C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200	事件结束时刻645 6字节*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00100200	正向有功总电能*/        
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00200200	反向有功总电能*/        
	{C_End_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00300200	组合无功1总电能*/   
	{C_End_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00400200	组合无功2总电能*/   
	{C_End_APosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00110200	A相正向有功电能*/   
	{C_End_ARevAcEn,						C_NormalRead,				CLPosA_Ac_En_0	},					/*0x00210200	A相反向有功电能*/   
	{C_End_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00310200	A相组合无功1总电能*/
	{C_End_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00410200	A相组合无功2总电能*/
	{C_End_BPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00122200	B相正向有功电能*/   
	{C_End_BRevAcEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00222200	B相反向有功电能*/   
	{C_End_BComRe1En,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00322200	B相组合无功1总电能*/
	{C_End_BComRe2En,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00422200	B相组合无功2总电能*/
	{C_End_CPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00130200	C相正向有功电能*/   
	{C_End_CRevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00230200	C相反向有功电能*/   
	{C_End_CComRe1En,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00330200	C相组合无功1总电能*/
	{C_End_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C相组合无功2总电能*/
};
#define EventTable2_RelateOAD0405_Len  ( sizeof(EventTable2_RelateOAD0405) / sizeof(Str_EventChange_Table2) )
/*表格顺序请勿随意调整*/
const Str_EventChange_Table2 EventTable2_RelateOAD00[] =  /**********失压/欠压/过压关联属性列表***************/
{
/*对应的698关联属性列表                  索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻 645   6字节*/                                      	
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	正向有功总电能*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	反向有功总电能*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	组合无功1总电能*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	组合无功2总电能*/   
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A相正向有功电能*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A相反向有功电能*/   
	{C_HP_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00312201	A相组合无功1总电能*/
	{C_HP_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00412201	A相组合无功2总电能*/
	{(CPhaseFF_Volage|C_EventHappen),		C_ReadDeal_A,				CLPhaseA_Volage},					/*0x20002200	*/
	{(CPhaseFF_Curr|C_EventHappen),			C_ReadDeal_A,				CLPhaseA_Curr},						/*0x20012200	*/
	{(CInstantFF_AcPow|C_EventHappen),		C_ReadDeal_B,				CLInstantA_AcPow},					/*0x20042200	*/
	{(CInstantFF_RePow|C_EventHappen),		C_ReadDeal_B,				CLInstantA_AcPow},					/*0x20052200	*/
	{(CPhaseFF_PowerFactor|C_EventHappen),	C_ReadDeal_B,				CLPhaseA_PowerFactor},				/*0x200A2200	*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B相正向有功电能*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B相反向有功电能*/   
	{C_HP_BComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00322200	B相组合无功1总电能*/
	{C_HP_BComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00422200	B相组合无功2总电能*/
	{(CPhaseFF_Volage|C_EventHappen),		C_ReadDeal_B,				CLPhaseA_Volage},					/*0x20002200	*/
	{(CPhaseFF_Curr|C_EventHappen),			C_ReadDeal_B,				CLPhaseA_Curr},						/*0x20012200	*/
	{(CInstantFF_AcPow|C_EventHappen),		C_ReadDeal_C,				CLInstantA_AcPow},					/*0x20042200	*/
	{(CInstantFF_RePow|C_EventHappen),		C_ReadDeal_C,				CLInstantA_AcPow},					/*0x20052200	*/
	{(CPhaseFF_PowerFactor|C_EventHappen),	C_ReadDeal_C,				CLPhaseA_PowerFactor},				/*0x200A2200	*/
	{C_HP_CPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C相正向有功电能*/   
	{C_HP_CRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C相反向有功电能*/   
	{C_HP_CComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00330200	C相组合无功1总电能*/
	{C_HP_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C相组合无功2总电能*/
	{(CPhaseFF_Volage|C_EventHappen),		C_ReadDeal_C,				CLPhaseA_Volage},					/*0x20002200	*/
	{(CPhaseFF_Curr|C_EventHappen),			C_ReadDeal_C,				CLPhaseA_Curr},						/*0x20012200	*/
	{(CInstantFF_AcPow|C_EventHappen),		C_ReadDeal_D,				CLInstantA_AcPow},					/*0x20042200	*/
	{(CInstantFF_RePow|C_EventHappen),		C_ReadDeal_D,				CLInstantA_AcPow},					/*0x20052200	*/
	{(CPhaseFF_PowerFactor|C_EventHappen),	C_ReadDeal_D,				CLPhaseA_PowerFactor},				/*0x200A2200	*/
	{(C_AhNature2|C_EventHappening),		C_ReadDeal_A,				4},									/*0x20292200	*/
	{(C_AhNature2|C_EventHappening),		C_ReadDeal_B,				4},									/*0x20296200	*/
	{(C_AhNature2|C_EventHappening),		C_ReadDeal_C,				4},									/*0x20296200	*/
	{(C_AhNature2|C_EventHappening),		C_ReadDeal_D,				4},									/*0x20296200	*/
	{(CEventEndTime),						C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200	事件结束时刻645 6字节*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00100200	正向有功总电能*/        
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00200200	反向有功总电能*/        
	{C_End_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00300200	组合无功1总电能*/   
	{C_End_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00400200	组合无功2总电能*/   
	{C_End_APosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00110200	A相正向有功电能*/   
	{C_End_ARevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00210200	A相反向有功电能*/   
	{C_End_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00310200	A相组合无功1总电能*/
	{C_End_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00410200	A相组合无功2总电能*/
	{C_End_BPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00122200	B相正向有功电能*/   
	{C_End_BRevAcEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00222200	B相反向有功电能*/   
	{C_End_BComRe1En,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00322200	B相组合无功1总电能*/
	{C_End_BComRe2En,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00422200	B相组合无功2总电能*/
	{C_End_CPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00130200	C相正向有功电能*/   
	{C_End_CRevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00230200	C相反向有功电能*/   
	{C_End_CComRe1En,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00330200	C相组合无功1总电能*/
	{C_End_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C相组合无功2总电能*/
};
#define EventTable2_RelateOAD00_Len  ( sizeof(EventTable2_RelateOAD00) /sizeof(Str_EventChange_Table2) )
/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD1B[] =  /**********开表盖关联属性列表***************/
{
/*对应的698关联属性列表                  索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0200	事件发生时刻*/
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200	事件结束时刻*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102200	正向有功总电能*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202200	反向有功总电能*/
	{C_Hp_TQuadrant1En,						C_NormalRead,				CLQua1_Re_T1_En_0},					/*0x00502201	事件发生时刻第一象限无功总电能*/
	{C_Hp_TQuadrant2En,						C_NormalRead,				CLQua1_Re_T2_En_0},					/*0x00602201	事件发生时刻第二象限无功总电能*/
	{C_Hp_TQuadrant3En,						C_NormalRead,				CLQua1_Re_T3_En_0},					/*0x00702201	事件发生时刻第三象限无功总电能*/
	{C_Hp_TQuadrant4En,						C_NormalRead,				CLQua1_Re_T4_En_0},					/*0x00802201	事件发生时刻第四象限无功总电能*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00108201	事件结束时刻正向有功总电能*/   
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00208201	事件结束时刻反向有功总电能*/   
	{C_End_TQuadrant1En,					C_NormalRead,				CLQua1_Re_T1_En_0},					/*0x00508201	事件结束时刻第一象限无功总电能*/
	{C_End_TQuadrant2En,					C_NormalRead,				CLQua1_Re_T2_En_0},					/*0x00608201	事件结束时刻第二象限无功总电能*/
	{C_End_TQuadrant3En,					C_NormalRead,				CLQua1_Re_T3_En_0},					/*0x00708201	事件结束时刻第三象限无功总电能*/
	{C_End_TQuadrant4En,					C_NormalRead,				CLQua1_Re_T4_En_0},					/*0x00808201	事件结束时刻第四象限无功总电能*/	
};
#define EventTable2_RelateOAD1B_Len  ( sizeof(EventTable2_RelateOAD1B) / sizeof(Str_EventChange_Table2) )
/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD2A[] =  /**********恒定磁场干扰关联属性列表***************/
{
/*对应的698关联属性列表                  索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻*/
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)},				/*0X20200201	事件结束时刻*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	事件发生时刻正向有功总电能*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	事件发生时刻反向有功总电能*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00108201	事件结束时刻正向有功总电能*/   
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00208201	事件结束时刻反向有功总电能*/   
};
#define EventTable2_RelateOAD2A_Len  (sizeof(EventTable2_RelateOAD2A)/sizeof(Str_EventChange_Table2))

/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD11[]=  /**********掉电关联属性列表***************/
{
/*对应的698关联属性列表                  索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)	},				/*0x201E0201	事件发生时刻*/
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)	},				/*0X20200201	事件结束时刻*/
};
#define EventTable2_RelateOAD11_Len  ( sizeof(EventTable2_RelateOAD11) / sizeof(Str_EventChange_Table2) )


/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD2C[] =  /**********电源异常关联属性列表***************/
{
/*对应的698关联属性列表                索引（分相读取标志）	                             	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻*/
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)},				/*0X20200201	事件结束时刻*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	事件发生时刻正向有功总电能*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	事件发生时刻反向有功总电能*/
};
#define EventTable2_RelateOAD2C_Len  ( sizeof(EventTable2_RelateOAD2C) / sizeof(Str_EventChange_Table2) )

/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD1F20[] =  /**********拉闸关联属性列表***************/
{
/*对应的698关联属性列表            索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻*/
	{CRelayOpen_OpeCode_1,					C_NormalRead,				CLRelayOpen_OpeCode_1},				/*0X1D000201	操作者代码*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	事件发生时刻正向有功总电能*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	事件发生时刻反向有功总电能*/
	{C_Hp_TQuadrant1En,						C_NormalRead,				CLQua1_Re_T1_En_0},					/*0x00502201	事件发生时刻第一象限无功总电能*/
	{C_Hp_TQuadrant2En,						C_NormalRead,				CLQua1_Re_T2_En_0},					/*0x00602201	事件发生时刻第二象限无功总电能*/
	{C_Hp_TQuadrant3En,						C_NormalRead,				CLQua1_Re_T3_En_0},					/*0x00702201	事件发生时刻第三象限无功总电能*/
	{C_Hp_TQuadrant4En,						C_NormalRead,				CLQua1_Re_T4_En_0},					/*0x00802201	事件发生时刻第四象限无功总电能*/
};
#define EventTable2_RelateOAD1F20_Len  ( sizeof(EventTable2_RelateOAD1F20) / sizeof(Str_EventChange_Table2) )

/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD13[] =  /**********电表清零关联属性列表***************/
{
/*对应的698关联属性列表  索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻*/
	{CRelayOpen_OpeCode_1,					C_NormalRead,				CLRelayOpen_OpeCode_1},				/*0X1D000201	操作者代码*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	事件发生时刻正向有功总电能*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	事件发生时刻反向有功总电能*/
	{C_Hp_TQuadrant1En,						C_NormalRead,				CLQua1_Re_T1_En_0},					/*0x00502201	事件发生时刻第一象限无功总电能*/
	{C_Hp_TQuadrant2En,						C_NormalRead,				CLQua1_Re_T2_En_0},					/*0x00602201	事件发生时刻第二象限无功总电能*/
	{C_Hp_TQuadrant3En,						C_NormalRead,				CLQua1_Re_T3_En_0},					/*0x00702201	事件发生时刻第三象限无功总电能*/
	{C_Hp_TQuadrant4En,						C_NormalRead,				CLQua1_Re_T4_En_0},					/*0x00802201	事件发生时刻第四象限无功总电能*/
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A相正向有功电能*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A相反向有功电能*/   
	{C_Hp_AQuadrant1En,						C_NormalRead,				CLQua1A_Re_En_0},					/*0x00512201	事件发生时刻A相第一象限无功总电能*/
	{C_Hp_AQuadrant2En,						C_NormalRead,				CLQua2A_Re_En_0},					/*0x00612201	事件发生时刻A相第二象限无功总电能*/
	{C_Hp_AQuadrant3En,						C_NormalRead,				CLQua3A_Re_En_0},					/*0x00712201	事件发生时刻A相第三象限无功总电能*/
	{C_Hp_AQuadrant4En,						C_NormalRead,				CLQua4A_Re_En_0},					/*0x00812201	事件发生时刻A相第四象限无功总电能*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B相正向有功电能*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B相反向有功电能*/   
	{C_Hp_BQuadrant1En,						C_NormalRead,				CLQua1B_Re_En_0},					/*0x00522201	事件发生时刻B相第一象限无功总电能*/ 
	{C_Hp_BQuadrant2En,						C_NormalRead,				CLQua2B_Re_En_0},					/*0x00622201	事件发生时刻B相第二象限无功总电能*/ 
	{C_Hp_BQuadrant3En,						C_NormalRead,				CLQua3B_Re_En_0},					/*0x00722201	事件发生时刻B相第三象限无功总电能*/ 
	{C_Hp_BQuadrant4En,						C_NormalRead,				CLQua4B_Re_En_0},					/*0x00822201	事件发生时刻B相第四象限无功总电能*/ 
	{C_HP_CPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C相正向有功电能*/   
	{C_HP_CRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C相反向有功电能*/   
	{C_Hp_CQuadrant1En,						C_NormalRead,				CLQua1C_Re_En_0},					/*0x00532201	事件发生时刻C相第一象限无功总电能*/
	{C_Hp_CQuadrant2En,						C_NormalRead,				CLQua2C_Re_En_0},					/*0x00632201	事件发生时刻C相第二象限无功总电能*/
	{C_Hp_CQuadrant3En,						C_NormalRead,				CLQua3C_Re_En_0},					/*0x00732201	事件发生时刻C相第三象限无功总电能*/
	{C_Hp_CQuadrant4En,						C_NormalRead,				CLQua4C_Re_En_0},					/*0x00832201	事件发生时刻C相第四象限无功总电能*/
};
#define EventTable2_RelateOAD13_Len  ( sizeof(EventTable2_RelateOAD13) / sizeof(Str_EventChange_Table2) )


/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD14_E1[] =  /**********需量清零关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻*/
	{CRelayOpen_OpeCode_1,					C_NormalRead,				CLRelayOpen_OpeCode_1},				/*0X1D000201	操作者代码*/
	{C_HP_PosAcTolDe,						C_NormalRead,				CLPos_Ac_Tol_De_0},					/*0x10102201	事件发生时刻正向有功最大需量及发生时间*/  
	{C_HP_RevAcTolDe,						C_NormalRead,				CLRev_Ac_Tol_De_0},					/*0x10202201	事件发生时刻反向有功最大需量及发生时间*/ 
	{C_Hp_TQuadrant1De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10502201	事件发生时刻第一象限无功总最大需量及发生时间*/ 
	{C_Hp_TQuadrant2De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10602201	事件发生时刻第二象限无功总最大需量及发生时间*/ 
	{C_Hp_TQuadrant3De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10702201	事件发生时刻第三象限无功总最大需量及发生时间*/
	{C_Hp_TQuadrant4De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10802201	事件发生时刻第四象限无功总最大需量及发生时间*/
};
#define EventTable2_RelateOAD14_E1_Len  ( sizeof(EventTable2_RelateOAD14_E1) / sizeof(Str_EventChange_Table2) )

/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD14_F1[] =  /**********需量清零关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）	*/
	{C_HP_APosAcDe,							C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10112201	事件发生时刻A相正向有功最大需量及发生时间*/
	{C_HP_ARevAcDe,							C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10212201	事件发生时刻A相反向有功最大需量及发生时间*/
	{C_Hp_AQuadrant1De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10512201	事件发生时刻A相第一象限无功总最大需量及发生时间*/
	{C_Hp_AQuadrant2De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10612201	事件发生时刻A相第二象限无功总最大需量及发生时间*/
	{C_Hp_AQuadrant3De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10712201	事件发生时刻A相第三象限无功总最大需量及发生时间*/
	{C_Hp_AQuadrant4De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10812201	事件发生时刻A相第四象限无功总最大需量及发生时间*/
	{C_HP_BPosAcDe,							C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10122201	事件发生时刻B相正向有功最大需量及发生时间*/
	{C_HP_BRevAcDe,							C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10222201	事件发生时刻B相反向有功最大需量及发生时间*/
	{C_Hp_BQuadrant1De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10522201	事件发生时刻B相第一象限无功总最大需量及发生时间*/ 
	{C_Hp_BQuadrant2De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10622201	事件发生时刻B相第二象限无功总最大需量及发生时间*/ 
	{C_Hp_BQuadrant3De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10722201	事件发生时刻B相第三象限无功总最大需量及发生时间*/ 
	{C_Hp_BQuadrant4De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10822201	事件发生时刻B相第四象限无功总最大需量及发生时间*/ 
	{C_HP_CPosAcDe,							C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10132201	事件发生时刻C相正向有功最大需量及发生时间*/
	{C_HP_CRevAcDe,							C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10232201	事件发生时刻C相反向有功最大需量及发生时间*/
	{C_Hp_CQuadrant1De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10532201	事件发生时刻C相第一象限无功总最大需量及发生时间*/
	{C_Hp_CQuadrant2De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10632201	事件发生时刻C相第二象限无功总最大需量及发生时间*/
	{C_Hp_CQuadrant3De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10732201	事件发生时刻C相第三象限无功总最大需量及发生时间*/
	{C_Hp_CQuadrant4De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10832201	事件发生时刻C相第四象限无功总最大需量及发生时间*/                    
};
#define EventTable2_RelateOAD14_F1_Len  ( sizeof(EventTable2_RelateOAD14_F1) / sizeof(Str_EventChange_Table2) )


/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD15[] =  /**********事件清零关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻*/
	{CRelayOpen_OpeCode_1,					C_NormalRead,				CLRelayOpen_OpeCode_1},				/*0X1D000201	操作者代码*/
	{0x330C0206,							C_NormalRead,				4},									/*清零数据标识      */
};
#define EventTable2_RelateOAD15_Len  ( sizeof(EventTable2_RelateOAD15) / sizeof(Str_EventChange_Table2) )

/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD2B[] =  /**********负荷开关误动作关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻*/  
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)},				/*0X20200201	事件结束时刻*/    
	{0xF2052201,							C_ReadDeal_F,				1},									/*0XF2052201 	负荷开关误动作时状态*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	事件发生时刻正向有功总电能*/  
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	事件发生时刻反向有功总电能*/ 
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00108201	事件结束时刻正向有功总电能*/   
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00208201	事件结束时刻反向有功总电能*/   	
};
#define EventTable2_RelateOAD2B_Len  (sizeof(EventTable2_RelateOAD2B)/sizeof(Str_EventChange_Table2))

/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD0F[] =  /**********电压逆相序关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻645   6字节*/                                      	
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	正向有功总电能*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	反向有功总电能*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	组合无功1总电能*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	组合无功2总电能*/   
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A相正向有功电能*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A相反向有功电能*/   
	{C_HP_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00312201	A相组合无功1总电能*/
	{C_HP_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00412201	A相组合无功2总电能*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B相正向有功电能*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B相反向有功电能*/   
	{C_HP_BComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00322200	B相组合无功1总电能*/
	{C_HP_BComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00422200	B相组合无功2总电能*/
	{C_HP_CPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C相正向有功电能*/   
	{C_HP_CRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C相反向有功电能*/   
	{C_HP_CComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00330200	C相组合无功1总电能*/
	{C_HP_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C相组合无功2总电能*/
	{(CEventEndTime),						C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200	事件结束时刻645 6字节*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00100200	正向有功总电能*/        
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00200200	反向有功总电能*/        
	{C_End_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00300200	组合无功1总电能*/   
	{C_End_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00400200	组合无功2总电能*/   
	{C_End_APosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00110200	A相正向有功电能*/   
	{C_End_ARevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00210200	A相反向有功电能*/   
	{C_End_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00310200	A相组合无功1总电能*/
	{C_End_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00410200	A相组合无功2总电能*/
	{C_End_BPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00122200	B相正向有功电能*/   
	{C_End_BRevAcEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00222200	B相反向有功电能*/   
	{C_End_BComRe1En,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00322200	B相组合无功1总电能*/
	{C_End_BComRe2En,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00422200	B相组合无功2总电能*/
	{C_End_CPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00130200	C相正向有功电能*/   
	{C_End_CRevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00230200	C相反向有功电能*/   
	{C_End_CComRe1En,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00330200	C相组合无功1总电能*/
	{C_End_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},    	//0x00430200	C相组合无功2总电能*/
};
#define EventTable2_RelateOAD0F_Len  ( sizeof(EventTable2_RelateOAD0F) / sizeof(Str_EventChange_Table2) )

/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD1D[] =  /**********电压不平衡关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻645   6字节*/                                      	
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	正向有功总电能*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	反向有功总电能*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	组合无功1总电能*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	组合无功2总电能*/   
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A相正向有功电能*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A相反向有功电能*/   
	{C_HP_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00312201	A相组合无功1总电能*/
	{C_HP_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00412201	A相组合无功2总电能*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B相正向有功电能*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B相反向有功电能*/   
	{C_HP_BComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00322200	B相组合无功1总电能*/
	{C_HP_BComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00422200	B相组合无功2总电能*/
	{C_HP_CPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C相正向有功电能*/   
	{C_HP_CRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C相反向有功电能*/   
	{C_HP_CComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00330200	C相组合无功1总电能*/
	{C_HP_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C相组合无功2总电能*/
	{C_VolUnbalanceRate_E,					C_NormalRead,				CLNoBalRate_Vol_End_1},				/*电压不平衡最大不平衡率*/ 
	{(CEventEndTime),						C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200  事件结束时刻645 6字节*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00100200	正向有功总电能*/        
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00200200	反向有功总电能*/        
	{C_End_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00300200	组合无功1总电能*/   
	{C_End_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00400200	组合无功2总电能*/   
	{C_End_APosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00110200	A相正向有功电能*/   
	{C_End_ARevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00210200	A相反向有功电能*/   
	{C_End_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00310200	A相组合无功1总电能*/
	{C_End_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00410200	A相组合无功2总电能*/
	{C_End_BPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00122200	B相正向有功电能*/   
	{C_End_BRevAcEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00222200	B相反向有功电能*/   
	{C_End_BComRe1En,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00322200	B相组合无功1总电能*/
	{C_End_BComRe2En,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00422200	B相组合无功2总电能*/
	{C_End_CPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00130200	C相正向有功电能*/   
	{C_End_CRevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00230200	C相反向有功电能*/   
	{C_End_CComRe1En,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00330200	C相组合无功1总电能*/
	{C_End_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C相组合无功2总电能*/
};
#define EventTable2_RelateOAD1D_Len  ( sizeof(EventTable2_RelateOAD1D) / sizeof(Str_EventChange_Table2) )
/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD17[] =  /**********电流不平衡关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻645   6字节*/                                      	
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	正向有功总电能*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	反向有功总电能*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	组合无功1总电能*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	组合无功2总电能*/   
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A相正向有功电能*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A相反向有功电能*/   
	{C_HP_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00312201	A相组合无功1总电能*/
	{C_HP_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00412201	A相组合无功2总电能*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B相正向有功电能*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B相反向有功电能*/   
	{C_HP_BComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00322200	B相组合无功1总电能*/
	{C_HP_BComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00422200	B相组合无功2总电能*/
	{C_HP_CPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C相正向有功电能*/   
	{C_HP_CRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C相反向有功电能*/   
	{C_HP_CComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00330200	C相组合无功1总电能*/
	{C_HP_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C相组合无功2总电能*/
	{C_CurUnbalanceRate_E,					C_NormalRead,				CLNoBalRate_Curr_1},				/*电流不平衡最大不平衡率*/ 
	{(CEventEndTime),						C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200  事件结束时刻645 6字节*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00100200	正向有功总电能*/        
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00200200	反向有功总电能*/        
	{C_End_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00300200	组合无功1总电能*/   
	{C_End_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00400200	组合无功2总电能*/   
	{C_End_APosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00110200	A相正向有功电能*/   
	{C_End_ARevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00210200	A相反向有功电能*/   
	{C_End_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00310200	A相组合无功1总电能*/
	{C_End_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00410200	A相组合无功2总电能*/
	{C_End_BPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00122200	B相正向有功电能*/   
	{C_End_BRevAcEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00222200	B相反向有功电能*/   
	{C_End_BComRe1En,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00322200	B相组合无功1总电能*/
	{C_End_BComRe2En,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00422200	B相组合无功2总电能*/
	{C_End_CPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00130200	C相正向有功电能*/   
	{C_End_CRevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00230200	C相反向有功电能*/   
	{C_End_CComRe1En,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00330200	C相组合无功1总电能*/
	{C_End_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C相组合无功2总电能*/
};
#define EventTable2_RelateOAD17_Len  ( sizeof(EventTable2_RelateOAD17) / sizeof(Str_EventChange_Table2) )


/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD0D[] =  /**********全失压关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻*/  
	{C_HP_Curr,								C_ReadDeal_E,				3},      							/*0x20012200	事件发生时刻电流值*/
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)},				/*0X20200201	事件结束时刻*/    
};
#define EventTable2_RelateOAD0D_Len  ( sizeof(EventTable2_RelateOAD0D) / sizeof(Str_EventChange_Table2) )
/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD16[] =  /**********校时关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）	*/
	{CRelayOpen_OpeCode_1,					C_NormalRead,				CLRelayOpen_OpeCode_1},				/*0X1D000201  	操作者代码*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻*/  
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)},				/*0X20200201  事件结束时刻*/    
};
#define EventTable2_RelateOAD16_Len  ( sizeof(EventTable2_RelateOAD16) / sizeof(Str_EventChange_Table2) )


/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD1A[] =  /**********结算日编程关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻*/  
	{CRelayOpen_OpeCode_1,					C_NormalRead,   			CLRelayOpen_OpeCode_1},				/*0X1D000201  	操作者代码*/
	{C_SettleDatebeforePro,					C_NormalRead,				CLSettleDatebeforePro},				/*0x41162200	编程前结算日*/  
};
#define EventTable2_RelateOAD1A_Len  ( sizeof(EventTable2_RelateOAD1A) / sizeof(Str_EventChange_Table2) )


/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD18[] =  /**********时区表编程关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻*/  
	{CRelayOpen_OpeCode_1,					C_NormalRead,				CLRelayOpen_OpeCode_1},				/*0X1D000201  	操作者代码*/
	{C_SpareBDayTablePrO,					C_ReadDeal_G,				CLProgTZ_645Comm_Note_OnlyData},	/*0x40152200	时区表编程数据*/  
};
#define EventTable2_RelateOAD18_Len  ( sizeof(EventTable2_RelateOAD18) / sizeof(Str_EventChange_Table2) )

#define C_HP_TolPowerCon					0x21FFFFFF
#define CLHP_TolPowerCon					1

/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD07[] =  /**********电压逆相序关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻645   6字节*/                                      	
	{C_HP_TolPowerCon,						C_NormalRead,				CLHP_TolPowerCon},					/*自扩潮流反向发生时总功率方向*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	正向有功总电能*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	反向有功总电能*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	组合无功1总电能*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	组合无功2总电能*/   
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A相正向有功电能*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A相反向有功电能*/   
	{C_HP_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00312201	A相组合无功1总电能*/
	{C_HP_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00412201	A相组合无功2总电能*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B相正向有功电能*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B相反向有功电能*/   
	{C_HP_BComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00322200	B相组合无功1总电能*/
	{C_HP_BComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00422200	B相组合无功2总电能*/
	{C_HP_CPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C相正向有功电能*/   
	{C_HP_CRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C相反向有功电能*/   
	{C_HP_CComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00330200	C相组合无功1总电能*/
	{C_HP_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C相组合无功2总电能*/
};
#define EventTable2_RelateOAD07_Len  ( sizeof(EventTable2_RelateOAD07) / sizeof(Str_EventChange_Table2) )

/*表格顺序请勿随意调整	*/
const Str_EventChange_Table2 EventTable2_RelateOAD0C[] =  /**********总功率因数超下限关联属性列表***************/
{
/*对应的698关联属性列表            		索引（分相读取标志）		*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	事件发生时刻645   6字节*/                                      	
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	正向有功总电能*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	反向有功总电能*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	组合无功1总电能*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	组合无功2总电能*/   
	{(CEventEndTime),						C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200	事件结束时刻645 6字节*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00100200	正向有功总电能*/        
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00200200	反向有功总电能*/        
	{C_End_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00300200	组合无功1总电能*/   
	{C_End_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00400200	组合无功2总电能*/   
};
#define EventTable2_RelateOADOC_Len  ( sizeof(EventTable2_RelateOAD0C) / sizeof(Str_EventChange_Table2) )


const Str_EventChange_Table1 EventTable1_OADChange698[] =  
{
/*		DI						OIB         		属性     				2级表格地址											2级表格个数*/
	{COpenW_Degree,				0x1B,				0x02,			(ulong32)(&EventTable2_RelateOAD1B[0]),				EventTable2_RelateOAD1B_Len},			/*开表盖 */
	{COpenCW_Degree,			0x1C,				0x02,			(ulong32)(&EventTable2_RelateOAD1B[0]),				EventTable2_RelateOAD1B_Len},			/*开端钮盖  */
	{CConM_Degree,				0x2A,				0x02,			(ulong32)(&EventTable2_RelateOAD2A[0]),				EventTable2_RelateOAD2A_Len},			/*恒定磁场*/ 
	{CPow_Down_Degree,			0x11,				0x02,			(ulong32)(&EventTable2_RelateOAD11[0]),				EventTable2_RelateOAD11_Len},			/*掉电*/
	{CPowerFa_Degree,			0x2C,				0x02,			(ulong32)(&EventTable2_RelateOAD2C[0]),				EventTable2_RelateOAD2C_Len},			/*电源异常*/
	{CLossA_Vol_Degree,			0x00,				0x07,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*A失压*/
	{CLossB_Vol_Degree,			0x00,				0x08,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*B失压*/
	{CLossC_Vol_Degree,			0x00,				0x09,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*C失压*/
	{CLossA_Curr_Degree,		0x04,				0x07,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*A失流*/
	{CLossB_Curr_Degree,		0x04,				0x08,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*B失流*/
	{CLossC_Curr_Degree,		0x04,				0x09,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*C失流*/
	{COverA_Curr_Degree,		0x05,				0x07,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*A过流*/
	{COverB_Curr_Degree,		0x05,				0x08,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*B过流*/
	{COverC_Curr_Degree,		0x05,				0x09,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*C过流*/
	{CRelayOpen_Degree,			0x1F,				0x02,			(ulong32)(&EventTable2_RelateOAD1F20[0]),			EventTable2_RelateOAD1F20_Len},			/*拉闸 */  
	{CRelayClose_Degree,		0x20,				0x02,			(ulong32)(&EventTable2_RelateOAD1F20[0]),			EventTable2_RelateOAD1F20_Len},			/*合闸*/
	{CTol_Clear_Degree,			0x13,				0x02,			(ulong32)(&EventTable2_RelateOAD13[0]),				EventTable2_RelateOAD13_Len},			/*电表清零 */
	{CEven_Clear_Degree,		0x15,				0x02,			(ulong32)(&EventTable2_RelateOAD15[0]),				EventTable2_RelateOAD15_Len},			/*事件清零 */ 
	{CRelayFa_Degree,			0x2B,				0x02,			(ulong32)(&EventTable2_RelateOAD2B[0]),				EventTable2_RelateOAD2B_Len},			/*负荷开关误动做*/ 
	{CRevPS_Vol_Degree,			0x0F,				0x02,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*电压逆相序 */
	{CNoBal_Vol_Degree,			0x1D,				0x02,			(ulong32)(&EventTable2_RelateOAD1D[0]),				EventTable2_RelateOAD1D_Len},			/*电压不平衡*/
	{CAdjTime_Degree,			0x16,				0x02,			(ulong32)(&EventTable2_RelateOAD16[0]),				EventTable2_RelateOAD16_Len},			/*校时 */
	{CLowA_Vol_Degree,			0x01,				0x07,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*A欠压 */
	{CLowB_Vol_Degree,			0x01,				0x08,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*B欠压 */
	{CLowC_Vol_Degree,			0x01,				0x09,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*C欠压 */
	{COverA_Vol_Degree,			0x02,				0x07,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*A过压 */
	{COverB_Vol_Degree,			0x02,				0x08,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*B过压 */
	{COverC_Vol_Degree,			0x02,				0x09,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*C过压 */
	{0x03050000,				0x0D,				0x02,			(ulong32)(&EventTable2_RelateOAD0D[0]),				EventTable2_RelateOAD0D_Len},			/*全失压 */
	{CBreakA_Vol_Degree,		0x03,				0x07,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*A断相 */
	{CBreakB_Vol_Degree,		0x03,				0x08,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*B断相 */
	{CBreakC_Vol_Degree,		0x03,				0x09,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*C断相 	*/
	{CPowerA_Rev_Degree,		0x07,				0x07,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*A有功功率反向 */
	{CPowerB_Rev_Degree,		0x07,				0x08,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*B有功功率反向*/
	{CPowerC_Rev_Degree,		0x07,				0x09,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*C有功功率反向*/
	{CProgSettD_Degree,			0x1A,				0x02,			(ulong32)(&EventTable2_RelateOAD1A[0]),				EventTable2_RelateOAD1A_Len},			/*结算日编程事件*/
	{CProgTZ_Degree,			0x18,				0x02,			(ulong32)(&EventTable2_RelateOAD18[0]),				EventTable2_RelateOAD18_Len},			/*时区表编程事件*/
	{CPowerT_Rev_Degree,		0x07,				0x06,			(ulong32)(&EventTable2_RelateOAD07[0]),				EventTable2_RelateOAD07_Len},			/*潮流反向（总有功功率反向）*/
	{CNoBal_Curr_Degree,		0x1E,				0x02,			(ulong32)(&EventTable2_RelateOAD17[0]),				EventTable2_RelateOAD17_Len},			/*电流不平衡  */
	{CSevNoBal_Curr_Degree,		0x2D,				0x02,			(ulong32)(&EventTable2_RelateOAD17[0]),				EventTable2_RelateOAD17_Len},			/*电流严重不平衡*/
	{CRevPS_Curr_Degree,		0x10,				0x02,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*电流逆向序*/
	{CPFactorT_Over_Degree,		CPFactorT_Over_OIB,	0x06,			(ulong32)(&EventTable2_RelateOAD0C[0]),				EventTable2_RelateOADOC_Len},			/*功率因数超下限*/
	{CBreakA_Curr_Degree,		0x06,				0x07,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*断流A*/
	{CBreakB_Curr_Degree,		0x06,				0x08,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*断流B*/
	{CBreakC_Curr_Degree,		0x06,				0x09,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*断流C*/
	{COverA_Lo_Degree,			0x08,				0x07,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*过载A*/
	{COverB_Lo_Degree,			0x08,				0x08,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*过载B */
	{COverC_Lo_Degree,			0x08,				0x09,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*过载C*/
	{CPFactorA_Over_Degree,		CPFactorT_Over_OIB,	0x07,			(ulong32)(&EventTable2_RelateOAD0C[0]),				EventTable2_RelateOADOC_Len},			/*A相功率因数超下限*/
	{CPFactorB_Over_Degree,		CPFactorT_Over_OIB,	0x08,			(ulong32)(&EventTable2_RelateOAD0C[0]),				EventTable2_RelateOADOC_Len},			/*B相功率因数超下限*/
	{CPFactorC_Over_Degree,		CPFactorT_Over_OIB,	0x09,			(ulong32)(&EventTable2_RelateOAD0C[0]),				EventTable2_RelateOADOC_Len},			/*C相功率因数超下限*/
};
#define EventTable1_OADChange698_Len  ( sizeof(EventTable1_OADChange698) / sizeof(Str_EventChange_Table1) )


const Str_ParaChange_OADToDI_Table ParaChange_OADToDI_Table40[] =
{
	{CDate_Time,					CDate_Week_Time_645},				/*时间*/
	{CDay_Table_Num,					CDay_Table_Num_645},    			 
	{CDay_Time_Num,						CDay_Time_Num_645},     			 
	{CRate_Num,							CRate_Num_645},         			 
	{CYear_Zone_Num,					CYear_Zone_Num_645},				/*年时区数 */
	{CSettle_Day1,						CSettle_Day1_645},					/*结算日1*/
	{CSettle_Day2,						CSettle_Day2_645},					/*结算日1*/
	{CSettle_Day3,						CSettle_Day3_645},					/*结算日1*/
	{CComm_Address,						CComm_Address_645},					/*通信地址*/
	{CHoliday_Num,						CHoliday_Num_645},
	{CChange_TZ_Time,					CChange_TZ_Time_645},
	{CChange_PT_Time,					CChange_PT_Time_645},
	{CWeek_RestDay,						CWeek_RestDay_645},
	{CWeek_RestDay,						CWeek_RestDay_645},
	{CFirst_TZone_Data,					CFirst_TZone_Data_645},
	{CFirst_TZone_1PT_Data,				CFirst_TZone_1PT_Data_645},
	{CFirst_TZone_2PT_Data,				CFirst_TZone_2PT_Data_645},
	{CFirst_TZone_3PT_Data,				CFirst_TZone_3PT_Data_645},
	{CFirst_TZone_4PT_Data,				CFirst_TZone_4PT_Data_645},
	{CFirst_TZone_5PT_Data,				CFirst_TZone_5PT_Data_645},
	{CFirst_TZone_6PT_Data,				CFirst_TZone_6PT_Data_645},
	{CFirst_TZone_7PT_Data,				CFirst_TZone_7PT_Data_645},
	{CFirst_TZone_8PT_Data,				CFirst_TZone_8PT_Data_645},
	{CSec_TZone_Data,					CSec_TZone_Data_645},
	{CSec_TZone_1PT_Data,				CSec_TZone_1PT_Data_645}, 
	{CSec_TZone_2PT_Data,				CSec_TZone_2PT_Data_645}, 
	{CSec_TZone_3PT_Data,				CSec_TZone_3PT_Data_645},
	{CSec_TZone_4PT_Data,				CSec_TZone_4PT_Data_645}, 
	{CSec_TZone_5PT_Data,				CSec_TZone_5PT_Data_645}, 
	{CSec_TZone_6PT_Data,				CSec_TZone_6PT_Data_645}, 
	{CSec_TZone_7PT_Data,				CSec_TZone_7PT_Data_645}, 
	{CSec_TZone_8PT_Data,				CSec_TZone_8PT_Data_645},                                		
};
#define ParaChange_OADToDI_Table40_Len  ( sizeof(ParaChange_OADToDI_Table40) / sizeof(Str_ParaChange_OADToDI_Table) )

const Str_ParaChange_OADToDI_Table ParaChange_OADToDI_Table41[] =
{
	{CActive_Com_State,					CActive_Com_State_645},
	{CReactive_Com_State1,				CReactive_Com_State1_645},
	{CReactive_Com_State2,				CReactive_Com_State2_645},
	{CSettle_Day1,						CSettle_Day1_645},           
	{CSettle_Day2,						CSettle_Day2_645},
	{CSettle_Day3,						CSettle_Day3_645},
	{CManage_Code,						CManage_Code_645},

};
#define ParaChange_OADToDI_Table41_Len  ( sizeof(ParaChange_OADToDI_Table41) / sizeof(Str_ParaChange_OADToDI_Table) )

const Str_ParaChange_OADToDI_Table ParaChange_OADToDI_Table30[] =
{
	{CLossVolage_Vol_UpLim,				CLossVolage_Vol_UpLim_645},
	{CLossVolage_Vol_LowLim,			CLossVolage_Vol_LowLim_645},
	{CLossVolage_Curr_LowLim,			CLossVolage_Curr_LowLim_645},
	{CLossVolage_Delay_T,				CLossVolage_Delay_T_645},
	{CLowVolage_Vol_UpLim,				CLowVolage_Vol_UpLim_645},
	{CLowVolage_Delay_T,				CLowVolage_Delay_T_645},
	{COverVolage_Vol_LowLim,			COverVolage_Vol_LowLim_645},
	{COverVolage_Delay_T,				COverVolage_Delay_T_645},
	{CBreakVol_Vol_UpLim,				CBreakVol_Vol_UpLim_645},
	{CBreakVol_Curr_UpLim,				CBreakVol_Curr_UpLim_645},
	{CBreakVol_Delay_T,					CBreakVol_Delay_T_645},
	{CNoBal_Vol_Lim,					CNoBal_Vol_Lim_645},
	{CNoBal_Vol_Delay_T,				CNoBal_Vol_Delay_T_645},
	{CNoBal_Curr_Lim,					CNoBal_Curr_Lim_645},
	{CNoBal_Curr_Delay_T,				CNoBal_Curr_Delay_T_645},
	{CSeriNoBal_Curr_Lim,				CSeriNoBal_Curr_Lim_645},
	{CSeriNoBal_Curr_Delay_T,			CSeriNoBal_Curr_Delay_T_645},
	{CLossCurr_Vol_LowLim,				CLossCurr_Vol_LowLim_645},
	{CLossCurr_Curr_UpLim,				CLossCurr_Curr_UpLim_645},
	{CLossCurr_Curr_LowLim,				CLossCurr_Curr_LowLim_645},
	{CLossCurr_Delay_T,					CLossCurr_Delay_T_645},
	{COverCurr_Curr_LowLim,				COverCurr_Curr_LowLim_645},
	{COverCurr_Delay_T,					COverCurr_Delay_T_645},
	{CBreakCurr_Vol_LowLim,				CBreakCurr_Vol_LowLim_645},
	{CBreakCurr_Curr_UpLim,				CBreakCurr_Curr_UpLim_645},
	{CBreakCurr_Delay_T,				CBreakCurr_Delay_T_645},
	{CTrendRev_AcPower_LowLim,			CTrendRev_AcPower_LowLim_645},
	{CTrendRev_Delay_T,					CTrendRev_Delay_T_645},
	{COverLoad_AcPower_LowLim,			COverLoad_AcPower_LowLim_645},
	{COverLoad_Delay_T,					COverLoad_Delay_T_645},
	{CVolage_Check_UpLim,				CVolage_Check_UpLim_645},
	{CVolage_Check_LowLim,				CVolage_Check_LowLim_645},
	{CPosAcDemandOv_De_LowLim,			CAcDemandOv_De_LowLim_645	},
	{CReDemandOv_De_LowLim,				CReDemandOv_De_LowLim_645	},
	{CPosAcDemandOv_Delay_T,			CDemandOv_Delay_T_645	    },
	{CPowerFactor_LowLim,				CPowerFactor_LowLim_645},
	{CPowerFactor_Delay_T,				CPowerFactor_Delay_T_645},
	{CPowerRev_AcPower_LowLim,			CPowerRev_AcPower_LowLim_645},
	{CPowerRev_Delay_T,					CPowerRev_Delay_T_645},
};                          	

#define ParaChange_OADToDI_Table30_Len  ( sizeof(ParaChange_OADToDI_Table30) / sizeof(Str_ParaChange_OADToDI_Table) )

#define C_EventRead_NeedTol_Len 14
const ulong32 C_EventRead_NeedTol[C_EventRead_NeedTol_Len] =   /*645协议中，没有每项数据单独读取   */
{
	0x03300D00,		/*开表盖*/
	0x03300E00,		/*开端钮盖*/
	0x03350000,		/*恒定磁场干扰*/
	0x03110000,		/*掉电*/
	0x03370000,		/*电源异常*/
	0x03360000,		/*负荷开关误动作*/
	0x03300100,		/*电表清零*/
	0x03300200,		/*需量清零*/
	0x03300300,		/*事件清零*/
	0x03300400,		/*校时 */
	0x03050000,		/*全失压*/
	0x03300C00,		/*结算日编程*/  
	0x03300600,		/*时区表编程*/
	0x21000000,		/*潮流反向*/
};

uchar8 SF_GetAPDU_FreezeRead( RdOI_Para_T *V_OAD, uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 NextFrameFlage );
uchar8 InF_RateNumChangeToHex( void );
uchar8 SF_Judge_CuerrntIDFlag( void );
uchar8 SF_GetEsamIDFlag( void );
uchar8 INF_RELEASE_Service_Deal_Card( void );

void InF_Clear_BroadTimeAbnormalTime( void );
uchar8 SF_Get_Active_OAD( ulong32 V_ulReadOAD, ulong32 *pV_ulSetAndFixedOAD, uchar8 V_ucDataType, uchar8 V_ucHappeningFlag );
#endif

