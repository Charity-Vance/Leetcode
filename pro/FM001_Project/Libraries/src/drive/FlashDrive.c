
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     FlashDrive.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   外部Flash驱动文件
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


#include "FlashDrive.h"


///*Flash的SPI操作采用模式0：sck空闲为低，在每个周期的第一个时钟沿采样*///


///***********************************************************************************///
///*Function：
///*Description：
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：
///*Tips：
///*Others：
///***********************************************************************************///





///**************************************************************************************************///
///*函数原型：void InF_Delay_1us					                                                *///
///*输入参数：																					    *///
///*输出参数：无                                                                                    *///
///*返回参数：无                                                                                    *///
///*功能说明：以1us为单位进行延时，此延时是在该接口函数中死等。                                     *///
///*备    注：                                                                                      *///
///**************************************************************************************************///
void InF_Delay_1us(void)
{
	__NOP();
}

///**************************************************************************************************///
///*函数原型：void DF_SetIO_DOFR()					                                                *///
///*功能说明：双线读取数据时,将spi口线配置一下                                     *///
///**************************************************************************************************///
void DF_SetIO_DOFR(void)
{
	Flash_Sck_Output_0;
	Flash_Set_Sdi_Input;
	Flash_Set_Sdo_Input;
}

///**************************************************************************************************///
///*函数原型：void DF_SetIO_DIFP()					                                                *///
///*功能说明：双线写数据时,将spi口线配置一下                                     *///
///**************************************************************************************************///
void DF_SetIO_DIFP(void)
{
	Flash_Sck_Output_0;
	Flash_Set_SDO_Output;
	Flash_Set_SDI_Output;
}

///***********************************************************************************///
///*函数原型：static uchar8 DF_FLASHSPI_ReadOneByte(void)                     	 	 *///
///*功能描述：将1字节数据读出，返回值即为读出值。                                  	 *///
///*备    注：采用1根数据线进行SPI的通信                                           	 *///
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
///*函数原型：static uchar8 DF_FLASHSPI_ReadOneByte_DOFR(void)                    	   *///
///*功能描述：将1字节数据读出，采用Dual Output Fast Read (DOFR)的方法，返回值即为读出值*///
///*备    注：采用2根数据线进行SPI的通信  	                                           *///
///*          调用本函数前,需要将sdi/sdo配置为输入,本函数为节省时间不单独配置          *///
///*************************************************************************************///
static uchar8 DF_FLASHSPI_ReadOneByte_DOFR(void)
{
	uchar8 i,V_ReadData = 0;
	///*下面口线的操作放到调用的地方,多字节读取节省时间*///
	//Flash_Sck_Output_0;
	//Flash_Set_Sdi_Input;
	//Flash_Set_Sdo_Input;
	
	for( i=0;i<4;i++ )		///*双线操作,仅需4个时钟*///
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
///*函数原型：static void DF_FLASHSPI_WriteOneByte(uchar8 V_Data)	      	     	*///
///*功能描述：将1字节数据写入Flash。                                                *///
///*备    注：采用1根数据线进行SPI的通信                                            *///
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
///*函数原型：static void DF_FLASHSPI_WriteOneByte_DIFP(uchar8 V_Data)	         	*///
///*功能描述：将1字节数据写入，采用Dual Iutput Fast Program(DIFP)的方法				*///
///*备    注：采用2根数据线进行SPI的通信                                            *///
//*           调用本函数前,需要将sdi/sdo配置为输出,本函数为节省时间不单独配置       *///
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
///*函数原型：static void DF_FLASHSPI_WriteAddr(ulong32 V_FlashAddr)      	     	*///
///*功能描述：将Flash内部数据3字节地址从SPI总线发送出去                             *///
///*备    注：采用1根数据线进行SPI的通信                                            *///
///**********************************************************************************///
static void DF_FLASHSPI_WriteAddr(ulong32 V_FlashAddr)
{
	ulong32 j;
	uchar8 i;
	
	Flash_Sck_Output_0;
	Flash_Set_SDO_Output;
	j = V_FlashAddr<<8;				///*低3字节为flash内部数据地址*///
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
///*Function：
///*Description：片选Flash
///*Input：
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：在片选前，将时钟线拉低：采用SPI模式0
///*Tips：
///*Others：
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
///*函数原型：static void InF_FlashChipDeselect (void)                          	*///
///*功能描述：取消片选。                                                            *///
///***********************************************************************************///
void InF_FlashChipDeselect(void)
{
	Flash_CS_Output_1;
	Flash_Set_CS_Output;
	Flash_CS_Output_1;
}


///**********************************************************************************///
///*函数原型：static void DF_CheckAndWaitFlash(void)								*///
///*功能描述：检查Flash是否处于busy状态，处于busy状态则一直等到非busy状态，最多等待160ms就强制退出*///
///**********************************************************************************///
static void DF_CheckAndWaitFlash(void)
{
	uchar8 V_Status;
	uchar8 i = C_FLASH_WaitLimited;
	
	InF_FlashChipSelect();
	DF_FLASHSPI_WriteOneByte(C_FLASH_CMD_RDSR);
	
	while( i != 0 )		///*最多延时200ms*///
	{
		V_Status = DF_FLASHSPI_ReadOneByte();
		//if( ((V_Status & C_FLASH_STATUS_WIP )==0) || ( V_Status & C_FLASH_STATUS_REASONABLE )  )
		if( (V_Status & C_FLASH_STATUS_WIP )==0  )
		{
			InF_FlashChipDeselect();
			return;
		}
		InF_Delay_us(C_FLASH_WaitTime);		///*延时2.5ms*///
		i -= 1;
	}
	InF_FlashChipDeselect();
}


/*******************************************************************************
函数原型：void InF_ReadFlash(ulong32 V_FlashAddr, uchar8 *p_databuff, ushort16 Len)
功能描述：为方便生产检验,支持读Flash芯片ID，
输入参数：V_FlashAddr：32位的Flash地址;*p_databuff：指定缓冲区首地址;Len：长度，要读取的Flash数据的长度
输出参数：*p_databuff：指定缓冲区首地址
返回参数：无
调用位置：该函数由InF_ReadFlash接口函数调用
备    注：
*******************************************************************************/
void SF_ReadFlashSign(ulong32 V_FlashAddr, uchar8 *p_databuff, ushort16 Len)
{
	ushort16 V_uci;
	uchar8 *P_ucdata;
	
	DF_FLASHSPI_WriteOneByte(C_FLASH_CMD_RDID_ANY);	/* 读1-3,读芯片ID */
	
	P_ucdata = p_databuff;
	
	for(V_uci = 0; V_uci < Len; V_uci ++)
	{
		*P_ucdata = DF_FLASHSPI_ReadOneByte();		
		 P_ucdata ++;
	}
	InF_FlashChipDeselect();	
}

///***********************************************************************************///
///*Function：读接口函数
///*Description：将Flash中地址V_FlashAddr开始的长度为Len的数据读取到指定缓冲区
///*Input：
	///*V_FlashAddr：32位的Flash地址
	///**p_databuff：指定缓冲区首地址
	///*Len：长度，要读取的Flash数据的长度
///*Output：数据缓冲区中的数据
///*Return：
///*Calls：
///*Called By：
///*Influence：读Flash时，将数据取反后再送入缓冲区；写与此相对应，也是取反后再写入Flash。
///*Tips：采用双线读取的方式
///*Others：
///***********************************************************************************///
void InF_ReadFlash(ulong32 V_FlashAddr,uchar8 *p_databuff,ushort16 Len)
{
	ushort16 i;
	uchar8 *p_data;
	
	
	DF_CheckAndWaitFlash();
	
	InF_FlashChipSelect();
	
	if(V_FlashAddr == C_FlashAddrFactory)	/*读Flash芯片ID*/
	{
		SF_ReadFlashSign(V_FlashAddr, p_databuff, Len);
		return;
	}
	
	if( (Len > C_ReadFlash_MaxLen) || ((V_FlashAddr & C_FlashAddr_Invalid) != 0) || (Len==0) )
	{
		InF_FlashChipDeselect();
		return;
	}
	
    DF_FLASHSPI_WriteOneByte(C_FLASH_CMD_DOFR);	///*双线读取*///
    DF_FLASHSPI_WriteAddr(V_FlashAddr);
    ///*双线操作,需要发送一个空字节*///
	DF_FLASHSPI_WriteOneByte(C_FLASH_DATA_DUMMY);
	///*将数据线配置为输入*///
	DF_SetIO_DOFR();
	
	p_data = p_databuff;
	for(i=0;i<Len;i++)
	{
		*p_data = ( ~DF_FLASHSPI_ReadOneByte_DOFR() );		///*读出的数据取反*///
		 p_data++;
	}
	
	InF_FlashChipDeselect();
}

///***********************************************************************************///
///*Function：写接口函数
///*Description：将指定缓冲区中长度为Len的数据写入 E2中地址E2Addr开始的存储区
///*Input：
	///*V_FlashAddr：32位的Flash地址:有效地址22位,高10位无效,如果地址超过22位直接返回
	///**p_databuff：指定缓冲区首地址
	///*Len：长度，要写入的Flash数据的长度,最大不超过1026字节
///*Output：数据缓冲区中的数据
///*Return：
///*Calls：
///*Called By：
///*Influence：写Flash时，将数据取反后再写入；读与此相对应，也是取反后再送入缓冲区。
///*Tips：如果只写1字节,采用单线写(因为双线写有奇偶地址的限制),超过1字节就用双线写
///*Others：
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
			///*没有跨页写:Flash最多一次只能写256字节*///
			j = Len;
			Len = 0;
		}
		else	///*跨页写*///
		{
			///*计算本次要写的长度=下页首地址-当前地址*///
			j = ( ((byteaddr+C_FlashPageLen)&0xffffff00)-byteaddr );
			Len -= j;											///*长度调整*///
		}
		/* 旺宏芯片只支持单线写 */
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
			DF_FLASHSPI_WriteOneByte(~*p_data);		///*取反写入*///
			p_data++;
		}
		
		InF_FlashChipDeselect();
		InF_Delay_us(C_Flash_Write_Delay);
		
		
		byteaddr += C_FlashPageLen;							///*地址调整*///
		byteaddr &= 0xffffff00;
	}
	
	DF_CheckAndWaitFlash();
}

///***********************************************************************************///
///*Function：擦除接口函数
///*Description：将指定Flash的页擦除
///*Input：V_FlashAddr：32位的Flash地址
///*Output：
///*Return：
///*Calls：
///*Called By：
///*Influence：擦除V_FlashAddr所在的Subsector (4-Kbyte)的Flash空间
///*Tips：
///*Others：
///***********************************************************************************///
void InF_EraseFlash(ulong32 V_FlashAddr)
{
	DF_CheckAndWaitFlash();
	
	InF_FlashChipSelect();							///*写使能*///
	DF_FLASHSPI_WriteOneByte(C_FLASH_CMD_WREN);
	InF_FlashChipDeselect();
	
	InF_Delay_2us();
	InF_Delay_2us();
	InF_Delay_2us();
	
	InF_FlashChipSelect();							///*写使能*///
	DF_FLASHSPI_WriteOneByte(C_FLASH_CMD_SSE);		///*发SSE命令*///
	DF_FLASHSPI_WriteAddr(V_FlashAddr);
	InF_FlashChipDeselect();
	
	DF_CheckAndWaitFlash();
}
