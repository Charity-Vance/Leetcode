
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     SPI.c
///*Version:       V1
///*Date:          2016-8-25
///*Description:   spi配置与操作
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


#include "Public.h"
#include "SPI.h"
#include "IO.h"

///*********************************************************************************///
///*函数原型:void DF_SPI_Configuration_ETH( void )
///*输入参数: 无
///*输出参数: 无
///*返回参数: 无
///*功能说明:
///*	自测发现当ESAM口线配置为SPI接口时，然后停活ESAM，即关闭ESAM电源，但Vesam还有电压。
///*	需把ESAM接口重新定义为普通IO，同时输出低，此时Vesam电源才能为0，怀疑是IO有漏电。
///*********************************************************************************///
void InF_DeadESAM_SPI_Initial( void )
{
	ulong32 ulTemp_SPI;
////	ushort16 usTemp_SPI;
	/* MOSI口线 */
	IO_ESAMMOSI->BSRR = ESAMMOSIRESET;
	ulTemp_SPI = IO_ESAMMOSI->MODER;	/* MODER */
	ulTemp_SPI &= ESAMMOSI_IN_MODE;
	ulTemp_SPI |= ESAMMOSI_OUT_MODE;
	IO_ESAMMOSI->MODER = ulTemp_SPI;

	ulTemp_SPI = IO_ESAMMOSI->OTYPER;	/* OTYPER */
	ulTemp_SPI &= ESAMMOSI_OUTPUT_PP;
	IO_ESAMMOSI->OTYPER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMMOSI->PUPDR;	/* PUPDR */
	ulTemp_SPI &= ESAMMOSI_NOPUPD;
	IO_ESAMMOSI->PUPDR = ulTemp_SPI;
	
	IO_ESAMMOSI->BSRR = ESAMMOSIRESET;	/* 再次拉低口线 */
	/* MISO口线 ,没有必要设置为推挽输出低*/
//	IO_ESAMMISO->BSRR |= ESAMSCKRESET;	
	ulTemp_SPI = IO_ESAMMISO->MODER;	/* MODER */
	ulTemp_SPI &= ESAMMISO_IN_MODE;
//	ulTemp_SPI |= ESAMMISO_OUT_MODE;
	IO_ESAMMISO->MODER = ulTemp_SPI;	
	
//	ulTemp_SPI = IO_ESAMMISO->OTYPER;	/* OTYPER */
//	ulTemp_SPI &= ESAMMISO_OUTPUT_PP;
//	IO_ESAMMISO->OTYPER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMMISO->PUPDR;	/* PUPDR */
	ulTemp_SPI &= ESAMMISO_NOPUPD;
//	ulTemp_SPI |= ESAMMISO_PULLUP;
	IO_ESAMMISO->PUPDR = ulTemp_SPI;

	ulTemp_SPI = IO_ESAMMISO->INEN;	/* INEN */
	ulTemp_SPI |= ESAMMISO_INOn;
	IO_ESAMMISO->INEN = ulTemp_SPI;	
	
//	IO_ESAMMISO->BSRR |= ESAMSCKRESET;	/* 再次拉低口线 */
	/* SCK口线 */
	IO_ESAMSCK->BSRR = ESAMSCKRESET;
	ulTemp_SPI = IO_ESAMSCK->MODER;	/* MODER */
	ulTemp_SPI &= ESAMSCK_IN_MODE;
	ulTemp_SPI |= ESAMSCK_OUT_MODE;
	IO_ESAMSCK->MODER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMSCK->OTYPER;	/* OTYPER */
	ulTemp_SPI &= ESAMSCK_OUTPUT_PP;
	IO_ESAMSCK->OTYPER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMSCK->PUPDR;	/* PUPDR */
	ulTemp_SPI &= ESAMSCK_NOPUPD;
	IO_ESAMSCK->PUPDR = ulTemp_SPI;
	
	IO_ESAMSCK->BSRR = ESAMSCKRESET;	/* 再次拉低口线 */
	/* 关闭HSPI */
	SFR_ESAMCOM->SPICR2 &= (~CR2SPI_HSPIEN);
	/* CS口线 */
	InF_EsamChipSelect();	/* 经过测试,CS口线会有漏电流到ESAM电源,所以将CS口线拉低 */
}


///*********************************************************************************///
///*函数原型:void DF_SPI_Configuration_ETH( void )
///*输入参数: 无
///*输出参数: 无
///*返回参数: 无
///*功能说明:
///*	1) 配置spi口线:MOSI/MISO/SCK
///*	2) 将spi1配置为主模式,用于和ESAM通信
///*	3) spi时钟配置为4MHz:16MHz4分频后得到
///*	4) 使能spi外设
///*	5) 初始化完成后,SPI处于使能状态
///*	6) 片选在外面完成
///*********************************************************************************///
void DF_SPI_Configuration( void )
{
	ulong32 ulTemp_SPI;

	/* 使能RCC中的HSPI时钟 */
	Esam_SouceClock_SFR |= EsamSouceClock_EN;

	/* 选择HSPI的口线,并配置口线 */
	/* MOSI口线 */
	ulTemp_SPI = IO_ESAMMOSI->MODER;	/* MODER */
	ulTemp_SPI &= ESAMMOSI_IN_MODE;
	ulTemp_SPI |= IO_ESAMMOSI_AF;
	IO_ESAMMOSI->MODER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMMOSI->OTYPER;	/* OTYPER */
	ulTemp_SPI &= ESAMMOSI_OUTPUT_PP;
	IO_ESAMMOSI->OTYPER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMMOSI->PUPDR;	/* PUPDR */
	ulTemp_SPI &= ESAMMOSI_NOPUPD;
	IO_ESAMMOSI->PUPDR = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMMOSI->INEN;	/* INEN */
	ulTemp_SPI &= ESAMMOSI_INOff;
	IO_ESAMMOSI->INEN = ulTemp_SPI;
	
	/* MISO口线 */
	ulTemp_SPI = IO_ESAMMISO->MODER;	/* MODER */
	ulTemp_SPI &= ESAMMISO_IN_MODE;
	ulTemp_SPI |= IO_ESAMMISO_AF;
	IO_ESAMMISO->MODER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMMISO->OTYPER;	/* OTYPER */
	ulTemp_SPI &= ESAMMISO_OUTPUT_PP;
	IO_ESAMMISO->OTYPER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMMISO->PUPDR;	/* PUPDR */
	ulTemp_SPI &= ESAMMISO_NOPUPD;
	ulTemp_SPI |= ESAMMISO_PULLUP;
	IO_ESAMMISO->PUPDR = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMMISO->INEN;	/* INEN */
	ulTemp_SPI |= ESAMMISO_INOn;
	IO_ESAMMISO->INEN = ulTemp_SPI;
	
	/* SCK口线 */
	ulTemp_SPI = IO_ESAMSCK->MODER;	/* MODER */
	ulTemp_SPI &= ESAMSCK_IN_MODE;
	ulTemp_SPI |= IO_ESAMSCK_AF;
	IO_ESAMSCK->MODER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMSCK->OTYPER;	/* OTYPER */
	ulTemp_SPI &= ESAMSCK_OUTPUT_PP;
	IO_ESAMSCK->OTYPER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMSCK->PUPDR;	/* PUPDR */
	ulTemp_SPI &= ESAMSCK_NOPUPD;
	IO_ESAMSCK->PUPDR = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMSCK->INEN;	/* INEN */
	ulTemp_SPI &= ESAMSCK_INOff;
	IO_ESAMSCK->INEN = ulTemp_SPI;

	/* SFR */
	ulTemp_SPI = SFR_ESAMCOM->SPICR1;
	/* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
	ulTemp_SPI &= CR1_CLEAR_MASK_SPI;
	
	ulTemp_SPI |= (CR1SPI_Delay_Cfg|SPI_Mode_Master |CR1SPI_WAIT |
				SPI_BaudRatePrescaler_8|SPI_FirstBit_MSB|SPI_CPOL_High |SPI_CPHA_2Edge);
				
	SFR_ESAMCOM->SPICR1 = ulTemp_SPI;
	/*CR2*/
	ulTemp_SPI = SFR_ESAMCOM->SPICR2;
	ulTemp_SPI &= CR2_CLEAR_MASK_SPI;
	ulTemp_SPI |= (CR2SPI_FLTEN_On|CR2SPI_SSNM_Off|CR2SPI_TXO_AC_Off|CR2SPI_TXO_Off|
				CR2SPI_SSN_Low|CR2SPI_SSN_Soft|CR2SPI_HSPIDIS);
	SFR_ESAMCOM->SPICR2 = ulTemp_SPI;
	/*CR3*/
	SFR_ESAMCOM->SPICR3 |= 0x0000000F;///*清除发送、接收、缓存
	/*IE*/
	SFR_ESAMCOM->SPIIE |= 0x00000007;///*中断禁止
	/* 中断标志寄存器 */
	SFR_ESAMCOM->SPIIF |= 0x00000018;///*接收、发送缓存溢出标志清零
	
	ulTemp_SPI = SFR_ESAMCOM->SPIIF;///*清状态标志、接收缓存
	ulTemp_SPI = SFR_ESAMCOM->SPIRXBUF;
	/* 使能HSPI */
	SFR_ESAMCOM->SPICR2 |= CR2SPI_HSPIEN;
	ulTemp_SPI = SFR_ESAMCOM->SPIIF;
	ulTemp_SPI = SFR_ESAMCOM->SPIRXBUF;
}

///*********************************************************************************///
///*函数原型:void InF_EsamChipSelect( void )
///*输入参数: Esam片选有效
///*输出参数:无
///*返回参数:无
///*功能说明:CS采用软件控制的方法，内部带延时
///*********************************************************************************///
void InF_EsamChipSelect( void )
{
	ulong32 ulTemp_SPI,V_Delay;
	
	/* CS口线 */
	IO_ESAMCS->BSRR = ESAMCSRESET;	/* 首先拉低口线 */
	
	ulTemp_SPI = IO_ESAMCS->MODER;	/* MODER */
	ulTemp_SPI &= ESAMCS_IN_MODE;
	ulTemp_SPI |= ESAMCS_OUT_MODE;
	IO_ESAMCS->MODER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMCS->OTYPER;	/* OTYPER */
	ulTemp_SPI &= ESAMCS_OUTPUT_PP;
	IO_ESAMCS->OTYPER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMCS->PUPDR;	/* PUPDR */
	ulTemp_SPI &= ESAMCS_NOPUPD;
	IO_ESAMCS->PUPDR = ulTemp_SPI;
	
	IO_ESAMCS->BSRR = ESAMCSRESET;	/* 再次拉低口线 */
	///*拉低延时
	for( V_Delay=0;V_Delay<C_Esam_Tcsl100us;V_Delay++)
	{
		InF_Delay_2us();
	}		
}


///*********************************************************************************///
///*函数原型:void InF_EsamChipDeselect( void )
///*输入参数: Esam片选取消
///*输出参数:无
///*返回参数:无
///*功能说明:CS采用软件控制的方法，内部带延时
///*********************************************************************************///
void InF_EsamChipDeselect( void )
{
	ulong32 ulTemp_SPI,V_Delay;
	
	/* CS口线 */
	IO_ESAMCS->BSETH = ESAMCSSET;	/* 首先拉高口线 */
	
	ulTemp_SPI = IO_ESAMCS->MODER;	/* MODER */
	ulTemp_SPI &= ESAMCS_IN_MODE;
	ulTemp_SPI |= ESAMCS_OUT_MODE;
	IO_ESAMCS->MODER = ulTemp_SPI;

	ulTemp_SPI = IO_ESAMCS->OTYPER;	/* OTYPER */
	ulTemp_SPI &= ESAMCS_OUTPUT_PP;
	IO_ESAMCS->OTYPER = ulTemp_SPI;
	
	ulTemp_SPI = IO_ESAMCS->PUPDR;	/* PUPDR */
	ulTemp_SPI &= ESAMCS_NOPUPD;
	IO_ESAMCS->PUPDR = ulTemp_SPI;
	
	IO_ESAMCS->BSETH = ESAMCSSET;	/* 再次拉高口线 */
	///*拉低延时
	for( V_Delay=0;V_Delay<C_Esam_Tcsh30us;V_Delay++)
	{
		InF_Delay_2us();
	}	
}

///***********************************************************************************///
///*Function：从ESAM接收1个字节*///
///*Description：*///
///*Input：接收数据的地址指针*///
///*Output：将从ESAM接收到的数据放到输入的地址中*///
///*Return：C_OK：接收成功；C_Error：未能接收到，超时*///
///***********************************************************************************///
uchar8 SF_RecOneByteFrom_Esam(uchar8 *P_Buff)
{
	ulong32 V_ulDelay = 0;
	
	if(SFR_ESAMCOM->SPIIF & SPI_FLAG_RXNE)
	{
		V_ulDelay =	SFR_ESAMCOM->SPIRXBUF;
	}
        V_ulDelay = 0; 
	while( !(SFR_ESAMCOM->SPIIF & SPI_FLAG_TXE ) )		/* 判断发送缓冲是否为空 */
	{
		InF_Delay_2us();
		V_ulDelay++;
		if( V_ulDelay > C_SPI_50ms )							///*最多延时50ms*///
		{
			return C_Error;
		}		
	}
	
	V_ulDelay = SFR_ESAMCOM->SPIIF;		
	SFR_ESAMCOM->SPITXBUF = 0x00;		/* ESAM要求主设备在接收数据时,MOSI引脚保持低电平 */

	V_ulDelay = 0;
	while( (SFR_ESAMCOM->SPIIF & SPI_FLAG_RXNE ) == 0 )		/* 判断接收缓冲是否为空 */
	{
		InF_Delay_2us();
		V_ulDelay++;
		if( V_ulDelay > C_SPI_50ms )							///*最多延时50ms*///
		{
			return C_Error;
		}		
	}
	*P_Buff = SFR_ESAMCOM->SPIRXBUF;	
	V_ulDelay = SFR_ESAMCOM->SPIIF;
//		InF_Delay_2us();
//    InF_Delay_2us();
//	while( (SFR_ESAMCOM->SR & USART_FLAG_RXNE) != USART_FLAG_RXNE )	///*等1字节接收完成*///
//	{
//		InF_Delay_2us();
//		V_ulDelay++;
//		if( V_ulDelay > C_Esam_9600ETU )							///*最多延时9600ETU*///
//		{
//			return C_Error;
//		}
//	}
//	*P_Buff = SFR_ESAMCOM->DR;	
	return C_OK;
}

///***********************************************************************************///


///***********************************************************************************///
///*Function：向ESAM发送1个字节*///
///*Description：*///
///*Input：要发送的数据*///
///*Output：将从ESAM接收到的数据放到输入的地址中*///
///*Return：C_OK：发送成功；C_Error：重发3次仍不能成功*///
///***********************************************************************************///
uchar8 SF_SendOneByteTo_Esam(uchar8 data)
{
	ulong32 V_ulDelay = 0;

	while( !(SFR_ESAMCOM->SPIIF & SPI_FLAG_TXE ) )		/* 判断发送缓冲是否为空 */
	{
		InF_Delay_2us();
		V_ulDelay++;
		if( V_ulDelay > C_SPI_50ms )							///*最多延时50ms*///
		{
			return C_Error;
		}		
	}
		
	V_ulDelay = 0;
	SFR_ESAMCOM->SPITXBUF = data;
	while( !(SFR_ESAMCOM->SPIIF & SPI_FLAG_TXE ) )		/* 等待1字节发送完成 */
	{
		InF_Delay_2us();
		V_ulDelay++;
		if( V_ulDelay > C_SPI_50ms)				///*最多延时50ms，正常不存在*///
		{
			return C_Error;
		}		
	}
	V_ulDelay = SFR_ESAMCOM->SPIRXBUF;	
	V_ulDelay = SFR_ESAMCOM->SPIIF;		
	return C_OK;
}



