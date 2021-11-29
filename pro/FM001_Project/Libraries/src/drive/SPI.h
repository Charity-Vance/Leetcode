
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     SPI.h
///*Version:       V1
///*Date:          2016-8-25
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__SPI_H
#define	__SPI_H


#define CR1_CLEAR_MASK_SPI 				    0xFFFFF000
#define CR1SPI_Delay_Cfg					0x00000000		/* ����ʱ */
#define SPI_Direction_2Lines_FullDuplex 	0x0000		    /* ˫��ȫ˫����ʽ */
#define SPI_Mode_Master 					0x00000100		/* ��ģʽ */
#define CR1SPI_WAIT 						0x00000000		/* ��ʱ1��CLK */
#define SPI_DataSize_8b						0x0000		    /* ���ݴ�С8λ */
#define SPI_CPOL_High						0x00000002		/* ʱ�Ӽ��ԣ�����ʱΪ�� */
#define SPI_CPHA_2Edge						0x00000001		/* ��2��������Ч��������Ϊ����ʱ�� */
#define SPI_BaudRatePrescaler_2				0x00000008		/* �����ʲ���2��Ƶ:8MHz */
#define SPI_BaudRatePrescaler_4				0x00000010		/* �����ʲ���4��Ƶ:4MHz */
#define SPI_BaudRatePrescaler_8				0x00000018		/* �����ʲ���8��Ƶ:2MHz */
#define SPI_BaudRatePrescaler_16			0x00000020		/* �����ʲ���16��Ƶ:1MHz */
#define SPI_FirstBit_MSB					0x00000000		/* ��λ��ǰ */

#define CR2_CLEAR_MASK_SPI 				    0xFFFFFF80
#define CR2SPI_FLTEN_Off 					0x00000000 		/*slave�����˲�ʹ��,���˲�*/
#define CR2SPI_FLTEN_On 					0x00000040 		/*slave�����˲�ʹ��*/
#define CR2SPI_SSNM_Off 					0x00000000 		/*MasterģʽSSN����ģʽѡ��ÿ�η������SSN����Ϊ��*/
#define CR2SPI_TXO_AC_Off  					0x00000000 		/*�ر�TXONLYӲ���Զ�����*/
#define CR2SPI_TXO_Off 	 					0x00000000 		/*�رյ�����ģʽ*/
#define CR2SPI_SSN_Low 	 					0x00000000 		/*SSN���Ϊ��*/
#define CR2SPI_SSN_Soft	 					0x00000002 		/*SSN������������*/
#define CR2SPI_HSPIEN	 					0x00000001 		/*ʹ��HSPI*/
#define CR2SPI_HSPIDIS	 					0x00000000 		/*�ر�HSPI*/


#define SPI_I2SCFGR_SPIMOD					0x0000			/* spi��ʽ */

#define SPI_CRCPolynomial				    7			    /* CRCֵ����Ķ���ʽ */


#define SPI_FLAG_BSY					    0x00000004		/* spiæ��־ */
#define SPI_FLAG_TXE					    0x00000002		/* 0��ʾ���ͻ��岻��,1��ʾΪ�� */
#define SPI_FLAG_RXNE					    0x00000001		/* 0��ʾ���ջ���Ϊ��,1��ʾ���ջ��岻�� */

#define	C_SPI_50ms		                    25000		    ///*���ճ�ʱ��50ms,2us��׼*///
#define	C_Esam_Tcsl100us	                50			    ///*�����ֲ�Ҫ������60us�����150us���˴�����Ϊ100us����2usΪ��λ��ʱ*///
#define	C_Esam_Tcsh30us	                    30			    ///*�����ֲ�Ҫ������10us�����50us���˴�����Ϊ30us����2usΪ��λ��ʱ*///


extern void DF_SPI_Configuration( void );
extern void InF_EsamChipDeselect( void );
extern void InF_EsamChipSelect( void );
extern uchar8 SF_RecOneByteFrom_Esam(uchar8 *P_Buff);
extern uchar8 SF_SendOneByteTo_Esam(uchar8 data);
extern void InF_DeadESAM_SPI_Initial( void );



#endif
