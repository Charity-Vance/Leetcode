
//*****************************************************************************************///
//*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
//*File name:     main.c
//*Author:        
//*Version:       V1
//*Date:          2014-2-17
//*Description:   此文件是主流程文件
//*Function List: 见函数声明
//*History:       修改日期、修改者、修改内容简述
//*1. Date:
//*   Author:
//*   Modification:
//*2. Date:
//*   Author:
//*   Modification:
//*****************************************************************************************///


#include "Public.h"
#include "uart.h"
#include "IO.h"
#include "RTCDrive.h"


//#define NOP()	_NOP()
//#define EI()	__enable_irq()
//#define DI()	__disable_irq()

//#define NOP()	__no_operation()
#define EI()	__enable_irq()
#define DI()	__disable_irq()
///***********************************************************************************///
///*Function：int main(void)                                                         *///
///*Description：主流程函数                                                          *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Input：                                                                          *///
///*                                                                                 *///
///*Output：                                                                         *///
///*Return：                                                                         *///
///*Others：                                                                         *///
///***********************************************************************************///
int main(void)
{
mainstart:
	DI();

// 	if(!(RCC->PERCLKCON1&RCC_PERRCCCON1_PDCCKEN_ON))
//	{
//		RCC->PERCLKCON1|=RCC_PERRCCCON1_PDCCKEN_ON;
//	}
//	SwitchOn_Beep();///*test
 
/*	该配置在BootLoader中已经配置过了，这里不需要重复配置*/
	SCU->MCUDBGCR = 0;
	#if _DEBUG
	{
		SCU->MCUDBGCR |= 0x03;
	}
	#endif
	
	///*上电后将SFR都配置一下:配置为默认值,防止复位不完全*///
	DF_ReloadRegister();
	///*配置CPU工作系统时钟*///
	InF_SystemClockInPowerOn();

	InF_ConfigIOInPowerON();
	
#if ( 0 == _DEBUG )
	///*看门狗配置:约2s溢出*///
	InF_WatchDog_Init();
#endif
	
	///*上电定时器清零:用于部分功能的闭锁时间,对频繁上下电的限制*///
	SF_ClrPowerOnTimer();
#if 0		/*在BootLoader中已经增加了延时，这里不需要延时*/
	InF_Delay_us(200000);	/*上电延时200ms*/
#endif
	/*上电固定延时500ms：在延时过程中如果检测到掉电，立即退出该延时函数*/
//      SwitchOn_BackLight();//*test
	InF_PowerOnDelay();

	if(InF_CheckPowerAndExcute() == C_PowerRising)
	{
//		 SwitchOff_Beep();///*test
		  goto mainstart;
//		RCC->SOFTRST=0x5C5CAABB;
	}
//	SwitchOff_BackLight();///*test
	///*初始化消息队列*///
	InF_InitMessage();
	
	///*初始化LCD驱动芯片:直接调InF*///

	InF_InitLCD();
	///*LCD全显:包括LCD全显,背光灯点亮,拉闸灯点亮*///
//       SwitchOff_BackLight();///*test
	InF_Display_Init();
	
	///*初始化计量芯片*///
	InF_Initial_MeterIC();
	InF_Initial();
	InF_InitialEvenHarmonicCompensationTime();
	
	///*Esam初始化：发初始化ESAM芯片冷复位消息*///
	InF_InitEsamPowerOn();
	
	///*初始化RTC*///
	InF_InitalRTC();
	SF_InitRTCState();
	///*读取外部实时时钟*///
	InF_Dispatch_ReadRtcToDataProcess(C_PowerRising);
	
	///*数据层的上电初始化*///
	InF_PowerOn_CurrEnergyDeal();
	InF_Initial_Data();
	
	///*电量处理模块的上电初始化*///
	InF_EnergyInit();
	
	///*时段费率判断*///
	InF_Deal_MultiRates();
	
	///*需量定时器上电初始化：该函数必须在费率判断后调用*///
	InF_DemandInit();
	
	///*上电关于冻结的处理：该函数必须在结算日处理前调用，防止结算后需量被清零，冻结中无需量数据*///
	InF_FreezeDayAfterPowerUp();
	
	///*上电关于结算日的处理*///
	InF_SettleAccountsAfterPowerUp();
	
	///*上电关于事件记录的处理*///
	Inf_PowerupEventrestore();
	
	///*模块复位/模块设置禁止*///
	InF_SwithPeripherals(C_ModuleReset,C_On);
	InF_SwithPeripherals(C_ModuleSet,C_Off);
	
	
	///*通信、安全模块初始化,直接调用InF*///
	INF_Comm_ForPowerOn();
	InF_S_PowerOn();
	
	///*电池检测上电初始化：上电默认电池正常*///
	InF_InitBatt();
	
	///*初始化定时器，开始计时*///
	InF_InitTimer();								///*定时器上电初始化*///
	InF_TickTimerStart();							///*启动基本节拍定时器*///
	InF_CalibrateRC();								///*校准RC振荡初始化*///
	
	///*多功能端口上电初始化*///
	InF_MultiFunctionOutput_Init();
	
	///*继电器模块上电初始化*///
	InF_InitRelayStatusPowerUp();

	///*电压合格率模块上电初始化*///
	InF_VoltageQRrestore();
    
    /*卡状态初始化*/
    /*InF_CardParam( );*/

	///*冻结标志字节初始化*///
	//InF_InitFreezeOADFlag(0);
#if _DEBUG
	memset((uchar8 *)0x20005D00,0xCC,0x4000);
#endif
	EI();
//	InF_SwithPeripherals(C_BackLight,C_On);
//	ulong32 j=0;
//	InF_Total_Clear(C_Msg_Communication, C_FactoryInType,C_ClearMeterSafeFlag);///*test
	while (1)
	{
		///*检测掉电并处理*///
		if(InF_CheckPowerAndExcute() == C_PowerRising)
		{
			goto mainstart;
		}
		
//		InF_Delay_us(3000);
		///*看门狗定时器清零*///
		InF_ClrWatchDogTimer();
		
		///*每个循环处理一次5ms事件：该函数中将定时相关的消息发布*///
		InF_DealWith5ms();
		
		///*串口解析在两个消息队列处理前后都调用了,加快有通信时的响应速度*///
		///*处理串口解析、串口初始化：中断里置标志，主流程根据标志直接调用解析函数*///
		InF_Dispatch_CommInterruptMessage();
		
		///*处理两个消息队列：只有第1队列为空的情况下才处理第2队列*///
		InF_Dealwith_MessageSqueue();
		
		///*处理串口解析、串口初始化：中断里置标志，主流程根据标志直接调用解析函数*///
		InF_Dispatch_CommInterruptMessage();
		///*定时校验温度系数，数据通过命令更新后也要及时校验，复旦微RTC补偿数据校验.
		///*该部分主要是通信用，正常上电运行在InF_CheckRTC函数中，每1min调用检查一次
		if( temperpara_veri_flag )
		{
			Temperpara_Verify();	//温度系数校验	
		}		
//		ushort16 V_ReturnFlag;
//		uchar8	P_SendBuffer[100];
//		ushort16 V_Datalen=6;
//		ushort16 i;
		
//		P_SendBuffer[0]=0x80;
//		P_SendBuffer[1]=0x36;
//		P_SendBuffer[2]=0x00;
//		P_SendBuffer[3]=0xFF;
//		P_SendBuffer[4]=0x00;
//		P_SendBuffer[5]=0x00;
//		i=100;
				
//		V_ReturnFlag=INF_SendData_698_Esam(&P_SendBuffer[0],V_Datalen,&P_SendBuffer[0],&i);		
//		if(V_ReturnFlag!=0x9000)
//		{
//			j++;
//		}
//		SwitchOn_Beep();///*test
	}
}
