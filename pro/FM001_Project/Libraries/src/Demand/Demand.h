/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Demand.h
Version:       V1
Author:        
Date:          2014-3-12
Description:   需量处理文件
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

#ifndef	__Demand_H
#define	__Demand_H


/*---------------------------------------------------------------------------*/
/*结构体定义*/
/*---------------------------------------------------------------------------*/
typedef struct
{
	ulong32	*PowerAvarageAddr;			/*需量当量存放地址*/
	ulong32 AvaragePowerCode;			/*需要更新1min平均功标示码*/
}SStr_DemandPowerAddr_Type;

/*---------------------------------------------------------------------------*/
/*宏定义*/
/*---------------------------------------------------------------------------*/
#define C_1minAvaragePowerNum		60					/*记录1min平均功率个数*/
			
#define C_NormalDemandInterval		15					/*默认需量周期*/
#define	C_NormalSlipTime			1					/*默认滑差时间*/
#define	C_NormalRate				1					/*默认费率*/
			
#define C_DerictionChange_AT		0x08				/*合相有功功率方向改变*/
#define C_DerictionChange_RT		0x09				/*合相无功功率方向改变*/
#define	C_DerictionChange_AA		0x0A				/*A相有功功率方向改变*/
#define	C_DerictionChange_AB		0x0B				/*B相有功功率方向改变*/
#define	C_DerictionChange_AC		0x0C				/*C相有功功率方向改变*/
#define	C_DerictionChange_RA		0x0D				/*A相无功功率方向改变*/
#define	C_DerictionChange_RB		0x0E				/*B相无功功率方向改变*/
#define	C_DerictionChange_RC		0x0F				/*C相无功功率方向改变*/
			
#define C_DerictActive_T			0x08				/*有功总方向标志字*/
#define C_DerictActive_A			0x01				/*有功A相方向标志字*/
#define C_DerictActive_B			0x02				/*有功B相方向标志字*/
#define C_DerictActive_C			0x04				/*有功C相方向标志字*/
#define C_DerictReactive_T			0x80				/*无功总方向标志字*/
#define C_DerictReactive_A			0x10				/*无功A相方向标志字*/
#define C_DerictReactive_B			0x20				/*无功B相方向标志字*/
#define C_DerictReactive_C			0x40				/*无功C相方向标志字*/
			
#define C_NormalCom1Mode			0x41				/*组合无功1默认模式字*/
#define C_NormalCom2Mode			0x14				/*组合无功2默认模式字*/
			
#define C_ReworkDemand				0x68		

#define CCurr_AcDemandLen			4						
#define CL_DemandAndTime			11					/*最大需量及发生时间数据层长度*/
#define CL_Demand					4					/*最大需量及发生时间中需量长度*/
						
#define C_T_ActiveCodeID			0x01				/*合相有功标识码*/
#define C_T_ReactiveCodeID			0x02				/*合相无功标识码*/
#define C_A_ActiveCodeID 			0x03				/*A相有功标识码*/
#define C_A_ReactiveCodeID 			0x04				/*A相无功标识码*/
#define C_B_ActiveCodeID 			0x05				/*B相有功标识码*/
#define C_B_ReactiveCodeID 			0x06				/*B相无功标识码*/
#define C_C_ActiveCodeID 			0x07				/*C相有功标识码*/
#define C_C_ReactiveCodeID 			0x08				/*C相无功标识码*/
				
#define C_GetNextRatesDemand		0x00000001			/*获取下一个费率需量标识码*/
#define C_GetNextQuadrantDemand		0x00100000		    /*获取下一个象限需量标识码*/

#define C_DeActiveDirection 		0x00				/*正向*/
#define C_DeReactiveDirection		0x80				/*反向*/

/*需量读取方法*/							
#define C_De_OADGetTpye_Com			0x01				/*组合需量类*/
#define C_De_OADGetTpye_Other		0x02				/*其他需量类*/

/*初始化总有功\总无功需量定时器标志*/
#define C_TDemandTimerInit_Flag		0x01				/*初始化总有功、总无功需量定时器*/
#define C_TDemandTimerNoInit_Flag	0x00				/*不初始化总有功、总无功需量定时器*/

#define CL1minPerPower              4					/*1min平均功率长度*/

/*需量周期定时器，ABC相在数组中的位置*/
#define C_APhasePosition            0					/*需量周期定时器中A相位置*/
#define C_BPhasePosition            1					/*需量周期定时器中B相位置*/
#define C_CPhasePosition            2					/*需量周期定时器中C相位置*/

/*---------------------------------------------------------------------------*/
/*函数声明*/
/*---------------------------------------------------------------------------*/
void SF_InitDemandTimer(uchar8 V_ucFlay);
void SF_Clear_CurrentDemand(void);

#endif
