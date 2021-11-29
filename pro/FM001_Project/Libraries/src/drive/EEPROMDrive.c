
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     EEPROMDrive.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   �ⲿEE�������ļ�
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


#include "EEPROMDrive.h"




///*�ײ���������											*///
///*���еĵײ���������ʹ��static���壬ֻ���ڸ�.c������á�	*///
///*E2��I2C�ٶ��ݶ�Ϊ200kHz��                            	*///

///***********************************************************************************///
///*Function��
///*Description��E2дʹ��
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence�����ݲ�дE2ǰ���ݰ�ȫ�����ֲ����ÿ���
///*Tips��
///*Others��
///***********************************************************************************///
void InF_E2WPEnable(void)
{
	EE_WP_Output_0;
	EE_Set_WP_Output;
}

///***********************************************************************************///
///*Function��
///*Description��E2д��ֹ
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence��д������ɺ����
///*Tips��
///*Others��
///***********************************************************************************///
void InF_E2WPDisable(void)
{
	EE_WP_Output_1;
	EE_Set_WP_Output;
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
///*Function��
///*Description����E2дһ���ֽ�
///*Input��
///*Output��
///*Return������ֵ������I2C�Ƿ����C_Ok��C_IICError
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
///***********************************************************************************///
static uchar8 DF_E2I2C_WriteOneByte(uchar8 V_Data)
{
	uchar8 V_Value = C_OK;
    char8 i = C_E2_BitLen;	///*ÿ�ֽڵ�λ��*///
    
	//EE_Scl_Output_0;		///*д������start֮������scl���ڵͣ�sdaΪ���̬���˴�����ȥ��*///
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
///*Function��
///*Description���ж�E2�Ƿ��ڿ���״̬:ST��E2����ͨ������ʼ->��д����->�Ƿ��յ�ACK���ж�E2�Ƿ����
///*Input��
///*Output��
///*Return:C_E2_Idle:����;C_E2_Busy:æ
///*Calls��
///*Called By��
///*Influence��Ŀ����ʹ��E2�������룬���͹���
///*Tips��1.�����ʱ13ms,���13ms�ڶ��ղ���ACK,�򷵻ش����־
///*Others��
///***********************************************************************************///
uchar8 SF_Judge_E2_Busy( void )
{
	
	InF_Delay_us_Start( C_E2_Write_Delay );		/* ������ʱ��ʱ�� */
	
	for(;;)
	{
		DF_E2I2C_Start();			/* ����ʼ */
		if( DF_E2I2C_WriteOneByte( C_EE_SlaveAddr_Write ) == C_OK )
		{
			InF_Delay_us_Stop();
			return C_E2_Idle;		/* ���ؿ��б�־ */
		}
		if( InF_Delay_us_Finish() == C_OK )
		{					/* ��ʱʱ�䵽��,��Ȼû���յ�ACK,��ʾE2����,����æ��־ */
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
///*Function�����ӿں���
///*Description����E2�е�ַE2Addr��ʼ�ĳ���ΪLen�����ݶ�ȡ��ָ��������
///*Input��
	///*E2Addr��16λ��E2��ַ           *///
	///**p_databuff��ָ���������׵�ַ  *///
	///*Len�����ȣ�Ҫ��ȡ��E2���ݵĳ���*///
///*Output�����ݻ������е�����
///*Return��C_Ok����ȡ�ɹ���C_IICError��I2c���ϣ���ȡ���ɹ���C_DataLenError�����ȳ���256
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
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
///*Function��д�ӿں���
///*Description����ָ���������г���ΪLen������д�� E2�е�ַE2Addr��ʼ�Ĵ洢��
///*Input��
	///*E2Addr��16λ��E2��ַ           *///
	///**p_databuff��ָ���������׵�ַ  *///
	///*Len�����ȣ�Ҫд���E2���ݵĳ���*///
///*Output��
///*Return��C_Ok��д�ɹ���C_IICError��I2c���ϣ�д���ɹ���C_DataLenError�����ȳ���256
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
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
	
	t = (E2Addr & C_E2_InternalPageAddr) + V_LenBuff;				///*�ж��Ƿ��ҳ*///
	if( t <= C_E2_Max_Len )											///*��ʼ��ַ+Ҫд�����ݳ���ȫ����ͬһҳ��*///
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
		
		if( SF_Judge_E2_Busy() == C_E2_Idle )	/* �ж�E2�Ƿ������:��д���� */
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
			
			if( SF_Judge_E2_Busy() == C_E2_Busy )	/* �ж�E2�Ƿ������:��д���� */
			{
				DF_E2I2C_Start();
				DF_E2I2C_Stop();
				InF_E2WPDisable();
				return	C_IICError;
			}
		}
		/* ����SF_Judge_E2_Busy()�����ж��Ƿ���е�ʱ��,������ʼ��д����,�˴��������� */
		DF_E2I2C_Start();
		DF_E2I2C_Stop();
	}

	InF_E2WPDisable();
	return C_OK;
}
///***********************************************************************************///
///*Function��E2����ӿں���
///*Description����E2�е�ַE2Addr��ʼ�ĳ���ΪLen�Ĵ洢������
///*Input��
	///*E2Addr��16λ��E2��ַ           *///
	///*Len�����ȣ�Ҫ�����E2���ݵĳ���*///
///*Output��
///*Return��C_Ok������ɹ���C_IICError��I2c���ϣ����㲻�ɹ���C_DataLenError�����ȳ���256
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
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
	
	t = (E2Addr & C_E2_InternalPageAddr) + V_LenBuff;				///*�ж��Ƿ��ҳ*///
	if( t <= C_E2_Max_Len )											///*��ʼ��ַ+Ҫд�����ݳ���ȫ����ͬһҳ��*///
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
		if( SF_Judge_E2_Busy() == C_E2_Idle )	/* �ж�E2�Ƿ������:��д���� */
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
			
			if( SF_Judge_E2_Busy() == C_E2_Busy )	/* �ж�E2�Ƿ������:��д���� */
			{
				DF_E2I2C_Start();
				DF_E2I2C_Stop();
				InF_E2WPDisable();
				return	C_IICError;
			}
		}
		/* ����SF_Judge_E2_Busy()�����ж��Ƿ���е�ʱ��,������ʼ��д����,�˴��������� */
		DF_E2I2C_Start();
		DF_E2I2C_Stop();
	}

	InF_E2WPDisable();
	return C_OK;
}
///***********************************************************************************///
///*Function����ʼ���ӿں���
///*Description����ʼ��E2��I2C����
///*Input��
///*Output��
///*Return��
///*Calls���������ϵ硢���͹��ĸ�����һ��
///*Called By��
///*Influence���ú���ʵ�ʾ��Ƿ���stop��start��stop����Ŀ����ʹ��I2C���߿��У�ʹ��E2������͡�
///*Tips��
///*Others��
///***********************************************************************************///
void InF_InitE2(void)
{
	EE_IO_Init;
	DF_E2I2C_Stop();
	DF_E2I2C_Start();
	DF_E2I2C_Stop();
}

///***********************************************************************************///
///*Function��
///*Description���͹�����E2���ߵ�����
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence��Ŀ����ʹ��E2�������룬���͹���
///*Tips��
///*Others��
///***********************************************************************************///
void InF_ConfigE2InPowerOff(void)
{
	EE_Set_WP_Input;
	EE_Set_Sda_Input;
	EE_Set_Scl_Input;
}
