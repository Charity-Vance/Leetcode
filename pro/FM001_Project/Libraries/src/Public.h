
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
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

///*调试程序的宏定义，修改该标志位注意更改startup_ht6x3x文件中：DCD     0xE3FFFFA2      ///*Flash 不加密，Sleep/Hold 下WDT开启
//#define		_DEBUG		1				///*调试程序定义为“1”*///
#define		_DEBUG		0				///*正式程序定义为“0”*///
/*
	从计量芯片读出的脉冲最大阀值,hex格式，目前电能模块用(防飞走)。不同规格类型的表，该预置要计算核对和否合适，不然会影响电能计量
	电压规格	电流规格		脉冲常数    3*1.5Un*2Imax时0.5s脉冲数    10s脉冲数    	取整    	转为16进制数
	3×220/380	3×1.5(6)A		6400		12.16							243.2		244			0xF4
	3×220/380	3×5(60)A		400			13.2							264			264			0x108
	3×220/380	3×10(100)A		300			8.25							132			132			0x84
	3×57.7/100	3×0.3(1.2)A		100000		8.655							173.1		174			0xAE
	3×57.7/100	3×1.5(6)A		20000		8.655							173.1		174			0xAE
	3×57.7/100	3×1(10)A		20000		14.425							288.5		289			0x121
	3×100		3×0.3(1.2)A		100000		10								200			200			0xC8
	3×100		3×1.5(6)A		20000		10								200			200			0xC8
	3×100		3×1(10)A		20000		16.6667							333.333		334			0x14E
*/

#define C_Pluse_Most__Lim    	0x121			/*计量芯片读出的脉冲最大阀值*/



/********支持规约列表的个数********/
#if 0
//#define C_CommProNum		0			/*支持1个规约列表*/
#define C_CommProNum		1			/*支持2个规约列表*/

#define CommProShortOrLong(ShortValue,LongValue) ( (C_CommProNum == 0) ? ShortValue:LongValue ) // ShortValue:16个字节 LongValue:32个字节
#endif

#define	C_MeterICDataNum_T	150

///********macro 大小端模式********///
#define	C_LargeType			0x01			///*大端模式*///
#define	C_LowType			0x02			///*小端模式*///
#define	C_WordType			C_LowType		///**///

///********macro 工作主频********///
#define	C_ClkFosc			0x01			///*主频工作在32.768*///
#define	C_ClkPll			0x02			///*工作在22M*///

///********macro pcb板号********///
#define	C_Pcb2457						0x01			///*-M表*///
#define	C_Pcb2481       	  0x02            ///*智能表、远程表*///
#define	C_PcbVersion		    C_Pcb2481		///*这个宏定义主要用于IO口线、Uart、PWM调制的配置，底层驱动用*///

#define C_MeterType_Module	0x02			///*模块表*///

///********macro 电能表类型********///
#define	C_SmartMeter		0x01            ///*智能表：无费控*///
#define	C_R_SmartMeter		0x02            ///*远程费控：Remote*///
#define	C_L_SmartMeter		0x03            ///*本地费控：Local*///

/********macro 输出数据格式********/
#define	C_Format_BCD			0x01			/*输出BCD格式*/
#define	C_Format_HEX			0x02			/*输出hex格式*/

#define	C_Happen_EventState		0x68			/*事件状态，有发生无恢复*/
#define	C_End_EventState		0x00			/*事件状态，非有发生无恢复*/

#define	C_AAorBBIsActive		0x98			/*AA/BB为有效数据*/
#define	C_AAorBBIsDisactive		0x86			/*AA/BB为无效数据*/
///********macro 是否开启计量参考源温度补偿********///
#define	C_Temp_VrefAotu_En		0x01            ///*开启温度补偿*///
#define	C_Temp_VrefAotu_Dis		0x02            ///*关闭温度补偿*///

///********macro 是否关闭ESAM电源********///
#define	C_ESAMPower_Open		0x01            ///*不关闭ESAM电源*///
#define	C_ESAMPower_Close		0x02            ///*关闭ESAM电源*///

///********macro 是否开启奇次谐波补偿********///
#define	C_Odd_Harmonic_En		  0x01            ///*开启奇次谐波补偿*///
#define	C_Odd_Harmonic_Dis		0x02            ///*关闭奇次谐波补偿*///

///********macro 是否开启偶次谐波补偿********///
#define	C_Even_Harmonic_En		  0x01            ///*开启偶次谐波补偿*///
#define	C_Even_Harmonic_Dis		0x02            ///*关闭偶次谐波补偿*///

///********macro 是否带有超级电容*******///
#define	C_Cap_WhetherUsed_En		  0x01            ///*使用超级电容*///
#define	C_Cap_WhetherUsed_Dis		  0x02            ///*不使用超级电容*///

/********macro 超级电容充电开启时间*******/
#define C_Cap_OpenAfter30min_En			0x01			/*上电30min后超级电容开始充电*/
#define C_Cap_OpenAfter30min_Dis		0x02			/*上电3s后超级电容开始充电*/

///********macro 电表类型标志********///
#define	C_3P3W				0x00			///*三相三线*///
#define	C_3P4W 				0x01			///*三相四线*///

///********macro 电源标志********///
#define	C_PowerOff			0x68            ///*掉电标志*///
#define	C_PowerOn			0x00            ///*有电标志*///
#define	C_PowerFalling		0x86            ///*发生从有电到掉电的沿变标志*///
#define	C_PowerRising		0xa5            ///*发生从掉电到有电的沿变标志*///
#define C_InfraWakeup_Flag		0x68	///*有红外中断标志*///
#define C_Enable			0x68		///*使能*///
#define C_Disable			0x00		///*禁止*///

#define C_EnterLowPowerTimer_NoUpdate	0x00	/*进低功耗时间未更新*/
#define C_EnterLowPowerTimer_Update		0xAA	/*进低功耗时间已更新*/

///********macro 厂内自扩读数据********///
#define		C_ReadRamFlay			0   	//读RAM
#define		C_ReadParaFlay			1		//读厂内参数
#define		C_ReadFlashFlay			2		//读Flash
#define		C_ReadE2Flay			4		//读E2
#define   C_ReadFRAMFlay          5       //读铁电FRAM
#define   C_ReadMCUFlay          3       //读MCU相关信息

#define C_ZeroCurrentOn		1	///*零线电流开启*///
#define C_ZeroCurrentOff	0	///*零线电流关闭*///

///********macro 模块号********///
#define	C_Msg_PowerNetworkMonitoring			0x01		///*电网监测判断消息		*///
#define	C_Msg_Write_PowerNetworkMonitoring      0x02		///*电网监测事件记录写消息	*///
#define	C_Msg_EnergyMetering                    0x03		///*电能计量消息			*///
#define	C_Msg_DemandMetering                    0x04		///*需量计量消息			*///
#define	C_Msg_Communication                     0x05		///*通信接口消息			*///
#define	C_Msg_SettleAccounts                    0x06		///*结算消息				*///
#define	C_Msg_Freeze                            0x07		///*冻结消息				*///
#define	C_Msg_LoadProfile                       0x08		///*负荷记录消息			*///
#define	C_Msg_Display                           0x09		///*显示消息				*///
#define	C_Msg_Deal_RelayStatus                  0x0A		///*继电器功能消息			*///
#define	C_Msg_Deal_MultiRates                   0x0B		///*费率判断消息			*///
#define	C_Msg_BatteryVoltagleMetering           0x0C		///*电池电压测量消息		*///
#define	C_Msg_VoltageQualifiedRateMetering      0x0D		///*电压合格率检测			*///
#define	C_Msg_Dispatch                          0x0E		///*调度					*///
#define	C_Msg_MeterIC							0x0F		///*计量消息模块			*///
#define	C_Msg_Card								0x10		///*卡处理消息模块			*///
#define	C_Msg_BroadcastAddress					0x11		///*以广播的形式发布消息	*///
#define	C_Msg_Esam		                        0x12		///*Esam消息				*///
#define C_Msg_DataProcess						0x13		///*数据层消息				*///
#define C_Msg_CalibrateRC						0x14		///*校准RC振荡消息			*///
#define C_Msg_AllLossVoltage					0x15		///*全失压消息:该消息只在停电唤醒的时候发*///
#define C_Msg_DataProcess_External				0x16		///*数据层消息:扩展功能处理，每秒处理				*///


///********macro 写数据层安全字********///
#define	C_W_SafeFlag				0x68		///*写数据层安全字节值                                                                        *///
#define	C_W_SafeFlag_1              0x08		///*使用时变量在三个地方或上这些值，判断时判断安全字节为0x68，就能确认程序肯定经过这三个地方*///
#define	C_W_SafeFlag_2              0x20		///**///
#define	C_W_SafeFlag_3              0x40		///**///
#define	C_ClearMeterSafeFlag        0x68		///*电表总清安全字节值                                                                        *///
#define	C_ClearMeterSafeFlag_1      0x08		///*使用时变量在三个地方或上这些值，判断时判断安全字节为0x86，就能确认程序肯定经过这三个地方*///
#define	C_ClearMeterSafeFlag_2      0x20		///**///
#define	C_ClearMeterSafeFlag_3      0x40		///**///


///********macro SERR********///
#define	C_SERR_OtherErr				0x01	///*其他错误*///
#define	C_SERR_ReRecharge			0x02	///*重复充值*///
#define	C_SERR_ESAM_VF				0x04	///*ESAM验证错*///
#define	C_SERR_AF					0x08	///*身份认证失败*///
#define	C_SERR_CNErr				0x10	///*客户编号不匹配*///
#define	C_SERR_RechargeNumErr		0x20	///*充值次数错*///
#define	C_SERR_RechargeHoarding		0x40	///*购电超囤积*///
#define	C_SERR_FWAddressErr			0x80	///*地址异常*///
#define	C_SERR_Meter_Safeguard		0x100	///*电表挂起*///

///********macro io********///
///*input io*///
#define	C_KeyUp					0x01		///*上翻键          *///
#define	C_KeyDown           	0x02		///*下翻键          *///
#define	C_KeyPrg            	0x03		///*编程键          *///
#define	C_KeyOpenCover      	0x04		///*开表盖          *///
#define	C_KeyOpenTerminal   	0x05		///*开端尾盖        *///
#define	C_CheckAuPower      	0x06		///*辅助电源检测    *///
#define	C_CheckMainPower    	0x07		///*主电源检测      *///
#define	C_Magnetic          	0x08		///*磁场检测        *///
#define	C_MeterICIRQ        	0x09		///*计量芯片IRQ中断 *///
#define	C_RelayStatus       	0x0a		///*继电器状态检测  *///
#define	C_ModuleStatus      	0x0b		///*模块发送状态指示*///
#define	C_CardStatus        	0x0c		///*插卡状态检测    *///
#define C_Key3s					0x10		///*按键3s有效		*///
#define	C_InsertCard			0x11		///*有插卡：任何卡	*///
#define	C_KeyUpForRelay			0x12		///*上翻键持续3s    *///
#define	C_KeyDownForRelay       0x13		///*下翻键持续3s    *///
#define	C_ExternalRelayStatus   0x14		///*外置继电器状态检测  *///

#define	C_Valid					0x63		///*输入口线状态有效*///
#define	C_Invalid				0x6c		///*输入口线状态无效*///
///*output Urat*///
#define	C_RS485_1				0x01		///*第一路485*///
#define	C_RS485_2				0x02		///*第二路485*///
#define	C_IR					0x00		///*红外通道*///
#define	C_Module				0x03		///*模块通道*///
#define	C_ESAM					0x04		///*ESAM*///
#define	C_Card					0x05		///*Card*///
///*output io*///
#define	C_BackLight				0x21		///*背光            *///
#define	C_TripLed           	0x22        ///*拉闸指示灯      *///
#define	C_Beep              	0x23        ///*蜂鸣器          *///
#define	C_WarnOut           	0x24        ///*报警继电器      *///
#define	C_MultiFunction			0x25		///*多功能输出      *///
#define	C_FlashPower        	0x26        ///*Flash电源控制   *///
#define	C_CapCharge         	0x27        ///*超级电容充电控制*///
#define	C_CapDischarge      	0x28        ///*超级电容放电控制*///
#define	C_WakeUpPower       	0x29        ///*6V电池电源控制  *///
#define	C_BattDischarge     	0x2a        ///*6V电池防钝化控制*///
#define	C_Relay             	0x2b        ///*负荷开关控制    *///
#define	C_EventOut           	0x2c        ///*主动上报        *///
#define	C_ModuleReset       	0x2d        ///*模块复位        *///
#define	C_ModuleSet         	0x2e        ///*模块设置        *///
#define	C_InfraPower			0x2f		///*红外接收电源*///
#define	C_EsamPower             0x30		///*ESAM电源    *///
#define	C_CardPower             0x31		///*CARD电源    *///
#define	C_EsamReset             0x32		///*ESAM复位    *///
#define	C_CardSck               0x33		///*卡时钟使能  *///
#define	C_CardReset             0x34		///*卡复位      *///
#define	C_MeterICPower          0x35		///*计量芯片电源*///


#define	C_On  					0x68		///*外部设备打开                *///
#define	C_Off                   0x66        ///*外部设备关闭                *///
#define	C_Hold                  0x69        ///*外部设备保持：专指内置继电器*///
#define	C_SecondPulse			0x62		///*多功能口输出秒脉冲*///
#define	C_DemandPulse			0x63		///*多功能口输出需量周期信号*///
#define	C_RatePulse				0x64		///*多功能口输出时段费率投切信号*///
#define	C_ClosePulse			0x65		///*多功能口输出关闭：即输出脉冲信号后关闭输出*///
#define	C_PowerInit				C_SecondPulse	///*上电后多功能脉冲输出方式*///

#define	C_RTCLen				0x07		///*读写RTC时数据长度，固定为7字节*///
#define	C_LCDLen				0x20		///*LCD驱动缓存字节数*///
#define	C_DataCodeLen			0x04		///*数据标识码字节数*///
#define	C_KillZero1       		0x01		///*灭1个零*///
#define	C_KillZero2       		0x02		///*灭2个零*///
#define	C_KillZero3       		0x03		///*灭3个零*///
#define	C_KillZero4       		0x04		///*灭4个零*///
#define	C_KillZero5       		0x05		///*灭5个零*///
#define	C_KillZero6       		0x06		///*灭6个零*///
#define C_KillZero7				0x07		///*灭7个零*///
#define	C_KillZero8       		0x08		///*灭8个零*///
#define C_KillZero9			    0x09		///*灭9个零*///
#define	C_Notkillzero     		0x68		///*不灭零 *///
#define	C_SF_Err	     		0xff		///*显示特殊字符*///
/*小数位数*/
#define C_DotNum_0                              0           /*0位小数*/
#define C_DotNum_1                              1           /*1位小数*/
#define C_DotNum_2                              2           /*2位小数*/
#define C_DotNum_3                              3           /*3位小数*/
#define C_DotNum_4                              4           /*4位小数*/


/*功率最大限值*/
#define C_PowerMax				799999
///*********主动上报相关宏定义***********///

#define C_Times_ContralLoopErr    		0		///*控制回路故障		*///
#define C_Times_ESAMErr      			1  		///*ESAM故障			*///
#define C_Times_InitialCardErr          2 		///*内卡初始化错误		*///
#define C_Times_RTCBatteryErr           3		///*时钟电池故障		*///
#define C_Times_InternalProgramErr      4   	///*内部程序错误		*///
#define C_Times_MemoryErr               5   	///*存储器故障			*///

#define C_Times_RTCErr                 	7		///*时钟故障			*///
#define C_Times_PowerBatteryErr         8     	///*停电抄表电池故障	*///
#define C_Times_OverDraft      			9		///*透支状态			*///
#define C_Times_OpenMeterCover        	10		///*开表盖				*///
#define C_Times_OpenTerminalCover     	11		///*开端尾盖			*///
#define C_Times_MagneticCheck     		12		///*恒定磁场干扰		*///
#define C_Times_PowerError     			13		///*电源异常			*///
#define C_Times_OpenRelay     			14		///*跳闸成功			*///
#define C_Times_CloseRelay     			15		///*合闸成功			*///

#define C_Times_ALossVoltage    		16		///*A失压				*///
#define C_Times_ALessVoltage      		17		///*A欠压				*///
#define C_Times_AOverVoltage            18		///*A过压				*///
#define C_Times_ALossCurrent            19		///*A失流				*///
#define C_Times_AOverCurrent            20		///*A过流				*///
#define C_Times_AOverLoad               21    	///*A过载				*///
#define C_Times_APowerReverse           22     	///*A功率反向			*///
#define C_Times_ALossPhase              23   	///*A断相				*///
#define C_Times_ALessCurrent     		24		///*A断流				*///

#define C_Times_BLossVoltage    		32		///*B失压				*///
#define C_Times_BLessVoltage      		33		///*B欠压				*///
#define C_Times_BOverVoltage            34		///*B过压				*///
#define C_Times_BLossCurrent            35		///*B失流				*///
#define C_Times_BOverCurrent            36		///*B过流				*///
#define C_Times_BOverLoad               37   	///*B过载				*///
#define C_Times_BPowerReverse           38     	///*B功率反向			*///
#define C_Times_BLossPhase              39   	///*B断相				*///
#define C_Times_BLessCurrent     		40		///*B断流				*///

#define C_Times_CLossVoltage    		48		///*C失压				*///
#define C_Times_CLessVoltage      		49		///*C欠压				*///
#define C_Times_COverVoltage            50		///*C过压				*///
#define C_Times_CLossCurrent            51		///*C失流				*///
#define C_Times_COverCurrent            52		///*C过流				*///
#define C_Times_COverLoad               53    	///*C过载				*///
#define C_Times_CPowerReverse           54      ///*C功率反向			*///
#define C_Times_CLossPhase              55   	///*C断相				*///
#define C_Times_CLessCurrent     		56		///*C断流				*///

#define C_Times_ReversedVoltage    		64		///*电压逆相序			*///
#define C_Times_ReversedCurrent      	65		///*电流逆相序			*///
#define C_Times_UnbalancedVoltage       66     	///*电压不平衡			*///
#define C_Times_UnbalancedCurrent       67     	///*电流不平衡			*///
#define C_Times_SubPowerOff        		68		///*辅助电源失电		*///
#define C_Times_PowerOff                69   	///*掉电				*///
#define C_Times_OverDemadn              70    	///*需量超限			*///
#define C_Times_OverPowerFact           71      ///*功率因数超限		*///
#define C_Times_SeriousUnbalancedCurrent 72   	///*电流严重不平衡		*///
#define C_Times_TActivePowerReversed     73 	///*总有功功率反向		*///
#define C_Times_NoVoltage            	74		///*全失压				*///

#define C_Times_Program    				80		///*编程发生过			*///
#define C_Times_MeterClear    			81		///*电表清零过			*///
#define C_Times_DemandClear    			82		///*需量清零过			*///
#define C_Times_EventClear    			83		///*事件清零过			*///
#define C_Times_ReworkTime    			84		///*修改时间过			*///
#define C_Times_ReworkTimeInterval    	85		///*修改时段表			*///
#define C_Times_ReworkTimeZone    		86		///*修改时区表			*///
#define C_Times_ReworkWeekDay    		87		///*修改周休日			*///
#define C_Times_ReworkHoliday    		88		///*修改节假日			*///
#define C_Times_ReworkActiveMode    	89		///*修改有功组合方式	*///
#define C_Times_ReworkReactiveMode1    	90		///*修改无功组合方式1	*///
#define C_Times_ReworkReactiveMode2    	91		///*修改无功组合方式2	*///
#define C_Times_ReworkSettlemantDay    	92		///*修改结算日			*///
#define C_Times_ReworkRatesCharge    	93		///*修复费率表			*///
#define C_Times_ReworkStepPara    		94		///*修改阶梯表			*///
#define C_Times_ReworkKey    			95		///*密钥更新过			*///

#define	C_SecondPulseOutput  			0x00	  ///*秒脉冲*///
#define	C_DemandPulseOutput  			0x01	  ///*需量周期脉冲*///
#define	C_RatePulseOutput    			0x02	  ///*时段投切脉冲*///

/*************费率数,修改需要修改两个 BCD和Hex 都要改！！！*************/
#define C_MaxRatesNum_BCD						0x12	            	/*最大费率数 BCD*/
#define C_MaxRatesNum	    					12	                	/*最大费率数 Hex*/
#define C_RatesNumTol	    					(C_MaxRatesNum+1)		/*费率数索引最大*/

/*阶梯表参数相关数据长度*/
#define C_StepSettlementLen						0x03					/*1个阶梯结算日参数的长度*/
#define C_StepChargeStartAddr					24						/*阶梯参数中阶梯电价对应的起始地址*/
#define C_StepSettlementStartAddr				52						/*阶梯参数中阶梯结算日参数对应的起始地址*/
#define C_StepSettlementNum						4						/*最大阶梯结算日参数个数*/
#define C_StepSettlementTotalLen				(C_StepSettlementLen * C_StepSettlementNum)					/*1个阶梯结算日参数的长度*/
#define C_StepSettlementDay_MM					2						/*阶梯结算日中月的偏移位置*/

/*************时段数最大,修改需要修改两个 BCD和Hex 都要改！！！*************/
#define C_RatesParmNum	    14	                /*最大日时段数 HEX*/

/*************事件关联列表个数，个数、长度一起修改！！！*************/
#define C_EventMAXRelatedOAD         60
#define C_EventMAXRelatedOADLen      (C_EventMAXRelatedOAD * 2)	 /*读取关联列表的最大长度，2字节一个*C_EventMAXRelatedOAD*/
#define C_FreezeMAXRelatedOAD        96         /*冻结698关联序号表最大支持个数*/
#define C_698Free_OADTabDataType     6          /*每类冻结OAD列表格式：2字节序号+2字节冻结周期+2字节存储深度*///
#define C_698Free_OADTabLen          (C_FreezeMAXRelatedOAD*C_698Free_OADTabDataType)       /*冻结698关联序号表*/

/*读取冻结数据的最大长度*/
#define C_FreezeMAXLen               2000

///*************数据抄读相关********************************************///
#define C_NotSupportAOD_Data  	 0xaa       		///*不支持的698冻结OAD数据*///
#define C_NotSupportAOD_DataBB   0xbb       		///*1）与模块写记录时，读数据层读不到反AA C_NotSupportAOD_Data作区分2）费率数超，数据层应答0xBB*///
#define C_NotSupportAOD_DataCC   0xcc       		///*要读的OAD列表，所有的OAD在关联列表中全部查不到标志。主要用于周期冻结抄读，避免循环查找时间过长*///
#define CL_NotSupportAOD_DataBB	 1			        //数据长度费率数超，数据层应答0xBB，0xBB长度1字节

///*************电能长度公共********************************************///
#define C_EnergyPulseLen	        0x05	///*数据层存储的电能脉冲数的长度*///
#define C_EnergyCommLen		        0x04	///*通信读取电能长度*///
#define C_AccurateEnergyCommLen		0x05	///*通信读取精确电能长度*///
#define C_EnergyCommPulseLastLen    0x01	///*通信读取脉冲尾数长度*///
#define C_DisEnergyCommPulseLastLen 0x05	///*显示读取脉冲尾数长度*///

#define C_EnergyNature2BCDLen		0x04	/*属性2，BCD，2位小数电能长度4字节*/
#define C_EnergyNature4BCDLen		0x08	/*属性4，BCD，4位小数电能长度8字节*/
#define C_EnergyNature2HEXLen		0x04	/*属性2，HEX，2位小数电能长度4字节*/
#define C_EnergyNature4HEXLen		0x05	/*属性4，HEX，4位小数电能长度5字节*/
#define C_EnergyNature4HEXLen_Comm	0x08	/*通信属性4，HEX，4位小数电能长度8字节*/

/*编程事件*/
#define	ProgOpClock_O	        4
#define	ProgEndTime		        11
#define	ProgDI_O		        20
#define	ProgCrc_O		        (20 + 50)
#define ProgOADLen              CLProgOADGather	/*一共记录10个标志码，每个标志码加一个类型是0AD还是OMD*/
#define	CLProgFixedData			20				/*序号4 + 发生时间7 + 结束时间7 + 发生源1 + 上报状态1*/

/*继电器描述符*/
#define CLRelayDescrip                  5          /*继电器描述符长度，5字节*/
#define CLRelayCurrentState             1          /*继电器状态，数据长度，1字节*/
#define CLRelaySwitchNature             1          /*继电器开关属性， 数据起始偏移*/
#define CLRelayWiringState              1          /*继电器接线状态， 数据起始偏移*/

#define CLRelayUnit                     (CLRelayDescrip + CLRelayCurrentState + CLRelaySwitchNature + CLRelayWiringState)       /*继电器接线状态， 数据起始偏移*/

//698兼容645增加
#define C_Flag03   0x03  ///*DI0为03*///
#define C_Flag10   0x10  ///*DI0为10*///
#define C_Flagelse 0x00  ///*其他DI0*///
//编程事件698存储，读出格式为：4+7+7+1+1+4*10
#define C_ProgEventHappen  	4  ///*编程记录数据发生时间偏移位置*///
#define C_ProgEvent			19        ///*编程记录数据关联OAD偏移位置*///
#define	CLProgram_Note_645	                 50    	        ///*645编程记录数据长度（上1-上10）*///
#define	CLProgram_Note_Code_645	             4    	       ///*645编程记录操作者代码长度*///
#define CLProgram_Note_698_DataIn              79           ///*698编程事件读取长度*///

#define CDrive_Report_Mode_645_Judge      0x001F042500DFFD89           ///*645默认允许上报项（电源异常、恒定磁场、开表盖、跳合闸、过流、失压、失流、掉电,电表清零(0x000200200019F400)
                                       ///*+20200227新增负荷开关误动作，时钟电池电压低，停抄电池欠压，开端钮盖，欠压，过压，功率反向，断相，电压逆相序，电压不平衡，全失压，校时，事件清零，需量清零，编程+时钟故障
#define CReport_645_Judge_Num    41    //支持的事件个数，645默认允许上报项（电源异常、恒定磁场、开表盖、跳合闸、过流、失压、失流、掉电,电表清零）16个+23个（同上描述）+1个时钟故障+总有功功率反向


#define C_pNULL_NoCode   0x00  	/*指针为空，不需要返回编码类型是用*/
typedef struct
{
	ulong32	OAD;	     ///*698OAD*///
	ulong32 DI;          ///*645DI*///
}Str_ParaChange_OADToDI_Table;

//698兼容645增加

///******公共结构体********///

typedef struct
{
	uchar8 PowerFlag;	///*掉电标志，用于各个消息处理模块自行判断是否进行掉电保存，C_PowerDown表示掉电准备进入低功耗，C_PowerOn表示有电*///
	uchar8 SourceAddr;	///*源消息号*///
	uchar8 DerictAddr;	///*目的消息号*///
	uchar8 Length;		///*Parameter的长度*///
	uchar8 *Parameter;	///*参数，长度不定*///
}Str_Msg_Parameter;


typedef struct
{
	uchar8 Deriction;		        /*功率反向        */
	long32 ActivePower_TABC[4];		/*当前合相ABC有功功率*/
	long32 ReativePower_TABC[4];	/*当前合相ABC无功功率*/
}Str_RealtimePower_Type;

typedef struct
{
    uchar8  FixedData[CLProgFixedData];                           /*第一个标识码编程时刻*/
    uchar8  DI[CProgOADNum][CLProgTypeOADGather];    /*编程最近的10个标识码*/
    ushort16 Crc;
}Str_ProgRecord;
typedef struct
{
    uchar8  Opclock[7];             ///*第一个标识码编程时刻*///
    uchar8  OpCode[4];              ///*第一个标识码编程时操作者代码*///
    uchar8  DI[10][4];                 ///*编程最近的10个标识码*///
    ushort16 Crc;
}Str_ProgRecord_645;


typedef struct
{
	ulong32	ConectOverTime;			/* 期望的应用连接超时时间*///
	ulong32	ConectOverTime_termal;	/* 期望的应用连接超时时间终端*///
	ushort16	ProtocolVersion;			/* 协议版本号*///
	ushort16	ClientTxMaxLen;			/* 客户机接收帧最大尺寸*///
	ushort16	ClientRxMaxLen;			/* 客户机发送帧最大尺寸*///
	ushort16	ClientAPDUMax;			/* 客户机最大可处理的APDU尺寸*///
	uchar8	ProtocolConformance[8];	/* 协议一致性块*///
	uchar8	FunctionConformance[16];	/* 功能一致性块*///
	uchar8	ClientRxMaxLenNum;		/* 客户机接收帧最大窗口尺寸*///
	uchar8	Com_NO;				/*当前应用连接建立通道*///
	ushort16	CurrentConectAPDULen_Tx;	/* 当前有效应用连接协商尺寸*///
	ushort16	CurrentConectAPDULen_Rx;	/* 当前有效应用连接协商尺寸*///
	uchar8	Com_Right;				/*应用连接权限*///
	ushort16	CRC16;					/**///
}ConectRequest_Type;
///********macro 厂内厂外模式*********///
#define C_FactoryInType     0x01
#define C_FactoryOutType    0x02

#define C_NotClearCurrData	0x00
#define C_ClearCurrData		0x01

///********macro ADC处理标志*********///
#define	C_ADC_Iint						0x00	///*ADC初始化标志*///
#define	C_ADC_CmpAndJec				0x01	///*ADC温度测量时钟调校调用*///
#define	C_ADC_Lowpower				0x02	///*ADC温度测量时钟调校调用*///

#define C_GetADC_On    0x55         //温度补偿采样开启
#define C_GetADC_Off   0x00         //温度补偿采样关闭

//RTC故障判断
#define	C_RTC_ERR				0x86	///*RTC故障；RTC故障发生过*///
#define	C_RTC_OK				0x00	///*RTC正常；RTC故障未发生报过*///
#define	C_RTC_ERR_BackTime		0x55	///*RTC故障且备份时间也故障*///
#define	C_RTCERR_MeterWorkState	0x80	///*电表运行特征字1中的RTC故障位*///

//数据标识判断使用
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

	uchar8 V_ucPowerDeriction;				///*功率方向*///
}Struct_Energy_Type;


//typedef struct
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
//}Struct_RTC_Adj;


///********macro for message type********///
#define Pt_DisplayStatus			0x01	///*显示状态字符消息类型*///
#define Pt_CodeID					0x02	///*标识码消息类型*///
#define Pt_RelayStateFlag			0x03	///*继电器相关标志消息类型*///
#define Pt_Dispatch_Timing			0x04	///*调度定时器消息类型*///
#define Pt_DemandStatus				0x05	///*最大需量标志消息类型*///
#define Pt_MsgFreezeImmediately		0x06	///*立即冻结消息*///
#define Pt_7DayAdd_FreezeTime		0x07	///*补日冻结消息类型*///
#define Pt_SettleAdd_Time			0x08	///*结算时间消息类型*///
#define Pt_StepSwitchFlag			0x09	///*阶梯切换消息类型*///
#define PT_Msg_UpdataKey_Review		0x0A	///*更新*///
#define PT_EventNo					0x0B	///*事件记录号消息类型*///
#define Pt_HappenTime				0x0C	///*事件记录发生时间消息类型*///
#define Pt_EndTime					0x0D	///*事件记录结束时间消息类型*///
#define Pt_ParaMetersChange			0x0E	///*与费率有关的参数修改消息类型*///
#define Pt_Initialization			0x0F	///*初始化消息类型*///
#define Pt_FristCheckDayChange		0x10	///*修改第一结算日消息类型*///
#define PT_CMsg_UpdataKey_Review	0x11	///*通信通知更新密钥消息*///
#define PT_CMsg_UpdKey_Rv_PWOn		0x12	///*上电初始化*///
#define Pt_Comm_No					0x13	///*通信发送解析函数时，所携带的通道号*///
#define Pt_Dispatch_Key				0x14	///*调度按键处理消息类型*///
#define Pt_EventClearDI				0x15	///*事件记录清零标识码消息类型*///
#define Pt_VoltageQR				0x16	///*电压合格率统计消息类型*///
#define Pt_DisplayID				0x17	///*液晶查看显示数据标识码数据类型*///
#define Pt_MeterClear				0x18	///*电表清零*///
#define Pt_InitialMeterIC			0x19	///*计量模块初始化消息*///
#define	Pt_YearCheckDayChange		0x1A	///*年结算日变化消息*///
#define	Pt_ResetEsam				0x1B	///*复位Esam模块消息*///
#define	Pt_CardFlag					0x1C	///*本地表插卡 消息参数*///
#define Pt_ERRXXDisplay				0x1d	///*插卡异常显示消息*///
#define	Pt_RatePrice				0x1E	///*更新费率电价消息*///
#define Pt_CalibrateRC				0x1F	///*校准RC振荡器消息*///
#define Pt_VRQTimeChange            0x20    /*zlj新增，通信修改时间发送给电压合格率模块*/
///********macro for message length********///
#define Pt_DisplayStatus_Len			0x03	///*显示状态字符消息长度*///
#define Pt_CodeID_Len					0x04	///*标识码消息长度*///
#define Pt_RelayStateFlag_Len			0x01	///*继电器相关标志消息长度*///
#define Pt_Dispatch_Timing_Len			0x01	///*调度定时器消息长度*///
#define Pt_Dispatch_Timing_Freeze_Len	0x08	///*调度定时器发送给冻结消息长度*///
#define Pt_DemandStatus_Len				0x01	///*最大需量标志消息长度*///
#define Pt_MsgFreezeImmediately_Len		0x00	///*立即冻结消息*///
#define Pt_7DayAdd_FreezeTime_Len		0x07	///*补日冻结消息长度*///
#define Pt_SettleAdd_Time_Len			0x07	///*结算时间消息长度*///
#define Pt_StepSwitchFlag_Len			0x07	///*阶梯切换消息长度*///   /*zlj,长度之前是6，改为7，因为年改为2字节*/
#define PT_Msg_UpdataKey_Review_Len		0x01	///*更新密钥消息长度*///
#define PT_EventNo_Len					0x01	///*事件记录号消息长度*///
#define Pt_HappenTime_Len				0x06	///*事件记录发生时间消息长度*///
#define Pt_EndTime_Len					0x06	///*事件记录结束时间消息长度*///
#define Pt_ParaMetersChange_Len			0x01	///*与费率有关的参数修改消息长度*///
#define Pt_Initialization_Len			0x00	///*初始化消息类型*///
#define Pt_FristCheckDayChange_Len		0x00	///*修改第一结算日消息类型*///
#define PT_CMsg_UpdataKey_Review_Len	0x00	///*密钥更新消息长度*///
#define PT_CMsg_UpdKey_Rv_PWOn_Len		0x00	///*上电初始化发生密钥更新消息长度*///
#define Pt_Comm_No_Len					0x01	///*通信发送解析函数时，所携带的通道号*///
#define Pt_Dispatch_Key_Len				0x01	///*调度按键处理消息类型*///
#define Pt_EventClearDI_Len				0x04	///*事件记录清零标识码消息类型*///
#define Pt_VoltageQR_Len				0x00	///*电压合格率统计消息类型*///
#define Pt_DisplayID_Len				0x0B	///*液晶查看显示数据标识码数据长度，4字节标识码加1字节显示屏号*///
#define	Pt_MeterClear_Len  				0x00	///*电表清零*///
#define Pt_InitialMeterIC_Len			0x00	///*计量模块初始化消息长度*///
#define Pt_YearCheckDayChange_Len		0x00    ///*修改年结算日参数*///
#define	Pt_ResetEsam_Len				0x00	///*复位Esam模块消息长度*///
#define	Pt_CardFlag_Len					0x00	///*本地表插卡 消息参数长度*///
#define	Pt_DataProcess_Len				0x00	///*数据层 消息参数长度*///
#define Pt_ERRXXDisplay_Len				0x03	///*插卡异常显示消息长度*///
#define	Pt_RatePrice_Len				0x00	///*更新费率电价消息*///
#define Pt_CalibrateRC_Len				0x00	///*校准RC振荡器消息长度*///
#define Pt_AllLossVoltage_Len			0x00	///*全失压处理消息长度*///
#define Pt_VRQTimeChange_Len            0x0E    /*zlj新增，通信修改时间发送给电压合格率模块长度，修改前时间7字节修改后时间7字节*/
///********macro for Pt_RelayStateFlag********///
#define C_Relay_Close_Direct		0x01		///*直接合闸        *///
#define C_Alarm						0x02		///*报警            *///
#define C_Alarm_Release				0x03		///*报警解除        *///
#define C_AlarmOpenRelay			0x04		///*本地预跳闸      *///
#define C_Relay_OpenNow				0x05		///*立即跳闸        *///
#define C_KeyDownDelay3s			0x06		///*按键3s消息		*///
#define C_Protect					0x07		///*当前处于保电	*///
#define C_NotProtect				0x08		///*当前不保电		*///
#define C_PurchaseOK				0x09		///*购电成功		*///
#define C_Relay_Close_Direct_Init	0x0A		///*初始化命令直接合闸*///

#define	C_VoltageOk		  0x01	///* 表示当前电压允许跳合闸 *///
#define	C_VoltageErr		0x02	///* 表示当前电压不允许跳合闸 *///
///********macro for Pt_DisplayStatus********///
#define C_TwinkleDisplay		0x40	///*闪烁显示*///
#define C_AlwaysDisplay			0xC0	///*常显*///
#define C_NotDisplay			0x00	///*不显示*///

#define C_AxisSign				1  		///*坐标轴				*///
#define C_Q1Sign                2       ///*1象限显示符号		*///
#define C_Q2Sign                3       ///*2象限显示符号		*///
#define C_Q3Sign                4       ///*3象限显示符号		*///
#define C_Q4Sign                5       ///*4象限显示符号		*///
//#define C_Step1Sign             6       ///*阶梯1        		*///
//#define C_Step2Sign             7       ///*阶梯2        		*///
//#define C_Step3Sign             8       ///*阶梯3        		*///
//#define C_Step4Sign             9       ///*阶梯4        		*///
//#define C_Rate1Sign             10      ///*费率1        		*///
//#define C_Rate2Sign             11      ///*费率2        		*///
//#define C_Rate3Sign             12      ///*费率3        		*///
//#define C_Rate4Sign             13      ///*费率4        		*///
#define C_TSign                 12      ///*费率字符T        		*///
#define C_LSign                 13      ///*阶梯字符L        		*///
#define C_GPRSSign              14      ///*天线符号     		*///
#define C_GPRSSignalSign1       15      ///*信号强度1    		*///
#define C_GPRSSignalSign2       16      ///*信号强度2    		*///
#define C_GPRSSignalSign3       17      ///*信号强度3    		*///
#define C_GPRSSignalSign4       18      ///*信号强度4    		*///
#define C_ModuleComSign         19      ///*模块通信符号 		*///
#define C_ComSign               20      ///*通信电话符号 		*///
#define C_ComChannel1Sign       21      ///*通信1符号    		*///
#define C_ComChannel2Sign       22      ///*通信2符号    		*///
#define C_ProgramEnableSign     23      ///*红外认证有效   		*///
#define C_HoldUpSign            24      ///*身份认证挂起 		*///
#define C_PublicKeySign         25      ///*公钥符号     		*///
#define C_AlarmSign             26      ///*报警标志     		*///
#define C_ReadCardSign          27      ///*“读卡”字符			*///
#define C_DoingSign             28      ///*“中”字符		   	*///
#define C_SuccessSign           29      ///*成功         		*///
#define C_FailSign              30      ///*失败         		*///
#define C_PurchaseSign          31      ///*请购电       		*///
#define C_OverdrawSign          32      ///*透支         		*///
#define C_RealayOpenSign        33      ///*拉闸         		*///
#define C_UaSign                34      ///*Ua           		*///
#define C_UbSign                35      ///*Ub           		*///
#define C_UcSign                36      ///*Uc           		*///
#define C_NegativePhaseSign     37      ///*逆相序       		*///
#define C_IaNegativeSign        38      ///*Ia电流前“-”			*///
#define C_IaSign                39      ///*Ia           		*///
#define C_IbNegativeSign        40      ///*Ib电流前“-”			*///
#define C_IbSign                41      ///*Ib           		*///
#define C_IcNegativeSign        42      ///*Ic电流前“-”			*///
#define C_IcSign                43      ///*Ic           		*///
#define C_TimeTable1Sign        44      ///*第一套时段表 		*///
#define C_TimeTable2Sign        45      ///*第二套时段表 		*///
#define C_RTCBatterySign        46      ///*时钟电池欠压 		*///
#define C_PowerBatterySign      47      ///*停抄电池欠压 		*///
#define C_HoardingSign			48      ///*超囤积标志        	*///
#define C_CurrentStep           49      ///*当前套阶梯        	*///
#define C_BakStep               50      ///*备用套阶梯有效符号	*///
#define C_BackLED               51      ///*背光		       	*///
#define C_WarnOutPut            52      ///*报警输出    		*///
#define C_Beeper                53      ///*蜂鸣器        		*///
#define C_RelayStatusLED        54      ///*跳闸指示灯			*///

///********macro for Pt_Dispatch_Timing ********///
#define C_SystemSecondChange	0x01      ///*调度系统秒变化			*///
#define C_SystemMinChange		0x02      ///*调度系统分钟变化			*///
#define C_SystemHourChange		0x03      ///*调度系统小时变化			*///
#define C_SystemDateChange		0x04      ///*调度系统日变化			*///
#define C_SystemMonthChange		0x05      ///*调度系统月变化			*///
#define C_SystemYearChange		0x0c      ///*调度系统年变化			*///


#define C_SecondChange			0x06      ///*调度基本节拍秒变化		*///
#define C_MinChange				0x07      ///*调度基本节拍分钟变化		*///
#define C_HourChange			0x08      ///*调度基本节拍小时变化		*///
#define C_5MS					0x09      ///*调度基本节拍5ms			*///
#define C_100MS					0x0A      ///*调度基本节拍100ms			*///
#define C_HalfSecond			0x0B      ///*调度基本节拍500ms			*///

/********macro for Pt_DemandStatus********/
#define	C_RewortDemandInternal		0x10	/*修改最大需量周期*/
#define	C_MeterClear				0x11	/*电表清零*/
#define	C_DemandClear				0x12	/*需量清零*/
#define	C_Settlement				0x13	/*过结算日*/
#define	C_RatesChanged				0x14	/*费率改变*/
#define	C_DemandPowerUp				0x15	/*上电*/
#define	C_DataFreeze				0x16	/*过日冻结*/
#define	C_Settlement_ReSettle_Day1	0x17	/*修改第一结算日*/

///********macro for Pt_StepSwitchFlag********///
#define	C_Step_MToY					0X16	///*月到年切换*///
#define	C_Step_YToM					0X17	///*年到月切换*///
#define	C_Step_YToY					0X18	///*年到年切换*///

#define	C_Step_SetttleChange	    0x19	/*阶梯结算切换*/
///********macro for communication********///
#define C_ContinueReceive			0x30	///*继续接收*///
#define C_AbortReceive				0x31	///*退出接收*///
#define C_CorrectFrame				0x32	///*收到正确帧*///

#define C_ContinueTransmit			0x33	///*继续发送*///
#define C_AbortTransmit				0x34	///*退出发送*///
#define	C_AbortTransmit_SetBPS		0x35	///*设置BPS应答结束，退出发送*///

#define		C_bps_38400					0x80	///*波特率38400*///
#define		C_bps_19200					0x40	///*波特率19200*///
#define		C_bps_9600					0x20	///*波特率9600*///
#define		C_bps_4800					0x10	///*波特率4800*///
#define		C_bps_2400					0x08	///*波特率2400*///
#define		C_bps_1200					0x04	///*波特率1200///
#define		C_bps_600					0x02	///*波特率600*///
#define		C_bps_300					0x01	///*波特率300*///
#define     C_bps_Error                 0xFF    ///*错误的波特率*///

///*698波特率对应的特征字*///
#define		C_bps_38400_698					0x08	///*波特率38400*///
#define		C_bps_19200_698					0x07	///*波特率19200*///
#define		C_bps_9600_698					0x06	///*波特率9600*///
#define		C_bps_4800_698					0x04	///*波特率4800*///
#define		C_bps_2400_698					0x03	///*波特率2400*///
#define		C_bps_1200_698					0x02	///*波特率1200///
#define		C_bps_600_698					0x01	///*波特率600*///
#define		C_bps_300_698					0x00	///*波特率300*///

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
#define		C_Relay_Open_comm                   0x1A	///*拉闸*///
#define		C_Relay_Close_Allow_comm            0x1B    ///*合闸允许*///
#define		C_Relay_Close_Direct_comm           0x1C    ///*立即合闸*///
#define		C_AlarmOpenRelay_Allow_comm         0x1E    ///*跳闸后自动恢复为立即合闸*///
#define		C_AlarmOpenRelay_Direct_comm        0x1D    ///*跳闸后自动恢复为合闸允许*///
#define		C_Alarm_comm                        0x2A    ///*远程报警*///
#define		C_Alarm_Release_comm                0x2B    ///*远程报警解除*///
#define		C_Protect_Current_comm              0x3A    ///*保电*///
#define		C_Protect_Current_Release_comm		0x3B    ///*保电解除*///

#define 	C_Relay_Close_Direct_Status			0x0001	///*直接合闸                   *///
#define 	C_Relay_Close_Allow_Status			0x0002	///*允许合闸                   *///
#define 	C_Relay_Open_Status					0x0004	///*直接跳闸                   *///
#define 	C_Relay_DelayOpen_Time_Status		0x0008	///*延时跳闸（跳闸延时时间非0）*///
#define 	C_AlarmOpenRelay_Status				0x0010	///*跳闸自动恢复               *///
#define 	C_Relay_DelayOpen_Current_Status	0x0020	///*延时跳闸（大电流）         *///
#define 	C_Protect_Current_Status			0x0100	///*保电                       *///
#define 	C_Protect_Current_Release_Status	0x0200	///*保电解除                   *///
#define 	C_Alarm_Status						0x0400	///*报警                       *///
#define 	C_Alarm_Release_Status				0x0800	///*报警解除                   *///

#define		C_Meter_Safeguardfailure			0x0001	///* 电表挂起  *///
#define		C_MACError_failure					0x0002	///* MAC错误  *///
#define		C_PasswordError_failure				0x0004	///* 密码错或未授权  *///
#define		C_AuthOverTime_failure				0x0008	///* 身份认证超时  *///
#define		C_ActTimeUnvalid_failure			0x0010	///* 执行时间无效  *///
#define		C_Protect_Openfailure				0x0020	///*跳闸失败（保电）           *///
#define		C_Protect_AlarmOpenfailure			0x0040	///*跳闸自动恢复失败（保电）   *///
#define		C_TimeUnvalid_AlarmOpenfailure		0x0080	///*跳闸自动恢复持续时间无效   *///
#define		C_RelayOpen_OpenAlarmfailure		0x0100	///*跳闸自动恢复失败（跳闸）   *///


///********macro for EventRecord********///
#define		C_TotalVoltageLoseEventNo			0x00	///*全失压*///
#define		C_ACPowerFailEventNo				0x01	///*辅助电源失电*///
#define		C_PowerfailEventNo					0x02	///*掉电*///
#define		C_OpenMeterCoverEventNo				0x03	///*开表盖*///
#define		C_OpenTerminalCoverEventNo			0x04	///*开端钮盖*///
#define		C_MagneticCheckEventNo				0x05	///*恒定磁场干扰*///
#define		C_PowerAbnormalEventNo				0x06	///*电源异常*///
#define		C_OverForwardActiveEventNo			0x07	///*正向有功需量超限*///
#define		C_OverReverseActiveEventNo			0x08	///*反向有功需量超限*///
#define		C_1OverIdleDemandEventNo			0x09	///*1象限无功需量超限*///
#define		C_2OverIdleDemandEventNo			0x0A	///*2象限无功需量超限*///
#define		C_3OverIdleDemandEventNo			0x0B	///*3象限无功需量超限*///
#define		C_4OverIdleDemandEventNo			0x0C	///*4象限无功需量超限*///
#define		C_AlossvoltageEventNo				0x0D	///*A相失压*///
#define		C_BlossvoltageEventNo				0x0E	///*B相失压*///
#define		C_ClossvoltageEventNo				0x0F	///*C相失压*///
#define		C_ALessvoltageEventNo				0x10	///*A相欠压*///
#define		C_BLessvoltageEventNo				0x11	///*B相欠压*///
#define		C_CLessvoltageEventNo				0x12	///*C相欠压*///
#define		C_AOvervoltageEventNo				0x13	///*A相过压*///
#define		C_BOvervoltageEventNo				0x14	///*B相过压*///
#define		C_COvervoltageEventNo				0x15	///*C相过压*///
#define		C_ALossphaseEventNo					0x16	///*A相断相*///
#define		C_BLossphaseEventNo					0x17	///*B相断相*///
#define		C_CLossphaseEventNo					0x18	///*C相断相*///
#define		C_ReversephaseVoltageEventNo		0x19	///*电压逆相序*///
#define		C_ReversephaseCurrentEventNo		0x1A	///*电流逆相序*///
#define		C_UnbanlanceVoltageEventNo			0x1B	///*电压不平衡*///
#define		C_UnbanlanceCurrentEventNo			0x1C	///*电流不平衡*///
#define		C_ALosscurrentEventNo				0x1D	///*A相失流*///
#define		C_BLosscurrentEventNo				0x1E	///*B相失流*///
#define		C_CLosscurrentEventNo				0x1F	///*C相失流*///
#define		C_AOvercurrentEventNo				0x20	///*A相过流*///
#define		C_BOvercurrentEventNo				0x21	///*B相过流*///
#define		C_COvercurrentEventNo				0x22	///*C相过流*///
#define		C_AFailcurrentEventNo				0x23	///*A相断流*///
#define		C_BFailcurrentEventNo				0x24	///*B相断流*///
#define		C_CFailcurrentEventNo				0x25	///*C相断流*///
#define		C_TReversecurrentEventNo			0x26	///*总功率反向*///
#define		C_AReversecurrentEventNo			0x27	///*A相功率反向*///
#define		C_BReversecurrentEventNo			0x28	///*B相功率反向*///
#define		C_CReversecurrentEventNo			0x29	///*C相功率反向*///
#define		C_AOverloadEventNo					0x2A	///*A相过载*///
#define		C_BOverloadEventNo					0x2B	///*B相过载*///
#define		C_COverloadEventNo					0x2C	///*C相过载*///
#define		C_OverpowerfactEventNo				0x2D	///*总功率因数超下限*///
#define		C_AOverpowerfactEventNo				0x2E	///*A相功率因数超下限*///
#define		C_BOverpowerfactEventNo				0x2F	///*B相功率因数超下限*///
#define		C_COverpowerfactEventNo				0x30	///*C相功率因数超下限*///
#define		C_SUnbanlanceCurrentEventNo			0x31	///*电流严重不平衡*///

///********698事件上报新增macro for EventRecord********///
#define		C_MeterFaEventNo				0x32	///*计量芯片故障*///
#define		C_ClockFaEventNo				0x33	///*时钟故障*///
#define     C_NeutralCurrentAbnormalEventNo 0x34	///*零线电流异常事件号*///

///*--------无开始结束状态的事件,负荷开关误动作除外--------------------------------------*///
#define		C_ProgramEventNo				0x35	///*编程*///
#define		C_TolClearEventNo				0x36	///*电表清零*///
#define		C_DemandClearEventNo			0x37	///*需量清零*///
#define		C_EventClearEventNo				0x38	///*事件清零*///
#define		C_AdjTimeEventNo				0x39	///*校时*///
#define		C_ProgPTEventNo					0x3A	///*时段表编程*///
#define		C_ProgPZEventNo					0x3B	///*时区表编程*///
#define		C_ProgWReEventNo				0x3C	///*周休日编程*///
#define		C_ProgSettDEventNo				0x3D	///*结算日编程*///
#define		C_RelayOpenEventNo				0x3E	///*跳闸*///
#define		C_RelayCloseEventNo				0x3F	///*合闸*///
#define		C_ProgHolEventNo				0x40	///*节假日编程*///
#define		C_ProgAcCEventNo				0x41	///*有功组合方式编程*///
#define		C_ProgReCEventNo				0x42	///*无功组合方式编程*///
#define		C_ProgTParaEventNo				0x43	///*费率参数表编程*///
#define		C_ProgLadEventNo				0x44	///*阶梯表编程*///
#define		C_Key_UpdateEventNo				0x45	///*密钥更新*///
#define		C_AbnorCEventNo					0x46	///*异常插卡*///
#define		C_BuyCurrEventNo				0x47	///*购电*///
#define		C_ReturnMoneyEventNo			0x48	///*退费*///
#define		C_RelayFaEndEnEventNo			0x49	///*负荷开关误动作*///
#define     C_ESAMErroEventNo               0x4A    ///*ESAM错*///
#define     C_RTCBatLowVolEventNo           0x4B    ///*时钟电池电压低*///
#define     C_MemoryCorrEventNo             0x4C    ///*存储器坏*///
#define     C_PowerBatLowVolEventNo         0x4D    ///*停电超标电池电压低*///
#define     C_OverdraftEventNo              0x4E    ///*透支*///
#define     C_CardErrorEventNo              0x4F    ///*内卡初始化错误*///
#define     C_ProgrammErrorEventNo          0x50    ///*内部程序错误*///
#define     C_SoftIJProgEventNo				0x51	///*软IJ编程*///
#define     C_LawlessCardEventNo			0x52	///*非法插卡*///
#define     C_BroadcastTimeEventNo			0x53	///*广播校时事件号*///
#define     C_BroadTimeAbnormalEventNo		0x54	///*广播校时异常事件号*///
#if 0
#define     C_ExternalRelayOpenEventNo		0x55	///*外置继电器反馈信号断*///
#define     C_ExternalRelayCloseEventNo		0x56	///*外置继电器反馈信号通*///
#endif
///********macro LoadProfile********///
#define C_FirstFrame			0x00		///*负荷连续抄读第一帧*///
#define C_OtherFrame			0xAA		///*负荷连续抄读非第一帧*///
#define C_Msg_LoadReadEarlyData        0xFF   ///*用于14规范负荷记录模块，读最早记录数据标志*///
///********macro Security********///
#define	C_Security_Null							0xff00+C_NULL
#define	C_Security_OverTime						0xff68						///*Esam/Card操作超时*///
#define C_Security_Err							0xff00+C_Error				///*Esam/Card操作异常*///
#define C_Security_MaxLenErr					0xff00+C_MaxResponseLen_ERR	///*Esam/Card操作缓冲区最大长度错误*///
#define C_Security_ProcessOk					0x6100		///*正常处理：61XX*///
#define C_Security_CommandOk					0x9000		///*命令执行成功*///
#define C_Security_CmdNotExist					0x6d00		///*INS不支持*///
#define C_Security_CLACmdTypeFault				0x6e00		///*CLA不支持*///
#define C_Security_TimeOut						0x6907		///*timer超时*///
#define C_Security_InvalidFile					0x6283		///*选择的文件无效*///
#define C_Security_AuthenFailed					0x6300		///*认证失败*///
#define C_Security_VerifyFailed					0x63c0		///*验证失败：63cX*///
#define C_Security_ExecutingError 				0x6400		///*执行出错*///
#define C_Security_E2Damage						0x6581		///*E2损坏*///
#define C_Security_LcLengthError				0x6700		///*Lc长度错误*///
#define C_Security_CLAError						0x6900		///*CLA不符合文件属性要求*///
#define C_Security_CmdNotReceiving				0x6901		///*命令不接收*///
#define C_Security_CmdNotCompatible				0x6981		///*命令与文件结构不相容*///
#define C_Security_NotMeetSafety				0x6982		///*不满足安全状态*///
#define C_Security_AuthMethodLocking			0x6983		///*认证方法锁定*///
#define C_Security_ReferenceDataInvalid			0x6984		///*引用数据无效*///
#define C_Security_ConditionNotSatisfied		0x6985		///*使用条件不满足*///
#define C_Security_CurrentFileNotSelected		0x6986		///*没有选择当前文件*///
#define C_Security_SafetyDataIncorrect			0x6988		///*安全报文数据项不正确*///
#define C_Security_MacErr						0x6989		///*MAC校验错*///
#define C_Security_DomainParaIncorrect			0x6a80		///*数据域参数不正确*///
#define C_Security_FunctionNotSupported			0x6a81		///*功能不支持*///
#define C_Security_FileNotFound					0x6a82		///*未找到文件*///
#define C_Security_RecordNotFound				0x6a83		///*未找到记录*///
#define C_Security_RecordSpaceFull				0x6a84		///*记录空间已满*///
#define C_Security_LcAndTLVNotMatch				0x6a85		///*Lc与TLV结构不匹配*///
#define C_Security_ParaP1AndP2NotCorrect		0x6a86		///*参数P1/P2不正确*///
#define C_Security_ReferenceDataNotFound		0x6a88		///*未找到引用数据*///
#define C_Security_ParameterError				0x6b00		///*参数错误*///
#define C_Security_LeLengthError				0x6c00		///*Le长度错误*///
#define C_Security_DataInvalid					0x6f00		///*数据无效*///
#define C_Security_MACInvalid					0x9302		///*MAC无效*///
#define C_Security_AppLocked					0x9303		///*应用被永久锁定*///
#define C_Security_AmountLess					0x9401		///*金额不足*///
///********macro for timer********///
#define C_StartTimer							0x68		///*启动计时*///
#define C_GetTimer								0x97		///*获取计时*///
///********macro for public.c********///
#define CL_Internal_Version				8					/* 内部型号长度8字节 */
///********macro ********///

typedef struct
{
         ulong32	V_ulOAD;
         //ulong32	V_ul645DI;
         uchar8		V_uc645Length;
		 uchar8		V_uc698Type;
		 uchar8		V_uc698NextNum;
		 uchar8		V_uc698NextType;
		 uchar8     V_uc698RateNumMethod;  /*2020增加，是否需要费率数判断的方法：需要：C_NeedRateNum_FF、C_NeedRateNum；不需要：C_NoRateNum*/
}Struct_FrozenConvert_Type;
#define C_NeedRateNum_FF         0x00	/*需要数据块判断费率数+1：如：组合有功电能数据块，正向有功电能数据块*/
#define C_NeedRateNum            0x01	/*需要判断费率数：如：组合有功总电能，*/
#define C_NeedRateNumPrice_FF    0x02	/*需要判断数据块费率数：如：费率电价数据块*/
#define C_NeedRateNumPrice       0x03	/*需要判断费率数：如：费率电价*/
#define C_NoRateNum              0x04	/*不需要判断费率数*/

#define C_RateNumError           0x86	/*费率数超标志*/
#define C_RateNumOK              0x68	/*费率数未超标志*/

#define C_ReadRecord_Hap         0x01	/*读记录型，发生*/
#define C_ReadRecord_End         0x02	/*读记录型，结束*/

#define CLEventDegree			 4	    /*事件序号长度*/
#define CLEventHappenTime		 CLDate_Time	    /*事件发生时间长度*/
#define CLEventEndTime			 CLDate_Time	    /*事件结束时间长度*/
#define CLEventSource			 1	    /*事件发生源长度*/
#define CLEventReport			 1	    /*事件上报状态长度*/
///***************数据类型定义**************///
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
#define		C_Ladder_Table				252	    /*阶梯表类型*/

#define		C_TypeLen				    1       /*类型长度，1字节*/

#define		C_TZone					    0x68
#define		C_SettleDay					0x86


#define		C_645					    0x68
#define		C_698						0x86

/********************新增返回真、假定义**********************/
#define		C_True						0
#define		C_Flase						1

//********************************************************************************************************************
///*类返回错误类型宏定义*///
#define     C_OK_DAR						0 	///* 成功 *///
#define     C_HardWareInvalid_DAR			1	///* 硬件失效*///
#define     C_TempInvalid_DAR				2 	///* 暂时失效 *///
#define     C_RWForbid_DAR				3 	///* 拒绝读写 *///
#define     C_ObjectUndefine_DAR			4 	///* 对象未定义 *///
#define     C_ObjectTypeErr_DAR			5	 ///* 对象接口类不符合*///
#define     C_ObjectNotExist_DAR			6 	///* 对象不存在 *///
#define     C_TypeErr_DAR					7 	///* 类型不匹配*///
#define     C_OverStep_DAR				8 	///* 越界*///
#define     C_DataBlockDisable_DAR		9 	///* 数据块不可用 *///
#define     C_FrameTransmitrEnd_DAR		10	///* 分帧传输已取消 *///
#define     C_FrameTransmitrInvalid_DAR	11	///* 不处于分帧传输状态 *///
#define     C_WriteBlockEnd_DAR			12	///* 块写取消 *///
#define     C_WriteBlockInvalid_DAR		13	///* 不存在块写状态 *///
#define     C_BlockNumInvalid_DAR			14	///* 数据块序号无效 *///
#define     C_Unauthorized_DAR			15	///* 密码错或未授权 *///
#define     C_Baud_NotModified_DAR		16	///* 通信速率不能修改 *///
#define     C_SeasonNum_OV_DAR			17	///* 年时区数超 *///
#define     C_PeriodNum_OV_DAR			18	///* 日时段数超*///
#define     C_RateNum_OV_DAR			19	///* 费率数超 *///
#define     C_SCMismatch_DAR				20	///* 安全认证不匹配*///
#define     C_ReRecharge_DAR				21	///* 重复充值 *///
#define     C_ESAMErr_DAR				22	///* ESAM验证失败 *///
#define     C_SCErr_DAR					23	///* 安全认证失败 *///
#define     C_CNMismatch_DAR				24	///* 客户编号不匹配 *///
#define     C_RechargeNumErr_DAR			25	///* 充值次数错 *///
#define     C_RechargeHoarding_DAR		26	///* 购电超囤积*///
#define     C_FWAddressErr_DAR			27	///* 地址异常 *///
#define     C_SymmetryDecodeErr_DAR		28	///* 对称解密错误 *///
#define     C_DissymmetryDecodeErr_DAR	29	///* 非对称解密错误 *///
#define     C_SignatureErr_DAR				30	///* 签名错误 *///
#define     C_MeterSafeguard_DAR			31	///* 电能表挂起 *///
#define     C_TimeLabelInvalid_DAR		32	///* 时间标签无效 *///
#define     C_RequestTimeOut_DAR			33	///* 请求超时 *///
#define     C_OtherErr_DAR				255	///* 其他 *///
//********************************************************************************************************************
//***********************************事件记录、冻结二级/三级表格******************************************************
//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
/////////////////////////////////////////////*OIB定义*//////////////////////////////////////////
#define CLoss_Vol_OIB      			0x00	///*698-失压*///
#define CLow_Vol_OIB				0x01	///*698-欠压*///
#define COver_Vol_OIB             	0x02    ///*698-过压*///
#define CBreak_Vol_OIB             	0x03    ///*698-断相*///
#define CLoss_Curr_OIB           	0x04    ///*698-失流*///
#define COver_Curr_OIB           	0x05    ///*698-过流*///
#define CBreak_Curr_OIB           	0x06    ///*698-断流*///
#define CTrend_Rev_OIB            	0x07    ///*698-潮流反向*///
#define COver_Lo_OIB             	0x08    ///*698-过载*///
#define CPos_De_Over_OIB  			0x09    ///*698-电能表正向有功需量超限事件*///
#define CRe_De_Over_OIB 			0x0A    ///*698-电能表反向有功需量超限事件*///
#define CRe_ReDe_Over_OIB        	0x0B	///*698-电能表无功需量超限事件*///
#define CPFactorT_Over_OIB          0x3B	///*698-电能表功率因数超下限事件*///
#define CAll_Loss_Vol_OIB           0x0D    ///*698-电能表全失压事件*///
#define CAux_Pow_Down_OIB          	0x0E    ///*698-电能表辅助电源失电事件*///
#define CRevPS_Vol_OIB              0x0F    ///*698-电能表电压逆相序事件*///
#define CRevPS_Curr_OIB      		0x10    ///*698-电能表电流逆相序事件*///
#define CPow_Down_OIB               0x11    ///*698-电能表掉电事件*///
#define CProgram_OIB               	0x12    ///*698-电能表编程事件*///
#define CTol_Clear_OIB            	0x13    ///*698-电能表清零事件*///
#define CDe_Clear_OIB             	0x14    ///*698-电能表需量清零事件*///
#define CEven_Clear_OIB          	0x15    ///*698-电能表事件清零事件*///
#define CAdjTime_OIB            	0x16    ///*698-电能表校时事件*///
#define CProgPT_OIB             	0x17    ///*698-电能表时段表编程事件*///
#define CProgTZ_OIB              	0x18    ///*698-电能表时区表编程事件*///
#define CProgWRe_OIB                0x19    ///*698-电能表周休日编程事件*///
#define CProgSettD_OIB            	0x1A    ///*698-电能表结算日编程事件*///
#define COpenW_OIB               	0x1B    ///*698-电能表开盖事件*///
#define COpenCW_OIB               	0x1C    ///*698-电能表开端钮盖事件*///
#define CNoBal_Vol_OIB              0x1D    ///*698-电能表电压不平衡事件*///
#define CNoBal_Curr_OIB           	0x1E    ///*698-电能表电流不平衡事件*///
#define CRelayOpen_OIB             	0x1F    ///*698-电能表跳闸事件*///
#define CRelayClose_OIB          	0x20    ///*698-电能表合闸事件*///
#define CProgHol_OIB              	0x21    ///*698-电能表节假日编程事件*///
#define CProgAcC_OIB              	0x22    ///*698-电能表有功组合方式编程事件*///
#define CProgReC_OIB                0x23    ///*698-电能表无功组合方式编程事件*///
#define CProgTPara_OIB            	0x24    ///*698-电能表费率参数表编程事件*///
#define	CProgLad_OIB                0x25    ///*698-电能表阶梯表编程事件*///
#define CKey_Update_OIB           	0x26    ///*698-电能表密钥更新事件*///
#define CAbnorC_OIB					0x27    ///*698-电能表异常插卡事件*///
#define CBuyCurr_OIB                0x28	///*698-电能表购电事件*///
#define CReturn_M_OIB              	0x29	///*698-电能表退费事件*///
#define CConM_OIB              		0x2A	///*698-电能表恒定磁场干扰事件*///
#define CRelayFa_OIB              	0x2B	///*698-电能表负荷开关误动作事件*///
#define CPowerFa_OIB              	0x2C	///*698-电能表电源异常事件*///
#define CSevNoBal_Curr_OIB          0x2D	///*698-电能表电流严重不平衡事件*///
#define	CClock_FaultState_OIB		0x2E	///*698-电能表时钟故障事件*///
#define	CMeteringChipFault_OIB		0x2F	///*698-电能表计量芯片故障事件*///
#define CBroadcastTime_OIB          0x3C    ///*698-电能表广播校时事件*///
#define CNeutralCurrentAbnormal_OIB 0x40    ///*698-电能表零线电流异常事件*///
#define CBroadTimeAbnormal_OIB      0x51    ///*698-电能表广播校时事件*///

#define	C_WriteEventRecord 	0x68	///*写事件记录*///
#define	C_ReadDate 			0x86	///*读数据写数据层*///
#define	C_NeedWriteEventRecord	0xAA	///*不写总的编程记录?///
#define	C_NeedWrite645EventRecord	0xBB	///*写645总的编程记录//

#define	C_Read							0x01		///*读取*///
#define	C_SetUp							0x02		///*设置*///
#define	C_Operation						0x04		///*操作*///

///********698主动上报事件动作定义********///
#define	C_Happen_EventReport	0x68	///*事件发生*///
#define	C_End_EventReport	0x66	///*事件恢复*///
#define C_EventTableDefaultVal	 0	///*事件主动上报默认值                *///

#define	C_ReportChannel1  	C_RS485_1   ///*通道1*///
#define	C_ReportChannel2  	C_RS485_2   ///*通道2*///
#define	C_ReportChannel3  	C_Module    ///*通道3*///
//#define	C_ReportChannel4  	0x88        ///*通道4*///
#define	C_ReportChannel4  	C_IR        ///*通道4,红外不支持*///
#define	C_ReportChannelAll	0xAA        ///*4个通道都开启*///
#define	C_ReportChannelNum  0x04///*4个通道*///

#define C_ReadRecord		0x68///*读记录数据*///
#define	C_ReadOther			0x86///*读其他数据*///


#define C_ReportState		0x68///*事件已上报*///
#define C_ConfirmState		0x86///*事件已上报已确认*///

#define C_NewReport  	0x68///*新增事件列表*///
#define C_DeletReport	0x86///*删除事件列表*///
#define C_OADError      0xEEEEEEEE///*事件OAD错误*///
#define C_BitError      0xEE       ///*电表运行状态字8 OAD错误*///

typedef struct
{
	uchar8 EventNo;				/*事件号码*/
	uchar8 StatusBit;			/*是否需要判断上报标志，0不需要，1需要*/
    ushort16 OIBANature;		/*0IB和属性*/
	//ulong32 EventModeDI;		/*事件对应模式字DI*/
	//ulong32 EventReportDI;	/*事件对应上报表格DI*/
	//uchar8 EventIB;			/*IB*/
}Str_698EventReport_Type;		/*698主动上报事件对应表格结构体*/


typedef  struct
{
    ulong32 *pV_ulROAD;       /*首地址对应读取对象OAD，后续数据当读取为记录则为关联OAD列表*/
    uchar8 *pV_ucRST;         /* pV_ucRST[0]读取方式：1给定时间读取，2给定区间读取，9读取上N次，pV_ucRST[1]~ pV_ucRST[N]为对应方法的参数，若为方法1和2，后续带4字节OAD+时间，方法9为1字节上n次
                            当读取为属性时该参数无效新增方法0xFF,用于读取645负荷记录，指定时间7字节pV_ucRST[1]~ pV_ucRST[8]，指定时间后读取数据条数pV_ucRST[9]*/
    ushort16 V_usROAD_Num;    /*0表示无关联OAD，即整条读取记录*/
    uchar8 V_ucReadMode;      /*1：模块内部使用，2：通信读取，3：显示读取*/
    uchar8 V_ucChannelNo;     /*通道号，非通信读取时为0xFF*/
}Str_Read_T;/*记录型接口参数结构体*/

#define C_OtherMode			1		/*模块内部使用*/
#define C_ComMode			2		/*通信读取*/
#define C_DisMode			3		/*显示读取*/

#define C_RST_Method_O			0		/*读取方法偏移*/
#define C_RST_OADOrNum_O		1		/*读取方法对象属性描述OAD首地址*/
#define C_RST_Timer1_O			5		/*读取方法1/2 第一个时间偏移首地址*/
#define C_RST_Timer2_O			12		/*读取方法2 第一个时间偏移首地址*/
#define C_RST_TIInter_O			19		/*读取方法2 TI时间间隔偏移首地址*/

typedef  struct
{
    ushort16 *pV_usEncode;  /*读取数据的内部编码缓存，第一处存放编码个数*/
    uchar8 V_ucFrameNum;   /*读到的总条数*/
    uchar8 V_ucNxtFrame;   /*后续帧标志，1表示有后续帧，0表示无后续*/
    uchar8 V_ucLastFlag;   /*低4位表示是否包含最近一条标志，1表示包括最近一条，0表示不包括*/
							/*高4位表示最近一条是否为有发生无回复，1表示有发生无恢复，0表示有发生有恢复*/
}Str_SuppInfo;/*记录型接口辅助信息结构体*/



typedef struct
{
	ulong32	DI;		        ///*645数据标识*///
	ulong32	OAD;			///*698数据标识*///
	uchar8	DILenth;		///*645数据长度*///
}Str_EventTable_645ChangeTo698;


#define C_645Mode           0x00
#define C_698Mode           0x01
#define C_698AheadTimeMode  0x68	/*负荷曲线读取时查找最早的有效时间点*/
#define C_698EarLoadMode    0x86	/*负荷曲线补数据时查找前一个有效时间点*/


#define C_Program	0x68
#define C_NotProgram	0x86
#define C_PluseWide		0x80

//****************698兼容645增加***************//
#define C_UsedBy698    0x00
#define C_UsedBy645    0x55

#define C_MonTwoOffset          1    //2月在数组中的偏移
#define C_NovOffset            11    //12月在数组中的偏移

#define C_MonMaxLim     0x1A4   //查询月数最大限制35年*12
#define C_YearMaxLim    0x23   //查询年数最大限制35年

#define C_CycleTimes  1500  //方法2抄读冻结数据，查找1500条限制

#define C_ALL00_Flag       0x55 ///读出发生时间全0
#define C_NoALL00_Flag     0xAA///读出发生时间非全0

///*2020标准主动上报2005*///
#define C_RS485_1MaxLen 512  ///*通道1最大接收发送长度*///
#define C_RS485_2MaxLen 512  ///*通道2最大接收发送长度*///
#define C_ModuleMaxLen 255  ///*通道3最大接收发送长度*///
#define C_IRMaxLen 200      ///*通道4最大接收发送长度*///

#define C_ActiveReportFlag              0x08                                            ///*主动上报*///
#define C_ActiveReportEndFlag           0x04                                            ///*主动上报刚结束*///
#define C_NoActiveReportFlag            0x02                                            ///*其他模式*///
#define C_ReadReportFlag                0x01                                            ///*读上报模式*///
#define C_NewReportFlag                 0x10                                            ///*新发生了上报之后要清掉10s那个时间立即上报*///
#define C_OtherActiveReportInit         0x20                                            ///*其他主动上报*///
#define C_EventTypeActiveReportInit     0x40                                            ///*掉电主动上报*///
#define C_NewReportFlag_EventType       (C_NewReportFlag|C_EventTypeActiveReportInit)     ///*新发生事件类型上报*///
#define C_NewReportFlag_Other           (C_NewReportFlag|C_OtherActiveReportInit)         ///*新发生其他类型上报*///
#define C_Check                         0x03                   ///*check CRC*///
#define C_CountCRC                      0x05                   ///*Count CRC*///
#define C_ReportMaxNum_Remin            0x06               ///*2.5s是否还未发送成功*///


#define C_RNLen                     12                      ///*8字节随机数+4字节计数器*///
#define C_MACLen                    4                      ///*MAC长度*///

#define C_ReportFlag                    0x6868        ///*目前处于事件主动上报数据发送状态*///
#define C_PowerDownReportFlag           0x8686          ///*目前处于掉电主动上报数据发送状态*///
#define C_ReportNULL                    0x0000        ///*没有处于主动上报状态*///

#define C_CommuniSafeWorld1         0x01                    ///*正常接收中断*///
#define C_CommuniSafeWorld2         0x02                    ///*正常解析完尚未发送*///
#define C_CommuniSafeWorld3         0x04                    ///*正常开始发送数据*///
#define C_CommuniSafeWorld4         0x08                    ///*正常通信，中断发送结束*///
#define C_CommunicationEnd          (C_CommuniSafeWorld1|C_CommuniSafeWorld2|C_CommuniSafeWorld3|C_CommuniSafeWorld4)///*通信刚结束*///
#define C_NoCommunication           0x00                    ///*没有处于通信状态*///

#define C_EventOIA              0x30            ///*事件OIA*///
#define C_Event07ReportType     0x0B            ///*07类事件上报类型11属性*///
#define C_Event24ReportType     0x0F            ///*24类事件上报类型15属性*///

#define C_ReportMode                            0x68            ///*获取上报模式字标志*///
#define C_ReportType                            0x86            ///*获取上报类型标志*///

#define C_ActiveReportType              0x00                    ///*上报类型，主动上报*////
#define C_FollowReportType              0x01                    ///*上报类型，跟随上报*///

#define C_ACTION_Request		0x07		///*操作请求*///

///*******************************数据验证信息******************************************///
///*解密加密模式宏定义*///
#define SID_MAC_698		0
#define RN_698  		1
#define RN_MAC_698  	2
#define SID_698  		3
#define	NO_RN_698		4
#define MAC_698         5

#define C_OneReportLen      3                                   ///*1个主动上报字节数*///

#define C_NewReportMaxNum	70						///*主动上报事件个数*个数不能小于1个*///
//#define C_NewReportDataLen	C_NewReportMaxNum*3		///*主动上报总长度（EventNo+Time）*///
#define C_NewReportDataLen	C_NewReportMaxNum*C_OneReportLen    ///*主动上报总长度（EventNo+Time）*///
#define C_NewReportNumByte	C_NewReportDataLen		///*主动上报个数*///
#define C_NewReportLen 		(C_NewReportDataLen+1)	///*主动上报表格大小*///
#define C_NewReportCRCLen 	(C_NewReportLen+2)		///*主动上报表格大小（主动上报总长度+个数+CRC）*///

#define CLNewReportList		            (C_NewReportMaxNum*2+1)		        ///*新增上报列表*///
#define CLDrive_Report_State_New		(CLDrive_Report_State+CLDrive_Report_State*8)	///*跟随上报状态字*///
#define C_NewReportSaveNumByte          (CLNewReportList-1)       ///*写数据层时的上报事件个数位置*///

#define C_SEvent_TimeAttri      0x0E            ///*分相事件时间状态属性*///
#define C_Event_TimeAttri       0x0A            ///*事件时间状态属性*///

#define  C_Money_Init	1
#define  C_Money_Purchase	2
#define C_MonTwoOffset          1    //2月在数组中的偏移
#define C_NovOffset            11    //12月在数组中的偏移
#define C_MonMaxLim     0x1A4   //查询月数最大限制35年*12
#define C_YearMaxLim    0x23   //查询年数最大限制35年
#define C_CycleTimes  1500  //方法2抄读冻结数据，查找1500条限制
#define C_FreezCycFlagErr     0xFF //抄读冻结周期失败标志

//CDate_Time数据的偏移
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

/*21规范新增，如果上电不到1hour不进行掉电上报要求*/
#define C_ActiveReportMaxNum    0x03    /*主动上报次数*//*2020标准主动上报2005*/

#define	C_Happen_EventState     0x68    /*事件状态，有发生无恢复*/
#define	C_End_EventState        0x00    /*事件状态，非有发生无恢复*/
#define	C_Close_EventState      0x66    /*事件状态，关闭*/
#define C_Active_NxtFrame 		0x01	/*有后续帧标志*/
#define C_Active_LastEvent 		0x01	/*包含最后一条*/
#define C_Active_Happening 		0x11	/*包含有发生无恢复*/
#define C_InActive				0x00	/*无效（无后续帧，无最后一条）*/

#define C_Interval_1hour        3600    /*基于基本节拍的60min=1hour间隔*/


#define	C_ReportNull	    0x00	    /*不上报*/
#define	C_ReportHP	        0x01	    /*发生上报*/
#define	C_ReportEed	        0x02	    /*结束上报*/
#define	C_ReportAll	        0x03	    /*发生结束上报*/

#define C_MeterReportOpen   0x68        /*电能表开启了电能表主动上报/开启了模块上报通道/并且是模块表*/
#define C_MeterReportClose  0x86        /*电能表没有开电能表主动上报或者没有开模块上报通道或者不是模块表*/

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
extern  void InF_RAMDataRecoverFromE2(void);///*由通信模块触发调用，用于E2数据对RAM数据进行恢复*///
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
extern uchar8 GV_KeyHState[CLKey_State_698];                  ///*电能表历史密钥状态字*///

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
//extern	void  PF_StepTypeProcess(uchar8 *OldDate,uchar8 *NewDate,uchar8 *SettlementTime);   /*zlj删除*/
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
#if _DEBUGFY /*不再存RAM，改为使用宏定义,拼接时去掉*/
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

#define	C_SaveFreezeTimeNum	80		//保存最近20条冻结记录时间
#define	C_FreezeTimeLen	7			//冻结时间长度
#define	C_SaveFreezeTimeBufLen	491		//保存最近20条冻结记录时间
#define	C_645FreezeTimeBufLen	610		//645负荷记录最多读出来99条
#define C_FreezeMAXRelatedOAD		96
#define C_MAXRelatedOAD  (C_FreezeMAXRelatedOAD+5)
#define C_645FreezeMAXRelatedOAD    99
#define C_698To645EnergyBlockLength    (4*4)
typedef  struct
{
	  //uchar8	DI0;             			///*DI0*///
	  uchar8	DataType;			///*数据类型*///
	  uchar8	DataLen_698;		///*数据长度*///
	  uchar8	DataLen_645;		///*数据长度*///

}Str_DI0_DataType_PaTable;				           ///*DI0/数据类型的映射*///

///*抄读数据标识码对应的各项数据*///
typedef struct
{
    ulong32 V_ulDataId698;	///*698数据标识*///
    uchar8 V_Num;           ///*包含698数据个数*///
    uchar8 V_SuppleData;    ///*补数据的类型，电能补上一个点的数据，瞬时量补0xFF*///
	ulong32 V_ulDataId645;	///*645数据标识*///
//	ulong32 V_ulTypeId;		///*对应原负荷类型标识码*///
//	uchar8 V_ucOffset;		///*数据标识在对应负荷种类的偏移 *///
	uchar8 V_ucDataLen;		///*标识码数据对应的长度*///
}Str_698To645LoadReadStatus;
/*负荷记录645DI对应698OAD*/
typedef struct
{
	ulong32 V_ulDataOAD698;		/*698数据标识*/
	ulong32 V_ulDataDI645;		/*645数据标识*/
	uchar8 V_ucDataLen;			/*标识码数据对应的长度*/
	uchar8 V_ucDataOffset;		/*数据标识在对应负荷种类的偏移*/
}Str_LoadRecord645DITo698OAD;
typedef struct
{
    ulong32 V_ulDataId698;	///*698数据标识*///
    uchar8 V_Num;           ///*包含698数据个数*///
//    uchar8 V_SuppleData;    ///*补数据的类型，电能补上一个点的数据，瞬时量补0xFF*///
	ulong32 V_ulDataId645;	///*645数据标识*///
//	ulong32 V_ulTypeId;		///*对应原负荷类型标识码*///
//	uchar8 V_ucOffset;		///*数据标识在对应负荷种类的偏移 *///
	uchar8 V_ucDataLen;		///*标识码数据对应的长度*///
}Str_698To645DFreezReadStatus;
//extern uchar8 GV_SaveFreezeTimeBuf[C_SaveFreezeTimeBufLen];
extern void InF_WriteFreezeTimeToBufer(uchar8 *pV_FreezeTimeBuf,uchar8 *pV_CurrentTime,uchar8 V_Mode);

#define C_MaxRCSDNum           25          ///*最大记录列选择描述符个数*///
typedef struct
{
	ulong32  	OAD;					///*读OI*///
	ushort16	CarryNum;				///*如果是数组，这里记录数组个数*//
	uchar8	DataType;				///*数据类型*///
	uchar8	CurrentFrameNum;	///*有后续帧时，保存上一帧的偏移(节假日)*//

}OAD_T;

typedef struct
{
	OAD_T  	RdOI;					///*读OI*///
	//OAD_T  	Rd_RecordRelatedOI[25];	///*读记录关联OI,这里按照失压发生数据关联对象个数定*///
	ulong32  	Rd_RecordRelatedOI[C_MaxRCSDNum];	///*读记录关联OI,这里按照失压发生数据关联对象个数定*///
	uchar8	 	Rd_RecordRelatedOINum;	///*读记录关联OI数*///
	uchar8	 	Rd_RecordRelatedOIType;	///*读记录关联类型*///
	uchar8	 	Rd_RecordSelect[25];		///*读取记录时选择方法*///
	uchar8	 	Rd_Result;				///*读操作结果*///
}RdOI_Para_T;

#define	C_RSDSelector1			0x01		///*事件记录读取选择方法1*///
#define	C_RSDSelector2			0x02		///*事件记录读取选择方法2*///
#define	C_RSDSelector9			0x09		///*事件记录读取选择方法9*///

#define C_GETNormal_Request		0x01		///*读取一个对象属性*///
#define C_GETNormalList_Request	0x02		///*读取多个对象属性*///
#define C_GETRecord_Request		0x03		///*读取一个记录*///
#define C_GETRecordList_Request	0x04		///*读取多个记录*///
#define C_GETNext_Request		0x05		///*读后续*///

/*************************通信下发RST偏移定义********************************/
#define C_GetSelect_Method_O		0		/*读取方法偏移*/
#define C_GetSelect_OADOrNum_O		1		/*读取方法对象属性描述首地址*/
#define C_GetSelect_Data1_O			5		/*读取方法1/2 Data偏移首地址*/
#define C_GetSelect_Data2_O			13		/*读取方法2 Data2偏移首地址(目前方法2只支持用时间区间)*/
#define C_GetSelect_TI_O			21		/*读取方法2 Data3偏移首地址(TI)*/
#define C_GetSelect_TIUnit_O		22		/*读取方法2 TI单位偏移首地址*/
#define C_GetSelect_TIInter_O		23		/*读取方法2 TI时间间隔偏移首地址*/


extern uchar8 SF_GetAPDU_FreezeRead(RdOI_Para_T *V_OAD,uchar8 *P_DataBuf,ushort16 *P_DataOff,uchar8 NextFrameFlage);
extern ushort16	SF_DataExchangeTo645_BasicData(uchar8 *pV_698data,uchar8 *pV_645data,uchar8 V_ucLen698,uchar8 *V_ucLen645);


extern void PF_Buffer8ToUlong64_698(uchar8 *BytesBuffer, ulong64 *DoubleWordBuufer, uchar8 Len);
extern void PF_Ulong64ToBuffer8_698(uchar8 *BytesBuffer, ulong64 *DoubleWordBuufer, uchar8 Len);


///*****************复旦微RTC时钟调校
//从0x811800开始会保存如下信息
#define const_tx_flag  			(*((ushort16 *)(0x1ffffa20))) //调校标志(0x3cc3为编程调校)
#define const_rtc_adj_top 	(*((short16 *)(0x1ffffa36))) //顶点误差ppm,0.01ppm
//温度曲线相关参数
extern const uchar8 RTC_Trim_Ctrl;	//0x55-补偿步长0.119ppm，其它-补偿补偿0.238ppm(仅404模式下可开启0.119)
extern const uchar8 SleepPtatOffsetCfg;	//0x55-启用3V偏置(3V电源ptat偏置控制开关)，其他-关闭
extern const float const_xtl_top;		//计算温度曲线使用的顶点
extern const float const_KL;	//温度补偿系数
extern const float const_KH;
extern const float const_TmpsL;	//温度ADC斜率
extern const float const_TmpsH;
extern const uchar8 constF_Volt;		//电压补偿量(兼容新硬件电池增加二极管),3表示0.03v/10表示0.1v
extern const ushort16 const_adc_TrimB;
extern const ushort16 const_adc_TrimT;
extern const ushort16 const_KHKL_TrimRange;//晶体曲线修调功能分界范围，25度±7度内使用常温修调值krh，krl，范围外使用高低温修调值kh，kl
extern const float const_T_OffsetRun;	//芯片发热修正-运行用
extern const float const_T_OffsetSlp;	//芯片发热修正-休眠用
extern const uchar8 const_TopNoTrim;  //顶点±x度附近不补偿 0x55:不补偿， 0x00:正常补偿
extern const uchar8 const_TopNTRange;	//顶点附近关闭自动补偿温度adc范围，±x/5.0379=温度范围
extern const float const_T_CL;	//低温查表中心温度
extern const float const_T_CH;		//高温查表中心温度
extern const uchar8 const_C_Mode;		//0x55:启动高低温高精度查表功能，其他，仅开启常温高精度查表

extern const short16 const_TR_LSTART;	//低温记录启动温度（short16放大10倍）
extern const short16 const_TR_HSTART;	//高温记录启动温度（short16放大10倍）
///extern const uchar8 const_TR_GAP;//1;//	//记录间隔，单位分钟
///extern const uchar8 const_TR_Mode;		//0x55:启动温度记录功能，其他，关闭
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
#define	C_PowerFail_Judge_Time	0x01  ///*掉电延时判断时间默认1s*///
extern void Inf_GetReportData(uchar8 *pReportBufStart,ushort16 *pReportLen,uchar8 CommChannelNo,uchar8 ReportType);
extern uchar8  INF_ValtageType(void);
extern uchar8 Inf_Event_REPORTONumGet(void);
/*extern void InF_CardParam(void); */
extern ulong32 Inf_PowerDownTime(void);
extern void Inf_ClearPowerDownTime(void);
extern ulong32 Inf_Get_PowerOffShutAcReportTime(void);
extern void Inf_Clear_PowerOffShutAcReportTime(void);
extern uchar8 Inf_SatisfyPowerOnTime();

/*zlj新增*/
extern uchar8 PF_HextoBCDOneBytes(uchar8 V_ucData);
extern uchar8 PF_Is_Buf_AllFixedData(uchar8 *P_ucData, uchar8 V_ucFixedData,  ushort16 V_usDataLen);
extern uchar8 PF_DataTimeActive_698(uchar8 *TimeBuffer,uchar8 StartByte,uchar8 Len);
uchar8 InF_Get_MeterICModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *p_usDataEncode);

#define	C_ShieldSignBit 0x7f		/*屏蔽符号位*/
#define	C_GetSignBit 	0x80		/*获取符号位*/

#define C_Minus     C_GetSignBit    /*负数用之前取符号位的定义（0x80），兼容之前程序的做法*/
#define C_Plus      C_ShieldSignBit /*正数*/


#define C_Immediate_Type			0	    /*瞬时冻结*/
#define C_Minute_Type				0x10	/*分钟冻结*/
#define C_Hour_Type					2	    /*小时冻结*/
#define C_Day_Type					3	    /*日冻结*/
#define C_Settlement_Type			4	    /*结算日冻结*/
#define C_Month_Type				5	    /*月冻结*/
#define C_Year_Type					6	    /*年冻结*/
#define C_Change_TimeZone_Type		7	    /*时区表切换冻结*/
#define C_Change_TimePeriod_Type	8	    /*日时段表切换冻结*/
#define C_Change_Fate_Type			9	    /*费率电价切换冻结*/
#define C_Change_Ladder_Type		10	    /*阶梯切换冻结*/
#define C_Day_Type_Add				11	    /*日冻结补冻*/
#define	C_YSettle_Type			    12	    /*阶梯结算冻结*/
#define	C_Month_Type_Add			13	    /*月冻结补冻*/

#define C_FrzOAD    0x50000000  /*做记录获取数据接口函数入参中冻结的OAD自扩标识*/

extern void SF_GetFreeze_StartTime(uchar8 *pFreezeTime);
extern uchar8 Inf_GetRecordData(uchar8 *V_ucData, ushort16 *V_ucLength, ulong32 V_ulOADTab, uchar8 V_ucTypeFlag);
extern void PF_Data_Week_Time_BCDtoData_Time_s_HEX(uchar8 *V_ucBCDBuffer, uchar8 *V_ucHexBuffer);
extern void PF_Data_Time_s_HEXtoData_Week_Time_BCD(uchar8 *V_ucHexBuffer, uchar8 *V_ucBCDBuffer);

#endif
