
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__RTCDrive_H
#define	__RTCDrive_H

#include "Public.h"
#include "IO.h"
#include "Timer.h"


//static ulong32	SV_RTC_SFRBuff;			///*����SFR�Ķ�->�޸�->д*///


//#define	C_RTC_ERR							0x86	///*RTC���ϣ�RTC�����ϱ���*///
//#define	C_RTC_OK							0x00	///*RTC������RTC����δ�ϱ���*///
//#define	C_RTCERR_MeterWorkState				0x80	///*�������������1�е�RTC����λ*///
#define C_RTC_Times							3		///*����3�δ�����Ϊʱ�ӹ��Ϸ���*///
#define C_Day1000				    1000	///*1000�죬ʱ�ӹ����ж�*///

#define C_Const_MCON01					0x2000
#define C_Const_MCON23					0x0588
#define C_Const_MCON45					0x4488
#define C_ReadRTC_Time1ms			500	

typedef struct
{
	uchar8	Timer;				///*������*///
	uchar8	HStatus;			///*��ʷ״̬*///
}Str_RTC_Type;

static Str_RTC_Type Str_RTC_Status;		///*RTC����״̬*///

#define	TAB_MeterSty_samp	3		///*3��У��
#define	EnWr_WPREG()		RTC->RTCWE = 0xACACACAC							//��ر�д�������ܣ��û�����д�����������ļĴ���
#define	DisWr_WPREG()		RTC->RTCWE = 0x00000000	

#define	C_RTC_SlaveAddr_Write		0x64		///*дRTC�Ĵӵ�ַ*///
#define	C_RTC_SlaveAddr_Read		0x65		///*��RTC�Ĵӵ�ַ*///
#define	C_RTC_StartAddr				0x00		///*��/дRTC����ʼ�Ĵ���*///
#define	C_RTC_SFRAddr				0x0D		///*RTC��SFR��ַ����0x0D��ʼ��3���Ĵ���*///
#define	C_RTC_MostSignificantBit	0x80		///*�����Чλ*///
#define C_RTC_Max_StopTimes			20			///*��stopʱ������*///
#define	C_RTC_BitLen				8			///*I2C�������ݵ����ݳ��ȣ�1�ֽ�*///

#define	C_RTC_SFR_D_DATA			0x00		///*D �Ĵ�����ֵ*///
#define	C_RTC_SFR_E_DATA			0x00		///*E �Ĵ�����ֵ*///
#define	C_RTC_SFR_E_VLF				0x02		///*E �Ĵ�����bit1����Ϊ0*///
#define	C_RTC_SFR_F_DATA			0x60		///*F �Ĵ�����ֵ*///

#define C_WeekAddr					3			///*week���ڵ�ַƫ��*///

///*io ���߲����ĺ궨��*///
///*******************************************************************///
#define RTC_Set_Scl_Input		{IO_RTCSCL->IOCFG&=RTCSCL_SELECT;\
								IO_RTCSCL->MODER &= RTCSCL_IN_MODE;\
								IO_RTCSCL->PUPDR |= RTCSCL_NOPUPD;}

#define RTC_Set_Scl_Output		{IO_RTCSCL->IOCFG&=RTCSCL_SELECT;\
								IO_RTCSCL->MODER |= RTCSCL_OUT_MODE;\
								IO_RTCSCL->OTYPER |= RTCSCL_OUTPUT_PP;}
 
#define RTC_Scl_Output_0		{IO_RTCSCL->PTCLR = RTCSCLRESET;}

#define RTC_Scl_Output_1		{IO_RTCSCL->PTSET = RTCSCLSET;}
///*******************************************************************///
#define RTC_IO_Init				{IO_RTCSCL->IOCFG&=RTCSCL_SELECT;\
								IO_RTCSCL->MODER &= RTCSCL_IN_MODE;\
								IO_RTCSCL->PUPDR |= RTCSCL_NOPUPD;\
								IO_RTCSDA->IOCFG &= RTCSDA_SELECT;\
								IO_RTCSDA->MODER &= RTCSDA_IN_MODE;\
								IO_RTCSDA->PUPDR |= RTCSDA_NOPUPD;}

#define RTC_Set_Sda_Input		{IO_RTCSDA->IOCFG &= RTCSDA_SELECT;\
								IO_RTCSDA->MODER &= RTCSDA_IN_MODE;\
								IO_RTCSDA->PUPDR |= RTCSDA_NOPUPD;}

#define RTC_Set_Sda_Output		{IO_RTCSDA->IOCFG&=RTCSDA_SELECT;\
								IO_RTCSDA->MODER |= RTCSDA_OUT_MODE;\
								IO_RTCSDA->OTYPER &= RTCSDA_OUTPUT_OD;}

#define RTC_Sda_Output_0		{IO_RTCSDA->PTCLR = RTCSDARESET;}

#define RTC_Sda_Output_1		{IO_RTCSDA->PTSET = RTCSDASET;}

#define	RTC_Read_Sda			(IO_RTCSDA->IDR & RTCSDASET)
///*******************************************************************///
///*����΢RTC
extern ushort16		Temperature_Adc;///��ǰ�¶�ADCֵ(hex��)
extern float		Rtcadj_Offset;///�¶Ȳ�����Уֵ
extern float		Rtcadj_Offset2;///�¶Ȳ�����Уֵ
extern uchar8		RtcStopProcFlag;///ֹͣ�²���־
extern char8  	Temperature_Hex;///�����¶�(hex��)
extern uchar8		temperpara_veri_flag;///�¶�ϵ��У���־

#define const_mark404		HXVAR( ushort16, 0x1FFFFC0E )	//404���


//�¶�������ز���
//extern const uchar8 RTC_Trim_Ctrl;	//0x55-��������0.119ppm������-��������0.238ppm(��404ģʽ�¿ɿ���0.119)
//extern const uchar8 SleepPtatOffsetCfg;	//0x55-����3Vƫ��(3V��Դptatƫ�ÿ��ƿ���)������-�ر� 
//extern const float const_xtl_top;		//�����¶�����ʹ�õĶ���
//extern const float const_KL;	//�¶Ȳ���ϵ��
//extern const float const_KH;
//extern const float const_TmpsL;	//�¶�ADCб��
//extern const float const_TmpsH;
//extern const uchar8 constF_Volt;		//��ѹ������(������Ӳ��������Ӷ�����),3��ʾ0.03v/10��ʾ0.1v
//extern const ushort16 const_adc_TrimB;
//extern const ushort16 const_adc_TrimT;
//extern const ushort16 const_KHKL_TrimRange;//���������޵����ֽܷ緶Χ��25�ȡ�7����ʹ�ó����޵�ֵkrh��krl����Χ��ʹ�øߵ����޵�ֵkh��kl
//extern const float const_T_OffsetRun;	//оƬ��������-������
//extern const float const_T_OffsetSlp;	//оƬ��������-������
//extern const uchar8 const_TopNoTrim;  //�����x�ȸ��������� 0x55:�������� 0x00:��������
//extern const uchar8 const_TopNTRange;	//���㸽���ر��Զ������¶�adc��Χ����x/5.0379=�¶ȷ�Χ
//extern const float const_T_CL;	//���²�������¶�
//extern const float const_T_CH;		//���²�������¶�
//extern const uchar8 const_C_Mode;		//0x55:�����ߵ��¸߾��Ȳ���ܣ����������������¸߾��Ȳ��
//
//extern const short16 const_TR_LSTART;	//���¼�¼�����¶ȣ�short16�Ŵ�10����
//extern const short16 const_TR_HSTART;	//���¼�¼�����¶ȣ�short16�Ŵ�10����
/////extern const uchar8 const_TR_GAP;//1;//	//��¼�������λ����
/////extern const uchar8 const_TR_Mode;		//0x55:�����¶ȼ�¼���ܣ��������ر�

#endif
