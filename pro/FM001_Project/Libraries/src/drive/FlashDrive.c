
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     FlashDrive.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   �ⲿFlash�����ļ�
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


#include "FlashDrive.h"


///*Flash��SPI��������ģʽ0��sck����Ϊ�ͣ���ÿ�����ڵĵ�һ��ʱ���ز���*///


///***********************************************************************************///
///*Function��
///*Description��
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence��
///*Tips��
///*Others��
///***********************************************************************************///





///**************************************************************************************************///
///*����ԭ�ͣ�void InF_Delay_1us					                                                *///
///*���������																					    *///
///*�����������                                                                                    *///
///*���ز�������                                                                                    *///
///*����˵������1usΪ��λ������ʱ������ʱ���ڸýӿں��������ȡ�                                     *///
///*��    ע��                                                                                      *///
///**************************************************************************************************///
void InF_Delay_1us(void)
{
	__NOP();
}

///**************************************************************************************************///
///*����ԭ�ͣ�void DF_SetIO_DOFR()					                                                *///
///*����˵����˫�߶�ȡ����ʱ,��spi��������һ��                                     *///
///**************************************************************************************************///
void DF_SetIO_DOFR(void)
{
	Flash_Sck_Output_0;
	Flash_Set_Sdi_Input;
	Flash_Set_Sdo_Input;
}

///**************************************************************************************************///
///*����ԭ�ͣ�void DF_SetIO_DIFP()					                                                *///
///*����˵����˫��д����ʱ,��spi��������һ��                                     *///
///**************************************************************************************************///
void DF_SetIO_DIFP(void)
{
	Flash_Sck_Output_0;
	Flash_Set_SDO_Output;
	Flash_Set_SDI_Output;
}

///***********************************************************************************///
///*����ԭ�ͣ�static uchar8 DF_FLASHSPI_ReadOneByte(void)                     	 	 *///
///*������������1�ֽ����ݶ���������ֵ��Ϊ����ֵ��                                  	 *///
///*��    ע������1�������߽���SPI��ͨ��                                           	 *///
///***********************************************************************************///
static uchar8 DF_FLASHSPI_ReadOneByte(void)
{
	uchar8 i,V_ReadData = 0;
	
	Flash_Sck_Output_0;
	Flash_Set_Sdi_Input;
	
	for( i=0;i<8;i++ )
	{
		Flash_Sck_Output_1;
		InF_Delay_1us();
		V_ReadData <<= 1;
		if( Flash_Read_Sdi  )
		{
			V_ReadData |= 0x01;
		}
		Flash_Sck_Output_0;
		InF_Delay_1us();
	}
	return V_ReadData;
}

///*************************************************************************************///
///*����ԭ�ͣ�static uchar8 DF_FLASHSPI_ReadOneByte_DOFR(void)                    	   *///
///*������������1�ֽ����ݶ���������Dual Output Fast Read (DOFR)�ķ���������ֵ��Ϊ����ֵ*///
///*��    ע������2�������߽���SPI��ͨ��  	                                           *///
///*          ���ñ�����ǰ,��Ҫ��sdi/sdo����Ϊ����,������Ϊ��ʡʱ�䲻��������          *///
///*************************************************************************************///
static uchar8 DF_FLASHSPI_ReadOneByte_DOFR(void)
{
	uchar8 i,V_ReadData = 0;
	///*������ߵĲ����ŵ����õĵط�,���ֽڶ�ȡ��ʡʱ��*///
	//Flash_Sck_Output_0;
	//Flash_Set_Sdi_Input;
	//Flash_Set_Sdo_Input;
	
	for( i=0;i<4;i++ )		///*˫�߲���,����4��ʱ��*///
	{
		Flash_Sck_Output_1;
		//InF_Delay_1us();
		V_ReadData <<= 1;
		if( Flash_Read_Sdi )
		{
			V_ReadData |= 0x01;
		}
		V_ReadData <<= 1;
		if( Flash_Read_Sdo )
		{
			V_ReadData |= 0x01;
		}
		Flash_Sck_Output_0;
		//InF_Delay_1us();
	}
	return V_ReadData;
}
///**********************************************************************************///
///*����ԭ�ͣ�static void DF_FLASHSPI_WriteOneByte(uchar8 V_Data)	      	     	*///
///*������������1�ֽ�����д��Flash��                                                *///
///*��    ע������1�������߽���SPI��ͨ��                                            *///
///**********************************************************************************///
static void DF_FLASHSPI_WriteOneByte(uchar8 V_Data)
{
	uchar8 i;
	
	Flash_Sck_Output_0;
	Flash_Set_SDO_Output;
	
	for( i=0;i<8;i++ )
	{
        if( V_Data&0x80 )
        {
        	Flash_Sdo_Output_1;
        }
        else
        {
        	Flash_Sdo_Output_0;
        }
        InF_Delay_1us();
        Flash_Sck_Output_1;
        InF_Delay_1us();
        Flash_Sck_Output_0;
        V_Data = V_Data<<1;
	}
}
///**********************************************************************************///
///*����ԭ�ͣ�static void DF_FLASHSPI_WriteOneByte_DIFP(uchar8 V_Data)	         	*///
///*������������1�ֽ�����д�룬����Dual Iutput Fast Program(DIFP)�ķ���				*///
///*��    ע������2�������߽���SPI��ͨ��                                            *///
//*           ���ñ�����ǰ,��Ҫ��sdi/sdo����Ϊ���,������Ϊ��ʡʱ�䲻��������       *///
///**********************************************************************************///
//static void DF_FLASHSPI_WriteOneByte_DIFP(uchar8 V_Data)
//{
//	uchar8 i;
//	
//	//Flash_Sck_Output_0;
//	//Flash_Set_SDO_Output;
//	
//	for( i=0;i<4;i++ )
//	{
//        if( V_Data&0x80 )
//        {
//        	Flash_Sdi_Output_1;
//        }
//        else
//        {
//        	Flash_Sdi_Output_0;
//        }
//        
//        V_Data = V_Data<<1;
//        if( V_Data&0x80 )
//        {
//        	Flash_Sdo_Output_1;
//        }
//        else
//        {
//        	Flash_Sdo_Output_0;
//        }
//        InF_Delay_1us();
//        Flash_Sck_Output_1;
//        InF_Delay_1us();
//        Flash_Sck_Output_0;
//        V_Data = V_Data<<1;
//	}
//}

///**********************************************************************************///
///*����ԭ�ͣ�static void DF_FLASHSPI_WriteAddr(ulong32 V_FlashAddr)      	     	*///
///*������������Flash�ڲ�����3�ֽڵ�ַ��SPI���߷��ͳ�ȥ                             *///
///*��    ע������1�������߽���SPI��ͨ��                                            *///
///**********************************************************************************///
static void DF_FLASHSPI_WriteAddr(ulong32 V_FlashAddr)
{
	ulong32 j;
	uchar8 i;
	
	Flash_Sck_Output_0;
	Flash_Set_SDO_Output;
	j = V_FlashAddr<<8;				///*��3�ֽ�Ϊflash�ڲ����ݵ�ַ*///
	for( i=0;i<24;i++ )
	{
        if( j&0x80000000 )
        {
        	Flash_Sdo_Output_1;
        }
        else
        {
        	Flash_Sdo_Output_0;
        }
        InF_Delay_1us();
        Flash_Sck_Output_1;
        InF_Delay_1us();
        Flash_Sck_Output_0;
        j = j<<1;
	}
}

///***********************************************************************************///
///*Function��
///*Description��ƬѡFlash
///*Input��
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence����Ƭѡǰ����ʱ�������ͣ�����SPIģʽ0
///*Tips��
///*Others��
///***********************************************************************************///
void InF_FlashChipSelect(void)
{
	Flash_Sck_Output_0;
	Flash_Set_Sck_Output;
	Flash_Sck_Output_0;
	Flash_Set_Sdi_Input;
	InF_Delay_2us();
	Flash_CS_Output_0;
	Flash_Set_CS_Output;
	Flash_CS_Output_0;
}

///***********************************************************************************///
///*����ԭ�ͣ�static void InF_FlashChipDeselect (void)                          	*///
///*����������ȡ��Ƭѡ��                                                            *///
///***********************************************************************************///
void InF_FlashChipDeselect(void)
{
	Flash_CS_Output_1;
	Flash_Set_CS_Output;
	Flash_CS_Output_1;
}


///**********************************************************************************///
///*����ԭ�ͣ�static void DF_CheckAndWaitFlash(void)								*///
///*�������������Flash�Ƿ���busy״̬������busy״̬��һֱ�ȵ���busy״̬�����ȴ�160ms��ǿ���˳�*///
///**********************************************************************************///
static void DF_CheckAndWaitFlash(void)
{
	uchar8 V_Status;
	uchar8 i = C_FLASH_WaitLimited;
	
	InF_FlashChipSelect();
	DF_FLASHSPI_WriteOneByte(C_FLASH_CMD_RDSR);
	
	while( i != 0 )		///*�����ʱ200ms*///
	{
		V_Status = DF_FLASHSPI_ReadOneByte();
		//if( ((V_Status & C_FLASH_STATUS_WIP )==0) || ( V_Status & C_FLASH_STATUS_REASONABLE )  )
		if( (V_Status & C_FLASH_STATUS_WIP )==0  )
		{
			InF_FlashChipDeselect();
			return;
		}
		InF_Delay_us(C_FLASH_WaitTime);		///*��ʱ2.5ms*///
		i -= 1;
	}
	InF_FlashChipDeselect();
}


/*******************************************************************************
����ԭ�ͣ�void InF_ReadFlash(ulong32 V_FlashAddr, uchar8 *p_databuff, ushort16 Len)
����������Ϊ������������,֧�ֶ�FlashоƬID��
���������V_FlashAddr��32λ��Flash��ַ;*p_databuff��ָ���������׵�ַ;Len�����ȣ�Ҫ��ȡ��Flash���ݵĳ���
���������*p_databuff��ָ���������׵�ַ
���ز�������
����λ�ã��ú�����InF_ReadFlash�ӿں�������
��    ע��
*******************************************************************************/
void SF_ReadFlashSign(ulong32 V_FlashAddr, uchar8 *p_databuff, ushort16 Len)
{
	ushort16 V_uci;
	uchar8 *P_ucdata;
	
	DF_FLASHSPI_WriteOneByte(C_FLASH_CMD_RDID_ANY);	/* ��1-3,��оƬID */
	
	P_ucdata = p_databuff;
	
	for(V_uci = 0; V_uci < Len; V_uci ++)
	{
		*P_ucdata = DF_FLASHSPI_ReadOneByte();		
		 P_ucdata ++;
	}
	InF_FlashChipDeselect();	
}

///***********************************************************************************///
///*Function�����ӿں���
///*Description����Flash�е�ַV_FlashAddr��ʼ�ĳ���ΪLen�����ݶ�ȡ��ָ��������
///*Input��
	///*V_FlashAddr��32λ��Flash��ַ
	///**p_databuff��ָ���������׵�ַ
	///*Len�����ȣ�Ҫ��ȡ��Flash���ݵĳ���
///*Output�����ݻ������е�����
///*Return��
///*Calls��
///*Called By��
///*Influence����Flashʱ��������ȡ���������뻺������д������Ӧ��Ҳ��ȡ������д��Flash��
///*Tips������˫�߶�ȡ�ķ�ʽ
///*Others��
///***********************************************************************************///
void InF_ReadFlash(ulong32 V_FlashAddr,uchar8 *p_databuff,ushort16 Len)
{
	ushort16 i;
	uchar8 *p_data;
	
	
	DF_CheckAndWaitFlash();
	
	InF_FlashChipSelect();
	
	if(V_FlashAddr == C_FlashAddrFactory)	/*��FlashоƬID*/
	{
		SF_ReadFlashSign(V_FlashAddr, p_databuff, Len);
		return;
	}
	
	if( (Len > C_ReadFlash_MaxLen) || ((V_FlashAddr & C_FlashAddr_Invalid) != 0) || (Len==0) )
	{
		InF_FlashChipDeselect();
		return;
	}
	
    DF_FLASHSPI_WriteOneByte(C_FLASH_CMD_DOFR);	///*˫�߶�ȡ*///
    DF_FLASHSPI_WriteAddr(V_FlashAddr);
    ///*˫�߲���,��Ҫ����һ�����ֽ�*///
	DF_FLASHSPI_WriteOneByte(C_FLASH_DATA_DUMMY);
	///*������������Ϊ����*///
	DF_SetIO_DOFR();
	
	p_data = p_databuff;
	for(i=0;i<Len;i++)
	{
		*p_data = ( ~DF_FLASHSPI_ReadOneByte_DOFR() );		///*����������ȡ��*///
		 p_data++;
	}
	
	InF_FlashChipDeselect();
}

///***********************************************************************************///
///*Function��д�ӿں���
///*Description����ָ���������г���ΪLen������д�� E2�е�ַE2Addr��ʼ�Ĵ洢��
///*Input��
	///*V_FlashAddr��32λ��Flash��ַ:��Ч��ַ22λ,��10λ��Ч,�����ַ����22λֱ�ӷ���
	///**p_databuff��ָ���������׵�ַ
	///*Len�����ȣ�Ҫд���Flash���ݵĳ���,��󲻳���1026�ֽ�
///*Output�����ݻ������е�����
///*Return��
///*Calls��
///*Called By��
///*Influence��дFlashʱ��������ȡ������д�룻��������Ӧ��Ҳ��ȡ���������뻺������
///*Tips�����ֻд1�ֽ�,���õ���д(��Ϊ˫��д����ż��ַ������),����1�ֽھ���˫��д
///*Others��
///***********************************************************************************///
void InF_WriteFlash(ulong32 V_FlashAddr,uchar8 *p_databuff,ushort16 Len)
{
	ulong32 byteaddr;
	uchar8 *p_data;
	ushort16 i,j;
	
	DF_CheckAndWaitFlash();
	
	if( (Len > C_ReadFlash_MaxLen) || ((V_FlashAddr & C_FlashAddr_Invalid) != 0) || (Len==0) )
	{
		return;
	}
	
	byteaddr = V_FlashAddr;
	p_data = p_databuff;
	
	while(Len>0)
	{
		if( (byteaddr&0xffffff00) == ((byteaddr+Len-1)&0xffffff00) )
		{
			///*û�п�ҳд:Flash���һ��ֻ��д256�ֽ�*///
			j = Len;
			Len = 0;
		}
		else	///*��ҳд*///
		{
			///*���㱾��Ҫд�ĳ���=��ҳ�׵�ַ-��ǰ��ַ*///
			j = ( ((byteaddr+C_FlashPageLen)&0xffffff00)-byteaddr );
			Len -= j;											///*���ȵ���*///
		}
		/* ����оƬֻ֧�ֵ���д */
		InF_FlashChipSelect();
		DF_FLASHSPI_WriteOneByte(C_FLASH_CMD_WREN);
		InF_FlashChipDeselect();
		InF_Delay_2us();
		InF_Delay_2us();
		InF_Delay_2us();
		InF_FlashChipSelect();
		DF_FLASHSPI_WriteOneByte(C_FLASH_CMD_PP);
		DF_FLASHSPI_WriteAddr(byteaddr);
		
		for(i=0;i<j;i++)
		{
			DF_FLASHSPI_WriteOneByte(~*p_data);		///*ȡ��д��*///
			p_data++;
		}
		
		InF_FlashChipDeselect();
		InF_Delay_us(C_Flash_Write_Delay);
		
		
		byteaddr += C_FlashPageLen;							///*��ַ����*///
		byteaddr &= 0xffffff00;
	}
	
	DF_CheckAndWaitFlash();
}

///***********************************************************************************///
///*Function�������ӿں���
///*Description����ָ��Flash��ҳ����
///*Input��V_FlashAddr��32λ��Flash��ַ
///*Output��
///*Return��
///*Calls��
///*Called By��
///*Influence������V_FlashAddr���ڵ�Subsector (4-Kbyte)��Flash�ռ�
///*Tips��
///*Others��
///***********************************************************************************///
void InF_EraseFlash(ulong32 V_FlashAddr)
{
	DF_CheckAndWaitFlash();
	
	InF_FlashChipSelect();							///*дʹ��*///
	DF_FLASHSPI_WriteOneByte(C_FLASH_CMD_WREN);
	InF_FlashChipDeselect();
	
	InF_Delay_2us();
	InF_Delay_2us();
	InF_Delay_2us();
	
	InF_FlashChipSelect();							///*дʹ��*///
	DF_FLASHSPI_WriteOneByte(C_FLASH_CMD_SSE);		///*��SSE����*///
	DF_FLASHSPI_WriteAddr(V_FlashAddr);
	InF_FlashChipDeselect();
	
	DF_CheckAndWaitFlash();
}
