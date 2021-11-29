
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     LowPower.h
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__LowPower_H
#define	__LowPower_H

#define	C_CheckPowerDownTimes	50				///*掉电中断里检测口线的次数：滤波*///
#define	C_CheckPowerDownCounter	45				///*掉电中断里检测口线有效次数*///
#define	C_CheckPowerOnTimes		6				///*低功耗下检测口线的次数：滤波*///
#define	C_CheckPowerOnCounter	4				///*低功耗下检测口线有效次数*///

#define C_BattPower                0x0F         /*停抄电池有电*/
#define C_EleCapacitor             0xF0         /*超级电容有电*/
#define C_BothBattAndCapacitor     (C_BattPower | C_EleCapacitor)         /*超级电容和抄表电池都有电*/
#define C_NoPower                  0            /*超级电容和抄表电池都没电*/

#define C_RTCRegWpr1	0xca	///*RTC的写保护*///
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

#define C_Enable			0x68		///*使能*///
#define C_Disable			0x00		///*禁止*///
#define C_LimitTimes		120			///*每次醒来后检测按键，连续这么多次后都按下，则禁止该按键的唤醒*///
#define	C_InfraWakeup_7Day	604800		///*7天折算为秒*///
#define	C_AllLossTime		60			///*进入低功耗60s后做全失压*///
#define	C_AllLossPrepare		58			///*进入低功耗58s后准备做全失压*///
#define	C_CheckKeyTimes		10			///*低功耗下，检测上/下翻按键的次数*///

#define C_PowerMode			0x04		///*供电方式：电池供电*///
#define C_PowerModeInit		0xf9		///*供电方式：电池供电*///

#define C_InfraWakeup_Interval	3		///*检查有无红外唤醒的间隔时间：初步定为3s*///
#define C_InfraWakeup_Flag		0x68	///*有红外中断标志*///
#define C_KeyLockCNT		8			///*按键卡死计数器*///
#define	C_LowPower_RTC83min	4980			///*停电情况下，RTC调校每83min更新一次*///

#define	C_PowerOffTime		3			///*进入低功耗3s后做掉电*///

typedef struct
{
	uchar8	Wakeup_En;			///*唤醒使能*///
	uchar8	Times;				///*按键卡死次数、红外满7天标志*///
	uchar8	WakeupState;		///*是否处于低功耗唤醒状态
}Str_LowPower_Type;


extern Str_LowPower_Type	Str_LowPower_Infra;
extern uchar8 SV_Wakeup_Flag;				///*有红外中断标志*///
extern ulong32 SV_Wakeup_Data;				///*红外唤醒收到的数据：68 11 04*///
extern const uchar8 C_Cap_WhetherUsed;
extern uchar8 Inf_LowpowerPowerFail_No6VBat();
uchar8 InF_GetEnterLowPowerTimerUpdateFlag(void);
#endif
