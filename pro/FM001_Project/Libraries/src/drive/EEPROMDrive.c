
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     EEPROMDrive.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   外部EE的驱动文件
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


#include "EEPROMDrive.h"




///*底层驱动函数											*///
///*所有的底层驱动函数使用static定义，只能在该.c里面调用。	*///
///*E2的I2C速度暂定为200kHz。                            	*///

///***********************************************************************************///
///*Function：
///*Description：E2写使能
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：数据层写E2前根据安全流程字操作该口线
///*Tips：
///*Others：
///***********************************************************************************///
void InF_E2WPEnable(void)
{
	EE_WP_Output_0;
	EE_Set_WP_Output;
}

///***********************************************************************************///
///*Function：
///*Description：E2写禁止
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：写函数完成后调用
///*Tips：
///*Others：
///***********************************************************************************///
void InF_E2WPDisable(void)
{
	EE_WP_Output_1;
	EE_Set_WP_Output;
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
///*Others：
///***********************************************************************************///
static uchar8 DF_E2I2C_ReadOneByteAck(void)
{
	uchar8 i = C_E2_BitLen;
	uchar8 V_Value = 0;
	
	//EE_Scl_Output_0;
	//EE_Set_Scl_Output;
	EE_Set_Sda_Input;
	
	while( i > 0 )
	{
		EE_Scl_Output_1;
		V_Value = V_Value<<1;
		i--;
		if( EE_Read_Sda )
		{
			V_Value |= 0x01;
		}
		EE_Scl_Output_0;
		InF_Delay_2us();
	}
	
	EE_Sda_Output_0;
	EE_Set_Sda_Output;
	InF_Delay_2us();
	EE_Scl_Output_1;
	InF_Delay_2us();
	
	EE_Scl_Output_0;
	return V_Value;
}
///***********************************************************************************///
///*Function：
///*Description：将1字节数据不带Ack读出，返回值即为读出值
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
static uchar8 DF_E2I2C_ReadOneByteNoAck(void)
{
	uchar8 i = C_E2_BitLen;
	uchar8 V_Value = 0;

	//EE_Scl_Output_0;
	//EE_Set_Scl_Output;
	EE_Set_Sda_Input;

	while( i > 0 )
	{
	EE_Scl_Output_1;
	V_Value = V_Value<<1;
	i--;
	InF_Delay_2us();
	if( EE_Read_Sda )
	{
		V_Value |= 0x01;
	}
	EE_Scl_Output_0;
	InF_Delay_2us();
	}

	EE_Sda_Output_1;
	EE_Set_Sda_Output;
	InF_Delay_2us();
	EE_Scl_Output_1;
	InF_Delay_2us();

	EE_Scl_Output_0;
	return V_Value;
}
///***********************************************************************************///
///*Function：
///*Description：向E2写一个字节
///*Input：
///*Output：
///*Return：返回值会体现I2C是否错误，C_Ok或C_IICError
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
static uchar8 DF_E2I2C_WriteOneByte(uchar8 V_Data)
{
	uchar8 V_Value = C_OK;
    char8 i = C_E2_BitLen;	///*每字节的位数*///
    
	//EE_Scl_Output_0;		///*写数据在start之后，所以scl处于低，sda为输出态，此处可以去掉*///
	//EE_Set_Scl_Output;
	//InF_Delay_2us();
	EE_Set_Sda_Output;
	
    while( i > 0 )
    {
    	if( (V_Data & C_EE_MostSignificantBit) == C_EE_MostSignificantBit )
    	{
    		EE_Sda_Output_1;
    	}
    	else
    	{
    		EE_Sda_Output_0;
    	}
        V_Data = V_Data<<1;
    	InF_Delay_2us();
        EE_Scl_Output_1;
    	InF_Delay_2us();
        EE_Scl_Output_0;
        i--;
    }
    EE_Set_Sda_Input;
    InF_Delay_2us();
    EE_Scl_Output_1;
    InF_Delay_2us();
    if( EE_Read_Sda )
    {
		V_Value = C_IICError;
    }
    EE_Scl_Output_0;
	
	return V_Value;
}
///***********************************************************************************///
///*Function：
///*Description：起始
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
static void DF_E2I2C_Start(void)
{
	EE_Scl_Output_0;
	EE_Set_Scl_Output;
	InF_Delay_2us();
	EE_Sda_Output_1;
	EE_Set_Sda_Output;
	InF_Delay_2us();
	EE_Scl_Output_1;
	InF_Delay_2us();
	EE_Sda_Output_0;
	InF_Delay_2us();
	EE_Scl_Output_0;
}
///***********************************************************************************///
///*Function：
///*Description：停止
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
static void DF_E2I2C_Stop(void)
{
	uchar8 V_Counter;
	for(V_Counter = C_E2_Max_StopTimes;V_Counter > 0;V_Counter--)
	{
		EE_Scl_Output_0;
		EE_Set_Scl_Output;
		InF_Delay_2us();
		EE_Set_Sda_Input;
		InF_Delay_2us();
		if(EE_Read_Sda )
		{
			break;
		}
		EE_Scl_Output_1;
		InF_Delay_2us();
		if(EE_Read_Sda )
		{
			break;
		}
	}
	EE_Scl_Output_0;
	InF_Delay_2us();
	EE_Sda_Output_0;
	EE_Set_Sda_Output;
	InF_Delay_2us();
	EE_Scl_Output_1;
	InF_Delay_2us();
	EE_Sda_Output_1;
	InF_Delay_2us();
	InF_Delay_2us();
	EE_Scl_Output_0;
	InF_Delay_2us();
	EE_Set_Sda_Input;
	InF_Delay_2us();
}

///***********************************************************************************///
///*Function：
///*Description：判断E2是否处于空闲状态:ST的E2可以通过发起始->发写命令->是否收到ACK来判断E2是否空闲
///*Input：
///*Output：
///*Return:C_E2_Idle:空闲;C_E2_Busy:忙
///*Calls：
///*Called By：
///*Influence：目的是使得E2口线输入，降低功耗
///*Tips：1.最多延时13ms,如果13ms内都收不到ACK,则返回错误标志
///*Others：
///***********************************************************************************///
uchar8 SF_Judge_E2_Busy( void )
{
	
	InF_Delay_us_Start( C_E2_Write_Delay );		/* 起动总延时定时器 */
	
	for(;;)
	{
		DF_E2I2C_Start();			/* 发起始 */
		if( DF_E2I2C_WriteOneByte( C_EE_SlaveAddr_Write ) == C_OK )
		{
			InF_Delay_us_Stop();
			return C_E2_Idle;		/* 返回空闲标志 */
		}
		if( InF_Delay_us_Finish() == C_OK )
		{					/* 延时时间到了,仍然没有收到ACK,表示E2故障,返回忙标志 */
			return C_E2_Busy;
		}
		InF_Delay_2us();
		InF_Delay_2us();
		InF_Delay_2us();
		InF_Delay_2us();
		InF_Delay_2us();
		InF_Delay_2us();
		InF_Delay_2us();
		InF_Delay_2us();
		InF_Delay_2us();
		InF_Delay_2us();
	}
}

///***********************************************************************************///
///*Function：读接口函数
///*Description：将E2中地址E2Addr开始的长度为Len的数据读取到指定缓冲区
///*Input：
	///*E2Addr：16位的E2地址           *///
	///**p_databuff：指定缓冲区首地址  *///
	///*Len：长度，要读取的E2数据的长度*///
///*Output：数据缓冲区中的数据
///*Return：C_Ok：读取成功；C_IICError：I2c故障，读取不成功；C_DataLenError：长度超过256
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
uchar8 InF_ReadE2(ushort16 E2Addr,uchar8 *p_databuff,ushort16 Len)
{
	uchar8 *j;
	ushort16 i;
	EE_IO_Init;
	
	DF_E2I2C_Start();
	
	if( Len > C_E2_MaxLen )
	{
		DF_E2I2C_Stop();
		return	C_DataLenError;
	}

	if( DF_E2I2C_WriteOneByte(C_EE_SlaveAddr_Write) == C_IICError )
	{
		DF_E2I2C_Stop();
		return	C_IICError;
	}

	if(DF_E2I2C_WriteOneByte( (uchar8)(E2Addr >> 8) ) == C_IICError )
	{
		DF_E2I2C_Stop();
		return	C_IICError;
	}

	if(DF_E2I2C_WriteOneByte( (uchar8)E2Addr ) == C_IICError )
	{
		DF_E2I2C_Stop();
		return	C_IICError;
	}
	
	j= p_databuff;
	
	DF_E2I2C_Start();

	if(DF_E2I2C_WriteOneByte( C_EE_SlaveAddr_Read ) == C_IICError )
	{
		DF_E2I2C_Stop();
		return	C_IICError;
	}
	for(i=0;i<(Len-1);i++)
	{
		*j=DF_E2I2C_ReadOneByteAck();

		j++;
	}
	*j = DF_E2I2C_ReadOneByteNoAck();
	
	DF_E2I2C_Stop();
	
	return C_OK;
}
///***********************************************************************************///
///*Function：写接口函数
///*Description：将指定缓冲区中长度为Len的数据写入 E2中地址E2Addr开始的存储区
///*Input：
	///*E2Addr：16位的E2地址           *///
	///**p_databuff：指定缓冲区首地址  *///
	///*Len：长度，要写入的E2数据的长度*///
///*Output：
///*Return：C_Ok：写成功；C_IICError：I2c故障，写不成功；C_DataLenError：长度超过256
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
uchar8 InF_WriteE2(ushort16 E2Addr,uchar8 *p_databuff,ushort16 Len)
{
	ushort16 i,max_write_bytes,t,V_LenBuff;
	uchar8 *j;
	
	EE_IO_Init;
	
	V_LenBuff = Len;
	
	if( (V_LenBuff > C_E2_MaxLen ) || (V_LenBuff == 0) )
	{
		//DF_E2I2C_Stop();
		return	C_DataLenError;
	}
	
	t = (E2Addr & C_E2_InternalPageAddr) + V_LenBuff;				///*判断是否跨页*///
	if( t <= C_E2_Max_Len )											///*起始地址+要写的数据长度全部在同一页内*///
	{
		DF_E2I2C_Start();
		if( DF_E2I2C_WriteOneByte(C_EE_SlaveAddr_Write) == C_IICError )
		{
			DF_E2I2C_Stop();
			InF_E2WPDisable();
			return	C_IICError;
		}
		
		if(DF_E2I2C_WriteOneByte( (uchar8)(E2Addr >> 8) ) == C_IICError )
		{
			DF_E2I2C_Stop();
			InF_E2WPDisable();
			return	C_IICError;
		}
		
		if(DF_E2I2C_WriteOneByte( (uchar8)E2Addr) == C_IICError )
		{
			DF_E2I2C_Stop();
			InF_E2WPDisable();
			return	C_IICError;
		}
		
		j= p_databuff;
		
		for(i=0;i<V_LenBuff;i++)
		{
			if( DF_E2I2C_WriteOneByte(*j) == C_IICError )
		    {
				DF_E2I2C_Stop();
				InF_E2WPDisable();
				return	C_IICError;
		    }
		    j++;
		}
		
		DF_E2I2C_Stop();
		
		if( SF_Judge_E2_Busy() == C_E2_Idle )	/* 判断E2是否空闲了:即写结束 */
		{
			DF_E2I2C_Start();
			DF_E2I2C_Stop();
		}
		else
		{
			DF_E2I2C_Start();
			DF_E2I2C_Stop();
			InF_E2WPDisable();
			return	C_IICError;
		}
	}
    else
    {
    	j = p_databuff;
		
		DF_E2I2C_Start();
		
		if(DF_E2I2C_WriteOneByte(C_EE_SlaveAddr_Write) == C_IICError )
		{
			DF_E2I2C_Stop();
			InF_E2WPDisable();
			return	C_IICError;
		}
		
    	while(V_LenBuff > 0)
    	{
			
			if(DF_E2I2C_WriteOneByte((uchar8 )(E2Addr>>8)) == C_IICError )
			{
				DF_E2I2C_Stop();
				InF_E2WPDisable();
				return	C_IICError;
			}
			if(DF_E2I2C_WriteOneByte((uchar8 )E2Addr) == C_IICError )
			{
				DF_E2I2C_Stop();
				InF_E2WPDisable();
				return	C_IICError;
			}
			
			t = (E2Addr & C_E2_InternalPageAddr) + V_LenBuff;
			
			if( t > C_E2_Max_Len)
			{
				max_write_bytes = C_E2_Max_Len - ( ((uchar8)E2Addr) & C_E2_InternalPageAddr );
			}
			else
			{
				max_write_bytes = V_LenBuff;
			}
			for(i=0;i<max_write_bytes;i++)
			{
			    if(DF_E2I2C_WriteOneByte(*j) == C_IICError )
			    {
					DF_E2I2C_Stop();
					InF_E2WPDisable();
					return	C_IICError;
			    }
			    j++;
			    V_LenBuff--;
			}
			
			DF_E2I2C_Stop();
			E2Addr = ( C_E2_Max_Len +( E2Addr & (~C_E2_InternalPageAddr) ) );
			
			if( SF_Judge_E2_Busy() == C_E2_Busy )	/* 判断E2是否空闲了:即写结束 */
			{
				DF_E2I2C_Start();
				DF_E2I2C_Stop();
				InF_E2WPDisable();
				return	C_IICError;
			}
		}
		/* 上面SF_Judge_E2_Busy()函数判断是否空闲的时候,发了起始和写命令,此处结束操作 */
		DF_E2I2C_Start();
		DF_E2I2C_Stop();
	}

	InF_E2WPDisable();
	return C_OK;
}
///***********************************************************************************///
///*Function：E2清零接口函数
///*Description：将E2中地址E2Addr开始的长度为Len的存储区清零
///*Input：
	///*E2Addr：16位的E2地址           *///
	///*Len：长度，要清零的E2数据的长度*///
///*Output：
///*Return：C_Ok：清零成功；C_IICError：I2c故障，清零不成功；C_DataLenError：长度超过256
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
uchar8 InF_ClearE2(ushort16 E2Addr,ushort16 Len)
{
	ushort16 i,max_write_bytes,t,V_LenBuff;
	uchar8 V_Zero = C_WriteZero;
	
	V_LenBuff = Len;
	
	if( (V_LenBuff > C_E2_MaxLen ) || (V_LenBuff == 0) )
	{
		return	C_DataLenError;
	}
	
	t = (E2Addr & C_E2_InternalPageAddr) + V_LenBuff;				///*判断是否跨页*///
	if( t <= C_E2_Max_Len )											///*起始地址+要写的数据长度全部在同一页内*///
	{
		DF_E2I2C_Start();
		if( DF_E2I2C_WriteOneByte(C_EE_SlaveAddr_Write) == C_IICError )
		{
			DF_E2I2C_Stop();
			InF_E2WPDisable();
			return	C_IICError;
		}
		
		if(DF_E2I2C_WriteOneByte( (uchar8)(E2Addr >> 8) ) == C_IICError )
		{
			DF_E2I2C_Stop();
			InF_E2WPDisable();
			return	C_IICError;
		}
		
		if(DF_E2I2C_WriteOneByte( (uchar8)E2Addr) == C_IICError )
		{
			DF_E2I2C_Stop();
			InF_E2WPDisable();
			return	C_IICError;
		}

		for(i=0;i<V_LenBuff;i++)
		{
			if( DF_E2I2C_WriteOneByte(V_Zero) == C_IICError )
		    {
				DF_E2I2C_Stop();
				InF_E2WPDisable();
				return	C_IICError;
		    }
		}
		
		DF_E2I2C_Stop();
		if( SF_Judge_E2_Busy() == C_E2_Idle )	/* 判断E2是否空闲了:即写结束 */
		{
			DF_E2I2C_Start();
			DF_E2I2C_Stop();
		}
		else
		{
			DF_E2I2C_Start();
			DF_E2I2C_Stop();
			InF_E2WPDisable();
			return	C_IICError;
		}
	}
    else
    {
		DF_E2I2C_Start();
		
		if(DF_E2I2C_WriteOneByte(C_EE_SlaveAddr_Write) == C_IICError )
		{
			DF_E2I2C_Stop();
			InF_E2WPDisable();
			return	C_IICError;
		}
		
    	while(V_LenBuff > 0)
    	{
			
			if(DF_E2I2C_WriteOneByte((uchar8 )(E2Addr>>8)) == C_IICError )
			{
				DF_E2I2C_Stop();
				InF_E2WPDisable();
				return	C_IICError;
			}
			if(DF_E2I2C_WriteOneByte((uchar8 )E2Addr) == C_IICError )
			{
				DF_E2I2C_Stop();
				InF_E2WPDisable();
				return	C_IICError;
			}
			
			t = (E2Addr & C_E2_InternalPageAddr) + V_LenBuff;
			
			if( t > C_E2_Max_Len)
			{
				max_write_bytes = C_E2_Max_Len - ( ((uchar8)E2Addr) & C_E2_InternalPageAddr );
			}
			else
			{
				max_write_bytes = V_LenBuff;
			}
			for(i=0;i<max_write_bytes;i++)
			{
			    if(DF_E2I2C_WriteOneByte(V_Zero) == C_IICError )
			    {
					DF_E2I2C_Stop();
					InF_E2WPDisable();
					return	C_IICError;
			    }
			    V_LenBuff--;
			}
			
			DF_E2I2C_Stop();
			E2Addr = ( C_E2_Max_Len +( E2Addr & (~C_E2_InternalPageAddr) ) );
			
			if( SF_Judge_E2_Busy() == C_E2_Busy )	/* 判断E2是否空闲了:即写结束 */
			{
				DF_E2I2C_Start();
				DF_E2I2C_Stop();
				InF_E2WPDisable();
				return	C_IICError;
			}
		}
		/* 上面SF_Judge_E2_Busy()函数判断是否空闲的时候,发了起始和写命令,此处结束操作 */
		DF_E2I2C_Start();
		DF_E2I2C_Stop();
	}

	InF_E2WPDisable();
	return C_OK;
}
///***********************************************************************************///
///*Function：初始化接口函数
///*Description：初始化E2的I2C总线
///*Input：
///*Output：
///*Return：
///*Calls：主调度上电、进低功耗各调用一次
///*Called By：
///*Influence：该函数实际就是发“stop→start→stop”，目的是使得I2C总线空闲，使得E2功耗最低。
///*Tips：
///*Others：
///***********************************************************************************///
void InF_InitE2(void)
{
	EE_IO_Init;
	DF_E2I2C_Stop();
	DF_E2I2C_Start();
	DF_E2I2C_Stop();
}

///***********************************************************************************///
///*Function：
///*Description：低功耗下E2口线的配置
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：目的是使得E2口线输入，降低功耗
///*Tips：
///*Others：
///***********************************************************************************///
void InF_ConfigE2InPowerOff(void)
{
	EE_Set_WP_Input;
	EE_Set_Sda_Input;
	EE_Set_Scl_Input;
}
