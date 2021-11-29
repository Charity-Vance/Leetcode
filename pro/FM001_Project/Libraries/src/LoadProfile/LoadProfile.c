
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     LoadProfile.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   负荷记录处理文件
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
#include "LoadProfile.h"

 ///*六类负荷数据时间间隔*///
const ulong32 C_TimeInteCode[6] = 
{
	CLoad_Rec1_Inte_Time,
	CLoad_Rec2_Inte_Time,
	CLoad_Rec3_Inte_Time,
	CLoad_Rec4_Inte_Time,
	CLoad_Rec5_Inte_Time,
	CLoad_Rec6_Inte_Time
};    

const Str_LoadDataType Str_LoadData[]=
{
	///*电压、电流、频率*///
	CPhaseA_Volage, 		CLPhaseA_Volage,    	C_VariableType,
	CPhaseB_Volage, 		CLPhaseB_Volage,     	C_VariableType,
	CPhaseC_Volage,  		CLPhaseC_Volage,     	C_VariableType,           
	CPhaseA_Curr,    		CLPhaseA_Curr,       	C_VariableType,
	CPhaseB_Curr,    		CLPhaseB_Curr,       	C_VariableType,
	CPhaseC_Curr,    		CLPhaseC_Curr,       	C_VariableType,
	CElecNet_Freq,   		CLElecNet_Freq,      	C_VariableType,
	///*有、无功功率*///
	CInstant_TolAcPow,      CLInstant_TolAcPow,     C_VariableType,
	CInstantA_AcPow,        CLInstantA_AcPow,       C_VariableType,
	CInstantB_AcPow,        CLInstantB_AcPow,       C_VariableType,
	CInstantC_AcPow,        CLInstantC_AcPow,       C_VariableType,
	CInstant_TolRePow,      CLInstant_TolRePow,     C_VariableType,
	CInstantA_RePow,        CLInstantA_RePow,       C_VariableType,
	CInstantB_RePow,        CLInstantB_RePow,       C_VariableType,
	CInstantC_RePow,        CLInstantC_RePow,       C_VariableType,
	///*功率因数*///
	CTol_PowerFactor,       CLTol_PowerFactor,      C_VariableType,
	CPhaseA_PowerFactor,    CLPhaseA_PowerFactor,   C_VariableType,
	CPhaseB_PowerFactor,    CLPhaseB_PowerFactor,   C_VariableType,
	CPhaseC_PowerFactor,    CLPhaseC_PowerFactor,   C_VariableType,
	///*有、无功总电能*///
	CPos_Ac_Tol_En_0,       CLPos_Ac_Tol_En_0,      C_EnergyType,
	CRev_Ac_Tol_En_0,       CLRev_Ac_Tol_En_0,      C_EnergyType,
	CCom_Re1_Tol_En_0,      CLCom_Re1_Tol_En_0,     C_EnergyType,
	CCom_Re2_Tol_En_0,      CLCom_Re2_Tol_En_0,     C_EnergyType,
	///*四象限无功总电能*///
	CQua1_Re_Tol_En_0,      CLQua1_Re_Tol_En_0,     C_EnergyType,
	CQua2_Re_Tol_En_0,      CLQua2_Re_Tol_En_0,     C_EnergyType,
	CQua3_Re_Tol_En_0,      CLQua3_Re_Tol_En_0,     C_EnergyType,
	CQua4_Re_Tol_En_0,      CLQua4_Re_Tol_En_0,     C_EnergyType,
	///*当前需量*///
	CCurr_AcDemand,			CLCurr_AcDemand,        C_DemandType,
	CCurr_ReDemand,			CLCurr_ReDemand,        C_DemandType
};
	
const uchar8 C_TypeNum[]={7,8,4,4,4,2};///*每一类负荷数据所含数据种类数*///

///******************************************************************************************///
///*Function:void  Msg_LoadProfile(Str_Msg_Parameter V_Msg)				 					*///
///*Description:负荷记录处理函数															*///
///*Input:	判断信息参数结构体V_Msg中的参数，C_SystemMinChange表示每分钟调度触发			*///
///*Output: 无									  									        *///
///*Return:	无	                                 											*///
///*Calls:																					*///
///*Called By:由每分钟调度触发																*///
///*Influence:																				*///
///*Author:																					*///
///*Tips: 														                            *///
///*Others:																					*///
///******************************************************************************************///
void Msg_LoadProfile(Str_Msg_Parameter *V_Msg)
{
	uchar8 V_ucCurrentTime[CLDate_Time];///*当前时间缓存,YYMMDDhhmmss*///
	uchar8 V_ucLength_CurrentT = CLDate_Time;
	uchar8 V_ucLoadStartTime[CLLoad_Rec_Time_Year+1];///*负荷起始时间缓存,比参数多秒*///
	uchar8 V_ucLength_LoadStartT = CLLoad_Rec_Time_Year;
	uchar8 V_ucLoadMode,V_ucModeTemp=0;///*负荷模式字*///
	uchar8 V_ucLength_LoadMode = CLLoad_Rec_Mode;
	ulong32 V_ulSubMins;///*当前时间与负荷起始时间的分钟差*///
	uchar8 V_ucTimeInte[2];///*时间间隔缓存*///
	uchar8 V_ucLength_TimeInte = CLLoad_Rec1_Inte_Time;
	uchar8 i,V_ucTemp=1;
	uchar8 V_ucDataTemp[104];///*负荷数据缓存区,最大为104字节*///
	uchar8 V_ucLen_LoadWrite;///*写数据层长度*///
	uchar8 V_ucWrSafeFlag=C_W_SafeFlag_1;
	
	if(SF_LoadProfile_ParseMessage(V_Msg) == C_Error)///*消息解析错误,直接返回*///
	{
		return;
	}
	if(InF_Read_Data(CDate_Time,V_ucCurrentTime,&V_ucLength_CurrentT) != C_OK)///*读当前时间,若失败则退出*///
	{
		return;
	}
	if(PF_DataTimeActive(V_ucCurrentTime,C_DT_Start_ss,CLDate_Time) != C_OK)
	{///*当前时间不合法，也不做负荷记录*///
		return;
	}
	V_ucLoadStartTime[C_Sec] = 0;///*负荷起始时间秒赋值0*///
//	if(InF_Read_Data(CLoad_Rec_Time_Year,&V_ucLoadStartTime[C_Minute],&V_ucLength_LoadStartT) != C_OK)
//	{
//		return;
//	}
	if((InF_Read_Data(CLoad_Rec_Time_Year,&V_ucLoadStartTime[C_Minute],&V_ucLength_LoadStartT) != C_OK)///*读负荷起始时间，读失败*///
		||(PF_DataTimeActive(&V_ucLoadStartTime[C_Minute],C_DT_Start_mm,CLLoad_Rec_Time_Year) != C_OK))///*或时间不合法,默认为2000年1月1日*///
	{///*时间不合法,默认为2000年1月1日*///
		V_ucLoadStartTime[C_Minute] = 0x00;
		V_ucLoadStartTime[C_Hour] = 0x00;
		V_ucLoadStartTime[C_Day] = 0x01;
		V_ucLoadStartTime[C_Month] = 0x01;
		V_ucLoadStartTime[C_Year] = 0x00;
	}
	if(PF_Campare_Data(&V_ucCurrentTime[C_Minute],&V_ucLoadStartTime[C_Minute],CLLoad_Rec_Time_Year) == C_LessThan)
	{///*当前时间不比负荷起始时间迟,直接退出*///后根据广东电科院测试结果，修改当时间相等时，也记录数据。
		return;
	}
	if(InF_Read_Data(CLoad_Rec_Mode,&V_ucLoadMode,&V_ucLength_LoadMode) != C_OK)
	{///*负荷模式字读取失败,默认为3F*///
		V_ucLoadMode = 0x3F;
	}
	V_ucWrSafeFlag |= C_W_SafeFlag_2;
	
	PF_TimeSub_Min(&V_ucLoadStartTime[C_Sec],&V_ucCurrentTime[C_Sec],&V_ulSubMins);///*计算当前时间与负荷起始时间的分钟差*///
	
	for (i=0;i<6;i++)
	{
		if(InF_Read_Data(C_TimeInteCode[i],V_ucTimeInte,&V_ucLength_TimeInte) != C_OK)
		{
			V_ucTimeInte[0] = 0x15;///*读取失败,默认为15分钟*///
		}
		V_ucTimeInte[0] = ((V_ucTimeInte[0]>>4)*10) + (V_ucTimeInte[0]&0x0F);
		
		if((V_ucTimeInte[0] != 0)&&((V_ulSubMins%V_ucTimeInte[0]) == 0))///*时间间隔到,则至临时模式字为1*///
		{
			V_ucModeTemp |= (V_ucTemp << i);
		}
	}
	V_ucLoadMode &= V_ucModeTemp;
	
	if(V_ucLoadMode != 0)
	{
		V_ucLen_LoadWrite = SF_GetData_LoadProfile(V_ucLoadMode,&V_ucCurrentTime[C_Minute],V_ucDataTemp);///*取负荷数据*///
		
		V_ucWrSafeFlag |= C_W_SafeFlag_3;
		///*06FE0000负荷记录次数*///
		uchar8 V_NumLen=3,i;
		uchar8 V_ucNum[3];
		ulong32 V_ulLoadWriteNum;
		
		if(InF_Read_Data(CLoadWriteNum,V_ucNum,&V_NumLen)!=C_OK)
		{
			 for(i=0;i<3;i++)
			   {
			   	  V_ucNum[i]=0;
			   }	
		}
		PF_Buffer4ToUlong32(V_ucNum,&V_ulLoadWriteNum,V_NumLen);
		V_ulLoadWriteNum++;
		PF_Ulong32ToBuffer4(V_ucNum,&V_ulLoadWriteNum,V_NumLen);
		InF_Write_Data(C_Msg_LoadProfile,CLoadWriteNum,V_ucNum,CLLoadWriteNum,V_ucWrSafeFlag);///*写数据层*///

		InF_Write_Data(C_Msg_LoadProfile,CLoad_Write,V_ucDataTemp,V_ucLen_LoadWrite,V_ucWrSafeFlag);///*写数据层*///
	}
	
}

///******************************************************************************************///
///*Function:uchar8 SF_LoadProfile_ParseMessage(Str_Msg_Parameter * P_Msg_Parameter)			*///
///*Description:负荷模块消息处理解析														*///
///*Input:	P_Msg_Parameter –消息结构体														*///
///*Output: 													 					        *///
///*Return:	C_OK-消息参数正确,需进行费率判断/C_Error-消息参数错误,无需处理					*///
///*Calls:																					*///
///*Called By:																				*///
///*Influence:																				*///
///*Author:																					*///
///*Tips: 
///* 情况2： SourceAddr= 调度。调度每分钟触发
///*                            DerictAddr = C_Msg_Deal_MultiRates
///*                            Len = 2
///*                            数据域：Pt_Dispatch_Timing，取值C_SystemMinChange
///******************************************************************************************///
uchar8 SF_LoadProfile_ParseMessage(Str_Msg_Parameter *P_Msg_Parameter)
{
	uchar8 *pParm;
	 
	if(P_Msg_Parameter->PowerFlag != C_PowerOn)///*掉电时直接返回错误,无需处理*///
	{
		return C_Error;
	}
	///*区分三种情况,根据情况调用分项解析函数*///
	pParm = P_Msg_Parameter->Parameter;
	
	if(*pParm == Pt_Dispatch_Timing)
	{
		if(P_Msg_Parameter->Length ==(Pt_Dispatch_Timing_Len+1))
		{
			return C_OK;
		}
	}
	return C_Error;
}

///******************************************************************************************///
///*Function:uchar8 SF_GetData_LoadProfile (uchar8 V_ucMode,uchar8 *p_ucDateTime,uchar8 *P_buffer)*///
///*Description:取负荷记录数据																*///
///*Input:	V_ucMode 模式字，为负荷记录模式字（0x04000901）与临时模式字相与的值，用于指示	*///
///*				当前实际需要取的负荷数据，同时传给数据层，用于判断数据长度合法性		*///
///*		p_ucDate当前时间，5字节，年月日时分												*///
///*		P_buffer输出缓存区																*///
///*Output: 无									  									        *///
///*Return:	无	                                 											*///
///*Calls:																					*///
///*Called By:Msg_LoadProfile																*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:根据模式字，读取数据生成负荷记录数据块，并调用数据层写负荷接口函数，将数据传给数据层*///
///*Others:																					*///
///******************************************************************************************///
uchar8 SF_GetData_LoadProfile(uchar8 V_ucMode,uchar8 *p_ucDateTime,uchar8 *P_buffer)
{
	uchar8 i,j,V_ucAddTemp=0,V_ucTemp=1;
	uchar8 V_ucLength_Load;
	uchar8 *P_ucData;///*数据缓存指针临时变量*///
	uchar8 V_ucLen=0;///*负荷记录长度*///
	
	P_buffer[C_Mode] = V_ucMode;///*赋值模式字*///
	
	P_buffer[C_A0] = 0xA0;///*赋值两个字节A0*///
	P_buffer[C_A0+1] = 0xA0;
	
	PF_CopyDataBytes(p_ucDateTime,&P_buffer[C_Time],C_LoadTimeLen);///*将时间赋值临时缓存*///
	V_ucLen += C_LoadTimeLen;///*累计负荷记录长度*///
	
	P_ucData = &P_buffer[C_Data];///*赋值临时数据指针*///
	
	for(i=0;i<6;i++)
	{		
		if(V_ucMode & (V_ucTemp<<i))
		{
			for(j=0;j<C_TypeNum[i];j++)
			{
				V_ucLength_Load = Str_LoadData[V_ucAddTemp].V_ucLength;					
				///*根据不同类型数据,调用不同函数进行取数据*///
				if(Str_LoadData[V_ucAddTemp].V_ucDataType == C_EnergyType)///*电量数据*///
				{
					InF_ReadEnergy_Protocol(Str_LoadData[V_ucAddTemp].V_ulDI,P_ucData,V_ucLength_Load);
				}
				else///*瞬时量数据*///
				{
					InF_Read_Data(Str_LoadData[V_ucAddTemp].V_ulDI,P_ucData,&V_ucLength_Load);
				}
				P_ucData += V_ucLength_Load;///*累加数据指针*///
				V_ucLen += V_ucLength_Load;///*累计负荷记录长度*///
				
				V_ucAddTemp ++;///*用于定位表格行数*///
			}
		}
		else
		{
			V_ucAddTemp += C_TypeNum[i];///*用于定位表格行数*///
		}
		*P_ucData = 0xAA;///*赋值AA并累加指针*///
		P_ucData ++;
		V_ucLen ++;	
	}
	P_buffer[C_Length] = V_ucLen;///*赋值负荷记录长度*///
	
	*P_ucData = SF_CalCS(&P_buffer[C_A0],V_ucLen+3);///*计算CS*///
	
	*(P_ucData+1) = 0xE5;
	
	V_ucLen += 6;///*总数据长度=1+2+1+L+2(模式字+A0A0+长度+L+CS+E5) *///
	return V_ucLen;
}

///******************************************************************************************///
///*Function:uchar8 SF_CalCS(uchar8 *P_buffer,uchar8 V_ucLen)								*///
///*Description:计算CS																		*///
///*Input:	*P_buffer 需计算CS数据的首地址  V_ucLen 需计算CS数据的长度						*///
///*Output: 无									  									        *///
///*Return:	V_ucCS CS数值                          											*///
///*Calls:																					*///
///*Called By:SF_GetData_LoadProfile														*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:																					*///
///*Others:																					*///
///******************************************************************************************///
uchar8 SF_CalCS(uchar8 *P_buffer,uchar8 V_ucLen)
{
	uchar8 i;
	uchar8 V_ucCS = 0;
	for( i=0;i<V_ucLen;i++)
	{
		V_ucCS += *(P_buffer+i);
	}
	return V_ucCS;
}


const Str_LoadReadStatus Str_LoadStatus[]=
{
	///*电压类*///
	CVoltageA_Load,			CGivenTimeRec1_Load,	 8,		CLVoltageA_Load,
	CVoltageB_Load,			CGivenTimeRec1_Load,     10,    CLVoltageB_Load,			
	CVoltageC_Load,			CGivenTimeRec1_Load,     12,    CLVoltageC_Load,			
	CVoltageBlock_Load,		CGivenTimeRec1_Load,     8,     CLVoltageBlock_Load,		
	///*电流类*///
	CCurrentA_Load,			CGivenTimeRec1_Load,     14,    CLCurrentA_Load,			
	CCurrentB_Load,			CGivenTimeRec1_Load,     17,    CLCurrentB_Load,			
	CCurrentC_Load,			CGivenTimeRec1_Load,     20,    CLCurrentC_Load,			
	CCurrentBlock_Load,		CGivenTimeRec1_Load,     14,    CLCurrentBlock_Load,		
	///*有功功率类*///
	CActPowerT_Load,		CGivenTimeRec2_Load,     9,     CLActPowerT_Load,		
	CActPowerA_Load,		CGivenTimeRec2_Load,     12,    CLActPowerA_Load,		
	CActPowerB_Load,		CGivenTimeRec2_Load,     15,    CLActPowerB_Load,		
	CActPowerC_Load,		CGivenTimeRec2_Load,     18,    CLActPowerC_Load,		
	CActPowerBlock_Load,	CGivenTimeRec2_Load,     9,     CLActPowerBlock_Load,	
	///*无功功率类*///
	CReActPowerT_Load,		CGivenTimeRec2_Load,     21,    CLReActPowerT_Load,		
	CReActPowerA_Load,		CGivenTimeRec2_Load,     24,    CLReActPowerA_Load,		
	CReActPowerB_Load,		CGivenTimeRec2_Load,     27,    CLReActPowerB_Load,		
	CReActPowerC_Load,		CGivenTimeRec2_Load,     30,    CLReActPowerC_Load,		
	CReActPowerBlock_Load,	CGivenTimeRec2_Load,     21,    CLReActPowerBlock_Load,	
	///*功率因素类*///
	CPowFactorT_Load,		CGivenTimeRec3_Load,     10,    CLPowFactorT_Load,		
	CPowFactorA_Load,		CGivenTimeRec3_Load,     12,    CLPowFactorA_Load,		
	CPowFactorB_Load,		CGivenTimeRec3_Load,     14,    CLPowFactorB_Load,		
	CPowFactorC_Load,		CGivenTimeRec3_Load,     16,    CLPowFactorC_Load,		
	CPowFactorBlock_Load,	CGivenTimeRec3_Load,     10,    CLPowFactorBlock_Load,	
	///*有无功总电能类*///
	CPosActEnergyT_Load,	CGivenTimeRec4_Load,     11,    CLPosActEnergyT_Load,	
	CRevActEnergyT_Load,	CGivenTimeRec4_Load,     15,    CLRevActEnergyT_Load,	
	CComReAct1T_Load,		CGivenTimeRec4_Load,     19,    CLComReAct1T_Load,		
	CComReAct2T_Load,		CGivenTimeRec4_Load,     23,    CLComReAct2T_Load,		
	CTotEnergyBlock_Load,	CGivenTimeRec4_Load,     11,    CLTotEnergyBlock_Load,	
	///*四象限无功电能类*///
	CReActQuad1_Load,		CGivenTimeRec5_Load,     12,    CLReActQuad1_Load,		
	CReActQuad2_Load,		CGivenTimeRec5_Load,     16,    CLReActQuad2_Load,		
	CReActQuad3_Load,		CGivenTimeRec5_Load,     20,    CLReActQuad3_Load,		
	CReActQuad4_Load,		CGivenTimeRec5_Load,     24,    CLReActQuad4_Load,		
	CReActQuadTBlock_Load,	CGivenTimeRec5_Load,     12,    CLReActQuadTBlock_Load,	
	///*当前需量类*///
	CActDemand_Load,		CGivenTimeRec6_Load,     13,    CLActDemand_Load,		
	CReActDemand_Load,		CGivenTimeRec6_Load,     16,    CLReActDemand_Load,		
	CDemandBlock_Load,		CGivenTimeRec6_Load,     13,    CLDemandBlock_Load		
};

///*用于判断月份天数*///
const uchar8 C_MonthNum[12]={31,28,31,30,31,30,31,31,30,31,30,31};


///******************************************************************************************///
///*Function:uchar8 InF_SeqRead_LoadProfile							 						*///
///*Description:此函数为通信模块进行负荷记录连续抄读时调用，将所需数据从数据层读取并组织后，传给通信模块*///
///*Input:	V_ulDataId-数据标识
///*		* P_ucTime-读取负荷记录的起始时间，5字节（mmhhDDMMYY）
///*		* P_ucBlockNum-所需抄读块数
///*		* P_ucData-数据缓存区
///*		*P_ucGVBuffer-存放电能全局变量的缓存首地址，读电能时使用,输入时用于补数据.当读非电能数据时，该处不处理。
///*		*P_ucLength：数据缓存区长度
///*		P_ucFollowFlag表示是否为负荷读取的第一帧,若为第一帧,需将标识码和归一时间放入数据缓存区,C_FirstFrame/C_FollowFrame
///*Output: * P_ucTime-作为输出参数时，返回后续帧需读取的负荷记录时间
///*		* P_ucBlockNum-作为输出参数时，返回值为所读数据剩余块数，用于后续帧抄读,为0表示无后续帧,hex格式。
///*		* P_ucData-负荷数据
///*		*P_ucGVBuffer-用作输出,在读电能负荷记录时，若读到实际记录数据，将电能放入此处
///*		*P_ucLength：输出的数据长度
///*Return:	C_OK-抄读成功,C_NoData-无数据,C_Error-读取错误	                 				*///
///*Calls:																					*///
///*Called By:通信收到负荷连续抄读时调用,后续帧也调用该函数									*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:根据*P_ucBlockNum的值来判断是否有后续帧				                            *///
///*Others:																					*///
///******************************************************************************************///
uchar8 InF_SeqRead_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucTime,uchar8 *P_ucData,uchar8 *P_ucGVBuffer,uchar8 *P_ucBlockNum,uchar8 *P_ucLength,uchar8 P_ucFollowFlag)
{
	uchar8 V_ucStartTime[CLLoad_Rec_Time_Year+1],V_ucCurrentTime[CLDate_Time];///*最早负荷记录时间和当前时间*///
	uchar8 V_ucFirstTime[C_LoadTLength+1],V_ucEndTime[C_LoadTLength+1];///*连续抄读第一块和截止块时间*///
	ulong32 V_ulLoadTypeID,V_ulSubMins;
	uchar8 V_ucDataLength,V_ucReturnTemp,V_ucFlag=0;
	uchar8 V_ucReadNum,V_ucIntTime,V_ucLength,i;
	uchar8 V_ucParaTime[CLLoad_Rec_Time_Year+1];
	uchar8 V_ucTableLen = sizeof(Str_LoadStatus)/sizeof(Str_LoadReadStatus);
	
	if(PF_DataTimeActive(P_ucTime,C_DT_Start_mm,CLLoad_Rec_Time_Year) != C_OK)///*读取时间不合法,返回无数据*///
	{
		return C_NoData;
	}
	V_ucFirstTime[C_Sec]=0;///*秒位补0,时间求差时使用*///
	V_ucEndTime[C_Sec]=0;
	
	for(i=0;i<V_ucTableLen;i++)
	{
		if(V_ulDataId == Str_LoadStatus[i].V_ulDataId)
		{
			V_ulLoadTypeID = Str_LoadStatus[i].V_ulTypeId;///*赋值类型标识码*///
		
			V_ucDataLength = Str_LoadStatus[i].V_ucDataLen;///*赋值数据长度*///
			
			break;
		}
	}
	if(i>=V_ucTableLen)
	{
		return C_Error;
	}
	V_ucIntTime = SF_GetIntTime_LoadProfile(V_ulLoadTypeID);///*获得间隔时间*///
	
	if(V_ucIntTime == 0)///*间隔时间为0,则返回无数据*///
	{
		return C_NoData;
	}
	if(P_ucFollowFlag == C_FirstFrame)///*第一帧取归一时间*///
	{
		V_ucStartTime[C_Sec] = 0;///*秒位补零*///
		V_ucParaTime[C_Sec] = 0;
		if(SF_StartTime_LoadProfile(V_ulLoadTypeID,&V_ucStartTime[C_Minute],&V_ucParaTime[C_Minute],V_ucIntTime) != C_OK)///*取最早负荷记录时间*///
		{
			return C_NoData;
		}
		V_ucLength = CLDate_Time;
		InF_Read_Data(CDate_Time,V_ucCurrentTime,&V_ucLength);///*读取当前时间*///
		
		V_ucFlag = SF_FirstTime_LoadProfile(V_ulLoadTypeID,&V_ucIntTime,P_ucTime,&V_ucStartTime[C_Sec],&V_ucParaTime[C_Sec],&V_ucFirstTime[C_Minute]);///*获取归一时间*///

		SF_MinsAdd_LoadProfile(P_ucTime,(*P_ucBlockNum)*V_ucIntTime-1,&V_ucEndTime[C_Minute]);///*计算出截止时间*///

		if(PF_Campare_Data(&V_ucEndTime[C_Minute],&V_ucCurrentTime[C_Minute],C_LoadTimeLen) == C_GreaterThan)
		{
			PF_CopyDataBytes(&V_ucCurrentTime[C_Minute],&V_ucEndTime[C_Minute],C_LoadTimeLen);
			
			V_ucFlag = C_ReCal;
		}
		V_ucReturnTemp = PF_Campare_Data(&V_ucFirstTime[C_Minute],&V_ucEndTime[C_Minute],C_LoadTimeLen);
		
		if(V_ucReturnTemp == C_GreaterThan)
		{///*第一个数据时间大于截止时间，返回无数据*///
			return C_NoData;
		}
		else if(V_ucReturnTemp == C_Equal)
		{
			*P_ucBlockNum = 1;
		}
		else if(V_ucFlag == C_ReCal)
		{
			PF_TimeSub_Min(V_ucEndTime,V_ucFirstTime,&V_ulSubMins);///*计算归一时间和截止时间的时间差*///

			*P_ucBlockNum = V_ulSubMins/V_ucIntTime + 1;///*算出归一时间后更新总抄读块数*///

		}
		V_ucReadNum =(*P_ucLength - CLLoad_Rec_Time_Year)/V_ucDataLength;///*赋值本帧读取块数*///
		
		if(*P_ucBlockNum > V_ucReadNum)
		{
			(*P_ucBlockNum) -= V_ucReadNum;///*输出后续帧需读取的块数*///
			
			SF_MinsAdd_LoadProfile(&V_ucFirstTime[C_Minute],V_ucReadNum*V_ucIntTime,P_ucTime);///*输出后续帧抄读起始时间*///
		}
		else
		{
			V_ucReadNum = *P_ucBlockNum;
			
			*P_ucBlockNum = 0;///*无后续帧*///
		}
		*P_ucLength = V_ucReadNum*V_ucDataLength + CLLoad_Rec_Time_Year;///*输出本帧的数据长度*///
	}
	else///*其他帧起始时间即为第一个抄读时间*///
	{
		PF_CopyDataBytes(P_ucTime,&V_ucFirstTime[C_Minute],C_LoadTLength);
		
		V_ucReadNum =(*P_ucLength)/V_ucDataLength;///*赋值本帧读取块数*///
		
		if(*P_ucBlockNum > V_ucReadNum)
		{
			(*P_ucBlockNum) -= V_ucReadNum;///*输出后续帧需读取的块数*///
			
			SF_MinsAdd_LoadProfile(&V_ucFirstTime[C_Minute],V_ucReadNum*V_ucIntTime,P_ucTime);///*输出后续帧抄读起始时间*///
		}
		else
		{
			V_ucReadNum = *P_ucBlockNum;
			
			*P_ucBlockNum = 0;///*无后续帧*///
		}
		*P_ucLength = V_ucReadNum*V_ucDataLength;///*输出本帧的数据长度*///
	}
	if(SF_GetSeqData_LoadProfile(&V_ulDataId,&V_ucFirstTime[C_Minute],&V_ucReadNum,&V_ucIntTime,P_ucFollowFlag,P_ucGVBuffer,P_ucData)!=C_OK)///*获取负荷数据*///
	{
		return C_Error;///*返回读取错误*///
	}
	return C_OK;
}

///******************************************************************************************///
///*Function:uchar8 SF_GetIntTime_LoadProfile												*///
///*Description:根据标识码读间隔时间														*///
///*Input:	V_ulLoadID 某类负荷对应的读取标识码												*///
///*Output: 无									  									        *///
///*Return:	间隔时间	                          											*///
///*Calls:																					*///
///*Called By:SF_SepRead_LoadProfile														*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:																					*///
///*Others:																					*///
///******************************************************************************************///
uchar8 SF_GetIntTime_LoadProfile(ulong32 V_ulLoadID)
{
	uchar8 V_ucIntTime[2];///*间隔时间*///
	ulong32 V_ulAddress;
	uchar8 V_ucLength=CLLoad_Rec1_Inte_Time;
	
	switch(V_ulLoadID)
	{
		case CGivenTimeRec1_Load:
			V_ulAddress = CLoad_Rec1_Inte_Time;
			break;
		case CGivenTimeRec2_Load:
			V_ulAddress = CLoad_Rec2_Inte_Time;
			break;
		case CGivenTimeRec3_Load:
			V_ulAddress = CLoad_Rec3_Inte_Time;
			break;
		case CGivenTimeRec4_Load:
			V_ulAddress = CLoad_Rec4_Inte_Time;
			break;
		case CGivenTimeRec5_Load:
			V_ulAddress = CLoad_Rec5_Inte_Time;
			break;
		case CGivenTimeRec6_Load:
			V_ulAddress = CLoad_Rec6_Inte_Time;
			break;
		default:
			return 0;
	}
	InF_Read_Data(V_ulAddress,V_ucIntTime,&V_ucLength);///*读间隔时间*///
	
	if(V_ucIntTime[0] > 0x60)///*数据不合法,默认为0*///
	{
		return 0;
	}
	V_ucIntTime[0] = ((V_ucIntTime[0] >> 4) * 10) + (V_ucIntTime[0] & 0x0f);///*转HEX*///
	
	return V_ucIntTime[0];
}

///******************************************************************************************///
///*Function:uchar8 SF_StartTime_LoadProfile												*///
///*Description:取最早一次负荷记录时间和负荷起始时间的较早时间点							*///
///*Input:	V_ulDataId-数据标识
///*		V_ucIntTime-间隔时间
///*Output: * P_ucStartTime –电表最早负荷记录时间									        *///
///*		*P_ucLoadParaTime-负荷记录起始时间
///*Return:C_OK,C_NoData							                      					*///
///*Calls:																					*///
///*Called By:																				*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:																					*///
///*Others:																					*///
///******************************************************************************************///
uchar8 SF_StartTime_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucStartTime,uchar8 *P_ucLoadParaTime,uchar8 V_ucIntTime)
{
	uchar8 V_ucStartTime[CLLoad_Rec_Time_Year],i;
	uchar8 V_ucDataTemp[C_LoadMaxLen],V_ucNum_RdLoad = 1,V_ucLength;
	uchar8 v_i=0;
	
	
	V_ucLength = C_LoadMaxLen;///*读取最早负荷记录*///
	for(i=0;i<CLLoad_Rec_Time_Year;i++)
	{
		V_ucStartTime[i] = 0;
	}
	if(InF_ReadLoadData(V_ulDataId-1,V_ucStartTime,V_ucDataTemp,&V_ucNum_RdLoad,&V_ucLength,C_Msg_LoadReadEarlyData) != C_OK)
	{
		return C_NoData;
	}
	V_ucLength = CLLoad_Rec_Time_Year;
	InF_Read_Data(CLoad_Rec_Time_Year,P_ucLoadParaTime,&V_ucLength);///*读负荷起始时间*///

	if(PF_DataTimeActive(P_ucLoadParaTime,C_DT_Start_mm,CLLoad_Rec_Time_Year) != C_OK)
	{///*时间不合法,默认为2000年1月1日*///
		P_ucLoadParaTime[C_Minute_L] = 0x00;
		P_ucLoadParaTime[C_Hour_L] = 0x00;
		P_ucLoadParaTime[C_Day_L] = 0x01;
		P_ucLoadParaTime[C_Month_L] = 0x01;
		P_ucLoadParaTime[C_Year_L] = 0x00;
	}
//	SF_MinsAdd_LoadProfile(P_ucLoadParaTime,V_ucIntTime,V_ucStartTime);///*实际第一个点从负荷起始时间后一个间隔时间开始记*///
	SF_MinsAdd_LoadProfile(P_ucLoadParaTime,v_i,V_ucStartTime);///*根据广东测试修改，记录起始点允许抄读*///
	
	if(PF_Campare_Data(&V_ucDataTemp[C_TimeOffset],V_ucStartTime,C_LoadTimeLen) == C_GreaterThan)
	{///*取负荷记录起始时间和最近负荷记录时间的较大值，作为电表的实际第一个记录时间*///
		PF_CopyDataBytes(&V_ucDataTemp[C_TimeOffset],P_ucStartTime,C_LoadTimeLen);
	}
	else
	{
		PF_CopyDataBytes(V_ucStartTime,P_ucStartTime,C_LoadTimeLen);
	}
	return C_OK;
}		

///******************************************************************************************///
///*Function:uchar8 SF_FirstTime_LoadProfile												*///
///*Description:根据起始时间和数据层的实际负荷记录点,取出归一时间							*///
///*Input:	V_ulDataId-数据标识
///*		*P_ucInteTime-间隔时间
///*		* P_ucReadStartTime -读取负荷记录的起始时间，5字节（YYMMDDhhmm）
///*		*P_ucStartTime-最早负荷记录事件,6字节
///*		*P_ucParaTime-负荷起始时间
///*		* P_SendTime –用于输出,返回时间首地址,5字节
///*Output: * P_SendTime –实际返回数据中第一个负荷记录的记录时间					        *///
///*Return:	V_ucflag,为0表示不用重新计算块数，C_ReCal表示需重新计算        					*///
///*Calls:																					*///
///*Called By:SF_SepRead_LoadProfile														*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:																					*///
///*Others:																					*///
///******************************************************************************************///
uchar8 SF_FirstTime_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucInteTime,uchar8 *P_ucReadStartTime,uchar8 *P_ucStartTime,uchar8 *P_ucParaTime,uchar8 *P_ucSendTime)
{
	uchar8 V_ucTimeBuff[CLLoad_Rec_Time_Year+1];///*归一时间中间变量缓存*///
	uchar8 V_ucflag=0,V_ucIntTime=*P_ucInteTime;///*间隔时间*///
	ulong32 V_ulSubMins;

	V_ucTimeBuff[C_Sec] = 0;///*将抄读时间扩为6字节*///
	PF_CopyDataBytes(P_ucReadStartTime,&V_ucTimeBuff[C_Minute],CLLoad_Rec_Time_Year);
	
	if(PF_Campare_Data(&V_ucTimeBuff[C_Minute],&P_ucStartTime[C_Minute],C_LoadTimeLen) == C_LessThan)///*抄读时间比最早负荷记录时间*///
	{
		PF_CopyDataBytes(&P_ucStartTime[C_Minute],&V_ucTimeBuff[C_Minute],CLLoad_Rec_Time_Year);
		
		V_ucflag = C_ReCal;
	}
	PF_TimeSub_Min(V_ucTimeBuff,P_ucParaTime,&V_ulSubMins);///*取抄读时间与负荷起始时间差值*///
	
	if(((V_ulSubMins%V_ucIntTime) != 0)&&(V_ucIntTime != 0))///*差值不能整除间隔时间,则往后取最近一个整除点*///
	{
		V_ulSubMins = V_ucIntTime - (V_ulSubMins%V_ucIntTime);
		
		SF_MinsAdd_LoadProfile(&V_ucTimeBuff[C_Minute],V_ulSubMins,&V_ucTimeBuff[C_Minute]);
		
		V_ucflag = C_ReCal;
	}
	PF_CopyDataBytes(&V_ucTimeBuff[C_Minute],P_ucSendTime,CLLoad_Rec_Time_Year);
	
	return V_ucflag;
}

///******************************************************************************************///
///*Function:void SF_MinsAdd_LoadProfile													*///
///*Description:在格式YYMMDDhhmm的时间上累加分钟数											*///
///*Input:	*P_ucSourceTime-需累加的原始时间,起始时间为分,5字节长度
///*		V_ulAddMins-累加的分钟数,分数值最大为4天,16进制
///*Output: *P_ucResultTime –输出累加后的时间										        *///
///*Return:无                         											*///
///*Calls:																					*///
///*Called By:																				*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:1.由于带进来的年数为1字节长度,函数中默认为20XX年;
///*	2.*P_ucSourceTime和*P_ucResultTime可为同一地址;
///*	3.累加的时间不能超过一个月时间(28天)												*///
///*Others:	此函数专为连续抄读累加分钟使用,连续抄读最长为96小时,故此函数累加分钟最长为一个月*///
///******************************************************************************************///
void SF_MinsAdd_LoadProfile(uchar8 *P_ucSourceTime,ulong32 V_ulAddMins,uchar8 *P_ucResultTime)
{
	uchar8 V_ucTemp,V_ucMthTemp;
	uchar8 V_ucTimeBuff[C_LoadTLength];
	ulong32 V_ulCalTemp,V_ulTemp,V_ulYearTemp;

	
	SF_DECtoHEXByte(&P_ucSourceTime[0],&V_ucTemp);
	
	V_ulCalTemp = V_ulAddMins + V_ucTemp;///*从分钟开始累加*///
	
	V_ulTemp = V_ulCalTemp%60;
	
	PF_Ulong32ToBuffer4(&V_ucTemp,&V_ulTemp,1);
	
	V_ucTimeBuff[C_Minute_L] = SF_HEXtoDECByte(V_ucTemp);	///*赋值分钟*///
	
	if(V_ulCalTemp >= 60)
	{
		V_ulCalTemp /= 60;		

		SF_DECtoHEXByte(&P_ucSourceTime[1],&V_ucTemp);
		
		V_ulCalTemp += V_ucTemp;///*累加小时*///
		
		V_ulTemp = V_ulCalTemp%24;
		
		PF_Ulong32ToBuffer4(&V_ucTemp,&V_ulTemp,1);
		
		V_ucTimeBuff[C_Hour_L] = SF_HEXtoDECByte(V_ucTemp);	///*赋值小时*///
		
		if(V_ulCalTemp >= 24)
		{
			V_ulCalTemp /= 24;		
	
			SF_DECtoHEXByte(&P_ucSourceTime[2],&V_ucTemp);
			
			V_ulCalTemp += V_ucTemp;///*累加天*///
			
			if(P_ucSourceTime[3] == 2)///*2月需判断闰年*///
			{
				SF_DECtoHEXByte(&P_ucSourceTime[4],&V_ucTemp);
				
				V_ulYearTemp = V_ucTemp + 2000;///*计算出当前年,默认为20XX年*///
				
				if(((V_ulYearTemp%4)==0))///*20XX年只要被4整除就是闰年*///
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
				SF_DECtoHEXByte(&P_ucSourceTime[3],&V_ucTemp);
				
				V_ucMthTemp = C_MonthNum[V_ucTemp-1];
			}
			if(V_ulCalTemp==V_ucMthTemp)
			{
				V_ulTemp = V_ulCalTemp;
			}
			else
			{
				V_ulTemp = V_ulCalTemp%V_ucMthTemp;
			}
			PF_Ulong32ToBuffer4(&V_ucTemp,&V_ulTemp,1);
			
			V_ucTimeBuff[C_Day_L] = SF_HEXtoDECByte(V_ucTemp);///*赋值天*///
			
			if(V_ulCalTemp > V_ucMthTemp)///*大于当前月的天数*///
			{
				V_ulCalTemp /= V_ucMthTemp;		
		
				SF_DECtoHEXByte(&P_ucSourceTime[3],&V_ucTemp);
				
				V_ulCalTemp += V_ucTemp;///*累加月*///
				
				if(V_ulCalTemp==12)
				{
					V_ulTemp = 12;
				}
				else
				{
					V_ulTemp = V_ulCalTemp%12;
				}
				PF_Ulong32ToBuffer4(&V_ucTemp,&V_ulTemp,1);
				
				V_ucTimeBuff[C_Month_L] = SF_HEXtoDECByte(V_ucTemp);///*赋值月*///
				
				if(V_ulCalTemp > 12)///*大于当前月的天数*///
				{
					SF_DECtoHEXByte(&P_ucSourceTime[4],&V_ucTemp);
					
					V_ucTemp++;
			
					V_ucTimeBuff[C_Year_L] = SF_HEXtoDECByte(V_ucTemp);///*赋值年*///		
				}
				else
				{
					V_ucTimeBuff[C_Year_L] = P_ucSourceTime[4];///*赋值年*///	
				}
			}
			else
			{
				V_ucTimeBuff[C_Month_L] = P_ucSourceTime[3];///*赋值月*///
				
				V_ucTimeBuff[C_Year_L] = P_ucSourceTime[4];///*赋值年*///	
			}
		}
		else
		{
			V_ucTimeBuff[C_Day_L] = P_ucSourceTime[2];///*赋值天*///
			
			V_ucTimeBuff[C_Month_L] = P_ucSourceTime[3];///*赋值月*///
		
			V_ucTimeBuff[C_Year_L] = P_ucSourceTime[4];///*赋值年*///
		}
	}
	else
	{
		V_ucTimeBuff[C_Hour_L] = P_ucSourceTime[1];///*赋值小时*///
		
		V_ucTimeBuff[C_Day_L] = P_ucSourceTime[2];///*赋值天*///
		
		V_ucTimeBuff[C_Month_L] = P_ucSourceTime[3];///*赋值月*///
		
		V_ucTimeBuff[C_Year_L] = P_ucSourceTime[4];///*赋值年*///	
	}
	PF_CopyDataBytes(V_ucTimeBuff,P_ucResultTime,C_LoadTLength);///*将累加后时间传给目标地址*///
}

///******************************************************************************************///
///*Function:uchar8 SF_GetSeqData_LoadProfile												*///
///*Description:读取数据层指定个数的负荷数据,没数据的补充相应内容											*///
///*Input:	*V_ulDataId-下行报文中的数据标识
///*		* P_ucStartTime -读取负荷记录的起始时间，5字节（YYMMDDhhmm）
///*		* P_ucBlockNum-本次所需抄读块数
///*		*P_ucIntTime-间隔时间
///*		P_ucFollowFlag--是否为第一帧
///*		* P_ucGVBuffer—全局变量,输入时用于补电能数据
///*		* P_ucDataTemp –用于输出,数据缓存区
///*Output: * P_ucGVBuffer—用于输出,将读到的电能数据放入此处
///*		* P_ucDataTemp –用于输出,数据缓存区
///*Return:C_OK、C_Error                         											*///
///*Calls:																					*///
///*Called By:																				*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:																					*///
///*Others:																					*///
///******************************************************************************************///
uchar8 SF_GetSeqData_LoadProfile(ulong32 *V_ulDataId,uchar8 *P_ucStartTime,uchar8 *P_ucBlockNum,uchar8 *P_ucIntTime,uchar8 P_ucFollowFlag,uchar8 *P_ucGVBuffer,uchar8 *P_ucDataTemp)
{
	uchar8 V_ucDataLen=0;///*缓存区的数据长度,同时用作偏移量*///
	uchar8 V_ucReadTime[C_LoadTLength];
	uchar8 V_ucDataTemp[C_LoadMaxLen],V_ucLength_Load=C_LoadMaxLen,V_ucNum_RdLoad=1;;///*负荷数据缓存区*///
	ulong32 V_ulLoadTypeID;///*对应的负荷类型标识码*////
	ulong32 V_ulTemp;
	uchar8 V_ucDataLength,V_ucOffset,V_ucBlockNum=*P_ucBlockNum;
	uchar8 i,j,V_ucTemp,V_ucReturnTemp=0;
	uchar8 V_ucFirstReadFlag = 0x11;///*在后续帧中指示第一次读数据标志,在读数据成时判断,当第一次读时用C_FirstFrame,否则为C_OtherFrame*///
	uchar8 V_ucTableLen = sizeof(Str_LoadStatus)/sizeof(Str_LoadReadStatus);
	uchar8 V_ucData[C_LoadMaxLen];
	
	PF_CopyDataBytes(P_ucStartTime,V_ucReadTime,C_LoadTLength);///*赋值抄读时间*///
	
	for(i=0;i<V_ucTableLen;i++)
	{
		if((*V_ulDataId) == Str_LoadStatus[i].V_ulDataId)
		{
			V_ulLoadTypeID = Str_LoadStatus[i].V_ulTypeId;///*赋值类型标识码*///
		
			V_ucDataLength = Str_LoadStatus[i].V_ucDataLen;///*赋值数据长度*///
			
			V_ucOffset = Str_LoadStatus[i].V_ucOffset;///*赋值偏移量*///
			
			break;
		}
	}
	if(i >= V_ucTableLen)
	{
		return C_Error;
	}
	if(P_ucFollowFlag == C_FirstFrame)///*第一帧,需将标识码和时间放入缓存*///
	{
		V_ucFirstReadFlag = 0xFF;///*当第一帧时,后续读数据层必为C_OtherFrame,此处置为FF*///
		
		PF_CopyDataBytes(V_ucReadTime,&P_ucDataTemp[V_ucDataLen],CLLoad_Rec_Time_Year);///*将起始点时间放入缓存*///
		V_ucDataLen += C_LoadTLength;	
		
		if(InF_ReadLoadData(V_ulLoadTypeID,V_ucReadTime,V_ucDataTemp,&V_ucNum_RdLoad,&V_ucLength_Load,C_FirstFrame)!=C_OK)
		{
			V_ucReturnTemp = 0xAA;
		}
		///*比较负荷记录的时间与之前所得的读取时间大小关系*///
		V_ucTemp = PF_Campare_Data(&V_ucDataTemp[C_TimeOffset],V_ucReadTime,CLLoad_Rec_Time_Year);
		
		if(V_ucTemp == C_Equal)///*当前时间和负荷记录时间相等时,直接赋值数据*///
		{///*将负荷数据放入缓存*///
			PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],&P_ucDataTemp[V_ucDataLen],V_ucDataLength);	
			
			if(SF_JudgeType_LoadProfile(*V_ulDataId)==C_LoadType_Energy)///*电能类数据,需将数据放入全局变量中*///
			{
				PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],P_ucGVBuffer,V_ucDataLength);
			}
			V_ucDataLen += V_ucDataLength;///*更新数据长度*///
		
			V_ucBlockNum --;///*抄读块更新*///
		
			SF_MinsAdd_LoadProfile(V_ucReadTime,*P_ucIntTime,V_ucReadTime);///*更新抄读时间*///
		}
		if((V_ucTemp != C_Equal) || (V_ucReturnTemp == 0xAA))
		{///*若读到的时间和要求时间不符,当读电能负荷时,往前读取最近一次负荷记录数据*///
			if(SF_JudgeType_LoadProfile(*V_ulDataId) == C_LoadType_Energy)
			{
				V_ucLength_Load=C_LoadMaxLen;
				V_ucNum_RdLoad = 1;
				
				if(InF_ReadLastTimeLoadData(V_ulLoadTypeID,V_ucReadTime,V_ucData,&V_ucNum_RdLoad,&V_ucLength_Load)!= C_OK)///*往前读最近相关负荷记录*///
				{///*往前无数据，电能则补零*///
					for(i=0;i<V_ucDataLength;i++)
					{
						V_ucData[V_ucOffset + i] = 0;
					}
				}
				///*将数据放入全局变量*///
				PF_CopyDataBytes(&V_ucData[V_ucOffset],P_ucGVBuffer,V_ucDataLength);
			}
			if(V_ucReturnTemp == 0xAA)///*若读不到后续负荷数据,补全数据*///
			{
				for(i=0;i<V_ucBlockNum;i++)
				{
					SF_FillData_LoadProfile(*V_ulDataId,P_ucGVBuffer,&P_ucDataTemp[V_ucDataLen],V_ucDataLength);///*补数据*///
					V_ucDataLen +=V_ucDataLength;///*累加长度*///
				}
				return C_OK;
			}
			else///*需补数据*///
			{
				SF_FillData_LoadProfile(*V_ulDataId,P_ucGVBuffer,&P_ucDataTemp[V_ucDataLen],V_ucDataLength);///*补数据*///
				
				V_ucDataLen +=V_ucDataLength;///*累加长度*///
				i = 1;
				
				PF_Buffer4ToUlong32(P_ucIntTime,&V_ulTemp,1);///*将间隔时间转ulong32,用作累加读取时间*///
		
				for(;i<V_ucBlockNum;i++)
				{
					SF_MinsAdd_LoadProfile(V_ucReadTime,V_ulTemp,V_ucReadTime);///*累加时间间隔*///
					
					V_ucTemp = PF_Campare_Data(&V_ucDataTemp[C_TimeOffset],V_ucReadTime,CLLoad_Rec_Time_Year);
			
					if(V_ucTemp == C_Equal)///*相等则将数据赋值*///
					{
						PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],&P_ucDataTemp[V_ucDataLen],V_ucDataLength);
						V_ucDataLen +=V_ucDataLength;///*累加长度*///
						
						SF_MinsAdd_LoadProfile(V_ucReadTime,*P_ucIntTime,V_ucReadTime);///*更新抄读时间*///
						
						if(SF_JudgeType_LoadProfile(*V_ulDataId)==C_LoadType_Energy)///*电能类数据,需将数据放入全局变量中*///
						{
							PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],P_ucGVBuffer,V_ucDataLength);
						}
                        i++;
						break;
					}
					else if(V_ucTemp == C_LessThan)///*数据层返回时间小于累加时间,退出j循环,继续读累加时间负荷*///
					{
						break;
					}
					else///*数据层返回时间大于累加时间,则继续j循环累加间隔时间*///
					{
						SF_FillData_LoadProfile(*V_ulDataId,P_ucGVBuffer,&P_ucDataTemp[V_ucDataLen],V_ucDataLength);///*补数据*///
						V_ucDataLen +=V_ucDataLength;///*累加长度*///
						
						continue;
					}
				}
				V_ucBlockNum -= i;///*抄读块更新*///
			}
		}
	}
	for(i=0;i<V_ucBlockNum;i++)///*i循环*///
	{
		V_ucLength_Load = C_LoadMaxLen;
		V_ucNum_RdLoad = 1;
		
		if(V_ucFirstReadFlag == 0x11)///*当后续帧首次读数据层时,需用C_FirstFrame读*///
		{
			V_ucFirstReadFlag = 0xFF;
			
			V_ucTemp = InF_ReadLoadData(V_ulLoadTypeID,V_ucReadTime,V_ucDataTemp,&V_ucNum_RdLoad,&V_ucLength_Load,C_FirstFrame);
		}
		else
		{
			V_ucTemp = InF_ReadLoadData(V_ulLoadTypeID,V_ucReadTime,V_ucDataTemp,&V_ucNum_RdLoad,&V_ucLength_Load,C_OtherFrame);
		}
		if(V_ucTemp != C_OK)
		{
			for(j=0;j<(V_ucBlockNum-i);j++)
			{
				SF_FillData_LoadProfile(*V_ulDataId,P_ucGVBuffer,&P_ucDataTemp[V_ucDataLen],V_ucDataLength);///*补数据*///
				V_ucDataLen +=V_ucDataLength;///*累加长度*///
			}
			return C_OK;
		}
		///*比较负荷记录的时间与之前所得的读取时间大小关系*///
		V_ucTemp = PF_Campare_Data(&V_ucDataTemp[C_TimeOffset],V_ucReadTime,CLLoad_Rec_Time_Year);
		
		if(V_ucTemp == C_Equal)///*返回时间和读取时间相同,则将数据放入缓存区和全局变量中*///
		{
			PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],&P_ucDataTemp[V_ucDataLen],V_ucDataLength);
			V_ucDataLen +=V_ucDataLength;///*累加长度*///
			
			SF_MinsAdd_LoadProfile(V_ucReadTime,*P_ucIntTime,V_ucReadTime);///*更新抄读时间*///
			
			if(SF_JudgeType_LoadProfile(*V_ulDataId)==C_LoadType_Energy)///*电能类数据,需将数据放入全局变量中*///
			{
				PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],P_ucGVBuffer,V_ucDataLength);
			}
		}
		else
		{
			SF_FillData_LoadProfile(*V_ulDataId,P_ucGVBuffer,&P_ucDataTemp[V_ucDataLen],V_ucDataLength);///*补数据*///
			
			V_ucDataLen +=V_ucDataLength;///*累加长度*///
			i++;
			
			PF_Buffer4ToUlong32(P_ucIntTime,&V_ulTemp,1);///*将间隔时间转ulong32,用作累加读取时间*///
			
			for(;i<V_ucBlockNum;i++)///*j循环*///
			{
				SF_MinsAdd_LoadProfile(V_ucReadTime,V_ulTemp,V_ucReadTime);///*累加时间间隔*///
				
				V_ucTemp = PF_Campare_Data(&V_ucDataTemp[C_TimeOffset],V_ucReadTime,CLLoad_Rec_Time_Year);
		
				if(V_ucTemp == C_Equal)///*相等则将数据赋值*///
				{
					PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],&P_ucDataTemp[V_ucDataLen],V_ucDataLength);
					V_ucDataLen +=V_ucDataLength;///*累加长度*///
					
					SF_MinsAdd_LoadProfile(V_ucReadTime,*P_ucIntTime,V_ucReadTime);///*更新抄读时间*///
					
					if(SF_JudgeType_LoadProfile(*V_ulDataId)==C_LoadType_Energy)///*电能类数据,需将数据放入全局变量中*///
					{
						PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],P_ucGVBuffer,V_ucDataLength);
					}
					break;
				}
				else if(V_ucTemp == C_LessThan)///*数据层返回时间小于累加时间,退出j循环,继续读累加时间负荷*///
				{
					i--;
					
					break;
				}
				else///*数据层返回时间大于累加时间,则继续j循环累加间隔时间*///
				{
					SF_FillData_LoadProfile(*V_ulDataId,P_ucGVBuffer,&P_ucDataTemp[V_ucDataLen],V_ucDataLength);///*补数据*///
					V_ucDataLen +=V_ucDataLength;///*累加长度*///
					
					continue;
				}
			}
		}	
	}
	return C_OK;
}

///******************************************************************************************///
///*Function:void  SF_FillData_LoadProfile													*///
///*Description:补数据函数																	*///
///*Input:	V_ulDataId-需读取数据的数据标识
///*		* P_ucGVBuffer –存放电能临时数据的全局变量
///*		*P_ucDataTemp-用于输出,将补数据放在此处
///*		V_ucLength-用于输出,所读数据的长度
///*Output: *P_ucDataTemp-用于输出,将补数据放在此处
///*Return:无			                         											*///
///*Calls:																					*///
///*Called By:																				*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:																					*///
///*Others:																					*///
///******************************************************************************************///
void SF_FillData_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucGVBuffer,uchar8 *P_ucDataTemp,uchar8 V_ucLength)
{
	uchar8 V_ucTemp[16];
	uchar8 i;
		
	if(SF_JudgeType_LoadProfile(V_ulDataId)==C_LoadType_Energy)///*电能类数据,需取全局变量中数据进行补充*///
	{
		PF_CopyDataBytes(P_ucGVBuffer,P_ucDataTemp,V_ucLength);	
	}
	else///*瞬时量补FF*///
	{
		for(i=0;i<V_ucLength;i++)
		{
			V_ucTemp[i] = 0xFF;	
		}
		PF_CopyDataBytes(V_ucTemp,P_ucDataTemp,V_ucLength);	
	}
}

///****************************************************************************************///
///*Function：uchar8 SF_JudgeType_LoadProfile										     *///
///*Description：根据标识码,判断要求读取的负荷类型       								  *///
///*Input：*V_ulID-抄读负荷记录的标识码													  *///
///*Output：无																			  *///
///*Return:			                         										*///
///*Calls：																				  *///
///*Called By：																			  *///
///*Influence：无																		  *///
///*Tips：																				  *///
///*Others：																			  *///
///*Author:																				  *///
///****************************************************************************************///
uchar8 SF_JudgeType_LoadProfile(ulong32 V_ulID)
{
	if((V_ulID &0x00000600)==0x00000600)///*电能类数据061006XX和061007XX,低2字节第2/3位为1*///
	{
		return C_LoadType_Energy;
	}
	else
	{
		return C_LoadType_Variable;
	}
}

///****************************************************************************************///
///*Function：void SF_DECtoHEXByte(uchar8 *V_ucSourceData,uchar8 *V_ucResultData)	     *///
///*Description：1字节10进制数转化为1字节16进制数       								  *///
///*Input：10进制数地址V_ucSourceData,转化后16进制数地址V_ucResultData					  *///
///*Output：无																			  *///
///*Calls：																				  *///
///*Called By：																			  *///
///*Influence：无																		  *///
///*Tips：																				  *///
///*Others：																			  *///
///*Author:																				  *///
///****************************************************************************************///
void SF_DECtoHEXByte(uchar8 *V_ucSourceData,uchar8 *V_ucResultData)
{
	*V_ucResultData = ((*V_ucSourceData >> 4) * 10) + (*V_ucSourceData & 0x0f);
}

///************************************************************************************************************************************///
///*Function：uchar8 SF_HEXtoDECByte																                         */// 
///*Description：将1个16进制BCD码, 转换为10进制数																				  *///
///*Input：HEXdata-hex格式数据										 							  *///
///*Output：无																								  *///
///*Return:十进制BCD                         											*///
///*Calls：																															  *///
///*Called By：																														  *///
///*Influence：无 																													  *///
///*Tips：此函数仅支持年月日时分的转换,最大值为99,故返回值为uchar8												 *///
///*Others：																														  *///
///*Author:																												  *///
///************************************************************************************************************************************///
uchar8 SF_HEXtoDECByte(uchar8 HEXdata)  
{
	ushort16 i;	
	
	i=HEXdata/10;
	
	i=i<<4;
	
	i+=HEXdata%10;

	return(i);		
}
