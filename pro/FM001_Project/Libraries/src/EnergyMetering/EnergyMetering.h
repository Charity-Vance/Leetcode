/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     EnergyMetering.h
Version:       V1
Author:        
Date:          2014-3-12
Description:   电能处理文件
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:   20219016
   	   Author: fy
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
----------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
   	   Author:
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
******************************************************************************/

#ifndef	__EnergyMetering_H
#define	__EnergyMetering_H

/*---------------------------------------------------------------------------*/
/*宏定义*/
/*---------------------------------------------------------------------------*/
#define C_ActiveDirection						0x00					/*正向*/
#define C_ReactiveDirection						0x01					/*反向*/

#define C_MoneyChangeEquivalent	    			10000					/*分与数据层存储金额格式转换当量*/
#define C_EnergyChangeEquivalent				1000000					/*电能与数据层存储脉冲数格式转换当量*/
#define C_EnergyChangeEquivalent_Hundred		100						/*电能与数据层存储脉冲数格式转换当量,100倍*/

#define C_ValidStep								0x00					/*有效阶梯*/
#define C_InValidStep							0x01					/*无效阶梯，没有阶梯功能*/

#define C_MaxStepNum							6						/*最大阶梯个数*/
#define C_MaxStepEnergyLen						24						/*阶梯值参数个数*/
	   
#define CLCurr_Money							0x05					/*剩余金额\透支金额数据层长度*/
			
/*20规范，电能范围(6位小数)*/
#define C_ConEnergyToZero_Nature4				 0x7FFFFFFFFF			/*属性4最大值范围*/
#define C_ConEnergyToZero_Nature2				 0x7FFFFFFF			    /*属性2最大值范围*/


#define C_GetNextRatesEnergy					0x00000001				/*获取下一个费率电能标识码*/
#define C_GetNextPhaseEnergy					0x00010000				/*获取下一个分相电能标识码*/
#define C_GetNextQuadrantEnergy					0x00100000		    	/*获取下一个象限电能标识码*/

#define C_ActiveDeriction_T						0x08
#define C_ActiveDeriction_A						0x01
#define C_ActiveDeriction_B						0x02
#define C_ActiveDeriction_C						0x04
			
#define C_ReactiveDeriction_T					0x88
#define C_ReactiveDeriction_A					0x11
#define C_ReactiveDeriction_B					0x22
#define C_ReactiveDeriction_C					0x44
			
#define C_ReactiveEDeriction_T					( C_ReactiveDeriction_T & 0xF0 )
#define C_ReactiveEDeriction_A					( C_ReactiveDeriction_A & 0xF0 )
#define C_ReactiveEDeriction_B					( C_ReactiveDeriction_B & 0xF0 )
#define C_ReactiveEDeriction_C					( C_ReactiveDeriction_C & 0xF0 )

#define C_RenewDerict							0x68					/*直接更新状态标志*/
#define C_RenewRederict							0x86					/*有状态变化才更新标志*/
							
#define C_NoMessage								0x00					/*不发消息*/
#define C_Warning1Message						0x01					/*发报警1消息消息*/
#define C_ReleaseWarning1Message				0x02					/*发取消报警1消息消息*/
#define C_Warning2Message						0x03					/*发报警1消息消息*/
#define C_RelayOffMessage						0x04					/*发立即拉闸消息消息*/
#define C_Warning3Message           			0x05    				/*剩余金额跨过0报警,需要先发一个合闸允许再发一个与跳闸报警消息*/

#define	C_SubMoneyFlag							0x8A					/*有扣费标志*/
#define	C_NoSubMoneyFlag						0x00					/*无扣费标志*/
							
#define C_MoneyToPurchase						0x68					/*购电*/
#define C_NoMoneyToPurchase						0x00					/*没有购电*/
#define C_MoneyToPurchaseFlagLen				0x01					/*标志长度*/

#if(_DEBUG_FY) /*拼接后去掉*/
/*电能读取方法*/						
#define C_Nature2BCD							0x01					/*属性2BCD*/
#define C_Nature4BCD							0x02					/*属性4BCD*/
#define C_Nature2HEX							0x03					/*属性2HEX*/
#define C_Nature4HEX							0x04					/*属性4HEX*/
#define C_Nature6HEX							0x05					/*属性6HEX*/
#define C_ErrorMethod							0xFF					/*异常方法*/
#endif	

/*电能读取方法*/							
#define C_En_OADGetTpye_Money					0x01					/*金额类*/
#define C_En_OADGetTpye_Month					0x02					/*月度用电量*/
#define C_En_OADGetTpye_StepSettle				0x03					/*阶梯结算用电量*/
#define C_En_OADGetTpye_Com						0x04					/*组合电能*/
#define C_En_OADGetTpye_Other					0x05					/*其他电能*/
			
/*阶梯结算日偏移*/			
#define C_FirstStepSettle_MonthOffset			0x00					/*第一阶梯结算日中月的偏移*/
#define C_FirstStepSettle_DayOffset				0x01					/*第一阶梯结算日中日的偏移*/

/*电表运行状态字1中透支状态*/
#define C_SetOverDraft							0x40					/*透支状态置位，置1*/
#define C_ClrOverDraft							0xBF					/*透支状态清位，置0*/

/*---------------------------------------------------------------------------*/
/*函数声明*/
/*---------------------------------------------------------------------------*/
void SF_Judge_CurrentStep(ulong32 V_ulEnergy_F, ulong32 *pV_ulEnergyPrice, uchar8 *pV_ucStepPara, uchar8 V_ucCurStepType);
void SF_JudgeWarningStatus(ulong64 V_ullRemainMoney, ulong64 V_ullRemainMoney_New, ulong64 V_ullOverDraftMoney, ulong64 V_ullOverDraftMoney_New, uchar8 V_ucRenewFlay);
void SF_ReworkWarningPara(void);
void SF_UpdateCurrentPrice(void);
void SF_WriteCurrentPrice(void);
void SF_SetMoneyToPurchaseFlag(uchar8 V_ucPurchaseFlag);


uchar8 SF_Judge_CurrentStep_Type(uchar8 *pV_ucBuffer);
uchar8 SF_RateChargeback(ulong64 V_ullEnergy_F, ulong64 V_ullEnergy, uchar8 V_ucRateNo);
uchar8 SF_Get_RMoney_DMoney(ulong64 *pV_ullRMoney, ulong64 *pV_ullDMoney);
uchar8 SF_CheckMoneyToPurchaseFlag(void);
uchar8 SF_ReadTotalEnergy(ulong32 V_ulPulOAD, ulong64 *pV_ullTolEnergy, uchar8 V_ucCalNum, ulong32 V_ulOADRegular );
uchar8 SF_DealEnergyPoint(uchar8 V_ucNature, ulong64 *pV_ullEnergyPulse, ushort16 *pV_usLen);
uchar8 SF_ReadConEnergy_Pulse(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen);


ulong64	SF_Get_V_I_Ratio(void);
ulong64 SF_Get_RateEnergyForChargeback(uchar8 V_ucRateNo);


#endif
