
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     SPI.c
///*Version:       V1
///*Date:          2016-8-25
///*Description:   spi���������
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


#include "Public.h"
#include "SPI.h"
#include "IO.h"

///*********************************************************************************///
///*����ԭ��:void DF_SPI_Configuration_ETH( void )
///*�������: ��
///*�������: ��
///*���ز���: ��
///*����˵��:
///*	�Բⷢ�ֵ�ESAM��������ΪSPI�ӿ�ʱ��Ȼ��ͣ��ESAM�����ر�ESAM��Դ����Vesam���е�ѹ��
///*	���ESAM�ӿ����¶���Ϊ��ͨIO��ͬʱ����ͣ���ʱVesam��Դ����Ϊ0��������IO��©�硣
///*********************************************************************************///
void InF_DeadESAM_SPI_Initial( void )
{
	ulong32 ulTemp_SPI;
////	ushort16 usTemp_SPI;
	/* MOSI���� */
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
	
	IO_ESAMMOSI->BSRR = ESAMMOSIRESET;	/* �ٴ����Ϳ��� */
	/* MISO���� ,û�б�Ҫ����Ϊ���������*/
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
	
//	IO_ESAMMISO->BSRR |= ESAMSCKRESET;	/* �ٴ����Ϳ��� */
	/* SCK���� */
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
	
	IO_ESAMSCK->BSRR = ESAMSCKRESET;	/* �ٴ����Ϳ��� */
	/* �ر�HSPI */
	SFR_ESAMCOM->SPICR2 &= (~CR2SPI_HSPIEN);
	/* CS���� */
	InF_EsamChipSelect();	/* ��������,CS���߻���©������ESAM��Դ,���Խ�CS�������� */
}


///*********************************************************************************///
///*����ԭ��:void DF_SPI_Configuration_ETH( void )
///*�������: ��
///*�������: ��
///*���ز���: ��
///*����˵��:
///*	1) ����spi����:MOSI/MISO/SCK
///*	2) ��spi1����Ϊ��ģʽ,���ں�ESAMͨ��
///*	3) spiʱ������Ϊ4MHz:16MHz4��Ƶ��õ�
///*	4) ʹ��spi����
///*	5) ��ʼ����ɺ�,SPI����ʹ��״̬
///*	6) Ƭѡ���������
///*********************************************************************************///
void DF_SPI_Configuration( void )
{
	ulong32 ulTemp_SPI;

	/* ʹ��RCC�е�HSPIʱ�� */
	Esam_SouceClock_SFR |= EsamSouceClock_EN;

	/* ѡ��HSPI�Ŀ���,�����ÿ��� */
	/* MOSI���� */
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
	
	/* MISO���� */
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
	
	/* SCK���� */
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
	SFR_ESAMCOM->SPICR3 |= 0x0000000F;///*������͡����ա�����
	/*IE*/
	SFR_ESAMCOM->SPIIE |= 0x00000007;///*�жϽ�ֹ
	/* �жϱ�־�Ĵ��� */
	SFR_ESAMCOM->SPIIF |= 0x00000018;///*���ա����ͻ��������־����
	
	ulTemp_SPI = SFR_ESAMCOM->SPIIF;///*��״̬��־�����ջ���
	ulTemp_SPI = SFR_ESAMCOM->SPIRXBUF;
	/* ʹ��HSPI */
	SFR_ESAMCOM->SPICR2 |= CR2SPI_HSPIEN;
	ulTemp_SPI = SFR_ESAMCOM->SPIIF;
	ulTemp_SPI = SFR_ESAMCOM->SPIRXBUF;
}

///*********************************************************************************///
///*����ԭ��:void InF_EsamChipSelect( void )
///*�������: EsamƬѡ��Ч
///*�������:��
///*���ز���:��
///*����˵��:CS����������Ƶķ������ڲ�����ʱ
///*********************************************************************************///
void InF_EsamChipSelect( void )
{
	ulong32 ulTemp_SPI,V_Delay;
	
	/* CS���� */
	IO_ESAMCS->BSRR = ESAMCSRESET;	/* �������Ϳ��� */
	
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
	
	IO_ESAMCS->BSRR = ESAMCSRESET;	/* �ٴ����Ϳ��� */
	///*������ʱ
	for( V_Delay=0;V_Delay<C_Esam_Tcsl100us;V_Delay++)
	{
		InF_Delay_2us();
	}		
}


///*********************************************************************************///
///*����ԭ��:void InF_EsamChipDeselect( void )
///*�������: EsamƬѡȡ��
///*�������:��
///*���ز���:��
///*����˵��:CS����������Ƶķ������ڲ�����ʱ
///*********************************************************************************///
void InF_EsamChipDeselect( void )
{
	ulong32 ulTemp_SPI,V_Delay;
	
	/* CS���� */
	IO_ESAMCS->BSETH = ESAMCSSET;	/* �������߿��� */
	
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
	
	IO_ESAMCS->BSETH = ESAMCSSET;	/* �ٴ����߿��� */
	///*������ʱ
	for( V_Delay=0;V_Delay<C_Esam_Tcsh30us;V_Delay++)
	{
		InF_Delay_2us();
	}	
}

///***********************************************************************************///
///*Function����ESAM����1���ֽ�*///
///*Description��*///
///*Input���������ݵĵ�ַָ��*///
///*Output������ESAM���յ������ݷŵ�����ĵ�ַ��*///
///*Return��C_OK�����ճɹ���C_Error��δ�ܽ��յ�����ʱ*///
///***********************************************************************************///
uchar8 SF_RecOneByteFrom_Esam(uchar8 *P_Buff)
{
	ulong32 V_ulDelay = 0;
	
	if(SFR_ESAMCOM->SPIIF & SPI_FLAG_RXNE)
	{
		V_ulDelay =	SFR_ESAMCOM->SPIRXBUF;
	}
        V_ulDelay = 0; 
	while( !(SFR_ESAMCOM->SPIIF & SPI_FLAG_TXE ) )		/* �жϷ��ͻ����Ƿ�Ϊ�� */
	{
		InF_Delay_2us();
		V_ulDelay++;
		if( V_ulDelay > C_SPI_50ms )							///*�����ʱ50ms*///
		{
			return C_Error;
		}		
	}
	
	V_ulDelay = SFR_ESAMCOM->SPIIF;		
	SFR_ESAMCOM->SPITXBUF = 0x00;		/* ESAMҪ�����豸�ڽ�������ʱ,MOSI���ű��ֵ͵�ƽ */

	V_ulDelay = 0;
	while( (SFR_ESAMCOM->SPIIF & SPI_FLAG_RXNE ) == 0 )		/* �жϽ��ջ����Ƿ�Ϊ�� */
	{
		InF_Delay_2us();
		V_ulDelay++;
		if( V_ulDelay > C_SPI_50ms )							///*�����ʱ50ms*///
		{
			return C_Error;
		}		
	}
	*P_Buff = SFR_ESAMCOM->SPIRXBUF;	
	V_ulDelay = SFR_ESAMCOM->SPIIF;
//		InF_Delay_2us();
//    InF_Delay_2us();
//	while( (SFR_ESAMCOM->SR & USART_FLAG_RXNE) != USART_FLAG_RXNE )	///*��1�ֽڽ������*///
//	{
//		InF_Delay_2us();
//		V_ulDelay++;
//		if( V_ulDelay > C_Esam_9600ETU )							///*�����ʱ9600ETU*///
//		{
//			return C_Error;
//		}
//	}
//	*P_Buff = SFR_ESAMCOM->DR;	
	return C_OK;
}

///***********************************************************************************///


///***********************************************************************************///
///*Function����ESAM����1���ֽ�*///
///*Description��*///
///*Input��Ҫ���͵�����*///
///*Output������ESAM���յ������ݷŵ�����ĵ�ַ��*///
///*Return��C_OK�����ͳɹ���C_Error���ط�3���Բ��ܳɹ�*///
///***********************************************************************************///
uchar8 SF_SendOneByteTo_Esam(uchar8 data)
{
	ulong32 V_ulDelay = 0;

	while( !(SFR_ESAMCOM->SPIIF & SPI_FLAG_TXE ) )		/* �жϷ��ͻ����Ƿ�Ϊ�� */
	{
		InF_Delay_2us();
		V_ulDelay++;
		if( V_ulDelay > C_SPI_50ms )							///*�����ʱ50ms*///
		{
			return C_Error;
		}		
	}
		
	V_ulDelay = 0;
	SFR_ESAMCOM->SPITXBUF = data;
	while( !(SFR_ESAMCOM->SPIIF & SPI_FLAG_TXE ) )		/* �ȴ�1�ֽڷ������ */
	{
		InF_Delay_2us();
		V_ulDelay++;
		if( V_ulDelay > C_SPI_50ms)				///*�����ʱ50ms������������*///
		{
			return C_Error;
		}		
	}
	V_ulDelay = SFR_ESAMCOM->SPIRXBUF;	
	V_ulDelay = SFR_ESAMCOM->SPIIF;		
	return C_OK;
}



