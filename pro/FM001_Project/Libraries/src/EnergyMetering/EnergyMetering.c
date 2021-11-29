/********************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     EnergyMetering.c
Version:       V1
Author:        jiangzs
Date:          2014-3-12
Description:   电能处理文件
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:   20219016
       Author: fy
       Modification:
       --------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
       Author:
       Modification:
       --------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
********************************************************************************/

#include "Public.h"
#include "EnergyMetering.h"


/*--------------------------------------------------------------------------*/
/*全局变量*/
/*--------------------------------------------------------------------------*/
static uchar8 SV_ucEnergySafeFlag;
static uchar8 SV_ucMoneyToPurchaseFlag[3];		/*充值标志,带两字节CRC,CRC不对认为没有购电*/
/*--------------------------------------------------------------------------*/

/*组合电能和脉冲数标识码转换*/
const ulong32 C_CurrentEnergyCode[ ][2]=
{	/*通信数据标识，				数据层数据标识*/
	CCom_Ac_PreEn_FF_0,		CPos_Ac_En_PreFF_0,         /*组合有功总电能*/
	
	CCom_Re1_PreEn_FF_0,	CQua1_Re_PreEn_FF_0,	    /*组合无功1总电能*/
	CCom_Re2_PreEn_FF_0,	CQua1_Re_PreEn_FF_0,	    /*组合无功2总电能*/
	
	C_Fre_AComRe1PreEn, 	C_Fre_AQuadrant1PreEn,		/*A相组合无功1电能*/
	C_Fre_AComRe2PreEn, 	C_Fre_AQuadrant1PreEn,		/*A相组合无功2电能*/

	C_Fre_BComRe1PreEn, 	C_Fre_BQuadrant1PreEn,		/*B相组合无功1电能*/
	C_Fre_BComRe2PreEn, 	C_Fre_BQuadrant1PreEn,		/*B相组合无功2电能*/
	
	C_Fre_CComRe1PreEn, 	C_Fre_CQuadrant1PreEn,		/*C相组合无功1电能*/
	C_Fre_CComRe2PreEn, 	C_Fre_CQuadrant1PreEn,		/*C相组合无功2电能*/
};  
#define C_EnergyCodeNum   ( (sizeof(C_CurrentEnergyCode) / 2 ) / sizeof(ulong32) )
 
/*组合电能*/
const uchar8 C_ComEnergyCode[ ]=
{
	0x00, 0x30, 0x40
};
#define C_ComDI2Num   ( ( sizeof(C_ComEnergyCode) ) / sizeof(uchar8) )


const uchar8 C_RCom1EnergyCode[ ]=
{
	0x30, 0x31, 0x32, 0x33
};
#define C_RCom1DI2Num   ( ( sizeof(C_RCom1EnergyCode) ) / sizeof(uchar8) )


/***************************************************************************************************
函数原型：void SF_SendMessege(uchar8 V_ucMsgDerictAddr, uchar8 *pV_ucBuffer, uchar8 V_ucMsgLen)
功能描述：发送消息
输入参数：V_ucMsgDerictAddr,目的地址；
          pV_ucBuffer，发送消息类型存放地址；
		  V_ucMsgLen，消息长度；V_ucMsgLen长度已经包括1字节的消息类型的长度，因此函数内部不需要再加1
输出参数：无
返回参数：无
调用位置：
备    注：
***************************************************************************************************/
void SF_SendMessege(uchar8 V_ucMsgDerictAddr, uchar8 *pV_ucBuffer, uchar8 V_ucMsgLen)
{
	Str_Msg_Parameter Str_Message;
	
	Str_Message.SourceAddr = C_Msg_EnergyMetering;
	Str_Message.DerictAddr = V_ucMsgDerictAddr;
	Str_Message.Length     = V_ucMsgLen;
	Str_Message.Parameter  = pV_ucBuffer;
	Str_Message.PowerFlag  = C_PowerOn;
	
	InF_WriteMessege(&Str_Message);		/*发送消息*/
}
/***************************************************************************************************
函数原型：void SF_Read_PulseConstant(ulong64 *pV_ullPulseConstant)
功能描述：读取电能脉冲常数的hex形式，读取数据不对默认1000常数
输入参数：pV_ullPulseConstant:指向读取脉冲常数缓存地址
输出参数：*pV_ullPulseConstant：8字节脉冲常数
返回参数：无
调用位置：电能读取接口函数调用	
备    注：
***************************************************************************************************/
void SF_Read_PulseConstant(ulong64 *pV_ullPulseConstant)
{
	uchar8   V_ucTurn;
	uchar8   V_ucBuffer[4];
	ushort16 V_usLen, V_usDataEncode;
	
	V_usDataEncode = 0;
	V_usLen = CLPulse_Constant;
	V_ucTurn = InF_Read_Data(CPulse_Constant, V_ucBuffer, &V_usLen, &V_usDataEncode);
    PF_Buffer8ToUlong64(V_ucBuffer, pV_ullPulseConstant, CLPulse_Constant);
	if( ( V_ucTurn != C_OK ) || ( *pV_ullPulseConstant == 0xFFFFFFFF ) )
	{
		*pV_ullPulseConstant = 1000;
	}
}
#if(_DEBUG_FY) /*拼接后去掉*/
/*******************************************************************************
函数原型：uchar8 SF_ReadEnergy_MethodJudge(ulong32 V_ulDataCode, uchar8 V_ucMethod)
功能描述：读电能方法判断
输入参数：V_ulDataCode：OAD（698OAD）
		 V_ucMethod：V_ ucMethod：（为希望获取的数据格式）C_Format_BCD为BCD格式，C_Format_HEX为hex格式，其他格式后续扩展。
输出参数：pV_ullMaxEnergy电能数据的最大值
返回参数：读取方法：C_Nature2BCD,属性2BCD
				   C_Nature4BCD,属性4BCD
				   C_Nature2HEX,属性2HEX
				   C_Nature4HEX,属性4HEX
				   C_Nature6HEX,属性6HEX
				   C_ErrorMethod,异常方法
调用位置：读取电能
备    注：
*******************************************************************************/
uchar8 SF_ReadEnergy_MethodJudge(ulong32 V_ulDataCode, uchar8 V_ucMethod, ulong64 *pV_ullMaxEnergy)
{
	uchar8 V_ucReturn = C_ErrorMethod;
	
	if ( ( V_ulDataCode & 0xFF00FF00) == 0x00000200)
	{
		if(V_ucMethod == C_Format_BCD)
		{
			V_ucReturn = C_Nature2BCD;
		}
		else if ( V_ucMethod == C_Format_HEX )
		{
			V_ucReturn = C_Nature2HEX;
		}
		
		*pV_ullMaxEnergy = C_ConEnergyToZero_Nature2;
	}
	else if ( ( V_ulDataCode & 0xFF00FF00) == 0x00000400) 
	{
		if(V_ucMethod == C_Format_BCD)
		{
			V_ucReturn = C_Nature4BCD;
		}
		else if ( V_ucMethod == C_Format_HEX )
		{
			V_ucReturn = C_Nature4HEX;
		}
		*pV_ullMaxEnergy = C_ConEnergyToZero_Nature4;
	}
	else if ( ( V_ulDataCode & 0xFF00FF00) == 0x00000600)
	{
		if ( V_ucMethod == C_Format_HEX )
		{
			V_ucReturn = C_Nature6HEX;
		}
		*pV_ullMaxEnergy = C_ConEnergyToZero_Nature6;
	}
	else 
	{
		if ( V_ucMethod == C_Format_BCD )
		{
			V_ucReturn = C_Nature2BCD;
		}
	}

	return V_ucReturn;
}
#endif
/**********************************************************************************************************
函数原型: uchar8 SF_ReadConEnergy_Pulse_Single(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen) 		
功能描述: 单个读取当前组合电能接口函数
输入参数: V_ulDataCode:为读取电能标识码;
		  pV_ucBuffer:读取数据的缓存的首地址
		  *pV_usLen: 读取数据的最大缓存的长度
输出参数: pV_ucBuffer:读取数据的缓存的首地址
		  *pV_usLen: 读取数据的长度
返回参数: C_OK表示读取成功，
          C_IDError表示数据标识码错，
          C_CRCError数据层CRC错，
          C_DataLenError表示数据长度错
          C_NoAccess表示无权限，
          C_SafeFlagError表示安全标志错，
          C_Error表示其他错误
调用位置: 电能读取接口函数调用
备    注: 与SF_ReadConEnergy_Pulse函数区别：
          SF_ReadConEnergy_Pulse会判断是否是集合，循环读取;
          SF_ReadConEnergy_Pulse_Single只能单个读取;

		  /---------------------------------------------------------------------------/
		  *		*	OAD属性2		*	OAD属性4			*		OAD属性6		  *				
		  *-------------------------------------------------*-------------------------*
		  *	HEX	*	4字节，2位小数	*	5字节，4位小数		*		1字节			  *
		  /---------------------------------------------------------------------------/

*********************************************************************************************************/
uchar8 SF_ReadConEnergy_Pulse_Single(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	ulong64 V_ullActiveData = 0, V_ullReactiveData = 0, V_ullTemp;
	ulong32 V_ulCodeTemp, V_ulCodeCal;
	uchar8  V_uci, V_ucOAD[C_DataCodeLen], V_ucNum, V_ucMode, V_ucModeTemp;
	ulong64 *pV_ullData;
	ushort16 V_usLen, V_usDataEncode;
	
	PF_Ulong32ToBufferX(V_ucOAD, &V_ulDataCode, C_DataCodeLen);		/*将标识码转换为数组*/
	
	/*首先判断需要读取的数据标识*/
	V_ulCodeTemp = ( V_ulDataCode & 0xFFFF0000 ) | 0x00000400;
	for( V_uci = 0; V_uci < C_EnergyCodeNum; V_uci++ )
	{
		if( C_CurrentEnergyCode[V_uci][0] == V_ulCodeTemp )
		{
			V_ulCodeTemp = C_CurrentEnergyCode[V_uci][1] | ( V_ulDataCode & 0x000000FF );
			break;
		}
	}   
	if(V_uci >= C_EnergyCodeNum)		/*没有查找到数据标识码，应答数据表示错*/
	{
		return C_IDError;
	}
	   
	/*读取数据层组合有功模式字*/
	V_usDataEncode = 0;
	V_usLen = CLActive_Com_State;
	if( V_ucOAD[C_O_DI2] == 0x00 )		/*组合有功总电能*/
	{
		if( InF_Read_Data( CActive_Com_State, &V_ucMode, &V_usLen, &V_usDataEncode) != C_OK )	
		{
			V_ucMode = 0x05;			/*模式字读取数据层出错，默认正加反*/
		}
		V_ucMode &= 0x0F;				/*组合有功模式字高4位无效*/
	}
	else
	{
        /*读取组合无功模式字*/
		for( V_uci = 0; V_uci < C_RCom1DI2Num; V_uci++ )
		{
			if( C_RCom1EnergyCode[V_uci] == V_ucOAD[C_O_DI2] )
			{
				break;
			}
		}
		if( V_uci < C_RCom1DI2Num )
		{
			if( InF_Read_Data( CReactive_Com_State1, &V_ucMode, &V_usLen, &V_usDataEncode ) != C_OK )	
			{
				V_ucMode = 0x41;				/*模式字读取数据层出错，默认1、4象限相加*/
			}
		}
		else
		{
			if( InF_Read_Data( CReactive_Com_State2, &V_ucMode, &V_usLen, &V_usDataEncode ) != C_OK )	
			{
				V_ucMode = 0x14;				/*模式字读取数据层出错，默认2、3象限相加*/
			}
		}
	}
	
	if( ( ( V_ucOAD[C_O_DI2] == 0x40 )
	   || ( V_ucOAD[C_O_DI2] == 0x30 )
	   || ( V_ucOAD[C_O_DI2] == 0x00 ) )
	   && ( V_ucOAD[C_O_DI0] == 0x01 ) )  		/*合相组合电能的总电能，需要读取12费率电能累加得到*/
	{
		V_ucNum = C_MaxRatesNum;
	    V_ulCodeTemp += C_GetNextRatesEnergy;
	}
	else if( ( ( V_ulCodeTemp & 0x000F0000 ) != 0x00000000 ) && ( V_ucOAD[C_O_DI0] == 0x00 ) )		/*分相索引00电能*/
	{
		V_ucNum = 1;
	    V_ulCodeTemp += C_GetNextRatesEnergy;
	}
	else
	{
		V_ucNum = 1;
	}
	
	/*以下读取累加到组合电能的电能数据*/
	for( V_uci = 0; V_uci < 4; V_uci++ )								/*有功有2组电量需要组合，无功有4组（4个象限）电量需要组合。循环4次。有功模式字高4位在本函数中已强制成0*/
	{
		V_ucModeTemp = ( V_ucMode >> ( V_uci * 2 ) ) & 0x03;
		if( ( V_ucModeTemp == 0x03 ) || ( V_ucModeTemp == 0x00 ) )		/*模式字对应的一类电能既加又减或者不加不减，组合电能不需要处理*/
		{
			continue;
		}
		
		if( V_ucModeTemp == 0x01 )				/*该电能累加到组合电能*/
		{
			pV_ullData = &V_ullActiveData;	 	/*取加入的临时电能地址*/
		}
		else					             	/*组合电能减去该电能*/
		{
			pV_ullData = &V_ullReactiveData;	/*取减去的临时电能地址*/
		}
		
		V_ullTemp  = 0;
		V_ulCodeCal = V_ulCodeTemp + C_GetNextQuadrantEnergy * V_uci;
		
		V_ucModeTemp = SF_ReadTotalEnergy( V_ulCodeCal, &V_ullTemp, V_ucNum, C_GetNextRatesEnergy );
		if( V_ucModeTemp != C_OK)
		{
			return V_ucModeTemp;	  			/*读取电能数据出错，则返回相应的错误类型*/
		}
		*pV_ullData += V_ullTemp;
	}
		
	
	/*以下计算组合电能*/
	if( V_ullActiveData >= V_ullReactiveData )	/*组合电能中正向电能不小于反向电能*/
	{
		V_ullActiveData = V_ullActiveData - V_ullReactiveData;
		V_ucMode = C_ActiveDirection;
	}
	else
	{
		V_ullActiveData = V_ullReactiveData - V_ullActiveData;
		V_ucMode = C_ReactiveDirection;
	}
	
	SF_Read_PulseConstant(&V_ullTemp);	        						/*读取电能脉冲常ulong64格式*/
    
	/*电能HEX格式，数据层电能小数6位*/
	V_ullActiveData *= C_EnergyChangeEquivalent;	/*这里不会溢出*/
	V_ullActiveData /= V_ullTemp;	

    V_ucModeTemp = SF_DealEnergyPoint(V_ucOAD[C_O_DI1], &V_ullActiveData, &V_usLen);
    if( V_ucModeTemp != C_OK)
    {
        return V_ucModeTemp;
    }       
	
	if( *pV_usLen < V_usLen )
	{
		return C_DataLenError;
	}
	else
	{
	    *pV_usLen = V_usLen;
        
		if(V_ucMode == C_ReactiveDirection)
		{
			V_ullActiveData = (~V_ullActiveData) + 1;
		}
		
		PF_Ulong64ToBuffer8(pV_ucBuffer, &V_ullActiveData, *pV_usLen);
		return C_OK;
	}
}

/********************************************************************************************************
函数原型: uchar8 SF_ReadMonthEnergy(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)		
功能描述: 读取月度用电量
输入参数: V_ulDataCode：为读取电能标识码；
		  pV_ucBuffer：指向读取数据存放的首地址；
		  *pV_usLen：   读取数据的最大缓存的长度；
输出参数: pV_ucBuffer：读取的电能的首地址；
          *pV_usLen：  读取的数据长度；
返回参数: C_OK：表示读取成功，
          C_IDError：表示数据标识码错，
          C_CRCError：数据层CRC错，
          C_DataLenError：表示数据长度错
          C_NoAccess：表示无权限，
          C_SafeFlagError：表示安全标志错，
          C_Error：表示其他错误
调用位置: 电能读取接口函数调用
备    注:（月度用电量=（正向有功总-上1结算正向有功总） 组合 （反向有功总-上1结算反向有功总））
          对外提供的数据格式：4字节HEX，2位小数
*********************************************************************************************************/
uchar8 SF_ReadMonthEnergy(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8  V_ucTurn, V_ucMode;
	uchar8  V_ucBuffer[5];
	ulong64 V_ullActiveEnergy, V_ullReactiveEnergy, V_ullTemp;
	ushort16 V_usLen, V_usDataEncode;

	/****************读取当前正向有功总电能脉冲数****************/
	V_ullActiveEnergy = 0;
	
	V_ucTurn = SF_ReadTotalEnergy(CPos_Ac_T1_PreEn_0, &V_ullActiveEnergy, C_MaxRatesNum, C_GetNextRatesEnergy );
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn; 
	}
	
	/**********读取上一结算时刻正向有功总电能脉冲数据*************/
	V_usDataEncode = 0;
	V_usLen = CLM_Pos_Ac_Tol_En_Pul_1;
	V_ucTurn = InF_Read_Data(CM_Pos_Ac_Tol_En_Pul_1, V_ucBuffer, &V_usLen, &V_usDataEncode);	
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
	
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullTemp, CLM_Pos_Ac_Tol_En_Pul_1);
	V_ullActiveEnergy -= V_ullTemp;		/*当前正向有功总电能减去上一结算时刻正向有功总电能*/

	/****************读取当前反向有功总电能脉冲数****************/
	V_ullReactiveEnergy = 0;

	V_ucTurn = SF_ReadTotalEnergy(CRev_Ac_T1_PreEn_0, &V_ullReactiveEnergy, C_MaxRatesNum, C_GetNextRatesEnergy );
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}

	/**********读取上一结算时刻反向有功总电能脉冲数据*************/
	V_usDataEncode = 0;
	V_usLen = CLM_Rev_Ac_Tol_En_Pul_1;
	V_ucTurn = InF_Read_Data(CM_Rev_Ac_Tol_En_Pul_1, V_ucBuffer, &V_usLen, &V_usDataEncode);	
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullTemp, CLM_Rev_Ac_Tol_En_Pul_1);
	V_ullReactiveEnergy -= V_ullTemp;	/*当前反向有功总电能减去上一结算时刻反向有功总电能*/
	
	/**********读取组合有功模式字*************/
	V_usDataEncode = 0;
	V_usLen = CLActive_Com_State;
	if( InF_Read_Data(CActive_Com_State, &V_ucMode, &V_usLen, &V_usDataEncode) != C_OK )
	{
		V_ucMode = 0x05;	/*模式字读取数据层出错，默认正加反*/
	}
	V_ucMode &= 0x05;		/*698月度用电量减不参与计算**组合有功模式字高4位无效*/
		
	/**********************根据组合模式字计算当前结算周期组合有功累计用电量**********************/
	V_ullTemp = 0;
	
	if( ( V_ucMode & 0x03 ) == 0x01 )		/*正向电能为加*/
	{
		V_ullTemp = V_ullActiveEnergy;
	}
	
	if( ( V_ucMode & 0x0C ) == 0x04 )		/*反向电能为加*/
	{
		V_ullTemp += V_ullReactiveEnergy;
	}
	/*else 不是正加、反加，已赋值0*/
	
	/*************************月度用电量两位小数******************************/
	SF_Read_PulseConstant(&V_ullReactiveEnergy);	  /*读取电能脉冲常数，ulong64格式*/
	V_ullTemp *= C_EnergyChangeEquivalent_Hundred;				/*这里不会溢出*/
	V_ullTemp /= V_ullReactiveEnergy;
				
	if( *pV_usLen <  CLM_Com_Ac_Tol_En_0 )
	{
		return C_DataLenError;
	}	
	
	*pV_usLen = CLM_Com_Ac_Tol_En_0;
	PF_Ulong64ToBuffer8(pV_ucBuffer, &V_ullTemp, CLM_Com_Ac_Tol_En_0);
	
	return C_OK;
}

/***********************************************************************************************************
函数原型：uchar8 SF_ReadSettlementCycleEnergy_L(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
功能描述：读取阶梯结算电能接口函数
输入参数：V_ulDataCode：为读取电能标识码；
		  pV_ucBuffer：指向读取数据缓存的首地址；
          *pV_usLen：读取数据缓存的最大长度；	
输出参数：pV_ucBuffer：读取的电能数据的首地址；
		  *pV_usLen：读取的数据的长度
返回参数：C_OK表示读取成功，C_IDError表示数据标识码错，C_CRCError数据层CRC错，C_DataLenError表示数据长度错
		  C_NoAccess表示无权限，C_SafeFlagError表示安全标志错，C_Error表示其他错误	
调用位置：电能读取接口函数调用	
备    注：
***********************************************************************************************************/
uchar8 SF_ReadSettlementCycleEnergy_L(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8 V_ucTurn;
	uchar8 V_ucBuffer[6];
	ulong64 V_ullEnergyPulse, V_ullReactiveEnergy;
	ushort16 V_usLen, V_usDataEncode;
		
	/****************读取阶梯结算用电量****************/
	V_usDataEncode = 0;
	V_usLen = C_EnergyPulseLen;
	V_ucTurn = InF_Read_Data(V_ulDataCode, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergyPulse, C_EnergyPulseLen);
	
	/*************************阶梯结算用电量为2位小数******************************/
	SF_Read_PulseConstant(&V_ullReactiveEnergy);				  /*读取电能脉冲常数ulong64格式*/
	
	V_ullEnergyPulse *= C_EnergyChangeEquivalent_Hundred;			/*这里不会溢出*/
	V_ullEnergyPulse /= V_ullReactiveEnergy;
	
	if( *pV_usLen < CLY_Com_Ac_Tol_En_0 )
	{
		return C_DataLenError;
	}
	else
	{
		*pV_usLen = CLY_Com_Ac_Tol_En_0;
		PF_Ulong64ToBuffer8(pV_ucBuffer, &V_ullEnergyPulse, CLY_Com_Ac_Tol_En_0);
	}
	return C_OK;
}
/**************************************************************************************************
函数原型：uchar8 SF_ReadSettlementCycleEnergy(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
功能描述：读阶梯结算电能处理
输入参数：V_ulDataCode:需要读取的金额数据标识；
          pV_ucBuffer： 数据存放的首地址；
          *pV_usLen：   数据缓存的最大长度；
输出参数：pV_ucBuffer： 存放的读取的金额数据的首地址；
          pV_usLen：    读取的数据长度；
返回参数：C_OK,读取成功;其他错误;
调用位置：读取阶梯计算电能的接口;
备    注：阶梯结算电能仅本地表支持
          对外提供的数据格式：4字节HEX，2位小数
***************************************************************************************************/
uchar8 SF_ReadSettlementCycleEnergy(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8 V_ucReturn;
	
	if( C_Meter_Type == C_L_SmartMeter )		/*本地费控表*/
	{
		V_ucReturn = SF_ReadSettlementCycleEnergy_L( V_ulDataCode, pV_ucBuffer, pV_usLen );
	}
	else										/*智能表或者远程费控表*/
	{
		V_ucReturn = C_IDError;
	}
	
	return V_ucReturn;
}

/***************************************************************************************************
函数原型：uchar8 SF_ReadRemainingMoney_L(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
功能描述：读取当前剩余金额、透支金额接口函数
输入参数：V_ulDataCode:为读取金额标识码;
		  pV_ucBuffer:指向读取数据存放地址;
		  *pV_usLen:入口表示读取数据的最大缓存长度;
输出参数：pV_ucbuffer:存放读取的金额数据的首地址;
          *pV_usLen:读取的数据长度;
返回参数：C_OK表示读取成功，C_IDError表示数据标识码错，C_CRCError数据层CRC错，C_DataLenError表示数据长度错
		  C_NoAccess表示无权限，C_SafeFlagError表示安全标志错，C_Error表示其他错误
调用位置：电能读取接口函数调用
备    注：本地费控表剩余金额、透支金额处理
          /---------------------------------------------------------------------------/
            对外提供的数据格式
          /---------------------------------------------------------------------------/
          *	4字节HEX，2位小数,0.01元
          * CChargeBal_Hex_Cent 0x202C0201
          * COverDraft_Hex_Cent 0x202D0200
          /---------------------------------------------------------------------------/
         
***************************************************************************************************/
uchar8 SF_ReadRemainingMoney_L(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	ulong64 V_ullMoney;
	uchar8  V_ucBuffer[5], V_ucReturn;
	ushort16 V_usLen, V_usDataEncode;
	
	/****************读取数据层金额/阶梯结算电能****************/
	V_usDataEncode = 0;
	V_usLen = CLChargeBal_Hex_Full;
	V_ucReturn = InF_Read_Data(V_ulDataCode, V_ucBuffer, &V_usLen, &V_usDataEncode);		
	if( V_ucReturn != C_OK )
	{
		return V_ucReturn;
	}
	
	/*读取0.01元的金额*/
	PF_Buffer8ToUlong64( V_ucBuffer, &V_ullMoney, CLChargeBal_Hex_Full );
	V_ullMoney /= C_MoneyChangeEquivalent;
	PF_Ulong64ToBuffer8( V_ucBuffer, &V_ullMoney, CLChargeBal_Hex_Cent );
	
	V_usLen = CLChargeBal_Hex_Cent;
	
	if( *pV_usLen <  V_usLen )
	{
		return C_DataLenError;
	}
	else
	{
		*pV_usLen = V_usLen;
		PF_CopyDataBytes_698(V_ucBuffer, pV_ucBuffer, *pV_usLen);
	}
	
	return C_OK;
}

/**************************************************************************************************
函数原型：uchar8 SF_ReadRemainingMoney(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
功能描述：读金额处理
输入参数：V_ulDataCode:需要读取的金额数据标识；
          pV_ucBuffer： 数据存放的首地址；
          *pV_usLen：   数据缓存的最大长度；
输出参数：pV_ucBuffer： 存放的读取的金额数据的首地址；
          *pV_usLen：    读取的数据长度；
返回参数：C_OK,读取成功;其他错误;
调用位置：读取金额的接口;
备    注： 剩余金额、透支金额
***************************************************************************************************/
uchar8 SF_ReadRemainingMoney(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8 V_ucReturn;
	
	if( C_Meter_Type == C_L_SmartMeter )		/*本地费控表*/
	{
		V_ucReturn = SF_ReadRemainingMoney_L( V_ulDataCode, pV_ucBuffer, pV_usLen );
	}
	else										/*智能表或者远程费控表*/
	{
		V_ucReturn = C_IDError;
	}
	
	return V_ucReturn;
}

/***********************************************************************************************************************
函数原型：uchar8 SF_DealEnergyPoint(uchar8 V_ucNature, ulong64 *pV_ullEnergyPulse, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
功能描述：将脉冲数处理为对应的属性电能需要的小数位数
输入参数：V_ucNature：电能属性，OAD中的属性，属性2，属性4，属性6;
          V_ullEnergyPulse:脉冲数（6位小数）
输出参数：pV_usLen：该属性数据的长度；
返回参数：C_OK：成功；C_NoAccess：无此属性，应答无权限；
调用位置：读电能
备    注：属性2，2位小数；
          属性4，4位小数；
          属性6;
************************************************************************************************************************/
uchar8 SF_DealEnergyPoint(uchar8 V_ucNature, ulong64 *pV_ullEnergyPulse, ushort16 *pV_usLen)
{
	if( V_ucNature == 0x02 )					/*属性2，2位小数*/
	{
		*pV_usLen = C_EnergyNature2HEXLen;
		
		/*将电能HEX格式，小数位数为2位*/
		*pV_ullEnergyPulse /= 10000;
		
		if( *pV_ullEnergyPulse > C_ConEnergyToZero_Nature2 )
		{
			*pV_ullEnergyPulse %= C_ConEnergyToZero_Nature2;
		}
		
	}
	else if( V_ucNature == 0x04 )				/*属性4，4位小数*/
	{
		*pV_usLen = C_EnergyNature4HEXLen;
		
		/*将电能HEX格式，小数位数为4位*/
		*pV_ullEnergyPulse /= 100;
		
		if( *pV_ullEnergyPulse > C_ConEnergyToZero_Nature4 )
		{
			*pV_ullEnergyPulse %= C_ConEnergyToZero_Nature4;
		}

		
	}
	else if( V_ucNature == 0x06 )				/*属性6,脉冲尾数*/
	{
		*pV_usLen = C_EnergyCommPulseLastLen;
		*pV_ullEnergyPulse %= 100;

	}
	else/*异常*/
	{
		return C_NoAccess;
	}

    return C_OK;
}


/**************************************************************************************************
函数原型: uchar8 SF_ReadEnergy_Single(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)   				
功能描述: 读取当前电能接口函数													            	
输入参数: V_ulDataCode:为读取电能标识码;
		  pV_ucBuffer:指向读取数据存放的首地址;
          *pV_usLen:读取数据最大的缓存长度;		    	
输出参数: pV_ucbuffer:读取的电能数据的首地址;  	
		  *pV_usLen:读取数据的长度；
返回参数: C_OK表示读取成功，
		  C_IDError表示数据标识码错，
		  C_CRCError数据层CRC错，
		  C_DataLenError表示数据长度错
		  C_NoAccess表示无权限，
		  C_SafeFlagError表示安全标志错，
		  C_Error表示其他错误						
调用位置: 电能读取接口函数调用																			
备    注: 读取正反向电能;	
		  与SF_ReadEnergy函数区别：
		  SF_ReadEnergy_Single会判断 是否是集合，循环读取;
		  SF_ReadEnergy只能单个读取;	

		  /---------------------------------------------------------------------------/
		  *		*	OAD属性2		*	OAD属性4			*		OAD属性6		  *				
		  *-------------------------------------------------*-------------------------*
		  *	HEX	*	4字节，2位小数	*	5字节，4位小数		*		1字节			  *
		  /---------------------------------------------------------------------------/
***************************************************************************************************/
uchar8 SF_ReadEnergy_Single(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8 V_ucReturn, V_ucNum;
	uchar8 V_ucOAD[C_DataCodeLen];
	ulong32 V_ulCodeTemp;
	ulong64 V_ullEnergyPulse, V_ullTemp;
	ushort16 V_usLen = 0;

	/*首先转换为用于读取脉冲数的数据据标识*/
	
	PF_Ulong32ToBufferX(V_ucOAD, &V_ulDataCode, C_DataCodeLen);	 
	V_ulCodeTemp  = ( V_ulDataCode & 0xFFFF00FF ) | 0x00000400;
	
	if( ( ( V_ucOAD[C_O_DI2] < 0x90 ) && ( ( V_ucOAD[C_O_DI2] & 0x0F ) == 0x00 ) )				/*读取合相总电能*/
	 && ( V_ucOAD[C_O_DI0] == 0x01 ) )	  
	{
		V_ucNum = C_MaxRatesNum;
        V_ulCodeTemp += C_GetNextRatesEnergy;
	}
	else if( ( ( V_ulCodeTemp & 0x000F0000 ) != 0x00000000 ) && ( V_ucOAD[C_O_DI0] == 0x00 ) )	/*读取分相00索引电能*/
	{
		V_ucNum = 1;
        V_ulCodeTemp += C_GetNextRatesEnergy;
	}
	else
	{
		V_ucNum = 1;
	}
	
	V_ullEnergyPulse = 0;
	V_ucReturn = SF_ReadTotalEnergy( V_ulCodeTemp, &V_ullEnergyPulse, V_ucNum, C_GetNextRatesEnergy );
	if( V_ucReturn != C_OK)
	{
		return V_ucReturn;	  						/*读取电能数据出错，则返回相应的错误类型*/
	}		
	
	/*电能转换为HEX格式，电能小数保留6位*/
	SF_Read_PulseConstant(&V_ullTemp);				/*读取电能脉冲常数，ulong64格式*/
	V_ullEnergyPulse *= C_EnergyChangeEquivalent;	/*这里不会溢出*/
	V_ullEnergyPulse /= V_ullTemp;
	
    V_ucReturn = SF_DealEnergyPoint(V_ucOAD[C_O_DI1], &V_ullEnergyPulse, &V_usLen);
    if( V_ucReturn != C_OK)
    {
        return V_ucReturn;                            
    }       


	if( *pV_usLen < V_usLen )
	{
		return C_DataLenError;
	}
	else
	{
		*pV_usLen = V_usLen;
                
		PF_Ulong64ToBuffer8(pV_ucBuffer, &V_ullEnergyPulse, *pV_usLen);
	}
	
	return C_OK;	
}
#if(_DEBUG)  /*自测使用，拼接去掉*/
/*******************************************************************************************************************
函数原型：uchar8 InF_ReadEnergy_Protocol (ulong32 V_ulOAD, uchar8 *pV_ucBuf, ushort8 *pV_ucLen, uchar8 V_ucMethod)
功能描述：统一读取电能接口，兼容BCD和HEX数据读取，
		  该函数根据输入OAD和数据读取方法，从数据层获取脉冲数，并转换为指定格式电能数据写入pV_ucBuf指定的缓存，
		  在实际应用模块调用时默认采用698的OAD调用该接口函数
输入参数：V_ulOAD： 当前正反向有功总及费率、四象限无功总及费率、
					组合有功总及费率、组合无功1、2总及费率、
					分相正反向有功及四象限无功总，
					（以上包括属性2、属性4、属性6）	
					剩余金额、透支金额、月度用电量、结算周期用电量；
		  pV_ucBuf ：读取数据缓存首地址，指向缓存最低地址
		 *pV_usLen：缓存的最大长度
		 V_ ucMethod：（为希望获取的数据格式）C_Format_BCD为BCD格式，C_Format_HEX为hex格式，其他格式后续扩展。
输出参数：*pV_ucBuf存电能数据，*pV_usLen为实际电能数据长度
返回参数：C_OK表示读取成功，C_IDError表示数据标识码错，C_CRCError数据层CRC错，C_DataLenError表示数据长度错
		  C_NoAccess表示无权限，C_SafeFlagError表示安全标志错，C_Error表示其他错误
调用位置：通信（645/698）、事件记录、冻结、安全、结算、电能、卡、显示
备    注：
			/---------------------------------------------------------------------------/
			*		*	OAD属性2		*	OAD属性4			*		OAD属性6		*				
			*---------------------------------------------------*-----------------------*
			*	BCD	*	4字节，2位小数	*	8字节，4位小数		*		无	        	*	
			*---------------------------------------------------*-----------------------*
			*	HEX	*	4字节，2位小数	*	5字节，4位小数		*		1字节			*
			/----------------------------------------------------------------------------/
*******************************************************************************************************************/
uchar8 InF_ReadEnergy_Protocol (ulong32 V_ulOAD, uchar8 *pV_ucBuf, uchar8 *pV_ucLen, uchar8 V_ucMethod)
{
//	uchar8 V_ucDI[C_DataCodeLen], V_uci;
////	uchar8 V_ucBuffer[250];
//	ulong32 V_ulEnergyCode_T;
//	
//	V_ulEnergyCode_T = V_ulOAD;
//	
//#if 0
//	if((V_ulOAD & 0xFF0F0000) != 0)
//	{
//		if((V_ulOAD & 0x00000F00) == 0x400)
//		{
//			V_ulEnergyCode_T = (V_ulEnergyCode_T & 0xFFFFF0FF | 0x200);
//		}
//	}
//#endif
//	
//	/*剩余金额的处理*/
//	if ( /*(V_ulOAD == CChargeBal_BCD)
//	  || (V_ulOAD == COverDraft_BCD)
//	  ||*/ (V_ulOAD == CChargeBal_Hex_Cent)
//      || (V_ulOAD == COverDraft_Hex_Cent)
//	  || (V_ulOAD == CChargeBal_Hex_Full)
//	  || (V_ulOAD == COverDraft_Hex_Full)
//	  || (V_ulOAD == CChargeBal_Hex_Deal)
//	  || (V_ulOAD == COverDraft_Hex_Deal) )	   /*读取剩余金额/透支金额*/
//	{
//		V_ucLenTemp = *pV_ucLen;
//		//V_ucTurn = SF_ReadRemainingMoney(V_ulOAD, V_ucBuffer, &V_ucLenTemp);
////		if(V_ucTurn != C_OK)
////		{
////			return V_ucTurn;
////		}
////		else
////		{
////			PF_CopyDataBytes(V_ucBuffer, pV_ucBuf, *pV_ucLen);
////		}
//	}
//	else
//	{
//		/*判断读取电能类型*/
//		PF_Ulong32ToBufferX(V_ucDI, &V_ulEnergyCode_T, C_DataCodeLen);
//		for(V_uci = 0; V_uci < C_ComDI2Num; V_uci++)
//		{
//			if(C_ComEnergyCode[V_uci] == V_ucDI[C_O_DI2])
//			{
//				break;
//			}
//		}
//		/*读取组合电能*/
//		if( (V_uci < C_ComDI2Num) && (V_ucDI[C_O_DI3] != 0x20) )	  /*组合电能的处理*/
//		{
//			V_ucLenTemp = *pV_ucLen;
//			//V_ucTurn = SF_ReadConEnergy_Pulse(V_ulEnergyCode_T, V_ucBuffer, &V_ucLenTemp, V_ucMethod);
////			if(V_ucTurn != C_OK)
////			{
////				return V_ucTurn;
////			}
////			else
////			{
////				if(*pV_ucLen >= V_ucLenTemp)
////				{
////					*pV_ucLen = V_ucLenTemp;
////					PF_CopyDataBytes(V_ucBuffer, pV_ucBuf, *pV_ucLen);
////				}
////				else
////				{
////					return C_DataLenError;
////				}
////			} 
//		}
//		/*读取月度累计用电量*/
//		else if(V_ulEnergyCode_T == CM_Com_Ac_Tol_En_0)	    /*月度计用电量的计算*/
//		{
//			V_ucLenTemp = *pV_ucLen;
//			//V_ucTurn = SF_ReadSettlementCycleEnergy(V_ulEnergyCode_T, V_ucBuffer, &V_ucLenTemp);
//			//if(V_ucTurn != C_OK)
//			//{
//			//	return V_ucTurn;
//			//}
//			//else
//			//{
//			//	PF_CopyDataBytes(V_ucBuffer, pV_ucBuf, V_ucLenTemp);
//			//}
//		}
//		/*读取其他电能*/
//		else
//		{
//			V_ucLenTemp = *pV_ucLen;
//			//V_ucTurn = SF_ReadEnergy(V_ulEnergyCode_T, V_ucBuffer, &V_ucLenTemp, V_ucMethod);
//			//if(V_ucTurn != C_OK)
////			{
////				return V_ucTurn;
////			}
////			else
////			{
////				if(*pV_ucLen >= V_ucLenTemp)
////				{
////					*pV_ucLen = V_ucLenTemp;
////					PF_CopyDataBytes(V_ucBuffer, pV_ucBuf, V_ucLenTemp);
////				}
////				else
////				{
////					return C_DataLenError;
////				}
////			}
//		}
//	}
    return C_OK;
}
#endif
/**************************************************************************************************************************
函数原型：uchar8 SF_ReadTotalEnergy(ulong32 V_ulPulOAD, ulon64 *pV_ullTolEnergy, uchar8 V_ucCalNum, ulong32 V_ulOADRegular )
功能描述：读总电能
输入参数：V_ulPulOAD:费率1脉冲数的OAD或A相脉冲数OAD；
          pV_ullTolEnergy:总电能地址；
          V_ucCalNum:需要累加的个数，C_MaxRatesNum：12费率；C_OnePhase:1相；C_ThreePhase:3相;
          V_ulOADRegular:OAD计算的规律，用于循环读取脉冲数;
          	C_GetNextRatesEnergy：0x00000001，获取下一个费率电能；
          	C_GetNextPhaseEnergy: 0x00010000,获取下一个分相电能；
输出参数：pV_ullTolEnergy:总电能地址；
返回参数：C_OK：成功; C_Error:读取脉冲数失败；
调用位置：电能模块
备    注：总电能为计算得到；
**************************************************************************************************************************/
uchar8 SF_ReadTotalEnergy(ulong32 V_ulPulOAD, ulong64 *pV_ullTolEnergy, uchar8 V_ucCalNum, ulong32 V_ulOADRegular )
{
	uchar8  V_uci, V_ucReturn = C_Error;
	uchar8  V_ucBuffer[C_EnergyPulseLen] = {0};
    ushort16 V_usLen, V_usDataEncode;	
	ulong64 V_ullEnergyPulse = 0, V_ullTemp = 0;
	
	for(V_uci = 0; V_uci < V_ucCalNum; V_uci++)
	{
		V_usDataEncode = 0;
		V_usLen = C_EnergyPulseLen;
		V_ucReturn = InF_Read_Data(V_ulPulOAD, V_ucBuffer, &V_usLen, &V_usDataEncode);		
		if( V_ucReturn != C_OK )
		{
			return V_ucReturn;
		}
		PF_Buffer8ToUlong64(V_ucBuffer, &V_ullTemp, C_EnergyPulseLen);
		V_ullEnergyPulse += V_ullTemp;
        V_ulPulOAD += V_ulOADRegular;
	}
	
	*pV_ullTolEnergy = V_ullEnergyPulse;
	return V_ucReturn;
}

/*******************************************************************************
函数原型：uchar8 SF_GetEnergy_Type(ulong32 V_ulOAD)
功能描述：获取电能数据的类型
输入参数：V_ulOAD为读取的OAD
输出参数：无
返回参数：电能数据的类型
		  C_En_OADGetTpye_Money:金额类（剩余金额、透支金额）
		  C_En_OADGetTpye_Com:	组合电能类
		  C_En_OADGetTpye_Month:月度用电量
		  C_En_OADGetTpye_StepSettle：阶梯结算电量
		  C_En_OADGetTpye_Other:其他电能
调用位置：读电能、金额接口
备    注：
*******************************************************************************/
uchar8 SF_GetEnergy_Type(ulong32 V_ulOAD)
{
	uchar8 V_ucEnergyType;
	uchar8 V_ucOAD[C_DataCodeLen];
	uchar8 V_uci;
		
	if( ( V_ulOAD == CChargeBal_Hex_Cent )		/*剩余金额、透支金额，与协议相同数据标识*/
     || ( V_ulOAD == COverDraft_Hex_Cent ) )
	{
		V_ucEnergyType = C_En_OADGetTpye_Money;
	}
	else if( V_ulOAD == CM_Com_Ac_Tol_En_0 )	/*月度用电量*/
	{
		V_ucEnergyType = C_En_OADGetTpye_Month;
	}
	else if( V_ulOAD == CY_Com_Ac_Tol_En_0 )	/*阶梯结算用电量*/
	{
		V_ucEnergyType = C_En_OADGetTpye_StepSettle;
	}	
	else
	{
		PF_Ulong32ToBufferX(V_ucOAD, &V_ulOAD, C_DataCodeLen);
		
		for(V_uci = 0; V_uci < C_ComDI2Num; V_uci++)
		{
			V_ucOAD[C_O_DI2] = V_ucOAD[C_O_DI2] & 0xF0;
			if( C_ComEnergyCode[V_uci] == V_ucOAD[C_O_DI2] )
			{
				break;
			}
		}
		if(V_uci < C_ComDI2Num)					 /*组合电能*/
		{
			V_ucEnergyType = C_En_OADGetTpye_Com;
		}
		else
		{
			V_ucEnergyType = C_En_OADGetTpye_Other;
		}	
	}
	
	return V_ucEnergyType;
}

/**********************************************************************************************************
函数原型: uchar8 SF_ReadConEnergy_Pulse(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)  		
功能描述: 读取当前组合电能接口函数
输入参数: V_ulDataCode:为读取电能标识码,
          pV_ucBuffer:指向读取数据存放的首地址,
          *pV_usLen:最大缓存长度；	    	
输出参数: pV_ucbuffer:存放读取电能数据的首地址；
		  *pV_usLen:读取数据的长度；
返回参数: C_OK表示读取成功，
          C_IDError表示数据标识码错，
          C_CRCError数据层CRC错，
          C_DataLenError表示数据长度错
          C_NoAccess表示无权限，
          C_SafeFlagError表示安全标志错，
          C_Error表示其他错误
调用位置: 电能读取接口函数调用
备    注: 与SF_ReadConEnergy_Pulse函数区别：
		  SF_ReadConEnergy_Pulse会判断是否是集合，循环读取；
		  SF_ReadConEnergy_Pulse_Single只能单个读取，读集合
*********************************************************************************************************/
uchar8 SF_ReadConEnergy_Pulse(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8  V_ucTimes, V_uci, V_ucReturn;
	ushort16 V_usDataLen = 0, V_usDataOffset = 0;
   
    if( ( V_ulDataCode & 0x000F00FF ) == 0x00000000 ) 		/*集合读取*/
    {
    	V_ucTimes = C_RatesNumTol;
		V_ulDataCode += C_GetNextRatesEnergy;   			/*集合，数据标识从索引1开始读*/
	}
	else			 /*单独读取总电能、费率电能、分相电能（00索引和01索引）*/
	{
		V_ucTimes = 1;
	}
    
    for( V_uci = 0; V_uci < V_ucTimes; V_uci++)
    {

        if( *pV_usLen < V_usDataLen )
        {
            return C_DataLenError;
        }
        
		*pV_usLen -= V_usDataLen;
    	V_usDataLen = *pV_usLen;
    	V_ucReturn = SF_ReadConEnergy_Pulse_Single(V_ulDataCode, &pV_ucBuffer[V_usDataOffset], &V_usDataLen);
    	if( V_ucReturn != C_OK)
    	{
    		return V_ucReturn;
    	}
        V_usDataOffset += V_usDataLen;
		V_ulDataCode += C_GetNextRatesEnergy;
	}
	*pV_usLen = V_usDataOffset;
	
	return V_ucReturn;        
}

/**********************************************************************************************************
函数原型: uchar8 SF_ReadEnergy(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen) 		
功能描述: 读取当前电能接口函数													           
输入参数: V_ulDataCode:为读取电能标识码,
          pV_ucBuffer:指向读取数据存放的首地址,
          *pV_usLen:最大缓存长度；	    	
输出参数: pV_ucbuffer:存放读取电能数据的首地址；
		  *pV_usLen:读取数据的长度；
返回参数: C_OK表示读取成功，
          C_IDError表示数据标识码错，
          C_CRCError数据层CRC错，
          C_DataLenError表示数据长度错
          C_NoAccess表示无权限，
          C_SafeFlagError表示安全标志错，
          C_Error表示其他错误						
调用位置: 电能读取接口函数调用																			
备    注: 与SF_ReadConEnergy_Pulse函数区别：
		  SF_ReadEnergy会判断是否是集合，循环读取；	
		  SF_ReadConEnergy_Pulse_Single只能单个读取，读集合																			                
*********************************************************************************************************/
uchar8 SF_ReadEnergy(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8  V_ucTimes, V_uci, V_ucReturn;
	ushort16 V_usDataLen = 0, V_usDataOffset = 0;
   
    if( ( V_ulDataCode & 0x000F00FF ) == 0x00000000 ) 		/*集合读取*/
    {
    	V_ucTimes = C_RatesNumTol;
		V_ulDataCode += C_GetNextRatesEnergy;

	}
	else			 /*单独读取*/
	{
		V_ucTimes = 1;
	}
    
    for( V_uci = 0; V_uci < V_ucTimes; V_uci++)
    {
    	if( *pV_usLen < V_usDataLen )
    	{
    		return C_DataLenError;
    	}
		
    	*pV_usLen -= V_usDataLen;
    	V_usDataLen = *pV_usLen;
    	V_ucReturn = SF_ReadEnergy_Single(V_ulDataCode, &pV_ucBuffer[V_usDataOffset], &V_usDataLen);
    	if( V_ucReturn != C_OK)
    	{
    		return V_ucReturn;
    	}
        V_usDataOffset += V_usDataLen;
		V_ulDataCode += C_GetNextRatesEnergy;
	}
	
	*pV_usLen = V_usDataOffset;
	return V_ucReturn;        
}

/**********************************************************************************************************************************
函数原型：uchar8 InF_Get_EnergyModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
功能描述：读电能、金额接口
输入参数：V_ulOAD:需要读取的OAD；
          pV_ucDataBuf:读取数据的缓存的首地址
         *pV_usDataLen:读取数据的缓存的最大长度；
输出参数：pV_ucDataBuf:读取数据的缓存的首地址
		 *pV_usDataLen:读取数据实际长度；
         *pV_usDataEncode:数据内部编码；
返回参数：C_OK,读取成功;其他错误;
调用位置：对象管理层
备    注：/---------------------------------------------------------------------------/
            电能模块对外提供的数据格式
          /---------------------------------------------------------------------------/
          /-金额----------------------------------------------------------------------/
          * 4字节HEX，2位小数,0.01元
          * CChargeBal_Hex_Cent 0x202C0201
          * COverDraft_Hex_Cent 0x202D0200
          /---------------------------------------------------------------------------/
          /-月度用电量、阶梯结算用电量------------------------------------------------/
          * 4字节HEX，2位小数，0.01元
          /-当前电能------------------------------------------------------------------/
          * 属性2,4字节HEX，2位小数
          * 属性4,5字节HEX，4位小数
          * 属性6,1字节HEX
          /---------------------------------------------------------------------------/
************************************************************************************************************************************/
uchar8 InF_Get_EnergyModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
{
	uchar8 V_ucEnergyType;
	uchar8 V_ucReturn;
	
	V_ucEnergyType = SF_GetEnergy_Type( V_ulOAD );
	
	if( V_ucEnergyType == C_En_OADGetTpye_Money )			/*金额*/
	{
		V_ucReturn = SF_ReadRemainingMoney( V_ulOAD, pV_ucDataBuf, pV_usDataLen );
		
	}
	else if( V_ucEnergyType == C_En_OADGetTpye_Month )		/*月度用电量*/
	{		
		V_ucReturn = SF_ReadMonthEnergy( V_ulOAD, pV_ucDataBuf, pV_usDataLen );	
		
	}
	else if( V_ucEnergyType == C_En_OADGetTpye_StepSettle )	/*阶梯结算用电量*/
	{
		V_ucReturn = SF_ReadSettlementCycleEnergy( V_ulOAD, pV_ucDataBuf, pV_usDataLen );
		
	}	
	else if( V_ucEnergyType == C_En_OADGetTpye_Com )		/*组合电能*/
	{
		V_ucReturn = SF_ReadConEnergy_Pulse( V_ulOAD, pV_ucDataBuf, pV_usDataLen );
		
	}
	else if( V_ucEnergyType == C_En_OADGetTpye_Other )		/*其他电能*/
	{
		V_ucReturn = SF_ReadEnergy( V_ulOAD,  pV_ucDataBuf, pV_usDataLen );
		
	}
	else
	{
		V_ucReturn = C_Error;
		
	}
	
	return V_ucReturn;
}
/*******************************************************************************
函数原型：uchar8 SF_SetOverDraft_Meter_Work_State(uchar8 V_ucState, uchar8 V_ucSafeFlag)
功能描述：写电表运行状态字1中透支状态位 
输入参数：V_ucState:C_SetOverDraft:置位；C_ClrOverDraft:清位；
          V_ucSafeFlag:写数据层的安全标志，SV_ucEnergySafeFlag，电能安全标志；C_W_SafeFlag，写安全
输出参数：无  
返回参数：C_OK,写成功；C_Error，写失败； 
调用位置：
备    注：
*******************************************************************************/
uchar8 SF_SetOverDraft_Meter_Work_State(uchar8 V_ucState, uchar8 V_ucSafeFlag)
{
	uchar8   V_ucBuffer[2];
	ushort16 V_usLen, V_usDataEncode;
	
	V_usDataEncode = 0;
	V_usLen = CLMeter_Work_State1;
	if( InF_Read_Data(CMeter_Work_State1, V_ucBuffer, &V_usLen, &V_usDataEncode) != C_OK )
	{
		return C_Error;
	}
	
	if(V_ucState == C_SetOverDraft)
	{
		V_ucBuffer[1] |= C_SetOverDraft;	/*透支状态置位，置1*/
	}
	else
	{
		V_ucBuffer[1] &= C_ClrOverDraft;	/*透支状态清位，置0*/
	}
	
	if( InF_Write_Data(C_Msg_EnergyMetering, CMeter_Work_State1, V_ucBuffer, CLMeter_Work_State1, V_ucSafeFlag ) != C_OK )
	{
		return C_Error;
	}
	
	return C_OK;
}

/*******************************************************************************
函数原型：void SF_EnergyInit_R(void)
功能描述：上电电能静态变量初始化  
输入参数：无 
输出参数：无  
返回参数：无 
调用位置：调度上电初始化时调用
备    注：非本地表上电初始化只需要将安全标志清零即可	
*******************************************************************************/
void SF_EnergyInit_R(void)
{
    SV_ucEnergySafeFlag = 0;	/*安全标志清零*/
	
	SF_SetOverDraft_Meter_Work_State( C_ClrOverDraft, C_W_SafeFlag );
	
}

/*******************************************************************************
函数原型：void SF_EnergyInit_L(void)
功能描述：上电电能静态变量初始化 
输入参数：无
输出参数：无
返回参数：无
调用位置：调度上电初始化时调用	
备    注：本地表上电初始化将安全标志清零，同时读取剩余金额和透支金额判断是否需要发送“透支”显示给显示
*******************************************************************************/
void SF_EnergyInit_L(void)
{
	ulong64 V_ullRemainingMoney, V_ullOverdraftMoney;
	
    SV_ucEnergySafeFlag = 0;		/*安全标志清零*/
	
	/******************读取数据层剩余金额、透支金额************************************/	
	if( SF_Get_RMoney_DMoney(&V_ullRemainingMoney, &V_ullOverdraftMoney) != C_OK )
	{
		return;
	}
	
	/*********************判断报警、预跳闸报警、透支、立即跳闸状态***********************/
	SF_JudgeWarningStatus(V_ullRemainingMoney, V_ullRemainingMoney, 0, V_ullOverdraftMoney, C_RenewDerict);	/*这里扣费前透支金额写成0，保证透支金额不为0的时候进行透支报警*/

}

/********************************************************************************************
函数原型：void InF_EnergyInit(void)
功能描述：上电电能静态变量初始化 
输入参数：无
输出参数：无
返回参数：无
调用位置：调度上电初始化时调用
备    注：调度上电初始化调用，不需要区分本地费控表或者远程费控表、智能表，函数内部进行区别处理
**********************************************************************************************/
void InF_EnergyInit(void)
{
	if( C_Meter_Type == C_L_SmartMeter )	/*本地费控电能表*/
	{
		SF_EnergyInit_L( );
	}
	else
	{
		SF_EnergyInit_R( );
	}
}

/********************************************************************************************************
函数原型：uchar8 SF_ReadEnergy_Settlement_L(void)
功能描述：用于结算模块，阶梯结算用电量做结算
输入参数：无
输出参数：无
返回参数：C_OK表示读取成功，C_IDError表示数据标识码错，C_CRCError数据层CRC错，C_DataLenError表示数据长度错
		  C_NoAccess表示无权限，C_SafeFlagError表示安全标志错，C_Error表示其他错误
调用位置：结算模块进行结算周期电能结算时调用
备    注：
*******************************************************************************************************/
uchar8 SF_ReadEnergy_Settlement_L(void)
{
	ulong64  V_ullEnergy, V_ullTemp;
	uchar8   V_ucTurn, V_ucBuffer[C_EnergyPulseLen], V_ucSageFlay = 0;
	ushort16 V_usLen, V_usDataEncode;
			
	V_ucSageFlay |= C_W_SafeFlag_1;
	
	/*******************读取数据层阶梯结算用电量脉冲数********************************/
	V_ullEnergy = 0;
	V_usDataEncode = 0;
	V_usLen = C_EnergyPulseLen;
	V_ucTurn = InF_Read_Data(CY_Com_Ac_Tol_En_0, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
	
	V_ucSageFlay |= C_W_SafeFlag_2;

	/********************电能转存，不足0.01度，尾数返写数据层*************************/
	SF_Read_PulseConstant(&V_ullTemp);							/*读取电能脉冲常数ulong64格式*/
	
	V_ullTemp /= C_EnergyChangeEquivalent_Hundred;
	V_ullEnergy = V_ullEnergy % V_ullTemp;						/*不足0.01度的余数，返写数据层*/
	PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
	
	V_ucSageFlay |= C_W_SafeFlag_3;
	
	V_ucTurn = InF_Write_Data(C_Msg_EnergyMetering, CY_Com_Ac_Tol_En_0, V_ucBuffer, C_EnergyPulseLen, V_ucSageFlay);	/*不足0.01度的脉冲余数返写数据层*/
    return V_ucTurn;
}

/********************************************************************************************************
函数原型：uchar8 InF_ReadEnergy_Settlement(void)
功能描述：用于结算模块，阶梯结算用电量做结算
输入参数：无
输出参数：无
返回参数：C_OK表示读取成功，C_IDError表示数据标识码错，C_CRCError数据层CRC错，C_DataLenError表示数据长度错
          C_NoAccess表示无权限，C_SafeFlagError表示安全标志错，C_Error表示其他错误
调用位置：结算模块进行阶梯结算时调用
备    注：结算模块结算时读取结算电能调用，不用区分表型，函数内部根据不同表型进行不同的处理
          只有本地表进行的阶梯结算电能使用，远程表阶梯结算电能不需要阶梯结算
*******************************************************************************************************/
uchar8 InF_ReadEnergy_Settlement(void)
{
	uchar8 V_ucReturn;
	
	if( C_Meter_Type == C_L_SmartMeter )	/*本地费控表*/
	{
		V_ucReturn = SF_ReadEnergy_Settlement_L( );
        SF_UpdateCurrentPrice();  			/*本地表结算后重新判断当前阶梯、费率、当前电价数据*/
	}
	else									/*智能表或者远程费控电能表，不需要阶梯结算*/
	{
		V_ucReturn = C_NoAccess;
	}
	return V_ucReturn;
}

/********************************************************************************************************************
函数原型：uchar8 InF_MoneyToPurchase(ulong32 V_ulBuyMoney, uchar8 V_ucPurchaseFlag, uchar8 V_ucSafeFlag)
功能描述：卡充值、远程充值、钱包初始化处理接口函数，
		  用于购电前后剩余金额与报警、透支门限、合闸允许金额关系判断，并将购电后剩余金额、透支金额反写数据层
输入参数：V_ulBuyMoney为充值金额,数据是单位为分的hex形式；
		  V_ucPurchaseFlag,购电标志：C_Money_Purchase 充值；C_Money_Init 钱包初始化；
		  V_ucSafeFlag:为安全标志 
输出参数：无
返回参数：C_OK表示读取成功，C_IDError表示数据标识码错，C_CRCError数据层CRC错，C_DataLenError表示数据长度错
          C_NoAccess表示无权限，C_SafeFlagError表示安全标志错，C_Error表示其他错误
调用位置：通信、卡处理模块充值、钱包初始化时调用	
备    注：
********************************************************************************************************************/
uchar8 InF_MoneyToPurchase(ulong32 V_ulBuyMoney, uchar8 V_ucPurchaseFlag, uchar8 V_ucSafeFlag)
{
	ulong64 V_ullRemainingMoney, V_ullRemainingMoney_L, V_ullOverdraftMoney, V_ullOverdraftMoney_L, V_ullBuyMoney, V_ullRellyOnThreshold;
	ulong32 V_ulTemp;
	uchar8  V_ucTurn, V_ucBuffer[6];
	ulong64 V_ullOverDraftThresdHold;
	ushort16 V_usLen, V_usDataEncode;

	SF_SetMoneyToPurchaseFlag( C_MoneyToPurchase );	/*首先将购电标志置1*/
	
	/***********************购电金额的处理********************************/
	V_ullBuyMoney = V_ulBuyMoney;
	V_ullBuyMoney *= C_MoneyChangeEquivalent;			/*转换为与数据层相同格式,0.0001分的hex格式*/
	
	/******************读取数据层剩余金额、透支金额***********************/
	V_ucTurn = SF_Get_RMoney_DMoney(&V_ullRemainingMoney, &V_ullOverdraftMoney); 
	if(V_ucTurn != C_OK)
	{
		return V_ucTurn;
	}
	
	/******************计算购电后的剩余金额、透支金额**********************************/
	if( V_ullRemainingMoney > 0 )
	{
		V_ullRemainingMoney_L = V_ullRemainingMoney + V_ullBuyMoney;			/*剩余金额等于原来剩余金额+购电金额*/
		V_ullOverdraftMoney_L = 0;												/*透支金额等于0*/
	}
	else	/*剩余金额为0*/
	{
		if(V_ullOverdraftMoney > V_ullBuyMoney)									/*透支金额大于购电金额*/
		{
			V_ullOverdraftMoney_L = V_ullOverdraftMoney - V_ullBuyMoney;
			V_ullRemainingMoney_L = 0;
		}
		else
		{
			V_ullRemainingMoney_L = V_ullBuyMoney - V_ullOverdraftMoney;
			V_ullOverdraftMoney_L = 0;
		}
	}
	
	/*以上，输出V_ullRemainingMoney_L(充值后的剩余金额)，V_ullOverdraftMoney_L（充值后的透支金额）*/
	/***********************报警、预跳闸报警、透支、立即拉闸状态判断*******************************/
	SF_JudgeWarningStatus(V_ullRemainingMoney, V_ullRemainingMoney_L, V_ullOverdraftMoney, V_ullOverdraftMoney_L, C_RenewDerict);

	/*****************************发送购电成功标志给继电器模块*************************************/
	V_ucBuffer[0] = Pt_RelayStateFlag;
	V_ucBuffer[1] = C_PurchaseOK;
	SF_SendMessege(C_Msg_Deal_RelayStatus, V_ucBuffer, ( Pt_RelayStateFlag_Len + 1 ) );	/*发送购电成功消息*/

	/******************读取合闸允许金额限值并转换为与数据层存储格式相同数据************************/
	if( V_ucPurchaseFlag == C_Money_Purchase )
	{
		V_usDataEncode = 0;
		V_usLen = CLClose_Relay_Money;
		V_ucTurn = InF_Read_Data(CClose_Relay_Money, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucTurn != C_OK )		/*数据层读取参数不正确默认设置为0*/
		{
			memset(V_ucBuffer, 0x00, CLClose_Relay_Money);
		}
		PF_BufferXToUlong32(V_ucBuffer, &V_ulTemp, CLClose_Relay_Money);
		V_ullRellyOnThreshold = V_ulTemp;
		V_ullRellyOnThreshold *= C_MoneyChangeEquivalent;
		
		/******************判断是否需要发合闸允许消息***************************/
		if(V_ullRemainingMoney_L > V_ullRellyOnThreshold)	/*购电后剩余金额大于合闸允许金额，则发送合闸允许消息给继电器模块*/
		{
			V_ucBuffer[0] = Pt_RelayStateFlag;
			V_ucBuffer[1] = C_Relay_Close_Direct;
			SF_SendMessege(C_Msg_Deal_RelayStatus, V_ucBuffer, (Pt_RelayStateFlag_Len + 1) );		/*发送合闸允许消息*/
		}
	}
	else if( V_ucPurchaseFlag == C_Money_Init )
	{
		/*****************透支金额门限,单位0.01元的BCD格式，需要转会为0.01元的hex格式******************/
		V_usDataEncode = 0;
		V_usLen = CLOverDraft_Money;
		if( InF_Read_Data(COverDraft_Money, V_ucBuffer, &V_usLen, &V_usDataEncode ) != C_OK )			/*数据层读取参数不正确默认设置为0*/
		{
			memset(V_ucBuffer, 0x00, CLOverDraft_Money);
		}
		PF_BufferXToUlong32(V_ucBuffer, &V_ulTemp, CLOverDraft_Money);
		V_ullOverDraftThresdHold = V_ulTemp;
		
		/******************判断是否需要发立即合闸消息***************************/
		if ( ( V_ullOverDraftThresdHold != 0 )								/*透支门限不是0*/
		  || ( ( V_ullRemainingMoney_L / C_MoneyChangeEquivalent ) > 0 ) )	/*剩余金额大于0*/
		{
			V_ucBuffer[0] = Pt_RelayStateFlag;
			V_ucBuffer[1] = C_Relay_Close_Direct_Init;
			SF_SendMessege(C_Msg_Deal_RelayStatus, V_ucBuffer, ( Pt_RelayStateFlag_Len + 1 ) );		/*发送立即合闸消息*/
		}

	}
	else
	{
		return C_Error;
	}
	/***********************将剩余金额、透支金额返写数据层**********************************/
	PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullRemainingMoney_L, C_EnergyPulseLen);	 /*剩余金额*/
	V_ucTurn = InF_Write_Data(C_Msg_EnergyMetering,CChargeBal_Hex_Full, V_ucBuffer, CLChargeBal_Hex_Full, V_ucSafeFlag);
	if(V_ucTurn != C_OK)
	{
		return V_ucTurn;
	}

	PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullOverdraftMoney_L, C_EnergyPulseLen);	 /*透支金额*/
	V_ucTurn = InF_Write_Data(C_Msg_EnergyMetering, COverDraft_Hex_Full, V_ucBuffer, CLOverDraft_Hex_Full, V_ucSafeFlag);
	if(V_ucTurn != C_OK)
	{
		return V_ucTurn;
	}

	/***********************将累计购电金额写数据层**********************************/
	V_usDataEncode = 0;
	V_usLen = CLBuyCurr_TMoney;
	V_ucTurn = InF_Read_Data( CBuyCurr_TMoney, V_ucBuffer, &V_usLen, &V_usDataEncode );			/*累计购电金额*/
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
	PF_BufferXToUlong32(V_ucBuffer, &V_ulTemp, CLBuyCurr_TMoney);
	
	if( V_ucPurchaseFlag == C_Money_Init )	/*钱包初始化累计购电金额为0*/
	{
		V_ulTemp =  0;
	}
	
	V_ulTemp += V_ulBuyMoney;
	
	PF_Ulong32ToBufferX(V_ucBuffer, &V_ulTemp, CLBuyCurr_TMoney);
	V_ucTurn = InF_Write_Data(C_Msg_EnergyMetering, CBuyCurr_TMoney, V_ucBuffer, CLBuyCurr_TMoney, V_ucSafeFlag);
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
    return C_OK;
}

/*******************************************************************************
函数原型：uchar8 SF_Judge_CurrentStep_Type(uchar8 *pV_ucBuffer)
功能描述：判断当前所处的阶梯状态是否有效	
输入参数：pV_ucBuffer指向第一个年阶梯参数首地址   
输出参数：无
返回参数：C_ValidStep有效阶梯，C_InValidStep无效阶梯
调用位置：电能处理消息调用，有0.01度进位时调用
备    注：阶梯结算日（月日时）中月在低字节，时在高字节
*******************************************************************************/
uchar8 SF_Judge_CurrentStep_Type(uchar8 *pV_ucBuffer)
{
	uchar8 V_uci;
	uchar8 V_ucBuffer[C_StepSettlementLen];

	for( V_uci = 0; V_uci < C_StepSettlementNum; V_uci++)
	{
		PF_OneDataReversed ( &pV_ucBuffer[V_uci * C_StepSettlementLen], V_ucBuffer, C_StepSettlementLen );
		if( PF_DataTimeActive_698( V_ucBuffer, C_DT_Start_hh, C_StepSettlementLen ) == C_OK)	/*循环判断4个结算日是否有效，只要有1个有效就执行年阶梯*/
		{
			return C_ValidStep;
		}
	}
	
	/*如果第一阶梯结算日中仅日、时有效，即月为99或FF，则以此每月该日时执行阶梯结算*/
	if( ( pV_ucBuffer[C_FirstStepSettle_MonthOffset] == 0x63 )	
	 || ( pV_ucBuffer[C_FirstStepSettle_MonthOffset] == 0xFF ) )
	{
		PF_OneDataReversed ( &pV_ucBuffer[C_FirstStepSettle_DayOffset], V_ucBuffer, ( C_StepSettlementLen - 1 ) );
		if( PF_DataTimeActive_698(V_ucBuffer, C_DT_Start_hh, 2) == C_OK )		/*循环判断4个结算日是否有效，只要有1个有效就执行月阶梯*/
		{
			return C_ValidStep;
		}
	}
    return C_InValidStep;
}

/********************************************************************************************************************************
函数原型：void SF_Judge_CurrentStep(ulong32 V_ulEnergy_F, ulong32 *pV_ulEnergyPrice, uchar8 *pV_ucStepPara, uchar8 V_ucCurStepType)
功能描述：判断当前所处的阶梯号，阶梯号改变后计算当前阶梯电价返写数据层
输入参数：V_ulEnergy_F，当前电能；
          pV_ulEnergyPrice，当前阶梯电价存放地址；
          pV_ucStepPara，阶梯表参数地址；
          V_ucCurStepType：C_ValidStep 有效阶梯；C_InValidStep，无效阶梯；
输出参数：pV_ulEnergyPrice，返回当前阶梯电价；
返回参数：无
调用位置：调度500ms定时器触发,有电能处理模块调用
备    注：V_ulEnergy_F = V_ulEnergy时，用于判断当前电价、阶梯电价，并返写数据层，该数据存放RAM，实时刷新 
********************************************************************************************************************************/
void SF_Judge_CurrentStep(ulong32 V_ulEnergy_F, ulong32 *pV_ulEnergyPrice, uchar8 *pV_ucStepPara, uchar8 V_ucCurStepType)
{
	ulong32  V_ulStepPara;
	ulong32  V_ulStepPrice;
	uchar8   V_ucBuffer[20], V_uci, V_ucLastStep, V_ucStepNum;
	ushort16 V_usLen, V_usDataEncode;
	
	memset(&V_ucBuffer[0], 0xFF, 20);
	
	/******************阶梯参数*******************/
	if ( ( PF_Is_Buf_AllFixedData(pV_ucStepPara, 0x00, C_MaxStepEnergyLen) == C_OK )	/* 当前阶梯无效,全为0，这里不考虑无效数据的情况 */
	  || ( V_ucCurStepType == C_InValidStep ) )											/* 这里是阶梯表参数无效的情况 */
	{
        V_ucStepNum = 0;	/*阶梯号清零*/
		InF_Write_Data(C_Msg_EnergyMetering, CCurr_Step_No, &V_ucStepNum, CLCurr_Step_No, C_W_SafeFlag);
		
		V_ucBuffer[0] = Pt_DisplayStatus;
		V_ucBuffer[1] = C_LSign | C_NotDisplay;
		V_ucBuffer[2] = 0xFF;
		V_ucBuffer[3] = 0xFF;
		V_uci = Pt_DisplayStatus_Len + 1;

		SF_SendMessege(C_Msg_Display, V_ucBuffer, V_uci);	/*发送当前阶梯号消息给显示*/
		
		/*********阶梯电价清零*********/
		memset(&V_ucBuffer[0], 0x00, 4);
	}
	else
	{
		V_ucLastStep = 0;
		V_usDataEncode = 0;
		V_usLen  = CLStep_Num;
		if( InF_Read_Data(CStep_Num, &V_ucBuffer[0], &V_usLen, &V_usDataEncode) == C_OK )
		{
			if( V_ucBuffer[0] > C_MaxStepNum )
			{
				V_ucBuffer[0] = C_MaxStepNum;
			}
		}
		else
		{
			V_ucBuffer[0] = C_MaxStepNum;
		}
		
		for( V_uci = 0; V_uci < V_ucBuffer[0]; V_uci++)
		{
			PF_BufferXToUlong32( &pV_ucStepPara[V_uci * CLCurr_Ladder_Price], &V_ulStepPara, CLCurr_Ladder_Price );
			if( V_ulEnergy_F >= V_ulStepPara )					    /* 说明电能累加前就运行在该阶梯 */
			{
				V_ucLastStep = V_uci + 1;
			}
			else
			{
				break;
			}
			
			/************ 判断下一个阶梯值是否大于当前判断的阶梯值，不大于则直接退出 **************/
			if( PF_Campare_Data( &pV_ucStepPara[(V_uci + 1) * CLCurr_Ladder_Price ], &pV_ucStepPara[V_uci * CLCurr_Ladder_Price], CLCurr_Ladder_Price) != C_GreaterThan )
			{
				break;
			}
		}
		
		V_ucStepNum = V_ucLastStep + 1;						/* 和实际需要显示的阶梯号，差1 */
        InF_Write_Data(C_Msg_EnergyMetering, CCurr_Step_No, &V_ucStepNum, CLCurr_Step_No, C_W_SafeFlag);
		
		V_ucBuffer[0] = Pt_DisplayStatus;
		V_ucBuffer[1] = C_LSign | C_AlwaysDisplay;
		V_ucBuffer[2] = 0xFF;
		V_ucBuffer[3] = 0xFF;
		V_uci = Pt_DisplayStatus_Len + 1;
		SF_SendMessege(C_Msg_Display, V_ucBuffer, V_uci); 		/*发送当前阶梯号消息给显示*/
		
		/********************将当前阶梯电价返写数据层********************************/
		PF_CopyDataBytes( &pV_ucStepPara[C_StepChargeStartAddr + V_ucLastStep * CLCurr_Ladder_Price], V_ucBuffer, CLCurr_Ladder_Price);
	}
	
	InF_Write_Data(C_Msg_EnergyMetering, CCurr_Ladder_Price, V_ucBuffer, CLCurr_Ladder_Price, C_W_SafeFlag);
	
	PF_BufferXToUlong32( &V_ucBuffer[0], &V_ulStepPrice, CLCurr_Ladder_Price );		/* 阶梯电价返回 */
	*pV_ulEnergyPrice = V_ulStepPrice;
	
	return;
}

/****************************************************************************************************************************
函数原型：void SF_GetWarningPara(ulong64 *pV_ullWarningMoney1, ulong64 *pV_ullWarningMoney2, ulong64 *pV_ullOverDraftThresdHold)
功能描述：获取报警金额1、报警金额2、透支门限，并将参数转换为与数据层金额相同的格式，即0.0001分的格式
输入参数：pV_ullWarningMoney1，转换后报警金额1存放地址；
          pV_ullWarningMoney2，转换后报警金额2存放地址；
		  pV_ullOverDraftThresdHold，转换后透支门限存放地址	；
输出参数：*pV_ullWarningMoney1为报警金额1，格式为单位是分的hex格式；
		  *pV_ullWarningMoney2为报警金额2，格式为单位是分的hex格式；
		  *pV_ullOverDraftThresdHold为透支门限，格式为单位是分的hex格式；
返回参数：无	
调用位置：本地表判断当前报警状态及拉合闸状态时调用：上电初始化、购电、退费、电费扣减后调用	
备    注：
****************************************************************************************************************************/
void SF_GetWarningPara(ulong64 *pV_ullWarningMoney1, ulong64 *pV_ullWarningMoney2, ulong64 *pV_ullOverDraftThresdHold)
{
	uchar8   V_ucBuffer[CLAlam1_Money], V_ucReturn;
	ushort16 V_usLen, V_usDataEncode;
	
	/***************** 报警金额1,单位0.01元hex格式 ********************/
	V_usDataEncode = 0;
	V_usLen = CLAlam1_Money;
	V_ucReturn = InF_Read_Data(CAlam1_Money, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucReturn != C_OK )		/* 数据层读取参数不正确默认设置为0 */
	{
		*pV_ullWarningMoney1 = 0;
	}
	else
	{
		PF_Buffer8ToUlong64(V_ucBuffer, pV_ullWarningMoney1, CLAlam1_Money);
	}
	
	/***************** 报警金额2,单位0.01元hex格式 ********************/
	V_usDataEncode = 0;
	V_usLen = CLAlam2_Money;
	V_ucReturn = InF_Read_Data(CAlam2_Money, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucReturn != C_OK )		/* 数据层读取参数不正确默认设置为0 */
	{
		*pV_ullWarningMoney2 = 0;
	}
	else
	{
		PF_Buffer8ToUlong64(V_ucBuffer, pV_ullWarningMoney2, CLAlam2_Money);
	}
	
	/***************** 透支金额门限,单位0.01元hex格式 *****************/
	V_usDataEncode = 0;
	V_usLen = CLOverDraft_Money;
	V_ucReturn = InF_Read_Data(COverDraft_Money, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucReturn != C_OK )		/* 数据层读取参数不正确默认设置为0 */
	{
		*pV_ullOverDraftThresdHold = 0;
	}
	else
	{
		PF_Buffer8ToUlong64(V_ucBuffer, pV_ullOverDraftThresdHold, CLOverDraft_Money);
	}
}

/*******************************************************************************
函数原型：void SF_JudgeWarningStatus(ulong64 V_ullRemainMoney, ulong64 V_ullRemainMoney_New, ulong64 V_ullOverDraftMoney, ulong64 V_ullOverDraftMoney_New, uchar8 V_ucRenewFlay)
功能描述：判断是否需要报警、预跳闸报警、立即拉闸及当前透支状态，并发消息给相应模块
输入参数：V_ullRemainMoney，扣费前的剩余金额；
         V_ullRemainMoney_New，扣费后的剩余金额；
         V_ullOverDraftMoney，扣费前的透支金额；						
		 V_ullOverDraftMoney_New，扣费后的透支金额；						
		 V_ucRenewFlay，是否直接更新标志，C_RenewDerict则直接更新，C_RenewRederict则判断状态变化更新；	
输出参数：无
返回参数：无
调用位置：本地表判断当前报警状态及拉闸状态时调用：上电初始化、购电、退费、电费扣减后调用
备    注：1）注意，购电时，仅判断报警1、2，是否发合闸信息在调用本函数的地方实现。
          2）其中金额的单位为0.000001元的hex格式
*******************************************************************************/
void SF_JudgeWarningStatus(ulong64 V_ullRemainMoney, ulong64 V_ullRemainMoney_New, ulong64 V_ullOverDraftMoney, ulong64 V_ullOverDraftMoney_New, uchar8 V_ucRenewFlay)
{
	ulong64 V_ullWarningMoney1, V_ullWarningMoney2, V_ullOverDraftThresdHold;
    ulong64 V_ullRemainMoney_Cent, V_ullRemainMoney_New_Cent;   /*以分为单位的扣费前后的剩余金额*/
    ulong64 V_ullOverDraftMoney_New_Cent;  						/*以分为单位的扣费前后的透支金额*/
	uchar8  V_ucBuffer[20], V_ucWarningStaus;
	
	/* 读取数据层报警金额1、2，透支门限 */
	SF_GetWarningPara(&V_ullWarningMoney1, &V_ullWarningMoney2, &V_ullOverDraftThresdHold);
	
	/* 发报警消息标志字节，初始化为0，不发消息 */
	V_ucWarningStaus = C_NoMessage;
	
	/* 将剩余金额、透支金额转换为以分为单位的hex格式 */
    V_ullRemainMoney_Cent = V_ullRemainMoney / C_MoneyChangeEquivalent;
    V_ullRemainMoney_New_Cent = V_ullRemainMoney_New / C_MoneyChangeEquivalent;
    V_ullOverDraftMoney_New_Cent = V_ullOverDraftMoney_New / C_MoneyChangeEquivalent;
	
	/*********************************************************************************************/
	/************************* 判断是否需要报警 ***************************/
	/* 输出：V_ucWarningStaus，可能取值C_ReleaseWarning1Message，C_Warning1Message，C_NoMessage */
	
	if( V_ullWarningMoney1 != 0 )	    /* 报警金额1设置为0，不进行欠费报警 */
	{
		if( V_ucRenewFlay == C_RenewDerict )
		{
			if( V_ullRemainMoney_New_Cent <= V_ullWarningMoney1 )	/* 发送报警显示给继电器模块 */
			{
				V_ucWarningStaus = C_Warning1Message;				/* 发报警金额1报警消息 */
			}
			else
			{
				V_ucWarningStaus = C_ReleaseWarning1Message;		/* 发报警金额1解除消息 */
			}
		}
		else
		{	/*不是直接，那么仅抓原剩余金额大于报警1，现剩余金额小于等于报警1的情况*/
			if( ( V_ullRemainMoney_Cent > V_ullWarningMoney1 ) && ( V_ullRemainMoney_New_Cent <= V_ullWarningMoney1 ) )		/*发送报警显示给继电器模块*/
			{
				V_ucWarningStaus = C_Warning1Message;				/*发报警金额1报警消息*/
			}
		}
	}
	else
	{	/* 报警金额1等于0 */
		if( V_ucRenewFlay == C_RenewDerict )
		{
			if( V_ullRemainMoney_New_Cent > 0 )						/*发送报警显示给继电器模块*/
			{
				V_ucWarningStaus = C_ReleaseWarning1Message;		/*发报警金额1解除消息*/
			}
		}
	}
	
	/************************* 判断是否需要预跳闸报警 ***************************/
	/* 输出：V_ucWarningStaus，可能取值C_ReleaseWarning1Message，C_Warning1Message，C_NoMessage, C_Warning2Message */
	
	if( V_ullRemainMoney_New_Cent > V_ullWarningMoney2 )	/* 剩余金额大于报警金额2,购电标志清零 */
	{
		SF_SetMoneyToPurchaseFlag( C_NoMoneyToPurchase );
	}
	
	if( V_ullWarningMoney2 != 0 )							/* 报警金额2设置为0不进行与跳闸报警 */
	{
		if( V_ucRenewFlay == C_RenewDerict )
		{
			if( V_ullRemainMoney_New_Cent <= V_ullWarningMoney2 )			/*发送一次跳闸消息显示给继电器模块*/
			{
				if( SF_CheckMoneyToPurchaseFlag( ) != C_MoneyToPurchase )	/*没有购电标志*/
				{
					V_ucWarningStaus = C_Warning2Message;					/*发报警金额2报警消息*/
				}
				else
				{
					V_ucWarningStaus = C_Warning1Message;					/*发报警金额1报警消息*/
				}
			}
		}
		else
		{	/*不是直接，那么仅抓原剩余金额大于报警2，现剩余金额小于等于报警2的情况*/
			if( ( V_ullRemainMoney_Cent > V_ullWarningMoney2 ) && ( V_ullRemainMoney_New_Cent <= V_ullWarningMoney2 ) )	
			{
				V_ucWarningStaus = C_Warning2Message;						/*发报警金额2报警消息*/
			}
		}
	}
	
	/**************************判断剩余金额是否过零***********************************************/
	/*剩余金额等于0，那么透支门限=0，直接跳闸，否则发报警2,这里不考虑报警金额2是否为0均需要进行与跳闸报警*/
	 /*考虑透支门限和拉闸在下面判断，同时如果发报警2，下面再发拉闸，会覆盖这条命令，因此这里不判断透支门限*/
	if( V_ucRenewFlay == C_RenewDerict )
	{	/*保留这个if，是考虑上电时，如果报警2=0，剩余金额跨0消息电能已发出，但继电器模块未执行情况。*/
		if( V_ullRemainMoney_New_Cent == 0 )		/*剩余金额为0,且没有购电标志*/
		{
			if( SF_CheckMoneyToPurchaseFlag( ) != C_MoneyToPurchase )		/*没有购电标志*/
			{
				V_ucWarningStaus = C_Warning2Message;	/*发报警金额2报警消息*/
			}
			else
			{
				V_ucWarningStaus = C_Warning1Message;	/*发报警金额1报警消息*/
			}
		}
	}
	else
	{	/*报警金额2等于0，还需判沿，原剩余金额不为0，现剩余金额为0*/
		if( ( V_ullRemainMoney_Cent > 0 ) && ( V_ullRemainMoney_New_Cent == 0 ) )
		{
			V_ucWarningStaus = C_Warning3Message;		/* 发报警金额2报警消息，这里表示报警金额2报警是跨过0的，定义一个特殊的报警 */
		}
	}
	
	/*************************判断是否需要立即拉闸***************************/
	/*************************拉闸不管沿，都是直接置*************************/
	if( V_ullRemainMoney_New_Cent == 0 )
	{	/*拉闸，当前剩余金额肯定为0，透支门限可以不判断是否为0*/
		if( V_ullOverDraftMoney_New_Cent >= V_ullOverDraftThresdHold )	/*发送立即跳闸消息显示给继电器模块*/
		{
			V_ucWarningStaus = C_RelayOffMessage;
		}
	}
	
	/*****************************下面根据发消息标志发消息给继电器模块******************************/
	V_ucBuffer[0] = Pt_RelayStateFlag; 	
	switch( V_ucWarningStaus )
	{
		case C_Warning1Message:
		{
			V_ucBuffer[1] = C_Alarm;
		}break;
		case C_ReleaseWarning1Message:
		{
			V_ucBuffer[1] = C_Alarm_Release;
		}break;
		case C_Warning2Message:
		{
			V_ucBuffer[1] = C_AlarmOpenRelay;
		}break;
		case C_Warning3Message:
		{
			V_ucBuffer[10] = Pt_RelayStateFlag;				/*剩余金额跨过0，报警需要先发一个合闸允许消息*/
			V_ucBuffer[11] = C_Relay_Close_Direct;
		    SF_SendMessege(C_Msg_Deal_RelayStatus, &V_ucBuffer[10], (Pt_RelayStateFlag_Len + 1) );	/*发送报警消息给显示*/	
			V_ucBuffer[1] = C_AlarmOpenRelay;
		}break;
		case C_RelayOffMessage:
		{
			V_ucBuffer[1] = C_Relay_OpenNow;
		}break;
		default:
			break;
	}
	if(V_ucWarningStaus != C_NoMessage)
	{
		SF_SendMessege(C_Msg_Deal_RelayStatus, V_ucBuffer, (Pt_RelayStateFlag_Len + 1) );			/*发送报警消息给显示*/	
	}
	
	/*************************判断是否透支,透支则发消息给显示模块***************************/
	memset(&V_ucBuffer[0], 0xFF, 4);
	
	V_ucBuffer[0] = Pt_DisplayStatus;
	if( V_ucRenewFlay == C_RenewDerict )	/*直接更新标志，不判断状态变化，只根据当前状态进行更新标志及发消息*/
	{
		if(V_ullOverDraftMoney_New > 0)
		{		
			SF_SetOverDraft_Meter_Work_State( C_SetOverDraft, SV_ucEnergySafeFlag );
		}
		else
		{
			SF_SetOverDraft_Meter_Work_State( C_ClrOverDraft, C_W_SafeFlag );
		}
	}
	else
	{	/*不是直接，仅抓从不透支到透支的沿*/
		if( ( V_ullOverDraftMoney  == 0 ) && ( V_ullOverDraftMoney_New > 0 ) )						/*发送透支显示字符给显示模块*/
		{
			if( SF_SetOverDraft_Meter_Work_State( C_SetOverDraft, SV_ucEnergySafeFlag ) == C_OK )
            {
				Inf_WriteMeterStatus8( C_OverdraftEventNo );
            }
		}
		else if( ( ( V_ullOverDraftMoney / C_MoneyChangeEquivalent ) < V_ullOverDraftThresdHold ) && ( V_ullOverDraftMoney_New_Cent >= V_ullOverDraftThresdHold ) )		/*发送透支显示字符给显示模块*/
		{
			SF_SetOverDraft_Meter_Work_State( C_SetOverDraft, SV_ucEnergySafeFlag );
		}
	}
}

/*************************************************************************************************************************
函数原型：uchar8 SF_Chargeback(ulong64 *pV_ullEnergy_F, ulong64 *pV_ullEnergy, uchar8 *pV_ucStepPara, uchar8 V_ucCurStepType)
功能描述：阶梯电价扣费，并刷新当前阶梯
输入参数：pV_ullEnergy_F，累加前电能地址；
         pV_ullEnergy，累加后电能地址；
         pV_ucStepPara，阶梯表参数地址；
         V_ucCurStepType：C_ValidStep 有效阶梯；C_InValidStep，无效阶梯；
输出参数：无
返回参数：有无扣费标志：C_SubMoneyFlag，表示有扣费标志；C_NoSubMoneyFlag，表示无扣费标志；
调用位置：本地费控表扣费调用
备    注：
*************************************************************************************************************************/
uchar8 SF_Chargeback(ulong64 *pV_ullEnergy_F, ulong64 *pV_ullEnergy, uchar8 *pV_ucStepPara, uchar8 V_ucCurStepType)
{
	ulong64 V_ullRemainMoney, V_ullRemainMoney_New, V_ullOverDraftMoney, V_ullOverDraftMoney_New;
	ulong64 V_ullFeeDeduction;	 /* 每0.01度扣费次数=当前电价*电压互感器变比*电流互感器变比 */
	ulong32 V_ulEnergy_F, V_ulEnergy;
	ulong32 V_ulCurrentPrice;
	uchar8  V_ucBuffer[8], V_ucj, V_ucEnergyTemp;
	ulong64 V_ullTemp1, V_ullTemp2, V_ullPulseConstant;
	
	/****************** 脉冲常数 *******************/
	SF_Read_PulseConstant(&V_ullPulseConstant);			  			/* 读取电能脉冲常数 ulong64格式*/

	/******************* 判断是否需扣费 ************/
	V_ullTemp1 = (*pV_ullEnergy_F) * C_EnergyChangeEquivalent_Hundred;		/*这里不会溢出，单位0.01*/
	V_ullTemp2 = (*pV_ullEnergy) * C_EnergyChangeEquivalent_Hundred;	
	
	/*计算电能，0.01度*/
	V_ulEnergy_F = (ulong32)(V_ullTemp1 / V_ullPulseConstant);
	V_ulEnergy = (ulong32)(V_ullTemp2 / V_ullPulseConstant);
	
	if(V_ulEnergy > V_ulEnergy_F)							/*当前电能大于上次处理时电能*/
	{
		/*********读取剩余金额、透支金额，单位0.000001元*********************/
		if( SF_Get_RMoney_DMoney( &V_ullRemainMoney, &V_ullOverDraftMoney ) != C_OK )
		{
			return ( C_NoSubMoneyFlag );
		}
		
		/********读取电压电流互感器变比，不对或者为0则默认为1**********/
		V_ullFeeDeduction = SF_Get_V_I_Ratio( );
		
		/*********************** 以下进行扣费 ***************************/	
		V_ucEnergyTemp = (uchar8)(V_ulEnergy - V_ulEnergy_F);
		for( V_ucj = 0; V_ucj < V_ucEnergyTemp; V_ucj++)
		{
			/********* 首先判断扣费前电能所处的阶梯 *********/
			SF_Judge_CurrentStep( (V_ulEnergy_F + V_ucj), &V_ulCurrentPrice, pV_ucStepPara, V_ucCurStepType);
			
			/****************** 当前阶梯电价是否为0，为0则不执行阶梯，不扣费，直接返回无扣费标志 *********/
			if( V_ulCurrentPrice == 0 )
			{
				return ( C_NoSubMoneyFlag );
			}
			
			/******************首先扣除0.01度电能金额,剩余金额单位0.000001元,hex格式*******************/
			/******************当前电价单位0.0001元的hex格式，而扣费单位为0.01度，因此这里直接相减即可*/
			if( V_ullRemainMoney >= ( V_ullFeeDeduction * V_ulCurrentPrice ) )
			{
				V_ullRemainMoney_New = V_ullRemainMoney - ( V_ullFeeDeduction * V_ulCurrentPrice );
				V_ullOverDraftMoney_New = 0;
			}
			else if(V_ullRemainMoney > 0)
			{
				V_ullRemainMoney_New = 0;
				V_ullOverDraftMoney_New = ( V_ullFeeDeduction * V_ulCurrentPrice ) - V_ullRemainMoney;
			}
			else
			{
				V_ullRemainMoney_New = 0;
				V_ullOverDraftMoney_New = V_ullOverDraftMoney + ( V_ullFeeDeduction * V_ulCurrentPrice );
			}
			
			V_ullRemainMoney = V_ullRemainMoney_New;
			V_ullOverDraftMoney = V_ullOverDraftMoney_New;
		}
		
		/***********************将新的剩余金额、透支金额返写数据层******************************/
		PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullRemainMoney, CLCurr_Money);
		InF_Write_Data(C_Msg_EnergyMetering, CChargeBal_Hex_Cent, V_ucBuffer, CLCurr_Money, SV_ucEnergySafeFlag);
		
		PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullOverDraftMoney, CLCurr_Money);
		InF_Write_Data(C_Msg_EnergyMetering, COverDraft_Hex_Cent, V_ucBuffer, CLCurr_Money, SV_ucEnergySafeFlag);
		
		return ( C_SubMoneyFlag );
	}
    return  ( C_NoSubMoneyFlag );
}

/*******************************************************************************
函数原型：uchar8 SF_JudgePulseActive(Struct_Energy_Type *pStr_Energy)
功能描述：判断计量芯片读出来的脉冲数的合法性
输入参数：Str_Energy电能脉冲结构体地址
输出参数：无
返回参数：C_OK脉冲合法，C_ERR脉冲非法
调用位置：电能消息处理函数中调用
备    注：
*******************************************************************************/
uchar8 SF_JudgePulseActive(Struct_Energy_Type *pStr_Energy)
{
	uchar8 V_ucFlay;

	if( SV_ucEnergySafeFlag != ( C_W_SafeFlag_2 | C_W_SafeFlag_1 ) )
	{
		return C_SafeFlagError;
	}
	
	V_ucFlay = C_OK;
		
	/*************************脉冲合法性判断*******************************/
	if( pStr_Energy->V_usActiveEnergy_T > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usActiveEnergy_A > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usActiveEnergy_B > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usActiveEnergy_C > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usReactiveEnergy_T > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usReactiveEnergy_A > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usReactiveEnergy_B > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usReactiveEnergy_C > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	/*************************有出错的就清零，返回错误**************************************/
	if( V_ucFlay == C_Error )
	{
		pStr_Energy->V_usActiveEnergy_T = 0;
		pStr_Energy->V_usActiveEnergy_A = 0;
		pStr_Energy->V_usActiveEnergy_B = 0;
		pStr_Energy->V_usActiveEnergy_C = 0;
		pStr_Energy->V_usReactiveEnergy_T = 0;
		pStr_Energy->V_usReactiveEnergy_A = 0;
		pStr_Energy->V_usReactiveEnergy_B = 0;
		pStr_Energy->V_usReactiveEnergy_C = 0;
		return V_ucFlay;
	}
	return C_OK;
}

/*******************************************************************************
函数原型：void SF_Adjust_EnergyPulse(Struct_Energy_Type *pV_StrEnergy)
功能描述：电能脉冲数抹平
输入参数：pV_StrEnergy电能脉冲结构体地址
输出参数：无
返回参数：无
调用位置：电能消息处理函数中调用
备    注：
*******************************************************************************/
void SF_Adjust_EnergyPulse(Struct_Energy_Type *pV_StrEnergy)
{
	ulong64  V_ullForward_T, V_ullReverse_T, V_ullForward_ABC, V_ullReverse_ABC, V_ullTemp;
	ushort16 *pV_usTemp;
	uchar8   V_ucPhaseFlay;
	
	if( SV_ucEnergySafeFlag != ( C_W_SafeFlag_2 | C_W_SafeFlag_1 ) )
	{
		return;
	}
	
	if ( ( pV_StrEnergy->V_usActiveEnergy_A == 0 )
	  && ( pV_StrEnergy->V_usActiveEnergy_B == 0 )
	  && ( pV_StrEnergy->V_usActiveEnergy_C == 0 ) )		/*有功分相脉冲读出来均为0则不进行有功脉冲调整*/
	{
		goto DealReverseEnergyPulse;
	}

	/**********************读取正向有功总脉冲数************************/	
	V_ullForward_T = 0;
	if ( SF_ReadTotalEnergy(CPos_Ac_T1_PreEn_0, &V_ullForward_T, C_MaxRatesNum, C_GetNextRatesEnergy ) != C_OK )
	{
		return;		/*读数据出现不成功，则直接退出，不进行脉冲调整*/
	}
	
	/**********************读取反向有功总脉冲数************************/	
	V_ullReverse_T = 0;
	if ( SF_ReadTotalEnergy(CRev_Ac_T1_PreEn_0, &V_ullReverse_T, C_MaxRatesNum, C_GetNextRatesEnergy ) != C_OK )
	{
		return;		/*读数据出现不成功，则直接退出，不进行脉冲调整*/
	}

	
	/**********************读取分相正向有功总脉冲数************************/
	V_ullForward_ABC = 0;
	if ( SF_ReadTotalEnergy(CPosA_Ac_PreEn_0, &V_ullForward_ABC, 3, C_GetNextPhaseEnergy ) != C_OK )
	{
		return;		/*读数据出现不成功，则直接退出，不进行脉冲调整*/
	}

	/**********************读取分相反向有功总脉冲数************************/
	V_ullReverse_ABC = 0;
	if ( SF_ReadTotalEnergy(CRevA_Ac_PreEn_0, &V_ullReverse_ABC, 3, C_GetNextPhaseEnergy ) != C_OK )
	{
		return;		/*读数据出现不成功，则直接退出，不进行脉冲调整*/
	}

	
/*************************将计量芯片读出的当前脉冲累加上去*****************************
输入:	                    														  
V_ullForward_T/V_ullReverse_T		总的正反向脉冲数                                  
V_ullForward_ABC/V_ullReverse_ABC	ABC三相正反向脉冲数                               
**************************************************************************************/
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ActiveDeriction_T ) == 0x00 )
	{
		V_ullForward_T += pV_StrEnergy->V_usActiveEnergy_T;		/*正向有功总脉冲数加上计量芯片读出来的总有功脉冲数*/
	}
	else
	{
		V_ullReverse_T += pV_StrEnergy->V_usActiveEnergy_T;		/*reverse total pulse add reverse pulse from meterIC*/
	}
	
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ActiveDeriction_A ) == 0x00 )
	{
		V_ullForward_ABC += pV_StrEnergy->V_usActiveEnergy_A;	/*正向有功总脉冲数加上计量芯片读出来的总有功脉冲数*/
	}
	else
	{
		V_ullReverse_ABC += pV_StrEnergy->V_usActiveEnergy_A;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ActiveDeriction_B ) == 0x00 )
	{
		V_ullForward_ABC += pV_StrEnergy->V_usActiveEnergy_B;	/*正向有功总脉冲数加上计量芯片读出来的总有功脉冲数*/
	}
	else
	{
		V_ullReverse_ABC += pV_StrEnergy->V_usActiveEnergy_B;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ActiveDeriction_C ) == 0x00 )
	{
		V_ullForward_ABC += pV_StrEnergy->V_usActiveEnergy_C;	/*正向有功总脉冲数加上计量芯片读出来的总有功脉冲数*/
	}
	else
	{
		V_ullReverse_ABC += pV_StrEnergy->V_usActiveEnergy_C;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
/****************************计算总和分相脉冲代数和****************************
输入:           															  
V_ullForward_T/V_ullReverse_T		总的正反向脉冲数                          
V_ullForward_ABC/V_ullReverse_ABC	ABC三相正反向脉冲数                       
*****************************************************************************/
	if(V_ullForward_T >= V_ullReverse_T)			/*计算合相正反向脉冲数差值*/
	{
		V_ullForward_T -= V_ullReverse_T;
		V_ullReverse_T = 0;
	}
	else
	{
		V_ullReverse_T -= V_ullForward_T;
		V_ullForward_T = 0;
	}
	
	if(V_ullForward_ABC >= V_ullReverse_ABC)		/*计算分相正反向脉冲数差值*/
	{
		V_ullForward_ABC -= V_ullReverse_ABC;
		V_ullReverse_ABC = 0;
	}
	else
	{
		V_ullReverse_ABC -= V_ullForward_ABC;
		V_ullForward_ABC = 0;
	}
	
/****************************计算总分代数和的差值*********************************
功能描述，本段代码根据上面计算出总、分代数和脉冲数，完成:						
1、计算总、分代数和脉冲数差值。该差值到下一步供判断是否满3个脉冲补偿阀值使用。  
2、得出分相脉冲补偿方法(详细可参见设计思路-电能抹平原则)。                      
	即补偿方法有4个:（实际只有2种可能，正+1（负-1）；正-1（负+1））             
		a、当前分相脉冲方向为正，脉冲数+1                                       
		b、当前分相脉冲方向为正，脉冲数-1                                       
		c、当前分相脉冲方向为负，脉冲数+1                                       
		d、当前分相脉冲方向为负，脉冲数-1                                       
输入:(以下寄存器，既表示了代数和脉冲数，又表示代数和方向)                       
V_ullForward_T/V_ullReverse_T		总的正反向脉冲数代数和                      
V_ullForward_ABC/V_ullReverse_ABC	ABC三相正反向脉冲数代数和                   
注意，以上代数和为正，则放置在正向脉冲数中,反向脉冲数为0                        
      代数和为负，则放置在反向脉冲数中，正向脉冲数为0                           
输出:由于本段段码不判断分相方向，因此根据电能抹平原则计算出差值:                
V_ullForward_T：合相和分相正反向脉冲代数和差值，表示正+1（负-1）                
	即:总分代数和同正，总>分;同负，总<分;总为正，分为负                         
V_ullForward_ABC:合相和分相正反向脉冲代数和差值，表示正-1（负+1））             
	即:总分代数和同正，总<分;同负，总>分;总为负，分为正                         
*********************************************************************************/
	if( ( V_ullForward_T != 0 ) && ( V_ullForward_ABC != 0 ) )			/*总脉冲数据均为正向*/
	{
		if(V_ullForward_T >= V_ullForward_ABC)
		{
			V_ullForward_T -= V_ullForward_ABC;
			V_ullForward_ABC = 0;
		}
		else
		{
			V_ullForward_ABC -= V_ullForward_T;
			V_ullForward_T = 0;
		}
	}
	else if( ( V_ullReverse_T != 0 ) && ( V_ullReverse_ABC != 0 ) )		/*总脉冲数据均为反向*/
	{
		if(V_ullReverse_T > V_ullReverse_ABC)
		{
			V_ullForward_ABC = V_ullReverse_T - V_ullReverse_ABC;
		}
		else
		{
			V_ullForward_T = V_ullReverse_ABC - V_ullReverse_T;
		}
	}
	else	/*差值合相与分相方向不同*/
	{
		if( ( V_ullForward_T > 0 ) || ( V_ullReverse_ABC > 0 ) )	/*这两中情况均为正向差值大于分相脉冲差值的情况*/
		{
			V_ullForward_T += V_ullReverse_ABC;
		}
		else
		{
			V_ullForward_ABC += V_ullReverse_T;
		}
	}
/**********************确定在哪一相上作补偿********************************
功能：将本次读计量芯片中最大脉冲数挑选出来							 
输入:当前读出的脉冲结构体 pV_StrEnergy                                
输出:                                                                
pV_usTemp			:待补偿的相别原始脉冲数的指针                    
V_ucPhaseFlay	:待补偿的相别指示，后续判断该相是正是负使用          
	2、4、8代表A、B、C,这里搞错了!应该是1、2、4采用宏!               
注意：1）这里默认在A相操作；2）由于前面全0直接跳走，                 
	因此到这里是不会出现*pV_usTemp=0情况                              
*************************************************************************/
	pV_usTemp = &(pV_StrEnergy->V_usActiveEnergy_A);
	V_ucPhaseFlay = C_ActiveDeriction_A;
	if( pV_StrEnergy->V_usActiveEnergy_A < pV_StrEnergy->V_usActiveEnergy_B )
	{
		pV_usTemp = &(pV_StrEnergy->V_usActiveEnergy_B);
		V_ucPhaseFlay = C_ActiveDeriction_B;
		if(pV_StrEnergy->V_usActiveEnergy_B < pV_StrEnergy->V_usActiveEnergy_C)
		{
			pV_usTemp = &(pV_StrEnergy->V_usActiveEnergy_C);
			V_ucPhaseFlay = C_ActiveDeriction_C;
		}
	}
	else
	{
		if(pV_StrEnergy->V_usActiveEnergy_A < pV_StrEnergy->V_usActiveEnergy_C)
		{
			pV_usTemp = &(pV_StrEnergy->V_usActiveEnergy_C);
			V_ucPhaseFlay = C_ActiveDeriction_C;
		}
	}
	
/********************补偿*****************************************************
输入：pV_usTemp 待补偿脉冲数指针								  
     V_ucPhaseFlay 待补偿相别指示。                              
V_ullForward_T：合相和分相正反向脉冲代数和差值，表示正+1（负-1）          
	即:总分代数和同正，总>分;同负，总<分;总为正，分为负                   
V_ullForward_ABC:合相和分相正反向脉冲代数和差值，表示正-1（负+1））       
	即:总分代数和同正，总<分;同负，总>分;总为负，分为正                   
*****************************************************************************/
	if( V_ullForward_T >= 3 )				 /*总脉冲数比分相脉冲数之和多于3个*/
	{
		/**********判断分相是正向脉冲还是反向脉冲**********/
		if( ( pV_StrEnergy->V_ucPowerDeriction & V_ucPhaseFlay ) == V_ucPhaseFlay )
		{
			*pV_usTemp -= 1;
		}
		else
		{
			*pV_usTemp += 1;
		}
	}
	else if( V_ullForward_ABC >= 3 )
	{
		/**********判断分相是正向脉冲还是反向脉冲**********/
		if( ( pV_StrEnergy->V_ucPowerDeriction & V_ucPhaseFlay) == V_ucPhaseFlay )
		{
			*pV_usTemp += 1;
		}
		else
		{
			*pV_usTemp -= 1;
		}
	}
/***********************************以下为无功脉冲调整*********************************************/
DealReverseEnergyPulse:
	if ( ( pV_StrEnergy->V_usReactiveEnergy_A == 0 )
	  && ( pV_StrEnergy->V_usReactiveEnergy_B == 0 )
	  && ( pV_StrEnergy->V_usReactiveEnergy_C == 0 ) )	   /*无功分相脉冲均为0就不进行无功脉冲调整*/
	{
		return;
	}
	
	/**********************读取正向无功总脉冲数************************/
	V_ullForward_T = 0;		
	if ( SF_ReadTotalEnergy(CQua1_Re_T1_PreEn_0, &V_ullForward_T, C_MaxRatesNum, C_GetNextRatesEnergy ) != C_OK )
	{
		return;		/*读数据出现不成功，则直接退出，不进行脉冲调整*/
	}
	
	V_ullTemp = 0;
	if ( SF_ReadTotalEnergy(CQua2_Re_T1_PreEn_0, &V_ullTemp, C_MaxRatesNum, C_GetNextRatesEnergy ) != C_OK )
	{
		return;		/*读数据出现不成功，则直接退出，不进行脉冲调整*/
	}
	V_ullForward_T += V_ullTemp;
	
	/**********************读取反向无功总脉冲数************************/
	V_ullReverse_T = 0;
	if ( SF_ReadTotalEnergy(CQua4_Re_T1_PreEn_0, &V_ullReverse_T, C_MaxRatesNum, C_GetNextRatesEnergy ) != C_OK )
	{
		return;		/*读数据出现不成功，则直接退出，不进行脉冲调整*/
	}
	
	V_ullTemp = 0;
	if ( SF_ReadTotalEnergy(CQua3_Re_T1_PreEn_0, &V_ullTemp, C_MaxRatesNum, C_GetNextRatesEnergy ) != C_OK )
	{
		return;		/*读数据出现不成功，则直接退出，不进行脉冲调整*/
	}
	
	V_ullReverse_T += V_ullTemp;
	/**********************读取分相正向无功总脉冲数************************/
	V_ullForward_ABC = 0;
	if ( SF_ReadTotalEnergy(CQua1A_Re_PreEn_0, &V_ullForward_ABC, 3, C_GetNextPhaseEnergy ) != C_OK )
	{
		return;		/*读数据出现不成功，则直接退出，不进行脉冲调整*/
	}
	
	V_ullTemp = 0;
	if ( SF_ReadTotalEnergy(CQua2A_Re_PreEn_0, &V_ullTemp, 3, C_GetNextPhaseEnergy ) != C_OK )
	{
		return;		/*读数据出现不成功，则直接退出，不进行脉冲调整*/
	}
	
	V_ullForward_ABC += V_ullTemp;
		
	/**********************读取分相反向无功总脉冲数************************/
	V_ullReverse_ABC = 0;
	if ( SF_ReadTotalEnergy(CQua4A_Re_PreEn_0, &V_ullReverse_ABC, 3, C_GetNextPhaseEnergy ) != C_OK )
	{
		return;		/*读数据出现不成功，则直接退出，不进行脉冲调整*/
	}
	
	V_ullTemp = 0;
	if ( SF_ReadTotalEnergy(CQua3A_Re_PreEn_0, &V_ullTemp, 3, C_GetNextPhaseEnergy ) != C_OK )
	{
		return;		/*读数据出现不成功，则直接退出，不进行脉冲调整*/
	}
	
	V_ullReverse_ABC += V_ullTemp;
	
/*************************将计量芯片读出的当前脉冲累加上去******************************
输入:																				  
V_ullForward_T/V_ullReverse_T		总的正反向脉冲数        						  
V_ullForward_ABC/V_ullReverse_ABC	ABC三相正反向脉冲数     						  
*************************************************************************************/
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ReactiveEDeriction_T ) == 0x00 )
	{
		V_ullForward_T += pV_StrEnergy->V_usReactiveEnergy_T;	/*正向无功总脉冲数加上计量芯片读出来的总无功脉冲数*/
	}
	else
	{
		V_ullReverse_T += pV_StrEnergy->V_usReactiveEnergy_T;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ReactiveEDeriction_A ) == 0x00 )
	{
		V_ullForward_ABC += pV_StrEnergy->V_usReactiveEnergy_A;	/*正向无功总脉冲数加上计量芯片读出来的总无功脉冲数*/
	}
	else
	{
		V_ullReverse_ABC += pV_StrEnergy->V_usReactiveEnergy_A;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ReactiveEDeriction_B ) == 0x00 )
	{
		V_ullForward_ABC += pV_StrEnergy->V_usReactiveEnergy_B;	/*正向无功总脉冲数加上计量芯片读出来的总无功脉冲数*/
	}
	else
	{
		V_ullReverse_ABC += pV_StrEnergy->V_usReactiveEnergy_B;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ReactiveEDeriction_C ) == 0x00 )
	{
		V_ullForward_ABC += pV_StrEnergy->V_usReactiveEnergy_C;	/*正向无功总脉冲数加上计量芯片读出来的总无功脉冲数*/
	}
	else
	{
		V_ullReverse_ABC += pV_StrEnergy->V_usReactiveEnergy_C;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
/****************************计算总和分相脉冲代数和********************************
输入:																			 
V_ullForward_T/V_ullReverse_T		总的正反向脉冲数                             
V_ullForward_ABC/V_ullReverse_ABC	ABC三相正反向脉冲数                          
*********************************************************************************/
	if( V_ullForward_T >= V_ullReverse_T )		/*计算合相正反向脉冲数差值*/
	{
		V_ullForward_T -= V_ullReverse_T;
		V_ullReverse_T = 0;
	}
	else
	{
		V_ullReverse_T -= V_ullForward_T;
		V_ullForward_T = 0;
	}
	
	if( V_ullForward_ABC >= V_ullReverse_ABC )	/*计算分相正反向脉冲数差值*/
	{
		V_ullForward_ABC -= V_ullReverse_ABC;
		V_ullReverse_ABC = 0;
	}
	else
	{
		V_ullReverse_ABC -= V_ullForward_ABC;
		V_ullForward_ABC = 0;
	}
	
/****************************计算总分代数和的差值***********************************
功能描述，本段代码根据上面计算出总、分代数和脉冲数，完成:						
1、计算总、分代数和脉冲数差值。该差值到下一步供判断是否满3个脉冲补偿阀值使用。  
2、得出分相脉冲补偿方法(详细可参见设计思路-电能抹平原则)。                      
	即补偿方法有4个:（实际只有2种可能，正+1（负-1）；正-1（负+1））             
		a、当前分相脉冲方向为正，脉冲数+1                                       
		b、当前分相脉冲方向为正，脉冲数-1                                       
		c、当前分相脉冲方向为负，脉冲数+1                                       
		d、当前分相脉冲方向为负，脉冲数-1                                       
输入:(以下寄存器，既表示了代数和脉冲数，又表示代数和方向)                       
V_ullForward_T/V_ullReverse_T		总的正反向脉冲数代数和                      
V_ullForward_ABC/V_ullReverse_ABC	ABC三相正反向脉冲数代数和                   
注意，以上代数和为正，则放置在正向脉冲数中,反向脉冲数为0                        
      代数和为负，则放置在反向脉冲数中，正向脉冲数为0                           
输出:由于本段段码不判断分相方向，因此根据电能抹平原则计算出差值:                
V_ullForward_T：合相和分相正反向脉冲代数和差值，表示正+1（负-1）                
		即:总分代数和同正，总>分;同负，总<分;总为正，分为负                     
V_ullForward_ABC:合相和分相正反向脉冲代数和差值，表示正-1（负+1））             
		即:总分代数和同正，总<分;同负，总>分;总为负，分为正                     
*********************************************************************************/
	if( ( V_ullForward_T != 0 ) && ( V_ullForward_ABC != 0 ) )		  /*总脉冲数据均为正向*/
	{
		if( V_ullForward_T >= V_ullForward_ABC )
		{
			V_ullForward_T -= V_ullForward_ABC;
			V_ullForward_ABC = 0;
		}
		else
		{
			V_ullForward_ABC -= V_ullForward_T;
			V_ullForward_T = 0;
		}
	}
	else if( ( V_ullReverse_T != 0 ) && ( V_ullReverse_ABC != 0 ) )  /*总脉冲数据均为反向向*/
	{
		if(V_ullReverse_T > V_ullReverse_ABC)
		{
			V_ullForward_ABC = V_ullReverse_T - V_ullReverse_ABC;
		}
		else
		{
			V_ullForward_T = V_ullReverse_ABC - V_ullReverse_T;
		}
	}
	else	/*差值合相与分相方向不同*/
	{
		if(V_ullForward_T > 0)
		{
			V_ullForward_T += V_ullReverse_ABC;
		}
		else
		{
			V_ullForward_ABC += V_ullReverse_T;
		}
	}
/**********************确定在哪一相上作补偿*******************************
功能：将本次读计量芯片中最大脉冲数挑选出来							 
输入:当前读出的脉冲结构体 pV_StrEnergy								
输出:																
pV_usTemp			:待补偿的相别原始脉冲数的指针					
V_ucPhaseFlay	:待补偿的相别指示，后续判断该相是正是负使用  		
	2、4、8代表A、B、C,这里搞错了!应该是1、2、4采用宏!				
注意：1）这里默认在A相操作；2）由于前面全0直接跳走，因此到这里是不会
	出现*pV_usTemp=0情况												
*********************确定在哪一相上作补偿********************************/
	pV_usTemp = &(pV_StrEnergy->V_usReactiveEnergy_A);
	V_ucPhaseFlay = C_ReactiveEDeriction_A;
	if( pV_StrEnergy->V_usReactiveEnergy_A < pV_StrEnergy->V_usReactiveEnergy_B )
	{
		pV_usTemp = &(pV_StrEnergy->V_usReactiveEnergy_B);
		V_ucPhaseFlay = C_ReactiveEDeriction_B;
		if( pV_StrEnergy->V_usReactiveEnergy_B < pV_StrEnergy->V_usReactiveEnergy_C )
		{
			pV_usTemp = &(pV_StrEnergy->V_usReactiveEnergy_C);
			V_ucPhaseFlay = C_ReactiveEDeriction_C;
		}
	}
	else
	{
		if( pV_StrEnergy->V_usReactiveEnergy_A < pV_StrEnergy->V_usReactiveEnergy_C )
		{
			pV_usTemp = &(pV_StrEnergy->V_usReactiveEnergy_C);
			V_ucPhaseFlay = C_ReactiveEDeriction_C;
		}
	}
/***********************************补偿******************************************************
输入：pV_usTemp			待补偿脉冲数指针												  
		V_ucPhaseFlay		待补偿相别指示。												
V_ullForward_T：合相和分相正反向脉冲代数和差值，											
				表示正+1（负-1）即:总分代数和同正，总>分;同负，总<分;总为正，分为负			
V_ullForward_ABC:合相和分相正反向脉冲代数和差值，表示正-1（负+1））即:总分代数和同正，总<分;
			同负，总>分;总为负，分为正														
*********************************************************************************************/
	if(V_ullForward_T >= 3)		/*总脉冲数比分相脉冲数之和多于3个*/
	{
		/**********判断分相是正向脉冲还是反向脉冲**********/
		if( ( pV_StrEnergy->V_ucPowerDeriction & V_ucPhaseFlay ) == V_ucPhaseFlay )
		{
			*pV_usTemp -= 1;
		}
		else
		{
			*pV_usTemp += 1;
		}
	}
	else if( V_ullForward_ABC >= 3 )
	{
		/**********判断分相是正向脉冲还是反向脉冲**********/
		if( ( pV_StrEnergy->V_ucPowerDeriction & V_ucPhaseFlay ) == V_ucPhaseFlay )
		{
			*pV_usTemp += 1;
		}
		else
		{
			*pV_usTemp -= 1;
		}
	}
}

/*******************************************************************************
函数原型：uchar8 SF_SettlementEnergy_Metering_L(Struct_Energy_Type *pStr_Energy)
功能描述：本地费控表阶梯结算电量处理函数
输入参数：Str_Energy指向电能脉冲结构体 
输出参数：无
返回参数：有没有扣费标志指示：
		  C_SubMoneyFlag，有扣费标志；
          C_NoSubMoneyFlag，无扣费标志；
调用位置：电能消息处理函数中调用
备    注：
*******************************************************************************/
uchar8 SF_SettlementEnergy_Metering_L(Struct_Energy_Type *pStr_Energy)
{
	ulong64 V_ullEnergy, V_ullEnergy_F;
	uchar8  V_ucBuffer[80], V_ucCurrentStepType, V_ucFlayTemp;
	uchar8  V_ucTemp[10];
    uchar8  V_ReturnData;
	ushort16 V_usLen, V_usDataEncode;

	if( pStr_Energy->V_usActiveEnergy_T == 0 )
	{
		return C_NoSubMoneyFlag ;		 /*合相有功总脉冲数为0直接返回无扣费*/
	}
	
	/**********************读取当前套阶梯表参数，并判断当前阶梯类型*******/
	V_usDataEncode = 0;
	V_usLen = CLCurrent_Ladder_Table;
	if( InF_Read_Data( CCurrent_Ladder_Table, V_ucBuffer, &V_usLen, &V_usDataEncode ) == C_OK )		/*读取当前套阶梯表参数*/
	{
		V_ucCurrentStepType = SF_Judge_CurrentStep_Type( &V_ucBuffer[C_StepSettlementStartAddr] );		/*判断当前阶梯类型*/
	}
	else
	{
		V_ucCurrentStepType = C_InValidStep;
	}
		
	/**********************当前阶梯结算用电量********************/
	V_usDataEncode = 0;
	V_usLen  = C_EnergyPulseLen;
	V_ucFlayTemp = InF_Read_Data(CY_Com_Ac_Tol_En_0, V_ucTemp, &V_usLen, &V_usDataEncode);
	if( V_ucFlayTemp == C_OK )
	{
		PF_Buffer8ToUlong64(V_ucTemp, &V_ullEnergy_F, C_EnergyPulseLen);
		V_ullEnergy = V_ullEnergy_F + pStr_Energy->V_usActiveEnergy_T;
		PF_Ulong64ToBuffer8(V_ucTemp, &V_ullEnergy, C_EnergyPulseLen);
		InF_Write_Data(C_Msg_EnergyMetering, CY_Com_Ac_Tol_En_0, V_ucTemp, C_EnergyPulseLen, SV_ucEnergySafeFlag);
			
		V_ReturnData = SF_Chargeback(&V_ullEnergy_F, &V_ullEnergy, V_ucBuffer, V_ucCurrentStepType);		/*进行扣费*/
        
		return V_ReturnData;
	}
	
	return C_NoSubMoneyFlag;		
}

/*******************************************************************************
函数原型：void SF_Energy_Metering(void)
功能描述：电能处理函数
输入参数：无
输出参数：无
返回参数：无
调用位置：电能消息处理函数中调用
备    注：
*******************************************************************************/
void SF_Energy_Metering(void)
{
	ulong64  V_ullEnergy;
	ulong32  V_ulID = 1;
	uchar8   V_ucBuffer[5], V_ucRateNo, V_ucFlayTemp;
	ulong64	 V_ullRateEnergy_F, V_ullRateEnergy;
	ushort16 V_usLen, V_usDataEncode;		
	ulong64  V_ullRemainMoney, V_ullRemainMoney_New, V_ullOverDraftMoney, V_ullOverDraftMoney_New;
	uchar8	 V_ucSubMoneyFlag1, V_ucSubMoneyFlag2;
	Struct_Energy_Type Str_Pulse;
	
	if( SV_ucEnergySafeFlag != C_W_SafeFlag_1 )
	{
		return;
	}
	
 	if( InF_Read_MeterIC_EnergyData( &Str_Pulse ) != C_OK )		/*计量芯片读数据不成功*/
	{
		return;
	}
	
	SV_ucEnergySafeFlag |= C_W_SafeFlag_2;
	
	if( SF_JudgePulseActive( &Str_Pulse ) != C_OK )				/*计量芯片数据非法*/
	{
		return;
	}
	
	SF_Adjust_EnergyPulse(&Str_Pulse);							/*进行脉冲调整*/
	
	/**************读取数据层当前费率***********************************/
	V_usDataEncode = 0;
	V_usLen = CLCurr_Rate_No;
	if( InF_Read_Data(CCurr_Rate_No, &V_ucRateNo, &V_usLen, &V_usDataEncode) != C_OK )
	{
		V_ucRateNo = 1;
	}
	
	if( ( V_ucRateNo == 0 ) || ( V_ucRateNo > C_MaxRatesNum ) )	/*当前费率非法在默认尖费率*/
	{
		V_ucRateNo = 1;
	}
	
	SV_ucEnergySafeFlag |= C_W_SafeFlag_3;
	
	/************读取当前数据层费率电能以便本地表进行扣费****************/
	V_ullRateEnergy_F = SF_Get_RateEnergyForChargeback( V_ucRateNo );
	
	/************以下将脉冲数累加到总电能脉冲****************************/
	if( Str_Pulse.V_usActiveEnergy_T > 0 )			 		/*合相有功脉冲不为0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ActiveDeriction_T ) == 0 )
		{
			V_ulID = CPos_Ac_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
		}
		else
		{
			V_ulID = CRev_Ac_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
		}
		
		V_usDataEncode = 0;
		V_usLen  = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK ) 
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usActiveEnergy_T;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data( C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag );
		}
		else
		{	/*读不出电能，直接退出本函数，不进行下一步累加。计量芯片内的本次读到的电能全部丢弃。*/
			return;
		}
	}
	
	if( Str_Pulse.V_usActiveEnergy_A > 0 )					/*A相有功脉冲不为0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ActiveDeriction_A ) == 0 )
		{
			V_ulID = CPosA_Ac_PreEn_0;
		}
		else
		{
			V_ulID = CRevA_Ac_PreEn_0;
		}
		
		V_usDataEncode = 0;
		V_usLen  = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK )
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usActiveEnergy_A;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*读不出电能，直接退出本函数，不进行下一步累加。计量芯片内的本次读到的电能全部丢弃。*/
			return;
		}
	}
	
	if( Str_Pulse.V_usActiveEnergy_B > 0 )					/*B相有功脉冲不为0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ActiveDeriction_B ) == 0 )
		{
			V_ulID = CPosB_Ac_PreEn_0;
		}
		else
		{
			V_ulID = CRevB_Ac_PreEn_0;
		}
		
		V_usDataEncode = 0;
		V_usLen = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK )
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usActiveEnergy_B;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*读不出电能，直接退出本函数，不进行下一步累加。计量芯片内的本次读到的电能全部丢弃。*/
			return;
		}
	}
	
	if( Str_Pulse.V_usActiveEnergy_C > 0 )					/*C相有功脉冲不为0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ActiveDeriction_C ) == 0 )
		{
			V_ulID = CPosC_Ac_PreEn_0;
		}
		else
		{
			V_ulID = CRevC_Ac_PreEn_0;
		}
		
		V_usDataEncode = 0;
		V_usLen = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK )
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usActiveEnergy_C;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*读不出电能，直接退出本函数，不进行下一步累加。计量芯片内的本次读到的电能全部丢弃。*/
			return;
		}
	}
	
	/*******************无功电能处理************************/
	if( Str_Pulse.V_usReactiveEnergy_T > 0 )				/*合相无功脉冲不为0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_T ) == 0x00 )							/*第1象限*/
		{
			V_ulID = CQua1_Re_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_T ) == C_ActiveDeriction_T )		/*第2象限*/
		{
			V_ulID = CQua2_Re_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_T ) == C_ReactiveDeriction_T )	/*第3象限*/
		{
			V_ulID = CQua3_Re_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
		}
		else												/*第4象限*/
		{
			V_ulID = CQua4_Re_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
		}
		
		V_usDataEncode = 0;
		V_usLen  = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode );
		if( V_ucFlayTemp == C_OK ) 
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usReactiveEnergy_T;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*读不出电能，直接退出本函数，不进行下一步累加。计量芯片内的本次读到的电能全部丢弃。*/
			return;
		}
	}
	
	if( Str_Pulse.V_usReactiveEnergy_A > 0 )				/*合相无功脉冲不为0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_A ) == 0x00 )							/*第1象限*/
		{
			V_ulID = CQua1A_Re_PreEn_0;
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_A ) == C_ActiveDeriction_A )		/*第2象限*/
		{
			V_ulID = CQua2A_Re_PreEn_0;
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_A ) == C_ReactiveDeriction_A )	/*第3象限*/
		{
			V_ulID = CQua3A_Re_PreEn_0;
		}
		else												/*第4象限*/
		{
			V_ulID = CQua4A_Re_PreEn_0;
		}
		
		V_usDataEncode = 0;
		V_usLen  = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK ) 
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usReactiveEnergy_A;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*读不出电能，直接退出本函数，不进行下一步累加。计量芯片内的本次读到的电能全部丢弃。*/
			return;
		}
	}
	
	if( Str_Pulse.V_usReactiveEnergy_B > 0 )				/*合相无功脉冲不为0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_B ) == 0x00 )						/*第1象限*/
		{
			V_ulID = CQua1B_Re_PreEn_0;
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_B ) == C_ActiveDeriction_B)	/*第2象限*/
		{
			V_ulID = CQua2B_Re_PreEn_0;
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_B ) == C_ReactiveDeriction_B)	/*第3象限*/
		{
			V_ulID = CQua3B_Re_PreEn_0;
		}
		else												/*第4象限*/
		{
			V_ulID = CQua4B_Re_PreEn_0;
		}
		
		V_usDataEncode = 0;
		V_usLen = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK ) 
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usReactiveEnergy_B;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*读不出电能，直接退出本函数，不进行下一步累加。计量芯片内的本次读到的电能全部丢弃。*/
			return;
		}
	}
	
	if( Str_Pulse.V_usReactiveEnergy_C > 0 )				/*合相无功脉冲不为0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_C ) == 0x00 )						 /*第1象限*/
		{
			V_ulID = CQua1C_Re_PreEn_0;
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_C ) == C_ActiveDeriction_C )	 /*第2象限*/
		{
			V_ulID = CQua2C_Re_PreEn_0;
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_C ) == C_ReactiveDeriction_C ) /*第3象限*/
		{
			V_ulID = CQua3C_Re_PreEn_0;
		}
		else													/*第4象限*/
		{
			V_ulID = CQua4C_Re_PreEn_0;
		}
		
		V_usDataEncode = 0;
		V_usLen = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK )
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usReactiveEnergy_C;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*读不出电能，直接退出本函数，不进行下一步累加。计量芯片内的本次读到的电能全部丢弃。*/
			return;
		}
	}
	
	if(C_Meter_Type != C_L_SmartMeter)
	{	/*非本地，用电量的处理。目前月用电量和结算用电量对于非本地，通过计算得到，这里直接返回。*/
		return;		/*远程费控表和智能表直接返回*/
	}
	else
	{
		/****************************本地表扣费及报警处理****************************************/
		
		/*获取扣费前的剩余金额、透支金额*/
		if( SF_Get_RMoney_DMoney(&V_ullRemainMoney, &V_ullOverDraftMoney) != C_OK )
		{
			return;
		}
		
		V_usDataEncode = 0;
		V_usLen = CLRate_Num;
		if( InF_Read_Data(CRate_Num, &V_ucFlayTemp, &V_usLen, &V_usDataEncode) != C_OK )
		{
			V_ucFlayTemp = 1;		/*费率数读不出，默认正常扣费*/
		}
		
		if( V_ucFlayTemp != 0 )
		{
			/*费率电能扣费*/	
			V_ullRateEnergy = SF_Get_RateEnergyForChargeback( V_ucRateNo );
			V_ucSubMoneyFlag1 = SF_RateChargeback(V_ullRateEnergy_F, V_ullRateEnergy, V_ucRateNo);
		}
		else   
		{
			/*去费率表，费率数是0，不扣费*/
			V_ucSubMoneyFlag1 = C_NoSubMoneyFlag;
		}
		/*用电量的累加及阶梯电价的扣减。*/
		V_ucSubMoneyFlag2 = SF_SettlementEnergy_Metering_L( &Str_Pulse );
		
		/*进行报警1、2及透支门限处理*/
		if( ( V_ucSubMoneyFlag1 == C_SubMoneyFlag ) || ( V_ucSubMoneyFlag2 == C_SubMoneyFlag ) )
		{
			if( SF_Get_RMoney_DMoney( &V_ullRemainMoney_New, &V_ullOverDraftMoney_New ) != C_OK )
			{
				return;
			}
			
			SF_JudgeWarningStatus(V_ullRemainMoney, V_ullRemainMoney_New, V_ullOverDraftMoney, V_ullOverDraftMoney_New, C_RenewRederict);
			
			/*刷新当前电价*/
			SF_WriteCurrentPrice( );
		}
	}
}

/************************************************************************************************
函数原型：uchar8 SF_RateChargeback(ulong64 V_ullEnergy_F, ulong64 V_ullEnergy, uchar8 V_ucRateNo)
功能描述：完成费率电价扣费
输入参数：V_ullEnergy_F，累加前电能(脉冲数)；
          V_ullEnergy，累加后电能 (脉冲数)；
          V_ucRateNo 费率号；
输出参数：无
返回参数：C_SubMoneyFlag:表示扣费标志；
         C_NoSubMoneyFlag：表示无扣费标志；
调用位置：本地费控表扣费调用
备    注：V_ucRateNo 费率号，调用本函数的地方，已确保1-12之间，函数内部不判断费率号的合法性
*************************************************************************************************/
uchar8 SF_RateChargeback(ulong64 V_ullEnergy_F, ulong64 V_ullEnergy, uchar8 V_ucRateNo)
{
	ulong64 V_ullRemainMoney, V_ullRemainMoney_New, V_ullOverDraftMoney, V_ullOverDraftMoney_New;
	ulong64 V_ullFeeDeduction;	    /* 每0.01度扣费次数=当前电价*电压互感器变比*电流互感器变比 */
	ulong64 V_ullPulseConstant;
	ulong32 V_ulCurrentPrice;
	uchar8  V_ucBuffer[8];
	ulong64 V_ullNeedChargebackMoney;
	ushort16 V_usLen, V_usDataEncode;
	
	/****************** 脉冲常数 ***************************************/
	SF_Read_PulseConstant(&V_ullPulseConstant);											/* 读取电能脉冲常数ulong64格式 */
	
	/***************** 判断是否需扣费 **********************************/
	V_ullEnergy_F *= C_EnergyChangeEquivalent_Hundred;			/* 这里不会溢出，单位0.01度*/
	V_ullEnergy *= C_EnergyChangeEquivalent_Hundred;
	
	/* 计算电能，0.01度 */
	V_ullEnergy_F = V_ullEnergy_F / V_ullPulseConstant;
	V_ullEnergy = V_ullEnergy / V_ullPulseConstant;
	
	if(V_ullEnergy > V_ullEnergy_F)								/* 有0.01度进位，需要扣费操作 */
	{
		if( SF_Get_RMoney_DMoney( &V_ullRemainMoney, &V_ullOverDraftMoney ) != C_OK )
		{
			return(C_NoSubMoneyFlag);
		}
		
		/********************获取费率电价并将当前费率电价返写数据层******************/
		/*输出V_ulCurrentPrice，单位为0.0001元/kWh，即0.01分/kWh*/
		V_usDataEncode = 0;
		V_usLen = CLCurr_Rate_Price; 
		if( InF_Read_Data( ( CCurrent_RateFF_Price & 0xFFFFFF00 ) | V_ucRateNo , &V_ucBuffer[0], &V_usLen, &V_usDataEncode ) != C_OK )
		{
			/*默认0.5元*/
            memset(&V_ucBuffer[0], 0x00, 4);
			V_ucBuffer[0] = 0x88;
			V_ucBuffer[1] = 0x13;
		}  
		else
		{
			;
		}
		
		InF_Write_Data(C_Msg_EnergyMetering, CCurr_Rate_Price, &V_ucBuffer[0], CLCurr_Rate_Price, C_W_SafeFlag);	/*更新数据层当前费率电价*/
		
		PF_BufferXToUlong32(V_ucBuffer, &V_ulCurrentPrice, CLCurr_Rate_Price);
		
		/******************** 获取电压、电流互感器变比 ******************/
		V_ullFeeDeduction = SF_Get_V_I_Ratio( );
		
		/******************** 进行扣费 **********************************/	
		V_ullNeedChargebackMoney = V_ulCurrentPrice * (V_ullEnergy - V_ullEnergy_F);	/*0.01度扣费金额*/
		V_ullNeedChargebackMoney *= V_ullFeeDeduction;		/* 乘以变比后的扣费金额 */
		
		if( V_ullRemainMoney != 0 )
		{	/*本次剩余金额不为0*/
			if(V_ullRemainMoney >= V_ullNeedChargebackMoney)
			{
				V_ullRemainMoney_New = V_ullRemainMoney - V_ullNeedChargebackMoney;
				V_ullOverDraftMoney_New = 0;
			}
			else
			{
				V_ullRemainMoney_New = 0;
				V_ullOverDraftMoney_New = V_ullNeedChargebackMoney - V_ullRemainMoney;
			}
		}
		else
		{	/*扣减前剩余金额为0*/
			V_ullRemainMoney_New = 0;
			V_ullOverDraftMoney_New = V_ullOverDraftMoney + V_ullNeedChargebackMoney;
		}
		
		/***********************将新的剩余金额、透支金额返写数据层******************************/
		PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullRemainMoney_New, CLCurr_Money);
		InF_Write_Data(C_Msg_EnergyMetering, CChargeBal_Hex_Cent, V_ucBuffer, CLCurr_Money, SV_ucEnergySafeFlag);
		
		PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullOverDraftMoney_New, CLCurr_Money);
		InF_Write_Data(C_Msg_EnergyMetering, COverDraft_Hex_Cent, V_ucBuffer, CLCurr_Money, SV_ucEnergySafeFlag);
		
		return(C_SubMoneyFlag);
	}
	else
	{	/*没有0.01度进位，不需要扣费操作*/
		return(C_NoSubMoneyFlag);
	}
}

/*******************************************************************************
函数原型：void SF_WriteCurrentPrice(void)
功能描述：根据数据层费率电价和阶梯电价，写数据层当前电价
输入参数：无
输出参数：无
返回参数：无
调用位置：本地费控表扣费调用
备    注：
*******************************************************************************/
void SF_WriteCurrentPrice(void)
{
	uchar8   V_ucBuffer[4];
	ulong32  V_ulCurr_Rate_Price = 0, V_ulCurr_Price_Temp = 0; 
	ushort16 V_usLen, V_usDataEncode;
	
	/*读费率电价*/
	V_usDataEncode = 0;
	V_usLen = CLCurr_Rate_Price;
	InF_Read_Data(CCurr_Rate_Price, V_ucBuffer, &V_usLen, &V_usDataEncode);
	PF_BufferXToUlong32(V_ucBuffer, &V_ulCurr_Rate_Price, CLCurr_Rate_Price);
	
	/*读阶梯电价*/
	V_usDataEncode = 0;
	V_usLen = CLCurr_Ladder_Price;
	InF_Read_Data(CCurr_Ladder_Price, V_ucBuffer, &V_usLen, &V_usDataEncode);
	PF_BufferXToUlong32(V_ucBuffer, &V_ulCurr_Price_Temp, CLCurr_Ladder_Price);

	/*计算*/
	V_ulCurr_Price_Temp += V_ulCurr_Rate_Price;	/*当前费率电价+当前阶梯电价得到当前电价*/
	PF_Ulong32ToBufferX(V_ucBuffer, &V_ulCurr_Price_Temp, CLCurr_Price);
	
	InF_Write_Data(C_Msg_EnergyMetering, CCurr_Price, &V_ucBuffer[0], CLCurr_Price, C_W_SafeFlag);		   /*当前电价返写数据层*/	
}

/*******************************************************************************
函数原型：ulong64 SF_Get_V_I_Ratio(void)
功能描述：获取电压电流互感器变比乘积
输入参数：无
输出参数：无
返回参数：64位脉冲数
调用位置：本地费控表扣费调用
备    注：
*******************************************************************************/
ulong64 SF_Get_V_I_Ratio(void)
{
	uchar8  V_ucReturn, V_ucBuffer[10];
	ulong64 V_ullFeeDeduction;
	ulong32 V_ulTemp;
	ushort16 V_usLen, V_usDataEncode;
	
	/**************读取电压电流互感器变比，不对或者为0则默认为1****************/
	V_usDataEncode = 0;
	V_usLen = CLRatio_Vol_Tran;
	V_ucReturn = InF_Read_Data(CRatio_Vol_Tran, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucReturn != C_OK )				 /*数据层读取参数不正确默认设置为1*/
	{
		V_ullFeeDeduction = 1;
	}
	else
	{
		PF_BufferXToUlong32(V_ucBuffer, &V_ulTemp, CLRatio_Vol_Tran);		/*互感器变比转化为hex格式*/
		V_ullFeeDeduction = V_ulTemp;	
		if(V_ullFeeDeduction == 0)
		{
			V_ullFeeDeduction = 1;
		}
	}
	
	V_usDataEncode = 0;
	V_usLen = CLRatio_Curr_Tran;
	V_ucReturn = InF_Read_Data(CRatio_Curr_Tran, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucReturn != C_OK )			/*数据层读取参数不正确默认设置为1*/
	{
		V_ulTemp = 1;
	}
	else
	{
		PF_BufferXToUlong32(V_ucBuffer, &V_ulTemp, CLRatio_Curr_Tran);		/*互感器变比转化为hex格式*/
		if(V_ulTemp == 0)
		{
			V_ulTemp = 1;
		}
	}
	
	V_ullFeeDeduction *= V_ulTemp;		/*电压电流互感器变比相乘*/
	
    return V_ullFeeDeduction;
}

/*******************************************************************************
函数原型：ulong64 SF_Get_RateEnergyForChargeback(uchar8 V_ucRateNo)
功能描述：根据费率号，读取数据层的费率电能脉冲数。
输入参数：V_ucRateNo:费率号
输出参数：无
返回参数：8字节脉冲数
调用位置：本地费控表扣费调用
备    注：1、脉冲数读不出，则累加0。
		 2、这里费率电能采用“正+反”的方式。不考虑组合状态字。
		 3、V_ucRateNo在调用这个函数的地方，已确保在1-12之间，函数内部不判断费率号合法性
*******************************************************************************/
ulong64 SF_Get_RateEnergyForChargeback(uchar8 V_ucRateNo)
{
	ulong64	V_ullRateEnergy = 0;
	ulong64	V_ullRev_RateEnergy = 0;
	ulong32	V_ulOAD;
	uchar8	V_ucBuffer[C_EnergyPulseLen];
	ushort16 V_usLen, V_usDataEncode;	
	
	/*读正向费率脉冲*/
	V_ulOAD = CPos_Ac_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
	V_usDataEncode = 0;
	V_usLen = C_EnergyPulseLen;
	if( InF_Read_Data(V_ulOAD, V_ucBuffer, &V_usLen, &V_usDataEncode) != C_OK )
	{
		memset(V_ucBuffer, 0x00, C_EnergyPulseLen);
	}	
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullRateEnergy, C_EnergyPulseLen);
	
	/*读反向费率脉冲*/		
	V_ulOAD = CRev_Ac_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
	V_usDataEncode = 0;
	V_usLen = C_EnergyPulseLen;
	if( InF_Read_Data(V_ulOAD, V_ucBuffer, &V_usLen, &V_usDataEncode) != C_OK)
	{
		memset(V_ucBuffer, 0x00, C_EnergyPulseLen);
	}	
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullRev_RateEnergy, C_EnergyPulseLen);
	
	/*正+反*/
	V_ullRateEnergy = V_ullRateEnergy + V_ullRev_RateEnergy;

	return(V_ullRateEnergy);
		
}

/*******************************************************************************
函数原型：uchar8 SF_Get_RMoney_DMoney(ulong64 *pV_ullRemainMoney, ulong64 *pV_ullOverDraftMoney)
功能描述：读取数据层当前的剩余金额及透支金额
输入参数：pV_ullRemainMoney:剩余金额的缓存地址；
          pV_ullOverDraftMoney:透支金额缓存地址
输出参数：*pV_ullRemainMoney:剩余金额，单位为0.000001元格式Hex
          *pV_ullOverDraftMoney:透支金额，单位为0.000001元格式Hex
返回参数：C_OK/C_Error
调用位置：本地费控表扣费调用
备    注：
*******************************************************************************/
uchar8 SF_Get_RMoney_DMoney(ulong64 *pV_ullRemainMoney, ulong64 *pV_ullOverDraftMoney)
{
	uchar8 V_ucReturn;
	uchar8 V_ucBuffer[10];
	ushort16 V_usLen, V_usDataEncode;		
	
	/*****************剩余金额，单位0.000001元***********************/
	V_usDataEncode = 0;
	V_usLen = CLCurr_Money;
	V_ucReturn = InF_Read_Data( CChargeBal_Hex_Cent, V_ucBuffer, &V_usLen, &V_usDataEncode );
	if( V_ucReturn != C_OK ) 	   
	{
		return C_Error;
	}
	else
	{
		PF_Buffer8ToUlong64(V_ucBuffer, pV_ullRemainMoney, CLCurr_Money); 		/*剩余金额转换为ulong64格式*/
	}
	
	/*****************透支金额，单位0.000001元***********************/
	V_usDataEncode = 0;
	V_usLen = CLCurr_Money;
	V_ucReturn = InF_Read_Data( COverDraft_Hex_Cent, V_ucBuffer, &V_usLen, &V_usDataEncode );
	if(V_ucReturn != C_OK) 			
	{
		return C_Error;
	}
	else
	{
		PF_Buffer8ToUlong64(V_ucBuffer, pV_ullOverDraftMoney, CLCurr_Money);     /*透支金额转换为ulong64格式*/
	}
	return(C_OK);
}

/*******************************************************************************
函数原型：uchar8 InF_EnergyMetering_Message(Str_Msg_Parameter *pStr_Msg_Parameter)
功能描述：电能消息处理函数
输入参数：pStr_Msg_Parameter指向消息读取后存放的静态变量
输出参数：无 
返回参数：C_OK正确处理，C_Error处理过程中错误
调用位置：调度500ms定时器到调用调用
备    注：
*******************************************************************************/
uchar8 InF_EnergyMetering_Message(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	SV_ucEnergySafeFlag = 0;
	
	if( pStr_Msg_Parameter->PowerFlag != C_PowerOn )
	{
		return C_Error;
	}
	
	if ( ( pStr_Msg_Parameter->SourceAddr 	== C_Msg_Dispatch )
	  && ( pStr_Msg_Parameter->DerictAddr 	== C_Msg_EnergyMetering )
	  && ( pStr_Msg_Parameter->Parameter[0] == Pt_Dispatch_Timing ) )			/*消息源地址和目的地址及消息类型均正确，安全标志加1*/
	{
		SV_ucEnergySafeFlag |= C_W_SafeFlag_1;
		SF_Energy_Metering( );
	}
	else if ( ( pStr_Msg_Parameter->DerictAddr 	  == C_Msg_EnergyMetering )		/*目的消息为电能计量*/
		    && ( pStr_Msg_Parameter->Parameter[0] == Pt_ParaMetersChange ) 	
			&& ( pStr_Msg_Parameter->Parameter[1] == C_ReworkWarningPara ) )	/*参数改变消息处理*/
	{	
		SV_ucEnergySafeFlag |= C_W_SafeFlag_1;	
		SF_ReworkWarningPara( );	
	}	
	else if ( ( ( pStr_Msg_Parameter->DerictAddr	== C_Msg_EnergyMetering )	/*目的消息为电能计量*/
		      && ( pStr_Msg_Parameter->Parameter[0] == Pt_RatePrice ) )			/*每分钟更新费率、阶梯、当前电价*/
		   || ( ( pStr_Msg_Parameter->DerictAddr 	== C_Msg_BroadcastAddress )	/*广播消息*/
		      && ( pStr_Msg_Parameter->Parameter[0] == Pt_MeterClear ) && ( C_Meter_Type == C_L_SmartMeter ) ) )	/*电表总清消息且为本地表*/
	{
		SF_UpdateCurrentPrice( );
	}
	else
	{
		return C_Error;
	}

	SV_ucEnergySafeFlag = 0;
	
    return C_OK;
}

/*******************************************************************************
函数原型：uchar8 InF_ReturnMoneyFromPurchase(ulong32 V_ulBuyMoney, uchar8 V_ucSafeFlag)
功能描述：退费处理，将退费后剩余金额、透支金额返写数据层
输入参数：V_ulBuyMoney,退费金额，hex格式，单位0.01元;
		  V_ucSafeFlag,安全标志;
输出参数：无
返回参数：C_OK表示退费成功，剩余金额、透支金额、报警处理、跳闸处理已经成功
          C_NoAccess表示无权限，C_SafeFlagError表示安全标志错，C_Error表示其他错误
调用位置：通信退费时调用
备    注：
*******************************************************************************/
uchar8 InF_ReturnMoneyFromPurchase(ulong32 V_ulBuyMoney, uchar8 V_ucSafeFlag)
{
	ulong64 V_ullRemainingMoney, V_ullRemainingMoney_L, V_ullOverdraftMoney;
	ulong64 V_ullReturnMoney;
	uchar8  V_ucTurn, V_ucBuffer[6];
    
    if( V_ucSafeFlag != C_W_SafeFlag )
    {
        return C_SafeFlagError;
    }
	
	/***********************退费金额的处理********************************/
	V_ullReturnMoney = V_ulBuyMoney;
	V_ullReturnMoney *= C_MoneyChangeEquivalent;	  /*转换为与数据层相同格式,0.0001分的hex格式*/
	
	/******************读取数据层剩余金额，单位0.0001分的hex格式*********************************/
	/******************读取数据层透支金额，单位0.0001分的hex格式*********************************/
	V_ucTurn = SF_Get_RMoney_DMoney(&V_ullRemainingMoney, &V_ullOverdraftMoney); 
	if(V_ucTurn != C_OK)
	{
		return V_ucTurn;
	}

    /******************判断是否允许退费**********************************************************/
    if ( ( V_ullReturnMoney > V_ullRemainingMoney )      		/*退费金额大于原来剩余金额*/
      || ( V_ullOverdraftMoney > 0 ) )                   		/*透支金额不为0*/
    {
        return C_NoAccess;
    }
	
    /******************计算退费后剩余金额，单位0.0001分的hex格式*********************************/
    V_ullRemainingMoney_L = V_ullRemainingMoney - V_ullReturnMoney;
    V_ullOverdraftMoney = 0;    /*透支金额为0*/
	
	/*************判断报警、预跳闸报警、透支及立即拉闸状态,入口参数为单位0.000001元的hex格式****/
	SF_JudgeWarningStatus(V_ullRemainingMoney, V_ullRemainingMoney_L, 0, V_ullOverdraftMoney, C_RenewDerict);	/*扣费前透支金额直接写0，因为必须有剩余金额的情况下才能退费，因此扣费前透支金额一定为0*/

	/***********************将剩余金额、透支金额返写数据层，单位0.0001分的hex格式**************/
	PF_Ulong64ToBuffer8(V_ucBuffer,&V_ullRemainingMoney_L, C_EnergyPulseLen);		/*剩余金额*/
	V_ucTurn = InF_Write_Data(C_Msg_EnergyMetering, CChargeBal_Hex_Full, V_ucBuffer, CLChargeBal_Hex_Full, V_ucSafeFlag);
	if(V_ucTurn != C_OK)
	{
		return C_Error;
	}

	PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullOverdraftMoney, C_EnergyPulseLen);		/*透支金额*/
	V_ucTurn = InF_Write_Data(C_Msg_EnergyMetering, COverDraft_Hex_Full, V_ucBuffer, CLOverDraft_Hex_Full, V_ucSafeFlag);
	if(V_ucTurn != C_OK)
	{
		return C_Error;
	}
	return C_OK;
}

/*******************************************************************************
函数原型：void SF_ReworkWarningPara(void)
功能描述：参数修改后判断当前报警、透支、跳闸状态
输入参数：无	
输出参数：无	
返回参数：无	
调用位置：电能模块消息处理函数
备    注：
*******************************************************************************/
void SF_ReworkWarningPara(void)
{
	ulong64  V_ullRemainingMoney, V_ullOverdraftMoney;
	uchar8   V_ucBuffer[CLCurrent_Ladder_Table];
	ushort16 V_usLen, V_usDataEncode;
        	
	/******************读取数据层剩余金额、透支金额,单位0.000001元的hex格式************************/
	V_usDataEncode = 0;
	V_usLen = C_EnergyPulseLen;
	if( InF_Read_Data( CChargeBal_Hex_Cent, V_ucBuffer, &V_usLen, &V_usDataEncode) != C_OK )	/*剩余金额*/
	{
		return;
	}
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullRemainingMoney, C_EnergyPulseLen);
	SV_ucEnergySafeFlag |= C_W_SafeFlag_2;
	
	V_usDataEncode = 0;
	V_usLen = C_EnergyPulseLen;
	if( InF_Read_Data(COverDraft_Hex_Cent, V_ucBuffer, &V_usLen, &V_usDataEncode) != C_OK )		/*透支金额*/
	{
		return;
	}
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullOverdraftMoney, C_EnergyPulseLen);
	SV_ucEnergySafeFlag |= C_W_SafeFlag_3;
	
	/*********************判断报警、预跳闸报警、透支、立即跳闸状态***********************/
	if( SV_ucEnergySafeFlag != ( C_W_SafeFlag_1 | C_W_SafeFlag_2 | C_W_SafeFlag_3 ) )
	{
		return;
	}
	
	SF_JudgeWarningStatus(V_ullRemainingMoney, V_ullRemainingMoney, 0, V_ullOverdraftMoney, C_RenewDerict);		/*这里扣费前透支金额写成0，保证透支金额不为0的时候进行透支报警*/
}

/*******************************************************************************
函数原型：void SF_UpdateCurrentPrice(void)
功能描述：更新数据层当前费率电价、阶梯电价、当前电价
输入参数：无	
输出参数：无	
返回参数：无	
调用位置：电能模块消息处理函数
备    注：
*******************************************************************************/
void SF_UpdateCurrentPrice(void)
{
	uchar8  V_ucBuffer[CLCurrent_Ladder_Table];
    uchar8  V_ucCurrentStepType, V_ucEnergy[10];
    ulong32 V_ulEnergy_F, V_ulCurrentPrice;
	uchar8	V_ucRateNo;
	ushort16 V_usLen, V_usDataEncode = 0;
        
	/* 读取当前套阶梯表参数，并判断当前阶梯类型 */
	V_usDataEncode = 0;
	V_usLen = CLCurrent_Ladder_Table;
	if( InF_Read_Data(CCurrent_Ladder_Table, V_ucBuffer, &V_usLen, &V_usDataEncode) == C_OK )		/* 读取当前套阶梯表参数 */
	{
		V_ucCurrentStepType = SF_Judge_CurrentStep_Type(&V_ucBuffer[C_StepSettlementStartAddr]);	/* 判断当前阶梯类型 */
	}
	else
	{
		V_ucCurrentStepType = C_InValidStep;
	}
	
	/* 根据当前阶梯类型读取相应电能 */
	V_ulEnergy_F = 0;
	V_usLen  = CLY_Com_Ac_Tol_En_0;
	if( V_ucCurrentStepType == C_ValidStep )					/* 读取阶梯结算用电量 */
	{
		if( InF_Get_EnergyModule(CY_Com_Ac_Tol_En_0, V_ucEnergy, &V_usLen, &V_usDataEncode) == C_OK )
		{
			PF_BufferXToUlong32(V_ucEnergy, &V_ulEnergy_F, CLY_Com_Ac_Tol_En_0);
		}
		else
		{
			V_ulEnergy_F = 0;	
		}
	}
	
	/* 更新数据层当前阶梯电价及刷新显示 */
	SF_Judge_CurrentStep(V_ulEnergy_F, &V_ulCurrentPrice, V_ucBuffer, V_ucCurrentStepType);
	
	/* 判断是否是去费率，去费率表不扣费，当前费率电价为0 */
	V_usDataEncode = 0;
	V_usLen = CLRate_Num;
	if( InF_Read_Data( CRate_Num, &V_ucRateNo, &V_usLen, &V_usDataEncode) != C_OK )
	{
		V_ucRateNo = 1;
	}	
	
	if( V_ucRateNo == 0 )  
	{
		memset( V_ucBuffer, 0x00, CLCurr_Rate_Price );
	}
	else
	{
	
		/* 更新数据层费率电价 */
		/* 读取当前费率 */
		V_usDataEncode = 0;
		V_usLen = CLCurr_Rate_No;
		if( InF_Read_Data(CCurr_Rate_No, &V_ucRateNo, &V_usLen, &V_usDataEncode) != C_OK )
		{
			V_ucRateNo = 1;
		}
		if( ( V_ucRateNo == 0 ) || ( V_ucRateNo > C_MaxRatesNum ) )
		{
			V_ucRateNo = 1;
		}
		
		/* 将当前费率电价返写数据层 */
		V_usDataEncode = 0;
		V_usLen = CLCurr_Rate_Price;	
		if( InF_Read_Data( ( CCurrent_RateFF_Price & 0xFFFFFF00 ) | V_ucRateNo, V_ucBuffer, &V_usLen, &V_usDataEncode ) != C_OK )
		{
			memset(V_ucBuffer, 0x00, 4);	/*读不出来，默认0.5元*/
			V_ucBuffer[0] = 0x88;
			V_ucBuffer[1] = 0x13;
		}
		
	}
	
	InF_Write_Data(C_Msg_EnergyMetering, CCurr_Rate_Price, V_ucBuffer, CLCurr_Rate_Price, C_W_SafeFlag);
	
	/* 刷新数据层的当前电价 */
	SF_WriteCurrentPrice( );
}

/*******************************************************************************
函数原型：uchar8 SF_CheckMoneyToPurchaseFlag(void)
功能描述：购电标志SV_ucMoneyToPurchaseFlag CRC标志校验；若校验错误，则购电标志清零。
输入参数：SV_ucMoneyToPurchaseFlag,全局购电标志；
输出参数：无
返回参数：是否购电:C_MoneyToPurchase购电,C_NoMoneyToPurchase没有购电
调用位置：电能模块报警判断函数	
备    注：该标志在购电的时候置起来,检测到购电金额大于报警金额2则清零
*******************************************************************************/
uchar8 SF_CheckMoneyToPurchaseFlag(void)
{
	if( PF_Check_CRC(SV_ucMoneyToPurchaseFlag, ( C_MoneyToPurchaseFlagLen + 2 ) ) != C_OK )
	{
		SF_SetMoneyToPurchaseFlag( C_NoMoneyToPurchase );		/* 购电标志清零 */
	}
	
	if( SV_ucMoneyToPurchaseFlag[0] == C_MoneyToPurchase )
	{
		return C_MoneyToPurchase;
	}
	else
	{
		return C_NoMoneyToPurchase;
	}
}

/*******************************************************************************
函数原型：void SF_SetMoneyToPurchaseFlag(uchar8 V_ucPurchaseFlag)
功能描述：置购电标志和清购电标志
输入参数：V_ucPurchaseFlag: C_MoneyToPurchase,购电；C_NoMoneyToPurchase，未购电；
输出参数：无
返回参数：无
调用位置：充值、钱包初始化、判断报警状态
备    注：
*******************************************************************************/
void SF_SetMoneyToPurchaseFlag(uchar8 V_ucPurchaseFlag)
{
	ushort16 V_usCRC;
	
	SV_ucMoneyToPurchaseFlag[0] = V_ucPurchaseFlag;
	V_usCRC = PF_Cal_CRC(SV_ucMoneyToPurchaseFlag, C_MoneyToPurchaseFlagLen);
	PF_Ushort16ToBuffer2(&SV_ucMoneyToPurchaseFlag[1], &V_usCRC);	
}

