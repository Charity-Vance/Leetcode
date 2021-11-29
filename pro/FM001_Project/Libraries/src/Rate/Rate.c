/********************************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Rate.c
Version:       V1
Author:        
Date:          2014-3-12
Description:   费率、时段等的处理
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
#include "Rate.h"
#include "IO.h"

/*******************************************************************************
函数原型: void SF_JudgeTimeInterval_RateNum(uchar8 *pV_ucData, uchar8 V_ucTimeIntervalNum)
功能描述: 判断时段表中费率号，费率号大于设置的费率数，则非法时段后面的时段均按最后一个合法的执行
输入参数: pV_ucData时段表数据地址（最大42字节）， TimeIntervalNum时段表个数
输出参数: pV_ucData时段表调整后的数据地址（调整为按最后1个合法）
返回参数: 无
调用位置: Msg_Deal_MultiRates	费率处理函数
备    注: TimeIntervalNum合法性外面已经判过了
*******************************************************************************/
void SF_JudgeTimeInterval_RateNum(uchar8 *pV_ucData, uchar8 V_ucTimeIntervalNum)
{
	uchar8 V_ucBuffer[CLFirst_TZone_1PT_Data];
	uchar8 V_uci, V_ucj, V_ucDataoff = 0, V_ucRateNum;
	ushort16 V_usDataLen, V_usDataEncode = 0;
	
	V_usDataLen = CLRate_Num;
	if (InF_Read_Data(CRate_Num, &V_ucRateNum, &V_usDataLen, &V_usDataEncode) != C_OK)
	{
		V_ucRateNum = C_MaxRatesNum;							/*zlj，之前是BCD格式，现在读出来是HEX格式*/
	}
	
	PF_CopyDataBytes(pV_ucData, V_ucBuffer, CLFirst_TZone_1PT_Data);
	for (V_uci = 0; V_uci < V_ucTimeIntervalNum; V_uci++)
	{
		if (V_ucBuffer[V_ucDataoff + 2] >  V_ucRateNum)			/*zlj，之前日时段表在低字节，现在日时段表在高字节*/
		{
			if (V_ucTimeIntervalNum == 1)						/*只有1个时段表且非法*/
			{
				V_ucBuffer[V_ucDataoff + 2] = 1;				/*第1个费率号，默认尖*/
				break;
			}
			if (V_uci == 0)										/*第1个费率号就非法*/
			{
				V_ucBuffer[V_ucDataoff + 2] = 1;				/*第1个费率号，默认尖*/
				for (V_ucj = 0; V_ucj < (V_ucTimeIntervalNum - 1); V_ucj++)
				{
					PF_CopyDataBytes(&V_ucBuffer[V_ucDataoff], &V_ucBuffer[V_ucDataoff + CL_OneTimeIntervalNum], CL_OneTimeIntervalNum);
					V_ucDataoff += CL_OneTimeIntervalNum;
					if (V_ucDataoff > CLFirst_TZone_1PT_Data)
					{
						break;
					}
				}
				break;
			}
			else
			{
				for (V_ucj = 0; V_ucj < (V_ucTimeIntervalNum - V_uci); V_ucj++)
				{
					PF_CopyDataBytes(&V_ucBuffer[V_ucDataoff - CL_OneTimeIntervalNum], &V_ucBuffer[V_ucDataoff + CL_OneTimeIntervalNum * V_ucj], CL_OneTimeIntervalNum);
				}
				break;
			}
		}
		else
		{
			V_ucDataoff += CL_OneTimeIntervalNum;
			if (V_ucDataoff > CLFirst_TZone_1PT_Data)
			{
				break;
			}
		}
	}
	PF_CopyDataBytes(V_ucBuffer, pV_ucData, CLFirst_TZone_1PT_Data);

}

/*******************************************************************************
函数原型: void InF_MultiRates_ParseMessageMsg_Deal_MultiRates (Str_Msg_Parameter *pStr_Msg)
功能描述: 费率判断处理函数
输入参数: 判断信息参数结构体pStr_Msg中的参数，结构体格式如下：
         SourceAddr 为Msg_Communication，则表示通信模块触发，为Msg_Dispatch（调度消息号），
         则表示每分钟调度触发，为C_Msg_Deal_MultiRates表示初始化调用（三种触发处理过程一致）
输出参数: 无
返回参数: 无
调用位置: 初始化，每分钟调度和通信模块触发
备    注: 
*******************************************************************************/
void InF_MultiRates_ParseMessage(Str_Msg_Parameter *pStr_Msg)
{
	uchar8 V_ucTimeInterval = 1;							/*时段*/
	uchar8 V_ucRates = 0;									/*费率号*/
	ushort16 V_usLength, V_usDataEncode = 0;
	uchar8 V_ucTimeZoneNum;									/*时区数*/
	uchar8 V_ucTimeIntervalNum;								/*时段表数*/
	uchar8 V_ucDaySwitchNum;								/*日时段数*/
	uchar8 V_ucRatesNum;									/*费率数*/
	uchar8 V_ucHolidayNum;									/*公共假日数*/
	uchar8 V_ucDisStutas_Char1;								/*特征字1中①②意义*/
	uchar8 V_ucMeterRunChar1;								/*电表运行特征字1缓存*/
	uchar8 V_ucCurrentTime[CLDate_Week_Time];				/*当前时间缓存*/
	uchar8 V_ucDataTemp[CLHolidy_PT_TableFF];				/*数据缓存区*/
	ulong32 V_ulDataCode;
	uchar8 V_uci;
	uchar8 V_ucWeekTemp;									/*星期*/
	uchar8 V_ucRestDayTemp;									/*周休日特征字*/
	uchar8 V_ucRestTimeIntervalTemp;						/*周休日采用日时段表号*/
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	uchar8 V_ucDisTemp[4], V_ucDemTemp[2],V_ucEneTemp;		/*消息参数缓存*/
	uchar8 V_ucTimeChangeFlag = C_TimeNoChange;				/*时段投切标识默认没发生投切*/
	uchar8 V_ucStepStatus = C_Valid, V_ucCurrentStepData[CLCurrent_Ladder_Table];
	uchar8 V_ucA[3], V_ucB[3];								/*zlj新增，用于比较时间时暂存，因为现在时区时段之类的存储次序和之前的相反，比较时间时需倒序*/
	uchar8 V_returnFlag;
	uchar8 V_ucGotoFlag = C_Error;
	
	if ( SF_ParseMessage_MultiRates(pStr_Msg) == C_Error )	/*消息解析错误,直接返回*/
	{
		SV_ucPowerStatus = C_PowerOnPeriod;					/*退出前置电表为有电状态*/
		return;
	}
    
    /*************************读当前费率数***************************/	
    V_usLength = CLRate_Num;
	if (InF_Read_Data(CRate_Num, &V_ucRatesNum, &V_usLength, &V_usDataEncode) != C_OK)
	{
		V_ucRatesNum = C_MaxRatesNum;				
	}
    
	if (C_Meter_Type == C_L_SmartMeter)
	{	
		V_usLength = CLCurrent_Ladder_Table;
		InF_Read_Data(CCurrent_Ladder_Table, V_ucCurrentStepData, &V_usLength, &V_usDataEncode);				/*读当前套阶梯数据*/

		V_ucStepStatus = PF_Is_Buf_AllFixedData(V_ucCurrentStepData, 0x00, CLCurrent_Ladder_Table_LadNum);		/*判断阶梯值是否为全0,zlj改用公共函数*/
	}
    
	if (*(pStr_Msg->Parameter) == Pt_ParaMetersChange)
	{
		SF_ParaChangeProcess_MultiRates(V_ucStepStatus, V_ucRatesNum);					/*参数发生改变时做的处理*/
	}
	V_usLength = CL1And2Display;
	InF_Read_Data(C1And2Display, &V_ucMeterRunChar1, &V_usLength, &V_usDataEncode);		/*读特征字1*/
	
	if (V_ucMeterRunChar1 == 0x01)														/*①②表示费率电价*/
	{
		V_ucDisStutas_Char1 = C_DisplayRate;
	}
	else			    /*①②表示时段表套数*/
	{
		V_ucDisStutas_Char1 = C_DisplayTimeInterval;
	}
	V_usLength = CLDate_Time;
	if (InF_Read_Data(CDate_Time, V_ucCurrentTime, &V_usLength, &V_usDataEncode) != C_OK)			/*读当前时间,最低位为秒,7字节*/
	{
		SV_ucPowerStatus = C_PowerOnPeriod;															/*退出前置电表为有电状态*/
		return;		/*读时间不成功,直接退出*/
	}
    
/*************************各类型套数判断***************************/	
	if (C_Meter_Type == C_L_SmartMeter)																/*本地表才处理费率电价与阶梯电价*/
	{
        if (V_ucRatesNum != 0)
        {
            SF_JudgeRateSwitch_MultiRates(V_ucDisStutas_Char1, V_ucCurrentTime);					/*费率电价判断,当前时间从分开始*/
        }
        
		SF_JudgeStepSwitch_MultiRates(V_ucCurrentTime, V_ucCurrentStepData, V_ucStepStatus);		/*阶梯电价判断*/
	}
    
    if (V_ucRatesNum != 0)
    {
        SF_JudgeTimeZoneSwitch_MultiRates(V_ucCurrentTime, &V_ucTimeChangeFlag);						        /*时区表套数判断*/
	
        SF_JudgeTimeIntervalSwitch_MultiRates(V_ucDisStutas_Char1, V_ucCurrentTime, &V_ucTimeChangeFlag);		/*时段表套数判断*/

    /*************************数据合法性判断***************************/	
        V_usLength = CLYear_Zone_Num;
        V_returnFlag = InF_Read_Data(CYear_Zone_Num, &V_ucTimeZoneNum, &V_usLength, &V_usDataEncode);			/*读时区数*/
        if ( (V_returnFlag != C_OK) || (V_ucTimeZoneNum == 0) || (V_ucTimeZoneNum > C_MaxYearTZNum) )			/*非法默认为1*/
        {
            V_ucTimeZoneNum = 1;
        }
        
        V_usLength = CLDay_Table_Num;
        V_returnFlag = InF_Read_Data(CDay_Table_Num, &V_ucTimeIntervalNum, &V_usLength, &V_usDataEncode);       /*读时段表数*/
        if ( (V_returnFlag != C_OK) || (V_ucTimeIntervalNum == 0) || (V_ucTimeIntervalNum > C_MaxDayPTTabNum) )	/*非法默认为1*/
        {
            V_ucTimeIntervalNum = 1;
        }
        
        V_usLength = CLDay_Time_Num;
        V_returnFlag = InF_Read_Data(CDay_Time_Num, &V_ucDaySwitchNum, &V_usLength, &V_usDataEncode);			/*读时段数*/
        if ( (V_returnFlag != C_OK) || (V_ucDaySwitchNum == 0) || (V_ucDaySwitchNum > C_MaxDayPTNum) )			/*非法默认为1*/
        {
            V_ucDaySwitchNum = 1;
        }
        
        V_usLength = CLHoliday_Num;							/*zlj长度改为1字节*/
        V_returnFlag = InF_Read_Data(CHoliday_Num, &V_ucHolidayNum, &V_usLength, &V_usDataEncode);	/*读公共假日数*/

        if ( (V_returnFlag != C_OK) || (V_ucHolidayNum > C_MaxHolidayNum) )							/*非法默认为1*/
        {
            V_ucHolidayNum = 0;
        }
        
    /****************************节假日判断**********************************/
        if (V_ucHolidayNum != 0)		/*zlj之前最大254个节假日，无法一次处理完，分段处理的，现在改为最大20个节假日，可以一次处理完*/
        {
            V_usLength = CLHolidy_PT_TableFF;
            if (InF_Read_Data(CHolidy_PT_TableFF, V_ucDataTemp, &V_usLength, &V_usDataEncode) == C_OK)
            {
                for (V_uci = 0; V_uci < V_ucHolidayNum; V_uci++)
                {
                    if ( (V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 4] == 0xFF)
                      && (V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 3] == 0xFF)
                      && (V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 1] != 0xFF) )               /*年无效,为当前年*//*zlj改为日期在低字节，日时段表号在高字节*/ 
                    {
                        V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 4] = V_ucCurrentTime[6];		/*年用当前日期赋值*/
                        V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 3] = V_ucCurrentTime[5];
                        
                        if (V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 2] == 0xFF)				/*年无效且月无效,日有效*/
                        {
                            V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 2] = V_ucCurrentTime[4];
                        }
                    }
                    if (PF_Campare_Data( (V_ucDataTemp + V_uci * CLHolidy_PT_Table1 + 1), &V_ucCurrentTime[C_DayStart], (CLHolidy_PT_Table1 - 1 - 1) ) == C_Equal)	/*判断当天是否节假日*/ /*去掉日时段表号和周*/
                    {
                        if ( (V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 5] > 0) && (V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 5] <= V_ucTimeIntervalNum) )			/*判断采用的时段表号是否有效*/
                        {
                            V_ucTimeInterval = V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 5];
                            V_ucGotoFlag = C_OK;
                            /*goto Judge_TimeInterval;*/		/*跳到时段表判断*/
                        }
                    }
                }
            }
        }
        
    /****************************周休日判断**********************************/
        if (V_ucGotoFlag != C_OK)
        {
            V_ucWeekTemp = PF_WeekCompute(V_ucCurrentTime);
            V_usLength = CLWeek_RestDay;
            if (InF_Read_Data(CWeek_RestDay, &V_ucRestDayTemp, &V_usLength, &V_usDataEncode) == C_OK)				/*读周休日特征字*/
            {
                if ( ( (V_ucRestDayTemp >> V_ucWeekTemp) & 0x01) == 0)												/*表示当天为周休日*/
                {
                    V_usLength = CLWeek_RestDay_DTable;
                    if (InF_Read_Data(CWeek_RestDay_DTable, &V_ucRestTimeIntervalTemp, &V_usLength, &V_usDataEncode) == C_OK)
                    {
                        if ( (V_ucRestTimeIntervalTemp > 0) && (V_ucRestTimeIntervalTemp <= V_ucTimeIntervalNum) )	/*判断采用的时段表号是否有效*/
                        {
                            V_ucTimeInterval = V_ucRestTimeIntervalTemp;
                            /*goto Judge_TimeInterval;*/															/*跳到时段表判断*/
                            V_ucGotoFlag = C_OK;
                        }
                    }
                }
            }
        }
    /****************************时区判断**********************************/
        if (V_ucGotoFlag != C_OK)
        {
            V_usLength = CLFirst_TZone_Data;								/*需读的数据长度*/

            InF_Read_Data(CFirst_TZone_Data, V_ucDataTemp, &V_usLength, &V_usDataEncode);

            /*判断数据是否为全0*/
            memset(&V_ucDataTemp[60], 0x00, 3);
            for (V_uci = (V_ucTimeZoneNum - 1); V_uci > 0; V_uci--)			/*zlj找出有效时区数的个数*/
            {
                if ( (PF_Campare_Data(&V_ucDataTemp[60], &V_ucDataTemp[V_uci * 3], 3) == C_Equal)
                  || (PF_Campare_Data(&V_ucDataTemp[V_uci * 3], &V_ucDataTemp[(V_uci - 1) * 3], 2) == C_Equal) )	/*zlj新程序改为月在低字节，日时段表号在高字节*/
                {
                    V_ucTimeZoneNum--;
                }
                else
                {
                    break;
                }
            }

            /*根据当前时间判断所处时段表*/
            SF_TimeZoneSequence(V_ucDataTemp, V_ucTimeZoneNum);										/*对时区表参数进行排序*/
            if ( (V_ucTimeZoneNum > 0) && (V_ucTimeZoneNum <= C_MaxYearTZNum) )						/*增加时区数合法性判断*/
            {
                PF_OneDataReversed(&V_ucDataTemp[0], &V_ucA[0], 2);									/*zlj新程序改为日在低字节，月在高字节，这里需倒序*/
                PF_OneDataReversed(&V_ucDataTemp[(V_ucTimeZoneNum - 1 ) * 3], &V_ucB[0], 2);

                if ( (PF_Campare_Data(&V_ucCurrentTime[C_Day], &V_ucA[0], 2) == C_LessThan)
                  || (PF_Campare_Data(&V_ucCurrentTime[C_Day], &V_ucB[0], 2) != C_LessThan) )
                {
                    V_ucTimeInterval = V_ucDataTemp[(V_ucTimeZoneNum - 1 ) * 3 + 2];				/*赋值临时时段表号*/
                }
                else
                {
                    for (V_uci = 0; V_uci < (V_ucTimeZoneNum - 1); V_uci++)							/*循环判断当前处于第几个时区*/
                    {
                        PF_OneDataReversed(&V_ucDataTemp[V_uci * 3], &V_ucA[0], 2);					/*zlj改为日在低字节，月在高字节*/
                        PF_OneDataReversed(&V_ucDataTemp[(V_uci + 1) * 3], &V_ucB[0], 2);
                        if ( (PF_Campare_Data(&V_ucCurrentTime[C_Day], &V_ucA[0], 2) != C_LessThan)
                          && (PF_Campare_Data(&V_ucCurrentTime[C_Day], &V_ucB[0], 2) == C_LessThan) )
                        {
                            V_ucTimeInterval = V_ucDataTemp[V_uci * 3 + 2];							/*赋值临时时段表号*/
                            break;
                        }
                    }
                }
            }
            if ( (V_ucTimeInterval == 0) || (V_ucTimeInterval > V_ucTimeIntervalNum) )				/*时段表非法,默认为1*/
            {
                V_ucTimeInterval = 1;
            }	
        }
    /****************************时段判断**********************************/
    /*Judge_TimeInterval:*/
        V_ucWrSafeFlag |= C_W_SafeFlag_2;
        
        V_usLength = CLFirst_TZone_1PT_Data;				/*需读的数据长度*/
        
        V_ulDataCode = (CFirst_TZone_1PT_Data & 0xFFFFFF00);
        V_ulDataCode = V_ulDataCode | V_ucTimeInterval;		/*根据临时时段表号读取数据*/
            
        InF_Read_Data(V_ulDataCode, V_ucDataTemp, &V_usLength, &V_usDataEncode);
        
        if (SV_ucTimeIntSetStatus != V_ucTimeInterval)		/*判断时段表是否切换*/
        {
            SV_ucTimeIntSetStatus = V_ucTimeInterval;
            
            V_ucTimeChangeFlag = C_TimeChange;				/*置时段投切有效*/
        }
        /*判断数据是否为全0*/
        memset(&V_ucDataTemp[60], 0x00, 3);
        for (V_uci = (V_ucDaySwitchNum - 1); V_uci > 0; V_uci--)
        {
            if ( (PF_Campare_Data(&V_ucDataTemp[60], &V_ucDataTemp[V_uci * 3], 3) == C_Equal)
              || (PF_Campare_Data(&V_ucDataTemp[V_uci * 3], &V_ucDataTemp[(V_uci - 1) * 3], 2) == C_Equal) )	/*zlj新程序时在低字节，费率号在高字节*/
            {
                V_ucDaySwitchNum--;
            }
            else
            {
                break;
            }
        }
        SF_JudgeTimeInterval_RateNum(V_ucDataTemp, V_ucDaySwitchNum);
        
        /*根据当前时间判断所处时段*/
        if ( (V_ucDaySwitchNum > 0) && (V_ucDaySwitchNum <= C_MaxDayPTNum) )			/*增加时段数合法性判断*/
        {
            PF_OneDataReversed(&V_ucDataTemp[0], &V_ucA[0], 2);							/*zlj新程序时在低字节，费率号在高字节，倒序改为分在低字节，时在高字节*/
            PF_OneDataReversed(&V_ucDataTemp[(V_ucDaySwitchNum - 1 ) * 3], &V_ucB[0], 2);
            
            if ( (PF_Campare_Data(&V_ucCurrentTime[C_Minute], &V_ucA[0], 2) == C_LessThan)
              || (PF_Campare_Data(&V_ucCurrentTime[C_Minute], &V_ucB[0], 2) != C_LessThan) )
            {
                V_ucRates = V_ucDataTemp[(V_ucDaySwitchNum - 1) * 3 + 2];				/*赋值临时费率号*/
                
                if (SV_ucTimeIntervalStatus != (V_uci + 1) )
                {	
                    SV_ucTimeIntervalStatus = (V_uci + 1);								/*赋值内部静态变量，与时段数相同*/
                    
                    V_ucTimeChangeFlag = C_TimeChange;									/*置时段投切有效*/
                }
            }
            else
            {
                for (V_uci = 0; V_uci < (V_ucDaySwitchNum - 1); V_uci++)				/*循环判断当前的费率号*/
                {
                    PF_OneDataReversed(&V_ucDataTemp[V_uci * 3], &V_ucA[0], 2);			/*zlj改为分在低字节，时在高字节*/
                    PF_OneDataReversed(&V_ucDataTemp[(V_uci + 1) * 3], &V_ucB[0], 2);
            
                    if ( (PF_Campare_Data(&V_ucCurrentTime[C_Minute], &V_ucA[0], 2) != C_LessThan)
                      && (PF_Campare_Data(&V_ucCurrentTime[C_Minute], &V_ucB[0], 2) == C_LessThan) )
                    {
                        V_ucRates = V_ucDataTemp[V_uci * 3 + 2];						/*赋值临时费率号*/
                        
                        if (SV_ucTimeIntervalStatus != (V_uci + 1) )					/*(V_uci+1)表示所处的时段号*/
                        {	
                            SV_ucTimeIntervalStatus = (V_uci + 1);						/*赋值内部静态变量-时段号*/
                            
                            V_ucTimeChangeFlag = C_TimeChange;							/*置时段投切有效*/
                        }
                        break;
                    }
                }
            }
        }
        
        if ( (V_ucRates == 0) || (V_ucRates > V_ucRatesNum) )	/*费率号非法,默认为尖*/
        {
            V_ucRates = 1;
        }
    }

    if (C_Meter_Type == C_L_SmartMeter)						/*本地表才处理费率电价*/
    {
        /*消息参数配置-电能*/
        V_ucEneTemp = Pt_RatePrice;
        SF_MsgProcess(&V_ucEneTemp, Pt_RatePrice_Len + 1, C_Msg_EnergyMetering);
    }

	V_usLength = CLCurr_Rate_No;
	V_returnFlag = InF_Read_Data(CCurr_Rate_No, V_ucDataTemp, &V_usLength, &V_usDataEncode);					/*读取当前费率*/
	if (V_returnFlag != C_OK)
	{
		V_ucDataTemp[0] = 1;
	}
	if (V_ucRates != V_ucDataTemp[0])						/*费率发生变化*/
	{
		V_ucWrSafeFlag = C_W_SafeFlag;
		
		InF_Write_Data(C_Msg_Deal_MultiRates, CCurr_Rate_No, &V_ucRates, CLCurr_Rate_No, V_ucWrSafeFlag);		/*写当前费率*/
		/*消息参数配置-显示*/
		V_ucDisTemp[0] = Pt_DisplayStatus;
		if (V_ucRates == 0)
		{
			V_ucDisTemp[1] = C_TSign | C_NotDisplay;			/*不显示费率T*/
		}
		else
		{
			V_ucDisTemp[1] = C_TSign | C_AlwaysDisplay;			/*显示费率T*/
		}
		V_ucDisTemp[2] = 0xFF;
		V_ucDisTemp[3] = 0xFF;
		SF_MsgProcess(V_ucDisTemp, (Pt_DisplayStatus_Len + 1), C_Msg_Display);
        
		/*消息参数配置-需量*/
		V_ucDemTemp[0] = Pt_DemandStatus;
		V_ucDemTemp[1] = C_RatesChanged;
		SF_MsgProcess(V_ucDemTemp, (Pt_DemandStatus_Len + 1), C_Msg_DemandMetering);
	}
    
	if (V_ucTimeChangeFlag == C_TimeChange)					/*时段发生投切*/
	{
		InF_MultiFunctionOutput(C_RatePulse);				/*调用IO驱动接口函数,发送时段投切信号*/
	}
	SV_ucPowerStatus = C_PowerOnPeriod;
}


/*******************************************************************************
函数原型: InF_Deal_MultiRates(void)
功能描述: 费率判断初始化处理
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 电表初始化调用
备    注: 
*******************************************************************************/
void InF_Deal_MultiRates(void)
{
	uchar8 V_ucMeterRunChar1;			            /*电表运行特征字1缓存*/
	uchar8 V_ucReturnTemp, V_ucDataTemp, V_ucDemTemp[2];
	uchar8 V_ucRatesNum;
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	uchar8 V_ucRateNum_Msg[4];			            /*显示参数缓存*/
	uchar8 V_ucRatePr_Msg[8];
	uchar8 V_ucStep_Msg[8];
	uchar8 V_ucTimeInt_Msg[8];
	uchar8 V_ucRateTemp = Pt_Initialization;		/*费率判断参数缓存*/
	uchar8 V_ucCurrentStepData[CLCurrent_Ladder_Table];
	uchar8 V_ucMeterRunStatus3[5];					/*电表运行状态字3缓存*/
	ushort16 V_usLength, V_usDataEncode = 0;
    
	SV_ucPowerStatus = C_PowerUpEdge;				/*上电初始化时,置为上电沿标志*/
	
	V_usLength = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, V_ucMeterRunStatus3, &V_usLength, &V_usDataEncode);	/*读状态字3*/
	
	V_usLength = CL1And2Display;
	InF_Read_Data(C1And2Display, &V_ucMeterRunChar1, &V_usLength, &V_usDataEncode);			/*读特征字1*/
	
	V_ucWrSafeFlag |= C_W_SafeFlag_2;	
	V_ucMeterRunStatus3[C_LowByte] &= C_FirstTimeZone;										/*状态字3默认第一套*/
	V_ucMeterRunStatus3[C_LowByte] &= C_FirstTimeInterval;
	V_ucWrSafeFlag |= C_W_SafeFlag_3;
	InF_Write_Data(C_Msg_Deal_MultiRates, CMeter_Work_State3, V_ucMeterRunStatus3, CLMeter_Work_State3, V_ucWrSafeFlag);		/*写状态字3*/

	V_usLength = CLCurr_Rate_No;
	V_ucReturnTemp = InF_Read_Data(CCurr_Rate_No, &V_ucDataTemp, &V_usLength, &V_usDataEncode);									/*读取当前费率*/
	
    V_usLength = CLRate_Num;
	if (InF_Read_Data(CRate_Num, &V_ucRatesNum, &V_usLength, &V_usDataEncode) != C_OK)
	{
		V_ucRatesNum = C_MaxRatesNum;				
	}
	
	if ( (V_ucReturnTemp != C_OK) || (V_ucDataTemp > V_ucRatesNum) )
	{
		V_ucDataTemp = 1;																	/*读数据错误或者数据不合法，默认为尖*/
		
		V_ucWrSafeFlag = C_W_SafeFlag;
		InF_Write_Data(C_Msg_Deal_MultiRates, CCurr_Rate_No, &V_ucDataTemp, CLCurr_Rate_No, V_ucWrSafeFlag);					/*写当前费率*/
	}

    V_ucRateNum_Msg[0] = Pt_DisplayStatus;
    if (V_ucRatesNum == 0)  /*去费率，不显示T*/
    {
        V_ucRateNum_Msg[1] = C_TSign | C_NotDisplay;										/*赋值显示标识*/
    }
    else
    {
        V_ucRateNum_Msg[1] = C_TSign | C_AlwaysDisplay;										/*赋值显示标识*/

    }
	V_ucRateNum_Msg[2] = 0xFF;
    V_ucRateNum_Msg[3] = 0xFF;
	SF_MsgProcess(V_ucRateNum_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);				/*触发费率号显示消息*/
	
	if (C_Meter_Type == C_L_SmartMeter)														/*本地表才处理费率和阶梯显示*/
	{
		V_usLength = CLCurrent_Ladder_Table;
		InF_Read_Data(CCurrent_Ladder_Table, V_ucCurrentStepData, &V_usLength, &V_usDataEncode);								/*读当前套阶梯数据*/
		
		if (PF_Is_Buf_AllFixedData(V_ucCurrentStepData, 0x00, CLCurrent_Ladder_Table_LadNum) != C_OK)							/*阶梯值不全为0才电量阶梯符号,zlj改用公共函数*/
		{
			SF_Deal12dig(CChange_Ladder, V_ucStep_Msg);
			SF_SendMsgToDisplay(C_CurrentStep, C_BakStep, V_ucStep_Msg[1], V_ucStep_Msg[5], 2);
		}
		
		if (V_ucMeterRunChar1 == 0x01)					/*①②表示费率电价*/
		{
            if (V_ucRatesNum == 0)                      /*去费率，不显示①②*/
            {
                V_ucRatePr_Msg[1] = C_NotDisplay;	    /*灭当前套费率符号*/
                V_ucRatePr_Msg[5] = C_NotDisplay;		/*灭备用套费率符号*/
            }
            else
            {
				SF_Deal12dig(CChange_Rate, V_ucRatePr_Msg);
            }
			SF_SendMsgToDisplay(C_TimeTable1Sign, C_TimeTable2Sign, V_ucRatePr_Msg[1], V_ucRatePr_Msg[5], 2);
		}	
	}
    
	if (V_ucMeterRunChar1 == 0)							/*①②表示时段套数*/
	{
        if (V_ucRatesNum == 0)                          /*去费率，不显示①②*/
        {
            V_ucRatePr_Msg[1] = C_NotDisplay;	        /*灭当前套费率符号*/
            V_ucRatePr_Msg[5] = C_NotDisplay;		    /*灭备用套费率符号*/
        }
        else
        {
			SF_Deal12dig(CChange_PT_Time, V_ucTimeInt_Msg);
        }
		SF_SendMsgToDisplay(C_TimeTable1Sign, C_TimeTable2Sign, V_ucTimeInt_Msg[1], V_ucTimeInt_Msg[5], 2);
	}
	SF_MsgProcess(&V_ucRateTemp, Pt_Initialization_Len + 1, C_Msg_Deal_MultiRates);			    /*触发费率判断消息*/
    
	/*上电需量初始化时，需要费率模块触发消息*/
	V_ucDemTemp[0] = Pt_DemandStatus;
	V_ucDemTemp[1] = C_RatesChanged;
	SF_MsgProcess(V_ucDemTemp, (Pt_DemandStatus_Len + 1), C_Msg_DemandMetering);
}

/*******************************************************************************
函数原型: void  SF_ParaChangeProcess(uchar8 V_ucStepStatus, uchar8 V_ucRatesNum)
功能描述: 参数发生变化时做的处理
输入参数: V_ucStepStatus-阶梯值若为全0,为C_Valid,否则为C_Invalid,用于判断是否点阶梯符号
         uchar8 V_ucRatesNum：当前费率数
输出参数: 无
返回参数: 无
调用位置: 费率模块
备    注: 
*******************************************************************************/
void SF_ParaChangeProcess_MultiRates(uchar8 V_ucStepStatus, uchar8 V_ucRatesNum)
{
	ushort16 V_usLength, V_usDataEncode = 0; 
	uchar8 V_ucMeterRunChar1;
	uchar8 V_ucStep_Msg[8], V_ucTimeInt_Msg[8];

    if (V_ucRatesNum == 0)                                      /*去费率*/
    {
        V_ucTimeInt_Msg[1] = C_NotDisplay;
        V_ucTimeInt_Msg[5] = C_NotDisplay;
    }
    else
    {
        V_usLength = CL1And2Display;
        InF_Read_Data(C1And2Display, &V_ucMeterRunChar1, &V_usLength, &V_usDataEncode);				/*读特征字1*/

        if (V_ucMeterRunChar1 == 0)								/*①②表示时段套数*/
        {
			SF_Deal12dig(CChange_PT_Time, V_ucTimeInt_Msg);  
        }
        else
        {
            if (C_Meter_Type == C_L_SmartMeter)					/*本地表需判断费率电价*/
            {
				SF_Deal12dig(CChange_Rate, V_ucTimeInt_Msg); 
            }
            else												/*非本地表,灭①②*/
            {
                V_ucTimeInt_Msg[1] = C_NotDisplay;
                V_ucTimeInt_Msg[5] = C_NotDisplay;
            }
        }
    }
	SF_SendMsgToDisplay(C_TimeTable1Sign, C_TimeTable2Sign, V_ucTimeInt_Msg[1], V_ucTimeInt_Msg[5], 2);

	/*本地表才处理阶梯显示*/
	if (C_Meter_Type == C_L_SmartMeter)
	{
		if (V_ucStepStatus != C_OK)
		{
			SF_Deal12dig(CChange_Ladder, V_ucStep_Msg);
		}
		else		/*阶梯值全为0,则不现实阶梯套数符号*/
		{
			V_ucStep_Msg[1] = C_NotDisplay;					/*灭当前套阶梯符号*/
			V_ucStep_Msg[5] = C_NotDisplay;					/*灭备用套阶梯符号*/
		}
		SF_SendMsgToDisplay(C_CurrentStep, C_BakStep, V_ucStep_Msg[1], V_ucStep_Msg[5], 2);
	}
}

/*******************************************************************************
函数原型: void  SF_JudgeStepSwitch_MultiRates(uchar8 *pV_ucCurrentTime, uchar8 *pV_ucCurrentStepData, uchar8 V_ucStepStatus)
功能描述: 阶梯电价切换判断	
输入参数: pV_ucCurrentTime-当前时间
         *pV_ucCurrentStepData-当前套阶梯数据首地址
         V_ucStepStatus-阶梯值若为全0,为C_Valid,否则为C_Invalid,用于判断是否点阶梯符号
输出参数: 无
返回参数: 无
调用位置: 费率模块
备    注: 
*******************************************************************************/
void SF_JudgeStepSwitch_MultiRates(uchar8 *pV_ucCurrentTime, uchar8 *pV_ucCurrentStepData, uchar8 V_ucStepStatus)
{
	uchar8 V_ucSwitchTime[CLChange_Ladder];						/*切换时间*/
	uchar8 V_ucBackupStepData[CLCurrent_Ladder_Table];			/*当前和备用套数据缓存区*/
	ushort16 V_ucStepDataLength = CLCurrent_Ladder_Table;		/*阶梯数据长度*/
	uchar8 V_ucSwitchStatus;									/*切换状态*/
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	uchar8 V_ucDisTemp[10], V_ucReturnFlag = C_OK;
    ushort16 V_usDataEncode = 0;
	
	V_ucSwitchStatus = SF_JudgeSwitchTime_MultiRates(CChange_Ladder, &pV_ucCurrentTime[C_MinStart], V_ucSwitchTime);						/*判断是否发生切换*/

	if (V_ucSwitchStatus == C_SwitchValid)
	{
		V_ucWrSafeFlag |= C_W_SafeFlag_2;
		/*读备用套阶梯数据*/
		if (InF_Read_Data(CBackUp_Ladder_Table, V_ucBackupStepData, &V_ucStepDataLength, &V_usDataEncode) != C_OK)
		{
			if (InF_Read_Data(CBackUp_Ladder_Table, V_ucBackupStepData, &V_ucStepDataLength, &V_usDataEncode) != C_OK)
			{
				V_ucReturnFlag = C_Error;
			}
		}
		if (V_ucReturnFlag == C_OK)								/*读备用套成功了，才将数据写入当前套,并进行年/月阶梯切换处理*/
		{
			V_ucWrSafeFlag |= C_W_SafeFlag_3;
			InF_Write_Data(C_Msg_Deal_MultiRates, CCurrent_Ladder_Table, V_ucBackupStepData, CLCurrent_Ladder_Table, V_ucWrSafeFlag);		/*将备用套数据写入当前套*/
			
			SF_StepTypeProcess(pV_ucCurrentStepData + CLCurrent_Ladder_Table_LadNum + CLCurrent_Ladder_Table_LadPri, V_ucBackupStepData + CLBackUp_Ladder_Table_LadNum + CLBackUp_Ladder_Table_LadPri, &V_ucSwitchTime[1]);		/*判断两套数据阶梯类型,并进行相关处理,zlj宏定义改用DILenth.h里的宏定义，不使用自己单独定义的宏定义*/
		}

		InF_FreezeSwitch(CChange_Ladder, pV_ucCurrentTime);		/*进行阶梯切换约定冻结*/

		if (PF_Is_Buf_AllFixedData(V_ucBackupStepData, 0x00, CLCurrent_Ladder_Table_LadNum) != C_OK)										/*阶梯值不全为0才点阶梯符号,zlj改用公共函数*/
		{
			V_ucDisTemp[1] = C_AlwaysDisplay;
		}
		else
		{
			V_ucDisTemp[1] = C_NotDisplay;
		}
		SF_SendMsgToDisplay(C_CurrentStep, C_BakStep, V_ucDisTemp[1], C_NotDisplay, 2);
	}
	else if ( (V_ucSwitchStatus == C_SwitchInvalid) && (V_ucStepStatus != C_OK) )
	{
		/*点亮当前和备用套阶梯符号*/
		SF_SendMsgToDisplay(C_CurrentStep, C_BakStep, C_AlwaysDisplay, C_AlwaysDisplay, 2);
	}
}

/*******************************************************************************
函数原型: void  SF_JudgeRateSwitch_MultiRates(uchar8 V_ucDisplayType, uchar8 *pV_ucCurrentTime)
功能描述: 费率电价切换判断
输入参数: V_ucDisplayType-液晶①②符号的表示意义，用于触发显示时判断
         pV_ucCurrentTime-当前时间	
输出参数: 无
返回参数: 无
调用位置: 费率模块
备    注: 
*******************************************************************************/
void SF_JudgeRateSwitch_MultiRates(uchar8 V_ucDisplayType, uchar8 *pV_ucCurrentTime)
{
	uchar8 V_ucSwitchTime[CLChange_Rate];					/*切换时间缓存*/
	uchar8 V_ucBackupRateData[CLBackUp_RateFF_Price];		/*备用套数据缓存区*/
	ushort16 V_usRateDataLength;							/*费率电价数据长度*/
	uchar8 V_ucSwitchStatus;								/*切换状态*/
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	uchar8 V_ucReturnFlag = C_Error;
	uchar8 V_uci;
    ushort16 V_usDataEncode = 0;

	V_ucSwitchStatus = SF_JudgeSwitchTime_MultiRates(CChange_Rate, &pV_ucCurrentTime[C_MinStart], V_ucSwitchTime);		/*判断是否发生切换*/
	
	if (V_ucSwitchStatus == C_SwitchValid)
	{
		V_ucWrSafeFlag |= C_W_SafeFlag_2;
		for (V_uci = 0; V_uci < C_MaxRatesNum; V_uci++)
		{
			V_usRateDataLength = CLBackUp_Rate1_Price;
			if (InF_Read_Data( (CBackUp_Rate1_Price + V_uci * C_RateOADChange_Flag), &V_ucBackupRateData[CLBackUp_Rate1_Price * V_uci], &V_usRateDataLength, &V_usDataEncode) != C_OK)
			{
				break;
			}
		}
		if (V_uci == C_MaxRatesNum)
		{
			V_ucReturnFlag = C_OK;
		}
		
		if (V_ucReturnFlag == C_OK)							/*读备用套成功了，才将数据写入当前套*/
		{
			V_usRateDataLength = CLBackUp_RateFF_Price;
			
			V_ucWrSafeFlag |= C_W_SafeFlag_3;
			InF_Write_Data(C_Msg_Deal_MultiRates, CCurrent_RateFF_Price, V_ucBackupRateData, V_usRateDataLength, V_ucWrSafeFlag);		/*将备用套数据写入当前套*/
		}
		InF_FreezeSwitch(CChange_Rate, pV_ucCurrentTime);	/*进行费率切换约定冻结*/

		if (V_ucDisplayType == C_DisplayRate)
		{
			/*点亮当前套费率电价符号*/
			SF_SendMsgToDisplay(C_TimeTable1Sign, C_TimeTable2Sign, C_AlwaysDisplay, C_NotDisplay,2);
		}
	}
	else if ( (V_ucSwitchStatus == C_SwitchInvalid) && (V_ucDisplayType == C_DisplayRate) )
	{
			/*点亮当前套费率电价符号*/
		SF_SendMsgToDisplay(C_TimeTable1Sign, C_TimeTable2Sign, C_AlwaysDisplay, C_AlwaysDisplay, 2);
	}
}	

/*******************************************************************************
函数原型: uchar8  SF_JudgeTimeZoneSwitch_MultiRates(uchar8 *pV_ucCurrentTime, uchar8 *pV_ucChangeFlag)
功能描述: 时区表切换判断
输入参数: pV_ucCurrentTime-当前时间,date_time_s格式
         pV_ucChangeFlag-时段投切标识,用于判断是否进行了时段投切		
输出参数: pV_ucChangeFlag-时段投切标识,若时区表切换,则置为C_TimeChange
返回参数: 当前所处时区表套数  
调用位置: 费率模块
备    注: 
*******************************************************************************/
void SF_JudgeTimeZoneSwitch_MultiRates(uchar8 *pV_ucCurrentTime, uchar8 *pV_ucChangeFlag)
{
	uchar8 V_ucSwitchTime[CLChange_TZ_Time];
	uchar8 V_ucSwitchStatus;		/*切换状态*/
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	ushort16 V_usLength, V_usDataEncode = 0;
	uchar8 V_ucSec_TZone_Data[CLSec_TZone_Data];
	
	
	V_ucSwitchStatus = SF_JudgeSwitchTime_MultiRates(CChange_TZ_Time, &pV_ucCurrentTime[C_MinStart], V_ucSwitchTime);			/*判断是否发生切换*/
	
	V_ucWrSafeFlag |= C_W_SafeFlag_2;
	
	if (V_ucSwitchStatus == C_SwitchValid)		/*切换有效*/
	{
		*pV_ucChangeFlag = C_TimeChange;		/*置时段投切有效*/
		V_ucWrSafeFlag |= C_W_SafeFlag_3;
		
		V_usLength = CLSec_TZone_Data;
		if (InF_Read_Data(CSec_TZone_Data, V_ucSec_TZone_Data, &V_usLength, &V_usDataEncode) == C_OK)							/*备用套第1日时段表*/
		{
			InF_Write_Data(C_Msg_Deal_MultiRates, CFirst_TZone_Data, V_ucSec_TZone_Data, CLFirst_TZone_Data, V_ucWrSafeFlag);	/*覆盖当前套*/
			
		}
		InF_FreezeSwitch(CChange_TZ_Time, pV_ucCurrentTime);																	/*进行时区表切换约定冻结*/
	}
}

/*******************************************************************************
函数原型: void SF_JudgeTimeIntervalSwitch_MultiRates(uchar8 V_ucDisplayType, uchar8 *pV_ucCurrentTime, uchar8 *pV_ucChangeFlag)
功能描述: 时段表切换判断
输入参数: V_ucDisplayType-当前时间,5字节,格式YYMMDDhhmm
         pV_ucCurrentTime-液晶①②符号的表示意义，用于触发显示时判断	
         pV_ucChangeFlag-时段投切标识,用于判断是否进行了时段投切	
输出参数: pV_ucChangeFlag-时段投切标识,时段表发生切换,则置为C_TimeChange
返回参数: 当前所处时段表套数
调用位置: 费率模块
备    注: 
*******************************************************************************/
void SF_JudgeTimeIntervalSwitch_MultiRates(uchar8 V_ucDisplayType, uchar8 *pV_ucCurrentTime, uchar8 *pV_ucChangeFlag)
{
	uchar8 V_ucSwitchTime[CLChange_TZ_Time], V_uci;
	uchar8 V_ucSwitchStatus;		/*切换状态*/
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	ushort16 V_usLength, V_usDataEncode = 0;
	uchar8 V_ucSec_TZone_PT_Data[CLSec_TZone_1PT_Data];
	

	V_ucSwitchStatus = SF_JudgeSwitchTime_MultiRates(CChange_PT_Time, &pV_ucCurrentTime[C_MinStart], V_ucSwitchTime);									/*判断是否发生切换*/
	
	V_ucWrSafeFlag |= C_W_SafeFlag_2;
	
	if (V_ucSwitchStatus == C_SwitchValid)							/*切换有效*/
	{
		*pV_ucChangeFlag = C_TimeChange;							/*置时段投切有效*/
		V_ucWrSafeFlag |= C_W_SafeFlag_3;
		
		for (V_uci = 0; V_uci < C_MaxDayPTTabNum; V_uci++)
		{
			V_usLength = CLSec_TZone_1PT_Data;
			if (InF_Read_Data(CSec_TZone_1PT_Data + V_uci, V_ucSec_TZone_PT_Data, &V_usLength, &V_usDataEncode) == C_OK)								/*备用套第1日时段表*/
			{
				InF_Write_Data(C_Msg_Deal_MultiRates, CFirst_TZone_1PT_Data + V_uci, V_ucSec_TZone_PT_Data, CLFirst_TZone_1PT_Data, V_ucWrSafeFlag);	/*覆盖当前套*/
				
			}
		}

		InF_FreezeSwitch(CChange_PT_Time, pV_ucCurrentTime);		/*进行时段表切换约定冻结*/

		if (V_ucDisplayType == C_DisplayTimeInterval)				/*①②表示时段表*/
		{
			/*点亮时段表套数对应的显示符号*/
			SF_SendMsgToDisplay(C_TimeTable2Sign, C_TimeTable2Sign, C_AlwaysDisplay, C_NotDisplay, 2);
		}
	}
	return;
}
/*******************************************************************************
函数原型: void SF_StepTypeProcess(uchar8 *pV_ucOldDate, uchar8 *pV_ucNewDate, uchar8 *pV_ucSettlementTime)
功能描述: 年/月阶梯切换判断
输入参数: pV_ucOldDate指向电表原执行的年结算日数据首地址,pV_ucNewDate新设置阶梯数据首地址,
         *pV_ucSettlementTime时间地址,用于结算时传给结算模块,6字节(年月日时分秒)
输出参数: 无
返回参数: 无
调用位置: 用于对当前阶梯数据修改时调用
备    注: 用于判断的数据长度为12字节
          根据对两块年结算日数据的有效性判断，用于年/月阶梯间切换的结算消息处理
*******************************************************************************/
void SF_StepTypeProcess(uchar8 *pV_ucOldDate, uchar8 *pV_ucNewDate, uchar8 *pV_ucSettlementTime)
{
	uchar8 V_ucOldValidNum = 0;
	uchar8 V_ucNewValidNum = 0;						/*存原/新数据有效个数*/
	uchar8 V_uci, V_ucDataTemp[10];
	uchar8 V_ucCurrentTime[CLDate_Week_Time];		/*zlj改为data_time_s数据格式*/
	uchar8 V_ucA[CLDate_Week_Time];					/*zlj存储倒序后的月日时*/
	ushort16 V_usLength, V_usDataEncode = 0;
    
	/*消息参数配置*/
	V_ucDataTemp[0] = Pt_StepSwitchFlag;
	if (SV_ucPowerStatus == C_PowerOnPeriod)		/*有电期间,结算为当前时间*/
	{
		V_usLength = CLDate_Time;
		if (InF_Read_Data(CDate_Time, V_ucCurrentTime, &V_usLength, &V_usDataEncode) == C_OK)			/*zlj，改为读698OAD的时间*/
		{
			PF_CopyDataBytes(&V_ucCurrentTime[C_MinStart], &V_ucDataTemp[2], (CLDate_Week_Time - 1) );	/*zlj，改成年月日时分6字节*/
		}
		else
		{
			PF_CopyDataBytes(pV_ucSettlementTime, &V_ucDataTemp[2], (CLDate_Week_Time - 1) );
		}
	}
	else
	{
		PF_CopyDataBytes(pV_ucSettlementTime, &V_ucDataTemp[2], (CLDate_Week_Time - 1) );
	}

	for (V_uci = 0; V_uci < C_SettlementNum; V_uci ++)                                                  /*判断两块数据中的结算日有效个数*/
	{
		PF_OneDataReversed(pV_ucOldDate + (C_SettlementLength_One * V_uci), &V_ucA[C_HourStart], C_SettlementLength_One);
        
		if (PF_DataTimeActive_698( &V_ucA[C_HourStart], C_HourStart, C_SettlementLength_One) == C_OK)	/*zlj改用698格式时间判断*/
		{
			V_ucOldValidNum++;
		}
        
		PF_OneDataReversed( (pV_ucNewDate + (C_SettlementLength_One * V_uci) ), &V_ucA[C_HourStart], C_SettlementLength_One);

		if (PF_DataTimeActive_698( &V_ucA[C_HourStart], C_HourStart, C_SettlementLength_One) == C_OK)	/*zlj改用698格式时间判断*/
		{
			V_ucNewValidNum++;
		}
	}

	if (V_ucOldValidNum != V_ucNewValidNum)
	{
		V_ucDataTemp[1] = C_Step_SetttleChange;
		SF_MsgProcess(V_ucDataTemp, (Pt_StepSwitchFlag_Len + 1), C_Msg_SettleAccounts);
	}
	else
	{
		for (V_uci = CLCurrent_Ladder_Table_LadSett; V_uci > 0; V_uci--)								/*zlj宏定义改用DILenth.h里的宏定义，不采用自己单独定义的宏定义*/
		{
			if ( ( (*(pV_ucOldDate + V_uci - 1) == 99) || (*(pV_ucOldDate + V_uci - 1) == 0xFF) )
              && ( (*(pV_ucNewDate + V_uci - 1) == 99) || (*(pV_ucNewDate + V_uci - 1) == 0xFF) ) )		/*新旧阶梯表参数均为99orFF*/  
			{
				continue;
			}
			else if ( (*(pV_ucOldDate + V_uci - 1) ) != (*(pV_ucNewDate + V_uci - 1) ) )		        /*不等直接发送阶梯结算冻结消息*/
			{
				V_ucDataTemp[1] = C_Step_SetttleChange;
				SF_MsgProcess(V_ucDataTemp, (Pt_StepSwitchFlag_Len + 1), C_Msg_SettleAccounts);
				break;
			}
			else
			{
				;					/*继续判断*/
			}
		}
	}

#if 0 
	if ( OldValidNum == 0 )			/*原年结算日无效*/
	{
		if ( NewValidNum != 0 )		/*月阶梯切年阶梯*/
		{
			V_ucDataTemp[1] = C_Step_MToY;
			SF_MsgProcess(V_ucDataTemp, (Pt_StepSwitchFlag_Len + 1), C_Msg_SettleAccounts);
		}
	}
	else							/*原年结算日有效*/
	{
		if (NewValidNum == 0)		/*年阶梯切月阶梯*/
		{
			V_ucDataTemp[1] = C_Step_YToM;
			SF_MsgProcess(V_ucDataTemp, (Pt_StepSwitchFlag_Len + 1), C_Msg_SettleAccounts);
		}
		else if (OldValidNum == NewValidNum)
		{
			for (i = 0; i < C_SettlementLength_T; i ++)
			{
				if (*(OldDate + i) != *(NewDate + i) )		/*若前后年结算日数据不一致,则年阶梯切年阶梯*/
				{
					V_ucDataTemp[1] = C_Step_YToY;
					SF_MsgProcess(V_ucDataTemp, Pt_StepSwitchFlag_Len + 1, C_Msg_SettleAccounts);
					break;
				}
			}
		}
		else
		{
			V_ucDataTemp[1] = C_Step_YToY;
			SF_MsgProcess(V_ucDataTemp, Pt_StepSwitchFlag_Len + 1, C_Msg_SettleAccounts);
		}
	}	
#endif
	
}

/*******************************************************************************
函数原型: uchar8 SF_JudgeSwitchTime_MultiRates(ulong32 V_ulSwitchTimeID, uchar8 *pV_ucCurrentTime, uchar8 *pV_ucSwitchTimeTemp)
功能描述: 拿切换时间和当前时间比较,判断是否发生切换	
输入参数: V_ulSwitchTimeID –所需判断切换时间的标识码,pV_ucCurrentTime –当前时间首地址,
         *pV_ucSwitchTimeTemp-寄存器首地址，用于存放输出参数	
输出参数: *pV_ucSwitchTimeTemp-用于输出切换时间，传给冻结和结算模块
返回参数: C_SwitchInvalid–切换无效,C_SwitchValid–切换有效
调用位置: SF_JudgeStepSwitch_MultiRates/SF_JudgeStepSwitch_MultiRates/
         PF_JudgeTimeIntervalSwitch_MultiRates/SF_JudgeStepSwitch_MultiRates
备    注: 
*******************************************************************************/
uchar8 SF_JudgeSwitchTime_MultiRates(ulong32 V_ulSwitchTimeID, uchar8 *pV_ucCurrentTime, uchar8 *pV_ucSwitchTimeTemp)
{
	uchar8 V_ucSwitchTime[CLChange_TZ_Time];		/*切换时间缓存区*/
	uchar8 V_ucResult;
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	uchar8 V_ucReturnTemp;
	ushort16 V_usSwitchTimeLength, V_usDataEncode = 0;
	
	V_usSwitchTimeLength = CLChange_TZ_Time;		/*切换时间长度,4种长度一样,此处取阶梯切换长度的宏*/
	
	V_ucReturnTemp = InF_Read_Data(V_ulSwitchTimeID, pV_ucSwitchTimeTemp, &V_usSwitchTimeLength, &V_usDataEncode);	/*读切换时间*/
	
	if ( (V_ucReturnTemp != C_OK)
      || (PF_DataTimeActive_698(&pV_ucSwitchTimeTemp[1], C_MinStart, (CLChange_TZ_Time - 1) ) != C_OK) )			/*zlj改用698格式时间判断*/
	{
		return C_SwitchTimeErr;																					/*读切换时间失败,返回错误*/
	}
	V_ucResult = PF_Campare_Data(pV_ucCurrentTime, &pV_ucSwitchTimeTemp[1], (CLChange_TZ_Time - 1) );				/*切换时间和当前时间做比较,zlj长度改用宏定义*/
	
	V_ucWrSafeFlag |= C_W_SafeFlag_2;
	
	if (V_ucResult == C_LessThan)		/*当前时间小于切换时间,判切换无效*/
	{
		return C_SwitchInvalid;
	}
	else								/*当前时间大于等于切换时间,切换有效*/
	{
		V_ucSwitchTime[0]= 0xFF;		/*将切换时间清零,返写数据层*/
		memset(&V_ucSwitchTime[1], 0x00, (CLChange_TZ_Time - 1) );
		
		V_ucWrSafeFlag |= C_W_SafeFlag_3;
		InF_Write_Data(C_Msg_Deal_MultiRates, V_ulSwitchTimeID, V_ucSwitchTime, CLChange_TZ_Time, V_ucWrSafeFlag);
		
		return C_SwitchValid;
	}
}

/*******************************************************************************
函数原型: uchar8 SF_MultiRates_ParseMessage(Str_Msg_Parameter *pStr_Msg_Parameter)
功能描述: 费率模块消息处理解析	
输入参数: P_Msg_Parameter –消息结构体
输出参数:  
返回参数: C_OK-消息参数正确,需进行费率判断/C_Error-消息参数错误,无需处理
调用位置: 
备    注:情况1： SourceAddr= 通信。设置与费率有关的参数时触发。
                 DerictAddr = C_Msg_Deal_MultiRates
                 Len = 1
                 数据域：Pt_ParaMetersChange,取值为空
         情况2： SourceAddr= 调度。调度每分钟触发
                 DerictAddr = C_Msg_Deal_MultiRates
                 Len = 2
                数据域：Pt_Dispatch_Timing，取值C_SystemMinChange
        情况3： SourceAddr：费率。上电初始化时触发
                DerictAddr = C_Msg_Deal_MultiRates
                Len = 1
                数据域：Pt_Initialization,取值为空
*******************************************************************************/
uchar8 SF_ParseMessage_MultiRates(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	uchar8 *pV_ucParm;
	 
	if (pStr_Msg_Parameter->PowerFlag != C_PowerOn)		/*掉电时直接返回错误,无需处理*/
	{
		return C_Error;
	}
	/*区分三种情况,根据情况调用分项解析函数*/
	pV_ucParm = pStr_Msg_Parameter->Parameter;
	
	if (*pV_ucParm == Pt_ParaMetersChange)
	{
		if(pStr_Msg_Parameter->Length == (Pt_ParaMetersChange_Len + 1) )
		{
			return C_OK;
		}
	}
	else if (*pV_ucParm == Pt_Dispatch_Timing)
	{
		if (pStr_Msg_Parameter->Length == (Pt_Dispatch_Timing_Len + 1) )
		{
			return C_OK;
		}
	}
	else if (*pV_ucParm == Pt_Initialization)
	{
		if (pStr_Msg_Parameter->Length ==(Pt_Initialization_Len + 1) )
		{
			return C_OK;
		}
	}
	return C_Error;
}

/*******************************************************************************
函数原型: void SF_MsgProcess(uchar8 *pV_ucParm, uchar8 V_ucParmLen, uchar8 V_ucDerictMod)
功能描述: 写消息函数	
输入参数: *pV_ucParm-消息参数中Parameter内容
          V_ucParmLen-消息参数长度
         V_ucDerictMod-目标消息号
输出参数: 无  
返回参数: 无 
调用位置: 
备    注:
*******************************************************************************/
void SF_MsgProcess(uchar8 *pV_ucParm, uchar8 V_ucParmLen, uchar8 V_ucDerictMod)
{
	Str_Msg_Parameter Str_Msg_MultiRates;
	
	Str_Msg_MultiRates.PowerFlag = C_PowerOn;
	Str_Msg_MultiRates.SourceAddr = C_Msg_Deal_MultiRates;
	Str_Msg_MultiRates.DerictAddr = V_ucDerictMod;
	Str_Msg_MultiRates.Length = V_ucParmLen;
	Str_Msg_MultiRates.Parameter = pV_ucParm;

	InF_WriteMessege(&Str_Msg_MultiRates);		/*写消息函数*/
}

/*******************************************************************************
函数原型: void SF_SendMsgToDisplay(uchar8 V_ucMsg1, uchar8 V_ucMsg2, uchar8 V_ucMsg1_Mode, uchar8 V_ucMsg2_Mode, uchar8 V_ucMsgNum)
功能描述: 发消息给显示模块，均为常显模式,最多发送2个消息	
输入参数: V_ucMsg1为消息1，V_ucMsg2为消息2，V_ucMsgNum发送消息个数，当=1时，第二个消息无效
输出参数: 无
返回参数: 无
调用位置: 
备    注:
*******************************************************************************/
void SF_SendMsgToDisplay(uchar8 V_ucMsg1, uchar8 V_ucMsg2, uchar8 V_ucMsg1_Mode, uchar8 V_ucMsg2_Mode, uchar8 V_ucMsgNum)
{
	uchar8 V_ucDisTemp[8];
    
	V_ucDisTemp[0] = Pt_DisplayStatus;
	V_ucDisTemp[1] = (V_ucMsg1 | V_ucMsg1_Mode);
	V_ucDisTemp[2] = 0xFF;
	V_ucDisTemp[3] = 0xFF;
	V_ucDisTemp[4] = Pt_DisplayStatus;
	V_ucDisTemp[5] = (V_ucMsg2 | V_ucMsg2_Mode);
	V_ucDisTemp[6] = 0xFF;
	V_ucDisTemp[7] = 0xFF;
	
	SF_MsgProcess(V_ucDisTemp, (Pt_DisplayStatus_Len + 1) * V_ucMsgNum, C_Msg_Display);
}

/*******************************************************************************
函数原型: void SF_TimeZoneSequence( uchar8 *pV_ucBuf, uchar8 V_ucNum)
功能描述: 时区表、时段表排序排序
输入参数: pV_ucBuf执行时区表暂存buffer首地址，V_ucNum时区表/时段表个数		
输出参数: 排序后的时区表
返回参数: 无
调用位置: 	
备    注:
*******************************************************************************/
void SF_TimeZoneSequence( uchar8 *pV_ucBuf, uchar8 V_ucNum)
{
	uchar8 V_uci, V_ucn;
	uchar8 V_ucBufB[3];
	uchar8 V_ucBF[2], V_ucAF[2];
	if ( V_ucNum < 2 ) 
	{
		return;
	}
	for ( V_ucn = 0; V_ucn < (V_ucNum - 1); V_ucn++ )
	{
		for ( V_uci = 0; V_uci < (V_ucNum - 1 - V_ucn); V_uci++)
		{
			PF_OneDataReversed(&pV_ucBuf[V_uci * 3], &V_ucBF[0], 2);						/*zlj新程序改为月在低字节，日时段表号在高字节，需要修改偏移，再倒序*/
			PF_OneDataReversed(&pV_ucBuf[(V_uci + 1) * 3], &V_ucAF[0], 2);

			if ( PF_Campare_Data( V_ucBF, V_ucAF, 2 ) == C_GreaterThan )					/*前数据 > 后数据*/
			{
				PF_CopyDataBytes( pV_ucBuf + V_uci * 3, V_ucBufB, 3 );						/*复制数据*/
				PF_CopyDataBytes( pV_ucBuf + (V_uci + 1) * 3, pV_ucBuf + V_uci * 3, 3 );	/*复制数据*/
				PF_CopyDataBytes( V_ucBufB, pV_ucBuf + (V_uci + 1) * 3, 3 );				/*复制数据*/
			}
		}
	}
}

/*******************************************************************************
函数原型: void SF_Deal12dig(ulong32 V_ulOAD, uchar8 *pV_ucdata)
功能描述: 处理显示①②
输入参数: ulong32 V_ulOAD：切换时间的OAD	；uchar8 *pV_ucdata：消息缓存
输出参数: pV_ucdata: 处理后的消息缓存
返回参数: 无
调用位置: 	
备    注:
*******************************************************************************/
void SF_Deal12dig(ulong32 V_ulOAD, uchar8 *pV_ucdata)
{
	uchar8 V_ucSwitchTime[CLChange_Rate];
	ushort16 V_usLength, V_usDataEncode = 0;
	
	V_usLength = CLChange_Rate;
	InF_Read_Data(V_ulOAD, V_ucSwitchTime, &V_usLength, &V_usDataEncode);	/*读时间*/

	pV_ucdata[1] = C_AlwaysDisplay;											/*点亮符号*/
	
	if (PF_DataTimeActive_698(&V_ucSwitchTime[C_MinStart], C_MinStart, (CLChange_Rate - C_MinStart) ) == C_OK)
	{
		pV_ucdata[5] = C_AlwaysDisplay;		/*点亮符号*/
	}
	else
	{
		pV_ucdata[5] = C_NotDisplay;		/*灭符号*/
	}
}