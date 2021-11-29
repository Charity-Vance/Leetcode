/********************************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     MultiFunctionOutput.c
Version:       V1
Author:        
Date:          2014-3-12
Description:   多功能端口输出
---------------------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
History3:      第3次修改
内容1. Date:2021.09.22
       Author:zlj
       Modification:
---------------------------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
********************************************************************************************/
#include "Public.h"
#include "MultiFunctionOutput.h"
#include "IO.h"
#include "timer.h"

static uchar8 GV_ucMultiFunctionOutput;             /*用于多功能输出特征字*/
                                                    /*C_SecondPulseOutput：秒脉冲*/
                                                    /*C_DemandPulseOutput：需量周期脉冲*/
                                                    /*C_RatePulseOutput：时段投切脉冲*/

/*******************************************************************************
函数原型: void InF_MultiFunctionOutput_Init(void)
功能描述: 多功能输出上电初始化的处理
输入参数: 无
输出参数: 多功能输出在上电后默认为秒脉冲
返回参数: 无
调用位置: 仅上电初始化调用
备    注: 上电输出秒脉冲，并将特征字初始化为秒脉冲
*******************************************************************************/
void InF_MultiFunctionOutput_Init(void)
{
	GV_ucMultiFunctionOutput = C_SecondPulseOutput;
	
	DF_MultiFunction_SelectSecondPulse();
	DF_MultiFunction_OutputSecondPulse();
	
	SF_Set_MultiFunctionTimer(C_Interval_0ms);
}

/*******************************************************************************
函数原型: uchar8 InF_ModifyFunctionWord(uchar8 V_Data)
功能描述: 通信设置模式字时直接调用本函数，通信模块不需要判断设置为什么脉冲输出
输入参数: V_ucData上位机设置的数据，原始数据，不需要转换，通信模块可以不判断合法性	
输出参数: 多功能端子输出，详见下面的功能说明
返回参数: C_OK：输入参数正确；C_DataError：输入数据错误	
调用位置: 通信调用
备    注: 通信修改多功能模式字时，调用本函数									
         在本函数内部，判断是否修改为秒脉冲										
         设置为秒脉冲：立即转为秒脉冲输出（调用驱动函数）						
         设置为其他脉冲：将口线转为非秒脉冲的常态								
         设置为非法值：原来输出什么脉冲还输出什么脉冲，并返回C_DataError：输入数据错误
*******************************************************************************/
uchar8 InF_ModifyFunctionWord(uchar8 V_ucData)
{
	uchar8 V_ucreturn = C_OK;       /*返回值置为正确*/
	switch ( V_ucData )
	{
		case C_SecondPulseOutput:
		{
			GV_ucMultiFunctionOutput = C_SecondPulseOutput;	/*模式字切换*/
			DF_MultiFunction_SelectSecondPulse();			/*选择秒脉冲：立即输出秒脉冲*/
		}break;
        
		case C_DemandPulseOutput:
		{
			GV_ucMultiFunctionOutput = C_DemandPulseOutput;	/*模式字切换*/
			DF_MultiFunction_SelectDemandPulse();			/*选择需量周期脉冲：但不输出需量周期脉冲*/
		}break;
        
		case C_RatePulseOutput:
		{
			GV_ucMultiFunctionOutput = C_RatePulseOutput;   /*模式字切换*/
			DF_MultiFunction_SelectRatePulse();				/*选择时段投切脉冲：但不输出时段投切脉冲*/
		}break;
        
		default:
		{
			V_ucreturn = C_DataError;
		}break;
	}
	return V_ucreturn;
}

/*******************************************************************************
函数原型: InF_MultiFunctionOutput
功能描述: 多功能输出
输入参数: C_SecondPulse：秒脉冲输出
          C_DemandPulse：需量周期脉冲输出
          C_RatePulse：  时段投切脉冲输出
输出参数: 无
返回参数: 无
调用位置: 需量处理、费率判断
备    注: 在需量模块、费率模块调用该函数时，不需要区分输出何种脉冲，只管调用本函数就可以了
          在本函数内部，将RAM中的多功能脉冲输出方式，再确定输出何种脉冲
*******************************************************************************/
void InF_MultiFunctionOutput(uchar8 V_ucFunction)
{
	if ( (C_SecondPulseOutput == GV_ucMultiFunctionOutput) && (C_SecondPulse == V_ucFunction) )
	{
		DF_MultiFunction_SelectSecondPulse();
		SF_Set_MultiFunctionTimer(C_Interval_0ms);
	}
	
	if ( (C_DemandPulseOutput == GV_ucMultiFunctionOutput) && (C_DemandPulse == V_ucFunction) )
	{
		DF_MultiFunction_SelectDemandPulse();
		DF_MultiFunction_OutputDemandPulse();
		SF_Set_MultiFunctionTimer(C_TimerSwitch_8|C_Interval_80ms);
	}
	
	if ( (C_RatePulseOutput == GV_ucMultiFunctionOutput) && (C_RatePulse == V_ucFunction) )
	{
		DF_MultiFunction_SelectRatePulse();
		DF_MultiFunction_OutputDemandPulse();
		SF_Set_MultiFunctionTimer(C_TimerSwitch_8 | C_Interval_80ms);
	}
}

/*******************************************************************************
函数原型: uchar8 InF_ModifyFunctionStatus(void)	
功能描述: 698读取当前多功能输出状态
输入参数: 无
输出参数: 无
返回参数: V_return：多功能输出状态
调用位置: 
备    注: 
*******************************************************************************/
uchar8 InF_ModifyFunctionStatus(void)
{
	uchar8 V_ucreturn = C_SecondPulseOutput;			/*返回值置为秒脉冲*/
	switch ( GV_ucMultiFunctionOutput )
	{
		case C_SecondPulseOutput:
		{
			V_ucreturn = C_SecondPulseOutput;			/*模式字切换*/
		}break;
        
		case C_DemandPulseOutput:
		{
			V_ucreturn = C_DemandPulseOutput;			/*模式字切换*/
		}break;
        
		case C_RatePulseOutput:
		{
			V_ucreturn = C_RatePulseOutput;				/*模式字切换*/
		}break;
        
		default:
		{
			V_ucreturn = C_SecondPulseOutput;
		}break;
	}
	return V_ucreturn;
}





