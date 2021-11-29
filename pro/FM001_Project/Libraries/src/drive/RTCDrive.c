

///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     RTCDrive.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   外部实时时钟驱动文件
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


#include "RTCDrive.h"
#include "Communication.h"

/////*复旦微RTC
ushort16		Temperature_Adc;//当前温度ADC值(hex码)
float		Rtcadj_Offset;//温度补偿调校值
float		Rtcadj_Offset2;//温度补偿调校值
uchar8	RtcStopProcFlag;//停止温补标志
char8		Temperature_Hex;//备份温度(hex码)
uchar8	temperpara_veri_flag;//温度系数校验标志

//
////温度曲线相关参数
//const uchar8 RTC_Trim_Ctrl = 0x55;	//0x55-补偿步长0.119ppm，其它-补偿补偿0.238ppm(仅404模式下可开启0.119)
//const uchar8 SleepPtatOffsetCfg = 0x55;	//0x55-启用3V偏置(3V电源ptat偏置控制开关)，其他-关闭
//const float const_xtl_top	= 25.0;		//计算温度曲线使用的顶点
//const float const_KL	= 0.0300;	//温度补偿系数
//const float const_KH	= 0.0382;
//const float const_TmpsL	= 5.0379;	//温度ADC斜率
//const float const_TmpsH	= 5.0379;
//const uchar8 constF_Volt	= 0;		//电压补偿量(兼容新硬件电池增加二极管),3表示0.03v/10表示0.1v
//const ushort16 const_adc_TrimB = 0x3ff;
//const ushort16 const_adc_TrimT = 0x640;
//const ushort16 const_KHKL_TrimRange = 36;//晶体曲线修调功能分界范围，25度±7度内使用常温修调值krh，krl，范围外使用高低温修调值kh，kl
//const float const_T_OffsetRun	= -3.0;	//芯片发热修正-运行用
//const float const_T_OffsetSlp	= -2.0;	//芯片发热修正-休眠用
//const uchar8 const_TopNoTrim = 0x55;  //顶点±x度附近不补偿 0x55:不补偿， 0x00:正常补偿
//const uchar8 const_TopNTRange = 8;	//顶点附近关闭自动补偿温度adc范围，±x/5.0379=温度范围
//const float const_T_CL	= -23.0;	//低温查表中心温度
//const float const_T_CH	= 62.0;		//高温查表中心温度
//const uchar8 const_C_Mode = 0x55;		//0x55:启动高低温高精度查表功能，其他，仅开启常温高精度查表
//
//const short16 const_TR_LSTART	= -15*10;	//低温记录启动温度（short16放大10倍）
//const short16 const_TR_HSTART	= 50*10;	//高温记录启动温度（short16放大10倍）
/////const uchar8 const_TR_GAP		= 6;//1;//	//记录间隔，单位分钟
/////const uchar8 const_TR_Mode 	= 0x55;		//0x55:启动温度记录功能，其他，关闭



///*底层驱动函数											*///
///*所有的底层驱动函数使用static定义，只能在该.c里面调用。	*///

///***********************************************************************************///
///*Function：判断寄存器值是否为设置值，如不是则设置为设置值
///*Description：
///*Input：ulong32 *RegAddr输入寄存器地址；ulong32 Value：寄存器设置值；
///*Output：
///*Return：C_OK:寄存器值为设置值;C_Error：寄存器值非设置值
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
//uchar8 DF_CheckSysReg( __IO ulong32 *RegAddr, ulong32 Value )
//{
//	if( *RegAddr != Value )
//	{
//		*RegAddr = Value;
//		return C_OK;
//	}
//	else
//	{
//		return C_Error;
//	}
//}
///***********************************************************************************///
///*Function：将RTCYYMMDDWWhhmmss读取到指定地址
///*Description：
///*Input：*p：指定缓冲区首地址(指向ss)，Len：长度，固定为7，使用宏定义
///*Output：7字节的日期时间
///*Return：C_OK:读取成功;C_TIMEERR:读出的时间非法
///*Calls：
///*Called By：主调度每500ms读取一次
///*Influence：
	///*1、读出的数据不判断是否正确。*///
	///*2、读取成功后才刷新入口指针指向的数据区*///
	///*3、在读时钟函数里面，不进行s/m/h/d/m/y变化的判断与处理。                                                    *///
///*Tips：
///*Others：
///***********************************************************************************///
uchar8 InF_ReadRTC(uchar8 *P_Time,uchar8 Len)
{
	uchar8	i,j;
	uchar8 BufA[C_RTCLen];

	if(Len != C_RTCLen)		///*读外部RTC，固定长度：7字节的YYMMDDWWhhmmss*///
	{
		return C_DataLenError;
	}

	for(j=0;j<3;j++)
	{
		BufA[0] = RTC->BCDSEC;
		BufA[1] = RTC->BCDMIN;
		BufA[2] = RTC->BCDHOUR;
		BufA[3] = RTC->BCDWEEK;
		BufA[4] = RTC->BCDDATE;
		BufA[5] = RTC->BCDMONTH;
		BufA[6] = RTC->BCDYEAR;

		P_Time[0] = RTC->BCDSEC;
		P_Time[1] = RTC->BCDMIN;
		P_Time[2] = RTC->BCDHOUR;
		P_Time[3] = RTC->BCDWEEK;
		P_Time[4] = RTC->BCDDATE;
		P_Time[5] = RTC->BCDMONTH;
		P_Time[6] = RTC->BCDYEAR;

		for(i=0;i<7;i++) //比对两次时钟是否一致
		{
			if( BufA[i] != P_Time[i] )
			{
				break;
			}
		}

		if( i == 7 ) //两者一致, 表示读取成功
		{
			if((PF_DataTimeActive(P_Time,C_DT_Start_ss,3)==C_OK)&&(PF_DataTimeActive(P_Time+4,C_DT_Start_DD,3)==C_OK))
			{///*判断ssmmhh和DDMMYY的合法性*///
				return C_OK;
			}
		}
	}
	return C_TIMEERR;
}
///***********************************************************************************///
///*Function：将日期时间写入RTC
///*Description：
///*Input：
	///**P_Time指向要写入日期时间的缓冲区首地址(ss)，数据格式为YYMMDDWWhhmmss	         *///
	///*Len：固定为7，用宏定义表示，因为涉及到指针，可以使用该入口参数用作安全标记。 *///
///*Output：
///*Return：C_Ok：写成功；C_IICError：I2c故障，写不成功
///*Calls：
///*Called By：
///*Influence：
	///*1、写的数据不判断万年历，“周次”外面写入时带入。                                                		*///
///*Tips：
///*Others：
///***********************************************************************************///
uchar8 InF_WriteRTC(uchar8 *P_Time,uchar8 Len)
{
	uchar8 V_TimeBuff[C_RTCLen],i;
	uchar8 V_TimeBuffCopy[C_RTCLen],V_ReturnFlag,j;

	PF_CopyDataBytes(P_Time,&V_TimeBuff[0],C_RTCLen);	///*将7字节时间日期拷贝:此处不用入口带过来的长度*///

	if( Len != C_RTCLen )		///*写RTC，固定长度：7字节的YYMMDDWWhhmmss*///
	{
		return C_DataLenError;
	}
	else
	{
		for( i=0; i<3; i++ )
		{
			EnWr_WPREG();///*寄存器写使能

			RTC->BCDSEC 	= V_TimeBuff[0];
			RTC->BCDMIN 	= V_TimeBuff[1];
			RTC->BCDHOUR	= V_TimeBuff[2];
			RTC->BCDWEEK	= V_TimeBuff[3];
			RTC->BCDDATE	= V_TimeBuff[4];
			RTC->BCDMONTH	= V_TimeBuff[5];
			RTC->BCDYEAR	= V_TimeBuff[6];

			DisWr_WPREG();///*禁止写

			V_ReturnFlag = InF_ReadRTC( &V_TimeBuffCopy[0],C_RTCLen);
			if(V_ReturnFlag == C_OK) //读取成功
			{
				for(j=0;j<7;j++)
				{
					if(V_TimeBuff[j]!=V_TimeBuffCopy[j])
					{
						break;
					}
				}

				if(j==7) //当前值和设置值相等, 设置成功
				{
					return C_OK; //设置成功
				}
			}
		}
		return C_TIMEERR; //设置失败
	}
}
///***********************************************************************************///
///*Function：初始化RTC相关配置。
///*Description：
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
	///*1、上电初始化调用一次。*///
///*Others：
///***********************************************************************************///
void InF_InitalRTC(void)
{
	if((RCC->PERCLKCON1&RCC_PERRCCCON1_RTCRCCEN_ON)!=RCC_PERRCCCON1_RTCRCCEN_ON)
	{
		RCC->PERCLKCON1|=RCC_PERRCCCON1_RTCRCCEN_ON;///*
	}
	if(RTC->RTCIE!=0)
	{
		RTC->RTCIE	&=	0xFFFFE000;		///*RTC中断使能禁止.
	}
	if(RTC->RTCIF!=0)
	{
		RTC->RTCIF |= 0x00001FFF; 	///*清中断标志
	}
	RTC->FSEL = RTC_FSEL_FSEL_PLL1HZ;	///*Tout输出高频补偿1hz

	///*TOUT输出口操作
	if((IO_MCUSECOND->MODER & MCUSECOND_ANALOG_MODE)!= MCUSECOND_SELECT_AF)
	{
		IO_MCUSECOND->MODER &= MCUSECOND_IN_MODE;
		IO_MCUSECOND->MODER |= MCUSECOND_SELECT_AF;
	}
	if((IO_MCUSECOND->INEN & MCUSECOND_IN_On)== MCUSECOND_IN_On)
	{
		IO_MCUSECOND->INEN &= MCUSECOND_IN_Off;
	}
	if((IO_MCUSECOND->PUPDR & MCUSECOND_PULLUP)== MCUSECOND_PULLUP)
	{
		IO_MCUSECOND->PUPDR &= MCUSECOND_NOPUPD;
	}
	if((IO_MCUSECOND->OTYPER & MCUSECOND_OUTPUT_OD)!= MCUSECOND_OUTPUT_OD)
	{
		IO_SECOND->OTYPER |= MCUSECOND_OUTPUT_OD;
	}
	if(GPIO->FOUTSEL != 0x00000005)
	{
		GPIO->FOUTSEL = 0x00000005;
	}

	InF_CheckRTC();  ///*

//	if((ANAC->FDETIF&0x00000040)==0x00000040)///*XTLF 停振检测,防止到check函数中
//	{
//		ANAC->XTLFIPW=RCC_XTLFIPW_250NA;
//	}
//	RCC->PLLCON=(RCC_PLLCON_PLLDB32768|RCC_PLLCON_PLLOSEL0|RCC_PLLCON_PLLINSEL_XTLF);
//	RCC->PLLCON|=RCC_PLLCON_PLLEN_ON;
}

///***********************************************************************************///
///*Function：判断RTC的SFR是否正确
///*Description：
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：1、读出SFR是否正确，如果不准确，写入正确值。
///*Tips：
	///*1、上电初始化调用一次。*///
	///*2、每分钟调用一次。    *///
///*Others：
///***********************************************************************************///
//static const struct
//{
//	ushort16	DFAH;							///*系数A, 常数项高位
//	ushort16	DFAL;							///*系数A, 常数项低位
//	ushort16	DFBH;							///*系数B, 一次项高位
//	ushort16	DFBL;							///*系数B, 一次项低位
//	ushort16	DFCH;							///*系数C, 二次项高位
//	ushort16	DFCL;							///*系数C, 二次项低位
//	ushort16	DFDH;							///*系数D, 三次项高位
//	ushort16	DFDL;							///*系数D, 三次项低位
//	ushort16	DFEH;							///*系数E, 四次项高位
//	ushort16	DFEL;							///*系数E, 四次项低位
//	ushort16	Toff;							///*温度偏置系数
//	ushort16	MCON01;						///*控制系数01
//	ushort16	MCON23;						///*控制系数23
//	ushort16	MCON45;						///*控制系数45
//}TAB_DFx[1] =
//{
//	{0x0000,0x0000,0x007F,0xD9A0,0x007E,0xDA54,0x0000,0x4C2A,0x007F,0xFD73,0x0000,0x0000,0x0000,0x0000},   ///*   TP_603x
//};

void InF_CheckRTC(void)
{
	if(RTC->STAMPEN!=(RTC_STAMPEN_STAMP1EN_Msk|RTC_STAMPEN_STAMP0EN_Msk))
	{
		RTC->STAMPEN=(RTC_STAMPEN_STAMP1EN_Msk|RTC_STAMPEN_STAMP0EN_Msk);
	}

	if((ANAC->FDETIF&0x00000040)==0x00000040)///*XTLF 停振检测,未停振
	{
		if(RCC->XTLFIPW!=RCC_XTLFIPW_250NA)
		{
			RCC->XTLFIPW=RCC_XTLFIPW_250NA;
		}
		if(RCC->PLLCON!=(RCC_PLLCON_PLLDB32768|RCC_PLLCON_PLLOSEL0|RCC_PLLCON_PLLINSEL_XTLF|RCC_PLLCON_PLLEN_ON))
		{
			RCC->PLLCON=(RCC_PLLCON_PLLDB32768|RCC_PLLCON_PLLOSEL0|RCC_PLLCON_PLLINSEL_XTLF|RCC_PLLCON_PLLEN_ON);
			RCC->PLLCON|=RCC_PLLCON_PLLEN_ON;
			InF_Delay_us(4000);///*延时
		}
		if(RTC->FSEL!=RTC_FSEL_FSEL_PLL1HZ)
		{
			RTC->FSEL=RTC_FSEL_FSEL_PLL1HZ;
		}
		if(RTC->PR1SEN!=RTC_PR1SEN_PR1SEN_Msk)
		{
			RTC->PR1SEN=RTC_PR1SEN_PR1SEN_Msk;
		}
	}
	///*复旦微温度补偿系数校验
	Temperpara_Verify();	//温度系数校验
}

/************************************************************************
*函数功能:上电时，从数据层读出时钟历史状态,并赋电表运行状态字中的时钟故障状态
*输入参数:无
*输出参数:时钟历史状态/电表运行状态字1
*返回参数:无
*调用时机：
************************************************************************/
void SF_InitRTCState(void)
{
	uchar8 V_ucBuffer[5];
	ushort16 V_uslen, V_usDataEncode;

	Str_RTC_Status.Timer = 0;
	/*从数据层读出电池的历史状态*/
	V_uslen = CLClock_FaultState;
	if( InF_Read_Data(CClock_FaultState, &Str_RTC_Status.HStatus, &V_uslen, &V_usDataEncode) != C_OK )
	{
		Str_RTC_Status.HStatus = C_RTC_OK;
	}
	/*更新数据层时钟故障状态标志：故障或正常；首先从数据层读，刷新后再写*/
	V_uslen = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1, &V_ucBuffer[0], &V_uslen, &V_usDataEncode);
	if(Str_RTC_Status.HStatus == C_RTC_OK)
	{
		V_ucBuffer[1] &= ~C_RTCERR_MeterWorkState;
	}
	else
	{
		V_ucBuffer[1] |= C_RTCERR_MeterWorkState;
	}
	InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State1, &V_ucBuffer[0], CLMeter_Work_State1, C_W_SafeFlag);
}
/************************************************************************
*函数原型:void InF_ExecuteClr_RTC(void)
*函数功能:电表总清时，对于时钟故障标志的处理
*输入参数:
*输出参数：
*返回参数:无
*调用时机：
*备注:
*功能说明：
************************************************************************/
void InF_ExecuteClr_RTC(void)
{
	uchar8 V_ucBuffer[5];
	ushort16 V_uslen, V_usDataEncode;

	Str_RTC_Status.HStatus = C_RTC_OK;
	Str_RTC_Status.Timer = 0;

	/*总清后将历史状态(时钟正常)写数据层*/
	InF_Write_Data(C_Msg_Dispatch, CClock_FaultState, &Str_RTC_Status.HStatus, CLClock_FaultState, C_W_SafeFlag);

	/*更新数据层RTC故障状态标志：故障或正常；首先从数据层读，刷新后再写*/
	V_uslen = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1, &V_ucBuffer[0], &V_uslen, &V_usDataEncode);

	V_ucBuffer[1] &= ~C_RTCERR_MeterWorkState;

	InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State1, &V_ucBuffer[0], CLMeter_Work_State1, C_W_SafeFlag);
}
/*******************************************************************************
函数原型：void SF_SetRTCErrState(uchar8 V_ucRTCFlag)
功能描述：置时钟故障状态位，电表运行状态字1 bit15
输入参数：V_ucRTCFlag RTC的状态
         RTC的状态是置位还是清位 C_RTC_ERR，置位；C_RTC_OK 清位
输出参数：无
返回参数：无
调用位置：首先从数据层读，刷新后再写
备    注：发生故障置电表运行状态字 ，写时钟故障自扩状态
*******************************************************************************/
void SF_SetRTCErrState(uchar8 V_ucRTCFlag)
{
	uchar8 V_ucBuffer[CLMeter_Work_State1];
	ushort16 V_uslen, V_usDataEncode;

	V_uslen = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1, &V_ucBuffer[0], &V_uslen, &V_usDataEncode);
	if(V_ucRTCFlag == C_RTC_OK)
	{
		V_ucBuffer[1] &= ~C_RTCERR_MeterWorkState;
	}
	else
	{
		V_ucBuffer[1] |= C_RTCERR_MeterWorkState;
	}
	InF_Write_Data(C_Msg_Dispatch,CMeter_Work_State1, &V_ucBuffer[0], CLMeter_Work_State1, C_W_SafeFlag);
	InF_Write_Data(C_Msg_Dispatch,CClock_FaultState, &V_ucRTCFlag, CLClock_FaultState, C_W_SafeFlag);
}
///*****************************************************************************///
///*函数原型:uchar8 SF_BackTimeIllegal(uchar8 V_ucBackTimeLegitFlag)           *///
///*函数功能:铁电备份时间非法或数据层读不出，将时间恢复为2000年1月1日 ，置状态字*///
///*输入参数:*pData，时间，6字节，年月日时分秒 ;                               *///
///*输出参数:*pData：恢复后时间，2000年1月1日00：00：00                        *///
///*返回参数:无                                                                *///
///*调用时机：                                                                 *///
///*备注:                                                                      *///
///*****************************************************************************///
void SF_BackTimeIllegal(uchar8 *pData)
{
	memset(pData,0,CLTime);//00：00：00
    memset(&pData[CLTime],0x01,CLMonthAndDay);//1月1日
	pData[CLTime+CLMonthAndDay]=0xd0;//2000年
	pData[CLTime+CLMonthAndDay+1]=0x07;//2000年
	SF_SetRTCErrState(C_RTC_ERR);
}

/****************************************************************************
*函数原型:uchar8 SF_RTCErrJudgeAndDeal(uchar8 *pData)
*函数功能:时钟故障判断及需要恢复的时间赋值
*输入参数:*pData，时间，6字节，年月日时分秒
*输出参数:*pData：如果需要恢复时间，赋值恢复后的时间；如果不需要赋值为原时间
*返回参数:是否发生了时钟故障,C_RTC_OK未发生故障；C_RTC_ERR发生故障
*调用时机：500ms
*备注:发生故障置电表运行状态字
*****************************************************************************/
uchar8 SF_RTCErrJudgeAndDeal(uchar8 *pData)
{
	uchar8 V_ucBuffer[CLDate_Time];
	uchar8 V_ucResult_RTCActive = C_OK, V_ucReturn = C_RTC_ERR;
	ushort16 V_usDataLenth, V_usDataEncode;
    ulong32 V_ulSubDays = 0;

	V_ucResult_RTCActive = PF_DataTimeActive_698(pData, C_DT_Start_ss, CLBackTime_OneSec);	/*RTC合法性*/

	V_usDataLenth = CLBackTime_OneSec;
	if(InF_Read_Data(CBackTime_OneSec, V_ucBuffer, &V_usDataLenth, &V_usDataEncode) == C_OK)
	{
		if(PF_DataTimeActive_698(V_ucBuffer, C_DT_Start_ss, CLBackTime_OneSec) == C_OK)		/*铁电时间合法性*/
		{
			if(V_ucResult_RTCActive == C_OK)
			{
			    if(PF_TimeSub_Day_698(pData, V_ucBuffer, &V_ulSubDays) == C_LessThan)			/*倒退*/
			    {
			        PF_CopyDataBytes(V_ucBuffer, pData, CLBackTime_OneSec); 			/*铁电时间恢复RTC*/
		            SF_SetRTCErrState(C_RTC_ERR);
					V_ucReturn = C_RTC_ERR;
			    }
			    else
			    {
				    if(V_ulSubDays > C_Day1000)
				    {
                        PF_CopyDataBytes(V_ucBuffer, pData, CLBackTime_OneSec); 		/*铁电时间恢复RTC*/
					    SF_SetRTCErrState(C_RTC_ERR);									/*只置状态，不恢复时间，此情况校时来恢复*/
					    V_ucReturn = C_RTC_ERR;
				    }
				    else
				    {
					    V_ucReturn = C_RTC_OK;
				    }
			    }
			}
			else 														/*铁电合法，RTC非法*/
			{
			    PF_CopyDataBytes(V_ucBuffer,pData, CLBackTime_OneSec);	/*铁电时间恢复RTC*/
		        SF_SetRTCErrState(C_RTC_ERR);
				V_ucReturn = C_RTC_ERR;
			}
		}
		else															/*铁电非法*/
		{
			SF_BackTimeIllegal(pData);
			V_ucReturn = C_RTC_ERR_BackTime;
		}
	}
	else
	{
		if(V_ucResult_RTCActive == C_OK)
		{
			V_ucReturn = C_RTC_OK;
		}
		else															/*铁电时间和RTC均非法，时间恢复为2000年1月1日，00：00：00*/
		{
		   SF_BackTimeIllegal(pData);
	       V_ucReturn = C_RTC_ERR_BackTime;
		}
	}
    return  V_ucReturn;
}

/************************************************************************
*函数原型:void InF_Execute_RTCErr(uchar8 P_Buff)
*函数功能:处理时钟故障标志
*输入参数:当前操作时钟成功、失败标志：C_OK、C_Error
*输出参数：将当前操作时钟成功/失败标志刷新数据层，并据此进行主动上报
*返回参数:无
*调用时机：
*备注:
*功能说明：
************************************************************************/
void InF_Execute_RTCErr(uchar8 P_Buff)
{
	uchar8 V_ucBuffer[5];
	uchar8 V_Delay_T;
	ushort16 V_uslen, V_usDataEncode;

	Str_RTC_Status.Timer++;
	V_uslen = CLClockFa_Delay_T;
	if(InF_Read_Data(CClockFa_Delay_T, &V_Delay_T, &V_uslen, &V_usDataEncode)!=C_OK)
	{
		V_Delay_T = 0x3C;	/*默认延时60s*/
	}

	V_Delay_T*=2;
	if( P_Buff == C_OK )	/*时钟不故障*/
	{
		if( Str_RTC_Status.HStatus == C_RTC_OK )
		{
			Str_RTC_Status.Timer = 0;
		}
		else
		{
			if( Str_RTC_Status.Timer >= V_Delay_T )
			{
				Str_RTC_Status.Timer = 0;
				Str_RTC_Status.HStatus = C_RTC_OK;
				/*历史状态写数据层*/
				InF_Write_Data(C_Msg_Dispatch, CClock_FaultState, &Str_RTC_Status.HStatus, CLClock_FaultState, C_W_SafeFlag);
			}
		}
	}
	else	/*时钟故障*/
	{
		/*原来故障，直接置故障标志；原来不故障，置故障标志并主动上报*/
		if(Str_RTC_Status.HStatus == C_RTC_ERR)
		{
			Str_RTC_Status.Timer = 0;
		}
		else
		{
			if(Str_RTC_Status.Timer >= V_Delay_T)
			{
				Str_RTC_Status.Timer = 0;
				Str_RTC_Status.HStatus = C_RTC_ERR;
#if  0
				//主动上报*/
				InF_ActiveReportSetting(C_Times_RTCErr);
                Inf_EventReport_HP(C_ClockFaEventNo,C_Happen_EventReport);事件记录模块中处理
#endif
				/*历史状态写数据层*/
				InF_Write_Data(C_Msg_Dispatch,CClock_FaultState,&Str_RTC_Status.HStatus,CLClock_FaultState,C_W_SafeFlag);
			}
		}
	}
	/**********************************************************/
	/*下面更新数据层状态字,每次都刷新:暂时这样做,不在状态变化里做,防止上电后这个标志位一直不管的现象*/
	/*更新数据层时钟故障状态标志：故障或正常；首先从数据层读，刷新后再写*/
	V_uslen = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1, &V_ucBuffer[0], &V_uslen, &V_usDataEncode);
	if(Str_RTC_Status.HStatus == C_RTC_OK)
	{
		V_ucBuffer[1] &= ~C_RTCERR_MeterWorkState;
	}
	else
	{
		V_ucBuffer[1] |= C_RTCERR_MeterWorkState;
	}
	InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State1, &V_ucBuffer[0], CLMeter_Work_State1, C_W_SafeFlag);
}
///*复旦微时钟调校
ushort16 InF_GetRTC_Adjust(void)
{
	return	(RTC->ADJUST&0x00007FFF);
}

void Fill_RTC_RT_TAdc(void)//读取查表adc数据
{
	//根据温度自动判断写入数据的地址
	ushort16 Page;
	uchar8 offset;
	uchar8 Len;
	uchar8 i;

	if( RTC_RT.TempFlag == 0 )//常温查表
	{
		Page = ee_ptatvalue_page;
		offset = ee_ptatvalue_inpage;
		Len = ee_ptatvalue_lenth;

		if(InF_ReadE2ThreeRTC( Page, offset, (uchar8*)RTC_RT.TAdc.PTAT_Value, Len )!=C_OK)
		{
			memset( (uchar8*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//非法则填ff
		}

		return;
	}
	else if( RTC_RT.TempFlag == 1 )//低温查表
	{
		Page = ee_ptatvalue_lt_page;
		offset = ee_ptatvalue_lt_inpage;
		Len = ee_ptatvalue_lt_lenth+2;
	}
	else if( RTC_RT.TempFlag == 2 )//高温查表
	{
		Page = ee_ptatvalue_ht_page;
		offset = ee_ptatvalue_ht_inpage;
		Len = ee_ptatvalue_ht_lenth+2;
	}
	else
	{
		memset( (uchar8*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//非法则填ff
		return;
	}

	InF_ReadE2ThreeRTC( Page, offset, (uchar8*)RTC_RT.TAdc.PTAT_Value, Len );
	if( C_OK == PF_Check_CRC( (uchar8*)RTC_RT.TAdc.PTAT_Value, Len ) )//ee crc正确，填充尾部数据并重新计算crc
	{
		for(i=Len-2;i<ee_ptatvalue_lenth;i=i+2)
		{
			RTC_RT.TAdc.PTAT_Value[i/2] = RTC_RT.TAdc.PTAT_Value[(Len-2)/2 - 1];
		}
		Crc_16Bits_Add2((uchar8*)RTC_RT.TAdc.PTAT_Value, ee_ptatvalue_lenth);
	}
	else				//ee crc错误，数据非法，填充ff
	{
		memset( (uchar8*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//非法则填ff
	}
}

void Fill_RTC_RT_TVal(void)//读取查表补偿值数据
{
	//根据温度自动判断写入数据的地址
	ushort16 Page;
	uchar8 offset;
	uchar8 Len;
	uchar8 i;

	if( RTC_RT.TempFlag == 0 )//常温查表
	{
		Page = ee_trimvalue_page;
		offset = ee_trimvalue_inpage;
		Len = ee_trimvalue_lenth;

		if(C_OK!=InF_ReadE2ThreeRTC( Page, offset, (uchar8*)RTC_RT.TVal.Trim_Value, Len ))
		{
			memset( (uchar8*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//非法则填00
		}

		return;
	}
	else if( RTC_RT.TempFlag == 1 )//低温查表
	{
		Page = ee_trimvalue_lt_page;
		offset = ee_trimvalue_lt_inpage;
		Len = ee_trimvalue_lt_lenth+2;
	}
	else if( RTC_RT.TempFlag == 2 )//高温查表
	{
		Page = ee_trimvalue_ht_page;
		offset = ee_trimvalue_ht_inpage;
		Len = ee_trimvalue_ht_lenth+2;
	}
	else
	{
		memset( (uchar8*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//非法
		return;
	}

	InF_ReadE2ThreeRTC( Page, offset, (uchar8*)RTC_RT.TVal.Trim_Value, Len );
	if( C_OK == PF_Check_CRC( (uchar8*)RTC_RT.TVal.Trim_Value, Len ) )//ee crc正确，填充尾部数据并重新计算crc
	{
		for(i=Len-2;i<ee_ptatvalue_lenth;i=i+2)
		{
			RTC_RT.TVal.Trim_Value[i/2] = RTC_RT.TVal.Trim_Value[(Len-2)/2 - 1];
		}
		Crc_16Bits_Add2((uchar8*)RTC_RT.TVal.Trim_Value, ee_ptatvalue_lenth);
	}
	else				//ee crc错误，数据非法，填充00
	{
		memset( (uchar8*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//非法则填00
	}
}

void Temperpara_Verify(void)	//温度系数校验
{
	temperpara_veri_flag = 0;
	if(Verify_para( ee_temperature_page, ee_temperature_inpage, Tpara.Offset, ee_temperature_lenth ))
	{
		memset( Tpara.Offset, 0x00, ee_temperature_lenth );//默认为0
		Tpara.Offset[0]	= 0x80;
	}
	if( Tpara.RtcTMode == 0xAA )//0xAA常温查表插值模式
	{
		if( PF_Check_CRC( (uchar8 *)RTC_RT.TAdc.PTAT_Value, ee_ptatvalue_lenth+2 ) != C_OK)
		{
			Fill_RTC_RT_TAdc();
		}
		if( PF_Check_CRC( (uchar8*)RTC_RT.TVal.Trim_Value, ee_trimvalue_lenth+2 ) != C_OK )
		{
			Fill_RTC_RT_TVal();
		}
	}
}
short16 Get_RTCTop_Proc( short16 Temp16 )	//顶点调校值折算
{
	short16 i;
	float Rtcadj;

	Rtcadj = Temp16 * 5.0 / 432.0 + Rtcadj_Offset2;		//此处单位均为ppm

	Rtcadj = Rtcadj * 100.0;

	if( Rtcadj >= 0 )
	{
		i = (short16)(Rtcadj + 0.5);
	}
	else
	{
		i = (short16)(Rtcadj - 0.5);
	}
	return i;
}

///************************************************************************///
///*函数原型:uchar8 InF_InitalRTC_Adjust(void)
///*函数功能:初始化RTC温度校验值为全0；
///*输入参数:
///*输出参数：
///*返回参数:
///*调用时机：
///*备注:
///*功能说明：厂内时钟调校用
///************************************************************************///
uchar8 InF_InitalRTC_Adjust(uchar8 V_SafeFlag)
{
	uchar8 V_DataBuff[CLRTC_AdjustTemp]={0};
	uchar8 V_ReturnFlag=C_Error;

	if(C_W_SafeFlag == V_SafeFlag)
	{
		V_ReturnFlag=InF_Write_Data(C_Msg_Dispatch,CRTC_AdjustTemp,&V_DataBuff[0],CLRTC_AdjustTemp,C_W_SafeFlag);
	}

	return	V_ReturnFlag;
}
/*******************************************************************************
功能描述：	编程InfoData数据
输入参数：	*pBuff:		接收数据指针
			addr:		数据地址(InfoFlash内地址)
			len:		数据长度
返回参数：
函数说明：
*******************************************************************************/
void Prog_InfoData(uchar8 *pBuff, ushort16 addr, uchar8 len)
{
//	ushort16	i, bank = addr & (HT_INFO_SIZE-1) & HT_INFO_BANK;
//	uchar8	info[HT_INFO_BANK];												//1页InfoFlash
//
//	addr &= (HT_INFO_BANK-1);
//	for (i=0; i<HT_INFO_BANK; i++)
//	{
//		info[i] = *((uchar8*)(HT_INFO_BASE + bank +i));						//整页读取
//	}
//	for (i=0; i<len; i++)
//	{
//		info[addr + i] = pBuff[i];											//更新数据
//	}
//	//擦除InfoData--------------------------------------------------------------
//	EnWr_WPREG();
//	HT_CMU->FLASHLOCK = 0x7A68;												//unlock flash memory
//	HT_CMU->INFOLOCK  = 0xF998;												//unlock information flash memory
//	HT_CMU->FLASHCON  = 0x02;												//page erase
//	*((ulong32*)(HT_INFO_BASE + bank)) = 0xFFFFFFFF;							//data
//	for(i=0;i<20000;i++)///*最大延时40ms
//	{
//		InF_Delay_2us();
//		if(!(HT_CMU->FLASHCON & CMU_FLASHCON_BUSY))
//		{
//			break;
//		}
//	}
//	if(i>=20000)
//	{
//		return;
//	}
//	HT_CMU->FLASHCON  = 0x00;												//read only
//
//	InF_Delay_us(2000);
//	//更新InfoData--------------------------------------------------------------
//	HT_CMU->FLASHCON  = 0x01;												//word write
//	for (i=0; i<HT_INFO_BANK; i++)
//	{
//		*((uchar8*)(HT_INFO_BASE + bank +i)) = info[i];						//program word
//		while (HT_CMU->FLASHCON  & 0x04)									//FLASH_BSY,只有在厂内会运行，时钟调校
//			;
//	}
//	HT_CMU->FLASHLOCK = ~0x7A68;											//lock flash memory
//	HT_CMU->INFOLOCK  = ~0xF998;											//lock information flash memory
//	HT_CMU->FLASHCON  = 0x00;												//read only
//	DisWr_WPREG();
}
/*******************************************************************************
功能描述：	获取温度原始数据
输入参数：
返回参数：
函数说明：
*******************************************************************************/
//short16 ADC_OrgTemp(void)
//{
//	short16	temp, toff;
//
//	toff = HT_RTC->Toff;
//	temp = HT_TBS->TMPDAT;
//	temp -= toff;
//	return temp;
//}
/*******************************************************************************
功能描述：	RTC误差校准
输入参数：	err:		秒脉冲误差（4字节，BCD码，XXX.XXXs/d，最高位符号位，输入范围-30.0s/d ~ +30.0s/d）
			pInfo:		RTC校准系数（Buffer外调,以减少堆栈需求）
返回参数：
函数说明：
*******************************************************************************/
//static const short16 TAB_Temperature[2][8] =
//{
//	{							//3点校准(HT60xx)
//		22495,	4638,			//-50C,0C
//		-720,	-7862,			//+15C,+35C
//		-13220,	-31077,			//+50C,+100C
//	},
//	{							//4点校准(HT62xx)
//		22495,	4638,			//-50C,0C
//		-720,	-7148,			//+15C,+33C
//		-7862,	-13220,			//+35C,+50C
//		-15005,	-31077,			//+55C,+100C
//	},
//};
uchar8 Sample_Error(uchar8 *err, uchar8 *pInfo)
{
//	uchar8	i, j, num, buff[CLRTC_AdjustTemp];
//	ulong32	chksum,error1=0;
//	long32	ratio[5];														//当前补偿系数
//	long32	error;
//	short16	tps[4];
//	long64	tmp64s;															//中间变量
//	double	FN, tmp;
//	double	add[4];															//修正补偿系数
//  double	TT13, TT23, T13, T23, T123;
//
//	//RTC误差及温度采样---------------------------------------------------------
//	PF_BCDtoHexBytes(&err[0],&error1,3);
//	error = error1;
//	if (err[3] & 0x80)
//	{
//		error = -error1;
//	}
//	if ((error < -30000) || (error > 30000))								//-30.0s/d ~ +30.0s/d
//	{
//		return C_Error;
//	}
//	tps[0] = ADC_OrgTemp();													//当前TpsCode
//	for (i=0; i<TAB_MeterSty_samp; i++)///*三点校正
//	{
//		if ((tps[0] <= TAB_Temperature[TAB_MeterSty_samp-3][i*2+0])
//		&& (tps[0] >= TAB_Temperature[TAB_MeterSty_samp-3][i*2+1]))
//		{
//			break;
//		}
//	}
//	if (i >= TAB_MeterSty_samp)
//	{
//		return C_Error;
//	}
//	j = i;																	//当前采样点
//	num = 1;																//1个有效点
//	//已采样数据收集------------------------------------------------------------
//	i=CLRTC_AdjustTemp;
//	if (C_OK != InF_Read_Data(CRTC_AdjustTemp,&buff[0],&i))						//读取温度采样数据
//	{
//		return C_Error;
//	}
//	for (i=0; i<TAB_MeterSty_samp; i++)
//	{
//		if (i != j)															//不同点
//		{
//			tps[num] = buff[i*2] | buff[i*2+1]<<8;
//			if ((tps[num] <= TAB_Temperature[TAB_MeterSty_samp-3][i*2+0])
//			&& (tps[num] >= TAB_Temperature[TAB_MeterSty_samp-3][i*2+1]))
//			{
//				num++;														//有效点
//			}
//		}
//		else																//同一点
//		{
//			buff[i*2]   = tps[0];
//			buff[i*2+1] = tps[0]>>8;
//		}
//	}
//
//	if (C_OK != InF_Write_Data(C_Msg_Dispatch,CRTC_AdjustTemp,&buff[0],CLRTC_AdjustTemp,C_W_SafeFlag))						//更新温度采样数据
//	{
//		return C_Error;
//	}
//	//读出InfoData--------------------------------------------------------------
//	ratio[0] = HT_RTC->DFAH<<16 | HT_RTC->DFAL;								//RTC曲线系数DFA
//	ratio[1] = HT_RTC->DFBH<<16 | HT_RTC->DFBL;								//RTC曲线系数DFB
//	ratio[2] = HT_RTC->DFCH<<16 | HT_RTC->DFCL;								//RTC曲线系数DFC
//	ratio[3] = HT_RTC->DFDH<<16 | HT_RTC->DFDL;								//RTC曲线系数DFD
//	ratio[4] = HT_RTC->DFEH<<16 | HT_RTC->DFEL;								//RTC曲线系数DFE
//	for (i=0; i<5; i++)
//	{
//		if (ratio[i] & 0x00400000)											//RTC系数为23位有符号数，需转换
//		{
//			ratio[i] |= 0xFF800000;
//		}
//	}
//	//计算公式：DFI = DFA +DFB*(TMPDAT-Toff) +DFC*(TMPDAT-Toff)^2 +DFD*(TMPDAT-Toff)^3 +DFE*(TMPDAT-Toff)^4
//	tmp64s  =  ratio[4];
//	tmp64s *=  tps[0];
//	tmp64s >>= 16;
//
//	tmp64s +=  ratio[3];
//	tmp64s *=  tps[0];
//	tmp64s >>= 16;
//
//	tmp64s +=  ratio[2];
//	tmp64s *=  tps[0];
//	tmp64s >>= 16;
//
//	tmp64s +=  ratio[1];
//	tmp64s *=  tps[0];
//	tmp64s >>= 16;
//
//	tmp64s +=  ratio[0];
//	tmp64s +=  2;
//	tmp64s >>= 2;
//
//	FN  = (double)tmp64s/512.0 +32768;
//	tmp = error / 1000.0;													//转换为double型
//	FN  = FN*tmp/(86400-tmp);												//转换为RTC需要补偿的值
//	//曲线拟合------------------------------------------------------------------
//	if (num == 4)															//4点拟合
//    {
//		T123 = (double)(tps[0]-tps[1]) *(tps[0]-tps[2]) *(tps[0]-tps[3]);
//		T13  = (double)(tps[3]+tps[1]+tps[2]);
//		TT23 = (double)tps[3]*tps[1]*tps[2];
//		TT13 = (double)tps[3]*tps[1] +(double)tps[3]*tps[2] +(double)tps[1]*tps[2];
//
//		add[3] = FN/T123;
//		add[2] = (-FN*T13)/T123;
//		add[1] = (FN*TT13)/T123;
//		add[0] = (-FN*TT23)/T123;
//
//		add[3] = add[3] *128 *16 *65536 *65536 *65536;
//		add[2] = add[2] *128 *16 *65536 *65536;
//		add[1] = add[1] *128 *16 *65536;
//		add[0] = add[0] *128 *16;
//    }
//	else if (num == 3)														//3点拟合
//	{
//		TT13 = (double)(tps[0]+tps[2]) * (tps[0]-tps[2]);					//dTps[0]^2 - dTps[2]^2
//		TT23 = (double)(tps[1]+tps[2]) * (tps[1]-tps[2]);					//dTps[1]^2 - dTps[2]^2
//
//		T13  = (double)(tps[0]-tps[2]);										//dTps[0] - dTps[2]
//		T23  = (double)(tps[1]-tps[2]);										//dTps[0] - dTps[2]
//
//		TT23 *= T13;
//		TT23 /= T23;
//		TT23  = TT13 - TT23;
//
//		add[2] = FN/TT23;													//2次系数修正
//		add[1] = (FN-add[2]*TT13)/T13;										//1次系数修正
//		add[0] = FN -add[2]*tps[0]*tps[0] -add[1]*tps[0];					//0次系数修正
//
//		add[3] = 0;
//		add[2] = add[2] *128 *16 *65536 *65536;
//		add[1] = add[1] *128 *16 *65536;
//		add[0] = add[0] *128 *16;
//	}
//	else if (num == 2)														//2点拟合
//	{
//		T23  = (double)(tps[1]-tps[0]);
//
//		add[1] = -FN/T23;
//		add[0] = -add[1]*tps[1];
//
//		add[3] = 0;
//		add[2] = 0;
//		add[1] = add[1] *128 *16 *65536;
//		add[0] = add[0] *128 *16;
//	}
//	else																	//1点拟合
//	{
//		add[3] = 0;
//		add[2] = 0;
//		add[1] = 0;
//		add[0] = FN*128*16;
//	}
//    ratio[0] += (long32)add[0];												//0次补偿系数
//    ratio[1] += (long32)add[1];												//1次补偿系数
//    ratio[2] += (long32)add[2];												//2次补偿系数
//		ratio[3] += (long32)add[3];												//3次补偿系数
//	//写入InfoData数据----------------------------------------------------------
//	chksum = 0;
//	for (i=0; i<5; i++)
//	{
//		chksum += (ratio[i]>>16) & 0x007F;
//		chksum += ratio[i]       & 0xFFFF;
//	}
//	chksum += HT_RTC->Toff;
//	chksum += HT_RTC->MCON01;
//	chksum += HT_RTC->MCON23;
//	chksum += HT_RTC->MCON45;
//
//	for (i=0; i<5; i++)
//	{
//		pInfo[i*8+0]  = (ratio[i]>>16) & 0x7F;
//		pInfo[i*8+1]  = 0x00;
//		pInfo[i*8+2]  = 0x00;
//		pInfo[i*8+3]  = 0x00;
//		pInfo[i*8+4]  = ratio[i]       & 0xFF;
//		pInfo[i*8+5]  = (ratio[i]>>8)  & 0xFF;
//		pInfo[i*8+6]  = 0x00;
//		pInfo[i*8+7]  = 0x00;
//	}
//	pInfo[40]  = HT_RTC->Toff & 0xFF;
//	pInfo[41]  = (HT_RTC->Toff>>8) & 0xFF;
//	pInfo[42]  = 0x00;
//	pInfo[43]  = 0x00;
//	pInfo[44]  = HT_RTC->MCON01 & 0xFF;
//	pInfo[45]  = (HT_RTC->MCON01>>8) & 0xFF;
//	pInfo[46]  = 0x00;
//	pInfo[47]  = 0x00;
//	pInfo[48]  = HT_RTC->MCON23 & 0xFF;
//	pInfo[49]  = (HT_RTC->MCON23>>8) & 0xFF;
//	pInfo[50]  = 0x00;
//	pInfo[51]  = 0x00;
//	pInfo[52]  = HT_RTC->MCON45 & 0xFF;
//	pInfo[53]  = (HT_RTC->MCON45>>8) & 0xFF;
//	pInfo[54]  = 0x00;
//	pInfo[55]  = 0x00;
//
//	pInfo[56]  = chksum & 0xFF;
//	pInfo[57]  = (chksum>>8) & 0xFF;
//	pInfo[58]  = (chksum>>16) & 0xFF;
//	pInfo[59]  = (chksum>>24) & 0xFF;
//
////	Prog_InfoData(&pInfo[0], 0x0104, 60);

	return C_OK;
}
///************************************************************************///
///*函数原型:uchar8 InF_WriteRTC_Adjust(uchar8 V_SafeFlag,uchar8 * P_data)
///*函数功能:时钟调校；
///*输入参数:
///*输出参数：
///*返回参数:
///*调用时机：
///*备注:
///*功能说明：厂内时钟调校用
///************************************************************************///
//uchar8 InF_WriteRTC_Adjust(uchar8 V_SafeFlag,uchar8 * P_data)
//{//
//	uchar8 V_DataBuff[60];
//	uchar8 V_ReturnFlag=C_Error;

//	if(C_W_SafeFlag != V_SafeFlag)
//	{
//		return V_ReturnFlag;
//	}
//
//	V_ReturnFlag=Sample_Error(P_data, &V_DataBuff[0]);///*获取Info补偿值
//
//	if(C_OK==V_ReturnFlag)
//	{
//		Prog_InfoData(&V_DataBuff[0], 0x0104, 60);
//	}
//	InF_CheckRTC();	///*立即触发时钟补偿
//	return	V_ReturnFlag;
//}

