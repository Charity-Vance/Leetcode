
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     LoadProfile.h
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__LoadProfile_H
#define	__LoadProfile_H

///***************************负荷写相关***********************************///
#define CLoad_Write             0x06000ADB      ///*负荷记录写数据层标识*/// 
///*时间和日期*///
#define	C_Sec					0	///*秒*///
#define	C_Minute				1	///*分*///
#define	C_Hour					2	///*时*///
#define	C_Day					3	///*日*///
#define	C_Month					4	///*月*///
#define	C_Year					5	///*年*///

///*负荷缓存区中各固定数据顺序*///
#define	C_Mode					0	///*模式字*///
#define	C_A0					1	///*A0*///
#define	C_Length				3	///*长度*///
#define	C_Time					4	///*时间*///
#define	C_Data					9	///*数据*///

#define	C_LoadTimeLen			5	///*负荷记录时间的长度*///
///*负荷数据种类,用于判断调用那种读数据函数*///
#define	C_VariableType			0	///*瞬时量*///
#define	C_EnergyType			1	///*电量*///
#define	C_DemandType			2	///*需量*///

///*取负荷数据查询表格*///
typedef struct
{
	ulong32 V_ulDI;	///*标识码，取数据时，传给读函数所	用的参数*///
	uchar8 V_ucLength;			///*长度，用于累加负荷数据块的总长度，及调用读数据函数时的长度参数*///
	uchar8 V_ucDataType;		///*数据类型（电能/需量/瞬时量）, 根据此数据，判断调用哪个读数据函数*///
}Str_LoadDataType;

///***************************负荷抄读相关***********************************///
#define C_LoadTLength			5      ///*负荷记录时间长度*/// 
#define C_LoadTypeNum			36     ///*负荷连续抄读种类*/// 
#define C_LoadMaxLen			103    ///*按种类读读负荷记录的最大数据长度*/// 

#define C_FirstFrame			0x00	   ///*负荷连续抄读第一帧*///
#define C_OtherFrame			0xAA	   ///*负荷连续抄读非第一帧*///
#define C_ReCal					0x78		///*当截止时间比当前时间大，块数需重算*///

#define C_TimeOffset			3	   ///*记录时间在负荷记录中的偏移量*/// 
///*负荷记录起始时间*///
#define	C_Minute_L				0	///*分*///
#define	C_Hour_L				1	///*时*///
#define	C_Day_L					2	///*日*///
#define	C_Month_L				3	///*月*///
#define	C_Year_L				4	///*年*///

///*抄读负荷记录的类型*///
#define	C_LoadType_Energy		0x12	///*电能类负荷数据*///
#define	C_LoadType_Variable		0x34	///*瞬时量类负荷数据*///

///*抄读数据标识码对应的各项数据*///
typedef struct
{
	ulong32 V_ulDataId;		///*数据标识*///
	ulong32 V_ulTypeId;		///*对应原负荷类型标识码*///
	uchar8 V_ucOffset;		///*数据标识在对应负荷种类的偏移 *///
	uchar8 V_ucDataLen;		///*标识码数据对应的长度*///
}Str_LoadReadStatus;

///*负荷写相关函数*///
void Msg_LoadProfile(Str_Msg_Parameter *V_Msg);
uchar8 SF_GetData_LoadProfile(uchar8 V_ucMode,uchar8 *p_ucDateTime,uchar8 *P_buffer);
uchar8 SF_CalCS(uchar8 *P_buffer,uchar8 V_ucLen);

///*负荷读相关函数*///
uchar8 InF_SeqRead_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucTime,uchar8 *P_ucData,uchar8 *P_ucGVBuffer,uchar8 *P_ucBlockNum,uchar8 *P_ucLength,uchar8 P_ucFollowFlag);
uchar8 SF_GetSeqData_LoadProfile(ulong32 *V_ulDataId,uchar8 *P_ucStartTime,uchar8 *P_ucBlockNum,uchar8 *P_ucIntTime,uchar8 P_ucFollowFlag,uchar8 *P_ucGVBuffer,uchar8 *P_ucDataTemp);
uchar8 SF_GetIntTime_LoadProfile(ulong32 V_ulLoadID);
uchar8 SF_StartTime_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucStartTime,uchar8 *P_ucLoadParaTime,uchar8 V_ucIntTime);
uchar8 SF_FirstTime_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucInteTime,uchar8 *P_ucReadStartTime,uchar8 *P_ucStartTime,uchar8 *P_ucParaTime,uchar8 *P_ucSendTime);
void SF_MinsAdd_LoadProfile(uchar8 *P_ucSourceTime,ulong32 V_ulAddMins,uchar8 *P_ucResultTime);
void SF_DECtoHEXByte(uchar8 *V_ucSourceData,uchar8 *V_ucResultData);
uchar8 SF_HEXtoDECByte(uchar8 HEXdata);
void SF_FillData_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucGVBuffer,uchar8 *P_ucDataTemp,uchar8 V_ucLength);
uchar8 SF_LoadProfile_ParseMessage(Str_Msg_Parameter *P_Msg_Parameter);
uchar8 SF_JudgeType_LoadProfile(ulong32 V_ulID);

#endif
