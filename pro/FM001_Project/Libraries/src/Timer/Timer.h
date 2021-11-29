
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
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
//TIM6: calibrate timer   (用于校准RC)
//ETIM1: card baud rate timer(用于卡通信:延时的控制)
//ETIM3: 用于RCHF时钟校准

//#define C_WatchDog_Feed				200						///*1s以内每5ms喂狗一次*///
#define C_WatchDog_Feed				2400					///*12s以内每5ms喂狗一次:超过12s不再喂狗*///
#define C_WatchDog_FeedOut			3000					///*超过15s不喂狗*///

///*红外发送38KHz调制信号使用TIMER11的PWM输出功能*///
///*工作于16MHz主频的配置*///
#define	InfraTimer					TIM11					///*timer11 use as 38KHz of infra *///
#define	C_InfraTimerCounter			0xd3					///*红外调制信号自动重装载值*///
#define	C_InfraTimerCounter_Wakeup	0x1c					///*低功耗唤醒后红外调制信号自动重装载值*///

#define C_TimerStatus_OVIF_RESET		((ulong32)0x00000001)		///*用于清除标志位*///
#define C_TimerStatus_CAPIF_RESET		((ulong32)0x00000002)		///*用于清除标志位*///
#define C_TimerStatus_UIF_RESET		((ulong32)0xfffe)		///*用于清除标志位*///
#define C_TimerStatus_BIF_RESET		((ushort16)0xff7f)
#define C_TimerStatus_TIF_RESET		((ushort16)0xffbf)
#define C_TimerStatus_CCIF_RESET	((ushort16)0xffe1)
#define C_TimerStatus_RESET			((ulong32)0x0000000f)

#define C_TimerCounter_EN			((ulong32)0x00000001)		///*计数器使能*///

#define C_InfraTimerClock_EN		((ulong32)0x00000010)	///*定时器时钟源使能*///
#define C_InfraTimerClock_DIS		((ulong32)0x00005a0d)	///*定时器时钟源禁止*///

#define	InfraTimer_START			{InfraTimer->CR1 |= C_TimerCounter_EN;}		///*定时器开始计数：输出PWM调制信号*///
#define	InfraTimer_STOP				{InfraTimer->CR1 &= (~C_TimerCounter_EN);}	///*定时器停止计数：停止PWM调制信号*///
#define InfraTimerClock_EN			{RCC->APB2ENR |= C_InfraTimerClock_EN;}		///*使能定时器时钟*///
#define InfraTimerClock_DIS			{RCC->APB2ENR &= C_InfraTimerClock_DIS;}	///*禁止定时器时钟*///


#define TIM_CounterMode_Up			((uint16_t)0xffef)
#define TIM_CounterMode_Down		((uint16_t)0x0010)

#define TIM_PSCReloadMode_Update	((uint16_t)0x0000)
#define TIM_PSCReloadMode_Immediate	((uint16_t)0x0001)

#define	TIM_Prescaler_0				0
#define	TIM_Prescaler_16			15						///*分频系数=N+1*///
#define	TIM_Prescaler_16000			15999					///*分频系数=N+1*///


#define TIM1_Period					16000
#define NoTIM_RepetitionCounter		0


#define SysTick_CLKSource_HCLK_Div8	((ulong32)0xFFFFFFFB)	///*SysTick时钟为“系统时钟/8”*///
#define SysTick_CLKSource_HCLK		((ulong32)0x00000004)
#define SysTick_TICKINT_EN			((ulong32)0x00000002)
#define SysTick_ENABLE				((ulong32)0x00000001)
#define SysTick_COUNTFLAG			((ulong32)0x00010000)

///*基本节拍的宏定义*///
///*工作于16MHz主频的配置*///
#define	TickTimer					ETIM2								///*timer10 use as tick timer:基本节拍定时器*///
#define	TickTimer_IRQHandler		ETIM2_IRQHandler		///*中断服务程序*///
#define	TickTimer_Interrupt			ETIM2_IRQn				///*中断向量地址*///

#define C_TickTimerClock_EN			((ulong32)0x00000008)	///*定时器时钟源使能*///
#define C_TickTimerClock_DIS		((ulong32)0xFFFFFFF7)	///*定时器时钟源禁止*///
#define	C_TickTimerCounter			25535			        ///*5ms,理论计算5.004ms*///



#define	C_TIM_EGR_CLEAR				0x0000					///*EGR复位*///
#define	C_TIM_SMCR_CLEAR			0x0000					///*SMCR复位*///
#define	C_TIM_CCMR1_CLEAR			0x0000					///*SMCR复位*///
#define	C_TIM_CR1_CLEAR				0x00000000					///*CR1复位*///
#define	C_TIM_CCER_CLEAR			0x0000					///*CCER复位*///
#define	C_TIM_UIE_DIS				0xFFFFFFF8					///*禁止中断*///
#define	C_TIM_UIE_EN				0x00000001					///*中断使能*///
#define	C_TIM_OUTPUT_DIS			0x0000					///*定时器输出禁止*///
#define	C_TIM_OR_CLEAR				0x0000					///*配置寄存器清零*///
#define	C_TIM_CR1_URS				0x0004					///*只有溢出才产生中断*///
#define	C_TIM_CR1_ARPE				0x0080					///*ARR具有缓冲*///
#define	C_TIM_CR1_DOWN				0x0010					///*向下计数*///
#define C_TIM_CR1_CEN				0x00000080					///*计数器使能*///
#define	C_TIM_SR_UIF				0x0001					///*定时器溢出标志*///
#define	C_TIM_EGR_UG				0x0001					///*停止计时*///
#define	C_TIM_CR1_UDIS				0x0002					///*停止计时*///



//#define	TickTimer_START				{TickTimer->CR1 |= C_TimerCounter_EN;}		///*定时器开始计数：输出PWM调制信号*///
//#define	TickTimer_STOP				{TickTimer->CR1 &= (~C_TimerCounter_EN);}	///*定时器停止计数：停止PWM调制信号*///
#define	TickTimerClock_EN			{RCC->PERCLKCON4 |= C_TickTimerClock_EN;}		///*使能定时器时钟*///
#define	TickTimerClock_DIS			{RCC->PERCLKCON4 &= C_TickTimerClock_DIS;}		///*禁止定时器时钟*///


#define	C_Interval_0ms				0						///*计时器清零*///
#define	C_Interval_20ms				4						///*基于基本节拍的20ms间隔*///
#define	C_Interval_50ms				10						///*基于基本节拍的50ms间隔*///
#define	C_Interval_80ms				16						///*基于基本节拍的80ms间隔*///
#define	C_Interval_100ms			20						///*基于基本节拍的100ms间隔*///
#define	C_Interval_150ms			30						///*基于基本节拍的100ms间隔*///
#define	C_Interval_300ms			60						///*基于基本节拍的300ms间隔*///
#define	C_Interval_400ms			80						///*基于基本节拍的400ms间隔*///
#define	C_Interval_500ms			100						///*基于基本节拍的500ms间隔*///
#define	C_Interval_1000ms			200						///*基于基本节拍的1s间隔*///
#define	C_Interval_2000ms			400						///*基于基本节拍的2s间隔*///
#define	C_Interval_2500ms			500						///*基于基本节拍的2.5s间隔*///
#define	C_Interval_3000ms			600						///*基于基本节拍的3s间隔*///
#define	C_Interval_3150ms			630						///*基于基本节拍的3.15s间隔*///
#define	C_Interval_5000ms			1000					///*基于基本节拍的5s间隔*///
#define	C_Interval_1min				12000					///*基于基本节拍的60s=1min间隔*///

#define	C_ExRelayInvaildNum		    15						/*500ms之内，5ms采样一次，采样15次*/
#define	C_HardDelay_100			    100						///*低功耗下的基于10ms硬延时的延时次数，防止定时器没有开启时进入死循环*///

#define	C_TimerSwitch_8				0x80					///*时间定时器的开关：最高位为1表示开关有效*///
#define	C_TimerSwitch_16			0x8000					///*时间定时器的开关：最高位为1表示开关有效*///
#define	C_PulseMode					0x01					///*外置继电器跳闸方式：脉冲式*///

#define C_PowerOn_3s				0x03					///*上电满3s*///
#define C_PowerOn_30min				(30*60)					/*上电满30min，基于1s*/
///*上电后功能模块闭锁时间:这些功能模块使用了计量的实时数据,而计量闭锁了1s的时间*///
#define C_ShutRealTimeData			C_Interval_2000ms
//#define	C_InitialValue_150ms		C_Interval_150ms		///*150ms初始值*///
//#define	C_InitialValue_3150ms		C_Interval_3100ms		///*3150ms初始值*///
//#define	C_Interval_Zero				0						///*定时器终止时间*///


///*停电唤醒后基本节拍的宏定义*///
///*工作于8MHz主频的配置*///
#define	LowpowerTimer								LPTIM					///*timer9 use as lowpower timer:停电唤醒基本节拍定时器*///
#define	LowpowerTimer_IRQHandler		LPTIM_IRQHandler			///*中断服务程序*///
#define	LowpowerTimer_Interrupt			LPTIM_IRQn				///*中断向量地址*///

#define C_LowpowerTimerClock_EN			((ulong32)0x00000003)			///*定时器时钟源使能*///
#define C_LowpowerTimerClock_DIS		((ulong32)0xfffffffc)			///*定时器时钟源禁止*///
#define	C_LowpowerTimerCounter			81						///*5ms,理论计算5.004ms*///

//#define	LowpowerTimer_START				{LowpowerTimer->CR1 |= C_TimerCounter_EN;}		///*定时器开始计数：输出PWM调制信号*///
//#define	LowpowerTimer_STOP				{LowpowerTimer->CR1 &= (~C_TimerCounter_EN);}	///*定时器停止计数：停止PWM调制信号*///
#define	LowpowerTimerClock_EN				{RCC->PERCLKCON1 |= C_LowpowerTimerClock_EN;}		///*使能定时器时钟*///
#define	LowpowerTimerClock_DIS			{RCC->PERCLKCON1 &= C_LowpowerTimerClock_DIS;}		///*禁止定时器时钟*///

///*RCHF 16M校准用定时器*///
#define	RCHF_RecTimer								ETIM3					///**///
#define	RCHF_RecTimer_Interrupt			ETIM3_IRQn				///*中断向量地址*///

#define C_RCHF_RecTimerClock_EN			((ulong32)0x00000010)			///*定时器时钟源使能*///
#define C_RCHF_RecTimerClock_DIS		((ulong32)0xffffffef)			///*定时器时钟源禁止*///
#define C_RCHF_RecTimerCounter_EN		((ulong32)0x00000080)

#define	RCHF_RecTimer_START					{RCHF_RecTimer->ETxCR |= C_RCHF_RecTimerCounter_EN;}		///*定时器开始计数*///
#define	RCHF_RecTimer_STOP					{RCHF_RecTimer->ETxCR &= (~C_RCHF_RecTimerCounter_EN);}	///*定时器停止计数*///
#define	RCHF_RecTimerClock_EN				{RCC->PERCLKCON4 |= C_RCHF_RecTimerClock_EN;}		///*使能定时器时钟*///
#define	RCHF_RecTimerClock_DIS			    {RCC->PERCLKCON4 &= C_RCHF_RecTimerClock_DIS;}		///*禁止定时器时钟*///


///*低功耗红外唤醒定时器的宏定义*///
///*工作于2.097MHz主频的配置*///
#define	InfraWakeupTimer				TIM7					///*timer9 use as lowpower timer:停电唤醒基本节拍定时器*///
#define	InfraWakeupTimer_IRQHandler		TIM7_IRQHandler			///*中断服务程序*///
#define	InfraWakeupTimer_Interrupt		TIM7_IRQn				///*中断向量地址*///

#define C_InfraWakeupTimerClock_EN		((ulong32)0x00000020)	///*定时器时钟源使能*///
#define C_InfraWakeupTimerClock_DIS		((ulong32)0xb0feca1f)	///*定时器时钟源禁止*///
//#define	C_InfraWakeupTimerCounter		107						///*不分频时，833us:实际测试约为836us*///
#define	C_InfraWakeupTimerCounter		1776					///*不分频时，833us:实际测试约为844us*///
//#define	InfraWakeupTimer_START			{LowpowerTimer->CR1 |= C_TimerCounter_EN;}		///*定时器开始计数：输出PWM调制信号*///
//#define	InfraWakeupTimer_STOP			{LowpowerTimer->CR1 &= (~C_TimerCounter_EN);}	///*定时器停止计数：停止PWM调制信号*///
#define	InfraWakeupTimerClock_EN		{RCC->APB1ENR |= C_InfraWakeupTimerClock_EN;}	///*使能定时器时钟*///
#define	InfraWakeupTimerClock_DIS		{RCC->APB1ENR &= C_InfraWakeupTimerClock_DIS;}	///*禁止定时器时钟*///


///*软件模拟卡通信波特率定时器的宏定义*///
///*工作于4MHz主频的配置*///
///*TIM5是32位定时器*///
#define	CardBaudRateTimer							ETIM1					///*timer5 use as card baud rate timer:卡通信波特率定时器*///
#define	CardBaudRateTimer_IRQHandler	ETIM1_IRQHandler			///*中断服务程序*///
#define	CardBaudRateTimer_Interrupt		ETIM1_IRQn				///*中断向量地址*///

#define C_CardBaudRateTimerClock_EN		((ulong32)0x00000004)	///*定时器时钟源使能*///
#define C_CardBaudRateTimerClock_DIS	((ulong32)0xFFFFFFFB)	///*定时器时钟源禁止*///

#define C_CardBaudRateTimerETxCR	((ulong32)0x00000000)	///*定时器时钟源禁止*///
///*单片机工作于16M,卡工作于3.579545M,按照此频率配置单片机的定时器

#define	C_CardBaudRateTimerCounter_4ms				1550		///*不分频时，4ms*///
#define	C_CardBaudRateTimerCounter_1_3_ETU		64981			///*不分频时，1/3ETU*///
#define	C_CardBaudRateTimerCounter_1_2_ETU		64704			///*不分频时，1/2ETU*///
#define	C_CardBaudRateTimerCounter_1_ETU			63872		///*不分频时，1ETU*///
#define	C_CardBaudRateTimerCounter_1_Piont_5_ETU	63041		///*不分频时，1.5ETU*///
#define	C_CardBaudRateTimerCounter_2_ETU			62209		///*不分频时，2ETU*///
#define	C_CardBaudRateTimerCounter_2_Piont_5_ETU	61378		///*不分频时，2.5ETU*///
#define	C_CardBaudRateTimerCounter_16_ETU			38931		///*不分频时，16ETU*///
#define	C_CardBaudRateTimerCounter_20_ETU			32279		///*不分频时，20ETU*///

#define	CardBaudRateTimerClock_EN		{RCC->PERCLKCON4 |= C_CardBaudRateTimerClock_EN;}	///*使能定时器时钟*///
#define	CardBaudRateTimerClock_DIS		{RCC->PERCLKCON4 &= C_CardBaudRateTimerClock_DIS;}	///*禁止定时器时钟*///


#define C_4ms					0		///*进行4ms定时:9600ETU实际为997.67ms,为了方便,设计为1000ms*///
										///*这样,9600ETU只需要循环250次就可以了,这样做的目的是为了分频不来回切换*///
										///*分频器切换时,需要等到下一个更新事件发生后才能装载进去*///
#define C_1_3_ETU				1		///*进行1/3个ETU定时*///
#define C_1_2_ETU				2		///*进行1/2个ETU定时*///
#define C_1_Piont_5_ETU			3		///*进行1.5个ETU定时*///
#define C_2_Piont_5_ETU			4		///*进行2.5个ETU定时*///
#define C_1_ETU					5		///*进行1个ETU定时*///
#define C_2_ETU					6		///*进行2个ETU定时*///
#define C_16_ETU				7		///*进行16个ETU定时*///
#define C_20_ETU				8		///*进行20个ETU定时*///

#define C_Init					0x68	///*需要初始化定时器*///
#define C_NotInit				0x00	///*不需要初始化定时器*///
///*下面的结构体用与采按键状态时的历史状态及其计时器*///
typedef struct
{
	uchar8	Timer;		///*计时器：以5ms为单位*///
	uchar8	HStatus;	///*历史状态*///
}Str_KeyStatus_Type1;
static Str_KeyStatus_Type1 Str_KeyUp;			///*上翻键*///
static Str_KeyStatus_Type1 Str_KeyDown;			///*下翻键*///
static Str_KeyStatus_Type1 Str_KeyPrg;			///*编程键*///
static Str_KeyStatus_Type1 Str_KeyOpenCover;	///*开表盖*///
static Str_KeyStatus_Type1 Str_KeyOpenTerminal;	///*开端尾盖*///
static Str_KeyStatus_Type1 Str_CheckAuPower;	///*辅助电源掉电检测*///
static Str_KeyStatus_Type1 Str_Magnetic;		///*磁场检测*///
static Str_KeyStatus_Type1 Str_MeterICIRQ;		///*计量芯片IRQ请求*///
static Str_KeyStatus_Type1 Str_RelayStatus;		///*继电器状态*///
static Str_KeyStatus_Type1 Str_ModuleStatus;	///*模块上行通信状态*///
static Str_KeyStatus_Type1 Str_CardStatus;		///*插卡状态*///

static ulong32 SV_PowerDownReportTime;         /*低功耗下主动上报*/ 
static ulong32 SV_PowerOffShutAcReportTime;    /*主动上报1小时闭锁时间*/ 

typedef struct
{
	ushort16 Timer;		///*计时器：以5ms为单位,1字节不够*///
	uchar8	 HStatus;	///*历史状态*///
}Str_KeyStatus_Type2;
static Str_KeyStatus_Type2 Str_KeyUpPermit;		///*上翻键合闸允许：3s*///
static Str_KeyStatus_Type2 Str_KeyDownPermit;	///*下翻键合闸允许：3s*///

//typedef struct
//{
//	uchar8	Timer;		///*计时器：以5ms为单位*///
//	uchar8	HStatus;	///*历史状态*///
//        uchar8  InvaildFlag;    ///*是否有高低*///
//}Str_KeyStatus_Type3;
static Str_KeyStatus_Type1 Str_ExternalRelayStatus;	///*外置继电器状态*///

static ushort16		SV_ExternalRelayActTime;		///*外置继电器动作计时器：可设*///
static ushort16		SV_InternalRelayActTime;		///*内置继电器动作计时器：400ms*///

static uchar8		SV_Timer_MultiFunction;			///*多功能输出计时器：80ms*///
static uchar8		SV_Timer_ModuleReset;			///*模块复位计时器：300ms*///

static	uchar8		SV_TimerBasedTickTimer_500ms;	///*基于基本节拍定时器的500ms定时器*///
static	uchar8		SV_TimerBasedTickTimer_100ms;	///*基于基本节拍定时器的100ms定时器*///
static	ushort16	SV_TimerBasedTickTimer_1000ms;	///*基于基本节拍定时器的1s定时器*///


static	ushort16	SV_TimerCruise;					///*5s巡航定时器：基于5ms定时*///
static	ushort16	SV_TimerCheckMcu;				///*1min检查MCU是否正常：基于5ms定时*///
static	uchar8		SV_TimerResetMoudle;			///*模块复位定时器：基于5ms基本节拍*///

static	ushort16	SV_TimerFeedWatchdog;			///*喂狗定时器：狗叫时间约为12s*///
static	ushort16	SV_RCHFTemp;					///*校准内部RCHF,环境温度每变化5℃调用一次

static	uchar8		SV_TimerShut100ms;				///*闭锁100ms定时器*///
static	ushort16	SV_TimerShutRealTimeData;		///*上电后因为电压等实时量原因进行闭锁定时器*///

static	uchar8		SV_TimerPowerOn;				///*上电计时器：用于区分频繁上下电*///
static	ushort16	SV_usSuperCapCharge_Time;				///*上电计时器：用于开启超级电容充电*///

#define	C_Interval_5ms		5						///*5ms:用于蜂鸣器总时间的扣减*///
#define	C_EXRELAY_5ms		1						///*5ms:用于外置继电器总时间的扣减*///
static	uchar8		SV_BeeperAct;					///*蜂鸣器动作类型:开或关或闪烁*///
static	ushort16	SV_BeeperTime;					///*蜂鸣器动作总时间*///
static	ushort16	SV_BeeperCycle;					///*蜂鸣器动作周期*///
static	ushort16	SV_BeeperReverseTime;			///*蜂鸣器闪烁时计时器*///

static	ushort16	SV_Timer_Delay;					///*延时计时器*///
static	uchar8		SV_CountDynamicDispNum;         ///*具体显示的“-*///
static	uchar8		SV_BasedTimer_500ms;	        ///*500ms定时器   *///
//extern uchar8 GV_ucGetADC_Flag@".DataProcessADDR";    //温度补偿采样标志
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
