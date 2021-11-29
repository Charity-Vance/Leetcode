
//*****************************************************************************************///
//*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
//*File name:     main.c
//*Author:        
//*Version:       V1
//*Date:          2014-2-17
//*Description:   ���ļ����������ļ�
//*Function List: ����������
//*History:       �޸����ڡ��޸��ߡ��޸����ݼ���
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
///*Function��int main(void)                                                         *///
///*Description�������̺���                                                          *///
///*Calls��                                                                          *///
///*Called By��                                                                      *///
///*Input��                                                                          *///
///*                                                                                 *///
///*Output��                                                                         *///
///*Return��                                                                         *///
///*Others��                                                                         *///
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
 
/*	��������BootLoader���Ѿ����ù��ˣ����ﲻ��Ҫ�ظ�����*/
	SCU->MCUDBGCR = 0;
	#if _DEBUG
	{
		SCU->MCUDBGCR |= 0x03;
	}
	#endif
	
	///*�ϵ��SFR������һ��:����ΪĬ��ֵ,��ֹ��λ����ȫ*///
	DF_ReloadRegister();
	///*����CPU����ϵͳʱ��*///
	InF_SystemClockInPowerOn();

	InF_ConfigIOInPowerON();
	
#if ( 0 == _DEBUG )
	///*���Ź�����:Լ2s���*///
	InF_WatchDog_Init();
#endif
	
	///*�ϵ綨ʱ������:���ڲ��ֹ��ܵı���ʱ��,��Ƶ�����µ������*///
	SF_ClrPowerOnTimer();
#if 0		/*��BootLoader���Ѿ���������ʱ�����ﲻ��Ҫ��ʱ*/
	InF_Delay_us(200000);	/*�ϵ���ʱ200ms*/
#endif
	/*�ϵ�̶���ʱ500ms������ʱ�����������⵽���磬�����˳�����ʱ����*/
//      SwitchOn_BackLight();//*test
	InF_PowerOnDelay();

	if(InF_CheckPowerAndExcute() == C_PowerRising)
	{
//		 SwitchOff_Beep();///*test
		  goto mainstart;
//		RCC->SOFTRST=0x5C5CAABB;
	}
//	SwitchOff_BackLight();///*test
	///*��ʼ����Ϣ����*///
	InF_InitMessage();
	
	///*��ʼ��LCD����оƬ:ֱ�ӵ�InF*///

	InF_InitLCD();
	///*LCDȫ��:����LCDȫ��,����Ƶ���,��բ�Ƶ���*///
//       SwitchOff_BackLight();///*test
	InF_Display_Init();
	
	///*��ʼ������оƬ*///
	InF_Initial_MeterIC();
	InF_Initial();
	InF_InitialEvenHarmonicCompensationTime();
	
	///*Esam��ʼ��������ʼ��ESAMоƬ�临λ��Ϣ*///
	InF_InitEsamPowerOn();
	
	///*��ʼ��RTC*///
	InF_InitalRTC();
	SF_InitRTCState();
	///*��ȡ�ⲿʵʱʱ��*///
	InF_Dispatch_ReadRtcToDataProcess(C_PowerRising);
	
	///*���ݲ���ϵ��ʼ��*///
	InF_PowerOn_CurrEnergyDeal();
	InF_Initial_Data();
	
	///*��������ģ����ϵ��ʼ��*///
	InF_EnergyInit();
	
	///*ʱ�η����ж�*///
	InF_Deal_MultiRates();
	
	///*������ʱ���ϵ��ʼ�����ú��������ڷ����жϺ����*///
	InF_DemandInit();
	
	///*�ϵ���ڶ���Ĵ����ú��������ڽ����մ���ǰ���ã���ֹ��������������㣬����������������*///
	InF_FreezeDayAfterPowerUp();
	
	///*�ϵ���ڽ����յĴ���*///
	InF_SettleAccountsAfterPowerUp();
	
	///*�ϵ�����¼���¼�Ĵ���*///
	Inf_PowerupEventrestore();
	
	///*ģ�鸴λ/ģ�����ý�ֹ*///
	InF_SwithPeripherals(C_ModuleReset,C_On);
	InF_SwithPeripherals(C_ModuleSet,C_Off);
	
	
	///*ͨ�š���ȫģ���ʼ��,ֱ�ӵ���InF*///
	INF_Comm_ForPowerOn();
	InF_S_PowerOn();
	
	///*��ؼ���ϵ��ʼ�����ϵ�Ĭ�ϵ������*///
	InF_InitBatt();
	
	///*��ʼ����ʱ������ʼ��ʱ*///
	InF_InitTimer();								///*��ʱ���ϵ��ʼ��*///
	InF_TickTimerStart();							///*�����������Ķ�ʱ��*///
	InF_CalibrateRC();								///*У׼RC�񵴳�ʼ��*///
	
	///*�๦�ܶ˿��ϵ��ʼ��*///
	InF_MultiFunctionOutput_Init();
	
	///*�̵���ģ���ϵ��ʼ��*///
	InF_InitRelayStatusPowerUp();

	///*��ѹ�ϸ���ģ���ϵ��ʼ��*///
	InF_VoltageQRrestore();
    
    /*��״̬��ʼ��*/
    /*InF_CardParam( );*/

	///*�����־�ֽڳ�ʼ��*///
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
		///*�����粢����*///
		if(InF_CheckPowerAndExcute() == C_PowerRising)
		{
			goto mainstart;
		}
		
//		InF_Delay_us(3000);
		///*���Ź���ʱ������*///
		InF_ClrWatchDogTimer();
		
		///*ÿ��ѭ������һ��5ms�¼����ú����н���ʱ��ص���Ϣ����*///
		InF_DealWith5ms();
		
		///*���ڽ�����������Ϣ���д���ǰ�󶼵�����,�ӿ���ͨ��ʱ����Ӧ�ٶ�*///
		///*�����ڽ��������ڳ�ʼ�����ж����ñ�־�������̸��ݱ�־ֱ�ӵ��ý�������*///
		InF_Dispatch_CommInterruptMessage();
		
		///*����������Ϣ���У�ֻ�е�1����Ϊ�յ�����²Ŵ����2����*///
		InF_Dealwith_MessageSqueue();
		
		///*�����ڽ��������ڳ�ʼ�����ж����ñ�־�������̸��ݱ�־ֱ�ӵ��ý�������*///
		InF_Dispatch_CommInterruptMessage();
		///*��ʱУ���¶�ϵ��������ͨ��������º�ҲҪ��ʱУ�飬����΢RTC��������У��.
		///*�ò�����Ҫ��ͨ���ã������ϵ�������InF_CheckRTC�����У�ÿ1min���ü��һ��
		if( temperpara_veri_flag )
		{
			Temperpara_Verify();	//�¶�ϵ��У��	
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
