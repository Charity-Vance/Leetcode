
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     FRAMDrive.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   �ⲿFRAM�������ļ�
///*Function List: 
///*****************************************************************************************///
///*History1:      ��1���޸�
///*����1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*����2. Date:
///*   	   Author:
///*       Modification:
		///*********************************************************************************///
///*History2:      ��2���޸�
///*����1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*����2. Date:
///*   	   Author:
///*       Modification:
///*****************************************************************************************///


#include "FRAMDrive.h"

///*�ײ���������											*///
///*���еĵײ���������ʹ��static���壬ֻ���ڸ�.c������á�	*///

///***********************************************************************************///
///*Function��
///*Description��FRAMдʹ��
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence�����ݲ�дFRAMǰ���ݰ�ȫ�����ֲ����ÿ���
///*Tips��
///*Others��
///***********************************************************************************///
void InF_FRAMWPEnable(void)
{
	FRAM_WP_Output_0;
	FRAM_Set_WP_Output;
}

///***********************************************************************************///
///*Function��
///*Description��FRAMд��ֹ
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence��д������ɺ����
///*Tips��
///*Others��
///***********************************************************************************///
void InF_FRAMWPDisable(void)
{
	FRAM_WP_Output_1;
	FRAM_Set_WP_Output;
}


///***********************************************************************************///
///*Function��
///*Description����1�ֽ����ݴ�Ack����������ֵ��Ϊ����ֵ
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
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
///*Function��
///*Description����1�ֽ����ݲ���Ack����������ֵ��Ϊ����ֵ
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
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
///*Function��
///*Description����FRAMдһ���ֽ�
///*Input��
///*Output��
///*Return������ֵ������I2C�Ƿ����C_Ok��C_IICError
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
///***********************************************************************************///
static uchar8 DF_FRAMI2C_WriteOneByte(uchar8 V_Data)
{
	uchar8 V_Value = C_OK;
  char8 i = C_FRAM_BitLen;	///*ÿ�ֽڵ�λ��*///
    
	//FRAM_Scl_Output_0;		///*д������start֮������scl���ڵͣ�sdaΪ���̬���˴�����ȥ��*///
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
    if( FRAM_Read_Sda )///*���ӳ�����
    {
			V_Value = C_IICError;
    }
    FRAM_Scl_Output_0;
	
	return V_Value;
}
///***********************************************************************************///
///*Function��
///*Description����ʼ
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
///***********************************************************************************///
static void DF_FRAMI2C_Start(void)///*��λSDAǰ���Ƿ���Ҫ�ж�SDA
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
///*Function����λ����
///*Description��������9��start����λ����
///*Input��
///*Output��
///*Return��
///*Calls���ڳ�ʼ��������д����ʧ��ʱ(��ACK�жϴ���)��������λ����
///*Called By��
///*Influence��
///*Tips��9��start������λ
///*Others��
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
///*Function��
///*Description��ֹͣ
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
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
///*Function�����ӿں���
///*Description����FRAM�е�ַFRAMAddr��ʼ�ĳ���ΪLen�����ݶ�ȡ��ָ��������
///*Input��
	///*FRAMAddr��16λ��FRAM��ַ           *///
	///**p_databuff��ָ���������׵�ַ  *///
	///*Len�����ȣ�Ҫ��ȡ��FRAM���ݵĳ���*///
///*Output�����ݻ������е�����
///*Return��C_Ok����ȡ�ɹ���C_IICError��I2c���ϣ���ȡ���ɹ���C_DataLenError�����ȳ�
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
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
	
	V_addr=(FRAMAddr&C_FRAM_GetHighAddr)>>7;///*ȡ����λ��ַ	
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
///*Function��д�ӿں���
///*Description����ָ���������г���ΪLen������д�� FRAM�е�ַFRAMAddr��ʼ�Ĵ洢��
///*Input��
	///*FRAMAddr��16λ��FRAM��ַ           *///
	///**p_databuff��ָ���������׵�ַ  *///
	///*Len�����ȣ�Ҫд���FRAM���ݵĳ���*///
///*Output��
///*Return��C_Ok��д�ɹ���C_IICError��I2c���ϣ�д���ɹ���C_DataLenError�����ȳ�
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
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

	if(C_FRAM_MaxBit&FRAMAddr)///*��ַ��
	{
		return	C_DataLenError;
	}

	if((FRAMAddr+V_LenBuff)>C_FRAM_MaxAddr)///*��ַ��
	{
		return	C_DataLenError;
	}	
	
	V_addr=(FRAMAddr&C_FRAM_GetHighAddr)>>7;///*ȡ����λ��ַ		

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
///*Function��FRAM����ӿں���
///*Description����FRAM�е�ַFRAMAddr��ʼ�ĳ���ΪLen�Ĵ洢������
///*Input��
	///*FRAMAddr��16λ��FRAM��ַ           *///
	///*Len�����ȣ�Ҫ�����FRAM���ݵĳ���*///
///*Output��
///*Return��C_Ok������ɹ���C_IICError��I2c���ϣ����㲻�ɹ���C_DataLenError�����ȳ���256
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
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
	
	if(C_FRAM_MaxBit&FRAMAddr)///*��ַ��
	{
		return	C_DataLenError;
	}
	
	if((FRAMAddr+V_LenBuff)>C_FRAM_MaxAddr)///*��ַ��
	{
		return	C_DataLenError;
	}	
	
	V_addr=(FRAMAddr&C_FRAM_GetHighAddr)>>7;///*ȡ����λ��ַ		
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
///*Function����ʼ���ӿں���
///*Description����ʼ��FRAM��I2C����
///*Input��
///*Output��
///*Return��
///*Calls���������ϵ硢���͹��ĸ�����һ��
///*Called By��
///*Influence���ú���ʵ�ʾ��Ƿ���stop��start��stop����Ŀ����ʹ��I2C���߿��У�ʹ��FRAM������͡�
///*Tips��9��start������λ
///*Others��
///***********************************************************************************///
void InF_InitFRAM(void)
{
	FRAM_IO_Init;
	DF_FRAMI2C_Stop();
	DF_SoftResetFRAM();		
	DF_FRAMI2C_Stop();
}

///***********************************************************************************///
///*Function��
///*Description���͹�����FRAM���ߵ�����
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence��Ŀ����ʹ��FRAM�������룬���͹���
///*Tips��
///*Others��
///***********************************************************************************///
void InF_ConfigFRAMInPowerOff(void)
{
	FRAM_Set_WP_Input;
	FRAM_Set_Sda_Input;
	FRAM_Set_Scl_Input;
}
