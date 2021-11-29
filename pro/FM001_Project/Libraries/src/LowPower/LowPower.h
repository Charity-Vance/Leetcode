
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     LowPower.h
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__LowPower_H
#define	__LowPower_H

#define	C_CheckPowerDownTimes	50				///*�����ж�������ߵĴ������˲�*///
#define	C_CheckPowerDownCounter	45				///*�����ж����������Ч����*///
#define	C_CheckPowerOnTimes		6				///*�͹����¼����ߵĴ������˲�*///
#define	C_CheckPowerOnCounter	4				///*�͹����¼�������Ч����*///

#define C_BattPower                0x0F         /*ͣ������е�*/
#define C_EleCapacitor             0xF0         /*���������е�*/
#define C_BothBattAndCapacitor     (C_BattPower | C_EleCapacitor)         /*�������ݺͳ����ض��е�*/
#define C_NoPower                  0            /*�������ݺͳ����ض�û��*/

#define C_RTCRegWpr1	0xca	///*RTC��д����*///
#define C_RTCRegWpr2	0x53

#define C_1sTimer		2375	///*2375*16/38000=1s*///

#define	LINE20NOMASK	0x00100000
#define	LINE20RSING		0x00100000
#define	LINE20FALLING	0x00100000
#define	LINE20TRIGGER	0x00100000

#define INITMODE_TIMEOUT	0x00002000
#define RTC_INIT_MASK		0xFFFFFFFF


#define C_PowerSupplyInit	0xf9
#define C_PowerSupply		0x04


#define C_PowerOnDelay		300
#define C_PowerOnCheck		200

#define C_Enable			0x68		///*ʹ��*///
#define C_Disable			0x00		///*��ֹ*///
#define C_LimitTimes		120			///*ÿ���������ⰴ����������ô��κ󶼰��£����ֹ�ð����Ļ���*///
#define	C_InfraWakeup_7Day	604800		///*7������Ϊ��*///
#define	C_AllLossTime		60			///*����͹���60s����ȫʧѹ*///
#define	C_AllLossPrepare		58			///*����͹���58s��׼����ȫʧѹ*///
#define	C_CheckKeyTimes		10			///*�͹����£������/�·������Ĵ���*///

#define C_PowerMode			0x04		///*���緽ʽ����ع���*///
#define C_PowerModeInit		0xf9		///*���緽ʽ����ع���*///

#define C_InfraWakeup_Interval	3		///*������޺��⻽�ѵļ��ʱ�䣺������Ϊ3s*///
#define C_InfraWakeup_Flag		0x68	///*�к����жϱ�־*///
#define C_KeyLockCNT		8			///*��������������*///
#define	C_LowPower_RTC83min	4980			///*ͣ������£�RTC��Уÿ83min����һ��*///

#define	C_PowerOffTime		3			///*����͹���3s��������*///

typedef struct
{
	uchar8	Wakeup_En;			///*����ʹ��*///
	uchar8	Times;				///*��������������������7���־*///
	uchar8	WakeupState;		///*�Ƿ��ڵ͹��Ļ���״̬
}Str_LowPower_Type;


extern Str_LowPower_Type	Str_LowPower_Infra;
extern uchar8 SV_Wakeup_Flag;				///*�к����жϱ�־*///
extern ulong32 SV_Wakeup_Data;				///*���⻽���յ������ݣ�68 11 04*///
extern const uchar8 C_Cap_WhetherUsed;
extern uchar8 Inf_LowpowerPowerFail_No6VBat();
uchar8 InF_GetEnterLowPowerTimerUpdateFlag(void);
#endif
