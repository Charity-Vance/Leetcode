
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
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
///*口线暂时定义，待程序拼接后删除*///
///*****************************************************************************************///
#define	C_LowPowerHappen_EventMsg	0x99	///*低功耗下事件状态，有发生无恢复*///
#define	C_LowPowerEnd_EventMsg	0x88	///*低功耗下事件状态，非有发生无恢复*///

#define	C_TpowerDirection_Forward	0x00	///*总功率反向，正向*///
#define	C_TpowerDirection_Reverse	0x01	///*总功率反向，反向*///
#define	C_TpowerDirection_Close		0x88	///*总功率反向关闭方向*///
#define	C_TpowerDirection_Init		0x66	///*总功率反向初始化方向*///

#define	C_Happen_EventMsg	0x68	///*事件发生动作*///
#define	C_End_EventMsg		0x66	///*事件恢复动作*///
#define	C_Null_EventMsg		0x00	///*事件无动作*///

#define C_JudgeTimeError  77		///*判断时间阀值返回错误*///
#define	C_Judge_Event_DefaultTime1	0x3C	///*默认事件判断时间阀值*///
#define	C_Close_Parameter			0x00	///*事件判断阀值为0*///
#define	C_Judge_Time0				0x00	///*事件判断时间为0s*///
#define	C_Judge_Time1				0x01	///*事件判断时间为1s*///
#define	C_Judge_Time2				0x02	///*事件判断时间为2s*///
#define	C_Judge_Time3				0x03	///*事件判断时间为3s*///
#define	C_Judge_Time4				0x05	///*事件判断时间为5s*///

#define	C_EventNoLength		0x37				///*事件个数*///
#define	C_EventNoLength1	C_EventNoLength-1	///*有发生无恢复事件个数*///
#define	C_ReadDataLength	115					///*支持读的数据总个数*///

#define	C_Event_MsgLength	10			///*判断消息发消息时数据长度*///
#define	C_PTEventNo_Msgbuffer	0				///*消息中，EventNo_PT缓存///
#define	C_EventNo_Msgbuffer		1				///*消息中，EventNo缓存///
#define	C_PTTime_Msgbuffer	    2				///*消息中，Time_PT缓存///
#define	C_Time_Msgbuffer	    3				///*消息中，Time缓存///

#define	C_3Wire	2			///*三相三线相数*///
#define	C_4Wire	3			///*三相四线相数*///


#define	C_TenThousand_times		10000///*10000倍*///
// #define	C_Ulong32_Length	4	///*4个字节*///

#define	ReversecurrentHappen  1 ///*潮流反向发生发生*///

#define C_RegDataLen                            3               ///*读计量芯片寄存器3字节*///
#define C_ChipID                                0x007022E0      ///*计量芯片ID     0x7022E0*///
#define C_ChipID_Reg							0x5D			//芯片版本指示寄存器
#define C_ReadMeaDataRegFlag					0x00			//将寄存器读取模式设置成读取计量参数寄存器
#define C_EventMAXLen					        1024			//读取事件的最大长度


#define C_ACPowerFail	1	 ///*带辅助电源*///
#define C_NoACPowerFail	0	 ///*不带辅助电源*///
#define C_ACPowerFailState  0x11 ///*带辅助电源*///

#define	C_Judge_StartBuffer0	0 ///*判断buffer首地址*///
#define C_Judge_StartBuffer1	1 ///*判断buffer第2字节*///
#define	C_Judge_StartBuffer2	2 ///*判断buffer第3字节*///
#define	C_Judge_StartBuffer3	3 ///*判断buffer第3字节*///
#define	C_Judge_StartBuffer4	4 ///*判断buffer第4字节*///
#define	C_Judge_StartBuffer5	5 ///*判断buffer第5字节*///
#define	C_Judge_StartBuffer6	6 ///*判断buffer第6字节*///
#define	C_Judge_StartBuffer7	7 ///*判断buffer第7字节*///

#define	C_ThreeBytesJudge_Buffer1	3///*3字节数据第1个地址*///
#define	C_ThreeBytesJudge_Buffer2	6///*3字节数据第2个地址*///
#define	C_ThreeBytesJudge_Buffer3	9///*3字节数据第3个地址*///
#define	C_FourBytesJudge_Buffer1	4///*3字节数据第1个地址*///
#define	C_FourBytesJudge_Buffer2	8///*3字节数据第2个地址*///
#define	C_FourBytesJudge_Buffer3	12///*3字节数据第3个地址*///

#define C_Judge_10BufferLength      10          //*10个字节buffer长度*///
#define	C_Judge_20BufferLength 	20 		//*其他事件判断buffer长度*///
#define	C_Judge_30BufferLength 	30 		//*读数据buffer长度*///
#define	C_Judge_50BufferLength 	50 		//*清零数据buffer长度*///
#define	C_Judge_110BufferLength 110 	//*写数据buffer长度*///
#define	C_Judge_300BufferLength 300 	//*写数据buffer长度698新增*///

#define	C_RC_BufferLength 71 		//*潮流反向buffer长度*///
#define	C_RC_DirectionBuffer 6 		///潮流反向方向buffer*///
#define	C_Judge_TimeEndBuffer 7 	///*判断时间buffer*///
#define	C_HappenEndTimeLength 12	///*判断时间buffer*///
#define	C_EventTimeLength 7 		///*事件发生时刻长度*///
#define	C_EventHappenTime 0 		///*事件发生时刻在表格中占第一列*///
#define	C_EventEndTime 1 			///*事件结束时刻在表格中占第二列*///
#define C_DelayTimeLength 1 		///*事件判断延时时间长度*///

#define	C_Volage_Length     2 	/*单相电压长度*/
#define	C_2Volage_Length    4 	/*两相电压长度*/
#define	C_3Volage_Length    6 	/*三相电压长度*/
#define	C_4Volage_Length    8 	/*判断三相电压长度*/

#define	C_Curr4Bytes_Length	4	/*4字节电流长度*/
#define	C_JudgeCurr_Length	4	/*判断电流阀值长度*/

#define	C_Curr_Length       4 	/*单相电流长度*/
#define	C_2Curr_Length      8 	/*两相电流长度*/
#define	C_3Curr_Length      12 	/*三相电流长度*/
#define	C_4Curr_Length      16 	/*判断及三相电流长度*/

#define	C_Curr4Dig_Length 4 	///*单相4位电流长度*///
#define	C_2Curr4Dig_Length 8 	///*两相2位电流长度*///
#define	C_3Curr4Dig_Length 12 	///*三相4位电流长度*///
#define	C_4Curr4Dig_Length 16 	///*判断及三相4位电流长度*///

#define	C_Curr3Dig_Length 3 	///*单相3位电流长度*///
#define	C_2Curr3Dig_Length 6 	///*三相3位电流长度*///
#define	C_3Curr3Dig_Length 9 	///*三相3位电流长度*///
#define	C_4Curr3Dig_Length 12 	///*判断及三相3位电流长度*///

#define	C_Energy_Length			4		///*电能长度*///
#define	C_Power_Length			4		/*功率长度*/
#define C_Demand_Length 		4		/*需量长度*/
#define	C_GetHappenEndTime_Length	7	/*需量事件发生时间长度*/
#define	C_DemandTime_Length		(C_Demand_Length + C_GetHappenEndTime_Length)		/*需量及发生时间长度*/
#define	C_PowerFactor_Length	2		///*功率因数长度*///

#define	C_DataCode_Length	4		///*数据标识长度*///

#define C_AddTime_Length 		4			///*累计时间长度*///
#define C_AddNumber_Length 		4			///*累计次数长度*///
#define C_AddTimeNumbers_Length		8			///*累计次数、时间长度*///
#define C_Ah_Length 			4			///*Ah长度*///
#define C_Unbalance_Length			CLNoBal_Vol_Lim		/*不平衡率长度*/
#define	C_OverDemandRenew_Length	(C_Demand_Length + C_GetHappenEndTime_Length)		/*需量超限事件，读数据长度*/
#define	C_OverDemandRead_Length		20		///*需量超限事件，读数据长度*///
#define C_RCurrentDirectionLength 1	///*潮流反向方向长度，1字节*///
#define C_PhaseAngle	2	///*相角长度*///

#define C_Positivephase 0	///*电压正相序*///
#define C_Reversephase 	1	///*电压逆相序*///


#define C_MeterWorkState_Length 2			///*电表运行状态字长度*///

#define	C_JudgeVolage_Buffer1   2 /*全失压、掉电，逆相序，A相电压buffer*/
#define	C_JudgeVolage_Buffer2   4 /*全失压、掉电，逆相序，B相电压buffer*/
#define	C_JudgeVolage_Buffer3   6 /*全失压、掉电，逆相序，C相电压buffer*/

#define	C_JudgeCurr_Buffer1     4   /*三位小数，A相电流buffer*/
#define	C_JudgeCurr_Buffer2     8   /*三位小数，B相电流buffer*/
#define	C_JudgeCurr_Buffer3     12  /*三位小数，C相电流buffer*/

#define	C_JudgeCurr4Dig_Buffer1 4 ///*4位小数，A相电流buffer*///
#define	C_JudgeCurr4Dig_Buffer2 8 ///*4位小数，B相电流buffer*///
#define	C_JudgeCurr4Dig_Buffer3 12 ///*4位小数，C相电流buffer*///

#define	C_Instant_AcPow_Buffer	        4	/*功率反向，功率buffer*/

#define C_NoVoltage_HTimeLength 9 ///*全失压起始时刻数据长度*///
#define C_NoVoltage_VolageLength 9 ///*全失压起始时刻数据长度*///

#define	C_EERAMChooseNo 		1		///*发生时包含RAM中调整数据*///
#define	C_EEChooseNo 			2		///*发生时EE中调整数据*///
#define	C_OverPowerfactChooseNo 3	  	///*功率因数调整数据*///
#define	C_OpenCoverChooseNo		4		///*开合盖调整数据*///
#define	C_EnergyChooseNo 		5		///*电能调整数据*///
#define	C_DemandChooseNo 		6		///*需量调整数据*///
#define	C_PowerAbnormalChooseNo	7		///*电源异常、恒定磁场干扰调整数据*///
#define	C_HappenCodeRowNo		0		///*发生数据，占调整表格第一列*///
#define C_EndCodeRowNo			1		///*结束数据，占调整表格第二列*///
#define C_HappenDataLengthRowNo	2		///*发生数据长度，调整表格第三列*///
#define C_EndDataLengthRowNo	3		///*结束数据长度，占调整表格第四列*///
#define	C_PhaseTypeRowN0		2		///*Event_ChooseTableNo表格中列数*///

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

#define C_Bit_MainPower 0xF9  ///*电表运行状态字3，电源供电类型，主电源供电*///

/*继电器描述符数据偏移*/
#define C_RelayDescrip_Offset           2     /*继电器描述符，数据起始偏移*/
#define C_RelayCurrentState_Offset      8     /*继电器状态， 数据起始偏移*/
#define C_RelaySwitchNature_Offset      10    /*继电器开关属性， 数据起始偏移*/
#define C_RelayWiringState_Offset       12    /*继电器接线状态， 数据起始偏移*/

///*698兼容645新增*///

#define C_Degree     0x01   ///*读次数标志*///
#define C_Time       0x02   ///*读时间标志*///

#define C_AddTimeDataNumbersLength   53  ///*一共有38个事件累计时间 新增15个事件*///
#define	C_AddAhBaseNo		13///*计算Ah的表格与EventNo对应，少了12个*///
#define	C_AddTimeBaseNo		11///*计算累计时间的表格，少了11个*///
#define	C_UnbalanceBaseNo	68///*不平衡实时量与CommunicateReadTable[NO]对应序号差值*///
#define	C_SUnbalanceBaseNo	48///*严重不平衡实时量与CommunicateReadTable[NO]对应序号差值*///
#define	C_OverDemandBaseNo	34///*需量超限与CommunicateReadTable[NO]对应序号差值*///

#pragma pack(1) ///*1字节对齐*///
typedef struct
{
	ulong32		V_ulID_Code;     	///*标识码 用于读电能*///
	ulong32	 	V_ucRAMAddr;		///*RAM里数据地址*///
	uchar8 		V_ucNum;			///*RAM里数据长度*///
}Str_EnergyRead_Type;


typedef struct
{		
	ulong32	DataCode;		///*数据标识码*///
	uchar8	*DataRAMAddr;	///*读数据RAM首地址*///
	uchar8	*CRCRAMAddr;	///*CRC RAM首地址*///	
	uchar8	Length;			///*数据长度*///
	uchar8	EventNo;		///*所读数据所在EventNo*///
}Str_CommunicateReadTable_Type;	///*通信抄读表格*///

#pragma pack() ///*1字节对齐*///

#pragma pack(2) ///*1字节对齐*///
typedef struct
{			                    	
	uchar8		*P_Str;				///*RAM地址*//
	uchar8		*P_CRCAddr;			///*CRC地址*///
	ushort16	Length;				///*长度*///
	ulong32		P_State;			///*状态字数据标识*/// 
	ushort16	V_Happen;			///*事件发生量*///	
	ushort16	V_End;				///*事件结束量*///  
	uchar8  	*P_BellAlarm;		///*小铃铛报警状态字*/// 
	uchar8  	*P_AlarmOuput;		///*报警输出状态字*///
	uchar8  	*P_BackLightAlarm;	///*背光报警状态字*///
	ushort16	V_AlarmStart;		///*报警发生量*///		
	ushort16	V_AlarmClose;		///*报警结束量*///  
}Str_CommunicateEventClearTable_Type;///*通信清零表格1*///

#define C_EventSymbolLength		10	///*电流电压符号总共有10个*///

#define C_AVoltage_SymbolNO		0	///*A相电压符号状态*///
#define C_BVoltage_SymbolNO		1	///*B相电压符号状态*///
#define C_CVoltage_SymbolNO		2	///*C相电压符号状态*///
#define C_ACurrentminus_SymbolNO	3	///*A相电流负号状态*///
#define C_BCurrentminus_SymbolNO	4	///*B相电流负号状态*///
#define C_CCurrentminus_SymbolNO	5	///*C相电流负号状态*///
#define C_ACurrent_SymbolNO		6	///*A相电流符号状态*///
#define C_BCurrent_SymbolNO		7	///*B相电流符号状态*///
#define C_CCurrent_SymbolNO		8	///*C相电流符号状态*///
#define C_Reversephase_SymbolNO	9	///*逆相序符号状态*///
#define	C_DisplayMsgPT1			0       ///*显示项目*///
#define	C_DisplayMsgType1		1       ///*闪烁/常显/不显*///
#define C_DisplayMsgTime1H		2       ///*显示时间*///
#define C_DisplayMsgTime1L		3       ///*显示时间*///
#define	C_DisplayMsgPT2			4       ///*显示项目*///
#define	C_DisplayMsgType2		5       ///*闪烁/常显/不显*///
#define C_DisplayMsgTime2H		6       ///*显示时间*///
#define C_DisplayMsgTime2L		7       ///*显示时间*///


typedef struct 
{
	uchar8     A0_Flag; ///*bit0失压，bit1过载，bit2功率反向，bit3失流，bit4断相，bit5过流，bit6过压，bit7欠压*///
    uchar8     A1_Flag;///*bit0断流,bit1功率因数超限*///
    uchar8     B0_Flag;
    uchar8     B1_Flag;
	uchar8     C0_Flag;
    uchar8     C1_Flag;
    uchar8     T0_Flag;  ///*bit0电压逆相序，bit1电流逆相序，bit2时钟电池欠压，bit3总潮流反向，bit4总功率因数超下限，bit5电压不平衡，bit6电流不平衡，bit7电流严重不平衡*///
	uchar8     T1_Flag;  ///*bit0需量超限，bit1开表盖，bit2开端尾盖，bit3掉电，bit4全失压，bit5恒定磁场，bit6电源异常，bit7辅助电源失电*///        
}Str_BeeperAlerm_Type;		///*报警当前状态*///

typedef struct
{
	uchar8 	BellAlarmNo;		///*小铃铛序号*///   
	uchar8 	AlarmOutputNo;			///*报警输出序号*///   
	uchar8 	BacklightAlarmLNo;	///*背光序号*///   
}Str_AlarmByteNo_Type;///*报警组合状态，在报警模式字读出来后，所占的缓存序号*///

#define C_BacklightAlarm_ABC0ByteNo  	0	///*分相事件背光报警在报警模式字读出缓存中占低字节*///
#define C_BacklightAlarm_ABC1ByteNo	1	///*分相事件背光报警在报警模式字读出缓存中占高字节*///
#define C_BacklightAlarm_T0ByteNo	        2	///*合相事件背光报警在报警模式字读出缓存中占低字节*///
#define C_BacklightAlarm_T1ByteNo	        3	///*合相事件背光报警在报警模式字读出缓存中占高字节*///
#define C_Alarmoutput_ABC0ByteNo         	4	///*分相事件报警输出在报警模式字读出缓存中占低字节*///
#define C_Alarmoutput_ABC1ByteNo	        5	///*分相事件报警输出在报警模式字读出缓存中占高字节*///
#define C_Alarmoutput_T0ByteNo	        6	///*合相事件报警输出在报警模式字读出缓存中占低字节*///
#define C_Alarmoutput_T1ByteNo	        7	///*合相事件报警输出在报警模式字读出缓存中占高字节*///
#define C_BellAlarm_ABC0ByteNo		8	///*分相事件小铃铛在报警模式字读出缓存中占低字节*///
#define C_BellAlarm_ABC1ByteNo		9	///*分相事件小铃铛在报警模式字读出缓存中占高字节*///
#define C_BellAlarm_T0ByteNo		        10	///*合相事件小铃铛在报警模式字读出缓存中占低字节*///
#define C_BellAlarm_T1ByteNo		        11	///*合相事件小铃铛在报警模式字读出缓存中占高字节*///*在报警状态字读出缓存中所占位置*///
#define	C_AlarmModeLength		        12	///*报警模式字长度*///
#define	C_AlarmTempLength		        8	///*报警字临时变量长度*///
#define	C_AlarmTempBitLength		        64	///*报警字临时变量Bit位数*///
#define	C_CurrentBitAlarmHappen		        1	///*当前位发生报警*///
#define	C_SendAlarmMessage		        1	///*发送报警消息*///
#define	C_NOAlarmMessage		        0	///*发送报警消息*///

#pragma pack() ///*2字节对齐*///
#pragma pack(1)
typedef struct
{
	uchar8	*P_TotalAhAddr;				///*总Ah*///
	uchar8	*P_AAhAddr;					///*A相Ah*///
	uchar8	*P_BAhAddr;					///*B相Ah*///
	uchar8	*P_CAhAddr;					///*C相Ah*///
}Str_AhCountTable_Type;	

typedef struct
{
	uchar8 	MeterState;							/*事件状态动作标志位*/
	uchar8 	Time[CLDate_Time];					/*低功耗状态下全失压时间*/
	uchar8 	AddTime[C_AddTime_Length];			/*总累计时间*/
	uchar8 	NoVoltageCurrent[C_3Curr_Length];	/*低功耗下全失压电流*/
	uchar8	V_CRC[2];
}Str_LpowerTvoltagelose_Type;		/*全失压低功耗结构体*/
extern	Str_LpowerTvoltagelose_Type	GStr_PowerfailStr;			/*掉电*/


typedef struct
{
	uchar8	OpenCoverState;				/*开盖事件状态*/
	uchar8	HappenTime[CLDate_Time];	/*开盖时间*/
	uchar8	CloseCoverState;			/*合盖事件状态*/
	uchar8	EndTime[CLDate_Time];		/*合盖时间*/
	uchar8 	AddTime[C_AddTime_Length];	/*总累计时间*/
	uchar8	V_CRC[2];
}Str_CoverRecord_Type;			/*低功耗下开合盖事件结构体*/

typedef struct
{
	uchar8 	MeterState;					/*事件状态标志位*/
	uchar8 	Time[CLDate_Time];			/*低功耗下事件发生时间*/
	uchar8 	AddTime[C_AddTime_Length];	/*总累计时间*/
	uchar8	V_CRC[2];
}Str_ACPowerFail_Type;		/*电源异常事件结构体*/


typedef struct
{
	uchar8	Renewal[C_Demand_Length];				/*事件发生过程中最大需量*/
	uchar8	RenewalTime[C_GetHappenEndTime_Length];	/*发生过程中需量发生时间*/
	uchar8 	MeterState;								/*事件状态*/
	uchar8 	AddTime[C_AddTime_Length];				/*总累计时间*/
	uchar8	V_CRC[2];
}Str_ActiveDemand_Type;			/*有功需量超限事件事件结构体（无功不记录事件状态）*/


typedef struct
{
	uchar8	Renewal[C_Unbalance_Length];	/*事件发生过程中数据*/
	uchar8 	AddTime[C_AddTime_Length];		/*总累计时间*/
	uchar8	V_CRC[2];
}Str_Unbanlance_Type;		/*不平衡事件结构体*/

typedef struct
{
	uchar8	Renewal[C_Ah_Length];	/*总Ah*/
	uchar8	ARenewal[C_Ah_Length];	/*A相Ah RAM数据*/
	uchar8	BRenewal[C_Ah_Length];	/*B相Ah RAM数据*/
	uchar8	CRenewal[C_Ah_Length];	/*C相Ah RAM数据*/
	uchar8	Ah[C_Ah_Length];		/*不足0.01Ah*/
	uchar8	AAh[C_Ah_Length];		/*A相不足0.01Ah*/
	uchar8 	BAh[C_Ah_Length];		/*B相不足0.01Ah*/
	uchar8	CAh[C_Ah_Length];		/*C相不足0.01Ah*/
	uchar8	AddTime[C_AddTime_Length];	/*总累计时间*/
	uchar8	V_CRC[2];
}Str_AhMeter_Type;			/*Ah数结构体*/

typedef struct
{
	uchar8	AddTime[C_AddTime_Length];	/*总累计时间*/
	uchar8	V_CRC[2];
}Str_OtherMeter_Type;		/*其他事件结构体*/

#define	C_CRC_Length	2						/////*CRC长度*///
#define	C_Str_LpowerTvoltagelose_TypeLength	sizeof(Str_LpowerTvoltagelose_Type)					///*全失压低功耗结构体长度*///
#define	C_Str_LpowerTvoltagelose_Length		sizeof(Str_LpowerTvoltagelose_Type)-C_CRC_Length	///*全失压低功耗数据长度*///
#define	C_Str_CoverRecord_TypeLength		sizeof(Str_CoverRecord_Type)						///*低功耗下开合盖事件结构体长度*///
#define	C_Str_CoverRecord_Length			sizeof(Str_CoverRecord_Type)-C_CRC_Length			///*低功耗下开合盖事件数据长度*///
#define	C_Str_ACPowerFail_TypeLength		sizeof(Str_ACPowerFail_Type)						///*低功耗下电源异常事件结构体长度*///
#define	C_Str_ACPowerFail_Length			sizeof(Str_ACPowerFail_Type)-C_CRC_Length			///*低功耗下电源异常事件数据长度*///
#define	C_Str_ActiveDemand_TypeLength		sizeof(Str_ActiveDemand_Type)						///*有功需量超限事件结构体长度*///
#define	C_Str_ActiveDemand_Length			sizeof(Str_ActiveDemand_Type)-C_CRC_Length			///*有功需量超限数据长度*///
#define	C_Str_Unbanlance_TypeLength			sizeof(Str_Unbanlance_Type)							///*不平衡事件结构体长度*///
#define	C_Str_Unbanlance_Length				sizeof(Str_Unbanlance_Type)-C_CRC_Length			///*不平衡数据长度*///
#define	C_Str_AhMeter_TypeLength			sizeof(Str_AhMeter_Type)							///*Ah事件结构体长度*///
#define	C_Str_AhMeter_Length				sizeof(Str_AhMeter_Type)-C_CRC_Length				///*Ah数据长度*///
#define	C_Str_OtherMeter_TypeLength			sizeof(Str_OtherMeter_Type)							///*其他事件结构体长度*///
#define	C_Str_OtherMeter_Length				sizeof(Str_OtherMeter_Type)-C_CRC_Length			///*其他数据长度*///

#define	C_OpenMeterCoverLowPower		55	///*用于低功耗下写消息*///
#define	C_CloseMeterCoverLowPower		66	///*用于低功耗下写消息*///
#define	C_OpenTerminalCoverLowPower		77	///*用于低功耗下写消息*///
#define	C_CloseTerminalCoverLowPower	88	///*用于低功耗下写消息*///

#define	C_REventE			0x20	///*bit5	有恢复上报发生*///
#define	C_REventH			0x10	///*bit4	有发生上报*///
#define	C_REventEConfirm	0x08	///*bit3恢复上报确认标志*///
#define	C_REventEReport		0x04	///*bit2恢复已上报标志*///
#define	C_REventHConfirm	0x02	///*bit1	发生上报确认标志*///
#define	C_REventHReport		0x01	///*bit0	发生已上报标志*///
#define C_REventReport      C_REventHReport|C_REventEReport     ///*发生/结束上报*///
#define C_REventConfirm     C_REventHConfirm|C_REventEConfirm   ///*发生/结束上报*///

typedef struct
{
	uchar8	EventNo;		///*事件号*///
	uchar8	SourceFlag;		///*事件发生源标志0x00无，0x01有*///
	ulong32	Degree;			///*事件次数*///
	ulong32	OADTab;			///*事件关联OAD*///
	ulong32	WriteOAD;		///*写事件OAD*///
}Str_EventMapping_Type;

#define	C_SourceNon	0x00	///*无发生源*///
#define	C_SourceExist	0x01	///*有发生源*///

typedef struct
{
	ulong32	EventOAD;		///*事件OAD*///
	ulong32	AddTimeOAD;		///*事件总累计时间*///
	ulong32	TolAh;			///*事件总安时或者不平衡率*///
	ulong32	AAh;			///*事件A相安时数*///
	ulong32	BAh;			///*事件B相安时数*///
	ulong32	CAh;			///*事件C相安时数*///
}Str_SpecialReadTable_Type;

typedef struct
{
	ulong32	EventOAD;		///*事件OAD*///
	uchar8	Source;			///*发生源*///
	uchar8	EventNo;		///*事件号*///
	ushort16 EventTimeStatus;///*时间状态表，OAD的低两字节，属性号+数据项索引*///
	ulong32	Degree;		///*事件发生次数*///
	ulong32	AddTime;		///*事件累计时间*///
}Str_CurrentDataReadTable_Type;
typedef struct
{
	ulong32	EventOAD;		///*事件OAD*///
	ulong32	Source;			///*发生源*///
	uchar8	EventNo;		///*事件号*///
}Str_CurrentDataReadTable1_Type;



#define C_Type1                 0x68                ///*区分读的是累计时间次数还是最近一次发生时间*///
#define C_Type2                 0x86                ///*区分读的是累计时间次数还是最近一次发生时间*///
#define	C_TolAh_E				0x20296201	       	///*事件期间总Ah数*///
#define	C_AAh_E					0x20296202	       	///*事件期间A相Ah数*///
#define	C_BAh_E					0x20296203	       	///*事件期间B相Ah数*///
#define	C_CAh_E					0x20296204	       	///*事件期间C相Ah数*///
#define C_CurUnbalanceRate_E	0x20276200			///*事件发生期间电流不平衡率*///

extern uchar8 SF_JudgeAllAA(uchar8 *P_DataBuf,uchar8 P_DataLen);

#define	C_AllEventNo					0xAA	///*用于报警清零*///

#pragma pack()
///*****************************************************************************************///
///*数据层定义后删掉*///
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

#define C_Evt       1   /*事件记录*/
#define C_Frz       2   /*冻结*/

#define C_Need      1   /*事件记录获取数据时，判断对应关联列表OAD内容是否需要取数据，需要*/
#define C_NoNeed    2   /*不需要*/

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


