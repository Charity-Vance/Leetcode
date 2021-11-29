
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     LCDDrive.c
///*Version:       V1
///*Date:          2017-9-23
///*Description:   外部LCD驱动芯片的驱动文件
///*Function List: 
///*****************************************************************************************///
///*History1:      第1次修改
///*内容1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*内容2. Date:
///*   	   Author:
///*       Modification:
		///*********************************************************************************///
///*History2:      第2次修改
///*内容1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*内容2. Date:
///*   	   Author:
///*       Modification:
///*****************************************************************************************///


#include "LCDDrive.h"






///***********************************************************************************///
///*Function：
///*Description：将1字节数据带Ack读出，返回值为读出值
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
//static uchar8 DF_LCDI2C_ReadOneByteAck(void)
//{
//	uchar8 i = C_LCD_BitLen;
//	uchar8 V_Value;
//	
//	//LCD_Scl_Output_0;
//	//LCD_Set_Scl_Output;
//	LCD_Set_Sda_Input;
//	
//	while( i > 0 )
//	{
//		LCD_Scl_Output_1;
//		V_Value = V_Value<<1;
//		i--;
//		if( LCD_Read_Sda == LCDSDA_SELECT )
//		{
//			V_Value |= 0x01;
//		}
//		LCD_Scl_Output_0;
//		InF_Delay_2us();
//	}
//	
//	LCD_Sda_Output_0;
//	LCD_Set_Sda_Output;
//	InF_Delay_2us();
//	LCD_Scl_Output_1;
//	InF_Delay_2us();
//	
//	LCD_Scl_Output_0;
//	return V_Value;
//}

///***********************************************************************************///
///*Function：
///*Description：将1字节数据不带Ack读到*P，返回值为I2C是否成功，C_Ok或C_IICError。
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
//static uchar8 DF_LCDI2C_ReadOneByteNoAck(void)
//{
//	
//	uchar8 i = C_LCD_BitLen;
//	uchar8 V_Value;
//
//	//LCD_Scl_Output_0;
//	//LCD_Set_Scl_Output;
//	LCD_Set_Sda_Input;
//
//	while( i > 0 )
//	{
//	LCD_Scl_Output_1;
//	V_Value = V_Value<<1;
//	i--;
//	InF_Delay_2us();
//	if( LCD_Read_Sda == LCDSDA_SELECT )
//	{
//		V_Value |= 0x01;
//	}
//	LCD_Scl_Output_0;
//	InF_Delay_2us();
//	}
//
//	LCD_Sda_Output_1;
//	LCD_Set_Sda_Output;
//	InF_Delay_2us();
//	LCD_Scl_Output_1;
//	InF_Delay_2us();
//
//	LCD_Scl_Output_0;
//	return V_Value;
//}

///***********************************************************************************///
///*Function：
///*Description：将1字节数据不带Ack读到*P，返回值为I2C是否成功，C_Ok或C_IICError。
///*Input：
///*Output：
///*Return：返回值会体现I2C是否错误，C_Ok或C_IICError。
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
static uchar8 DF_LCDI2C_WriteOneByte(uchar8 V_Data)
{
	uchar8 V_Value = C_OK;
    char8 i = C_LCD_BitLen;	///*每字节的位数*///
    
	//LCD_Scl_Output_0;		///*写数据在start之后，所以scl处于低，sda为输出态，此处可以去掉*///
	//LCD_Set_Scl_Output;
	//InF_Delay_2us();
	LCD_Set_Sda_Output;
	
    while( i > 0 )
    {
    	if( (V_Data & C_LCD_MostSignificantBit) == C_LCD_MostSignificantBit )
    	{
    		LCD_Sda_Output_1;
    	}
    	else
    	{
    		LCD_Sda_Output_0;
    	}
        V_Data = V_Data<<1;
    	InF_Delay_2us();
        LCD_Scl_Output_1;
    	InF_Delay_2us();
        LCD_Scl_Output_0;
        i--;
    }
    LCD_Set_Sda_Input;
    InF_Delay_2us();
    LCD_Scl_Output_1;
    InF_Delay_2us();
    if( LCD_Read_Sda  )
    {
		V_Value = C_IICError;
    }
    LCD_Scl_Output_0;
	
	return V_Value;
}

///***********************************************************************************///
///*Function：
///*Description：将1字节数据不带Ack读到*P，返回值为I2C是否成功，C_Ok或C_IICError。
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
static void DF_LCDI2C_Start(void)
{
	LCD_Scl_Output_0;
	LCD_Set_Scl_Output;
	InF_Delay_2us();
	LCD_Sda_Output_1;
	LCD_Set_Sda_Output;
	InF_Delay_2us();
	LCD_Scl_Output_1;
	InF_Delay_2us();
	LCD_Sda_Output_0;
	InF_Delay_2us();
	LCD_Scl_Output_0;
}


///***********************************************************************************///
///*Function：
///*Description：将1字节数据不带Ack读到*P，返回值为I2C是否成功，C_Ok或C_IICError。
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
static void DF_LCDI2C_Stop(void)
{
	uchar8 V_Counter;
	for(V_Counter = C_LCD_Max_StopTimes;V_Counter > 0;V_Counter--)
	{
		LCD_Scl_Output_0;
		LCD_Set_Scl_Output;
		InF_Delay_2us();
		LCD_Set_Sda_Input;
		InF_Delay_2us();
		if(LCD_Read_Sda )
		{
			break;
		}
		LCD_Scl_Output_1;
		InF_Delay_2us();
		if(LCD_Read_Sda )
		{
			break;
		}
	}
	LCD_Scl_Output_0;
	InF_Delay_2us();
	LCD_Sda_Output_0;
	LCD_Set_Sda_Output;
	InF_Delay_2us();
	LCD_Scl_Output_1;
	InF_Delay_2us();
	LCD_Sda_Output_1;
	InF_Delay_2us();
	InF_Delay_2us();
	LCD_Scl_Output_0;
	InF_Delay_2us();
	LCD_Set_Sda_Input;
	LCD_Set_Scl_Input;///*8com	3.3转5V上拉电阻原因设置为输入态
	InF_Delay_2us();
}

///***********************************************************************************///
///*Function：
///*Description：将1字节数据带Ack读出，返回值为读出值
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
//static uchar8 DF_LCDXI2C_ReadOneByteAck(void)
//{
//	uchar8 i = C_LCD_BitLen;
//	uchar8 V_Value;
//	
//	//LCDX_Scl_Output_0;
//	//LCDX_Set_Scl_Output;
//	LCDX_Set_Sda_Input;
//	
//	while( i > 0 )
//	{
//		LCDX_Scl_Output_1;
//		V_Value = V_Value<<1;
//		i--;
//		if( LCDX_Read_Sda == LCDXSDA_SELECT )
//		{
//			V_Value |= 0x01;
//		}
//		LCDX_Scl_Output_0;
//		InF_Delay_2us();
//	}
//	
//	LCDX_Sda_Output_0;
//	LCDX_Set_Sda_Output;
//	InF_Delay_2us();
//	LCDX_Scl_Output_1;
//	InF_Delay_2us();
//	
//	LCDX_Scl_Output_0;
//	return V_Value;
//}

///***********************************************************************************///
///*Function：
///*Description：将1字节数据不带Ack读到*P，返回值为I2C是否成功，C_Ok或C_IICError。
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
//static uchar8 DF_LCDXI2C_ReadOneByteNoAck(void)
//{
//	
//	uchar8 i = C_LCD_BitLen;
//	uchar8 V_Value;
//
//	//LCDX_Scl_Output_0;
//	//LCDX_Set_Scl_Output;
//	LCDX_Set_Sda_Input;
//
//	while( i > 0 )
//	{
//	LCDX_Scl_Output_1;
//	V_Value = V_Value<<1;
//	i--;
//	InF_Delay_2us();
//	if( LCDX_Read_Sda == LCDXSDA_SELECT )
//	{
//		V_Value |= 0x01;
//	}
//	LCDX_Scl_Output_0;
//	InF_Delay_2us();
//	}
//
//	LCDX_Sda_Output_1;
//	LCDX_Set_Sda_Output;
//	InF_Delay_2us();
//	LCDX_Scl_Output_1;
//	InF_Delay_2us();
//
//	LCDX_Scl_Output_0;
//	return V_Value;
//}

///***********************************************************************************///
///*Function：
///*Description：将1字节数据不带Ack读到*P，返回值为I2C是否成功，C_Ok或C_IICError。
///*Input：
///*Output：
///*Return：返回值会体现I2C是否错误，C_Ok或C_IICError。
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
/////*static uchar8 DF_LCDXI2C_WriteOneByte(uchar8 V_Data)
//{
//	uchar8 V_Value = C_OK;
//    char8 i = C_LCD_BitLen;		///*每字节的位数*///
//    
//	//LCDX_Scl_Output_0;		///*写数据在start之后，所以scl处于低，sda为输出态，此处可以去掉*///
//	//LCDX_Set_Scl_Output;
//	//InF_Delay_2us();
//	LCDX_Set_Sda_Output;
//	
//    while( i > 0 )
//    {
//    	if( (V_Data & C_LCD_MostSignificantBit) == C_LCD_MostSignificantBit )
//    	{
//    		LCDX_Sda_Output_1;
//    	}
//    	else
//    	{
//    		LCDX_Sda_Output_0;
//    	}
//        V_Data = V_Data<<1;
//    	InF_Delay_2us();
//        LCDX_Scl_Output_1;
//    	InF_Delay_2us();
//        LCDX_Scl_Output_0;
//        i--;
//    }
//    LCDX_Set_Sda_Input;
//    InF_Delay_2us();
//    LCDX_Scl_Output_1;
//    InF_Delay_2us();
//    if( LCDX_Read_Sda )
//    {
//		V_Value = C_IICError;
//    }
//    LCDX_Scl_Output_0;
//	
//	return V_Value;
//}*/

///***********************************************************************************///
///*Function：
///*Description：将1字节数据不带Ack读到*P，返回值为I2C是否成功，C_Ok或C_IICError。
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
//static void DF_LCDXI2C_Start(void)
//{
//	LCDX_Scl_Output_0;
//	LCDX_Set_Scl_Output;
//	InF_Delay_2us();
//	LCDX_Sda_Output_1;
//	LCDX_Set_Sda_Output;
//	InF_Delay_2us();
//	LCDX_Scl_Output_1;
//	InF_Delay_2us();
//	LCDX_Sda_Output_0;
//	InF_Delay_2us();
//	LCDX_Scl_Output_0;
//}


///***********************************************************************************///
///*Function：
///*Description：将1字节数据不带Ack读到*P，返回值为I2C是否成功，C_Ok或C_IICError。
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
//static void DF_LCDXI2C_Stop(void)
//{
//	uchar8 V_Counter;
//	for(V_Counter = C_LCD_Max_StopTimes;V_Counter > 0;V_Counter--)
//	{
//		LCDX_Scl_Output_0;
//		LCDX_Set_Scl_Output;
//		InF_Delay_2us();
//		LCDX_Set_Sda_Input;
//		InF_Delay_2us();
//		if(LCDX_Read_Sda )
//		{
//			break;
//		}
//		LCDX_Scl_Output_1;
//		InF_Delay_2us();
//		if(LCDX_Read_Sda )
//		{
//			break;
//		}
//	}
//	LCDX_Scl_Output_0;
//	InF_Delay_2us();
//	LCDX_Sda_Output_0;
//	LCDX_Set_Sda_Output;
//	InF_Delay_2us();
//	LCDX_Scl_Output_1;
//	InF_Delay_2us();
//	LCDX_Sda_Output_1;
//	InF_Delay_2us();
//	InF_Delay_2us();
//	LCDX_Scl_Output_0;
//	InF_Delay_2us();
//	LCDX_Set_Sda_Input;
//	InF_Delay_2us();
//}

///*表格格式如下*///
///*传入数据缓冲区地址偏移,传入数据在缓冲区的位号,显示缓冲区地址偏移,显示的位号*///
const uchar8 DataBuffToDispBuff_Table[C_DotNumber][C_Column]=
{
/////////////////////////////////////
C_DataBuff_DP10,C_DataBit_DP10,		C_DispBuff_DP10,C_DispBit_DP10,         //1
C_DataBuff_DP11,C_DataBit_DP11,		C_DispBuff_DP11,C_DispBit_DP11,         //2
C_DataBuff_DP12,C_DataBit_DP12,		C_DispBuff_DP12,C_DispBit_DP12,         //3
C_DataBuff_Q,C_DataBit_Q,			C_DispBuff_Q,C_DispBit_Q,	            //4
/////////////////////////////////////
C_DataBuff_Q4,C_DataBit_Q4,			C_DispBuff_Q4,C_DispBit_Q4,             //5
C_DataBuff_Q3,C_DataBit_Q3,			C_DispBuff_Q3,C_DispBit_Q3,             //6
C_DataBuff_Q2,C_DataBit_Q2,			C_DispBuff_Q2,C_DispBit_Q2,             //7
C_DataBuff_Q1,C_DataBit_Q1,			C_DispBuff_Q1,C_DispBit_Q1,             //8
/////////////////////////////////////
C_DataBuff_S56,C_DataBit_S56,			C_DispBuff_S56,C_DispBit_S56,       //9
C_DataBuff_S67,C_DataBit_S67,			C_DispBuff_S67,C_DispBit_S67,       //10
/////////////////////////////////////
C_DataBuff_S80,C_DataBit_S80,			C_DispBuff_S80,C_DispBit_S80,       //11
C_DataBuff_S81,C_DataBit_S81,			C_DispBuff_S81,C_DispBit_S81,       //12
C_DataBuff_S82,C_DataBit_S82,			C_DispBuff_S82,C_DispBit_S82,       //13
C_DataBuff_S83,C_DataBit_S83,			C_DispBuff_S83,C_DispBit_S83,       //14
C_DataBuff_S79,C_DataBit_S79,			C_DispBuff_S79,C_DispBit_S79,	    //15
C_DataBuff_S84,C_DataBit_S84,			C_DispBuff_S84,C_DispBit_S84,	    //16
C_DataBuff_S85,C_DataBit_S85,			C_DispBuff_S85,C_DispBit_S85,		//17
C_DataBuff_S86,C_DataBit_S86,			C_DispBuff_S86,C_DispBit_S86,       //18
/////////////////////////////////////
C_DataBuff_S87,C_DataBit_S87,			C_DispBuff_S87,C_DispBit_S87,	    //19
C_DataBuff_S88,C_DataBit_S88,			C_DispBuff_S88,C_DispBit_S88,	    //20
C_DataBuff_S89,C_DataBit_S89,			C_DispBuff_S89,C_DispBit_S89,       //21
C_DataBuff_S90,C_DataBit_S90,			C_DispBuff_S90,C_DispBit_S90,	    //22
C_DataBuff_S91,C_DataBit_S91,			C_DispBuff_S91,C_DispBit_S91,       //23
C_DataBuff_S95,C_DataBit_S95,			C_DispBuff_S95,C_DispBit_S95,       //24
/////////////////////////////////////
C_DataBuff_S96,C_DataBit_S96,			C_DispBuff_S96,C_DispBit_S96,	    //25
C_DataBuff_S97,C_DataBit_S97,			C_DispBuff_S97,C_DispBit_S97,       //26
C_DataBuff_S98,C_DataBit_S98,			C_DispBuff_S98,C_DispBit_S98,	    //27
C_DataBuff_S76,C_DataBit_S76,			C_DispBuff_S76,C_DispBit_S76,	    //28
C_DataBuff_S77,C_DataBit_S77,			C_DispBuff_S77,C_DispBit_S77,	    //29
C_DataBuff_S92,C_DataBit_S92,			C_DispBuff_S92,C_DispBit_S92,       //30
C_DataBuff_S93,C_DataBit_S93,			C_DispBuff_S93,C_DispBit_S93,	    //31
/////////////////////////////////////
C_DataBuff_S64,C_DataBit_S64,			C_DispBuff_S64,C_DispBit_S64,		//32
C_DataBuff_S65,C_DataBit_S65,			C_DispBuff_S65,C_DispBit_S65,       //33
C_DataBuff_S66,C_DataBit_S66,			C_DispBuff_S66,C_DispBit_S66,       //34
C_DataBuff_S94,C_DataBit_S94,			C_DispBuff_S94,C_DispBit_S94,	    //35
C_DataBuff_S68,C_DataBit_S68,			C_DispBuff_S68,C_DispBit_S68,       //36
C_DataBuff_S69,C_DataBit_S69,			C_DispBuff_S69,C_DispBit_S69,	    //37
C_DataBuff_S70,C_DataBit_S70,			C_DispBuff_S70,C_DispBit_S70,	    //38
C_DataBuff_S71,C_DataBit_S71,			C_DispBuff_S71,C_DispBit_S71,	    //39
/////////////////////////////////////
C_DataBuff_S72,C_DataBit_S72,			C_DispBuff_S72,C_DispBit_S72,	    //40
C_DataBuff_S73,C_DataBit_S73,			C_DispBuff_S73,C_DispBit_S73,       //41
/////////////////////////////////////
C_DataBuff_S6,C_DataBit_S6,				C_DispBuff_S6,C_DispBit_S6,	        //42
C_DataBuff_S7,C_DataBit_S7,				C_DispBuff_S7,C_DispBit_S7,	        //43
C_DataBuff_S9,C_DataBit_S9,				C_DispBuff_S9,C_DispBit_S9,	        //44
C_DataBuff_S10,C_DataBit_S10,			C_DispBuff_S10,C_DispBit_S10,       //45
C_DataBuff_S11,C_DataBit_S11,			C_DispBuff_S11,C_DispBit_S11,	    //46
C_DataBuff_S12,C_DataBit_S12,			C_DispBuff_S12,C_DispBit_S12,       //47
C_DataBuff_S13,C_DataBit_S13,			C_DispBuff_S13,C_DispBit_S13,       //48
C_DataBuff_S14,C_DataBit_S14,			C_DispBuff_S14,C_DispBit_S14,       //49
/////////////////////////////////////
C_DataBuff_S15,C_DataBit_S15,			C_DispBuff_S15,C_DispBit_S15,	    //50
C_DataBuff_S16,C_DataBit_S16,			C_DispBuff_S16,C_DispBit_S16,       //51
C_DataBuff_S20,C_DataBit_S20,			C_DispBuff_S20,C_DispBit_S20,	    //52
C_DataBuff_S21,C_DataBit_S21,			C_DispBuff_S21,C_DispBit_S21,	    //53
C_DataBuff_S22,C_DataBit_S22,			C_DispBuff_S22,C_DispBit_S22,	    //54
/////////////////////////////////////
C_DataBuff_S29,C_DataBit_S29,			C_DispBuff_S29,C_DispBit_S29,       //55
C_DataBuff_S30,C_DataBit_S30,			C_DispBuff_S30,C_DispBit_S30,	    //56
C_DataBuff_S31,C_DataBit_S31,			C_DispBuff_S31,C_DispBit_S31,		//57
C_DataBuff_S32,C_DataBit_S32,			C_DispBuff_S32,C_DispBit_S32,       //58
C_DataBuff_S33,C_DataBit_S33,			C_DispBuff_S33,C_DispBit_S33,       //59
C_DataBuff_S34,C_DataBit_S34,			C_DispBuff_S34,C_DispBit_S34,       //60
C_DataBuff_S35,C_DataBit_S35,			C_DispBuff_S35,C_DispBit_S35,	    //61
C_DataBuff_S36,C_DataBit_S36,			C_DispBuff_S36,C_DispBit_S36,	    //62
/////////////////////////////////////
C_DataBuff_S37,C_DataBit_S37,			C_DispBuff_S37,C_DispBit_S37,	    //63
C_DataBuff_S38,C_DataBit_S38,			C_DispBuff_S38,C_DispBit_S38,       //64
C_DataBuff_S39,C_DataBit_S39,			C_DispBuff_S39,C_DispBit_S39,	    //65
C_DataBuff_S40,C_DataBit_S40,			C_DispBuff_S40,C_DispBit_S40,	    //66
C_DataBuff_S41,C_DataBit_S41,			C_DispBuff_S41,C_DispBit_S41,	    //67
C_DataBuff_S42,C_DataBit_S42,			C_DispBuff_S42,C_DispBit_S42,	    //68
C_DataBuff_S43,C_DataBit_S43,			C_DispBuff_S43,C_DispBit_S43,       //69
C_DataBuff_S44,C_DataBit_S44,			C_DispBuff_S44,C_DispBit_S44,       //70
/////////////////////////////////////
C_DataBuff_S45,C_DataBit_S45,			C_DispBuff_S45,C_DispBit_S45,	    //71
C_DataBuff_S46,C_DataBit_S46,			C_DispBuff_S46,C_DispBit_S46,	    //72
C_DataBuff_S47,C_DataBit_S47,			C_DispBuff_S47,C_DispBit_S47,	    //73
C_DataBuff_S48,C_DataBit_S48,			C_DispBuff_S48,C_DispBit_S48,       //74

C_DataBuff_S17,C_DataBit_S17,			C_DispBuff_S17,C_DispBit_S17,		//
C_DataBuff_S18,C_DataBit_S18,			C_DispBuff_S18,C_DispBit_S18,		//
C_DataBuff_S19,C_DataBit_S19,			C_DispBuff_S19,C_DispBit_S19,

/////////////////////////////////////
C_DataBuff_S74,C_DataBit_S74,			C_DispBuff_S74,C_DispBit_S74,	    //75
C_DataBuff_S75,C_DataBit_S75,			C_DispBuff_S75,C_DispBit_S75,       //76
C_DataBuff_S53,C_DataBit_S53,			C_DispBuff_S53,C_DispBit_S53,       //77
C_DataBuff_S57,C_DataBit_S57,			C_DispBuff_S57,C_DispBit_S57,       //78
C_DataBuff_DP8,C_DataBit_DP8,			C_DispBuff_DP8,C_DispBit_DP8,	    //79
/////////////////////////////////////
C_DataBuff_S58,C_DataBit_S58,			C_DispBuff_S58,C_DispBit_S58,       //80
C_DataBuff_S59,C_DataBit_S59,			C_DispBuff_S59,C_DispBit_S59,	    //81
C_DataBuff_S61,C_DataBit_S61,			C_DispBuff_S61,C_DispBit_S61,	    //82
C_DataBuff_S60,C_DataBit_S60,			C_DispBuff_S60,C_DispBit_S60,	    //83
C_DataBuff_S62,C_DataBit_S62,			C_DispBuff_S62,C_DispBit_S62,       //84
C_DataBuff_S63,C_DataBit_S63,			C_DispBuff_S63,C_DispBit_S63,	    //85
/////////////////////////////////////
C_DataBuff_DP1,C_DataBit_DP1,			C_DispBuff_DP1,C_DispBit_DP1,	    //86
C_DataBuff_DP2,C_DataBit_DP2,			C_DispBuff_DP2,C_DispBit_DP2,	    //87
C_DataBuff_DP5,C_DataBit_DP5,			C_DispBuff_DP5,C_DispBit_DP5,       //89
C_DataBuff_DP3,C_DataBit_DP3,			C_DispBuff_DP3,C_DispBit_DP3,       //88
C_DataBuff_DP4,C_DataBit_DP4,			C_DispBuff_DP4,C_DispBit_DP4,	    //90
C_DataBuff_DP6,C_DataBit_DP6,			C_DispBuff_DP6,C_DispBit_DP6,       //91
C_DataBuff_DP7,C_DataBit_DP7,			C_DispBuff_DP7,C_DispBit_DP7,	    //92				
};
///*数字的真值*///
const uchar8 LCDDrive_DataCodeTable[C_LCD_DataTruthTableLen]=          //数据编码表格ABCX_FGED
  {0xEB,0x60,0xC7,0xE5,0x6C,0xAD,0xAF,0xE0,0xEF,0xED,0xEE, 0x2F,0x8B,0x67,0x8F,0x8E};
 ///*0   1    2    3    4   	5    6    7    8    9    A     b    C    d    E    F    *///
const uchar8 Table_LCDBuff1RealAddrABC[C_LCD_BuffAddrLen]=
	{19,21,23,25,27,29, 31,33,  7,   5,   17, 15, 13, 11,  9,  7,  5, 3,  32, 32};
///* 12 11 10  9  8  7  6  5    24  23   20  19  18  17  16   15  14,13,   1  1P
const uchar8 Table_LCDBuff1RealAddrDEGF[C_LCD_BuffAddrLen]=
  {18,22,24,26,28,30, 32,34,    6,   4,   16, 14, 12, 10,  8,   6, 4,  2,  33, 33};
//{19,21,23,25,27,29, 31,33,    7,   5,,  17, 15, 13, 11,  9,  7,5,  3,   32, 32};

 const uchar8 Table_LCDDataBuff1SegNum[C_LCD_BuffAddrLen]=
     { 12,11,10,9,8,7,6,5,24,23, 20,19,18,17,16,15, 14,13,   1,1};     

 const uchar8 Table_LCDBuff2RealAddrABC[5]=            //对应实际电路
   { 21,11, 19, 1, 3};
///* 2，21，22，4，3
const uchar8 Table_LCDBuff2RealAddrDEGF[5]=            //对应实际电路
   { 22,12,18,0,2};
///* 2，21，22，4，3

 const uchar8 Table_LCDDataBuff2SegNum[5]=             //data2、data21、data22、data4、data3    对应真值表
  { 2,21, 22, 4, 3};   
 
const uchar8 Table_LCDSegTable[C_LCD_DataLen]=
  {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,1,0};
// 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34
 
//表格0-8行用于主显示区灭零,不插卡时只需要用到表格的0-8行。9-19行用于其他数字显示区灭零，插卡动态显示全灭零时需要用到。
   const uchar8 Table_KillZero[C_KillZeroTotalNumber][C_Column_KillZero]=
  {
	C_DispData3ABC_Addr,C_DispData3DEGF_Addr,C_DispData3KillZero,    //主显示区数字3灭零
	C_DispData4ABC_Addr,C_DispData4DEGF_Addr,C_DispData4KillZero,    //主显示区数字4灭零
	C_DispData5ABC_Addr,C_DispData5DEGF_Addr,C_DispData5KillZero,    //主显示区数字5灭零
	C_DispData6ABC_Addr,C_DispData6DEGF_Addr,C_DispData6KillZero,    //主显示区数字6灭零
	C_DispData7ABC_Addr,C_DispData7DEGF_Addr,C_DispData7KillZero,    //主显示区数字7灭零
	C_DispData8ABC_Addr,C_DispData8DEGF_Addr,C_DispData8KillZero,	 //主显示区数字8灭零
    C_DispData9ABC_Addr,C_DispData9DEGF_Addr,C_DispData9KillZero,    //主显示区数字9灭零
	C_DispData10ABC_Addr,C_DispData10DEGF_Addr,C_DispData10KillZero, //主显示区数字10灭零
	C_DispData11ABC_Addr,C_DispData11DEGF_Addr,C_DispData11KillZero, //主显示区数字11灭零
    
  	C_DispData12ABC_Addr,C_DispData12DEGF_Addr,C_DispData12KillZero,
	C_DispData13ABC_Addr,C_DispData13DEGF_Addr,C_DispData13KillZero,
	C_DispData14ABC_Addr,C_DispData14DEGF_Addr,C_DispData14KillZero,
	C_DispData15ABC_Addr,C_DispData15DEGF_Addr,C_DispData15KillZero,
	C_DispData16ABC_Addr,C_DispData16DEGF_Addr,C_DispData16KillZero,
	C_DispData17ABC_Addr,C_DispData17DEGF_Addr,C_DispData17KillZero,	
    C_DispData18ABC_Addr,C_DispData18DEGF_Addr,C_DispData18KillZero,
	C_DispData19ABC_Addr,C_DispData19DEGF_Addr,C_DispData19KillZero,
	C_DispData20ABC_Addr,C_DispData20DEGF_Addr,C_DispData20KillZero,	 
    C_DispData23ABC_Addr,C_DispData23DEGF_Addr,C_DispData23KillZero,
	C_DispData24ABC_Addr,C_DispData24DEGF_Addr,C_DispData24KillZero,	
  };
  
const uchar8 Special_Number[C_Special_Number_Len]=
{
	C_DispNumber1Buff,
};

uchar8  SVuc_CheckTime;						///*该变量用于定时检查显示24H地址寄存器，如不等于设置值，则重新初始化显示寄存器。上电前3s不检查，后面每500ms检查一次
 ///***********************************************************************************///
///*Function：
///*Description：编码转换ABC*_FGED  对应真值表转换成  *CBA_DEGF用于显示赋值
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
uchar8 Change_CodeDispData(uchar8 InputData)
{
     uchar8  OutputData;
     OutputData=0;
     if( InputData&0x80 )
     {
          OutputData|=0x10;
     }      
     if( InputData&0x40 )
     {
          OutputData|=0x20;
     }
     if( InputData&0x20 )
     {
          OutputData|=0x40;
     }
     if( InputData&0x10 )
     {
          OutputData|=0x80;
     }
     if( InputData&0x08 )
     {
          OutputData|=0x01;
     }      
     if( InputData&0x04 )
     {
          OutputData|=0x02;
     }
     if( InputData&0x02 )
     {
          OutputData|=0x04;
     }     
     if( InputData&0x01 )
     {
          OutputData|=0x08;
     }
     return  OutputData;
}

///***********************************************************************************///
///*Function：
///*Description：真值表转换：将应用层的虚拟驱动的真值表转换为实际驱动芯片的真值表
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：*p_dispbuff缓存输入之前需清零
///***********************************************************************************///
void DF_Convert_TruthTable(uchar8 *p_databuff,uchar8 *p_dispbuff)
{
	uchar8 i,j,k,h4bit,l4bit,V_ucTemph4bit,V_ucTempl4bit;
	//uchar8 V_ucTestBuff[30];
	for(k=0;k<(C_LCD_BuffAddrLen-1);k++)///*去除1P的处理，下面单独处理1P
	{	

		j=k/2;
		if(k%2)
		{
			i = (p_databuff[j]>>4)&0x0f;			
		}
		else
		{
			i = p_databuff[j]&0x0f;
		}

        h4bit=((LCDDrive_DataCodeTable[i]>>4)&0x0f);
        l4bit=( LCDDrive_DataCodeTable[i]&0x0f);

        if((Table_LCDDataBuff1SegNum[k]==2)||(Table_LCDDataBuff1SegNum[k]==13)||(Table_LCDDataBuff1SegNum[k]==22)||(Table_LCDDataBuff1SegNum[k]==23)||(Table_LCDDataBuff1SegNum[k]==24))
        {
          V_ucTemph4bit=h4bit;
          V_ucTempl4bit=l4bit;
          h4bit=Change_CodeDispData(V_ucTemph4bit);   //编码转换
          l4bit=Change_CodeDispData(V_ucTempl4bit);
          p_dispbuff[Table_LCDBuff1RealAddrABC[k]]  |=((h4bit<<4)&0xf0);
          p_dispbuff[Table_LCDBuff1RealAddrDEGF[k]] |=((l4bit<<4)&0xf0);  
        }
        else if((Table_LCDDataBuff1SegNum[k]==1))
        {
          p_dispbuff[Table_LCDBuff1RealAddrABC[k]]  |=((h4bit<<4)&0xf0);
          p_dispbuff[Table_LCDBuff1RealAddrDEGF[k]] |=((l4bit<<4)&0xf0); 
        }
        else
        {
          p_dispbuff[Table_LCDBuff1RealAddrABC[k]]   |=h4bit;
          p_dispbuff[Table_LCDBuff1RealAddrDEGF[k]] |=l4bit;	
        }
        
	}
    for(k=0;k<C_LCD_BuffAddrLen2;k++)       //数据2、21、22、4、3的显示转换
    {
        if(k<3)                             //数据2、21、22
        {
          i = p_databuff[25+k]&0x0f;
        }
        else
        {
          if(k%2)
          {
            i = p_databuff[28]&0x0f;			
          }
          else
          {
 
            i = (p_databuff[28]>>4)&0x0f;
          }
        }
        h4bit=((LCDDrive_DataCodeTable[i]>>4)&0x0f);
        l4bit=( LCDDrive_DataCodeTable[i]&0x0f);
        if((Table_LCDDataBuff2SegNum[k]==21)||(Table_LCDDataBuff2SegNum[k]==22))
        {
          V_ucTemph4bit=h4bit;
          V_ucTempl4bit=l4bit;
          h4bit=Change_CodeDispData(V_ucTemph4bit);
          l4bit=Change_CodeDispData(V_ucTempl4bit);
          p_dispbuff[Table_LCDBuff2RealAddrABC[k]]  |=((h4bit<<4)&0xf0);
          p_dispbuff[Table_LCDBuff2RealAddrDEGF[k]] |=((l4bit<<4)&0xf0);  
        }
        else if((Table_LCDDataBuff2SegNum[k]==2))
        {
          p_dispbuff[Table_LCDBuff2RealAddrABC[k]]  |=((h4bit<<4)&0xf0);
          p_dispbuff[Table_LCDBuff2RealAddrDEGF[k]] |=((l4bit<<4)&0xf0);
        }
        else 
       {
          p_dispbuff[Table_LCDBuff2RealAddrABC[k]]   |=h4bit;
          p_dispbuff[Table_LCDBuff2RealAddrDEGF[k]] |=l4bit;
        }
    }
//	p_dispbuff[Table_LCDBuffAddr[C_LCD_BuffAddrLen-1]] &= 0x7F;		///*上18 月，显示特别处理，上1，30缓存*///
//	p_dispbuff[Table_LCDBuffAddr[C_LCD_BuffAddrLen-2]] &= 0x0F;		///*上18 月，显示特别处理，29缓存*///
	
	
	///*上?月，?显示特殊处理。只显示0时，0不显示；显示10时，0才显示*///
	if( p_databuff[9] != 0 )		///*1P、数字1所传入的地址*///
	{
		if( p_databuff[9] >= 0x10 )		///*1P显示*///
	    {
	       p_dispbuff[Table_LCDSegTable[C_DispBuff_1P]] |= C_DispBit_1P;           
	    }
	}
	else///*为0，不显示
	{
        p_dispbuff[Table_LCDSegTable[C_DispBuff_1P]] &= ~C_DispBit_1P; 
        p_dispbuff[Table_LCDSegTable[C_DispBuff_1ABC]] &=0x1F;
        p_dispbuff[Table_LCDSegTable[C_DispBuff_1DEGF]]&=0x0F;  
	}
	
   
   if( p_databuff[25] != 0 )		        ///*2P、数字2所传入的地址*///
	{
		if( p_databuff[25] >= 0x10 )		///*2P显示*///
	    {
	       p_dispbuff[Table_LCDSegTable[C_DispBuff_2P]] |= C_DispBit_2P;           
	    }
	}
	else                                    //灭零
	{
        p_dispbuff[Table_LCDSegTable[C_DispBuff_2P]] &= ~C_DispBit_2P; 
        p_dispbuff[Table_LCDSegTable[C_DispBuff_2ABC]] &=0x1F;
        p_dispbuff[Table_LCDSegTable[C_DispBuff_2DEGF]]&=0x0F;
	}
    
    if( p_databuff[26] == 0 )		       ///*数字21所传入的地址*///
	{
        p_dispbuff[Table_LCDSegTable[C_DispBuff_21ABC]] &=0x8F;
        p_dispbuff[Table_LCDSegTable[C_DispBuff_21DEGF]]&=0x0F;          
	}    
    
    if( p_databuff[27] != 0 )		        ///*22P、数字22所传入的地址*///
	{
		if( p_databuff[27] >= 0x10 )		///*22P显示*///
	    {
            p_dispbuff[Table_LCDSegTable[C_DispBuff_22P]] |= C_DispBit_22P;           
	    }
	}
	else                                    //灭零
	{
        p_dispbuff[Table_LCDSegTable[C_DispBuff_22P]] &= ~C_DispBit_22P; 
        p_dispbuff[Table_LCDSegTable[C_DispBuff_22ABC]] &=0x8F;
        p_dispbuff[Table_LCDSegTable[C_DispBuff_22DEGF]]&=0x0F;  
	}
	///*点辅助字符*///
	for(i=0;i<(C_DotNumber);i++)
	{
		if( (p_databuff[DataBuffToDispBuff_Table[i][0]] & DataBuffToDispBuff_Table[i][1]) == DataBuffToDispBuff_Table[i][1] )
		{
			p_dispbuff[Table_LCDSegTable[DataBuffToDispBuff_Table[i][2]]] |= DataBuffToDispBuff_Table[i][3];
		}
	}
}
///**************************************************************************************************///
///*函数原型：void SF_AdjustCom(void)																*///
///*功能描述：对于布板的不同，对com、seg进行调整						                          	*///
///*输入参数：*p_buf：指向显示驱动缓冲区的首地址：低地址                                            *///
///*输出参数：					                                                                    *///
///*返回参数：                                                                                      *///
///*功能说明：																		                *///
///*调用机制：						                                                                *///
///*备    注：                                                                                      *///
///**************************************************************************************************///
///********macro pcb板号********///
//#define	C_Pcb1512			0x01			///*0.2S表的主板板号，无费控功能*///
//#define	C_Pcb1595       	0x02            ///*智能表的主板板号，有费控功能：本地和远程都有*///
//#if	( C_PcbVersion == C_Pcb1512 )		///*0.2S表*///
//void SF_AdjustCom(uchar8 *p_buf)
//{
//	uchar8 i,k;
//	
//	for(i=0;i<C_LCD_DataLen;i++)
//	{		///*下半部的COM1与COM2需要颠倒一下*///
//		k = p_buf[i];
//		p_buf[i] &= 0x99;
//		p_buf[i] |= ((k&0x22)<<1);
//		p_buf[i] |= ((k&0x44)>>1);
//	}
//	
//	for(i=C_LCD_DataLen; i<C_LCD_DataLen+C_LCD_DataLen; i++)
//	{		///*上半部的COM0与COM3需要颠倒一下*///
//		k = p_buf[i];
//		p_buf[i] &= 0x66;
//		p_buf[i] |= ((k&0x11)<<3);
//		p_buf[i] |= ((k&0x88)>>3);
//	}
//}
//#else
void SF_AdjustCom(uchar8 *p_buf)
{
	uchar8 i,k;
	
	///*7&0,6&1,5&2,4&3,对调位置*///
	for(i=0; i<C_LCD_DataLen; i++)
	{
		k = 0;
		if( p_buf[i] & 0x01)
		{
			k |= 0x80;
		}
		
		if( p_buf[i] & 0x02)
		{
			k |= 0x40;
		}
		
		if( p_buf[i] & 0x04)
		{
			k |= 0x20;
		}
		
		if( p_buf[i] & 0x08)
		{
			k |= 0x10;
		}
		
		if( p_buf[i] & 0x10)
		{
			k |= 0x08;
		}
		
		if( p_buf[i] & 0x20)
		{
			k |= 0x04;
		}
		
		if( p_buf[i] & 0x40)
		{
			k |= 0x02;
		}
		
		if( p_buf[i] & 0x80)
		{
			k |= 0x01;
		}
		
		p_buf[i] = k;
	}
}
///***********************************************************************************///
///*Function：
///*Description：将1字节数据带Ack读出，返回值即为读出值
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：约270k
///***********************************************************************************///
void DF_LCDI2C_ReadOneByteAck(uchar8 * Vuc_Data)
{
	uchar8 i = C_LCD_BitLen;
	uchar8 V_Value=0;
	
	LCD_Set_Sda_Input;
	
	while( i > 0 )
	{
		LCD_Scl_Output_1;
		InF_Delay_2us();		
		V_Value = V_Value<<1;
		i--;
		if( LCD_Read_Sda )
		{
			V_Value |= 0x01;
		}
		LCD_Scl_Output_0;
		InF_Delay_2us();
	}
	
	LCD_Sda_Output_0;
	LCD_Set_Sda_Output;
	InF_Delay_2us();
	LCD_Scl_Output_1;
	InF_Delay_2us();	
	LCD_Scl_Output_0;
	* Vuc_Data=V_Value;
}


void InF_InitLCD(void)
{
	uchar8 i;
	LCD_IO_Init;
	///*********************************************************///
	DF_LCDI2C_Stop();
	
	InF_Delay_2us();
	InF_Delay_2us();
	DF_LCDI2C_Start();
	DF_LCDI2C_WriteOneByte( C_LCD_BU9792_SlaveAddr_Write );		///*LCD的从地址*///
	DF_LCDI2C_WriteOneByte( C_LCD_BU9792_CMD_ICSet_RESETOff );			///*软复位*///
	InF_Delay_2us();
	DF_LCDI2C_WriteOneByte( C_LCD_BU9792_CMD_DISCTL );			///*工作方式,LCD刷新频率及工作模式*///
	DF_LCDI2C_WriteOneByte( C_LCD_BU9792_CMD_EVRSET );			///*The relationship of electrical volume register (EVR) setting and V0 voltage*///
	DF_LCDI2C_WriteOneByte( C_LCD_BU9792_CMD_APCTL );		
	InF_Delay_2us();
	DF_LCDI2C_WriteOneByte( C_LCD_BU9792_DataStartAddr );		///*初始化data address*///
	for(i = 0; i < C_LCD_DataLen; i++)							///*数据区清零*///
	{
		DF_LCDI2C_WriteOneByte( C_LCD_Data_Zero );
	}
	DF_LCDI2C_Stop();
	///*********************************************************///	
	InF_Delay_2us();
	///*lcd on*///
    DF_LCDI2C_Start();
    DF_LCDI2C_WriteOneByte( C_LCD_BU9792_SlaveAddr_Write );
    DF_LCDI2C_WriteOneByte( C_LCD_BU9792_CMD_ICSet_ModeOn );
    DF_LCDI2C_Stop();
    SVuc_CheckTime=0;
}
//#endif
///**************************************************************************************************///
///*函数原型：void SF_TimeCheck(void)																*///
///*功能描述：定时检验函数，检查显示驱动寄存器，参数是否为设置值。非默认值则调用驱动初始化函数     	*///
///*输入参数：																						                                          *///
///*输出参数：					                                                                    *///
///*返回参数：                                                                                      *///
///*功能说明：																		                *///
///*调用机制：						                                                                *///
///*备    注：上电闭锁检查，然后每次调用显示函数时，都检查                                           *///
///**************************************************************************************************///
void SF_TimeCheck(void)	
{
	uchar8 Vuc_DisTemp;
	
	DF_LCDI2C_Start();
 	DF_LCDI2C_WriteOneByte(C_LCD_BU9792_SlaveAddr_Write);
 	DF_LCDI2C_WriteOneByte(C_LCD_BU9792_CMD_REG2);
	InF_Delay_2us();
 	DF_LCDI2C_Start();
 	DF_LCDI2C_WriteOneByte(C_LCD_BU9792_SlaveAddr_Read);
 	DF_LCDI2C_ReadOneByteAck(&Vuc_DisTemp);
	DF_LCDI2C_Stop();
 	SVuc_CheckTime++;
 	if(SVuc_CheckTime>=C_StartTime_3s)///*先上电闭锁3s
 	{ 		
 		if(Vuc_DisTemp!=C_LCD_BU9792_CheckData)
 		{
 			InF_InitLCD();
			InF_Delay_2us();
			InF_Delay_2us();
			InF_Delay_2us();
			InF_Delay_2us();
			LCD_IO_Init;
 		}
		SVuc_CheckTime=C_StartTime_3s-1;
 	} 	
}

///**************************************************************************************************///
///*函数原型：void InF_WriteLCD(uchar8 *p_databuff,uchar8 Len,uchar8 KillZero)						*///
///*功能描述：将指定缓冲区中长度为Len的数据写入 E2中地址E2Addr开始的存储区                          *///
///*输入参数：*p_databuff：指定缓冲区首地址                                                         *///
///*Len：长度，固定为32字节，采用宏定义C_LCDLen，可以用在安全标志                                   *///
///*KillZero：灭零                                                                                  *///
///*     C_KillZero1       0x01	灭1个零                                                             *///
///*     C_KillZero2       0x02	灭2个零                                                             *///
///*     C_KillZero3       0x03	灭3个零                                                             *///
///*     C_KillZero4       0x04	灭4个零                                                             *///
///*     C_KillZero5       0x05	灭5个零                                                             *///
///*     C_KillZero6       0x06	灭6个零                                                             *///
///*     C_Notkillzero     0x68 不灭零                                                              *///
///*     其他任何值，不灭零                                                                         *///
///*输出参数：数据缓冲区中的数据                                                                    *///
///*返回参数：                                                                                      *///
///*功能说明：该函数入口缓冲区中，首16字节对应上半部分lcd，尾16字节对应下半部分lcd                  *///
///*调用机制：该函数供显示模块调用                                                                  *///
///*备    注：                                                                                      *///
///**************************************************************************************************///
///********macro pcb板号********///
//#define	C_Pcb1512			0x01			///*0.2S表的主板板号，无费控功能*///
//#define	C_Pcb1595       	0x02            ///*智能表的主板板号，有费控功能：本地和远程都有*///
//#if	( C_PcbVersion == C_Pcb1512 )		///*0.2S表*///
//void InF_WriteLCD(uchar8 *p_databuff,uchar8 Len,uchar8 KillZero)
//{
//	uchar8 i;
//	
//	LCD_IO_Init;
//	
//	uchar8 V_LCDDataBuff[C_LCD_DataLen+C_LCD_DataLen];			///*定义32字节缓冲区*///
//	
//	for(i=0;i<(C_LCD_DataLen+C_LCD_DataLen);i++)
//	{
//		V_LCDDataBuff[i] = 0;						///*32字节缓冲区清零*///
//	}
//	///*********************************************************///
//	DF_Convert_TruthTable(p_databuff,&V_LCDDataBuff[0]);		///*真值表转换*///
//	///*********************************************************///
//	///*进行灭零处理*///
//	if( ( KillZero > 0 ) && ( KillZero <= C_KillZeroNumber ) )
//	{
//		for(i=0;i<KillZero;i++)
//		{
//			V_LCDDataBuff[Table_KillZero[i][0]] &= Table_KillZero[i][1];
//		}
//	}
//	///*判断是否显示特殊字符*///
//	if( C_SF_Err == KillZero )
//	{
//		for(i=0;i<6;i++)
//		{
//			V_LCDDataBuff[26+i] = 0;
//		}
//		for(i=0;i<9;i++)
//		{
//			V_LCDDataBuff[4+i] = 0;
//		}
//		V_LCDDataBuff[13] &= C_DispBit_N30_P;
//		//V_LCDDataBuff[1] = 0;
//		
//		V_LCDDataBuff[26] = 0x02;
//		V_LCDDataBuff[27] = 0x42;
//		V_LCDDataBuff[28] = 0x42;
//		V_LCDDataBuff[29] = 0xf2;
//	}
//	///*********************************************************///
//	///*因为硬件布板，需要对COM、SEG进行调整*///
//	SF_AdjustCom(&V_LCDDataBuff[0]);
////	for(i=0;i<C_LCD_DataLen;i++)
////	{		///*下半部的COM1与COM2需要颠倒一下*///
////		k = V_LCDDataBuff[i];
////		V_LCDDataBuff[i] &= 0x99;
////		V_LCDDataBuff[i] |= ((k&0x22)<<1);
////		V_LCDDataBuff[i] |= ((k&0x44)>>1);
////	}
////	
////	for(i=C_LCD_DataLen; i<C_LCD_DataLen+C_LCD_DataLen; i++)
////	{		///*上半部的COM0与COM3需要颠倒一下*///
////		k = V_LCDDataBuff[i];
////		V_LCDDataBuff[i] &= 0x66;
////		V_LCDDataBuff[i] |= ((k&0x11)<<3);
////		V_LCDDataBuff[i] |= ((k&0x88)>>3);
////	}
//	///*********************************************************///
//    DF_LCDI2C_Start();
//	if( Len == C_LCDLen )
//	{
//		DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );
//		DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_DataStartAddr );
//		for(i = 0; i < C_LCD_DataLen; i++)
//		{
//			DF_LCDI2C_WriteOneByte( V_LCDDataBuff[i] );
//	    }
//		InF_Delay_2us();
//		InF_Delay_2us();
//		
//		DF_LCDI2C_Start();
//		DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//		DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_CMD_Mode_On );		///*工作模式*///
//		DF_LCDI2C_Stop();
//		
//		InF_Delay_2us();
//		InF_Delay_2us();
//		DF_LCDI2C_Start();
//		DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//		DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_CMD_IVA );			///*IVA配置*///
//		DF_LCDI2C_Stop();
//		
//		InF_Delay_2us();
//		InF_Delay_2us();
//		DF_LCDI2C_Start();
//		DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//		DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_CMD_BlinkingOff );	///*闪烁方式*///
//		DF_LCDI2C_Stop();
//	}
//    DF_LCDI2C_Stop();
//	///*********************************************************///
//    DF_LCDXI2C_Start();
//	if( Len == C_LCDLen )
//	{
//		DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );
//		DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_DataStartAddr );
//		for(i = 0; i < C_LCD_DataLen; i++)
//		{
//			DF_LCDXI2C_WriteOneByte( V_LCDDataBuff[C_LCD_DataLen+i] );
//	    }
//		InF_Delay_2us();
//		InF_Delay_2us();
//	
//		DF_LCDXI2C_Start();
//		DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//		DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_CMD_Mode_On );		///*工作模式*///
//		DF_LCDXI2C_Stop();
//		
//		InF_Delay_2us();
//		InF_Delay_2us();
//		DF_LCDXI2C_Start();
//		DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//		DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_CMD_IVA );			///*IVA配置*///
//		DF_LCDXI2C_Stop();
//		
//		InF_Delay_2us();
//		InF_Delay_2us();
//		DF_LCDXI2C_Start();
//		DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//		DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_CMD_BlinkingOff );	///*闪烁方式*///
//		DF_LCDXI2C_Stop();
//	}
//    DF_LCDXI2C_Stop();
//	///*********************************************************///
//	///*********************************************************///
//	///*********************************************************///
//	///*lcd on*///
////    DF_LCDI2C_Start();
////    DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );
////    DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_CMD_BlinkingOff );
////    DF_LCDI2C_Stop();
////	///*********************************************************///
////    DF_LCDXI2C_Start();
////    DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );
////    DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_CMD_BlinkingOff );
////    DF_LCDXI2C_Stop();
//	///*********************************************************///
//}
//#else

void InF_WriteLCD(uchar8 *p_databuff,uchar8 Len,uchar8 KillZero)
{
	uchar8 i;
	uchar8 V_LCDDataBuff[C_LCD_DataLen];			            ///*定义35字节缓冲区*///
	
	LCD_IO_Init;
	
	for(i=0;i<C_LCD_DataLen;i++)
	{
		V_LCDDataBuff[i] = 0;						            ///*35字节缓冲区清零*///
	}
	///*********************************************************///
	DF_Convert_TruthTable(p_databuff,&V_LCDDataBuff[0]);		///*真值表转换*///
    ///*********************************************************///
	///*进行灭零处理*///
	if( ( KillZero > 0 ) && ( KillZero <= C_KillZeroNumberNoCardIn) )   ///*不插卡情况下灭零
	{
		for(i=0;i<KillZero;i++)
		{
          V_LCDDataBuff[Table_LCDSegTable[Table_KillZero[i][0]]] &= Table_KillZero[i][2];
           V_LCDDataBuff[Table_LCDSegTable[Table_KillZero[i][1]]] &= Table_KillZero[i][2];
           V_LCDDataBuff[Table_LCDSegTable[Table_KillZero[i][1]]] &= 0xFE;
		}        
	}
       
	///*判断是否显示特殊字符,Err*///
	if( C_SF_Err == KillZero )
	{
        V_LCDDataBuff[Table_LCDSegTable[0]] &= 0xF0;      //数字3
        V_LCDDataBuff[Table_LCDSegTable[1]] &= 0xF0;
        for(i=21;i<=34;i++)                               //数字4-10
        {
            V_LCDDataBuff[Table_LCDSegTable[i]] &= 0xF0; 
        }
        V_LCDDataBuff[Table_LCDSegTable[0]]  &= 0x0F;     //数字13
        V_LCDDataBuff[Table_LCDSegTable[1]]  &= 0x0F;
        V_LCDDataBuff[Table_LCDSegTable[2]] &= 0xF0;      //数字14
        V_LCDDataBuff[Table_LCDSegTable[3]] &= 0xF0;   
        
        V_LCDDataBuff[Table_LCDSegTable[4]] &= 0xF0;      //数字15
        V_LCDDataBuff[Table_LCDSegTable[5]] &= 0xF1;      
        for(i=6;i<=11;i++)
        {
           V_LCDDataBuff[Table_LCDSegTable[i]] &= 0xF0;   //数字16-18
        }
        
        V_LCDDataBuff[Table_LCDSegTable[12]] &= 0xF0;      //数字19
        V_LCDDataBuff[Table_LCDSegTable[13]] &= 0xF1;      
        
        V_LCDDataBuff[Table_LCDSegTable[14]] &= 0xF0;      //数字20
        V_LCDDataBuff[Table_LCDSegTable[15]] &= 0xF1;   
        for(i=2;i<=5;i++)                                //数字23 24
        {
            V_LCDDataBuff[Table_LCDSegTable[i]] &= 0x0F; 
        }
        V_LCDDataBuff[Table_LCDSegTable[27]] |=0x08;      //7   E   AFGED  
        V_LCDDataBuff[Table_LCDSegTable[28]] |=0x0F;
        
        V_LCDDataBuff[Table_LCDSegTable[25]] |=0x00;     //8   r   GE 
        V_LCDDataBuff[Table_LCDSegTable[26]] |=0x06; 
        
        V_LCDDataBuff[Table_LCDSegTable[23]] |=0x00;     //9   r   GE 
        V_LCDDataBuff[Table_LCDSegTable[24]] |=0x06; 
        
        V_LCDDataBuff[Table_LCDSegTable[21]] |=0x00;     //10  -   G 
        V_LCDDataBuff[Table_LCDSegTable[22]] |=0x04; 
	}
    
	SF_TimeCheck();///*定时检查函数，如寄存器不正常则初始化显示
		
	DF_LCDI2C_Start();
 	DF_LCDI2C_WriteOneByte(C_LCD_BU9792_SlaveAddr_Write);
// 	DF_LCDI2C_WriteOneByte(C_LCD_BU9792_CMD_Mode);
// 	DF_LCDI2C_WriteOneByte(C_LCD_BU9792_CMD_Blink);
// 	DF_LCDI2C_WriteOneByte(C_LCD_BU9792_CMD_Pixel);
 	DF_LCDI2C_WriteOneByte(C_LCD_BU9792_CMD_LCDON);
 	DF_LCDI2C_WriteOneByte(C_LCD_BU9792_DataStartAddr);
	if( Len == C_LCDLen )
	{
		for(i = 0; i < C_LCD_DataLen; i++)
		{
			DF_LCDI2C_WriteOneByte( V_LCDDataBuff[i] );
	    }
	}
    DF_LCDI2C_Stop();
	///*********************************************************///
//    DF_LCDXI2C_Start();
// 	DF_LCDXI2C_WriteOneByte(C_LCD_BU9792_SlaveAddr_Write);
// 	DF_LCDXI2C_WriteOneByte(C_LCD_BU9792_CMD_Mode);
// 	DF_LCDXI2C_WriteOneByte(C_LCD_BU9792_CMD_Blink);
// 	DF_LCDXI2C_WriteOneByte(C_LCD_BU9792_CMD_Pixel);
// 	DF_LCDXI2C_WriteOneByte(C_LCD_BU9792_CMD_LCDON);
// 	DF_LCDXI2C_WriteOneByte(C_LCD_BU9792_DataStartAddr);
//	if( Len == C_LCDLen )
//	{
//		for(i = 0; i < C_LCD_DataLen; i++)
//		{
//        DF_LCDXI2C_WriteOneByte(V_LCDDataBuff[C_LCD_DataLen+i]);
//	  }
//	}
//    DF_LCDXI2C_Stop();
	///*********************************************************///
}
//#endif
///****************************************************************************///
///*函数原型   InF_WriteLCD_DispDynamicSign
///*函数功能   插卡显示动态符号“-” ，DynamicSignNum为0时显示第一个“-”
///*输入参数	
///*输出参数   无
///*返回参数   无
///*全局变量 	
///*函数备注	
///****************************************************************************///
void InF_WriteLCD_DispDynamicSign(uchar8 *p_databuff,uchar8 DynamicSignNum)
{
    uchar8 i;
	uchar8 V_LCDDataBuff[C_LCD_DataLen];		///*定义35字节缓冲区*///
	
	LCD_IO_Init;

    for(i=0;i<=9;i++)                          ///*非状态显示区域灭零*///                      
    {
      p_databuff[i] = 0;	
    }
    p_databuff[10]&=0x1F;        
	p_databuff[13]&=0xFE;                      ///*失败字符取消显示*///
    p_databuff[14]&=0x7F;                      ///*成功字符取消显示*///    
    p_databuff[17] = 0;	
    p_databuff[18] = 0;	
    p_databuff[19] = 0;	
    p_databuff[20] = 0;
    p_databuff[21] = 0;
    p_databuff[22]&= 0xC0;
    p_databuff[23] = 0;
    p_databuff[24] = 0;
    p_databuff[25] = 0;
    p_databuff[28] = 0;
    
	for(i=0;i<C_LCD_DataLen;i++)
	{
		V_LCDDataBuff[i] = 0;						            ///*35字节缓冲区清零*///
	}

    DF_Convert_TruthTable(p_databuff,&V_LCDDataBuff[0]);	   ///*真值表转换*///

    
    for(i=0;i<	C_KillZeroTotalNumber;i++)                     ///*动态显示时，主屏区数字不显示*///
    {
      V_LCDDataBuff[Table_LCDSegTable[Table_KillZero[i][0]]] &= Table_KillZero[i][2];
      V_LCDDataBuff[Table_LCDSegTable[Table_KillZero[i][1]]] &= Table_KillZero[i][2];
      if((i==10)||(i==18)||(i==19))
      {
          V_LCDDataBuff[Table_LCDSegTable[Table_KillZero[i][1]]] &= 0x7F;
      }
      else
      {
        V_LCDDataBuff[Table_LCDSegTable[Table_KillZero[i][1]]] &= 0xFE;
      }
    }   
    
    if(DynamicSignNum>=9)                                     ///*动态显示时，显示的“-”符号*///
    {
      V_LCDDataBuff[Table_LCDSegTable[C_DispData12DEGF_Addr]]|=0x04;
      for(i=0;i<=8;i++)
      {
        V_LCDDataBuff[Table_LCDSegTable[Table_KillZero[i][1]]]|=0x04;
      }
    }
    else
    {
      for(i=0;i<=DynamicSignNum;i++)
      {
        V_LCDDataBuff[Table_LCDSegTable[Table_KillZero[i][1]]]|=0x04;
      }
    }
    
    
	SF_TimeCheck();///*定时检查函数，如寄存器不正常则初始化显示
		
	DF_LCDI2C_Start();
 	DF_LCDI2C_WriteOneByte(C_LCD_BU9792_SlaveAddr_Write);
 	DF_LCDI2C_WriteOneByte(C_LCD_BU9792_CMD_LCDON);
 	DF_LCDI2C_WriteOneByte(C_LCD_BU9792_DataStartAddr);
    for(i = 0; i < C_LCD_DataLen; i++)
    {
        DF_LCDI2C_WriteOneByte( V_LCDDataBuff[i] );
    }
    DF_LCDI2C_Stop();
}
///**************************************************************************************************///
///*函数原型：void InF_InitLCD(void)                                                                *///
///*功能描述：初始化LCD                                                                             *///
///*输入参数：                                                                                      *///
///*输出参数：                                                                                      *///
///*返回参数：                                                                                      *///
///*功能说明：将LCD驱动配置为有电模式或低功耗模式                                                   *///
///*调用机制：                                                                                      *///
///*备    注：                                                                                      *///
///**************************************************************************************************///
///********macro pcb板号********///
//#define	C_Pcb1512			0x01			///*0.2S表的主板板号，无费控功能*///
//#define	C_Pcb1595       	0x02            ///*智能表的主板板号，有费控功能：本地和远程都有*///
//#if	( C_PcbVersion == C_Pcb1512 )		///*0.2S表*///
//void InF_InitLCD(void)
//{
//	uchar8 i;
//	LCD_IO_Init;
//	///*********************************************************///
//	DF_LCDI2C_Stop();
//	
//	InF_Delay_2us();
//	InF_Delay_2us();
//	DF_LCDI2C_Start();
//	DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//	DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_DataStartAddr );		///*初始化data address*///
//	for(i = 0; i < C_LCD_DataLen; i++)							///*数据区清零*///
//	{
//		DF_LCDI2C_WriteOneByte( C_LCD_Data_Zero );
//	}
//	DF_LCDI2C_Stop();
//	
//	InF_Delay_2us();
//	InF_Delay_2us();
//	DF_LCDI2C_Start();
//	DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//	DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_CMD_Mode_On );		///*工作模式*///
//	DF_LCDI2C_Stop();
//	
//	InF_Delay_2us();
//	InF_Delay_2us();
//	DF_LCDI2C_Start();
//	DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//	DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_CMD_IVA );			///*IVA配置*///
//	DF_LCDI2C_Stop();
//	
//	InF_Delay_2us();
//	InF_Delay_2us();
//	DF_LCDI2C_Start();
//	DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//	DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_CMD_BlinkingOff );	///*闪烁方式*///
//	DF_LCDI2C_Stop();
//	///*********************************************************///
//	DF_LCDXI2C_Stop();
//	
//	InF_Delay_2us();
//	InF_Delay_2us();
//	DF_LCDXI2C_Start();
//	DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCDX的从地址*///
//	DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_DataStartAddr );		///*初始化data address*///
//	for(i = 0; i < C_LCD_DataLen; i++)							///*数据区清零*///
//	{
//		DF_LCDXI2C_WriteOneByte( C_LCD_Data_Zero );
//	}
//	DF_LCDXI2C_Stop();
//	
//	InF_Delay_2us();
//	InF_Delay_2us();
//	DF_LCDXI2C_Start();
//	DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//	DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_CMD_Mode_On );		///*工作模式*///
//	DF_LCDXI2C_Stop();
//	
//	InF_Delay_2us();
//	InF_Delay_2us();
//	DF_LCDXI2C_Start();
//	DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//	DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_CMD_IVA );			///*IVA配置*///
//	DF_LCDXI2C_Stop();
//	
//	InF_Delay_2us();
//	InF_Delay_2us();
//	DF_LCDXI2C_Start();
//	DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//	DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_CMD_BlinkingOff );	///*闪烁方式*///
//	DF_LCDXI2C_Stop();
//	
//	///*********************************************************///
//	///*********************************************************///
//	///*lcd on*///
//    DF_LCDI2C_Start();
//    DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );
//    DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_CMD_BlinkingOff );
//    DF_LCDI2C_Stop();
//	///*********************************************************///
//    DF_LCDXI2C_Start();
//    DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );
//    DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_CMD_BlinkingOff );
//    DF_LCDXI2C_Stop();
//	///*********************************************************///
//}
//#else									///*1595*///

//#endif

///**************************************************************************************************///
///*函数原型：void InF_SwitchOffLCD(void)                                                           *///
///*功能描述：初始化LCD                                                                             *///
///*输入参数：无                                                                                    *///
///*输出参数：无                                                                                    *///
///*返回参数：无                                                                                    *///
///*功能说明：在电能表检测到掉电的时候，为了快速关闭LCD（掉电时如果不关闭LCD显示，                  *///
///*		  可能会产生鬼影，而将显示缓冲全写0的时间比直接关闭的时间长，因此直接使用LCD关闭命令）。*///
///*调用机制：检测到掉电调用一次。                                                                  *///
///*备    注：                                                                                      *///
///**************************************************************************************************///
///********macro pcb板号********///
//#define	C_Pcb1512			0x01			///*0.2S表的主板板号，无费控功能*///
//#define	C_Pcb1595       	0x02            ///*智能表的主板板号，有费控功能：本地和远程都有*///
//#if	( C_PcbVersion == C_Pcb1512 )		///*0.2S表*///
//void InF_SwitchOffLCD(void)
//{
//	///*********************************************************///
//	DF_LCDI2C_Start();
//	DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//	DF_LCDI2C_WriteOneByte( C_LCD_HT16C22_CMD_Mode_Off );		///*停止工作*///
//	DF_LCDI2C_Stop();
//	///*********************************************************///
//	DF_LCDXI2C_Start();
//	
//	InF_Delay_2us();
//	InF_Delay_2us();
//	DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_SlaveAddr_Write );	///*LCD的从地址*///
//	DF_LCDXI2C_WriteOneByte( C_LCD_HT16C22_CMD_Mode_Off );		///*停止工作*///
//	///*********************************************************///
//}
//#else
void InF_SwitchOffLCD(void)
{
	///*********************************************************///
	DF_LCDI2C_Start();
	DF_LCDI2C_WriteOneByte( C_LCD_BU9792_SlaveAddr_Write );		///*LCD的从地址*///
	DF_LCDI2C_WriteOneByte( C_LCD_BU9792_CMD_LCDOFF );			///*停止工作*///
	DF_LCDI2C_Stop();
	///*********************************************************///
}


//#endif







