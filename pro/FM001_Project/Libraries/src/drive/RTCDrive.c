

///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     RTCDrive.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   �ⲿʵʱʱ�������ļ�
///*Function List:
///*****************************************************************************************///
///*History1:      ��1���޸�
///*����1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*����2. Date:
///*   	   Author:
///*       Modification:
		///*********************************************************************************///
///*History2:      ��2���޸�
///*����1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*����2. Date:
///*   	   Author:
///*       Modification:
///*****************************************************************************************///


#include "RTCDrive.h"
#include "Communication.h"

/////*����΢RTC
ushort16		Temperature_Adc;//��ǰ�¶�ADCֵ(hex��)
float		Rtcadj_Offset;//�¶Ȳ�����Уֵ
float		Rtcadj_Offset2;//�¶Ȳ�����Уֵ
uchar8	RtcStopProcFlag;//ֹͣ�²���־
char8		Temperature_Hex;//�����¶�(hex��)
uchar8	temperpara_veri_flag;//�¶�ϵ��У���־

//
////�¶�������ز���
//const uchar8 RTC_Trim_Ctrl = 0x55;	//0x55-��������0.119ppm������-��������0.238ppm(��404ģʽ�¿ɿ���0.119)
//const uchar8 SleepPtatOffsetCfg = 0x55;	//0x55-����3Vƫ��(3V��Դptatƫ�ÿ��ƿ���)������-�ر�
//const float const_xtl_top	= 25.0;		//�����¶�����ʹ�õĶ���
//const float const_KL	= 0.0300;	//�¶Ȳ���ϵ��
//const float const_KH	= 0.0382;
//const float const_TmpsL	= 5.0379;	//�¶�ADCб��
//const float const_TmpsH	= 5.0379;
//const uchar8 constF_Volt	= 0;		//��ѹ������(������Ӳ��������Ӷ�����),3��ʾ0.03v/10��ʾ0.1v
//const ushort16 const_adc_TrimB = 0x3ff;
//const ushort16 const_adc_TrimT = 0x640;
//const ushort16 const_KHKL_TrimRange = 36;//���������޵����ֽܷ緶Χ��25�ȡ�7����ʹ�ó����޵�ֵkrh��krl����Χ��ʹ�øߵ����޵�ֵkh��kl
//const float const_T_OffsetRun	= -3.0;	//оƬ��������-������
//const float const_T_OffsetSlp	= -2.0;	//оƬ��������-������
//const uchar8 const_TopNoTrim = 0x55;  //�����x�ȸ��������� 0x55:�������� 0x00:��������
//const uchar8 const_TopNTRange = 8;	//���㸽���ر��Զ������¶�adc��Χ����x/5.0379=�¶ȷ�Χ
//const float const_T_CL	= -23.0;	//���²�������¶�
//const float const_T_CH	= 62.0;		//���²�������¶�
//const uchar8 const_C_Mode = 0x55;		//0x55:�����ߵ��¸߾��Ȳ���ܣ����������������¸߾��Ȳ��
//
//const short16 const_TR_LSTART	= -15*10;	//���¼�¼�����¶ȣ�short16�Ŵ�10����
//const short16 const_TR_HSTART	= 50*10;	//���¼�¼�����¶ȣ�short16�Ŵ�10����
/////const uchar8 const_TR_GAP		= 6;//1;//	//��¼�������λ����
/////const uchar8 const_TR_Mode 	= 0x55;		//0x55:�����¶ȼ�¼���ܣ��������ر�



///*�ײ���������											*///
///*���еĵײ���������ʹ��static���壬ֻ���ڸ�.c������á�	*///

///***********************************************************************************///
///*Function���жϼĴ���ֵ�Ƿ�Ϊ����ֵ���粻��������Ϊ����ֵ
///*Description��
///*Input��ulong32 *RegAddr����Ĵ�����ַ��ulong32 Value���Ĵ�������ֵ��
///*Output��
///*Return��C_OK:�Ĵ���ֵΪ����ֵ;C_Error���Ĵ���ֵ������ֵ
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
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
///*Function����RTCYYMMDDWWhhmmss��ȡ��ָ����ַ
///*Description��
///*Input��*p��ָ���������׵�ַ(ָ��ss)��Len�����ȣ��̶�Ϊ7��ʹ�ú궨��
///*Output��7�ֽڵ�����ʱ��
///*Return��C_OK:��ȡ�ɹ�;C_TIMEERR:������ʱ��Ƿ�
///*Calls��
///*Called By��������ÿ500ms��ȡһ��
///*Influence��
	///*1�����������ݲ��ж��Ƿ���ȷ��*///
	///*2����ȡ�ɹ����ˢ�����ָ��ָ���������*///
	///*3���ڶ�ʱ�Ӻ������棬������s/m/h/d/m/y�仯���ж��봦��                                                    *///
///*Tips��
///*Others��
///***********************************************************************************///
uchar8 InF_ReadRTC(uchar8 *P_Time,uchar8 Len)
{
	uchar8	i,j;
	uchar8 BufA[C_RTCLen];

	if(Len != C_RTCLen)		///*���ⲿRTC���̶����ȣ�7�ֽڵ�YYMMDDWWhhmmss*///
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

		for(i=0;i<7;i++) //�ȶ�����ʱ���Ƿ�һ��
		{
			if( BufA[i] != P_Time[i] )
			{
				break;
			}
		}

		if( i == 7 ) //����һ��, ��ʾ��ȡ�ɹ�
		{
			if((PF_DataTimeActive(P_Time,C_DT_Start_ss,3)==C_OK)&&(PF_DataTimeActive(P_Time+4,C_DT_Start_DD,3)==C_OK))
			{///*�ж�ssmmhh��DDMMYY�ĺϷ���*///
				return C_OK;
			}
		}
	}
	return C_TIMEERR;
}
///***********************************************************************************///
///*Function��������ʱ��д��RTC
///*Description��
///*Input��
	///**P_Timeָ��Ҫд������ʱ��Ļ������׵�ַ(ss)�����ݸ�ʽΪYYMMDDWWhhmmss	         *///
	///*Len���̶�Ϊ7���ú궨���ʾ����Ϊ�漰��ָ�룬����ʹ�ø���ڲ���������ȫ��ǡ� *///
///*Output��
///*Return��C_Ok��д�ɹ���C_IICError��I2c���ϣ�д���ɹ�
///*Calls��
///*Called By��
///*Influence��
	///*1��д�����ݲ��ж������������ܴΡ�����д��ʱ���롣                                                		*///
///*Tips��
///*Others��
///***********************************************************************************///
uchar8 InF_WriteRTC(uchar8 *P_Time,uchar8 Len)
{
	uchar8 V_TimeBuff[C_RTCLen],i;
	uchar8 V_TimeBuffCopy[C_RTCLen],V_ReturnFlag,j;

	PF_CopyDataBytes(P_Time,&V_TimeBuff[0],C_RTCLen);	///*��7�ֽ�ʱ�����ڿ���:�˴�������ڴ������ĳ���*///

	if( Len != C_RTCLen )		///*дRTC���̶����ȣ�7�ֽڵ�YYMMDDWWhhmmss*///
	{
		return C_DataLenError;
	}
	else
	{
		for( i=0; i<3; i++ )
		{
			EnWr_WPREG();///*�Ĵ���дʹ��

			RTC->BCDSEC 	= V_TimeBuff[0];
			RTC->BCDMIN 	= V_TimeBuff[1];
			RTC->BCDHOUR	= V_TimeBuff[2];
			RTC->BCDWEEK	= V_TimeBuff[3];
			RTC->BCDDATE	= V_TimeBuff[4];
			RTC->BCDMONTH	= V_TimeBuff[5];
			RTC->BCDYEAR	= V_TimeBuff[6];

			DisWr_WPREG();///*��ֹд

			V_ReturnFlag = InF_ReadRTC( &V_TimeBuffCopy[0],C_RTCLen);
			if(V_ReturnFlag == C_OK) //��ȡ�ɹ�
			{
				for(j=0;j<7;j++)
				{
					if(V_TimeBuff[j]!=V_TimeBuffCopy[j])
					{
						break;
					}
				}

				if(j==7) //��ǰֵ������ֵ���, ���óɹ�
				{
					return C_OK; //���óɹ�
				}
			}
		}
		return C_TIMEERR; //����ʧ��
	}
}
///***********************************************************************************///
///*Function����ʼ��RTC������á�
///*Description��
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence��
///*Tips��
	///*1���ϵ��ʼ������һ�Ρ�*///
///*Others��
///***********************************************************************************///
void InF_InitalRTC(void)
{
	if((RCC->PERCLKCON1&RCC_PERRCCCON1_RTCRCCEN_ON)!=RCC_PERRCCCON1_RTCRCCEN_ON)
	{
		RCC->PERCLKCON1|=RCC_PERRCCCON1_RTCRCCEN_ON;///*
	}
	if(RTC->RTCIE!=0)
	{
		RTC->RTCIE	&=	0xFFFFE000;		///*RTC�ж�ʹ�ܽ�ֹ.
	}
	if(RTC->RTCIF!=0)
	{
		RTC->RTCIF |= 0x00001FFF; 	///*���жϱ�־
	}
	RTC->FSEL = RTC_FSEL_FSEL_PLL1HZ;	///*Tout�����Ƶ����1hz

	///*TOUT����ڲ���
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

//	if((ANAC->FDETIF&0x00000040)==0x00000040)///*XTLF ͣ����,��ֹ��check������
//	{
//		ANAC->XTLFIPW=RCC_XTLFIPW_250NA;
//	}
//	RCC->PLLCON=(RCC_PLLCON_PLLDB32768|RCC_PLLCON_PLLOSEL0|RCC_PLLCON_PLLINSEL_XTLF);
//	RCC->PLLCON|=RCC_PLLCON_PLLEN_ON;
}

///***********************************************************************************///
///*Function���ж�RTC��SFR�Ƿ���ȷ
///*Description��
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence��1������SFR�Ƿ���ȷ�������׼ȷ��д����ȷֵ��
///*Tips��
	///*1���ϵ��ʼ������һ�Ρ�*///
	///*2��ÿ���ӵ���һ�Ρ�    *///
///*Others��
///***********************************************************************************///
//static const struct
//{
//	ushort16	DFAH;							///*ϵ��A, �������λ
//	ushort16	DFAL;							///*ϵ��A, �������λ
//	ushort16	DFBH;							///*ϵ��B, һ�����λ
//	ushort16	DFBL;							///*ϵ��B, һ�����λ
//	ushort16	DFCH;							///*ϵ��C, �������λ
//	ushort16	DFCL;							///*ϵ��C, �������λ
//	ushort16	DFDH;							///*ϵ��D, �������λ
//	ushort16	DFDL;							///*ϵ��D, �������λ
//	ushort16	DFEH;							///*ϵ��E, �Ĵ����λ
//	ushort16	DFEL;							///*ϵ��E, �Ĵ����λ
//	ushort16	Toff;							///*�¶�ƫ��ϵ��
//	ushort16	MCON01;						///*����ϵ��01
//	ushort16	MCON23;						///*����ϵ��23
//	ushort16	MCON45;						///*����ϵ��45
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

	if((ANAC->FDETIF&0x00000040)==0x00000040)///*XTLF ͣ����,δͣ��
	{
		if(RCC->XTLFIPW!=RCC_XTLFIPW_250NA)
		{
			RCC->XTLFIPW=RCC_XTLFIPW_250NA;
		}
		if(RCC->PLLCON!=(RCC_PLLCON_PLLDB32768|RCC_PLLCON_PLLOSEL0|RCC_PLLCON_PLLINSEL_XTLF|RCC_PLLCON_PLLEN_ON))
		{
			RCC->PLLCON=(RCC_PLLCON_PLLDB32768|RCC_PLLCON_PLLOSEL0|RCC_PLLCON_PLLINSEL_XTLF|RCC_PLLCON_PLLEN_ON);
			RCC->PLLCON|=RCC_PLLCON_PLLEN_ON;
			InF_Delay_us(4000);///*��ʱ
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
	///*����΢�¶Ȳ���ϵ��У��
	Temperpara_Verify();	//�¶�ϵ��У��
}

/************************************************************************
*��������:�ϵ�ʱ�������ݲ����ʱ����ʷ״̬,�����������״̬���е�ʱ�ӹ���״̬
*�������:��
*�������:ʱ����ʷ״̬/�������״̬��1
*���ز���:��
*����ʱ����
************************************************************************/
void SF_InitRTCState(void)
{
	uchar8 V_ucBuffer[5];
	ushort16 V_uslen, V_usDataEncode;

	Str_RTC_Status.Timer = 0;
	/*�����ݲ������ص���ʷ״̬*/
	V_uslen = CLClock_FaultState;
	if( InF_Read_Data(CClock_FaultState, &Str_RTC_Status.HStatus, &V_uslen, &V_usDataEncode) != C_OK )
	{
		Str_RTC_Status.HStatus = C_RTC_OK;
	}
	/*�������ݲ�ʱ�ӹ���״̬��־�����ϻ����������ȴ����ݲ����ˢ�º���д*/
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
*����ԭ��:void InF_ExecuteClr_RTC(void)
*��������:�������ʱ������ʱ�ӹ��ϱ�־�Ĵ���
*�������:
*���������
*���ز���:��
*����ʱ����
*��ע:
*����˵����
************************************************************************/
void InF_ExecuteClr_RTC(void)
{
	uchar8 V_ucBuffer[5];
	ushort16 V_uslen, V_usDataEncode;

	Str_RTC_Status.HStatus = C_RTC_OK;
	Str_RTC_Status.Timer = 0;

	/*�������ʷ״̬(ʱ������)д���ݲ�*/
	InF_Write_Data(C_Msg_Dispatch, CClock_FaultState, &Str_RTC_Status.HStatus, CLClock_FaultState, C_W_SafeFlag);

	/*�������ݲ�RTC����״̬��־�����ϻ����������ȴ����ݲ����ˢ�º���д*/
	V_uslen = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1, &V_ucBuffer[0], &V_uslen, &V_usDataEncode);

	V_ucBuffer[1] &= ~C_RTCERR_MeterWorkState;

	InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State1, &V_ucBuffer[0], CLMeter_Work_State1, C_W_SafeFlag);
}
/*******************************************************************************
����ԭ�ͣ�void SF_SetRTCErrState(uchar8 V_ucRTCFlag)
������������ʱ�ӹ���״̬λ���������״̬��1 bit15
���������V_ucRTCFlag RTC��״̬
         RTC��״̬����λ������λ C_RTC_ERR����λ��C_RTC_OK ��λ
�����������
���ز�������
����λ�ã����ȴ����ݲ����ˢ�º���д
��    ע�����������õ������״̬�� ��дʱ�ӹ�������״̬
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
///*����ԭ��:uchar8 SF_BackTimeIllegal(uchar8 V_ucBackTimeLegitFlag)           *///
///*��������:���籸��ʱ��Ƿ������ݲ����������ʱ��ָ�Ϊ2000��1��1�� ����״̬��*///
///*�������:*pData��ʱ�䣬6�ֽڣ�������ʱ���� ;                               *///
///*�������:*pData���ָ���ʱ�䣬2000��1��1��00��00��00                        *///
///*���ز���:��                                                                *///
///*����ʱ����                                                                 *///
///*��ע:                                                                      *///
///*****************************************************************************///
void SF_BackTimeIllegal(uchar8 *pData)
{
	memset(pData,0,CLTime);//00��00��00
    memset(&pData[CLTime],0x01,CLMonthAndDay);//1��1��
	pData[CLTime+CLMonthAndDay]=0xd0;//2000��
	pData[CLTime+CLMonthAndDay+1]=0x07;//2000��
	SF_SetRTCErrState(C_RTC_ERR);
}

/****************************************************************************
*����ԭ��:uchar8 SF_RTCErrJudgeAndDeal(uchar8 *pData)
*��������:ʱ�ӹ����жϼ���Ҫ�ָ���ʱ�丳ֵ
*�������:*pData��ʱ�䣬6�ֽڣ�������ʱ����
*�������:*pData�������Ҫ�ָ�ʱ�䣬��ֵ�ָ����ʱ�䣻�������Ҫ��ֵΪԭʱ��
*���ز���:�Ƿ�����ʱ�ӹ���,C_RTC_OKδ�������ϣ�C_RTC_ERR��������
*����ʱ����500ms
*��ע:���������õ������״̬��
*****************************************************************************/
uchar8 SF_RTCErrJudgeAndDeal(uchar8 *pData)
{
	uchar8 V_ucBuffer[CLDate_Time];
	uchar8 V_ucResult_RTCActive = C_OK, V_ucReturn = C_RTC_ERR;
	ushort16 V_usDataLenth, V_usDataEncode;
    ulong32 V_ulSubDays = 0;

	V_ucResult_RTCActive = PF_DataTimeActive_698(pData, C_DT_Start_ss, CLBackTime_OneSec);	/*RTC�Ϸ���*/

	V_usDataLenth = CLBackTime_OneSec;
	if(InF_Read_Data(CBackTime_OneSec, V_ucBuffer, &V_usDataLenth, &V_usDataEncode) == C_OK)
	{
		if(PF_DataTimeActive_698(V_ucBuffer, C_DT_Start_ss, CLBackTime_OneSec) == C_OK)		/*����ʱ��Ϸ���*/
		{
			if(V_ucResult_RTCActive == C_OK)
			{
			    if(PF_TimeSub_Day_698(pData, V_ucBuffer, &V_ulSubDays) == C_LessThan)			/*����*/
			    {
			        PF_CopyDataBytes(V_ucBuffer, pData, CLBackTime_OneSec); 			/*����ʱ��ָ�RTC*/
		            SF_SetRTCErrState(C_RTC_ERR);
					V_ucReturn = C_RTC_ERR;
			    }
			    else
			    {
				    if(V_ulSubDays > C_Day1000)
				    {
                        PF_CopyDataBytes(V_ucBuffer, pData, CLBackTime_OneSec); 		/*����ʱ��ָ�RTC*/
					    SF_SetRTCErrState(C_RTC_ERR);									/*ֻ��״̬�����ָ�ʱ�䣬�����Уʱ���ָ�*/
					    V_ucReturn = C_RTC_ERR;
				    }
				    else
				    {
					    V_ucReturn = C_RTC_OK;
				    }
			    }
			}
			else 														/*����Ϸ���RTC�Ƿ�*/
			{
			    PF_CopyDataBytes(V_ucBuffer,pData, CLBackTime_OneSec);	/*����ʱ��ָ�RTC*/
		        SF_SetRTCErrState(C_RTC_ERR);
				V_ucReturn = C_RTC_ERR;
			}
		}
		else															/*����Ƿ�*/
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
		else															/*����ʱ���RTC���Ƿ���ʱ��ָ�Ϊ2000��1��1�գ�00��00��00*/
		{
		   SF_BackTimeIllegal(pData);
	       V_ucReturn = C_RTC_ERR_BackTime;
		}
	}
    return  V_ucReturn;
}

/************************************************************************
*����ԭ��:void InF_Execute_RTCErr(uchar8 P_Buff)
*��������:����ʱ�ӹ��ϱ�־
*�������:��ǰ����ʱ�ӳɹ���ʧ�ܱ�־��C_OK��C_Error
*�������������ǰ����ʱ�ӳɹ�/ʧ�ܱ�־ˢ�����ݲ㣬���ݴ˽��������ϱ�
*���ز���:��
*����ʱ����
*��ע:
*����˵����
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
		V_Delay_T = 0x3C;	/*Ĭ����ʱ60s*/
	}

	V_Delay_T*=2;
	if( P_Buff == C_OK )	/*ʱ�Ӳ�����*/
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
				/*��ʷ״̬д���ݲ�*/
				InF_Write_Data(C_Msg_Dispatch, CClock_FaultState, &Str_RTC_Status.HStatus, CLClock_FaultState, C_W_SafeFlag);
			}
		}
	}
	else	/*ʱ�ӹ���*/
	{
		/*ԭ�����ϣ�ֱ���ù��ϱ�־��ԭ�������ϣ��ù��ϱ�־�������ϱ�*/
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
				//�����ϱ�*/
				InF_ActiveReportSetting(C_Times_RTCErr);
                Inf_EventReport_HP(C_ClockFaEventNo,C_Happen_EventReport);�¼���¼ģ���д���
#endif
				/*��ʷ״̬д���ݲ�*/
				InF_Write_Data(C_Msg_Dispatch,CClock_FaultState,&Str_RTC_Status.HStatus,CLClock_FaultState,C_W_SafeFlag);
			}
		}
	}
	/**********************************************************/
	/*����������ݲ�״̬��,ÿ�ζ�ˢ��:��ʱ������,����״̬�仯����,��ֹ�ϵ�������־λһֱ���ܵ�����*/
	/*�������ݲ�ʱ�ӹ���״̬��־�����ϻ����������ȴ����ݲ����ˢ�º���д*/
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
///*����΢ʱ�ӵ�У
ushort16 InF_GetRTC_Adjust(void)
{
	return	(RTC->ADJUST&0x00007FFF);
}

void Fill_RTC_RT_TAdc(void)//��ȡ���adc����
{
	//�����¶��Զ��ж�д�����ݵĵ�ַ
	ushort16 Page;
	uchar8 offset;
	uchar8 Len;
	uchar8 i;

	if( RTC_RT.TempFlag == 0 )//���²��
	{
		Page = ee_ptatvalue_page;
		offset = ee_ptatvalue_inpage;
		Len = ee_ptatvalue_lenth;

		if(InF_ReadE2ThreeRTC( Page, offset, (uchar8*)RTC_RT.TAdc.PTAT_Value, Len )!=C_OK)
		{
			memset( (uchar8*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//�Ƿ�����ff
		}

		return;
	}
	else if( RTC_RT.TempFlag == 1 )//���²��
	{
		Page = ee_ptatvalue_lt_page;
		offset = ee_ptatvalue_lt_inpage;
		Len = ee_ptatvalue_lt_lenth+2;
	}
	else if( RTC_RT.TempFlag == 2 )//���²��
	{
		Page = ee_ptatvalue_ht_page;
		offset = ee_ptatvalue_ht_inpage;
		Len = ee_ptatvalue_ht_lenth+2;
	}
	else
	{
		memset( (uchar8*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//�Ƿ�����ff
		return;
	}

	InF_ReadE2ThreeRTC( Page, offset, (uchar8*)RTC_RT.TAdc.PTAT_Value, Len );
	if( C_OK == PF_Check_CRC( (uchar8*)RTC_RT.TAdc.PTAT_Value, Len ) )//ee crc��ȷ�����β�����ݲ����¼���crc
	{
		for(i=Len-2;i<ee_ptatvalue_lenth;i=i+2)
		{
			RTC_RT.TAdc.PTAT_Value[i/2] = RTC_RT.TAdc.PTAT_Value[(Len-2)/2 - 1];
		}
		Crc_16Bits_Add2((uchar8*)RTC_RT.TAdc.PTAT_Value, ee_ptatvalue_lenth);
	}
	else				//ee crc�������ݷǷ������ff
	{
		memset( (uchar8*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//�Ƿ�����ff
	}
}

void Fill_RTC_RT_TVal(void)//��ȡ�����ֵ����
{
	//�����¶��Զ��ж�д�����ݵĵ�ַ
	ushort16 Page;
	uchar8 offset;
	uchar8 Len;
	uchar8 i;

	if( RTC_RT.TempFlag == 0 )//���²��
	{
		Page = ee_trimvalue_page;
		offset = ee_trimvalue_inpage;
		Len = ee_trimvalue_lenth;

		if(C_OK!=InF_ReadE2ThreeRTC( Page, offset, (uchar8*)RTC_RT.TVal.Trim_Value, Len ))
		{
			memset( (uchar8*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//�Ƿ�����00
		}

		return;
	}
	else if( RTC_RT.TempFlag == 1 )//���²��
	{
		Page = ee_trimvalue_lt_page;
		offset = ee_trimvalue_lt_inpage;
		Len = ee_trimvalue_lt_lenth+2;
	}
	else if( RTC_RT.TempFlag == 2 )//���²��
	{
		Page = ee_trimvalue_ht_page;
		offset = ee_trimvalue_ht_inpage;
		Len = ee_trimvalue_ht_lenth+2;
	}
	else
	{
		memset( (uchar8*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//�Ƿ�
		return;
	}

	InF_ReadE2ThreeRTC( Page, offset, (uchar8*)RTC_RT.TVal.Trim_Value, Len );
	if( C_OK == PF_Check_CRC( (uchar8*)RTC_RT.TVal.Trim_Value, Len ) )//ee crc��ȷ�����β�����ݲ����¼���crc
	{
		for(i=Len-2;i<ee_ptatvalue_lenth;i=i+2)
		{
			RTC_RT.TVal.Trim_Value[i/2] = RTC_RT.TVal.Trim_Value[(Len-2)/2 - 1];
		}
		Crc_16Bits_Add2((uchar8*)RTC_RT.TVal.Trim_Value, ee_ptatvalue_lenth);
	}
	else				//ee crc�������ݷǷ������00
	{
		memset( (uchar8*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//�Ƿ�����00
	}
}

void Temperpara_Verify(void)	//�¶�ϵ��У��
{
	temperpara_veri_flag = 0;
	if(Verify_para( ee_temperature_page, ee_temperature_inpage, Tpara.Offset, ee_temperature_lenth ))
	{
		memset( Tpara.Offset, 0x00, ee_temperature_lenth );//Ĭ��Ϊ0
		Tpara.Offset[0]	= 0x80;
	}
	if( Tpara.RtcTMode == 0xAA )//0xAA���²���ֵģʽ
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
short16 Get_RTCTop_Proc( short16 Temp16 )	//�����Уֵ����
{
	short16 i;
	float Rtcadj;

	Rtcadj = Temp16 * 5.0 / 432.0 + Rtcadj_Offset2;		//�˴���λ��Ϊppm

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
///*����ԭ��:uchar8 InF_InitalRTC_Adjust(void)
///*��������:��ʼ��RTC�¶�У��ֵΪȫ0��
///*�������:
///*���������
///*���ز���:
///*����ʱ����
///*��ע:
///*����˵��������ʱ�ӵ�У��
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
����������	���InfoData����
���������	*pBuff:		��������ָ��
			addr:		���ݵ�ַ(InfoFlash�ڵ�ַ)
			len:		���ݳ���
���ز�����
����˵����
*******************************************************************************/
void Prog_InfoData(uchar8 *pBuff, ushort16 addr, uchar8 len)
{
//	ushort16	i, bank = addr & (HT_INFO_SIZE-1) & HT_INFO_BANK;
//	uchar8	info[HT_INFO_BANK];												//1ҳInfoFlash
//
//	addr &= (HT_INFO_BANK-1);
//	for (i=0; i<HT_INFO_BANK; i++)
//	{
//		info[i] = *((uchar8*)(HT_INFO_BASE + bank +i));						//��ҳ��ȡ
//	}
//	for (i=0; i<len; i++)
//	{
//		info[addr + i] = pBuff[i];											//��������
//	}
//	//����InfoData--------------------------------------------------------------
//	EnWr_WPREG();
//	HT_CMU->FLASHLOCK = 0x7A68;												//unlock flash memory
//	HT_CMU->INFOLOCK  = 0xF998;												//unlock information flash memory
//	HT_CMU->FLASHCON  = 0x02;												//page erase
//	*((ulong32*)(HT_INFO_BASE + bank)) = 0xFFFFFFFF;							//data
//	for(i=0;i<20000;i++)///*�����ʱ40ms
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
//	//����InfoData--------------------------------------------------------------
//	HT_CMU->FLASHCON  = 0x01;												//word write
//	for (i=0; i<HT_INFO_BANK; i++)
//	{
//		*((uchar8*)(HT_INFO_BASE + bank +i)) = info[i];						//program word
//		while (HT_CMU->FLASHCON  & 0x04)									//FLASH_BSY,ֻ���ڳ��ڻ����У�ʱ�ӵ�У
//			;
//	}
//	HT_CMU->FLASHLOCK = ~0x7A68;											//lock flash memory
//	HT_CMU->INFOLOCK  = ~0xF998;											//lock information flash memory
//	HT_CMU->FLASHCON  = 0x00;												//read only
//	DisWr_WPREG();
}
/*******************************************************************************
����������	��ȡ�¶�ԭʼ����
���������
���ز�����
����˵����
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
����������	RTC���У׼
���������	err:		��������4�ֽڣ�BCD�룬XXX.XXXs/d�����λ����λ�����뷶Χ-30.0s/d ~ +30.0s/d��
			pInfo:		RTCУ׼ϵ����Buffer���,�Լ��ٶ�ջ����
���ز�����
����˵����
*******************************************************************************/
//static const short16 TAB_Temperature[2][8] =
//{
//	{							//3��У׼(HT60xx)
//		22495,	4638,			//-50C,0C
//		-720,	-7862,			//+15C,+35C
//		-13220,	-31077,			//+50C,+100C
//	},
//	{							//4��У׼(HT62xx)
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
//	long32	ratio[5];														//��ǰ����ϵ��
//	long32	error;
//	short16	tps[4];
//	long64	tmp64s;															//�м����
//	double	FN, tmp;
//	double	add[4];															//��������ϵ��
//  double	TT13, TT23, T13, T23, T123;
//
//	//RTC���¶Ȳ���---------------------------------------------------------
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
//	tps[0] = ADC_OrgTemp();													//��ǰTpsCode
//	for (i=0; i<TAB_MeterSty_samp; i++)///*����У��
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
//	j = i;																	//��ǰ������
//	num = 1;																//1����Ч��
//	//�Ѳ��������ռ�------------------------------------------------------------
//	i=CLRTC_AdjustTemp;
//	if (C_OK != InF_Read_Data(CRTC_AdjustTemp,&buff[0],&i))						//��ȡ�¶Ȳ�������
//	{
//		return C_Error;
//	}
//	for (i=0; i<TAB_MeterSty_samp; i++)
//	{
//		if (i != j)															//��ͬ��
//		{
//			tps[num] = buff[i*2] | buff[i*2+1]<<8;
//			if ((tps[num] <= TAB_Temperature[TAB_MeterSty_samp-3][i*2+0])
//			&& (tps[num] >= TAB_Temperature[TAB_MeterSty_samp-3][i*2+1]))
//			{
//				num++;														//��Ч��
//			}
//		}
//		else																//ͬһ��
//		{
//			buff[i*2]   = tps[0];
//			buff[i*2+1] = tps[0]>>8;
//		}
//	}
//
//	if (C_OK != InF_Write_Data(C_Msg_Dispatch,CRTC_AdjustTemp,&buff[0],CLRTC_AdjustTemp,C_W_SafeFlag))						//�����¶Ȳ�������
//	{
//		return C_Error;
//	}
//	//����InfoData--------------------------------------------------------------
//	ratio[0] = HT_RTC->DFAH<<16 | HT_RTC->DFAL;								//RTC����ϵ��DFA
//	ratio[1] = HT_RTC->DFBH<<16 | HT_RTC->DFBL;								//RTC����ϵ��DFB
//	ratio[2] = HT_RTC->DFCH<<16 | HT_RTC->DFCL;								//RTC����ϵ��DFC
//	ratio[3] = HT_RTC->DFDH<<16 | HT_RTC->DFDL;								//RTC����ϵ��DFD
//	ratio[4] = HT_RTC->DFEH<<16 | HT_RTC->DFEL;								//RTC����ϵ��DFE
//	for (i=0; i<5; i++)
//	{
//		if (ratio[i] & 0x00400000)											//RTCϵ��Ϊ23λ�з���������ת��
//		{
//			ratio[i] |= 0xFF800000;
//		}
//	}
//	//���㹫ʽ��DFI = DFA +DFB*(TMPDAT-Toff) +DFC*(TMPDAT-Toff)^2 +DFD*(TMPDAT-Toff)^3 +DFE*(TMPDAT-Toff)^4
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
//	tmp = error / 1000.0;													//ת��Ϊdouble��
//	FN  = FN*tmp/(86400-tmp);												//ת��ΪRTC��Ҫ������ֵ
//	//�������------------------------------------------------------------------
//	if (num == 4)															//4�����
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
//	else if (num == 3)														//3�����
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
//		add[2] = FN/TT23;													//2��ϵ������
//		add[1] = (FN-add[2]*TT13)/T13;										//1��ϵ������
//		add[0] = FN -add[2]*tps[0]*tps[0] -add[1]*tps[0];					//0��ϵ������
//
//		add[3] = 0;
//		add[2] = add[2] *128 *16 *65536 *65536;
//		add[1] = add[1] *128 *16 *65536;
//		add[0] = add[0] *128 *16;
//	}
//	else if (num == 2)														//2�����
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
//	else																	//1�����
//	{
//		add[3] = 0;
//		add[2] = 0;
//		add[1] = 0;
//		add[0] = FN*128*16;
//	}
//    ratio[0] += (long32)add[0];												//0�β���ϵ��
//    ratio[1] += (long32)add[1];												//1�β���ϵ��
//    ratio[2] += (long32)add[2];												//2�β���ϵ��
//		ratio[3] += (long32)add[3];												//3�β���ϵ��
//	//д��InfoData����----------------------------------------------------------
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
///*����ԭ��:uchar8 InF_WriteRTC_Adjust(uchar8 V_SafeFlag,uchar8 * P_data)
///*��������:ʱ�ӵ�У��
///*�������:
///*���������
///*���ز���:
///*����ʱ����
///*��ע:
///*����˵��������ʱ�ӵ�У��
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
//	V_ReturnFlag=Sample_Error(P_data, &V_DataBuff[0]);///*��ȡInfo����ֵ
//
//	if(C_OK==V_ReturnFlag)
//	{
//		Prog_InfoData(&V_DataBuff[0], 0x0104, 60);
//	}
//	InF_CheckRTC();	///*��������ʱ�Ӳ���
//	return	V_ReturnFlag;
//}

