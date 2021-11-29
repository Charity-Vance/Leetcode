
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     FRAMDrive.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   外部FRAM的驱动文件
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


#include "FRAMDrive.h"

///*底层驱动函数											*///
///*所有的底层驱动函数使用static定义，只能在该.c里面调用。	*///

///***********************************************************************************///
///*Function：
///*Description：FRAM写使能
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：数据层写FRAM前根据安全流程字操作该口线
///*Tips：
///*Others：
///***********************************************************************************///
void InF_FRAMWPEnable(void)
{
	FRAM_WP_Output_0;
	FRAM_Set_WP_Output;
}

///***********************************************************************************///
///*Function：
///*Description：FRAM写禁止
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：写函数完成后调用
///*Tips：
///*Others：
///***********************************************************************************///
void InF_FRAMWPDisable(void)
{
	FRAM_WP_Output_1;
	FRAM_Set_WP_Output;
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
static uchar8 DF_FRAMI2C_ReadOneByteAck(void)
{
	uchar8 i = C_FRAM_BitLen;
	uchar8 V_Value = 0;
	
	FRAM_Set_Sda_Input;
	
	while( i > 0 )
	{
		FRAM_Scl_Output_1;
		V_Value = V_Value<<1;
		i--;
		if( FRAM_Read_Sda )
		{
			V_Value |= 0x01;
		}
		FRAM_Scl_Output_0;
		InF_Delay_2us();
	}
	
	FRAM_Sda_Output_0;
	FRAM_Set_Sda_Output;
	InF_Delay_2us();
	FRAM_Scl_Output_1;
	InF_Delay_2us();
	
	FRAM_Scl_Output_0;
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
static uchar8 DF_FRAMI2C_ReadOneByteNoAck(void)
{
	uchar8 i = C_FRAM_BitLen;
	uchar8 V_Value = 0;

	FRAM_Set_Sda_Input;

	while( i > 0 )
	{
	FRAM_Scl_Output_1;
	V_Value = V_Value<<1;
	i--;
	InF_Delay_2us();
	if( FRAM_Read_Sda )
	{
		V_Value |= 0x01;
	}
	FRAM_Scl_Output_0;
	InF_Delay_2us();
	}

	FRAM_Sda_Output_1;
	FRAM_Set_Sda_Output;
	InF_Delay_2us();
	FRAM_Scl_Output_1;
	InF_Delay_2us();

	FRAM_Scl_Output_0;
	return V_Value;
}
///***********************************************************************************///
///*Function：
///*Description：向FRAM写一个字节
///*Input：
///*Output：
///*Return：返回值会体现I2C是否错误，C_Ok或C_IICError
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
static uchar8 DF_FRAMI2C_WriteOneByte(uchar8 V_Data)
{
	uchar8 V_Value = C_OK;
  char8 i = C_FRAM_BitLen;	///*每字节的位数*///
    
	//FRAM_Scl_Output_0;		///*写数据在start之后，所以scl处于低，sda为输出态，此处可以去掉*///
	//FRAM_Set_Scl_Output;
	//InF_Delay_2us();
	FRAM_Set_Sda_Output;
	
    while( i > 0 )
    {
    	if( (V_Data & C_FRAM_MostSignificantBit) == C_FRAM_MostSignificantBit )
    	{
    		FRAM_Sda_Output_1;
    	}
    	else
    	{
    		FRAM_Sda_Output_0;
    	}
        V_Data = V_Data<<1;
    	InF_Delay_2us();
        FRAM_Scl_Output_1;
    	InF_Delay_2us();
        FRAM_Scl_Output_0;
        i--;
    }
    FRAM_Set_Sda_Input;
    InF_Delay_2us();
    FRAM_Scl_Output_1;
    InF_Delay_2us();
    if( FRAM_Read_Sda )///*增加出错处理
    {
			V_Value = C_IICError;
    }
    FRAM_Scl_Output_0;
	
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
static void DF_FRAMI2C_Start(void)///*置位SDA前，是否需要判断SDA
{
	FRAM_Scl_Output_0;
	FRAM_Set_Scl_Output;
	InF_Delay_2us();
	FRAM_Sda_Output_1;
	FRAM_Set_Sda_Output;
	InF_Delay_2us();
	FRAM_Scl_Output_1;
	InF_Delay_2us();
	FRAM_Sda_Output_0;
	InF_Delay_2us();
	FRAM_Scl_Output_0;
}
///***********************************************************************************///
///*Function：软复位铁电
///*Description：连续发9个start，软复位铁电
///*Input：
///*Output：
///*Return：
///*Calls：在初始化函数及写数据失败时(即ACK判断错误)，调用软复位铁电
///*Called By：
///*Influence：
///*Tips：9个start进行软复位
///*Others：
///***********************************************************************************///
void DF_SoftResetFRAM(void)
{
	DF_FRAMI2C_Start();
	DF_FRAMI2C_Start();	
	DF_FRAMI2C_Start();
	DF_FRAMI2C_Start();
	DF_FRAMI2C_Start();
	DF_FRAMI2C_Start();
	DF_FRAMI2C_Start();
	DF_FRAMI2C_Start();
	DF_FRAMI2C_Start();			
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
static void DF_FRAMI2C_Stop(void)
{
	uchar8 V_Counter;
	for(V_Counter = C_FRAM_Max_StopTimes;V_Counter > 0;V_Counter--)
	{
		FRAM_Scl_Output_0;
		FRAM_Set_Scl_Output;
		InF_Delay_2us();
		FRAM_Set_Sda_Input;
		InF_Delay_2us();
		if(FRAM_Read_Sda )
		{
			break;
		}
		FRAM_Scl_Output_1;
		InF_Delay_2us();
		if(FRAM_Read_Sda )
		{
			break;
		}
	}
	FRAM_Scl_Output_0;
	InF_Delay_2us();
	FRAM_Sda_Output_0;
	FRAM_Set_Sda_Output;
	InF_Delay_2us();
	FRAM_Scl_Output_1;
	InF_Delay_2us();
	FRAM_Sda_Output_1;
	InF_Delay_2us();
	InF_Delay_2us();
	FRAM_Scl_Output_0;
	InF_Delay_2us();
	FRAM_Set_Sda_Input;
	InF_Delay_2us();
}
///***********************************************************************************///
///*Function：读接口函数
///*Description：将FRAM中地址FRAMAddr开始的长度为Len的数据读取到指定缓冲区
///*Input：
	///*FRAMAddr：16位的FRAM地址           *///
	///**p_databuff：指定缓冲区首地址  *///
	///*Len：长度，要读取的FRAM数据的长度*///
///*Output：数据缓冲区中的数据
///*Return：C_Ok：读取成功；C_IICError：I2c故障，读取不成功；C_DataLenError：长度超
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
uchar8 InF_ReadFRAM(ushort16 FRAMAddr,uchar8 *p_databuff,ushort16 Len)
{
	uchar8 *j;
	ushort16 i;
	uchar8 V_addr;
	
	FRAM_IO_Init;
	
	DF_FRAMI2C_Start();
	
	if( Len > C_FRAM_MaxLen )
	{
		DF_FRAMI2C_Stop();
		return	C_DataLenError;
	}
	
	V_addr=(FRAMAddr&C_FRAM_GetHighAddr)>>7;///*取高三位地址	
	if( DF_FRAMI2C_WriteOneByte(C_FRAM_SlaveAddr_Write|V_addr) == C_IICError )
	{
		DF_FRAMI2C_Stop();
		DF_SoftResetFRAM();
		DF_FRAMI2C_Stop();
		return	C_IICError;
	}

	if(DF_FRAMI2C_WriteOneByte( (uchar8)FRAMAddr ) == C_IICError )
	{
		DF_FRAMI2C_Stop();
		DF_SoftResetFRAM();
		DF_FRAMI2C_Stop();
		return	C_IICError;
	}
	
	j= p_databuff;
	
	DF_FRAMI2C_Start();

	if(DF_FRAMI2C_WriteOneByte( C_FRAM_SlaveAddr_Read|V_addr ) == C_IICError )
	{
		DF_FRAMI2C_Stop();
		DF_SoftResetFRAM();
		DF_FRAMI2C_Stop();
		return	C_IICError;
	}
	for(i=0;i<(Len-1);i++)
	{
		*j=DF_FRAMI2C_ReadOneByteAck();

		j++;
	}
	*j = DF_FRAMI2C_ReadOneByteNoAck();
	
	DF_FRAMI2C_Stop();
	
	return C_OK;
}
///***********************************************************************************///
///*Function：写接口函数
///*Description：将指定缓冲区中长度为Len的数据写入 FRAM中地址FRAMAddr开始的存储区
///*Input：
	///*FRAMAddr：16位的FRAM地址           *///
	///**p_databuff：指定缓冲区首地址  *///
	///*Len：长度，要写入的FRAM数据的长度*///
///*Output：
///*Return：C_Ok：写成功；C_IICError：I2c故障，写不成功；C_DataLenError：长度超
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
uchar8 InF_WriteFRAM(ushort16 FRAMAddr,uchar8 *p_databuff,ushort16 Len)
{
	ushort16 i,V_LenBuff;
	uchar8 *j;
	uchar8 V_addr;
	
	FRAM_IO_Init;
	
	V_LenBuff = Len;
	
	if((V_LenBuff > C_FRAM_MaxLen ) || (V_LenBuff == 0))
	{
		//DF_FRAMI2C_Stop();
		return	C_DataLenError;
	}

	if(C_FRAM_MaxBit&FRAMAddr)///*地址超
	{
		return	C_DataLenError;
	}

	if((FRAMAddr+V_LenBuff)>C_FRAM_MaxAddr)///*地址超
	{
		return	C_DataLenError;
	}	
	
	V_addr=(FRAMAddr&C_FRAM_GetHighAddr)>>7;///*取高三位地址		

	DF_FRAMI2C_Start();
	if( DF_FRAMI2C_WriteOneByte(C_FRAM_SlaveAddr_Write|V_addr) == C_IICError )
	{
		DF_FRAMI2C_Stop();
		DF_SoftResetFRAM();
		DF_FRAMI2C_Stop();
		InF_FRAMWPDisable();
		return	C_IICError;
	}
		
	if(DF_FRAMI2C_WriteOneByte( (uchar8)FRAMAddr) == C_IICError )
	{
		DF_FRAMI2C_Stop();
		DF_SoftResetFRAM();
		DF_FRAMI2C_Stop();
		InF_FRAMWPDisable();
		return	C_IICError;
	}
	
	j=p_databuff;	
	for(i=0;i<V_LenBuff;i++)
	{
		if( DF_FRAMI2C_WriteOneByte(*j) == C_IICError )
	  {
			DF_FRAMI2C_Stop();
			DF_SoftResetFRAM();
			DF_FRAMI2C_Stop();
			InF_FRAMWPDisable();
			return	C_IICError;
		}
	  j++;
	}

	DF_FRAMI2C_Stop();
	InF_FRAMWPDisable();
	return C_OK;
}
///***********************************************************************************///
///*Function：FRAM清零接口函数
///*Description：将FRAM中地址FRAMAddr开始的长度为Len的存储区清零
///*Input：
	///*FRAMAddr：16位的FRAM地址           *///
	///*Len：长度，要清零的FRAM数据的长度*///
///*Output：
///*Return：C_Ok：清零成功；C_IICError：I2c故障，清零不成功；C_DataLenError：长度超过256
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///
uchar8 InF_ClearFRAM(ushort16 FRAMAddr,ushort16 Len)
{
	ushort16 i,V_LenBuff;
	uchar8 V_Zero = C_WriteZero;
	uchar8 V_addr;
	
	V_LenBuff = Len;
	
	if((V_LenBuff > C_FRAM_MaxLen ) || (V_LenBuff == 0))
	{
		return	C_DataLenError;
	}
	
	if(C_FRAM_MaxBit&FRAMAddr)///*地址超
	{
		return	C_DataLenError;
	}
	
	if((FRAMAddr+V_LenBuff)>C_FRAM_MaxAddr)///*地址超
	{
		return	C_DataLenError;
	}	
	
	V_addr=(FRAMAddr&C_FRAM_GetHighAddr)>>7;///*取高三位地址		
	DF_FRAMI2C_Start();
	if( DF_FRAMI2C_WriteOneByte(C_FRAM_SlaveAddr_Write|V_addr) == C_IICError )
	{
		DF_FRAMI2C_Stop();
		DF_SoftResetFRAM();
		DF_FRAMI2C_Stop();
		InF_FRAMWPDisable();
		return	C_IICError;
	}		
		
	if(DF_FRAMI2C_WriteOneByte( (uchar8)FRAMAddr) == C_IICError )
	{
		DF_FRAMI2C_Stop();
		DF_SoftResetFRAM();
		DF_FRAMI2C_Stop();
		InF_FRAMWPDisable();
		return	C_IICError;
	}

	for(i=0;i<V_LenBuff;i++)
	{
		if( DF_FRAMI2C_WriteOneByte(V_Zero) == C_IICError )
	  {
			DF_FRAMI2C_Stop();
			DF_SoftResetFRAM();
			DF_FRAMI2C_Stop();
			InF_FRAMWPDisable();
			return	C_IICError;
	  }
	}
	DF_FRAMI2C_Stop();
	
	InF_FRAMWPDisable();
	return C_OK;
}

///***********************************************************************************///
///*Function：初始化接口函数
///*Description：初始化FRAM的I2C总线
///*Input：
///*Output：
///*Return：
///*Calls：主调度上电、进低功耗各调用一次
///*Called By：
///*Influence：该函数实际就是发“stop→start→stop”，目的是使得I2C总线空闲，使得FRAM功耗最低。
///*Tips：9个start进行软复位
///*Others：
///***********************************************************************************///
void InF_InitFRAM(void)
{
	FRAM_IO_Init;
	DF_FRAMI2C_Stop();
	DF_SoftResetFRAM();		
	DF_FRAMI2C_Stop();
}

///***********************************************************************************///
///*Function：
///*Description：低功耗下FRAM口线的配置
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：目的是使得FRAM口线输入，降低功耗
///*Tips：
///*Others：
///***********************************************************************************///
void InF_ConfigFRAMInPowerOff(void)
{
	FRAM_Set_WP_Input;
	FRAM_Set_Sda_Input;
	FRAM_Set_Scl_Input;
}
