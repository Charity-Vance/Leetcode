
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     EventRecord.h
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///


///*****************************************************************************************///
///*Copyright?o    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     EventRecord.h
///*Version:       V1
///*Date:          2014-3-12
///*Description:
///*Function List:
///*****************************************************************************************///
#ifndef	__EventRecord_H
#define	__EventRecord_H

///*****************************************************************************************///
///*������ʱ���壬������ƴ�Ӻ�ɾ��*///
///*****************************************************************************************///
#define	C_LowPowerHappen_EventMsg	0x99	///*�͹������¼�״̬���з����޻ָ�*///
#define	C_LowPowerEnd_EventMsg	0x88	///*�͹������¼�״̬�����з����޻ָ�*///

#define	C_TpowerDirection_Forward	0x00	///*�ܹ��ʷ�������*///
#define	C_TpowerDirection_Reverse	0x01	///*�ܹ��ʷ��򣬷���*///
#define	C_TpowerDirection_Close		0x88	///*�ܹ��ʷ���رշ���*///
#define	C_TpowerDirection_Init		0x66	///*�ܹ��ʷ����ʼ������*///

#define	C_Happen_EventMsg	0x68	///*�¼���������*///
#define	C_End_EventMsg		0x66	///*�¼��ָ�����*///
#define	C_Null_EventMsg		0x00	///*�¼��޶���*///

#define C_JudgeTimeError  77		///*�ж�ʱ�䷧ֵ���ش���*///
#define	C_Judge_Event_DefaultTime1	0x3C	///*Ĭ���¼��ж�ʱ�䷧ֵ*///
#define	C_Close_Parameter			0x00	///*�¼��жϷ�ֵΪ0*///
#define	C_Judge_Time0				0x00	///*�¼��ж�ʱ��Ϊ0s*///
#define	C_Judge_Time1				0x01	///*�¼��ж�ʱ��Ϊ1s*///
#define	C_Judge_Time2				0x02	///*�¼��ж�ʱ��Ϊ2s*///
#define	C_Judge_Time3				0x03	///*�¼��ж�ʱ��Ϊ3s*///
#define	C_Judge_Time4				0x05	///*�¼��ж�ʱ��Ϊ5s*///

#define	C_EventNoLength		0x37				///*�¼�����*///
#define	C_EventNoLength1	C_EventNoLength-1	///*�з����޻ָ��¼�����*///
#define	C_ReadDataLength	115					///*֧�ֶ��������ܸ���*///

#define	C_Event_MsgLength	10			///*�ж���Ϣ����Ϣʱ���ݳ���*///
#define	C_PTEventNo_Msgbuffer	0				///*��Ϣ�У�EventNo_PT����///
#define	C_EventNo_Msgbuffer		1				///*��Ϣ�У�EventNo����///
#define	C_PTTime_Msgbuffer	    2				///*��Ϣ�У�Time_PT����///
#define	C_Time_Msgbuffer	    3				///*��Ϣ�У�Time����///

#define	C_3Wire	2			///*������������*///
#define	C_4Wire	3			///*������������*///


#define	C_TenThousand_times		10000///*10000��*///
// #define	C_Ulong32_Length	4	///*4���ֽ�*///

#define	ReversecurrentHappen  1 ///*��������������*///

#define C_RegDataLen                            3               ///*������оƬ�Ĵ���3�ֽ�*///
#define C_ChipID                                0x007022E0      ///*����оƬID     0x7022E0*///
#define C_ChipID_Reg							0x5D			//оƬ�汾ָʾ�Ĵ���
#define C_ReadMeaDataRegFlag					0x00			//���Ĵ�����ȡģʽ���óɶ�ȡ���������Ĵ���
#define C_EventMAXLen					        1024			//��ȡ�¼�����󳤶�


#define C_ACPowerFail	1	 ///*��������Դ*///
#define C_NoACPowerFail	0	 ///*����������Դ*///
#define C_ACPowerFailState  0x11 ///*��������Դ*///

#define	C_Judge_StartBuffer0	0 ///*�ж�buffer�׵�ַ*///
#define C_Judge_StartBuffer1	1 ///*�ж�buffer��2�ֽ�*///
#define	C_Judge_StartBuffer2	2 ///*�ж�buffer��3�ֽ�*///
#define	C_Judge_StartBuffer3	3 ///*�ж�buffer��3�ֽ�*///
#define	C_Judge_StartBuffer4	4 ///*�ж�buffer��4�ֽ�*///
#define	C_Judge_StartBuffer5	5 ///*�ж�buffer��5�ֽ�*///
#define	C_Judge_StartBuffer6	6 ///*�ж�buffer��6�ֽ�*///
#define	C_Judge_StartBuffer7	7 ///*�ж�buffer��7�ֽ�*///

#define	C_ThreeBytesJudge_Buffer1	3///*3�ֽ����ݵ�1����ַ*///
#define	C_ThreeBytesJudge_Buffer2	6///*3�ֽ����ݵ�2����ַ*///
#define	C_ThreeBytesJudge_Buffer3	9///*3�ֽ����ݵ�3����ַ*///
#define	C_FourBytesJudge_Buffer1	4///*3�ֽ����ݵ�1����ַ*///
#define	C_FourBytesJudge_Buffer2	8///*3�ֽ����ݵ�2����ַ*///
#define	C_FourBytesJudge_Buffer3	12///*3�ֽ����ݵ�3����ַ*///

#define C_Judge_10BufferLength      10          //*10���ֽ�buffer����*///
#define	C_Judge_20BufferLength 	20 		//*�����¼��ж�buffer����*///
#define	C_Judge_30BufferLength 	30 		//*������buffer����*///
#define	C_Judge_50BufferLength 	50 		//*��������buffer����*///
#define	C_Judge_110BufferLength 110 	//*д����buffer����*///
#define	C_Judge_300BufferLength 300 	//*д����buffer����698����*///

#define	C_RC_BufferLength 71 		//*��������buffer����*///
#define	C_RC_DirectionBuffer 6 		///����������buffer*///
#define	C_Judge_TimeEndBuffer 7 	///*�ж�ʱ��buffer*///
#define	C_HappenEndTimeLength 12	///*�ж�ʱ��buffer*///
#define	C_EventTimeLength 7 		///*�¼�����ʱ�̳���*///
#define	C_EventHappenTime 0 		///*�¼�����ʱ���ڱ����ռ��һ��*///
#define	C_EventEndTime 1 			///*�¼�����ʱ���ڱ����ռ�ڶ���*///
#define C_DelayTimeLength 1 		///*�¼��ж���ʱʱ�䳤��*///

#define	C_Volage_Length     2 	/*�����ѹ����*/
#define	C_2Volage_Length    4 	/*�����ѹ����*/
#define	C_3Volage_Length    6 	/*�����ѹ����*/
#define	C_4Volage_Length    8 	/*�ж������ѹ����*/

#define	C_Curr4Bytes_Length	4	/*4�ֽڵ�������*/
#define	C_JudgeCurr_Length	4	/*�жϵ�����ֵ����*/

#define	C_Curr_Length       4 	/*�����������*/
#define	C_2Curr_Length      8 	/*�����������*/
#define	C_3Curr_Length      12 	/*�����������*/
#define	C_4Curr_Length      16 	/*�жϼ������������*/

#define	C_Curr4Dig_Length 4 	///*����4λ��������*///
#define	C_2Curr4Dig_Length 8 	///*����2λ��������*///
#define	C_3Curr4Dig_Length 12 	///*����4λ��������*///
#define	C_4Curr4Dig_Length 16 	///*�жϼ�����4λ��������*///

#define	C_Curr3Dig_Length 3 	///*����3λ��������*///
#define	C_2Curr3Dig_Length 6 	///*����3λ��������*///
#define	C_3Curr3Dig_Length 9 	///*����3λ��������*///
#define	C_4Curr3Dig_Length 12 	///*�жϼ�����3λ��������*///

#define	C_Energy_Length			4		///*���ܳ���*///
#define	C_Power_Length			4		/*���ʳ���*/
#define C_Demand_Length 		4		/*��������*/
#define	C_GetHappenEndTime_Length	7	/*�����¼�����ʱ�䳤��*/
#define	C_DemandTime_Length		(C_Demand_Length + C_GetHappenEndTime_Length)		/*����������ʱ�䳤��*/
#define	C_PowerFactor_Length	2		///*������������*///

#define	C_DataCode_Length	4		///*���ݱ�ʶ����*///

#define C_AddTime_Length 		4			///*�ۼ�ʱ�䳤��*///
#define C_AddNumber_Length 		4			///*�ۼƴ�������*///
#define C_AddTimeNumbers_Length		8			///*�ۼƴ�����ʱ�䳤��*///
#define C_Ah_Length 			4			///*Ah����*///
#define C_Unbalance_Length			CLNoBal_Vol_Lim		/*��ƽ���ʳ���*/
#define	C_OverDemandRenew_Length	(C_Demand_Length + C_GetHappenEndTime_Length)		/*���������¼��������ݳ���*/
#define	C_OverDemandRead_Length		20		///*���������¼��������ݳ���*///
#define C_RCurrentDirectionLength 1	///*���������򳤶ȣ�1�ֽ�*///
#define C_PhaseAngle	2	///*��ǳ���*///

#define C_Positivephase 0	///*��ѹ������*///
#define C_Reversephase 	1	///*��ѹ������*///


#define C_MeterWorkState_Length 2			///*�������״̬�ֳ���*///

#define	C_JudgeVolage_Buffer1   2 /*ȫʧѹ�����磬������A���ѹbuffer*/
#define	C_JudgeVolage_Buffer2   4 /*ȫʧѹ�����磬������B���ѹbuffer*/
#define	C_JudgeVolage_Buffer3   6 /*ȫʧѹ�����磬������C���ѹbuffer*/

#define	C_JudgeCurr_Buffer1     4   /*��λС����A�����buffer*/
#define	C_JudgeCurr_Buffer2     8   /*��λС����B�����buffer*/
#define	C_JudgeCurr_Buffer3     12  /*��λС����C�����buffer*/

#define	C_JudgeCurr4Dig_Buffer1 4 ///*4λС����A�����buffer*///
#define	C_JudgeCurr4Dig_Buffer2 8 ///*4λС����B�����buffer*///
#define	C_JudgeCurr4Dig_Buffer3 12 ///*4λС����C�����buffer*///

#define	C_Instant_AcPow_Buffer	        4	/*���ʷ��򣬹���buffer*/

#define C_NoVoltage_HTimeLength 9 ///*ȫʧѹ��ʼʱ�����ݳ���*///
#define C_NoVoltage_VolageLength 9 ///*ȫʧѹ��ʼʱ�����ݳ���*///

#define	C_EERAMChooseNo 		1		///*����ʱ����RAM�е�������*///
#define	C_EEChooseNo 			2		///*����ʱEE�е�������*///
#define	C_OverPowerfactChooseNo 3	  	///*����������������*///
#define	C_OpenCoverChooseNo		4		///*���ϸǵ�������*///
#define	C_EnergyChooseNo 		5		///*���ܵ�������*///
#define	C_DemandChooseNo 		6		///*������������*///
#define	C_PowerAbnormalChooseNo	7		///*��Դ�쳣���㶨�ų����ŵ�������*///
#define	C_HappenCodeRowNo		0		///*�������ݣ�ռ��������һ��*///
#define C_EndCodeRowNo			1		///*�������ݣ�ռ�������ڶ���*///
#define C_HappenDataLengthRowNo	2		///*�������ݳ��ȣ�������������*///
#define C_EndDataLengthRowNo	3		///*�������ݳ��ȣ�ռ������������*///
#define	C_PhaseTypeRowN0		2		///*Event_ChooseTableNo���������*///

#define C_EnergyRead_Length 31
#define C_EnergyRead_Length1 24

#define	C_Length_One 1
#define	C_Length_Two 2
#define	C_Length_Three 3
#define	C_Length_Four 4
#define	C_Length_Five 5
#define	C_Length_Six 6
#define	C_Length_Seven 7
#define	C_Length_Eight 8
#define	C_Length_Nine 9
#define	C_Length_Ten 10
#define	C_Length_Eleven 11
#define	C_Length_Twelve 12

#define	C_Bit0_Start	0x01
#define C_Bit1_Start	0x02
#define C_Bit2_Start	0x04
#define C_Bit3_Start	0x08
#define C_Bit4_Start	0x10
#define C_Bit5_Start	0x20
#define C_Bit6_Start	0x40
#define C_Bit7_Start	0x80

#define	C_Bit0_End	0xFE
#define	C_Bit1_End	0xFD
#define	C_Bit2_End	0xFB
#define	C_Bit3_End	0xF7
#define	C_Bit4_End	0xEF
#define	C_Bit5_End	0xDF
#define	C_Bit6_End	0xBF
#define	C_Bit7_End	0x7F

#define C_Bit_MainPower 0xF9  ///*�������״̬��3����Դ�������ͣ�����Դ����*///

/*�̵�������������ƫ��*/
#define C_RelayDescrip_Offset           2     /*�̵�����������������ʼƫ��*/
#define C_RelayCurrentState_Offset      8     /*�̵���״̬�� ������ʼƫ��*/
#define C_RelaySwitchNature_Offset      10    /*�̵����������ԣ� ������ʼƫ��*/
#define C_RelayWiringState_Offset       12    /*�̵�������״̬�� ������ʼƫ��*/

///*698����645����*///

#define C_Degree     0x01   ///*��������־*///
#define C_Time       0x02   ///*��ʱ���־*///

#define C_AddTimeDataNumbersLength   53  ///*һ����38���¼��ۼ�ʱ�� ����15���¼�*///
#define	C_AddAhBaseNo		13///*����Ah�ı����EventNo��Ӧ������12��*///
#define	C_AddTimeBaseNo		11///*�����ۼ�ʱ��ı������11��*///
#define	C_UnbalanceBaseNo	68///*��ƽ��ʵʱ����CommunicateReadTable[NO]��Ӧ��Ų�ֵ*///
#define	C_SUnbalanceBaseNo	48///*���ز�ƽ��ʵʱ����CommunicateReadTable[NO]��Ӧ��Ų�ֵ*///
#define	C_OverDemandBaseNo	34///*����������CommunicateReadTable[NO]��Ӧ��Ų�ֵ*///

#pragma pack(1) ///*1�ֽڶ���*///
typedef struct
{
	ulong32		V_ulID_Code;     	///*��ʶ�� ���ڶ�����*///
	ulong32	 	V_ucRAMAddr;		///*RAM�����ݵ�ַ*///
	uchar8 		V_ucNum;			///*RAM�����ݳ���*///
}Str_EnergyRead_Type;


typedef struct
{		
	ulong32	DataCode;		///*���ݱ�ʶ��*///
	uchar8	*DataRAMAddr;	///*������RAM�׵�ַ*///
	uchar8	*CRCRAMAddr;	///*CRC RAM�׵�ַ*///	
	uchar8	Length;			///*���ݳ���*///
	uchar8	EventNo;		///*������������EventNo*///
}Str_CommunicateReadTable_Type;	///*ͨ�ų������*///

#pragma pack() ///*1�ֽڶ���*///

#pragma pack(2) ///*1�ֽڶ���*///
typedef struct
{			                    	
	uchar8		*P_Str;				///*RAM��ַ*//
	uchar8		*P_CRCAddr;			///*CRC��ַ*///
	ushort16	Length;				///*����*///
	ulong32		P_State;			///*״̬�����ݱ�ʶ*/// 
	ushort16	V_Happen;			///*�¼�������*///	
	ushort16	V_End;				///*�¼�������*///  
	uchar8  	*P_BellAlarm;		///*С��������״̬��*/// 
	uchar8  	*P_AlarmOuput;		///*�������״̬��*///
	uchar8  	*P_BackLightAlarm;	///*���ⱨ��״̬��*///
	ushort16	V_AlarmStart;		///*����������*///		
	ushort16	V_AlarmClose;		///*����������*///  
}Str_CommunicateEventClearTable_Type;///*ͨ��������1*///

#define C_EventSymbolLength		10	///*������ѹ�����ܹ���10��*///

#define C_AVoltage_SymbolNO		0	///*A���ѹ����״̬*///
#define C_BVoltage_SymbolNO		1	///*B���ѹ����״̬*///
#define C_CVoltage_SymbolNO		2	///*C���ѹ����״̬*///
#define C_ACurrentminus_SymbolNO	3	///*A���������״̬*///
#define C_BCurrentminus_SymbolNO	4	///*B���������״̬*///
#define C_CCurrentminus_SymbolNO	5	///*C���������״̬*///
#define C_ACurrent_SymbolNO		6	///*A���������״̬*///
#define C_BCurrent_SymbolNO		7	///*B���������״̬*///
#define C_CCurrent_SymbolNO		8	///*C���������״̬*///
#define C_Reversephase_SymbolNO	9	///*���������״̬*///
#define	C_DisplayMsgPT1			0       ///*��ʾ��Ŀ*///
#define	C_DisplayMsgType1		1       ///*��˸/����/����*///
#define C_DisplayMsgTime1H		2       ///*��ʾʱ��*///
#define C_DisplayMsgTime1L		3       ///*��ʾʱ��*///
#define	C_DisplayMsgPT2			4       ///*��ʾ��Ŀ*///
#define	C_DisplayMsgType2		5       ///*��˸/����/����*///
#define C_DisplayMsgTime2H		6       ///*��ʾʱ��*///
#define C_DisplayMsgTime2L		7       ///*��ʾʱ��*///


typedef struct 
{
	uchar8     A0_Flag; ///*bit0ʧѹ��bit1���أ�bit2���ʷ���bit3ʧ����bit4���࣬bit5������bit6��ѹ��bit7Ƿѹ*///
    uchar8     A1_Flag;///*bit0����,bit1������������*///
    uchar8     B0_Flag;
    uchar8     B1_Flag;
	uchar8     C0_Flag;
    uchar8     C1_Flag;
    uchar8     T0_Flag;  ///*bit0��ѹ������bit1����������bit2ʱ�ӵ��Ƿѹ��bit3�ܳ�������bit4�ܹ������������ޣ�bit5��ѹ��ƽ�⣬bit6������ƽ�⣬bit7�������ز�ƽ��*///
	uchar8     T1_Flag;  ///*bit0�������ޣ�bit1����ǣ�bit2����β�ǣ�bit3���磬bit4ȫʧѹ��bit5�㶨�ų���bit6��Դ�쳣��bit7������Դʧ��*///        
}Str_BeeperAlerm_Type;		///*������ǰ״̬*///

typedef struct
{
	uchar8 	BellAlarmNo;		///*С�������*///   
	uchar8 	AlarmOutputNo;			///*����������*///   
	uchar8 	BacklightAlarmLNo;	///*�������*///   
}Str_AlarmByteNo_Type;///*�������״̬���ڱ���ģʽ�ֶ���������ռ�Ļ������*///

#define C_BacklightAlarm_ABC0ByteNo  	0	///*�����¼����ⱨ���ڱ���ģʽ�ֶ���������ռ���ֽ�*///
#define C_BacklightAlarm_ABC1ByteNo	1	///*�����¼����ⱨ���ڱ���ģʽ�ֶ���������ռ���ֽ�*///
#define C_BacklightAlarm_T0ByteNo	        2	///*�����¼����ⱨ���ڱ���ģʽ�ֶ���������ռ���ֽ�*///
#define C_BacklightAlarm_T1ByteNo	        3	///*�����¼����ⱨ���ڱ���ģʽ�ֶ���������ռ���ֽ�*///
#define C_Alarmoutput_ABC0ByteNo         	4	///*�����¼���������ڱ���ģʽ�ֶ���������ռ���ֽ�*///
#define C_Alarmoutput_ABC1ByteNo	        5	///*�����¼���������ڱ���ģʽ�ֶ���������ռ���ֽ�*///
#define C_Alarmoutput_T0ByteNo	        6	///*�����¼���������ڱ���ģʽ�ֶ���������ռ���ֽ�*///
#define C_Alarmoutput_T1ByteNo	        7	///*�����¼���������ڱ���ģʽ�ֶ���������ռ���ֽ�*///
#define C_BellAlarm_ABC0ByteNo		8	///*�����¼�С�����ڱ���ģʽ�ֶ���������ռ���ֽ�*///
#define C_BellAlarm_ABC1ByteNo		9	///*�����¼�С�����ڱ���ģʽ�ֶ���������ռ���ֽ�*///
#define C_BellAlarm_T0ByteNo		        10	///*�����¼�С�����ڱ���ģʽ�ֶ���������ռ���ֽ�*///
#define C_BellAlarm_T1ByteNo		        11	///*�����¼�С�����ڱ���ģʽ�ֶ���������ռ���ֽ�*///*�ڱ���״̬�ֶ�����������ռλ��*///
#define	C_AlarmModeLength		        12	///*����ģʽ�ֳ���*///
#define	C_AlarmTempLength		        8	///*��������ʱ��������*///
#define	C_AlarmTempBitLength		        64	///*��������ʱ����Bitλ��*///
#define	C_CurrentBitAlarmHappen		        1	///*��ǰλ��������*///
#define	C_SendAlarmMessage		        1	///*���ͱ�����Ϣ*///
#define	C_NOAlarmMessage		        0	///*���ͱ�����Ϣ*///

#pragma pack() ///*2�ֽڶ���*///
#pragma pack(1)
typedef struct
{
	uchar8	*P_TotalAhAddr;				///*��Ah*///
	uchar8	*P_AAhAddr;					///*A��Ah*///
	uchar8	*P_BAhAddr;					///*B��Ah*///
	uchar8	*P_CAhAddr;					///*C��Ah*///
}Str_AhCountTable_Type;	

typedef struct
{
	uchar8 	MeterState;							/*�¼�״̬������־λ*/
	uchar8 	Time[CLDate_Time];					/*�͹���״̬��ȫʧѹʱ��*/
	uchar8 	AddTime[C_AddTime_Length];			/*���ۼ�ʱ��*/
	uchar8 	NoVoltageCurrent[C_3Curr_Length];	/*�͹�����ȫʧѹ����*/
	uchar8	V_CRC[2];
}Str_LpowerTvoltagelose_Type;		/*ȫʧѹ�͹��Ľṹ��*/
extern	Str_LpowerTvoltagelose_Type	GStr_PowerfailStr;			/*����*/


typedef struct
{
	uchar8	OpenCoverState;				/*�����¼�״̬*/
	uchar8	HappenTime[CLDate_Time];	/*����ʱ��*/
	uchar8	CloseCoverState;			/*�ϸ��¼�״̬*/
	uchar8	EndTime[CLDate_Time];		/*�ϸ�ʱ��*/
	uchar8 	AddTime[C_AddTime_Length];	/*���ۼ�ʱ��*/
	uchar8	V_CRC[2];
}Str_CoverRecord_Type;			/*�͹����¿��ϸ��¼��ṹ��*/

typedef struct
{
	uchar8 	MeterState;					/*�¼�״̬��־λ*/
	uchar8 	Time[CLDate_Time];			/*�͹������¼�����ʱ��*/
	uchar8 	AddTime[C_AddTime_Length];	/*���ۼ�ʱ��*/
	uchar8	V_CRC[2];
}Str_ACPowerFail_Type;		/*��Դ�쳣�¼��ṹ��*/


typedef struct
{
	uchar8	Renewal[C_Demand_Length];				/*�¼������������������*/
	uchar8	RenewalTime[C_GetHappenEndTime_Length];	/*������������������ʱ��*/
	uchar8 	MeterState;								/*�¼�״̬*/
	uchar8 	AddTime[C_AddTime_Length];				/*���ۼ�ʱ��*/
	uchar8	V_CRC[2];
}Str_ActiveDemand_Type;			/*�й����������¼��¼��ṹ�壨�޹�����¼�¼�״̬��*/


typedef struct
{
	uchar8	Renewal[C_Unbalance_Length];	/*�¼���������������*/
	uchar8 	AddTime[C_AddTime_Length];		/*���ۼ�ʱ��*/
	uchar8	V_CRC[2];
}Str_Unbanlance_Type;		/*��ƽ���¼��ṹ��*/

typedef struct
{
	uchar8	Renewal[C_Ah_Length];	/*��Ah*/
	uchar8	ARenewal[C_Ah_Length];	/*A��Ah RAM����*/
	uchar8	BRenewal[C_Ah_Length];	/*B��Ah RAM����*/
	uchar8	CRenewal[C_Ah_Length];	/*C��Ah RAM����*/
	uchar8	Ah[C_Ah_Length];		/*����0.01Ah*/
	uchar8	AAh[C_Ah_Length];		/*A�಻��0.01Ah*/
	uchar8 	BAh[C_Ah_Length];		/*B�಻��0.01Ah*/
	uchar8	CAh[C_Ah_Length];		/*C�಻��0.01Ah*/
	uchar8	AddTime[C_AddTime_Length];	/*���ۼ�ʱ��*/
	uchar8	V_CRC[2];
}Str_AhMeter_Type;			/*Ah���ṹ��*/

typedef struct
{
	uchar8	AddTime[C_AddTime_Length];	/*���ۼ�ʱ��*/
	uchar8	V_CRC[2];
}Str_OtherMeter_Type;		/*�����¼��ṹ��*/

#define	C_CRC_Length	2						/////*CRC����*///
#define	C_Str_LpowerTvoltagelose_TypeLength	sizeof(Str_LpowerTvoltagelose_Type)					///*ȫʧѹ�͹��Ľṹ�峤��*///
#define	C_Str_LpowerTvoltagelose_Length		sizeof(Str_LpowerTvoltagelose_Type)-C_CRC_Length	///*ȫʧѹ�͹������ݳ���*///
#define	C_Str_CoverRecord_TypeLength		sizeof(Str_CoverRecord_Type)						///*�͹����¿��ϸ��¼��ṹ�峤��*///
#define	C_Str_CoverRecord_Length			sizeof(Str_CoverRecord_Type)-C_CRC_Length			///*�͹����¿��ϸ��¼����ݳ���*///
#define	C_Str_ACPowerFail_TypeLength		sizeof(Str_ACPowerFail_Type)						///*�͹����µ�Դ�쳣�¼��ṹ�峤��*///
#define	C_Str_ACPowerFail_Length			sizeof(Str_ACPowerFail_Type)-C_CRC_Length			///*�͹����µ�Դ�쳣�¼����ݳ���*///
#define	C_Str_ActiveDemand_TypeLength		sizeof(Str_ActiveDemand_Type)						///*�й����������¼��ṹ�峤��*///
#define	C_Str_ActiveDemand_Length			sizeof(Str_ActiveDemand_Type)-C_CRC_Length			///*�й������������ݳ���*///
#define	C_Str_Unbanlance_TypeLength			sizeof(Str_Unbanlance_Type)							///*��ƽ���¼��ṹ�峤��*///
#define	C_Str_Unbanlance_Length				sizeof(Str_Unbanlance_Type)-C_CRC_Length			///*��ƽ�����ݳ���*///
#define	C_Str_AhMeter_TypeLength			sizeof(Str_AhMeter_Type)							///*Ah�¼��ṹ�峤��*///
#define	C_Str_AhMeter_Length				sizeof(Str_AhMeter_Type)-C_CRC_Length				///*Ah���ݳ���*///
#define	C_Str_OtherMeter_TypeLength			sizeof(Str_OtherMeter_Type)							///*�����¼��ṹ�峤��*///
#define	C_Str_OtherMeter_Length				sizeof(Str_OtherMeter_Type)-C_CRC_Length			///*�������ݳ���*///

#define	C_OpenMeterCoverLowPower		55	///*���ڵ͹�����д��Ϣ*///
#define	C_CloseMeterCoverLowPower		66	///*���ڵ͹�����д��Ϣ*///
#define	C_OpenTerminalCoverLowPower		77	///*���ڵ͹�����д��Ϣ*///
#define	C_CloseTerminalCoverLowPower	88	///*���ڵ͹�����д��Ϣ*///

#define	C_REventE			0x20	///*bit5	�лָ��ϱ�����*///
#define	C_REventH			0x10	///*bit4	�з����ϱ�*///
#define	C_REventEConfirm	0x08	///*bit3�ָ��ϱ�ȷ�ϱ�־*///
#define	C_REventEReport		0x04	///*bit2�ָ����ϱ���־*///
#define	C_REventHConfirm	0x02	///*bit1	�����ϱ�ȷ�ϱ�־*///
#define	C_REventHReport		0x01	///*bit0	�������ϱ���־*///
#define C_REventReport      C_REventHReport|C_REventEReport     ///*����/�����ϱ�*///
#define C_REventConfirm     C_REventHConfirm|C_REventEConfirm   ///*����/�����ϱ�*///

typedef struct
{
	uchar8	EventNo;		///*�¼���*///
	uchar8	SourceFlag;		///*�¼�����Դ��־0x00�ޣ�0x01��*///
	ulong32	Degree;			///*�¼�����*///
	ulong32	OADTab;			///*�¼�����OAD*///
	ulong32	WriteOAD;		///*д�¼�OAD*///
}Str_EventMapping_Type;

#define	C_SourceNon	0x00	///*�޷���Դ*///
#define	C_SourceExist	0x01	///*�з���Դ*///

typedef struct
{
	ulong32	EventOAD;		///*�¼�OAD*///
	ulong32	AddTimeOAD;		///*�¼����ۼ�ʱ��*///
	ulong32	TolAh;			///*�¼��ܰ�ʱ���߲�ƽ����*///
	ulong32	AAh;			///*�¼�A�లʱ��*///
	ulong32	BAh;			///*�¼�B�లʱ��*///
	ulong32	CAh;			///*�¼�C�లʱ��*///
}Str_SpecialReadTable_Type;

typedef struct
{
	ulong32	EventOAD;		///*�¼�OAD*///
	uchar8	Source;			///*����Դ*///
	uchar8	EventNo;		///*�¼���*///
	ushort16 EventTimeStatus;///*ʱ��״̬��OAD�ĵ����ֽڣ����Ժ�+����������*///
	ulong32	Degree;		///*�¼���������*///
	ulong32	AddTime;		///*�¼��ۼ�ʱ��*///
}Str_CurrentDataReadTable_Type;
typedef struct
{
	ulong32	EventOAD;		///*�¼�OAD*///
	ulong32	Source;			///*����Դ*///
	uchar8	EventNo;		///*�¼���*///
}Str_CurrentDataReadTable1_Type;



#define C_Type1                 0x68                ///*���ֶ������ۼ�ʱ������������һ�η���ʱ��*///
#define C_Type2                 0x86                ///*���ֶ������ۼ�ʱ������������һ�η���ʱ��*///
#define	C_TolAh_E				0x20296201	       	///*�¼��ڼ���Ah��*///
#define	C_AAh_E					0x20296202	       	///*�¼��ڼ�A��Ah��*///
#define	C_BAh_E					0x20296203	       	///*�¼��ڼ�B��Ah��*///
#define	C_CAh_E					0x20296204	       	///*�¼��ڼ�C��Ah��*///
#define C_CurUnbalanceRate_E	0x20276200			///*�¼������ڼ������ƽ����*///

extern uchar8 SF_JudgeAllAA(uchar8 *P_DataBuf,uchar8 P_DataLen);

#define	C_AllEventNo					0xAA	///*���ڱ�������*///

#pragma pack()
///*****************************************************************************************///
///*���ݲ㶨���ɾ��*///
///*****************************************************************************************///
extern uchar8 SF_ReadOneReg_MeterIC(uchar8 V_usRegAddr, uchar8* P_Data,uchar8 V_MeaORCal);
void SF_Sub_Sec(uchar8 Sec1,uchar8 Sec2,ulong32 *SubMins);
extern void SF_InitRTCState(void);
void SF_FrozenDataFF_NextNum(Struct_FrozenConvert_Type *str_Encode,ushort16 V_usLineNum);
extern uchar8 SF_FrozenData_JudgeRateNum(ushort16 V_ucLineNum, ulong32 V_ulOAD);
extern void SF_Event_SpecificDataLenCal(ulong32 V_ulROAD, uchar8 *V_ucDataLen);

#define CLoss_TollVol_Attri14_Nature		0x0E01
#define CLossA_Vol_Attri14_Nature			0x0E02
#define CLossB_Vol_Attri14_Nature			0x0E03
#define CLossC_Vol_Attri14_Nature			0x0E04
#define CLowA_Vol_Attri14_Nature			0x0E02
#define CLowB_Vol_Attri14_Nature			0x0E03
#define CLowC_Vol_Attri14_Nature			0x0E04
#define COverA_Vol_Attri14_Nature			0x0E02
#define COverB_Vol_Attri14_Nature			0x0E03
#define COverC_Vol_Attri14_Nature			0x0E04
#define CBreakA_Vol_Attri14_Nature			0x0E02
#define CBreakB_Vol_Attri14_Nature			0x0E03
#define CBreakC_Vol_Attri14_Nature			0x0E04
#define CLossA_Curr_Attri14_Nature			0x0E02
#define CLossB_Curr_Attri14_Nature			0x0E03
#define CLossC_Curr_Attri14_Nature			0x0E04
#define COverA_Curr_Attri14_Nature			0x0E02
#define COverB_Curr_Attri14_Nature			0x0E03
#define COverC_Curr_Attri14_Nature			0x0E04
#define CBreakA_Curr_Attri14_Nature			0x0E02
#define CBreakB_Curr_Attri14_Nature			0x0E03
#define CBreakC_Curr_Attri14_Nature			0x0E04
#define CPowerT_Rev_Attri14_Nature			0x0E01
#define CPowerA_Rev_Attri14_Nature			0x0E02
#define CPowerB_Rev_Attri14_Nature			0x0E03
#define CPowerC_Rev_Attri14_Nature			0x0E04
#define COverA_Lo_Attri14_Nature			0x0E02
#define COverB_Lo_Attri14_Nature			0x0E03
#define COverC_Lo_Attri14_Nature			0x0E04
#define CPos_Ac_De_Over_Attri7_Nature		0x0A00
#define CRev_Ac_De_Over_Attri7_Nature		0x0A00
#define CQua1_Re_De_Over_Attri14_Nature		0x0E01
#define CQua2_Re_De_Over_Attri14_Nature		0x0E02
#define CQua3_Re_De_Over_Attri14_Nature		0x0E03
#define CQua4_Re_De_Over_Attri14_Nature		0x0E04
#define CPFactorT_Over_Attri14_Nature		0x0E01
#define CPFactorA_Over_Attri14_Nature		0x0E02
#define CPFactorB_Over_Attri14_Nature		0x0E03
#define CPFactorC_Over_Attri14_Nature		0x0E04
#define CAll_Loss_Vol_Attri7_Nature			0x0A00
#define CAux_Pow_Down_Attri7_Nature			0x0A00
#define CRevPS_Vol_Attri7_Nature			0x0A00
#define CRevPS_Curr_Attri7_Nature			0x0A00
#define CPow_Down_Attri7_Nature				0x0A00
#define CProgram_Attri7_Nature				0x0A00
#define CTol_Clear_Attri7_Nature			0x0A00
#define CDe_Clear_Attri7_Nature				0x0A00
#define CEven_Clear_Attri7_Nature			0x0A00
#define CAdjTime_Attri7_Nature				0x0A00
#define CProgPT_Attri7_Nature				0x0A00
#define CProgTZ_Attri7_Nature				0x0A00
#define CProgWRe_Attri7_Nature				0x0A00
#define CProgSettD_Attri7_Nature			0x0A00
#define COpenW_Attri7_Nature				0x0A00
#define COpenCW_Attri7_Nature				0x0A00
#define CNoBal_Vol_Attri7_Nature			0x0A00
#define CNoBal_Curr_Attri7_Nature			0x0A00
#define CRelayOpen_Attri7_Nature			0x0A00
#define CRelayClose_Attri7_Nature			0x0A00
#define CProgHol_Attri7_Nature				0x0A00
#define CProgAcC_Attri7_Nature				0x0A00
#define CProgReC_Attri7_Nature				0x0A00
#define CProgTPara_Attri7_Nature			0x0A00
#define CProgLad_Attri7_Nature				0x0A00
#define CProgKD_Attri7_Nature				0x0A00
#define CAbnorC_Attri7_Nature				0x0A00
#define CBuyCurr_Attri7_Nature				0x0A00
#define CReturn_M_Attri7_Nature				0x0A00
#define CConM_Attri7_Nature					0x0A00
#define CRelayFa_Attri7_Nature				0x0A00
#define CPowerFa_Attri7_Nature				0x0A00
#define CSevNoBal_Curr_Attri7_Nature		0x0A00
#define CClockFa_Attri7_Nature				0x0A00
#define CMeterFa_Attri7_Nature				0x0A00
#define CBroadcastTime_Attri7_Nature		0x0A00
#define CNeutralCurrentAbnormal_Attri7_Nature	0x0A00
#define CBroadTimeAbnormal_Attri7_Nature	0x0A00

#define C_Evt       1   /*�¼���¼*/
#define C_Frz       2   /*����*/

#define C_Need      1   /*�¼���¼��ȡ����ʱ���ж϶�Ӧ�����б�OAD�����Ƿ���Ҫȡ���ݣ���Ҫ*/
#define C_NoNeed    2   /*����Ҫ*/

typedef struct
{
	uchar8	(*EvtJudgeFunc)(uchar8 EventNo,uchar8 Hstate);
}Str_EvtJudge;

typedef struct
{
	ulong32 V_ulOAD;
	uchar8 V_ucLen;
}Str_EvtFixRCSD_Type;

#endif


