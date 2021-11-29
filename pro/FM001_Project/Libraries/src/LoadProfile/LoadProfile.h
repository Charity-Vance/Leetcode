
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     LoadProfile.h
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__LoadProfile_H
#define	__LoadProfile_H

///***************************����д���***********************************///
#define CLoad_Write             0x06000ADB      ///*���ɼ�¼д���ݲ��ʶ*/// 
///*ʱ�������*///
#define	C_Sec					0	///*��*///
#define	C_Minute				1	///*��*///
#define	C_Hour					2	///*ʱ*///
#define	C_Day					3	///*��*///
#define	C_Month					4	///*��*///
#define	C_Year					5	///*��*///

///*���ɻ������и��̶�����˳��*///
#define	C_Mode					0	///*ģʽ��*///
#define	C_A0					1	///*A0*///
#define	C_Length				3	///*����*///
#define	C_Time					4	///*ʱ��*///
#define	C_Data					9	///*����*///

#define	C_LoadTimeLen			5	///*���ɼ�¼ʱ��ĳ���*///
///*������������,�����жϵ������ֶ����ݺ���*///
#define	C_VariableType			0	///*˲ʱ��*///
#define	C_EnergyType			1	///*����*///
#define	C_DemandType			2	///*����*///

///*ȡ�������ݲ�ѯ���*///
typedef struct
{
	ulong32 V_ulDI;	///*��ʶ�룬ȡ����ʱ��������������	�õĲ���*///
	uchar8 V_ucLength;			///*���ȣ������ۼӸ������ݿ���ܳ��ȣ������ö����ݺ���ʱ�ĳ��Ȳ���*///
	uchar8 V_ucDataType;		///*�������ͣ�����/����/˲ʱ����, ���ݴ����ݣ��жϵ����ĸ������ݺ���*///
}Str_LoadDataType;

///***************************���ɳ������***********************************///
#define C_LoadTLength			5      ///*���ɼ�¼ʱ�䳤��*/// 
#define C_LoadTypeNum			36     ///*����������������*/// 
#define C_LoadMaxLen			103    ///*������������ɼ�¼��������ݳ���*/// 

#define C_FirstFrame			0x00	   ///*��������������һ֡*///
#define C_OtherFrame			0xAA	   ///*�������������ǵ�һ֡*///
#define C_ReCal					0x78		///*����ֹʱ��ȵ�ǰʱ��󣬿���������*///

#define C_TimeOffset			3	   ///*��¼ʱ���ڸ��ɼ�¼�е�ƫ����*/// 
///*���ɼ�¼��ʼʱ��*///
#define	C_Minute_L				0	///*��*///
#define	C_Hour_L				1	///*ʱ*///
#define	C_Day_L					2	///*��*///
#define	C_Month_L				3	///*��*///
#define	C_Year_L				4	///*��*///

///*�������ɼ�¼������*///
#define	C_LoadType_Energy		0x12	///*�����ฺ������*///
#define	C_LoadType_Variable		0x34	///*˲ʱ���ฺ������*///

///*�������ݱ�ʶ���Ӧ�ĸ�������*///
typedef struct
{
	ulong32 V_ulDataId;		///*���ݱ�ʶ*///
	ulong32 V_ulTypeId;		///*��Ӧԭ�������ͱ�ʶ��*///
	uchar8 V_ucOffset;		///*���ݱ�ʶ�ڶ�Ӧ���������ƫ�� *///
	uchar8 V_ucDataLen;		///*��ʶ�����ݶ�Ӧ�ĳ���*///
}Str_LoadReadStatus;

///*����д��غ���*///
void Msg_LoadProfile(Str_Msg_Parameter *V_Msg);
uchar8 SF_GetData_LoadProfile(uchar8 V_ucMode,uchar8 *p_ucDateTime,uchar8 *P_buffer);
uchar8 SF_CalCS(uchar8 *P_buffer,uchar8 V_ucLen);

///*���ɶ���غ���*///
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
