
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     Timer.h
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef __TIMER_H
#define __TIMER_H

#include "Public.h"
#include "Dispatch.h"

//LPTIM:system base time  (power off)
//ETIM2: system base time  (power on)
//TIM7: infra wakeup      (power off)
//TIM6: calibrate timer   (����У׼RC)
//ETIM1: card baud rate timer(���ڿ�ͨ��:��ʱ�Ŀ���)
//ETIM3: ����RCHFʱ��У׼

//#define C_WatchDog_Feed				200						///*1s����ÿ5msι��һ��*///
#define C_WatchDog_Feed				2400					///*12s����ÿ5msι��һ��:����12s����ι��*///
#define C_WatchDog_FeedOut			3000					///*����15s��ι��*///

///*���ⷢ��38KHz�����ź�ʹ��TIMER11��PWM�������*///
///*������16MHz��Ƶ������*///
#define	InfraTimer					TIM11					///*timer11 use as 38KHz of infra *///
#define	C_InfraTimerCounter			0xd3					///*��������ź��Զ���װ��ֵ*///
#define	C_InfraTimerCounter_Wakeup	0x1c					///*�͹��Ļ��Ѻ��������ź��Զ���װ��ֵ*///

#define C_TimerStatus_OVIF_RESET		((ulong32)0x00000001)		///*���������־λ*///
#define C_TimerStatus_CAPIF_RESET		((ulong32)0x00000002)		///*���������־λ*///
#define C_TimerStatus_UIF_RESET		((ulong32)0xfffe)		///*���������־λ*///
#define C_TimerStatus_BIF_RESET		((ushort16)0xff7f)
#define C_TimerStatus_TIF_RESET		((ushort16)0xffbf)
#define C_TimerStatus_CCIF_RESET	((ushort16)0xffe1)
#define C_TimerStatus_RESET			((ulong32)0x0000000f)

#define C_TimerCounter_EN			((ulong32)0x00000001)		///*������ʹ��*///

#define C_InfraTimerClock_EN		((ulong32)0x00000010)	///*��ʱ��ʱ��Դʹ��*///
#define C_InfraTimerClock_DIS		((ulong32)0x00005a0d)	///*��ʱ��ʱ��Դ��ֹ*///

#define	InfraTimer_START			{InfraTimer->CR1 |= C_TimerCounter_EN;}		///*��ʱ����ʼ���������PWM�����ź�*///
#define	InfraTimer_STOP				{InfraTimer->CR1 &= (~C_TimerCounter_EN);}	///*��ʱ��ֹͣ������ֹͣPWM�����ź�*///
#define InfraTimerClock_EN			{RCC->APB2ENR |= C_InfraTimerClock_EN;}		///*ʹ�ܶ�ʱ��ʱ��*///
#define InfraTimerClock_DIS			{RCC->APB2ENR &= C_InfraTimerClock_DIS;}	///*��ֹ��ʱ��ʱ��*///


#define TIM_CounterMode_Up			((uint16_t)0xffef)
#define TIM_CounterMode_Down		((uint16_t)0x0010)

#define TIM_PSCReloadMode_Update	((uint16_t)0x0000)
#define TIM_PSCReloadMode_Immediate	((uint16_t)0x0001)

#define	TIM_Prescaler_0				0
#define	TIM_Prescaler_16			15						///*��Ƶϵ��=N+1*///
#define	TIM_Prescaler_16000			15999					///*��Ƶϵ��=N+1*///


#define TIM1_Period					16000
#define NoTIM_RepetitionCounter		0


#define SysTick_CLKSource_HCLK_Div8	((ulong32)0xFFFFFFFB)	///*SysTickʱ��Ϊ��ϵͳʱ��/8��*///
#define SysTick_CLKSource_HCLK		((ulong32)0x00000004)
#define SysTick_TICKINT_EN			((ulong32)0x00000002)
#define SysTick_ENABLE				((ulong32)0x00000001)
#define SysTick_COUNTFLAG			((ulong32)0x00010000)

///*�������ĵĺ궨��*///
///*������16MHz��Ƶ������*///
#define	TickTimer					ETIM2								///*timer10 use as tick timer:�������Ķ�ʱ��*///
#define	TickTimer_IRQHandler		ETIM2_IRQHandler		///*�жϷ������*///
#define	TickTimer_Interrupt			ETIM2_IRQn				///*�ж�������ַ*///

#define C_TickTimerClock_EN			((ulong32)0x00000008)	///*��ʱ��ʱ��Դʹ��*///
#define C_TickTimerClock_DIS		((ulong32)0xFFFFFFF7)	///*��ʱ��ʱ��Դ��ֹ*///
#define	C_TickTimerCounter			25535			        ///*5ms,���ۼ���5.004ms*///



#define	C_TIM_EGR_CLEAR				0x0000					///*EGR��λ*///
#define	C_TIM_SMCR_CLEAR			0x0000					///*SMCR��λ*///
#define	C_TIM_CCMR1_CLEAR			0x0000					///*SMCR��λ*///
#define	C_TIM_CR1_CLEAR				0x00000000					///*CR1��λ*///
#define	C_TIM_CCER_CLEAR			0x0000					///*CCER��λ*///
#define	C_TIM_UIE_DIS				0xFFFFFFF8					///*��ֹ�ж�*///
#define	C_TIM_UIE_EN				0x00000001					///*�ж�ʹ��*///
#define	C_TIM_OUTPUT_DIS			0x0000					///*��ʱ�������ֹ*///
#define	C_TIM_OR_CLEAR				0x0000					///*���üĴ�������*///
#define	C_TIM_CR1_URS				0x0004					///*ֻ������Ų����ж�*///
#define	C_TIM_CR1_ARPE				0x0080					///*ARR���л���*///
#define	C_TIM_CR1_DOWN				0x0010					///*���¼���*///
#define C_TIM_CR1_CEN				0x00000080					///*������ʹ��*///
#define	C_TIM_SR_UIF				0x0001					///*��ʱ�������־*///
#define	C_TIM_EGR_UG				0x0001					///*ֹͣ��ʱ*///
#define	C_TIM_CR1_UDIS				0x0002					///*ֹͣ��ʱ*///



//#define	TickTimer_START				{TickTimer->CR1 |= C_TimerCounter_EN;}		///*��ʱ����ʼ���������PWM�����ź�*///
//#define	TickTimer_STOP				{TickTimer->CR1 &= (~C_TimerCounter_EN);}	///*��ʱ��ֹͣ������ֹͣPWM�����ź�*///
#define	TickTimerClock_EN			{RCC->PERCLKCON4 |= C_TickTimerClock_EN;}		///*ʹ�ܶ�ʱ��ʱ��*///
#define	TickTimerClock_DIS			{RCC->PERCLKCON4 &= C_TickTimerClock_DIS;}		///*��ֹ��ʱ��ʱ��*///


#define	C_Interval_0ms				0						///*��ʱ������*///
#define	C_Interval_20ms				4						///*���ڻ������ĵ�20ms���*///
#define	C_Interval_50ms				10						///*���ڻ������ĵ�50ms���*///
#define	C_Interval_80ms				16						///*���ڻ������ĵ�80ms���*///
#define	C_Interval_100ms			20						///*���ڻ������ĵ�100ms���*///
#define	C_Interval_150ms			30						///*���ڻ������ĵ�100ms���*///
#define	C_Interval_300ms			60						///*���ڻ������ĵ�300ms���*///
#define	C_Interval_400ms			80						///*���ڻ������ĵ�400ms���*///
#define	C_Interval_500ms			100						///*���ڻ������ĵ�500ms���*///
#define	C_Interval_1000ms			200						///*���ڻ������ĵ�1s���*///
#define	C_Interval_2000ms			400						///*���ڻ������ĵ�2s���*///
#define	C_Interval_2500ms			500						///*���ڻ������ĵ�2.5s���*///
#define	C_Interval_3000ms			600						///*���ڻ������ĵ�3s���*///
#define	C_Interval_3150ms			630						///*���ڻ������ĵ�3.15s���*///
#define	C_Interval_5000ms			1000					///*���ڻ������ĵ�5s���*///
#define	C_Interval_1min				12000					///*���ڻ������ĵ�60s=1min���*///

#define	C_ExRelayInvaildNum		    15						/*500ms֮�ڣ�5ms����һ�Σ�����15��*/
#define	C_HardDelay_100			    100						///*�͹����µĻ���10msӲ��ʱ����ʱ��������ֹ��ʱ��û�п���ʱ������ѭ��*///

#define	C_TimerSwitch_8				0x80					///*ʱ�䶨ʱ���Ŀ��أ����λΪ1��ʾ������Ч*///
#define	C_TimerSwitch_16			0x8000					///*ʱ�䶨ʱ���Ŀ��أ����λΪ1��ʾ������Ч*///
#define	C_PulseMode					0x01					///*���ü̵�����բ��ʽ������ʽ*///

#define C_PowerOn_3s				0x03					///*�ϵ���3s*///
#define C_PowerOn_30min				(30*60)					/*�ϵ���30min������1s*/
///*�ϵ����ģ�����ʱ��:��Щ����ģ��ʹ���˼�����ʵʱ����,������������1s��ʱ��*///
#define C_ShutRealTimeData			C_Interval_2000ms
//#define	C_InitialValue_150ms		C_Interval_150ms		///*150ms��ʼֵ*///
//#define	C_InitialValue_3150ms		C_Interval_3100ms		///*3150ms��ʼֵ*///
//#define	C_Interval_Zero				0						///*��ʱ����ֹʱ��*///


///*ͣ�绽�Ѻ�������ĵĺ궨��*///
///*������8MHz��Ƶ������*///
#define	LowpowerTimer								LPTIM					///*timer9 use as lowpower timer:ͣ�绽�ѻ������Ķ�ʱ��*///
#define	LowpowerTimer_IRQHandler		LPTIM_IRQHandler			///*�жϷ������*///
#define	LowpowerTimer_Interrupt			LPTIM_IRQn				///*�ж�������ַ*///

#define C_LowpowerTimerClock_EN			((ulong32)0x00000003)			///*��ʱ��ʱ��Դʹ��*///
#define C_LowpowerTimerClock_DIS		((ulong32)0xfffffffc)			///*��ʱ��ʱ��Դ��ֹ*///
#define	C_LowpowerTimerCounter			81						///*5ms,���ۼ���5.004ms*///

//#define	LowpowerTimer_START				{LowpowerTimer->CR1 |= C_TimerCounter_EN;}		///*��ʱ����ʼ���������PWM�����ź�*///
//#define	LowpowerTimer_STOP				{LowpowerTimer->CR1 &= (~C_TimerCounter_EN);}	///*��ʱ��ֹͣ������ֹͣPWM�����ź�*///
#define	LowpowerTimerClock_EN				{RCC->PERCLKCON1 |= C_LowpowerTimerClock_EN;}		///*ʹ�ܶ�ʱ��ʱ��*///
#define	LowpowerTimerClock_DIS			{RCC->PERCLKCON1 &= C_LowpowerTimerClock_DIS;}		///*��ֹ��ʱ��ʱ��*///

///*RCHF 16MУ׼�ö�ʱ��*///
#define	RCHF_RecTimer								ETIM3					///**///
#define	RCHF_RecTimer_Interrupt			ETIM3_IRQn				///*�ж�������ַ*///

#define C_RCHF_RecTimerClock_EN			((ulong32)0x00000010)			///*��ʱ��ʱ��Դʹ��*///
#define C_RCHF_RecTimerClock_DIS		((ulong32)0xffffffef)			///*��ʱ��ʱ��Դ��ֹ*///
#define C_RCHF_RecTimerCounter_EN		((ulong32)0x00000080)

#define	RCHF_RecTimer_START					{RCHF_RecTimer->ETxCR |= C_RCHF_RecTimerCounter_EN;}		///*��ʱ����ʼ����*///
#define	RCHF_RecTimer_STOP					{RCHF_RecTimer->ETxCR &= (~C_RCHF_RecTimerCounter_EN);}	///*��ʱ��ֹͣ����*///
#define	RCHF_RecTimerClock_EN				{RCC->PERCLKCON4 |= C_RCHF_RecTimerClock_EN;}		///*ʹ�ܶ�ʱ��ʱ��*///
#define	RCHF_RecTimerClock_DIS			    {RCC->PERCLKCON4 &= C_RCHF_RecTimerClock_DIS;}		///*��ֹ��ʱ��ʱ��*///


///*�͹��ĺ��⻽�Ѷ�ʱ���ĺ궨��*///
///*������2.097MHz��Ƶ������*///
#define	InfraWakeupTimer				TIM7					///*timer9 use as lowpower timer:ͣ�绽�ѻ������Ķ�ʱ��*///
#define	InfraWakeupTimer_IRQHandler		TIM7_IRQHandler			///*�жϷ������*///
#define	InfraWakeupTimer_Interrupt		TIM7_IRQn				///*�ж�������ַ*///

#define C_InfraWakeupTimerClock_EN		((ulong32)0x00000020)	///*��ʱ��ʱ��Դʹ��*///
#define C_InfraWakeupTimerClock_DIS		((ulong32)0xb0feca1f)	///*��ʱ��ʱ��Դ��ֹ*///
//#define	C_InfraWakeupTimerCounter		107						///*����Ƶʱ��833us:ʵ�ʲ���ԼΪ836us*///
#define	C_InfraWakeupTimerCounter		1776					///*����Ƶʱ��833us:ʵ�ʲ���ԼΪ844us*///
//#define	InfraWakeupTimer_START			{LowpowerTimer->CR1 |= C_TimerCounter_EN;}		///*��ʱ����ʼ���������PWM�����ź�*///
//#define	InfraWakeupTimer_STOP			{LowpowerTimer->CR1 &= (~C_TimerCounter_EN);}	///*��ʱ��ֹͣ������ֹͣPWM�����ź�*///
#define	InfraWakeupTimerClock_EN		{RCC->APB1ENR |= C_InfraWakeupTimerClock_EN;}	///*ʹ�ܶ�ʱ��ʱ��*///
#define	InfraWakeupTimerClock_DIS		{RCC->APB1ENR &= C_InfraWakeupTimerClock_DIS;}	///*��ֹ��ʱ��ʱ��*///


///*���ģ�⿨ͨ�Ų����ʶ�ʱ���ĺ궨��*///
///*������4MHz��Ƶ������*///
///*TIM5��32λ��ʱ��*///
#define	CardBaudRateTimer							ETIM1					///*timer5 use as card baud rate timer:��ͨ�Ų����ʶ�ʱ��*///
#define	CardBaudRateTimer_IRQHandler	ETIM1_IRQHandler			///*�жϷ������*///
#define	CardBaudRateTimer_Interrupt		ETIM1_IRQn				///*�ж�������ַ*///

#define C_CardBaudRateTimerClock_EN		((ulong32)0x00000004)	///*��ʱ��ʱ��Դʹ��*///
#define C_CardBaudRateTimerClock_DIS	((ulong32)0xFFFFFFFB)	///*��ʱ��ʱ��Դ��ֹ*///

#define C_CardBaudRateTimerETxCR	((ulong32)0x00000000)	///*��ʱ��ʱ��Դ��ֹ*///
///*��Ƭ��������16M,��������3.579545M,���մ�Ƶ�����õ�Ƭ���Ķ�ʱ��

#define	C_CardBaudRateTimerCounter_4ms				1550		///*����Ƶʱ��4ms*///
#define	C_CardBaudRateTimerCounter_1_3_ETU		64981			///*����Ƶʱ��1/3ETU*///
#define	C_CardBaudRateTimerCounter_1_2_ETU		64704			///*����Ƶʱ��1/2ETU*///
#define	C_CardBaudRateTimerCounter_1_ETU			63872		///*����Ƶʱ��1ETU*///
#define	C_CardBaudRateTimerCounter_1_Piont_5_ETU	63041		///*����Ƶʱ��1.5ETU*///
#define	C_CardBaudRateTimerCounter_2_ETU			62209		///*����Ƶʱ��2ETU*///
#define	C_CardBaudRateTimerCounter_2_Piont_5_ETU	61378		///*����Ƶʱ��2.5ETU*///
#define	C_CardBaudRateTimerCounter_16_ETU			38931		///*����Ƶʱ��16ETU*///
#define	C_CardBaudRateTimerCounter_20_ETU			32279		///*����Ƶʱ��20ETU*///

#define	CardBaudRateTimerClock_EN		{RCC->PERCLKCON4 |= C_CardBaudRateTimerClock_EN;}	///*ʹ�ܶ�ʱ��ʱ��*///
#define	CardBaudRateTimerClock_DIS		{RCC->PERCLKCON4 &= C_CardBaudRateTimerClock_DIS;}	///*��ֹ��ʱ��ʱ��*///


#define C_4ms					0		///*����4ms��ʱ:9600ETUʵ��Ϊ997.67ms,Ϊ�˷���,���Ϊ1000ms*///
										///*����,9600ETUֻ��Ҫѭ��250�ξͿ�����,��������Ŀ����Ϊ�˷�Ƶ�������л�*///
										///*��Ƶ���л�ʱ,��Ҫ�ȵ���һ�������¼����������װ�ؽ�ȥ*///
#define C_1_3_ETU				1		///*����1/3��ETU��ʱ*///
#define C_1_2_ETU				2		///*����1/2��ETU��ʱ*///
#define C_1_Piont_5_ETU			3		///*����1.5��ETU��ʱ*///
#define C_2_Piont_5_ETU			4		///*����2.5��ETU��ʱ*///
#define C_1_ETU					5		///*����1��ETU��ʱ*///
#define C_2_ETU					6		///*����2��ETU��ʱ*///
#define C_16_ETU				7		///*����16��ETU��ʱ*///
#define C_20_ETU				8		///*����20��ETU��ʱ*///

#define C_Init					0x68	///*��Ҫ��ʼ����ʱ��*///
#define C_NotInit				0x00	///*����Ҫ��ʼ����ʱ��*///
///*����Ľṹ������ɰ���״̬ʱ����ʷ״̬�����ʱ��*///
typedef struct
{
	uchar8	Timer;		///*��ʱ������5msΪ��λ*///
	uchar8	HStatus;	///*��ʷ״̬*///
}Str_KeyStatus_Type1;
static Str_KeyStatus_Type1 Str_KeyUp;			///*�Ϸ���*///
static Str_KeyStatus_Type1 Str_KeyDown;			///*�·���*///
static Str_KeyStatus_Type1 Str_KeyPrg;			///*��̼�*///
static Str_KeyStatus_Type1 Str_KeyOpenCover;	///*�����*///
static Str_KeyStatus_Type1 Str_KeyOpenTerminal;	///*����β��*///
static Str_KeyStatus_Type1 Str_CheckAuPower;	///*������Դ������*///
static Str_KeyStatus_Type1 Str_Magnetic;		///*�ų����*///
static Str_KeyStatus_Type1 Str_MeterICIRQ;		///*����оƬIRQ����*///
static Str_KeyStatus_Type1 Str_RelayStatus;		///*�̵���״̬*///
static Str_KeyStatus_Type1 Str_ModuleStatus;	///*ģ������ͨ��״̬*///
static Str_KeyStatus_Type1 Str_CardStatus;		///*�忨״̬*///

static ulong32 SV_PowerDownReportTime;         /*�͹����������ϱ�*/ 
static ulong32 SV_PowerOffShutAcReportTime;    /*�����ϱ�1Сʱ����ʱ��*/ 

typedef struct
{
	ushort16 Timer;		///*��ʱ������5msΪ��λ,1�ֽڲ���*///
	uchar8	 HStatus;	///*��ʷ״̬*///
}Str_KeyStatus_Type2;
static Str_KeyStatus_Type2 Str_KeyUpPermit;		///*�Ϸ�����բ����3s*///
static Str_KeyStatus_Type2 Str_KeyDownPermit;	///*�·�����բ����3s*///

//typedef struct
//{
//	uchar8	Timer;		///*��ʱ������5msΪ��λ*///
//	uchar8	HStatus;	///*��ʷ״̬*///
//        uchar8  InvaildFlag;    ///*�Ƿ��иߵ�*///
//}Str_KeyStatus_Type3;
static Str_KeyStatus_Type1 Str_ExternalRelayStatus;	///*���ü̵���״̬*///

static ushort16		SV_ExternalRelayActTime;		///*���ü̵���������ʱ��������*///
static ushort16		SV_InternalRelayActTime;		///*���ü̵���������ʱ����400ms*///

static uchar8		SV_Timer_MultiFunction;			///*�๦�������ʱ����80ms*///
static uchar8		SV_Timer_ModuleReset;			///*ģ�鸴λ��ʱ����300ms*///

static	uchar8		SV_TimerBasedTickTimer_500ms;	///*���ڻ������Ķ�ʱ����500ms��ʱ��*///
static	uchar8		SV_TimerBasedTickTimer_100ms;	///*���ڻ������Ķ�ʱ����100ms��ʱ��*///
static	ushort16	SV_TimerBasedTickTimer_1000ms;	///*���ڻ������Ķ�ʱ����1s��ʱ��*///


static	ushort16	SV_TimerCruise;					///*5sѲ����ʱ��������5ms��ʱ*///
static	ushort16	SV_TimerCheckMcu;				///*1min���MCU�Ƿ�����������5ms��ʱ*///
static	uchar8		SV_TimerResetMoudle;			///*ģ�鸴λ��ʱ��������5ms��������*///

static	ushort16	SV_TimerFeedWatchdog;			///*ι����ʱ��������ʱ��ԼΪ12s*///
static	ushort16	SV_RCHFTemp;					///*У׼�ڲ�RCHF,�����¶�ÿ�仯5�����һ��

static	uchar8		SV_TimerShut100ms;				///*����100ms��ʱ��*///
static	ushort16	SV_TimerShutRealTimeData;		///*�ϵ����Ϊ��ѹ��ʵʱ��ԭ����б�����ʱ��*///

static	uchar8		SV_TimerPowerOn;				///*�ϵ��ʱ������������Ƶ�����µ�*///
static	ushort16	SV_usSuperCapCharge_Time;				///*�ϵ��ʱ�������ڿ����������ݳ��*///

#define	C_Interval_5ms		5						///*5ms:���ڷ�������ʱ��Ŀۼ�*///
#define	C_EXRELAY_5ms		1						///*5ms:�������ü̵�����ʱ��Ŀۼ�*///
static	uchar8		SV_BeeperAct;					///*��������������:����ػ���˸*///
static	ushort16	SV_BeeperTime;					///*������������ʱ��*///
static	ushort16	SV_BeeperCycle;					///*��������������*///
static	ushort16	SV_BeeperReverseTime;			///*��������˸ʱ��ʱ��*///

static	ushort16	SV_Timer_Delay;					///*��ʱ��ʱ��*///
static	uchar8		SV_CountDynamicDispNum;         ///*������ʾ�ġ�-*///
static	uchar8		SV_BasedTimer_500ms;	        ///*500ms��ʱ��   *///
//extern uchar8 GV_ucGetADC_Flag@".DataProcessADDR";    //�¶Ȳ���������־
///***********************************************************************************///
void InF_TickTimerStart(void);
void InF_TickTimerStop(void);
void InF_InfraModulatedSignalOutput(void);
void InF_InfraModulatedSignalOff(void);
uchar8 InF_GetPeripheralStatus(uchar8 Peripheral);
uchar8 InF_SwithPeripherals(uchar8 Peripherals,uchar8 Act);
extern void SF_MultiFunctionOutput(uchar8 V_Function);
extern void InF_Delay_2us(void);
extern void InF_Delay_us(ulong32 Delay_Num);
extern void SF_Set_MultiFunctionTimer(uchar8 Timer);
extern uchar8 InF_GetPowerOnTimer(void);
extern void SF_LowpowerTimerStart(void);
extern void SF_LowpowerTimerStop(void);
extern void SF_ClrPowerOnTimer();
extern void SF_InfarWakeupTimerStop(void);
//extern void SF_InfarWakeupTimer_Disable(void);
extern void SF_InfarWakeupTimer_Start(void);
extern void SF_ClrShutTime(void);
extern void SF_ClrSV_TimerBasedTickTimer_1000ms(void);

extern void SF_CardBaudRateTimerInit( uchar8 Timer_Init,uchar8 ETU_Number );
extern void SF_CardBaudRateTimer_Start(void);
extern void SF_CardBaudRateTimerStop(void);
extern void SF_CardTimerDelay_N_ETU( uchar8 ETU_Number );
extern void InF_SysTickDelay_1s(void);
extern uchar8 InF_JudgeDelay_1s(void);
extern void SF_ADC_Set(uchar8 V_ucFlag);



#endif
