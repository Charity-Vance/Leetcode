
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     Public.h
///*Version:       V1
///*Date:          2014-3-12
///*Description:
///*Function List:
///*****************************************************************************************///
#ifndef	__Public_H
#define	__Public_H



#include <math.h>
#include <stdio.h>
#include <string.h>
#include "FM33A0XX.h"
#include "system_FM33A0XX.h"
#include "fm32l0xx_anac.h"
#include "fm32l0xx_rcc.h"
#include "Public_CBB.h"

#include "DI.h"
#include "DILenth.h"

///*���Գ���ĺ궨�壬�޸ĸñ�־λע�����startup_ht6x3x�ļ��У�DCD     0xE3FFFFA2      ///*Flash �����ܣ�Sleep/Hold ��WDT����
//#define		_DEBUG		1				///*���Գ�����Ϊ��1��*///
#define		_DEBUG		0				///*��ʽ������Ϊ��0��*///
/*
	�Ӽ���оƬ�������������ֵ,hex��ʽ��Ŀǰ����ģ����(������)����ͬ������͵ı���Ԥ��Ҫ����˶Ժͷ���ʣ���Ȼ��Ӱ����ܼ���
	��ѹ���	�������		���峣��    3*1.5Un*2Imaxʱ0.5s������    10s������    	ȡ��    	תΪ16������
	3��220/380	3��1.5(6)A		6400		12.16							243.2		244			0xF4
	3��220/380	3��5(60)A		400			13.2							264			264			0x108
	3��220/380	3��10(100)A		300			8.25							132			132			0x84
	3��57.7/100	3��0.3(1.2)A		100000		8.655							173.1		174			0xAE
	3��57.7/100	3��1.5(6)A		20000		8.655							173.1		174			0xAE
	3��57.7/100	3��1(10)A		20000		14.425							288.5		289			0x121
	3��100		3��0.3(1.2)A		100000		10								200			200			0xC8
	3��100		3��1.5(6)A		20000		10								200			200			0xC8
	3��100		3��1(10)A		20000		16.6667							333.333		334			0x14E
*/

#define C_Pluse_Most__Lim    	0x121			/*����оƬ�������������ֵ*/



/********֧�ֹ�Լ�б�ĸ���********/
#if 0
//#define C_CommProNum		0			/*֧��1����Լ�б�*/
#define C_CommProNum		1			/*֧��2����Լ�б�*/

#define CommProShortOrLong(ShortValue,LongValue) ( (C_CommProNum == 0) ? ShortValue:LongValue ) // ShortValue:16���ֽ� LongValue:32���ֽ�
#endif

#define	C_MeterICDataNum_T	150

///********macro ��С��ģʽ********///
#define	C_LargeType			0x01			///*���ģʽ*///
#define	C_LowType			0x02			///*С��ģʽ*///
#define	C_WordType			C_LowType		///**///

///********macro ������Ƶ********///
#define	C_ClkFosc			0x01			///*��Ƶ������32.768*///
#define	C_ClkPll			0x02			///*������22M*///

///********macro pcb���********///
#define	C_Pcb2457						0x01			///*-M��*///
#define	C_Pcb2481       	  0x02            ///*���ܱ�Զ�̱�*///
#define	C_PcbVersion		    C_Pcb2481		///*����궨����Ҫ����IO���ߡ�Uart��PWM���Ƶ����ã��ײ�������*///

#define C_MeterType_Module	0x02			///*ģ���*///

///********macro ���ܱ�����********///
#define	C_SmartMeter		0x01            ///*���ܱ��޷ѿ�*///
#define	C_R_SmartMeter		0x02            ///*Զ�̷ѿأ�Remote*///
#define	C_L_SmartMeter		0x03            ///*���طѿأ�Local*///

/********macro ������ݸ�ʽ********/
#define	C_Format_BCD			0x01			/*���BCD��ʽ*/
#define	C_Format_HEX			0x02			/*���hex��ʽ*/

#define	C_Happen_EventState		0x68			/*�¼�״̬���з����޻ָ�*/
#define	C_End_EventState		0x00			/*�¼�״̬�����з����޻ָ�*/

#define	C_AAorBBIsActive		0x98			/*AA/BBΪ��Ч����*/
#define	C_AAorBBIsDisactive		0x86			/*AA/BBΪ��Ч����*/
///********macro �Ƿ��������ο�Դ�¶Ȳ���********///
#define	C_Temp_VrefAotu_En		0x01            ///*�����¶Ȳ���*///
#define	C_Temp_VrefAotu_Dis		0x02            ///*�ر��¶Ȳ���*///

///********macro �Ƿ�ر�ESAM��Դ********///
#define	C_ESAMPower_Open		0x01            ///*���ر�ESAM��Դ*///
#define	C_ESAMPower_Close		0x02            ///*�ر�ESAM��Դ*///

///********macro �Ƿ������г������********///
#define	C_Odd_Harmonic_En		  0x01            ///*�������г������*///
#define	C_Odd_Harmonic_Dis		0x02            ///*�ر����г������*///

///********macro �Ƿ���ż��г������********///
#define	C_Even_Harmonic_En		  0x01            ///*����ż��г������*///
#define	C_Even_Harmonic_Dis		0x02            ///*�ر�ż��г������*///

///********macro �Ƿ���г�������*******///
#define	C_Cap_WhetherUsed_En		  0x01            ///*ʹ�ó�������*///
#define	C_Cap_WhetherUsed_Dis		  0x02            ///*��ʹ�ó�������*///

/********macro �������ݳ�翪��ʱ��*******/
#define C_Cap_OpenAfter30min_En			0x01			/*�ϵ�30min�󳬼����ݿ�ʼ���*/
#define C_Cap_OpenAfter30min_Dis		0x02			/*�ϵ�3s�󳬼����ݿ�ʼ���*/

///********macro ������ͱ�־********///
#define	C_3P3W				0x00			///*��������*///
#define	C_3P4W 				0x01			///*��������*///

///********macro ��Դ��־********///
#define	C_PowerOff			0x68            ///*�����־*///
#define	C_PowerOn			0x00            ///*�е��־*///
#define	C_PowerFalling		0x86            ///*�������е絽������ر��־*///
#define	C_PowerRising		0xa5            ///*�����ӵ��絽�е���ر��־*///
#define C_InfraWakeup_Flag		0x68	///*�к����жϱ�־*///
#define C_Enable			0x68		///*ʹ��*///
#define C_Disable			0x00		///*��ֹ*///

#define C_EnterLowPowerTimer_NoUpdate	0x00	/*���͹���ʱ��δ����*/
#define C_EnterLowPowerTimer_Update		0xAA	/*���͹���ʱ���Ѹ���*/

///********macro ��������������********///
#define		C_ReadRamFlay			0   	//��RAM
#define		C_ReadParaFlay			1		//�����ڲ���
#define		C_ReadFlashFlay			2		//��Flash
#define		C_ReadE2Flay			4		//��E2
#define   C_ReadFRAMFlay          5       //������FRAM
#define   C_ReadMCUFlay          3       //��MCU�����Ϣ

#define C_ZeroCurrentOn		1	///*���ߵ�������*///
#define C_ZeroCurrentOff	0	///*���ߵ����ر�*///

///********macro ģ���********///
#define	C_Msg_PowerNetworkMonitoring			0x01		///*��������ж���Ϣ		*///
#define	C_Msg_Write_PowerNetworkMonitoring      0x02		///*��������¼���¼д��Ϣ	*///
#define	C_Msg_EnergyMetering                    0x03		///*���ܼ�����Ϣ			*///
#define	C_Msg_DemandMetering                    0x04		///*����������Ϣ			*///
#define	C_Msg_Communication                     0x05		///*ͨ�Žӿ���Ϣ			*///
#define	C_Msg_SettleAccounts                    0x06		///*������Ϣ				*///
#define	C_Msg_Freeze                            0x07		///*������Ϣ				*///
#define	C_Msg_LoadProfile                       0x08		///*���ɼ�¼��Ϣ			*///
#define	C_Msg_Display                           0x09		///*��ʾ��Ϣ				*///
#define	C_Msg_Deal_RelayStatus                  0x0A		///*�̵���������Ϣ			*///
#define	C_Msg_Deal_MultiRates                   0x0B		///*�����ж���Ϣ			*///
#define	C_Msg_BatteryVoltagleMetering           0x0C		///*��ص�ѹ������Ϣ		*///
#define	C_Msg_VoltageQualifiedRateMetering      0x0D		///*��ѹ�ϸ��ʼ��			*///
#define	C_Msg_Dispatch                          0x0E		///*����					*///
#define	C_Msg_MeterIC							0x0F		///*������Ϣģ��			*///
#define	C_Msg_Card								0x10		///*��������Ϣģ��			*///
#define	C_Msg_BroadcastAddress					0x11		///*�Թ㲥����ʽ������Ϣ	*///
#define	C_Msg_Esam		                        0x12		///*Esam��Ϣ				*///
#define C_Msg_DataProcess						0x13		///*���ݲ���Ϣ				*///
#define C_Msg_CalibrateRC						0x14		///*У׼RC����Ϣ			*///
#define C_Msg_AllLossVoltage					0x15		///*ȫʧѹ��Ϣ:����Ϣֻ��ͣ�绽�ѵ�ʱ��*///
#define C_Msg_DataProcess_External				0x16		///*���ݲ���Ϣ:��չ���ܴ���ÿ�봦��				*///


///********macro д���ݲ㰲ȫ��********///
#define	C_W_SafeFlag				0x68		///*д���ݲ㰲ȫ�ֽ�ֵ                                                                        *///
#define	C_W_SafeFlag_1              0x08		///*ʹ��ʱ�����������ط�������Щֵ���ж�ʱ�жϰ�ȫ�ֽ�Ϊ0x68������ȷ�ϳ���϶������������ط�*///
#define	C_W_SafeFlag_2              0x20		///**///
#define	C_W_SafeFlag_3              0x40		///**///
#define	C_ClearMeterSafeFlag        0x68		///*������尲ȫ�ֽ�ֵ                                                                        *///
#define	C_ClearMeterSafeFlag_1      0x08		///*ʹ��ʱ�����������ط�������Щֵ���ж�ʱ�жϰ�ȫ�ֽ�Ϊ0x86������ȷ�ϳ���϶������������ط�*///
#define	C_ClearMeterSafeFlag_2      0x20		///**///
#define	C_ClearMeterSafeFlag_3      0x40		///**///


///********macro SERR********///
#define	C_SERR_OtherErr				0x01	///*��������*///
#define	C_SERR_ReRecharge			0x02	///*�ظ���ֵ*///
#define	C_SERR_ESAM_VF				0x04	///*ESAM��֤��*///
#define	C_SERR_AF					0x08	///*�����֤ʧ��*///
#define	C_SERR_CNErr				0x10	///*�ͻ���Ų�ƥ��*///
#define	C_SERR_RechargeNumErr		0x20	///*��ֵ������*///
#define	C_SERR_RechargeHoarding		0x40	///*���糬�ڻ�*///
#define	C_SERR_FWAddressErr			0x80	///*��ַ�쳣*///
#define	C_SERR_Meter_Safeguard		0x100	///*������*///

///********macro io********///
///*input io*///
#define	C_KeyUp					0x01		///*�Ϸ���          *///
#define	C_KeyDown           	0x02		///*�·���          *///
#define	C_KeyPrg            	0x03		///*��̼�          *///
#define	C_KeyOpenCover      	0x04		///*�����          *///
#define	C_KeyOpenTerminal   	0x05		///*����β��        *///
#define	C_CheckAuPower      	0x06		///*������Դ���    *///
#define	C_CheckMainPower    	0x07		///*����Դ���      *///
#define	C_Magnetic          	0x08		///*�ų����        *///
#define	C_MeterICIRQ        	0x09		///*����оƬIRQ�ж� *///
#define	C_RelayStatus       	0x0a		///*�̵���״̬���  *///
#define	C_ModuleStatus      	0x0b		///*ģ�鷢��״ָ̬ʾ*///
#define	C_CardStatus        	0x0c		///*�忨״̬���    *///
#define C_Key3s					0x10		///*����3s��Ч		*///
#define	C_InsertCard			0x11		///*�в忨���κο�	*///
#define	C_KeyUpForRelay			0x12		///*�Ϸ�������3s    *///
#define	C_KeyDownForRelay       0x13		///*�·�������3s    *///
#define	C_ExternalRelayStatus   0x14		///*���ü̵���״̬���  *///

#define	C_Valid					0x63		///*�������״̬��Ч*///
#define	C_Invalid				0x6c		///*�������״̬��Ч*///
///*output Urat*///
#define	C_RS485_1				0x01		///*��һ·485*///
#define	C_RS485_2				0x02		///*�ڶ�·485*///
#define	C_IR					0x00		///*����ͨ��*///
#define	C_Module				0x03		///*ģ��ͨ��*///
#define	C_ESAM					0x04		///*ESAM*///
#define	C_Card					0x05		///*Card*///
///*output io*///
#define	C_BackLight				0x21		///*����            *///
#define	C_TripLed           	0x22        ///*��բָʾ��      *///
#define	C_Beep              	0x23        ///*������          *///
#define	C_WarnOut           	0x24        ///*�����̵���      *///
#define	C_MultiFunction			0x25		///*�๦�����      *///
#define	C_FlashPower        	0x26        ///*Flash��Դ����   *///
#define	C_CapCharge         	0x27        ///*�������ݳ�����*///
#define	C_CapDischarge      	0x28        ///*�������ݷŵ����*///
#define	C_WakeUpPower       	0x29        ///*6V��ص�Դ����  *///
#define	C_BattDischarge     	0x2a        ///*6V��ط��ۻ�����*///
#define	C_Relay             	0x2b        ///*���ɿ��ؿ���    *///
#define	C_EventOut           	0x2c        ///*�����ϱ�        *///
#define	C_ModuleReset       	0x2d        ///*ģ�鸴λ        *///
#define	C_ModuleSet         	0x2e        ///*ģ������        *///
#define	C_InfraPower			0x2f		///*������յ�Դ*///
#define	C_EsamPower             0x30		///*ESAM��Դ    *///
#define	C_CardPower             0x31		///*CARD��Դ    *///
#define	C_EsamReset             0x32		///*ESAM��λ    *///
#define	C_CardSck               0x33		///*��ʱ��ʹ��  *///
#define	C_CardReset             0x34		///*����λ      *///
#define	C_MeterICPower          0x35		///*����оƬ��Դ*///


#define	C_On  					0x68		///*�ⲿ�豸��                *///
#define	C_Off                   0x66        ///*�ⲿ�豸�ر�                *///
#define	C_Hold                  0x69        ///*�ⲿ�豸���֣�רָ���ü̵���*///
#define	C_SecondPulse			0x62		///*�๦�ܿ����������*///
#define	C_DemandPulse			0x63		///*�๦�ܿ�������������ź�*///
#define	C_RatePulse				0x64		///*�๦�ܿ����ʱ�η���Ͷ���ź�*///
#define	C_ClosePulse			0x65		///*�๦�ܿ�����رգ�����������źź�ر����*///
#define	C_PowerInit				C_SecondPulse	///*�ϵ��๦�����������ʽ*///

#define	C_RTCLen				0x07		///*��дRTCʱ���ݳ��ȣ��̶�Ϊ7�ֽ�*///
#define	C_LCDLen				0x20		///*LCD���������ֽ���*///
#define	C_DataCodeLen			0x04		///*���ݱ�ʶ���ֽ���*///
#define	C_KillZero1       		0x01		///*��1����*///
#define	C_KillZero2       		0x02		///*��2����*///
#define	C_KillZero3       		0x03		///*��3����*///
#define	C_KillZero4       		0x04		///*��4����*///
#define	C_KillZero5       		0x05		///*��5����*///
#define	C_KillZero6       		0x06		///*��6����*///
#define C_KillZero7				0x07		///*��7����*///
#define	C_KillZero8       		0x08		///*��8����*///
#define C_KillZero9			    0x09		///*��9����*///
#define	C_Notkillzero     		0x68		///*������ *///
#define	C_SF_Err	     		0xff		///*��ʾ�����ַ�*///
/*С��λ��*/
#define C_DotNum_0                              0           /*0λС��*/
#define C_DotNum_1                              1           /*1λС��*/
#define C_DotNum_2                              2           /*2λС��*/
#define C_DotNum_3                              3           /*3λС��*/
#define C_DotNum_4                              4           /*4λС��*/


/*���������ֵ*/
#define C_PowerMax				799999
///*********�����ϱ���غ궨��***********///

#define C_Times_ContralLoopErr    		0		///*���ƻ�·����		*///
#define C_Times_ESAMErr      			1  		///*ESAM����			*///
#define C_Times_InitialCardErr          2 		///*�ڿ���ʼ������		*///
#define C_Times_RTCBatteryErr           3		///*ʱ�ӵ�ع���		*///
#define C_Times_InternalProgramErr      4   	///*�ڲ��������		*///
#define C_Times_MemoryErr               5   	///*�洢������			*///

#define C_Times_RTCErr                 	7		///*ʱ�ӹ���			*///
#define C_Times_PowerBatteryErr         8     	///*ͣ�糭���ع���	*///
#define C_Times_OverDraft      			9		///*͸֧״̬			*///
#define C_Times_OpenMeterCover        	10		///*�����				*///
#define C_Times_OpenTerminalCover     	11		///*����β��			*///
#define C_Times_MagneticCheck     		12		///*�㶨�ų�����		*///
#define C_Times_PowerError     			13		///*��Դ�쳣			*///
#define C_Times_OpenRelay     			14		///*��բ�ɹ�			*///
#define C_Times_CloseRelay     			15		///*��բ�ɹ�			*///

#define C_Times_ALossVoltage    		16		///*Aʧѹ				*///
#define C_Times_ALessVoltage      		17		///*AǷѹ				*///
#define C_Times_AOverVoltage            18		///*A��ѹ				*///
#define C_Times_ALossCurrent            19		///*Aʧ��				*///
#define C_Times_AOverCurrent            20		///*A����				*///
#define C_Times_AOverLoad               21    	///*A����				*///
#define C_Times_APowerReverse           22     	///*A���ʷ���			*///
#define C_Times_ALossPhase              23   	///*A����				*///
#define C_Times_ALessCurrent     		24		///*A����				*///

#define C_Times_BLossVoltage    		32		///*Bʧѹ				*///
#define C_Times_BLessVoltage      		33		///*BǷѹ				*///
#define C_Times_BOverVoltage            34		///*B��ѹ				*///
#define C_Times_BLossCurrent            35		///*Bʧ��				*///
#define C_Times_BOverCurrent            36		///*B����				*///
#define C_Times_BOverLoad               37   	///*B����				*///
#define C_Times_BPowerReverse           38     	///*B���ʷ���			*///
#define C_Times_BLossPhase              39   	///*B����				*///
#define C_Times_BLessCurrent     		40		///*B����				*///

#define C_Times_CLossVoltage    		48		///*Cʧѹ				*///
#define C_Times_CLessVoltage      		49		///*CǷѹ				*///
#define C_Times_COverVoltage            50		///*C��ѹ				*///
#define C_Times_CLossCurrent            51		///*Cʧ��				*///
#define C_Times_COverCurrent            52		///*C����				*///
#define C_Times_COverLoad               53    	///*C����				*///
#define C_Times_CPowerReverse           54      ///*C���ʷ���			*///
#define C_Times_CLossPhase              55   	///*C����				*///
#define C_Times_CLessCurrent     		56		///*C����				*///

#define C_Times_ReversedVoltage    		64		///*��ѹ������			*///
#define C_Times_ReversedCurrent      	65		///*����������			*///
#define C_Times_UnbalancedVoltage       66     	///*��ѹ��ƽ��			*///
#define C_Times_UnbalancedCurrent       67     	///*������ƽ��			*///
#define C_Times_SubPowerOff        		68		///*������Դʧ��		*///
#define C_Times_PowerOff                69   	///*����				*///
#define C_Times_OverDemadn              70    	///*��������			*///
#define C_Times_OverPowerFact           71      ///*������������		*///
#define C_Times_SeriousUnbalancedCurrent 72   	///*�������ز�ƽ��		*///
#define C_Times_TActivePowerReversed     73 	///*���й����ʷ���		*///
#define C_Times_NoVoltage            	74		///*ȫʧѹ				*///

#define C_Times_Program    				80		///*��̷�����			*///
#define C_Times_MeterClear    			81		///*��������			*///
#define C_Times_DemandClear    			82		///*���������			*///
#define C_Times_EventClear    			83		///*�¼������			*///
#define C_Times_ReworkTime    			84		///*�޸�ʱ���			*///
#define C_Times_ReworkTimeInterval    	85		///*�޸�ʱ�α�			*///
#define C_Times_ReworkTimeZone    		86		///*�޸�ʱ����			*///
#define C_Times_ReworkWeekDay    		87		///*�޸�������			*///
#define C_Times_ReworkHoliday    		88		///*�޸Ľڼ���			*///
#define C_Times_ReworkActiveMode    	89		///*�޸��й���Ϸ�ʽ	*///
#define C_Times_ReworkReactiveMode1    	90		///*�޸��޹���Ϸ�ʽ1	*///
#define C_Times_ReworkReactiveMode2    	91		///*�޸��޹���Ϸ�ʽ2	*///
#define C_Times_ReworkSettlemantDay    	92		///*�޸Ľ�����			*///
#define C_Times_ReworkRatesCharge    	93		///*�޸����ʱ�			*///
#define C_Times_ReworkStepPara    		94		///*�޸Ľ��ݱ�			*///
#define C_Times_ReworkKey    			95		///*��Կ���¹�			*///

#define	C_SecondPulseOutput  			0x00	  ///*������*///
#define	C_DemandPulseOutput  			0x01	  ///*������������*///
#define	C_RatePulseOutput    			0x02	  ///*ʱ��Ͷ������*///

/*************������,�޸���Ҫ�޸����� BCD��Hex ��Ҫ�ģ�����*************/
#define C_MaxRatesNum_BCD						0x12	            	/*�������� BCD*/
#define C_MaxRatesNum	    					12	                	/*�������� Hex*/
#define C_RatesNumTol	    					(C_MaxRatesNum+1)		/*�������������*/

/*���ݱ����������ݳ���*/
#define C_StepSettlementLen						0x03					/*1�����ݽ����ղ����ĳ���*/
#define C_StepChargeStartAddr					24						/*���ݲ����н��ݵ�۶�Ӧ����ʼ��ַ*/
#define C_StepSettlementStartAddr				52						/*���ݲ����н��ݽ����ղ�����Ӧ����ʼ��ַ*/
#define C_StepSettlementNum						4						/*�����ݽ����ղ�������*/
#define C_StepSettlementTotalLen				(C_StepSettlementLen * C_StepSettlementNum)					/*1�����ݽ����ղ����ĳ���*/
#define C_StepSettlementDay_MM					2						/*���ݽ��������µ�ƫ��λ��*/

/*************ʱ�������,�޸���Ҫ�޸����� BCD��Hex ��Ҫ�ģ�����*************/
#define C_RatesParmNum	    14	                /*�����ʱ���� HEX*/

/*************�¼������б����������������һ���޸ģ�����*************/
#define C_EventMAXRelatedOAD         60
#define C_EventMAXRelatedOADLen      (C_EventMAXRelatedOAD * 2)	 /*��ȡ�����б����󳤶ȣ�2�ֽ�һ��*C_EventMAXRelatedOAD*/
#define C_FreezeMAXRelatedOAD        96         /*����698������ű����֧�ָ���*/
#define C_698Free_OADTabDataType     6          /*ÿ�ඳ��OAD�б��ʽ��2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*///
#define C_698Free_OADTabLen          (C_FreezeMAXRelatedOAD*C_698Free_OADTabDataType)       /*����698������ű�*/

/*��ȡ�������ݵ���󳤶�*/
#define C_FreezeMAXLen               2000

///*************���ݳ������********************************************///
#define C_NotSupportAOD_Data  	 0xaa       		///*��֧�ֵ�698����OAD����*///
#define C_NotSupportAOD_DataBB   0xbb       		///*1����ģ��д��¼ʱ�������ݲ��������AA C_NotSupportAOD_Data������2���������������ݲ�Ӧ��0xBB*///
#define C_NotSupportAOD_DataCC   0xcc       		///*Ҫ����OAD�б����е�OAD�ڹ����б���ȫ���鲻����־����Ҫ�������ڶ��᳭��������ѭ������ʱ�����*///
#define CL_NotSupportAOD_DataBB	 1			        //���ݳ��ȷ������������ݲ�Ӧ��0xBB��0xBB����1�ֽ�

///*************���ܳ��ȹ���********************************************///
#define C_EnergyPulseLen	        0x05	///*���ݲ�洢�ĵ����������ĳ���*///
#define C_EnergyCommLen		        0x04	///*ͨ�Ŷ�ȡ���ܳ���*///
#define C_AccurateEnergyCommLen		0x05	///*ͨ�Ŷ�ȡ��ȷ���ܳ���*///
#define C_EnergyCommPulseLastLen    0x01	///*ͨ�Ŷ�ȡ����β������*///
#define C_DisEnergyCommPulseLastLen 0x05	///*��ʾ��ȡ����β������*///

#define C_EnergyNature2BCDLen		0x04	/*����2��BCD��2λС�����ܳ���4�ֽ�*/
#define C_EnergyNature4BCDLen		0x08	/*����4��BCD��4λС�����ܳ���8�ֽ�*/
#define C_EnergyNature2HEXLen		0x04	/*����2��HEX��2λС�����ܳ���4�ֽ�*/
#define C_EnergyNature4HEXLen		0x05	/*����4��HEX��4λС�����ܳ���5�ֽ�*/
#define C_EnergyNature4HEXLen_Comm	0x08	/*ͨ������4��HEX��4λС�����ܳ���8�ֽ�*/

/*����¼�*/
#define	ProgOpClock_O	        4
#define	ProgEndTime		        11
#define	ProgDI_O		        20
#define	ProgCrc_O		        (20 + 50)
#define ProgOADLen              CLProgOADGather	/*һ����¼10����־�룬ÿ����־���һ��������0AD����OMD*/
#define	CLProgFixedData			20				/*���4 + ����ʱ��7 + ����ʱ��7 + ����Դ1 + �ϱ�״̬1*/

/*�̵���������*/
#define CLRelayDescrip                  5          /*�̵������������ȣ�5�ֽ�*/
#define CLRelayCurrentState             1          /*�̵���״̬�����ݳ��ȣ�1�ֽ�*/
#define CLRelaySwitchNature             1          /*�̵����������ԣ� ������ʼƫ��*/
#define CLRelayWiringState              1          /*�̵�������״̬�� ������ʼƫ��*/

#define CLRelayUnit                     (CLRelayDescrip + CLRelayCurrentState + CLRelaySwitchNature + CLRelayWiringState)       /*�̵�������״̬�� ������ʼƫ��*/

//698����645����
#define C_Flag03   0x03  ///*DI0Ϊ03*///
#define C_Flag10   0x10  ///*DI0Ϊ10*///
#define C_Flagelse 0x00  ///*����DI0*///
//����¼�698�洢��������ʽΪ��4+7+7+1+1+4*10
#define C_ProgEventHappen  	4  ///*��̼�¼���ݷ���ʱ��ƫ��λ��*///
#define C_ProgEvent			19        ///*��̼�¼���ݹ���OADƫ��λ��*///
#define	CLProgram_Note_645	                 50    	        ///*645��̼�¼���ݳ��ȣ���1-��10��*///
#define	CLProgram_Note_Code_645	             4    	       ///*645��̼�¼�����ߴ��볤��*///
#define CLProgram_Note_698_DataIn              79           ///*698����¼���ȡ����*///

#define CDrive_Report_Mode_645_Judge      0x001F042500DFFD89           ///*645Ĭ�������ϱ����Դ�쳣���㶨�ų�������ǡ�����բ��������ʧѹ��ʧ��������,�������(0x000200200019F400)
                                       ///*+20200227�������ɿ���������ʱ�ӵ�ص�ѹ�ͣ�ͣ�����Ƿѹ������ť�ǣ�Ƿѹ����ѹ�����ʷ��򣬶��࣬��ѹ�����򣬵�ѹ��ƽ�⣬ȫʧѹ��Уʱ���¼����㣬�������㣬���+ʱ�ӹ���
#define CReport_645_Judge_Num    41    //֧�ֵ��¼�������645Ĭ�������ϱ����Դ�쳣���㶨�ų�������ǡ�����բ��������ʧѹ��ʧ��������,������㣩16��+23����ͬ��������+1��ʱ�ӹ���+���й����ʷ���


#define C_pNULL_NoCode   0x00  	/*ָ��Ϊ�գ�����Ҫ���ر�����������*/
typedef struct
{
	ulong32	OAD;	     ///*698OAD*///
	ulong32 DI;          ///*645DI*///
}Str_ParaChange_OADToDI_Table;

//698����645����

///******�����ṹ��********///

typedef struct
{
	uchar8 PowerFlag;	///*�����־�����ڸ�����Ϣ����ģ�������ж��Ƿ���е��籣�棬C_PowerDown��ʾ����׼������͹��ģ�C_PowerOn��ʾ�е�*///
	uchar8 SourceAddr;	///*Դ��Ϣ��*///
	uchar8 DerictAddr;	///*Ŀ����Ϣ��*///
	uchar8 Length;		///*Parameter�ĳ���*///
	uchar8 *Parameter;	///*���������Ȳ���*///
}Str_Msg_Parameter;


typedef struct
{
	uchar8 Deriction;		        /*���ʷ���        */
	long32 ActivePower_TABC[4];		/*��ǰ����ABC�й�����*/
	long32 ReativePower_TABC[4];	/*��ǰ����ABC�޹�����*/
}Str_RealtimePower_Type;

typedef struct
{
    uchar8  FixedData[CLProgFixedData];                           /*��һ����ʶ����ʱ��*/
    uchar8  DI[CProgOADNum][CLProgTypeOADGather];    /*��������10����ʶ��*/
    ushort16 Crc;
}Str_ProgRecord;
typedef struct
{
    uchar8  Opclock[7];             ///*��һ����ʶ����ʱ��*///
    uchar8  OpCode[4];              ///*��һ����ʶ����ʱ�����ߴ���*///
    uchar8  DI[10][4];                 ///*��������10����ʶ��*///
    ushort16 Crc;
}Str_ProgRecord_645;


typedef struct
{
	ulong32	ConectOverTime;			/* ������Ӧ�����ӳ�ʱʱ��*///
	ulong32	ConectOverTime_termal;	/* ������Ӧ�����ӳ�ʱʱ���ն�*///
	ushort16	ProtocolVersion;			/* Э��汾��*///
	ushort16	ClientTxMaxLen;			/* �ͻ�������֡���ߴ�*///
	ushort16	ClientRxMaxLen;			/* �ͻ�������֡���ߴ�*///
	ushort16	ClientAPDUMax;			/* �ͻ������ɴ����APDU�ߴ�*///
	uchar8	ProtocolConformance[8];	/* Э��һ���Կ�*///
	uchar8	FunctionConformance[16];	/* ����һ���Կ�*///
	uchar8	ClientRxMaxLenNum;		/* �ͻ�������֡��󴰿ڳߴ�*///
	uchar8	Com_NO;				/*��ǰӦ�����ӽ���ͨ��*///
	ushort16	CurrentConectAPDULen_Tx;	/* ��ǰ��ЧӦ������Э�̳ߴ�*///
	ushort16	CurrentConectAPDULen_Rx;	/* ��ǰ��ЧӦ������Э�̳ߴ�*///
	uchar8	Com_Right;				/*Ӧ������Ȩ��*///
	ushort16	CRC16;					/**///
}ConectRequest_Type;
///********macro ���ڳ���ģʽ*********///
#define C_FactoryInType     0x01
#define C_FactoryOutType    0x02

#define C_NotClearCurrData	0x00
#define C_ClearCurrData		0x01

///********macro ADC�����־*********///
#define	C_ADC_Iint						0x00	///*ADC��ʼ����־*///
#define	C_ADC_CmpAndJec				0x01	///*ADC�¶Ȳ���ʱ�ӵ�У����*///
#define	C_ADC_Lowpower				0x02	///*ADC�¶Ȳ���ʱ�ӵ�У����*///

#define C_GetADC_On    0x55         //�¶Ȳ�����������
#define C_GetADC_Off   0x00         //�¶Ȳ��������ر�

//RTC�����ж�
#define	C_RTC_ERR				0x86	///*RTC���ϣ�RTC���Ϸ�����*///
#define	C_RTC_OK				0x00	///*RTC������RTC����δ��������*///
#define	C_RTC_ERR_BackTime		0x55	///*RTC�����ұ���ʱ��Ҳ����*///
#define	C_RTCERR_MeterWorkState	0x80	///*�������������1�е�RTC����λ*///

//���ݱ�ʶ�ж�ʹ��
#define		C_O_DI0						0
#define		C_O_DI1						1
#define		C_O_DI2						2
#define		C_O_DI3						3


typedef struct
{
	ushort16 V_usActiveEnergy_T;
	ushort16 V_usActiveEnergy_A;
	ushort16 V_usActiveEnergy_B;
	ushort16 V_usActiveEnergy_C;

	ushort16 V_usReactiveEnergy_T;
	ushort16 V_usReactiveEnergy_A;
	ushort16 V_usReactiveEnergy_B;
	ushort16 V_usReactiveEnergy_C;

	uchar8 V_ucPowerDeriction;				///*���ʷ���*///
}Struct_Energy_Type;


//typedef struct
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
//}Struct_RTC_Adj;


///********macro for message type********///
#define Pt_DisplayStatus			0x01	///*��ʾ״̬�ַ���Ϣ����*///
#define Pt_CodeID					0x02	///*��ʶ����Ϣ����*///
#define Pt_RelayStateFlag			0x03	///*�̵�����ر�־��Ϣ����*///
#define Pt_Dispatch_Timing			0x04	///*���ȶ�ʱ����Ϣ����*///
#define Pt_DemandStatus				0x05	///*���������־��Ϣ����*///
#define Pt_MsgFreezeImmediately		0x06	///*����������Ϣ*///
#define Pt_7DayAdd_FreezeTime		0x07	///*���ն�����Ϣ����*///
#define Pt_SettleAdd_Time			0x08	///*����ʱ����Ϣ����*///
#define Pt_StepSwitchFlag			0x09	///*�����л���Ϣ����*///
#define PT_Msg_UpdataKey_Review		0x0A	///*����*///
#define PT_EventNo					0x0B	///*�¼���¼����Ϣ����*///
#define Pt_HappenTime				0x0C	///*�¼���¼����ʱ����Ϣ����*///
#define Pt_EndTime					0x0D	///*�¼���¼����ʱ����Ϣ����*///
#define Pt_ParaMetersChange			0x0E	///*������йصĲ����޸���Ϣ����*///
#define Pt_Initialization			0x0F	///*��ʼ����Ϣ����*///
#define Pt_FristCheckDayChange		0x10	///*�޸ĵ�һ��������Ϣ����*///
#define PT_CMsg_UpdataKey_Review	0x11	///*ͨ��֪ͨ������Կ��Ϣ*///
#define PT_CMsg_UpdKey_Rv_PWOn		0x12	///*�ϵ��ʼ��*///
#define Pt_Comm_No					0x13	///*ͨ�ŷ��ͽ�������ʱ����Я����ͨ����*///
#define Pt_Dispatch_Key				0x14	///*���Ȱ���������Ϣ����*///
#define Pt_EventClearDI				0x15	///*�¼���¼�����ʶ����Ϣ����*///
#define Pt_VoltageQR				0x16	///*��ѹ�ϸ���ͳ����Ϣ����*///
#define Pt_DisplayID				0x17	///*Һ���鿴��ʾ���ݱ�ʶ����������*///
#define Pt_MeterClear				0x18	///*�������*///
#define Pt_InitialMeterIC			0x19	///*����ģ���ʼ����Ϣ*///
#define	Pt_YearCheckDayChange		0x1A	///*������ձ仯��Ϣ*///
#define	Pt_ResetEsam				0x1B	///*��λEsamģ����Ϣ*///
#define	Pt_CardFlag					0x1C	///*���ر�忨 ��Ϣ����*///
#define Pt_ERRXXDisplay				0x1d	///*�忨�쳣��ʾ��Ϣ*///
#define	Pt_RatePrice				0x1E	///*���·��ʵ����Ϣ*///
#define Pt_CalibrateRC				0x1F	///*У׼RC������Ϣ*///
#define Pt_VRQTimeChange            0x20    /*zlj������ͨ���޸�ʱ�䷢�͸���ѹ�ϸ���ģ��*/
///********macro for message length********///
#define Pt_DisplayStatus_Len			0x03	///*��ʾ״̬�ַ���Ϣ����*///
#define Pt_CodeID_Len					0x04	///*��ʶ����Ϣ����*///
#define Pt_RelayStateFlag_Len			0x01	///*�̵�����ر�־��Ϣ����*///
#define Pt_Dispatch_Timing_Len			0x01	///*���ȶ�ʱ����Ϣ����*///
#define Pt_Dispatch_Timing_Freeze_Len	0x08	///*���ȶ�ʱ�����͸�������Ϣ����*///
#define Pt_DemandStatus_Len				0x01	///*���������־��Ϣ����*///
#define Pt_MsgFreezeImmediately_Len		0x00	///*����������Ϣ*///
#define Pt_7DayAdd_FreezeTime_Len		0x07	///*���ն�����Ϣ����*///
#define Pt_SettleAdd_Time_Len			0x07	///*����ʱ����Ϣ����*///
#define Pt_StepSwitchFlag_Len			0x07	///*�����л���Ϣ����*///   /*zlj,����֮ǰ��6����Ϊ7����Ϊ���Ϊ2�ֽ�*/
#define PT_Msg_UpdataKey_Review_Len		0x01	///*������Կ��Ϣ����*///
#define PT_EventNo_Len					0x01	///*�¼���¼����Ϣ����*///
#define Pt_HappenTime_Len				0x06	///*�¼���¼����ʱ����Ϣ����*///
#define Pt_EndTime_Len					0x06	///*�¼���¼����ʱ����Ϣ����*///
#define Pt_ParaMetersChange_Len			0x01	///*������йصĲ����޸���Ϣ����*///
#define Pt_Initialization_Len			0x00	///*��ʼ����Ϣ����*///
#define Pt_FristCheckDayChange_Len		0x00	///*�޸ĵ�һ��������Ϣ����*///
#define PT_CMsg_UpdataKey_Review_Len	0x00	///*��Կ������Ϣ����*///
#define PT_CMsg_UpdKey_Rv_PWOn_Len		0x00	///*�ϵ��ʼ��������Կ������Ϣ����*///
#define Pt_Comm_No_Len					0x01	///*ͨ�ŷ��ͽ�������ʱ����Я����ͨ����*///
#define Pt_Dispatch_Key_Len				0x01	///*���Ȱ���������Ϣ����*///
#define Pt_EventClearDI_Len				0x04	///*�¼���¼�����ʶ����Ϣ����*///
#define Pt_VoltageQR_Len				0x00	///*��ѹ�ϸ���ͳ����Ϣ����*///
#define Pt_DisplayID_Len				0x0B	///*Һ���鿴��ʾ���ݱ�ʶ�����ݳ��ȣ�4�ֽڱ�ʶ���1�ֽ���ʾ����*///
#define	Pt_MeterClear_Len  				0x00	///*�������*///
#define Pt_InitialMeterIC_Len			0x00	///*����ģ���ʼ����Ϣ����*///
#define Pt_YearCheckDayChange_Len		0x00    ///*�޸�������ղ���*///
#define	Pt_ResetEsam_Len				0x00	///*��λEsamģ����Ϣ����*///
#define	Pt_CardFlag_Len					0x00	///*���ر�忨 ��Ϣ��������*///
#define	Pt_DataProcess_Len				0x00	///*���ݲ� ��Ϣ��������*///
#define Pt_ERRXXDisplay_Len				0x03	///*�忨�쳣��ʾ��Ϣ����*///
#define	Pt_RatePrice_Len				0x00	///*���·��ʵ����Ϣ*///
#define Pt_CalibrateRC_Len				0x00	///*У׼RC������Ϣ����*///
#define Pt_AllLossVoltage_Len			0x00	///*ȫʧѹ������Ϣ����*///
#define Pt_VRQTimeChange_Len            0x0E    /*zlj������ͨ���޸�ʱ�䷢�͸���ѹ�ϸ���ģ�鳤�ȣ��޸�ǰʱ��7�ֽ��޸ĺ�ʱ��7�ֽ�*/
///********macro for Pt_RelayStateFlag********///
#define C_Relay_Close_Direct		0x01		///*ֱ�Ӻ�բ        *///
#define C_Alarm						0x02		///*����            *///
#define C_Alarm_Release				0x03		///*�������        *///
#define C_AlarmOpenRelay			0x04		///*����Ԥ��բ      *///
#define C_Relay_OpenNow				0x05		///*������բ        *///
#define C_KeyDownDelay3s			0x06		///*����3s��Ϣ		*///
#define C_Protect					0x07		///*��ǰ���ڱ���	*///
#define C_NotProtect				0x08		///*��ǰ������		*///
#define C_PurchaseOK				0x09		///*����ɹ�		*///
#define C_Relay_Close_Direct_Init	0x0A		///*��ʼ������ֱ�Ӻ�բ*///

#define	C_VoltageOk		  0x01	///* ��ʾ��ǰ��ѹ��������բ *///
#define	C_VoltageErr		0x02	///* ��ʾ��ǰ��ѹ����������բ *///
///********macro for Pt_DisplayStatus********///
#define C_TwinkleDisplay		0x40	///*��˸��ʾ*///
#define C_AlwaysDisplay			0xC0	///*����*///
#define C_NotDisplay			0x00	///*����ʾ*///

#define C_AxisSign				1  		///*������				*///
#define C_Q1Sign                2       ///*1������ʾ����		*///
#define C_Q2Sign                3       ///*2������ʾ����		*///
#define C_Q3Sign                4       ///*3������ʾ����		*///
#define C_Q4Sign                5       ///*4������ʾ����		*///
//#define C_Step1Sign             6       ///*����1        		*///
//#define C_Step2Sign             7       ///*����2        		*///
//#define C_Step3Sign             8       ///*����3        		*///
//#define C_Step4Sign             9       ///*����4        		*///
//#define C_Rate1Sign             10      ///*����1        		*///
//#define C_Rate2Sign             11      ///*����2        		*///
//#define C_Rate3Sign             12      ///*����3        		*///
//#define C_Rate4Sign             13      ///*����4        		*///
#define C_TSign                 12      ///*�����ַ�T        		*///
#define C_LSign                 13      ///*�����ַ�L        		*///
#define C_GPRSSign              14      ///*���߷���     		*///
#define C_GPRSSignalSign1       15      ///*�ź�ǿ��1    		*///
#define C_GPRSSignalSign2       16      ///*�ź�ǿ��2    		*///
#define C_GPRSSignalSign3       17      ///*�ź�ǿ��3    		*///
#define C_GPRSSignalSign4       18      ///*�ź�ǿ��4    		*///
#define C_ModuleComSign         19      ///*ģ��ͨ�ŷ��� 		*///
#define C_ComSign               20      ///*ͨ�ŵ绰���� 		*///
#define C_ComChannel1Sign       21      ///*ͨ��1����    		*///
#define C_ComChannel2Sign       22      ///*ͨ��2����    		*///
#define C_ProgramEnableSign     23      ///*������֤��Ч   		*///
#define C_HoldUpSign            24      ///*�����֤���� 		*///
#define C_PublicKeySign         25      ///*��Կ����     		*///
#define C_AlarmSign             26      ///*������־     		*///
#define C_ReadCardSign          27      ///*���������ַ�			*///
#define C_DoingSign             28      ///*���С��ַ�		   	*///
#define C_SuccessSign           29      ///*�ɹ�         		*///
#define C_FailSign              30      ///*ʧ��         		*///
#define C_PurchaseSign          31      ///*�빺��       		*///
#define C_OverdrawSign          32      ///*͸֧         		*///
#define C_RealayOpenSign        33      ///*��բ         		*///
#define C_UaSign                34      ///*Ua           		*///
#define C_UbSign                35      ///*Ub           		*///
#define C_UcSign                36      ///*Uc           		*///
#define C_NegativePhaseSign     37      ///*������       		*///
#define C_IaNegativeSign        38      ///*Ia����ǰ��-��			*///
#define C_IaSign                39      ///*Ia           		*///
#define C_IbNegativeSign        40      ///*Ib����ǰ��-��			*///
#define C_IbSign                41      ///*Ib           		*///
#define C_IcNegativeSign        42      ///*Ic����ǰ��-��			*///
#define C_IcSign                43      ///*Ic           		*///
#define C_TimeTable1Sign        44      ///*��һ��ʱ�α� 		*///
#define C_TimeTable2Sign        45      ///*�ڶ���ʱ�α� 		*///
#define C_RTCBatterySign        46      ///*ʱ�ӵ��Ƿѹ 		*///
#define C_PowerBatterySign      47      ///*ͣ�����Ƿѹ 		*///
#define C_HoardingSign			48      ///*���ڻ���־        	*///
#define C_CurrentStep           49      ///*��ǰ�׽���        	*///
#define C_BakStep               50      ///*�����׽�����Ч����	*///
#define C_BackLED               51      ///*����		       	*///
#define C_WarnOutPut            52      ///*�������    		*///
#define C_Beeper                53      ///*������        		*///
#define C_RelayStatusLED        54      ///*��բָʾ��			*///

///********macro for Pt_Dispatch_Timing ********///
#define C_SystemSecondChange	0x01      ///*����ϵͳ��仯			*///
#define C_SystemMinChange		0x02      ///*����ϵͳ���ӱ仯			*///
#define C_SystemHourChange		0x03      ///*����ϵͳСʱ�仯			*///
#define C_SystemDateChange		0x04      ///*����ϵͳ�ձ仯			*///
#define C_SystemMonthChange		0x05      ///*����ϵͳ�±仯			*///
#define C_SystemYearChange		0x0c      ///*����ϵͳ��仯			*///


#define C_SecondChange			0x06      ///*���Ȼ���������仯		*///
#define C_MinChange				0x07      ///*���Ȼ������ķ��ӱ仯		*///
#define C_HourChange			0x08      ///*���Ȼ�������Сʱ�仯		*///
#define C_5MS					0x09      ///*���Ȼ�������5ms			*///
#define C_100MS					0x0A      ///*���Ȼ�������100ms			*///
#define C_HalfSecond			0x0B      ///*���Ȼ�������500ms			*///

/********macro for Pt_DemandStatus********/
#define	C_RewortDemandInternal		0x10	/*�޸������������*/
#define	C_MeterClear				0x11	/*�������*/
#define	C_DemandClear				0x12	/*��������*/
#define	C_Settlement				0x13	/*��������*/
#define	C_RatesChanged				0x14	/*���ʸı�*/
#define	C_DemandPowerUp				0x15	/*�ϵ�*/
#define	C_DataFreeze				0x16	/*���ն���*/
#define	C_Settlement_ReSettle_Day1	0x17	/*�޸ĵ�һ������*/

///********macro for Pt_StepSwitchFlag********///
#define	C_Step_MToY					0X16	///*�µ����л�*///
#define	C_Step_YToM					0X17	///*�굽���л�*///
#define	C_Step_YToY					0X18	///*�굽���л�*///

#define	C_Step_SetttleChange	    0x19	/*���ݽ����л�*/
///********macro for communication********///
#define C_ContinueReceive			0x30	///*��������*///
#define C_AbortReceive				0x31	///*�˳�����*///
#define C_CorrectFrame				0x32	///*�յ���ȷ֡*///

#define C_ContinueTransmit			0x33	///*��������*///
#define C_AbortTransmit				0x34	///*�˳�����*///
#define	C_AbortTransmit_SetBPS		0x35	///*����BPSӦ��������˳�����*///

#define		C_bps_38400					0x80	///*������38400*///
#define		C_bps_19200					0x40	///*������19200*///
#define		C_bps_9600					0x20	///*������9600*///
#define		C_bps_4800					0x10	///*������4800*///
#define		C_bps_2400					0x08	///*������2400*///
#define		C_bps_1200					0x04	///*������1200///
#define		C_bps_600					0x02	///*������600*///
#define		C_bps_300					0x01	///*������300*///
#define     C_bps_Error                 0xFF    ///*����Ĳ�����*///

///*698�����ʶ�Ӧ��������*///
#define		C_bps_38400_698					0x08	///*������38400*///
#define		C_bps_19200_698					0x07	///*������19200*///
#define		C_bps_9600_698					0x06	///*������9600*///
#define		C_bps_4800_698					0x04	///*������4800*///
#define		C_bps_2400_698					0x03	///*������2400*///
#define		C_bps_1200_698					0x02	///*������1200///
#define		C_bps_600_698					0x01	///*������600*///
#define		C_bps_300_698					0x00	///*������300*///

#define		C_CommDataLen7				0x07///*word lenth,7bits*///
#define		C_CommDataLen8				0x08///*word lenth,8bits*///

#define		C_parity_None				0x00///*no parity*///
#define		C_parity_Even				0x02///*even parity*///
#define		C_parity_Odd				0x01///*odd parity*///

#define		C_SerStp_1					0x01///*one stop bit*///
#define		C_SerStp_2					0x02///*twe stop bit*///

///********macro for Pt_ParaMetersChange********///
#define		C_ReworkTime				0x35	///*rework time*///
#define		C_ReDemand_Cycle  			0x36	///*rework demand interval parameter*///
#define		C_ReMultiRatesParm			0x37	///*rework time consumption parameters*///
#define		C_ReSettle_Day1				0x38	///*rework the first settlement*///
#define		C_ReworkWarningPara			0x39	///*rework local warning parameters*///

///********macro for Relay contral module********///
#define		C_Relay_Open_comm                   0x1A	///*��բ*///
#define		C_Relay_Close_Allow_comm            0x1B    ///*��բ����*///
#define		C_Relay_Close_Direct_comm           0x1C    ///*������բ*///
#define		C_AlarmOpenRelay_Allow_comm         0x1E    ///*��բ���Զ��ָ�Ϊ������բ*///
#define		C_AlarmOpenRelay_Direct_comm        0x1D    ///*��բ���Զ��ָ�Ϊ��բ����*///
#define		C_Alarm_comm                        0x2A    ///*Զ�̱���*///
#define		C_Alarm_Release_comm                0x2B    ///*Զ�̱������*///
#define		C_Protect_Current_comm              0x3A    ///*����*///
#define		C_Protect_Current_Release_comm		0x3B    ///*������*///

#define 	C_Relay_Close_Direct_Status			0x0001	///*ֱ�Ӻ�բ                   *///
#define 	C_Relay_Close_Allow_Status			0x0002	///*�����բ                   *///
#define 	C_Relay_Open_Status					0x0004	///*ֱ����բ                   *///
#define 	C_Relay_DelayOpen_Time_Status		0x0008	///*��ʱ��բ����բ��ʱʱ���0��*///
#define 	C_AlarmOpenRelay_Status				0x0010	///*��բ�Զ��ָ�               *///
#define 	C_Relay_DelayOpen_Current_Status	0x0020	///*��ʱ��բ���������         *///
#define 	C_Protect_Current_Status			0x0100	///*����                       *///
#define 	C_Protect_Current_Release_Status	0x0200	///*������                   *///
#define 	C_Alarm_Status						0x0400	///*����                       *///
#define 	C_Alarm_Release_Status				0x0800	///*�������                   *///

#define		C_Meter_Safeguardfailure			0x0001	///* ������  *///
#define		C_MACError_failure					0x0002	///* MAC����  *///
#define		C_PasswordError_failure				0x0004	///* ������δ��Ȩ  *///
#define		C_AuthOverTime_failure				0x0008	///* �����֤��ʱ  *///
#define		C_ActTimeUnvalid_failure			0x0010	///* ִ��ʱ����Ч  *///
#define		C_Protect_Openfailure				0x0020	///*��բʧ�ܣ����磩           *///
#define		C_Protect_AlarmOpenfailure			0x0040	///*��բ�Զ��ָ�ʧ�ܣ����磩   *///
#define		C_TimeUnvalid_AlarmOpenfailure		0x0080	///*��բ�Զ��ָ�����ʱ����Ч   *///
#define		C_RelayOpen_OpenAlarmfailure		0x0100	///*��բ�Զ��ָ�ʧ�ܣ���բ��   *///


///********macro for EventRecord********///
#define		C_TotalVoltageLoseEventNo			0x00	///*ȫʧѹ*///
#define		C_ACPowerFailEventNo				0x01	///*������Դʧ��*///
#define		C_PowerfailEventNo					0x02	///*����*///
#define		C_OpenMeterCoverEventNo				0x03	///*�����*///
#define		C_OpenTerminalCoverEventNo			0x04	///*����ť��*///
#define		C_MagneticCheckEventNo				0x05	///*�㶨�ų�����*///
#define		C_PowerAbnormalEventNo				0x06	///*��Դ�쳣*///
#define		C_OverForwardActiveEventNo			0x07	///*�����й���������*///
#define		C_OverReverseActiveEventNo			0x08	///*�����й���������*///
#define		C_1OverIdleDemandEventNo			0x09	///*1�����޹���������*///
#define		C_2OverIdleDemandEventNo			0x0A	///*2�����޹���������*///
#define		C_3OverIdleDemandEventNo			0x0B	///*3�����޹���������*///
#define		C_4OverIdleDemandEventNo			0x0C	///*4�����޹���������*///
#define		C_AlossvoltageEventNo				0x0D	///*A��ʧѹ*///
#define		C_BlossvoltageEventNo				0x0E	///*B��ʧѹ*///
#define		C_ClossvoltageEventNo				0x0F	///*C��ʧѹ*///
#define		C_ALessvoltageEventNo				0x10	///*A��Ƿѹ*///
#define		C_BLessvoltageEventNo				0x11	///*B��Ƿѹ*///
#define		C_CLessvoltageEventNo				0x12	///*C��Ƿѹ*///
#define		C_AOvervoltageEventNo				0x13	///*A���ѹ*///
#define		C_BOvervoltageEventNo				0x14	///*B���ѹ*///
#define		C_COvervoltageEventNo				0x15	///*C���ѹ*///
#define		C_ALossphaseEventNo					0x16	///*A�����*///
#define		C_BLossphaseEventNo					0x17	///*B�����*///
#define		C_CLossphaseEventNo					0x18	///*C�����*///
#define		C_ReversephaseVoltageEventNo		0x19	///*��ѹ������*///
#define		C_ReversephaseCurrentEventNo		0x1A	///*����������*///
#define		C_UnbanlanceVoltageEventNo			0x1B	///*��ѹ��ƽ��*///
#define		C_UnbanlanceCurrentEventNo			0x1C	///*������ƽ��*///
#define		C_ALosscurrentEventNo				0x1D	///*A��ʧ��*///
#define		C_BLosscurrentEventNo				0x1E	///*B��ʧ��*///
#define		C_CLosscurrentEventNo				0x1F	///*C��ʧ��*///
#define		C_AOvercurrentEventNo				0x20	///*A�����*///
#define		C_BOvercurrentEventNo				0x21	///*B�����*///
#define		C_COvercurrentEventNo				0x22	///*C�����*///
#define		C_AFailcurrentEventNo				0x23	///*A�����*///
#define		C_BFailcurrentEventNo				0x24	///*B�����*///
#define		C_CFailcurrentEventNo				0x25	///*C�����*///
#define		C_TReversecurrentEventNo			0x26	///*�ܹ��ʷ���*///
#define		C_AReversecurrentEventNo			0x27	///*A�๦�ʷ���*///
#define		C_BReversecurrentEventNo			0x28	///*B�๦�ʷ���*///
#define		C_CReversecurrentEventNo			0x29	///*C�๦�ʷ���*///
#define		C_AOverloadEventNo					0x2A	///*A�����*///
#define		C_BOverloadEventNo					0x2B	///*B�����*///
#define		C_COverloadEventNo					0x2C	///*C�����*///
#define		C_OverpowerfactEventNo				0x2D	///*�ܹ�������������*///
#define		C_AOverpowerfactEventNo				0x2E	///*A�๦������������*///
#define		C_BOverpowerfactEventNo				0x2F	///*B�๦������������*///
#define		C_COverpowerfactEventNo				0x30	///*C�๦������������*///
#define		C_SUnbanlanceCurrentEventNo			0x31	///*�������ز�ƽ��*///

///********698�¼��ϱ�����macro for EventRecord********///
#define		C_MeterFaEventNo				0x32	///*����оƬ����*///
#define		C_ClockFaEventNo				0x33	///*ʱ�ӹ���*///
#define     C_NeutralCurrentAbnormalEventNo 0x34	///*���ߵ����쳣�¼���*///

///*--------�޿�ʼ����״̬���¼�,���ɿ�����������--------------------------------------*///
#define		C_ProgramEventNo				0x35	///*���*///
#define		C_TolClearEventNo				0x36	///*�������*///
#define		C_DemandClearEventNo			0x37	///*��������*///
#define		C_EventClearEventNo				0x38	///*�¼�����*///
#define		C_AdjTimeEventNo				0x39	///*Уʱ*///
#define		C_ProgPTEventNo					0x3A	///*ʱ�α���*///
#define		C_ProgPZEventNo					0x3B	///*ʱ������*///
#define		C_ProgWReEventNo				0x3C	///*�����ձ��*///
#define		C_ProgSettDEventNo				0x3D	///*�����ձ��*///
#define		C_RelayOpenEventNo				0x3E	///*��բ*///
#define		C_RelayCloseEventNo				0x3F	///*��բ*///
#define		C_ProgHolEventNo				0x40	///*�ڼ��ձ��*///
#define		C_ProgAcCEventNo				0x41	///*�й���Ϸ�ʽ���*///
#define		C_ProgReCEventNo				0x42	///*�޹���Ϸ�ʽ���*///
#define		C_ProgTParaEventNo				0x43	///*���ʲ�������*///
#define		C_ProgLadEventNo				0x44	///*���ݱ���*///
#define		C_Key_UpdateEventNo				0x45	///*��Կ����*///
#define		C_AbnorCEventNo					0x46	///*�쳣�忨*///
#define		C_BuyCurrEventNo				0x47	///*����*///
#define		C_ReturnMoneyEventNo			0x48	///*�˷�*///
#define		C_RelayFaEndEnEventNo			0x49	///*���ɿ�������*///
#define     C_ESAMErroEventNo               0x4A    ///*ESAM��*///
#define     C_RTCBatLowVolEventNo           0x4B    ///*ʱ�ӵ�ص�ѹ��*///
#define     C_MemoryCorrEventNo             0x4C    ///*�洢����*///
#define     C_PowerBatLowVolEventNo         0x4D    ///*ͣ�糬���ص�ѹ��*///
#define     C_OverdraftEventNo              0x4E    ///*͸֧*///
#define     C_CardErrorEventNo              0x4F    ///*�ڿ���ʼ������*///
#define     C_ProgrammErrorEventNo          0x50    ///*�ڲ��������*///
#define     C_SoftIJProgEventNo				0x51	///*��IJ���*///
#define     C_LawlessCardEventNo			0x52	///*�Ƿ��忨*///
#define     C_BroadcastTimeEventNo			0x53	///*�㲥Уʱ�¼���*///
#define     C_BroadTimeAbnormalEventNo		0x54	///*�㲥Уʱ�쳣�¼���*///
#if 0
#define     C_ExternalRelayOpenEventNo		0x55	///*���ü̵��������źŶ�*///
#define     C_ExternalRelayCloseEventNo		0x56	///*���ü̵��������ź�ͨ*///
#endif
///********macro LoadProfile********///
#define C_FirstFrame			0x00		///*��������������һ֡*///
#define C_OtherFrame			0xAA		///*�������������ǵ�һ֡*///
#define C_Msg_LoadReadEarlyData        0xFF   ///*����14�淶���ɼ�¼ģ�飬�������¼���ݱ�־*///
///********macro Security********///
#define	C_Security_Null							0xff00+C_NULL
#define	C_Security_OverTime						0xff68						///*Esam/Card������ʱ*///
#define C_Security_Err							0xff00+C_Error				///*Esam/Card�����쳣*///
#define C_Security_MaxLenErr					0xff00+C_MaxResponseLen_ERR	///*Esam/Card������������󳤶ȴ���*///
#define C_Security_ProcessOk					0x6100		///*��������61XX*///
#define C_Security_CommandOk					0x9000		///*����ִ�гɹ�*///
#define C_Security_CmdNotExist					0x6d00		///*INS��֧��*///
#define C_Security_CLACmdTypeFault				0x6e00		///*CLA��֧��*///
#define C_Security_TimeOut						0x6907		///*timer��ʱ*///
#define C_Security_InvalidFile					0x6283		///*ѡ����ļ���Ч*///
#define C_Security_AuthenFailed					0x6300		///*��֤ʧ��*///
#define C_Security_VerifyFailed					0x63c0		///*��֤ʧ�ܣ�63cX*///
#define C_Security_ExecutingError 				0x6400		///*ִ�г���*///
#define C_Security_E2Damage						0x6581		///*E2��*///
#define C_Security_LcLengthError				0x6700		///*Lc���ȴ���*///
#define C_Security_CLAError						0x6900		///*CLA�������ļ�����Ҫ��*///
#define C_Security_CmdNotReceiving				0x6901		///*�������*///
#define C_Security_CmdNotCompatible				0x6981		///*�������ļ��ṹ������*///
#define C_Security_NotMeetSafety				0x6982		///*�����㰲ȫ״̬*///
#define C_Security_AuthMethodLocking			0x6983		///*��֤��������*///
#define C_Security_ReferenceDataInvalid			0x6984		///*����������Ч*///
#define C_Security_ConditionNotSatisfied		0x6985		///*ʹ������������*///
#define C_Security_CurrentFileNotSelected		0x6986		///*û��ѡ��ǰ�ļ�*///
#define C_Security_SafetyDataIncorrect			0x6988		///*��ȫ�����������ȷ*///
#define C_Security_MacErr						0x6989		///*MACУ���*///
#define C_Security_DomainParaIncorrect			0x6a80		///*�������������ȷ*///
#define C_Security_FunctionNotSupported			0x6a81		///*���ܲ�֧��*///
#define C_Security_FileNotFound					0x6a82		///*δ�ҵ��ļ�*///
#define C_Security_RecordNotFound				0x6a83		///*δ�ҵ���¼*///
#define C_Security_RecordSpaceFull				0x6a84		///*��¼�ռ�����*///
#define C_Security_LcAndTLVNotMatch				0x6a85		///*Lc��TLV�ṹ��ƥ��*///
#define C_Security_ParaP1AndP2NotCorrect		0x6a86		///*����P1/P2����ȷ*///
#define C_Security_ReferenceDataNotFound		0x6a88		///*δ�ҵ���������*///
#define C_Security_ParameterError				0x6b00		///*��������*///
#define C_Security_LeLengthError				0x6c00		///*Le���ȴ���*///
#define C_Security_DataInvalid					0x6f00		///*������Ч*///
#define C_Security_MACInvalid					0x9302		///*MAC��Ч*///
#define C_Security_AppLocked					0x9303		///*Ӧ�ñ���������*///
#define C_Security_AmountLess					0x9401		///*����*///
///********macro for timer********///
#define C_StartTimer							0x68		///*������ʱ*///
#define C_GetTimer								0x97		///*��ȡ��ʱ*///
///********macro for public.c********///
#define CL_Internal_Version				8					/* �ڲ��ͺų���8�ֽ� */
///********macro ********///

typedef struct
{
         ulong32	V_ulOAD;
         //ulong32	V_ul645DI;
         uchar8		V_uc645Length;
		 uchar8		V_uc698Type;
		 uchar8		V_uc698NextNum;
		 uchar8		V_uc698NextType;
		 uchar8     V_uc698RateNumMethod;  /*2020���ӣ��Ƿ���Ҫ�������жϵķ�������Ҫ��C_NeedRateNum_FF��C_NeedRateNum������Ҫ��C_NoRateNum*/
}Struct_FrozenConvert_Type;
#define C_NeedRateNum_FF         0x00	/*��Ҫ���ݿ��жϷ�����+1���磺����й��������ݿ飬�����й��������ݿ�*/
#define C_NeedRateNum            0x01	/*��Ҫ�жϷ��������磺����й��ܵ��ܣ�*/
#define C_NeedRateNumPrice_FF    0x02	/*��Ҫ�ж����ݿ���������磺���ʵ�����ݿ�*/
#define C_NeedRateNumPrice       0x03	/*��Ҫ�жϷ��������磺���ʵ��*/
#define C_NoRateNum              0x04	/*����Ҫ�жϷ�����*/

#define C_RateNumError           0x86	/*����������־*/
#define C_RateNumOK              0x68	/*������δ����־*/

#define C_ReadRecord_Hap         0x01	/*����¼�ͣ�����*/
#define C_ReadRecord_End         0x02	/*����¼�ͣ�����*/

#define CLEventDegree			 4	    /*�¼���ų���*/
#define CLEventHappenTime		 CLDate_Time	    /*�¼�����ʱ�䳤��*/
#define CLEventEndTime			 CLDate_Time	    /*�¼�����ʱ�䳤��*/
#define CLEventSource			 1	    /*�¼�����Դ����*/
#define CLEventReport			 1	    /*�¼��ϱ�״̬����*/
///***************�������Ͷ���**************///
#define		C_array						1
#define		C_structure					2
#define		C_bool						3
#define		C_bit_string					4
#define		C_double_long				5
#define		C_double_long_unsigned		6
#define		C_octet_string				9
#define		C_visible_string				10
#define		C_UTF8_string				12
#define		C_integer					15
#define		C_long						16
#define		C_unsigned					17
#define		C_long_unsigned				18
#define		C_long64					20
#define		C_long64_unsigned			21
#define		C_enum						22
#define		C_float32					23
#define		C_float64					24
#define		C_date_time					25
#define		C_date						26
#define		C_time						27
#define		C_date_time_s				28
#define		C_OI						80
#define		C_OAD						81
#define		C_ROAD						82
#define		C_OMD						83
#define		C_TI						84
#define		C_TSA						85
#define		C_MAC						86
#define		C_RN						87
#define		C_Region					88
#define		C_Scaler_Unit				89
#define		C_RSD						90
#define		C_CSD						91
#define		C_MS						92
#define		C_SID						93
#define		C_SID_MAC					94
#define		C_COMDCB					95
#define		C_RCSD						96
#define		C_Ladder_Table				252	    /*���ݱ�����*/

#define		C_TypeLen				    1       /*���ͳ��ȣ�1�ֽ�*/

#define		C_TZone					    0x68
#define		C_SettleDay					0x86


#define		C_645					    0x68
#define		C_698						0x86

/********************���������桢�ٶ���**********************/
#define		C_True						0
#define		C_Flase						1

//********************************************************************************************************************
///*�෵�ش������ͺ궨��*///
#define     C_OK_DAR						0 	///* �ɹ� *///
#define     C_HardWareInvalid_DAR			1	///* Ӳ��ʧЧ*///
#define     C_TempInvalid_DAR				2 	///* ��ʱʧЧ *///
#define     C_RWForbid_DAR				3 	///* �ܾ���д *///
#define     C_ObjectUndefine_DAR			4 	///* ����δ���� *///
#define     C_ObjectTypeErr_DAR			5	 ///* ����ӿ��಻����*///
#define     C_ObjectNotExist_DAR			6 	///* ���󲻴��� *///
#define     C_TypeErr_DAR					7 	///* ���Ͳ�ƥ��*///
#define     C_OverStep_DAR				8 	///* Խ��*///
#define     C_DataBlockDisable_DAR		9 	///* ���ݿ鲻���� *///
#define     C_FrameTransmitrEnd_DAR		10	///* ��֡������ȡ�� *///
#define     C_FrameTransmitrInvalid_DAR	11	///* �����ڷ�֡����״̬ *///
#define     C_WriteBlockEnd_DAR			12	///* ��дȡ�� *///
#define     C_WriteBlockInvalid_DAR		13	///* �����ڿ�д״̬ *///
#define     C_BlockNumInvalid_DAR			14	///* ���ݿ������Ч *///
#define     C_Unauthorized_DAR			15	///* ������δ��Ȩ *///
#define     C_Baud_NotModified_DAR		16	///* ͨ�����ʲ����޸� *///
#define     C_SeasonNum_OV_DAR			17	///* ��ʱ������ *///
#define     C_PeriodNum_OV_DAR			18	///* ��ʱ������*///
#define     C_RateNum_OV_DAR			19	///* �������� *///
#define     C_SCMismatch_DAR				20	///* ��ȫ��֤��ƥ��*///
#define     C_ReRecharge_DAR				21	///* �ظ���ֵ *///
#define     C_ESAMErr_DAR				22	///* ESAM��֤ʧ�� *///
#define     C_SCErr_DAR					23	///* ��ȫ��֤ʧ�� *///
#define     C_CNMismatch_DAR				24	///* �ͻ���Ų�ƥ�� *///
#define     C_RechargeNumErr_DAR			25	///* ��ֵ������ *///
#define     C_RechargeHoarding_DAR		26	///* ���糬�ڻ�*///
#define     C_FWAddressErr_DAR			27	///* ��ַ�쳣 *///
#define     C_SymmetryDecodeErr_DAR		28	///* �Գƽ��ܴ��� *///
#define     C_DissymmetryDecodeErr_DAR	29	///* �ǶԳƽ��ܴ��� *///
#define     C_SignatureErr_DAR				30	///* ǩ������ *///
#define     C_MeterSafeguard_DAR			31	///* ���ܱ���� *///
#define     C_TimeLabelInvalid_DAR		32	///* ʱ���ǩ��Ч *///
#define     C_RequestTimeOut_DAR			33	///* ����ʱ *///
#define     C_OtherErr_DAR				255	///* ���� *///
//********************************************************************************************************************
//***********************************�¼���¼���������/�������******************************************************
//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
/////////////////////////////////////////////*OIB����*//////////////////////////////////////////
#define CLoss_Vol_OIB      			0x00	///*698-ʧѹ*///
#define CLow_Vol_OIB				0x01	///*698-Ƿѹ*///
#define COver_Vol_OIB             	0x02    ///*698-��ѹ*///
#define CBreak_Vol_OIB             	0x03    ///*698-����*///
#define CLoss_Curr_OIB           	0x04    ///*698-ʧ��*///
#define COver_Curr_OIB           	0x05    ///*698-����*///
#define CBreak_Curr_OIB           	0x06    ///*698-����*///
#define CTrend_Rev_OIB            	0x07    ///*698-��������*///
#define COver_Lo_OIB             	0x08    ///*698-����*///
#define CPos_De_Over_OIB  			0x09    ///*698-���ܱ������й����������¼�*///
#define CRe_De_Over_OIB 			0x0A    ///*698-���ܱ����й����������¼�*///
#define CRe_ReDe_Over_OIB        	0x0B	///*698-���ܱ��޹����������¼�*///
#define CPFactorT_Over_OIB          0x3B	///*698-���ܱ��������������¼�*///
#define CAll_Loss_Vol_OIB           0x0D    ///*698-���ܱ�ȫʧѹ�¼�*///
#define CAux_Pow_Down_OIB          	0x0E    ///*698-���ܱ�����Դʧ���¼�*///
#define CRevPS_Vol_OIB              0x0F    ///*698-���ܱ��ѹ�������¼�*///
#define CRevPS_Curr_OIB      		0x10    ///*698-���ܱ�����������¼�*///
#define CPow_Down_OIB               0x11    ///*698-���ܱ�����¼�*///
#define CProgram_OIB               	0x12    ///*698-���ܱ����¼�*///
#define CTol_Clear_OIB            	0x13    ///*698-���ܱ������¼�*///
#define CDe_Clear_OIB             	0x14    ///*698-���ܱ����������¼�*///
#define CEven_Clear_OIB          	0x15    ///*698-���ܱ��¼������¼�*///
#define CAdjTime_OIB            	0x16    ///*698-���ܱ�Уʱ�¼�*///
#define CProgPT_OIB             	0x17    ///*698-���ܱ�ʱ�α����¼�*///
#define CProgTZ_OIB              	0x18    ///*698-���ܱ�ʱ�������¼�*///
#define CProgWRe_OIB                0x19    ///*698-���ܱ������ձ���¼�*///
#define CProgSettD_OIB            	0x1A    ///*698-���ܱ�����ձ���¼�*///
#define COpenW_OIB               	0x1B    ///*698-���ܱ����¼�*///
#define COpenCW_OIB               	0x1C    ///*698-���ܱ���ť���¼�*///
#define CNoBal_Vol_OIB              0x1D    ///*698-���ܱ��ѹ��ƽ���¼�*///
#define CNoBal_Curr_OIB           	0x1E    ///*698-���ܱ������ƽ���¼�*///
#define CRelayOpen_OIB             	0x1F    ///*698-���ܱ���բ�¼�*///
#define CRelayClose_OIB          	0x20    ///*698-���ܱ��բ�¼�*///
#define CProgHol_OIB              	0x21    ///*698-���ܱ�ڼ��ձ���¼�*///
#define CProgAcC_OIB              	0x22    ///*698-���ܱ��й���Ϸ�ʽ����¼�*///
#define CProgReC_OIB                0x23    ///*698-���ܱ��޹���Ϸ�ʽ����¼�*///
#define CProgTPara_OIB            	0x24    ///*698-���ܱ���ʲ��������¼�*///
#define	CProgLad_OIB                0x25    ///*698-���ܱ���ݱ����¼�*///
#define CKey_Update_OIB           	0x26    ///*698-���ܱ���Կ�����¼�*///
#define CAbnorC_OIB					0x27    ///*698-���ܱ��쳣�忨�¼�*///
#define CBuyCurr_OIB                0x28	///*698-���ܱ����¼�*///
#define CReturn_M_OIB              	0x29	///*698-���ܱ��˷��¼�*///
#define CConM_OIB              		0x2A	///*698-���ܱ�㶨�ų������¼�*///
#define CRelayFa_OIB              	0x2B	///*698-���ܱ��ɿ��������¼�*///
#define CPowerFa_OIB              	0x2C	///*698-���ܱ��Դ�쳣�¼�*///
#define CSevNoBal_Curr_OIB          0x2D	///*698-���ܱ�������ز�ƽ���¼�*///
#define	CClock_FaultState_OIB		0x2E	///*698-���ܱ�ʱ�ӹ����¼�*///
#define	CMeteringChipFault_OIB		0x2F	///*698-���ܱ����оƬ�����¼�*///
#define CBroadcastTime_OIB          0x3C    ///*698-���ܱ�㲥Уʱ�¼�*///
#define CNeutralCurrentAbnormal_OIB 0x40    ///*698-���ܱ����ߵ����쳣�¼�*///
#define CBroadTimeAbnormal_OIB      0x51    ///*698-���ܱ�㲥Уʱ�¼�*///

#define	C_WriteEventRecord 	0x68	///*д�¼���¼*///
#define	C_ReadDate 			0x86	///*������д���ݲ�*///
#define	C_NeedWriteEventRecord	0xAA	///*��д�ܵı�̼�¼?///
#define	C_NeedWrite645EventRecord	0xBB	///*д645�ܵı�̼�¼//

#define	C_Read							0x01		///*��ȡ*///
#define	C_SetUp							0x02		///*����*///
#define	C_Operation						0x04		///*����*///

///********698�����ϱ��¼���������********///
#define	C_Happen_EventReport	0x68	///*�¼�����*///
#define	C_End_EventReport	0x66	///*�¼��ָ�*///
#define C_EventTableDefaultVal	 0	///*�¼������ϱ�Ĭ��ֵ                *///

#define	C_ReportChannel1  	C_RS485_1   ///*ͨ��1*///
#define	C_ReportChannel2  	C_RS485_2   ///*ͨ��2*///
#define	C_ReportChannel3  	C_Module    ///*ͨ��3*///
//#define	C_ReportChannel4  	0x88        ///*ͨ��4*///
#define	C_ReportChannel4  	C_IR        ///*ͨ��4,���ⲻ֧��*///
#define	C_ReportChannelAll	0xAA        ///*4��ͨ��������*///
#define	C_ReportChannelNum  0x04///*4��ͨ��*///

#define C_ReadRecord		0x68///*����¼����*///
#define	C_ReadOther			0x86///*����������*///


#define C_ReportState		0x68///*�¼����ϱ�*///
#define C_ConfirmState		0x86///*�¼����ϱ���ȷ��*///

#define C_NewReport  	0x68///*�����¼��б�*///
#define C_DeletReport	0x86///*ɾ���¼��б�*///
#define C_OADError      0xEEEEEEEE///*�¼�OAD����*///
#define C_BitError      0xEE       ///*�������״̬��8 OAD����*///

typedef struct
{
	uchar8 EventNo;				/*�¼�����*/
	uchar8 StatusBit;			/*�Ƿ���Ҫ�ж��ϱ���־��0����Ҫ��1��Ҫ*/
    ushort16 OIBANature;		/*0IB������*/
	//ulong32 EventModeDI;		/*�¼���Ӧģʽ��DI*/
	//ulong32 EventReportDI;	/*�¼���Ӧ�ϱ����DI*/
	//uchar8 EventIB;			/*IB*/
}Str_698EventReport_Type;		/*698�����ϱ��¼���Ӧ���ṹ��*/


typedef  struct
{
    ulong32 *pV_ulROAD;       /*�׵�ַ��Ӧ��ȡ����OAD���������ݵ���ȡΪ��¼��Ϊ����OAD�б�*/
    uchar8 *pV_ucRST;         /* pV_ucRST[0]��ȡ��ʽ��1����ʱ���ȡ��2���������ȡ��9��ȡ��N�Σ�pV_ucRST[1]~ pV_ucRST[N]Ϊ��Ӧ�����Ĳ�������Ϊ����1��2��������4�ֽ�OAD+ʱ�䣬����9Ϊ1�ֽ���n��
                            ����ȡΪ����ʱ�ò�����Ч��������0xFF,���ڶ�ȡ645���ɼ�¼��ָ��ʱ��7�ֽ�pV_ucRST[1]~ pV_ucRST[8]��ָ��ʱ����ȡ��������pV_ucRST[9]*/
    ushort16 V_usROAD_Num;    /*0��ʾ�޹���OAD����������ȡ��¼*/
    uchar8 V_ucReadMode;      /*1��ģ���ڲ�ʹ�ã�2��ͨ�Ŷ�ȡ��3����ʾ��ȡ*/
    uchar8 V_ucChannelNo;     /*ͨ���ţ���ͨ�Ŷ�ȡʱΪ0xFF*/
}Str_Read_T;/*��¼�ͽӿڲ����ṹ��*/

#define C_OtherMode			1		/*ģ���ڲ�ʹ��*/
#define C_ComMode			2		/*ͨ�Ŷ�ȡ*/
#define C_DisMode			3		/*��ʾ��ȡ*/

#define C_RST_Method_O			0		/*��ȡ����ƫ��*/
#define C_RST_OADOrNum_O		1		/*��ȡ����������������OAD�׵�ַ*/
#define C_RST_Timer1_O			5		/*��ȡ����1/2 ��һ��ʱ��ƫ���׵�ַ*/
#define C_RST_Timer2_O			12		/*��ȡ����2 ��һ��ʱ��ƫ���׵�ַ*/
#define C_RST_TIInter_O			19		/*��ȡ����2 TIʱ����ƫ���׵�ַ*/

typedef  struct
{
    ushort16 *pV_usEncode;  /*��ȡ���ݵ��ڲ����뻺�棬��һ����ű������*/
    uchar8 V_ucFrameNum;   /*������������*/
    uchar8 V_ucNxtFrame;   /*����֡��־��1��ʾ�к���֡��0��ʾ�޺���*/
    uchar8 V_ucLastFlag;   /*��4λ��ʾ�Ƿ�������һ����־��1��ʾ�������һ����0��ʾ������*/
							/*��4λ��ʾ���һ���Ƿ�Ϊ�з����޻ظ���1��ʾ�з����޻ָ���0��ʾ�з����лָ�*/
}Str_SuppInfo;/*��¼�ͽӿڸ�����Ϣ�ṹ��*/



typedef struct
{
	ulong32	DI;		        ///*645���ݱ�ʶ*///
	ulong32	OAD;			///*698���ݱ�ʶ*///
	uchar8	DILenth;		///*645���ݳ���*///
}Str_EventTable_645ChangeTo698;


#define C_645Mode           0x00
#define C_698Mode           0x01
#define C_698AheadTimeMode  0x68	/*�������߶�ȡʱ�����������Чʱ���*/
#define C_698EarLoadMode    0x86	/*�������߲�����ʱ����ǰһ����Чʱ���*/


#define C_Program	0x68
#define C_NotProgram	0x86
#define C_PluseWide		0x80

//****************698����645����***************//
#define C_UsedBy698    0x00
#define C_UsedBy645    0x55

#define C_MonTwoOffset          1    //2���������е�ƫ��
#define C_NovOffset            11    //12���������е�ƫ��

#define C_MonMaxLim     0x1A4   //��ѯ�����������35��*12
#define C_YearMaxLim    0x23   //��ѯ�����������35��

#define C_CycleTimes  1500  //����2�����������ݣ�����1500������

#define C_ALL00_Flag       0x55 ///��������ʱ��ȫ0
#define C_NoALL00_Flag     0xAA///��������ʱ���ȫ0

///*2020��׼�����ϱ�2005*///
#define C_RS485_1MaxLen 512  ///*ͨ��1�����շ��ͳ���*///
#define C_RS485_2MaxLen 512  ///*ͨ��2�����շ��ͳ���*///
#define C_ModuleMaxLen 255  ///*ͨ��3�����շ��ͳ���*///
#define C_IRMaxLen 200      ///*ͨ��4�����շ��ͳ���*///

#define C_ActiveReportFlag              0x08                                            ///*�����ϱ�*///
#define C_ActiveReportEndFlag           0x04                                            ///*�����ϱ��ս���*///
#define C_NoActiveReportFlag            0x02                                            ///*����ģʽ*///
#define C_ReadReportFlag                0x01                                            ///*���ϱ�ģʽ*///
#define C_NewReportFlag                 0x10                                            ///*�·������ϱ�֮��Ҫ���10s�Ǹ�ʱ�������ϱ�*///
#define C_OtherActiveReportInit         0x20                                            ///*���������ϱ�*///
#define C_EventTypeActiveReportInit     0x40                                            ///*���������ϱ�*///
#define C_NewReportFlag_EventType       (C_NewReportFlag|C_EventTypeActiveReportInit)     ///*�·����¼������ϱ�*///
#define C_NewReportFlag_Other           (C_NewReportFlag|C_OtherActiveReportInit)         ///*�·������������ϱ�*///
#define C_Check                         0x03                   ///*check CRC*///
#define C_CountCRC                      0x05                   ///*Count CRC*///
#define C_ReportMaxNum_Remin            0x06               ///*2.5s�Ƿ�δ���ͳɹ�*///


#define C_RNLen                     12                      ///*8�ֽ������+4�ֽڼ�����*///
#define C_MACLen                    4                      ///*MAC����*///

#define C_ReportFlag                    0x6868        ///*Ŀǰ�����¼������ϱ����ݷ���״̬*///
#define C_PowerDownReportFlag           0x8686          ///*Ŀǰ���ڵ��������ϱ����ݷ���״̬*///
#define C_ReportNULL                    0x0000        ///*û�д��������ϱ�״̬*///

#define C_CommuniSafeWorld1         0x01                    ///*���������ж�*///
#define C_CommuniSafeWorld2         0x02                    ///*������������δ����*///
#define C_CommuniSafeWorld3         0x04                    ///*������ʼ��������*///
#define C_CommuniSafeWorld4         0x08                    ///*����ͨ�ţ��жϷ��ͽ���*///
#define C_CommunicationEnd          (C_CommuniSafeWorld1|C_CommuniSafeWorld2|C_CommuniSafeWorld3|C_CommuniSafeWorld4)///*ͨ�Ÿս���*///
#define C_NoCommunication           0x00                    ///*û�д���ͨ��״̬*///

#define C_EventOIA              0x30            ///*�¼�OIA*///
#define C_Event07ReportType     0x0B            ///*07���¼��ϱ�����11����*///
#define C_Event24ReportType     0x0F            ///*24���¼��ϱ�����15����*///

#define C_ReportMode                            0x68            ///*��ȡ�ϱ�ģʽ�ֱ�־*///
#define C_ReportType                            0x86            ///*��ȡ�ϱ����ͱ�־*///

#define C_ActiveReportType              0x00                    ///*�ϱ����ͣ������ϱ�*////
#define C_FollowReportType              0x01                    ///*�ϱ����ͣ������ϱ�*///

#define C_ACTION_Request		0x07		///*��������*///

///*******************************������֤��Ϣ******************************************///
///*���ܼ���ģʽ�궨��*///
#define SID_MAC_698		0
#define RN_698  		1
#define RN_MAC_698  	2
#define SID_698  		3
#define	NO_RN_698		4
#define MAC_698         5

#define C_OneReportLen      3                                   ///*1�������ϱ��ֽ���*///

#define C_NewReportMaxNum	70						///*�����ϱ��¼�����*��������С��1��*///
//#define C_NewReportDataLen	C_NewReportMaxNum*3		///*�����ϱ��ܳ��ȣ�EventNo+Time��*///
#define C_NewReportDataLen	C_NewReportMaxNum*C_OneReportLen    ///*�����ϱ��ܳ��ȣ�EventNo+Time��*///
#define C_NewReportNumByte	C_NewReportDataLen		///*�����ϱ�����*///
#define C_NewReportLen 		(C_NewReportDataLen+1)	///*�����ϱ�����С*///
#define C_NewReportCRCLen 	(C_NewReportLen+2)		///*�����ϱ�����С�������ϱ��ܳ���+����+CRC��*///

#define CLNewReportList		            (C_NewReportMaxNum*2+1)		        ///*�����ϱ��б�*///
#define CLDrive_Report_State_New		(CLDrive_Report_State+CLDrive_Report_State*8)	///*�����ϱ�״̬��*///
#define C_NewReportSaveNumByte          (CLNewReportList-1)       ///*д���ݲ�ʱ���ϱ��¼�����λ��*///

#define C_SEvent_TimeAttri      0x0E            ///*�����¼�ʱ��״̬����*///
#define C_Event_TimeAttri       0x0A            ///*�¼�ʱ��״̬����*///

#define  C_Money_Init	1
#define  C_Money_Purchase	2
#define C_MonTwoOffset          1    //2���������е�ƫ��
#define C_NovOffset            11    //12���������е�ƫ��
#define C_MonMaxLim     0x1A4   //��ѯ�����������35��*12
#define C_YearMaxLim    0x23   //��ѯ�����������35��
#define C_CycleTimes  1500  //����2�����������ݣ�����1500������
#define C_FreezCycFlagErr     0xFF //������������ʧ�ܱ�־

//CDate_Time���ݵ�ƫ��
#define		C_ss_O					0
#define		C_mm_O					1
#define		C_hh_O					2
#define		CDate_Time_DD_O			3
#define		CDate_Time_MM_O			4
#define		CDate_Time_YYL_O		5
#define		CDate_Time_YYH_O		6

#define C_MoneyLimit	99999999
#define C_FirstNo       0x00
#define C_OtherNo       0xFF

/*21�淶����������ϵ粻��1hour�����е����ϱ�Ҫ��*/
#define C_ActiveReportMaxNum    0x03    /*�����ϱ�����*//*2020��׼�����ϱ�2005*/

#define	C_Happen_EventState     0x68    /*�¼�״̬���з����޻ָ�*/
#define	C_End_EventState        0x00    /*�¼�״̬�����з����޻ָ�*/
#define	C_Close_EventState      0x66    /*�¼�״̬���ر�*/
#define C_Active_NxtFrame 		0x01	/*�к���֡��־*/
#define C_Active_LastEvent 		0x01	/*�������һ��*/
#define C_Active_Happening 		0x11	/*�����з����޻ָ�*/
#define C_InActive				0x00	/*��Ч���޺���֡�������һ����*/

#define C_Interval_1hour        3600    /*���ڻ������ĵ�60min=1hour���*/


#define	C_ReportNull	    0x00	    /*���ϱ�*/
#define	C_ReportHP	        0x01	    /*�����ϱ�*/
#define	C_ReportEed	        0x02	    /*�����ϱ�*/
#define	C_ReportAll	        0x03	    /*���������ϱ�*/

#define C_MeterReportOpen   0x68        /*���ܱ����˵��ܱ������ϱ�/������ģ���ϱ�ͨ��/������ģ���*/
#define C_MeterReportClose  0x86        /*���ܱ�û�п����ܱ������ϱ�����û�п�ģ���ϱ�ͨ�����߲���ģ���*/

///********extern for ADC********///
extern void InF_ADC_Action_Message(Str_Msg_Parameter *P_Msg_Parameter);
extern void InF_ADC_OFF(void);
extern void InF_InitADC(void);
extern void InF_ExecuteClr_RTCBatt(void);
extern void InF_ExecuteClr_WakeUpBatt(void);
extern void InF_InitBatt();
extern void	InF_TempAdc_CmpAndJec(void);

///********extern for communication********///
extern	uchar8 INF_Comm_RecForInt(uchar8 CommNo,uchar8 RecData);
extern	void INF_Comm_ForPowerOn(void);
extern	uchar8 INF_Comm_TxdForInt(uchar8 CommNum,uchar8	*p_TxdData);
extern	uchar8 INF_WrClearAllRecord (uchar8 *pOpCode,uchar8	SafeFlag);
extern	uchar8 INF_WrRateProgRecord (uchar8 *pOpCode,uchar8	SafeFlag);
extern	uchar8 INF_WrStepProgRecord (uchar8 *pOpCode,uchar8	SafeFlag);
extern	void InF_LowPower_IR_Inti(void);
extern	uchar8	InF_JudgeIJTimer( void );
//extern	uchar8 INF_WrElePurchasingProgRecord(uchar8 *pPreChargeBalance);
extern	uchar8 INF_StopProgState(Str_ProgRecord *pProgRecord);
extern	uchar8 Comm_ParseMessage(Str_Msg_Parameter * P_Msg_Parameter);
extern	void	NF_Init_Str_ProgRecord (Str_ProgRecord *pProgRecord);
extern	void	INF_Append_ProgRecordDI (uchar8 *pOpCode,uchar8 *pProgDI,Str_ProgRecord *pProgRecord,uchar8 V_ProgType);
extern	void	INF_StopCommProgState(void);
extern	uchar8  InF_EventNumFind(ulong32 V_Data_Id);
extern	void	InF_InitComm(uchar8 CommNo);
extern	void	InF_ActiveReportSetting(uchar8 V_ucBitNum);
extern	uchar8	InF_IsInFactoryState(void);
//extern	uchar8 InF_RD_ProgRecordReg(ulong32 V_ulDI,uchar8 *P_Buffer,uchar8 *P_BufMaxLen);
extern	uchar8 InF_RD_ProgRecordReg(ulong32 V_ulDI,uchar8 *P_Buffer);

/********extern for dataprocess********/
extern	uchar8 InF_GetData_Record(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo);
extern	uchar8 InF_GetData_Record_DataBase(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo);
extern	uchar8 InF_GetData_ObjectManage(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode);
extern	uchar8 InF_SetData_ObjectManage(uchar8 Msg_Num, ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 V_usDataLen, uchar8 V_W_Safe_Flag);
extern	uchar8 InF_Write_Data(uchar8 Msg_Num, ulong32 V_Data_Id, uchar8 *P_Data, ushort16 V_Data_Length, uchar8 C_W_Safe_Flag);
extern	uchar8 InF_Read_Data(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode);
extern	uchar8 InF_Read_Data_For_Dis(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length);
extern	void  InF_PowerOn_CurrEnergyDeal(void);
extern	void  InF_ChangeTime_LoadProfileCover(void);
extern	uchar8  InF_ReadLoadData(ulong32 V_Data_Id,uchar8 * P_FixTime,uchar8 * P_Data,uchar8 * V_BlockNum,uchar8 * V_Length,uchar8 V_ReadSign);
extern	uchar8  InF_Total_Clear(uchar8 Msg_Num,uchar8 V_CurrentState,uchar8 C_Safe_Flag );
extern	uchar8  InF_EventNote_Clear(uchar8 Msg_Num,ulong32 V_Data_Id,uchar8 C_Safe_Flag);
extern	uchar8  InF_Demand_Clear(uchar8 Msg_Num,uchar8 C_Safe_Flag);
extern	void  Data_CruiseCheck_Message(Str_Msg_Parameter *P_Msg_Parameter);
extern	void  InF_Initial_Data(void);
extern  uchar8  InF_EventNumFind(ulong32 V_Data_Id);
extern  uchar8  InF_ReadLastTimeLoadData(ulong32 V_Data_Id,uchar8 * P_FixTime,uchar8 * P_Data,uchar8 * V_BlockNum,uchar8 * V_Length);
extern	uchar8  InF_Read_RecMeterData(uchar8 V_Data_Num,uchar8 * P_Data,uchar8 * P_Data_Length);
extern  uchar8  InF_RecMeterNote_Clear(uchar8 Msg_Num,uchar8 C_Safe_Flag);
extern  uchar8  InF_Write_RecMeterData(uchar8 Msg_Num,uchar8 * P_Data,uchar8 V_Data_Length,uchar8 V_W_Safe_Flag,uchar8 V_Data_Num);
extern  void InF_ReadE2_Flash_Data(uchar8  * PV_Data,uchar8 V_Len,uchar8 V_Sign,ulong32 V_Addr);
extern  void SF_UpdateE2CurrEnergy(void);
extern  void InF_RAMDataRecoverFromE2(void);///*��ͨ��ģ�鴥�����ã�����E2���ݶ�RAM���ݽ��лָ�*///
extern  uchar8  InF_ReadOADTab_Data(ulong32 V_Data_Id,uchar8 * P_Data,ushort16 * P_Data_Length);
extern  uchar8  InF_ReadLaterFreezeNum(ulong32 V_Data_Id1,uchar8 * P_Data,uchar8 * V_Length);
extern  uchar8  InF_GetMinFreezeNum_OADTab(uchar8 V_ProNum,uchar8 * P_DataOAD_NumTab,ushort16 * P_Length);
extern  uchar8  InF_GetMinFreezeTolNum(void);
extern  uchar8  InF_ReadFreezeData(ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,ushort16 * V_BlockNum,ushort16 * V_Length,ushort16 V_IntervalTime,uchar8 *pV_FreezeTimeBuf,uchar8 V_Mode);
extern	uchar8  SF_Clear_Freeze(uchar8 V_D_SafeFlag,uchar8 V_OIB);
extern	uchar8  InF_ReadParam_Data(ulong32 V_Data_Id,uchar8 * P_Data,uchar8 * P_Data_Length);
extern	uchar8 InF_RecoverFactoryPara(ulong32 *P_ulDI,uchar8 V_ucDINum);
extern	uchar8  InF_ReadEventData(ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,uchar8 * V_NextSign,ushort16 * P_Data_Length,uchar8 V_timeFlash);
extern	void 	InF_WriteFreezeData(uchar8 V_Num);
extern	void  InF_Get_Comm_Address(uchar8 *pV_ucComm_Address,uchar8 V_ucAddr_Type);
extern	void  InF_Check_Comm_Address(void);
extern  uchar8 Verify_para(unsigned char Page ,unsigned char Inpage, unsigned char *Buf, unsigned char Len );
extern  uchar8 InF_ReadE2ThreeRTC(ushort16 Page ,ushort16 Inpage, unsigned char *P_Data, unsigned char V_DataLen );
extern  uchar8 InF_WriteE2ThreeRTC(ushort16 Page, ushort16 Inpage, uchar8 *P_Data, uchar8 V_DataLen );
extern  uchar8 InF_RateNumChangeToHex(void);
extern  void  DataProcess_External_Message(Str_Msg_Parameter * P_Msg_Parameter);
extern	ulong32 SF_FindMinFreezeFirstVolidOAD(ulong32 *P_Data_Id_OAD);

/********extern for demand****************/
extern	void InF_DemandInit(void);
extern	void InF_LowPower_DemandInit(void);
extern void InF_PowerChanggeInitDemand(Str_RealtimePower_Type *pStr_RealtimePower);

extern	uchar8 InF_DemandMetering_Message(Str_Msg_Parameter *pStr_Msg_Parameter);
extern uchar8 InF_Get_DemandModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode);

/********extern for energymetering********/
extern	void InF_EnergyInit(void);

extern uchar8 InF_ReadEnergy_Settlement(void);
extern uchar8 InF_EnergyMetering_Message(Str_Msg_Parameter *pStr_Msg_Parameter);
extern uchar8 InF_MoneyToPurchase(ulong32 V_ulBuyMoney, uchar8 V_ucPurchaseFlag, uchar8 V_ucSafeFlag);
extern uchar8 InF_ReturnMoneyFromPurchase(ulong32 V_ulBuyMoney, uchar8 V_ucSafeFlag);
extern uchar8 InF_Get_EnergyModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode);

///********extern for display********///
extern  uchar8 InF_Display_JudgeIDActive( ulong32 V_ulCodeID,ulong32 V_ulRelatedCodeID,uchar8 V_ucScreenNum );
extern  void InF_Display_Init( void );
extern  void InF_Display_WakeUpInit( void );
extern  void InF_Display_ForCard( void );
extern  void InF_Display_Message( Str_Msg_Parameter *pStr_Msg_Parameter );
extern	uchar8 InF_GetPowerOffDisplayState( void );
extern	uchar8 InF_AlarmState( void );
extern	void InF_Card_DispDynamicSign( void );
extern	uchar8 InF_LocalAndRemoteMeterDiJudge( ulong32 V_ulDi );
extern void InF_Clear_Engry_BorrowPoint( void );

///********extern for carddrive********///
extern uchar8 INF_ColdReset_7816_Card(uchar8 *P_CardNo);
extern ushort16 INF_SendData_7816_Card(uchar8 *P_SendBuffer,uchar8 V_DataLen,uchar8 *pResponse,uchar8 *pMaxResponseLen);
extern uchar8 INF_WarmReset_7816_Card(uchar8 *P_CardNo);
extern void InF_Deactivation_7816_Card(void);
extern uchar8  INF_WarmRest_7816_Card(void);
extern uchar8	InF_Card_Message(Str_Msg_Parameter *pStr_Msg_Parameter);

///********extern for eepromdrive********///
extern	uchar8 InF_ReadE2(ushort16 E2Addr,uchar8 *p_databuff,ushort16 Len);
extern	uchar8 InF_WriteE2(ushort16 E2Addr,uchar8 *p_databuff,ushort16 Len);
extern	void InF_InitE2(void);
extern	uchar8 InF_ClearE2(ushort16 E2Addr,ushort16 Len);
extern	void InF_E2WPEnable(void);
extern	void InF_E2WPDisable(void);

///********extern for FRAMdrive********///
extern	uchar8 InF_ReadFRAM(ushort16 FRAMAddr,uchar8 *p_databuff,ushort16 Len);
extern	uchar8 InF_WriteFRAM(ushort16 FRAMAddr,uchar8 *p_databuff,ushort16 Len);
extern	void InF_InitFRAM(void);
extern	uchar8 InF_ClearFRAM(ushort16 FRAMAddr,ushort16 Len);
extern	void InF_FRAMWPEnable(void);
extern	void InF_FRAMWPDisable(void);

///********extern for esamdrive********///
extern	ushort16 INF_SendData_7816_Esam(uchar8*P_SendBuffer,uchar8 V_Datalen,uchar8 *pResponse,uchar8 *pMaxResponseLen);
extern	ushort16 INF_SendData_698_Esam(uchar8*P_SendBuffer,ushort16 V_Datalen,uchar8 *pResponse,ushort16 *pMaxResponseLen);
extern	uchar8 EsamPowerOnRest_Message(Str_Msg_Parameter * P_Msg_Parameter);
extern  uchar8  INF_WarmRest_7816_Esam(void);
extern	void InF_InitEsamPowerOn(void);
extern	uchar8 InF_SwitchEsam(uchar8 V_Act);
extern	void InF_ExecuteClr_Esam(void);
extern void InF_Deactivation_7816_Esam(void);

///********extern for flashdrive********///
extern	void InF_ReadFlash(ulong32 V_FlashAddr,uchar8 *p_databuff,ushort16 Len);
extern	void InF_WriteFlash(ulong32 V_FlashAddr,uchar8 *p_databuff,ushort16 Len);
extern	void InF_EraseFlash(ulong32 V_FlashAddr);
extern	void InF_FlashChipSelect(void);
extern	void InF_FlashChipDeselect(void);

///********extern for lcddrive********///
extern	void InF_WriteLCD(uchar8 *p_databuff,uchar8 Len,uchar8 KillZero);
extern	void InF_WriteLCD_DispDynamicSign(uchar8 *p_databuff,uchar8 DynamicSignNum);
extern	void InF_InitLCD(void);
extern	void InF_SwitchOffLCD(void);



///********extern for metericdrive********///
extern	void  InF_Initial_MeterIC (void);
extern	uchar8  InF_GetDataNO_MeterIC(ulong32  V_Data_Id);
extern	uchar8 InF_ReadReg_MeterIC(ushort16 V_Data_Id,uchar8 *PStr_Data,uchar8 *PLength);
//extern	uchar8  INF_WriteCalReg_MeterIC(ulong32 V_Data_Id,uchar8 *Ptr_Data);
extern	uchar8  InF_Read_MeterIC_EnergyData(Struct_Energy_Type  *P_EnergyData);
extern	void  InF_PowerDownInitial_MeterIC(void);
extern	uchar8  InF_PowerDownReadData_MeterIC(void);
extern	void InF_MeterIC_ParseMessage(Str_Msg_Parameter  *P_Msg_Parameter);
extern	uchar8  InF_WriteCalReg_MeterIC(ushort16 V_Data_Id,uchar8 *Ptr_Data,uchar8 V_DataLen,uchar8 *Ptr_PhaseNO,uchar8 *Ptr_NOAmount);
extern	void  InF_ClearHexVarregtype_MeterIC(uchar8 V_ClearType);
extern	void  InF_Initial(void);
extern void InF_InitialEvenHarmonicCompensationTime (void);
extern uchar8 InF_ValtageType(void);

///********extern for RTCdrive********///
extern	uchar8 InF_ReadRTC(uchar8 *p,uchar8 Len);
extern	uchar8 InF_WriteRTC(uchar8 *P_Time,uchar8 Len);
extern	void InF_CheckRTC(void);
extern	void InF_InitalRTC(void);
extern	void InF_Dispatch_ReadRtcToDataProcess(uchar8 powerflag);
extern	void InF_ExecuteClr_RTC(void);
extern	void InF_Execute_RTCErr(uchar8 P_Buff);
extern  void SF_InitRTCState(void);
extern  ushort16 InF_GetRTC_Adjust(void);
extern  void Temperpara_Verify(void);
extern  void Fill_RTC_RT_TAdc(void);
extern  void Fill_RTC_RT_TVal(void);
extern  short16 Get_RTCTop_Proc( short16 Temp16 );

///********extern for eventrecord********///
extern	uchar8 Inf_ReadEventRenew(ulong32 *V_Data_Id,uchar8 *Data,uchar8 *Data_Length);
extern	void Inf_PowerupEventrestore(void);
extern	void Inf_LowpowerACPowerFail(void);
extern	void Inf_PowerAbnormal(void);
extern	void Inf_LowpowerTotalVoltagelose(void);
extern	uchar8 Inf_LowpowerPowerFail(void);
extern	void Inf_LowpowerOpenMeterCover(void);
extern	void Inf_LowpowerTerminalCoverState(void);
extern	void InF_Event_Message(Str_Msg_Parameter *V_Msg);
extern	uchar8 Inf_BackLightLimit(void);
extern  void Inf_LowPowerMeterStatus(void);
#if (_DEBUG_DB)
extern	uchar8 Inf_GetEventData(uchar8 *V_Data,ushort16 *V_Data_Length, ulong32 V_OADTab, uchar8 V_Event_Flag);
#endif
extern	uchar8 Inf_ReadEventCurrentData(ulong32 V_Data_Id,uchar8 *P_Data,uchar8 *P_Data_Length);
extern	uchar8 Inf_ReadEventLast_H(ulong32 *V_Data_OAD,uchar8 *P_Data,ushort16 *P_Data_Length,uchar8 V_timeFlash, uchar8 *pV_ucHappeningFlag);
ulong32  InF_EventOADFind(uchar8 V_EventNo);
void Inf_EventReport_Sign(uchar8 Type,uchar8 CommChannel,uchar8 EventNo,uchar8 ReportType);
void SF_Write_EventCurrentRelate(uchar8 EventNo,uchar8 *P_DataBuffer);
uchar8 Inf_Get_PowerDownEvent_Data(uchar8 EventNo, uchar8 *P_DataBuffer , ushort16 *P_DataLen);
extern uchar8 SF_Judge_EventIntegrity(uchar8 EventNo);
//extern ulong32    Inf_GetEventModeDI(uchar8 EventLine);
extern ulong32    Inf_GetEventModeDI(uchar8 EventLine,uchar8 OADType);
extern uchar8 Inf_GetPowerDownEventType(uchar8 EventNo);
extern void Inf_LowpowerOpenCoverState(uchar8 V_ucEvtNo);
extern uchar8 InF_Get_EventModule(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo);

///********extern for freeze********///
extern	void InF_FreezeDayAfterPowerUp(void);
extern	void InF_FreezeSwitch (ulong32 V_ulDataCode,uchar8 Swich_Time[5]);
extern	void Msg_Freeze(Str_Msg_Parameter *P_Msg);
extern	void Inf_EventReport_HP(uchar8 EventNo,uchar8 State);
extern	uchar8 SF_Judge_EventIntegrity(uchar8 EventNo);

///********extern for io********///
extern void InF_ConfigIOInPowerON(void);
extern void InF_JTagEnable( void );
///********extern for loadprofile********///
//extern	uchar8 InF_SeqRead_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucTime,uchar8 *P_ucData,uchar8 *P_ucGVBuffer,uchar8 *P_ucBlockNum,uchar8 *P_ucLength,uchar8 *P_ucFollowFlag);
extern	uchar8 SF_HEXtoDECByte(uchar8 HEXdata);
//extern	void Msg_LoadProfile(Str_Msg_Parameter *V_Msg);
//extern	uchar8 InF_SeqRead_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucTime,uchar8 *P_ucData,uchar8 *P_ucGVBuffer,uchar8 *P_ucBlockNum,uchar8 *P_ucLength,uchar8 P_ucFollowFlag);
extern	void SF_MinsAdd_LoadProfile(uchar8 *P_ucSourceTime,ulong32 V_ulAddMins,uchar8 *P_ucResultTime);
///********extern for lowpower********///
extern uchar8 InF_ReadPowerState(void);
extern uchar8 InF_CheckPowerAndExcute(void);
extern void InF_PowerOnDelay(void);
extern void InF_CalibrateRC(void);
extern  void SF_KeyLock(void);
extern  void SF_WritePowerMode_PowerOff(void);
extern uchar8 InF_GetEnterLowPowerTimerUpdateFlag(void);
///********extern for mcuconfig********///
extern void InF_SystemClockInPowerOn();
extern void DF_ReloadRegister(void);
extern void InF_SystemMonitor(void);
extern void RCHF_Adj_Proc(void);
extern void Msg_CalibrateRC(Str_Msg_Parameter *P_Msg_Parameter);

extern void InF_Enable_Flash_CLK(void);
extern void InF_Disable_Flash_CLK(void);
extern void InF_Reset_MCU(void);


///********extern for Comm_698********///
extern uchar8 GV_KeyHState[CLKey_State_698];                  ///*���ܱ���ʷ��Կ״̬��*///

extern	void Inf_ReportList(uchar8 channel,uchar8 EventNo,uchar8 Action);
//extern	void Inf_TimingDealReportList(void);
extern	void Inf_WriteMeterStatus8(uchar8 EventNo);
extern  void Inf_Get_ApplianceF205(ulong32 V_OAD,uchar8 *P_DataBuf,uchar8 *V_Len);
//extern  uchar8  Inf_GetMeter8(uchar8 V_Channel,uchar8 *P_Data,uchar8 V_ucBufLen);
//extern uchar8 Inf_ReportGetEventNo(Str_Comm_698_RW pV_698RWPara,uchar8 *V_Flag,uchar8 *V_ReadSign,uchar8 *V_EventNo,uchar8 *V_ReadTime,uchar8 *V_OADNum);
extern  uchar8  Inf_GetMeter8(uchar8 V_Channel,uchar8 *P_Data,uchar8 V_ucBufLen,uchar8 ReportType,uchar8 *P_Numdata,uchar8 *NumLen);
extern  uchar8 InF_GETListData(uchar8 Channel,uchar8 *P_NumOAD,uchar8 *P_EventNo,uchar8 Len,uchar8 *P_RemainReportNO,uchar8 *P_RemainReportNum,uchar8 ReportType);
extern  void Inf_CommReport(uchar8  PowerFlag);
//extern  void Inf_Set_REPORTFlag(void);
extern uchar8 Inf_EventTypeCommReport(uchar8  PowerFlag, uchar8 SendNo);
//extern uchar8 InF_GETListData(uchar8 Channel,uchar8 *P_NumOAD,uchar8 *P_EventNo,uchar8 Len);
extern void Inf_PowerupComm(void);
extern void SF_Deal_ReportCRC(uchar8 Type);
///********extern for message********///
extern	void InF_WriteMessege(Str_Msg_Parameter *V_Msg);
extern	uchar8 InF_ReadMessegeDerictAddr(Str_Msg_Parameter *V_Msg,uchar8 V_ucMessageSqueueNum);
extern	void InF_InitMessage(void);
extern	void InF_ExcuteMessage_PowerFalling(void);
///********extern for multifunctionoutput********///
extern	void InF_MultiFunctionOutput(uchar8 V_Function);
extern	uchar8 InF_ModifyFunctionWord(uchar8 V_Data);
extern	void InF_MultiFunctionOutput_Init(void);
extern	uchar8 InF_ModifyFunctionStatus(void);

///********extern for rate********///
extern	void InF_Deal_MultiRates(void);
//extern	void  PF_StepTypeProcess(uchar8 *OldDate,uchar8 *NewDate,uchar8 *SettlementTime);   /*zljɾ��*/
extern	void InF_MultiRates_ParseMessage(Str_Msg_Parameter *V_Msg);

///********extern for relay********///
extern	void InF_InitRelayStatusPowerUp(void);
extern	uchar8 InF_RelayOpenStatus(void);
extern	uchar8 InF_DealwithComRelayOrder(uchar8 V_ucOrderType,uchar8 *P_OperaterCode,ulong32 V_ucDelayTime,ushort16 *V_usOrderExcuteStatus,uchar8 V_Flag);
extern	void Msg_Deal_RelayStatus (Str_Msg_Parameter *V_Msg);
extern	uchar8 InF_RelayProtectStatus (void);
extern  uchar8 InF_JudgeVolage_Relay(void);
extern  uchar8 InF_RelayOpenStatus_698 (void);
extern  uchar8 InF_Get_RelayModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *p_usDataEncode);
///********extern for securitymodule********///
extern void	InF_S_UpdataChargeBalInESAM(uchar8 *pChargeBal_Hex_Cent);
extern void InF_S_PowerOn(void);
extern ushort16  InF_S_ControlCommand( uchar8 *P_Data,uchar8 *P_Length);
extern void InF_S_GetMeterNum_ReworkDL(void);
extern void  InF_S_GetKeyStatus_ReworkKeyStatus(void);
extern void InF_S_Dispatch_5s(void);
extern uchar8 InF_IS_UpdateMInEsamTimer(void);
extern ushort16	InF_S_Software_Campare(uchar8 *pData,uchar8 *pFactorData,uchar8 V_ucKeyNum);

extern	uchar8  INF_S_ActionEsam_698old(ulong32 OAD,uchar8 *p_Data,ushort16 *Len,uchar8 Action,uchar8 V_ucClientAddr);
extern	uchar8 	InF_S_Authentication_698(uchar8 *P_Data, ushort16* Len,uchar8 V_ClientAddr);
extern	uchar8  INF_S_Decrypt(uchar8 *p_APDU,ushort16 Len,uchar8 SecurityMode,uchar8 *SID_Data,ushort16 SID_Len);
extern	uchar8  INF_S_Encrypt(uchar8 *p_APDU,ushort16 Len,uchar8 SecurityMode,uchar8 *RN_Data,ushort16 RD_Len);
extern	ushort16	InF_S_Software_Campare_698(uchar8 *pData,uchar8 *pFactorData,uchar8 V_ucKeyNum,ushort16 *p_DataLen,uchar8 *pRN_Data);

extern	uchar8 InF_Get_SafeModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *P_usDataEncode);


///********extern for settleaccount********///
extern	void InF_SettleAccountsAfterPowerUp (void);
extern	void Msg_SettleAccounts(Str_Msg_Parameter *P_Msg);
extern	uchar8 Inf_GetFrozenData_Settle23(uchar8 *V_ucData,ushort16 *V_ucResultDataLength,uchar8 V_Demand,ulong32 V_OADTable);
extern	uchar8 Inf_Read_FrozenData_OneOAD(ulong32 *V_Data_Id_OAD,uchar8 *V_Data,ushort16 *V_Length);

///********extern for timer********///
extern void InF_TickTimerStart(void);
extern void InF_TickTimerStop(void);
extern uchar8 InF_GetPeripheralStatus(uchar8 Peripheral);
extern uchar8 InF_SwithPeripherals(uchar8 Peripherals,uchar8 Act);
extern void InF_InitTimer(void);
extern void InF_DealWith5ms(void);
extern void InF_WatchDog_Init(void);
extern uchar8 InF_RelayAct(uchar8 C_Act);
extern void InF_BeeperOut(uchar8 BeeperOutType,ushort16 BeeperOutTime,ushort16 BeeperOutCycle);
extern ushort16 InF_OprateTimer(uchar8 Method,ushort16 time);
extern void SF_ClrPowerOnTimer(void);
extern uchar8 SF_Shut_RealTimeData(void);
extern void InF_Delay_2us(void);
extern void InF_Delay_us_Start(ulong32 Delay_Num);
extern void InF_Delay_us_Stop( void );
extern uchar8 InF_Delay_us_Finish( void );
extern void InF_Delay_us(ulong32 Delay_Num);
///********extern for uart********///
extern	void InF_InitCommUartForInterrupt(uchar8 CommNum);
extern	uchar8 InF_InitCommUartForDispatch(uchar8 CommNum,uchar8 bps,uchar8 DataLen,uchar8 StpLen,uchar8 parityChk);
extern	uchar8 InF_CommUart_RecDisableForInterrupt(uchar8 CommNum);
extern	uchar8 InF_CommUart_RecDisableForDispatch(uchar8 CommNum);
extern	uchar8 InF_CommUart_RecEnableForInterrupt(uchar8 CommNum);
extern	uchar8 InF_CommUart_RecEnableForDispatch(uchar8 CommNum);
extern	uchar8 InF_CommUart_TxdDataForInterrupt(uchar8 CommNum,uchar8 TxdData);
//extern	uchar8 InF_CommUart_TxdDataForDispatch(uchar8 CommNum,uchar8 TxdData);
extern	uchar8 InF_CommUart_TxdDataForDispatch(uchar8 CommNum,uchar8 TxdData,uchar8 ReportMode);
extern	void SF_GetMeterType(void);
extern uchar8 Inf_GetMeterType(void);

///********extern for voltageQR********///
extern	uchar8 InF_VoltageQR_ParseMessage(Str_Msg_Parameter *pStr_Msg_Parameter);
extern	void InF_VoltageQRrestore(void);
//extern	void InF_GetVoltageQR_Data(uchar8 *V_ucResultData);
extern	void InF_ClearVoltageQR_Data_D(void);
///********extern for Comm_698.c********///
extern void Inf_CleanAllMeterStatus8(void);
extern void InF_Clear_BroadTimeAbnormalTime(void);
extern uchar8 SF_Get_Active_OAD(ulong32 V_ulReadOAD, ulong32 *pV_ulSetAndFixedOAD, uchar8 V_ucDataType, uchar8 V_ucHappeningFlag);
///********extern for Disptch********///
//extern	void InF_Dealwith_FirstSqueue(void);
//extern	void InF_Dealwith_SecondSqueue(void);
extern	void InF_ClrWatchDogTimer(void);
extern	void InF_FeedWatchDog(void);
extern	uchar8 Msg_ExcuteRTC_Message(Str_Msg_Parameter * P_Msg_Parameter);
extern	void Msg_AllLoseVoltage(Str_Msg_Parameter * P_Msg_Parameter);
extern	uchar8	Card_ParseMessage(Str_Msg_Parameter * P_Msg_Parameter);
extern	uchar8 InF_Dealwith_MessageSqueue(void);
extern	const   uchar8	GV_C_Internal_Version[CL_Internal_Version];
#if _DEBUGFY /*���ٴ�RAM����Ϊʹ�ú궨��,ƴ��ʱȥ��*/
extern	const		uchar8 GV_C_Pluse_Most__Lim[CLPluse_Most__Lim];
#endif
extern	const		uchar8 GV_C_SlipCurrent__Flag;
//extern	const	Struct_RTC_Adj TAB_DFx[1];
extern uchar8 Inf_MeterReportOpen(uchar8  PowerFlag, uchar8 SendNo);
extern	void	InF_InitFreezeOADFlag(uchar8	V_InitFlag);
//extern	uchar8 SF_DIChangeToOI(uchar8 *P_645DI,uchar8 *P_698OI);
//extern	uchar8  InF_ReadEventData(ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,uchar8 * V_NextSign,ushort16 * P_Data_Length);
extern	uchar8 SF_ColdReset_7816_Esam(uchar8 *P_Buff);
//#define Str_FrozenConvert_Table_Len  637
extern const Struct_FrozenConvert_Type Str_FrozenConvert_Table[];
extern const ushort16 Str_FrozenConvert_Table_Len;
extern const ushort16 Str_698EventReport_Len;
extern const  Str_698EventReport_Type Str_698EventReport[];
extern	uchar8 InF_JudgeNoEndTimeEvent(ulong32 V_EventOAD);

#define	C_SaveFreezeTimeNum	80		//�������20�������¼ʱ��
#define	C_FreezeTimeLen	7			//����ʱ�䳤��
#define	C_SaveFreezeTimeBufLen	491		//�������20�������¼ʱ��
#define	C_645FreezeTimeBufLen	610		//645���ɼ�¼��������99��
#define C_FreezeMAXRelatedOAD		96
#define C_MAXRelatedOAD  (C_FreezeMAXRelatedOAD+5)
#define C_645FreezeMAXRelatedOAD    99
#define C_698To645EnergyBlockLength    (4*4)
typedef  struct
{
	  //uchar8	DI0;             			///*DI0*///
	  uchar8	DataType;			///*��������*///
	  uchar8	DataLen_698;		///*���ݳ���*///
	  uchar8	DataLen_645;		///*���ݳ���*///

}Str_DI0_DataType_PaTable;				           ///*DI0/�������͵�ӳ��*///

///*�������ݱ�ʶ���Ӧ�ĸ�������*///
typedef struct
{
    ulong32 V_ulDataId698;	///*698���ݱ�ʶ*///
    uchar8 V_Num;           ///*����698���ݸ���*///
    uchar8 V_SuppleData;    ///*�����ݵ����ͣ����ܲ���һ��������ݣ�˲ʱ����0xFF*///
	ulong32 V_ulDataId645;	///*645���ݱ�ʶ*///
//	ulong32 V_ulTypeId;		///*��Ӧԭ�������ͱ�ʶ��*///
//	uchar8 V_ucOffset;		///*���ݱ�ʶ�ڶ�Ӧ���������ƫ�� *///
	uchar8 V_ucDataLen;		///*��ʶ�����ݶ�Ӧ�ĳ���*///
}Str_698To645LoadReadStatus;
/*���ɼ�¼645DI��Ӧ698OAD*/
typedef struct
{
	ulong32 V_ulDataOAD698;		/*698���ݱ�ʶ*/
	ulong32 V_ulDataDI645;		/*645���ݱ�ʶ*/
	uchar8 V_ucDataLen;			/*��ʶ�����ݶ�Ӧ�ĳ���*/
	uchar8 V_ucDataOffset;		/*���ݱ�ʶ�ڶ�Ӧ���������ƫ��*/
}Str_LoadRecord645DITo698OAD;
typedef struct
{
    ulong32 V_ulDataId698;	///*698���ݱ�ʶ*///
    uchar8 V_Num;           ///*����698���ݸ���*///
//    uchar8 V_SuppleData;    ///*�����ݵ����ͣ����ܲ���һ��������ݣ�˲ʱ����0xFF*///
	ulong32 V_ulDataId645;	///*645���ݱ�ʶ*///
//	ulong32 V_ulTypeId;		///*��Ӧԭ�������ͱ�ʶ��*///
//	uchar8 V_ucOffset;		///*���ݱ�ʶ�ڶ�Ӧ���������ƫ�� *///
	uchar8 V_ucDataLen;		///*��ʶ�����ݶ�Ӧ�ĳ���*///
}Str_698To645DFreezReadStatus;
//extern uchar8 GV_SaveFreezeTimeBuf[C_SaveFreezeTimeBufLen];
extern void InF_WriteFreezeTimeToBufer(uchar8 *pV_FreezeTimeBuf,uchar8 *pV_CurrentTime,uchar8 V_Mode);

#define C_MaxRCSDNum           25          ///*����¼��ѡ������������*///
typedef struct
{
	ulong32  	OAD;					///*��OI*///
	ushort16	CarryNum;				///*��������飬�����¼�������*//
	uchar8	DataType;				///*��������*///
	uchar8	CurrentFrameNum;	///*�к���֡ʱ��������һ֡��ƫ��(�ڼ���)*//

}OAD_T;

typedef struct
{
	OAD_T  	RdOI;					///*��OI*///
	//OAD_T  	Rd_RecordRelatedOI[25];	///*����¼����OI,���ﰴ��ʧѹ�������ݹ������������*///
	ulong32  	Rd_RecordRelatedOI[C_MaxRCSDNum];	///*����¼����OI,���ﰴ��ʧѹ�������ݹ������������*///
	uchar8	 	Rd_RecordRelatedOINum;	///*����¼����OI��*///
	uchar8	 	Rd_RecordRelatedOIType;	///*����¼��������*///
	uchar8	 	Rd_RecordSelect[25];		///*��ȡ��¼ʱѡ�񷽷�*///
	uchar8	 	Rd_Result;				///*���������*///
}RdOI_Para_T;

#define	C_RSDSelector1			0x01		///*�¼���¼��ȡѡ�񷽷�1*///
#define	C_RSDSelector2			0x02		///*�¼���¼��ȡѡ�񷽷�2*///
#define	C_RSDSelector9			0x09		///*�¼���¼��ȡѡ�񷽷�9*///

#define C_GETNormal_Request		0x01		///*��ȡһ����������*///
#define C_GETNormalList_Request	0x02		///*��ȡ�����������*///
#define C_GETRecord_Request		0x03		///*��ȡһ����¼*///
#define C_GETRecordList_Request	0x04		///*��ȡ�����¼*///
#define C_GETNext_Request		0x05		///*������*///

/*************************ͨ���·�RSTƫ�ƶ���********************************/
#define C_GetSelect_Method_O		0		/*��ȡ����ƫ��*/
#define C_GetSelect_OADOrNum_O		1		/*��ȡ�����������������׵�ַ*/
#define C_GetSelect_Data1_O			5		/*��ȡ����1/2 Dataƫ���׵�ַ*/
#define C_GetSelect_Data2_O			13		/*��ȡ����2 Data2ƫ���׵�ַ(Ŀǰ����2ֻ֧����ʱ������)*/
#define C_GetSelect_TI_O			21		/*��ȡ����2 Data3ƫ���׵�ַ(TI)*/
#define C_GetSelect_TIUnit_O		22		/*��ȡ����2 TI��λƫ���׵�ַ*/
#define C_GetSelect_TIInter_O		23		/*��ȡ����2 TIʱ����ƫ���׵�ַ*/


extern uchar8 SF_GetAPDU_FreezeRead(RdOI_Para_T *V_OAD,uchar8 *P_DataBuf,ushort16 *P_DataOff,uchar8 NextFrameFlage);
extern ushort16	SF_DataExchangeTo645_BasicData(uchar8 *pV_698data,uchar8 *pV_645data,uchar8 V_ucLen698,uchar8 *V_ucLen645);


extern void PF_Buffer8ToUlong64_698(uchar8 *BytesBuffer, ulong64 *DoubleWordBuufer, uchar8 Len);
extern void PF_Ulong64ToBuffer8_698(uchar8 *BytesBuffer, ulong64 *DoubleWordBuufer, uchar8 Len);


///*****************����΢RTCʱ�ӵ�У
//��0x811800��ʼ�ᱣ��������Ϣ
#define const_tx_flag  			(*((ushort16 *)(0x1ffffa20))) //��У��־(0x3cc3Ϊ��̵�У)
#define const_rtc_adj_top 	(*((short16 *)(0x1ffffa36))) //�������ppm,0.01ppm
//�¶�������ز���
extern const uchar8 RTC_Trim_Ctrl;	//0x55-��������0.119ppm������-��������0.238ppm(��404ģʽ�¿ɿ���0.119)
extern const uchar8 SleepPtatOffsetCfg;	//0x55-����3Vƫ��(3V��Դptatƫ�ÿ��ƿ���)������-�ر�
extern const float const_xtl_top;		//�����¶�����ʹ�õĶ���
extern const float const_KL;	//�¶Ȳ���ϵ��
extern const float const_KH;
extern const float const_TmpsL;	//�¶�ADCб��
extern const float const_TmpsH;
extern const uchar8 constF_Volt;		//��ѹ������(������Ӳ��������Ӷ�����),3��ʾ0.03v/10��ʾ0.1v
extern const ushort16 const_adc_TrimB;
extern const ushort16 const_adc_TrimT;
extern const ushort16 const_KHKL_TrimRange;//���������޵����ֽܷ緶Χ��25�ȡ�7����ʹ�ó����޵�ֵkrh��krl����Χ��ʹ�øߵ����޵�ֵkh��kl
extern const float const_T_OffsetRun;	//оƬ��������-������
extern const float const_T_OffsetSlp;	//оƬ��������-������
extern const uchar8 const_TopNoTrim;  //�����x�ȸ��������� 0x55:�������� 0x00:��������
extern const uchar8 const_TopNTRange;	//���㸽���ر��Զ������¶�adc��Χ����x/5.0379=�¶ȷ�Χ
extern const float const_T_CL;	//���²�������¶�
extern const float const_T_CH;		//���²�������¶�
extern const uchar8 const_C_Mode;		//0x55:�����ߵ��¸߾��Ȳ���ܣ����������������¸߾��Ȳ��

extern const short16 const_TR_LSTART;	//���¼�¼�����¶ȣ�short16�Ŵ�10����
extern const short16 const_TR_HSTART;	//���¼�¼�����¶ȣ�short16�Ŵ�10����
///extern const uchar8 const_TR_GAP;//1;//	//��¼�������λ����
///extern const uchar8 const_TR_Mode;		//0x55:�����¶ȼ�¼���ܣ��������ر�
extern const uchar8 C_Temp_VrefAotu;
extern const uchar8 C_ESAMPower;
extern const uchar8 C_Odd_Harmonic;
extern const uchar8 C_Even_Harmonic;
extern const uchar8 C_Cap_OpenAfter30min;

extern  uchar8 INF_Comm_TxdForInt_698Report(uchar8 CommNum,uchar8	*p_TxdData);
extern void INF_SetReportTest(uchar8 V_Set,uchar8 V_BufNo);
extern uchar8 Inf_Event_REPORTONumDeal(uchar8 Type);
extern ushort16 Inf_Comm_REPORTFlag(void);
extern uchar8 Inf_Comm_REPORTFlagClear(uchar8 ClearMode);
extern uchar8 Inf_Comm_InitModuleCommuniFlag(uchar8 Key);
extern void Inf_Comm_ClearModuleCommuniFlag(uchar8 V_ModuleFlag);
extern uchar8 Inf_Comm_GetModuleCommuniFlag(void);
extern void InF_InitASaveData(uchar8	PowerFlag,uchar8 V_Channel);
extern uchar8 Inf_DealEventReportShut(uchar8 Type);
extern void Inf_CalReportCRC(void);
#define	C_PowerFail_Judge_Time	0x01  ///*������ʱ�ж�ʱ��Ĭ��1s*///
extern void Inf_GetReportData(uchar8 *pReportBufStart,ushort16 *pReportLen,uchar8 CommChannelNo,uchar8 ReportType);
extern uchar8  INF_ValtageType(void);
extern uchar8 Inf_Event_REPORTONumGet(void);
/*extern void InF_CardParam(void); */
extern ulong32 Inf_PowerDownTime(void);
extern void Inf_ClearPowerDownTime(void);
extern ulong32 Inf_Get_PowerOffShutAcReportTime(void);
extern void Inf_Clear_PowerOffShutAcReportTime(void);
extern uchar8 Inf_SatisfyPowerOnTime();

/*zlj����*/
extern uchar8 PF_HextoBCDOneBytes(uchar8 V_ucData);
extern uchar8 PF_Is_Buf_AllFixedData(uchar8 *P_ucData, uchar8 V_ucFixedData,  ushort16 V_usDataLen);
extern uchar8 PF_DataTimeActive_698(uchar8 *TimeBuffer,uchar8 StartByte,uchar8 Len);
uchar8 InF_Get_MeterICModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *p_usDataEncode);

#define	C_ShieldSignBit 0x7f		/*���η���λ*/
#define	C_GetSignBit 	0x80		/*��ȡ����λ*/

#define C_Minus     C_GetSignBit    /*������֮ǰȡ����λ�Ķ��壨0x80��������֮ǰ���������*/
#define C_Plus      C_ShieldSignBit /*����*/


#define C_Immediate_Type			0	    /*˲ʱ����*/
#define C_Minute_Type				0x10	/*���Ӷ���*/
#define C_Hour_Type					2	    /*Сʱ����*/
#define C_Day_Type					3	    /*�ն���*/
#define C_Settlement_Type			4	    /*�����ն���*/
#define C_Month_Type				5	    /*�¶���*/
#define C_Year_Type					6	    /*�궳��*/
#define C_Change_TimeZone_Type		7	    /*ʱ�����л�����*/
#define C_Change_TimePeriod_Type	8	    /*��ʱ�α��л�����*/
#define C_Change_Fate_Type			9	    /*���ʵ���л�����*/
#define C_Change_Ladder_Type		10	    /*�����л�����*/
#define C_Day_Type_Add				11	    /*�ն��Ჹ��*/
#define	C_YSettle_Type			    12	    /*���ݽ��㶳��*/
#define	C_Month_Type_Add			13	    /*�¶��Ჹ��*/

#define C_FrzOAD    0x50000000  /*����¼��ȡ���ݽӿں�������ж����OAD������ʶ*/

extern void SF_GetFreeze_StartTime(uchar8 *pFreezeTime);
extern uchar8 Inf_GetRecordData(uchar8 *V_ucData, ushort16 *V_ucLength, ulong32 V_ulOADTab, uchar8 V_ucTypeFlag);
extern void PF_Data_Week_Time_BCDtoData_Time_s_HEX(uchar8 *V_ucBCDBuffer, uchar8 *V_ucHexBuffer);
extern void PF_Data_Time_s_HEXtoData_Week_Time_BCD(uchar8 *V_ucHexBuffer, uchar8 *V_ucBCDBuffer);

#endif
