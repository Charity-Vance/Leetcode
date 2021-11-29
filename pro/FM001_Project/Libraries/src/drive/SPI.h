
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     SPI.h
///*Version:       V1
///*Date:          2016-8-25
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__SPI_H
#define	__SPI_H


#define CR1_CLEAR_MASK_SPI 				    0xFFFFF000
#define CR1SPI_Delay_Cfg					0x00000000		/* 无延时 */
#define SPI_Direction_2Lines_FullDuplex 	0x0000		    /* 双线全双工方式 */
#define SPI_Mode_Master 					0x00000100		/* 主模式 */
#define CR1SPI_WAIT 						0x00000000		/* 延时1个CLK */
#define SPI_DataSize_8b						0x0000		    /* 数据大小8位 */
#define SPI_CPOL_High						0x00000002		/* 时钟极性，空闲时为高 */
#define SPI_CPHA_2Edge						0x00000001		/* 第2个边沿有效，上升沿为采样时刻 */
#define SPI_BaudRatePrescaler_2				0x00000008		/* 波特率采用2分频:8MHz */
#define SPI_BaudRatePrescaler_4				0x00000010		/* 波特率采用4分频:4MHz */
#define SPI_BaudRatePrescaler_8				0x00000018		/* 波特率采用8分频:2MHz */
#define SPI_BaudRatePrescaler_16			0x00000020		/* 波特率采用16分频:1MHz */
#define SPI_FirstBit_MSB					0x00000000		/* 高位在前 */

#define CR2_CLEAR_MASK_SPI 				    0xFFFFFF80
#define CR2SPI_FLTEN_Off 					0x00000000 		/*slave输入滤波使能,不滤波*/
#define CR2SPI_FLTEN_On 					0x00000040 		/*slave输入滤波使能*/
#define CR2SPI_SSNM_Off 					0x00000000 		/*Master模式SSN控制模式选择，每次发送完后SSN保持为低*/
#define CR2SPI_TXO_AC_Off  					0x00000000 		/*关闭TXONLY硬件自动清零*/
#define CR2SPI_TXO_Off 	 					0x00000000 		/*关闭单发送模式*/
#define CR2SPI_SSN_Low 	 					0x00000000 		/*SSN输出为低*/
#define CR2SPI_SSN_Soft	 					0x00000002 		/*SSN输出由软件控制*/
#define CR2SPI_HSPIEN	 					0x00000001 		/*使能HSPI*/
#define CR2SPI_HSPIDIS	 					0x00000000 		/*关闭HSPI*/


#define SPI_I2SCFGR_SPIMOD					0x0000			/* spi方式 */

#define SPI_CRCPolynomial				    7			    /* CRC值计算的多项式 */


#define SPI_FLAG_BSY					    0x00000004		/* spi忙标志 */
#define SPI_FLAG_TXE					    0x00000002		/* 0表示发送缓冲不空,1表示为空 */
#define SPI_FLAG_RXNE					    0x00000001		/* 0表示接收缓冲为空,1表示接收缓冲不空 */

#define	C_SPI_50ms		                    25000		    ///*接收超时：50ms,2us基准*///
#define	C_Esam_Tcsl100us	                50			    ///*数据手册要求最少60us，最大150us，此处设置为100us，以2us为单位计时*///
#define	C_Esam_Tcsh30us	                    30			    ///*数据手册要求最少10us，最大50us，此处设置为30us，以2us为单位计时*///


extern void DF_SPI_Configuration( void );
extern void InF_EsamChipDeselect( void );
extern void InF_EsamChipSelect( void );
extern uchar8 SF_RecOneByteFrom_Esam(uchar8 *P_Buff);
extern uchar8 SF_SendOneByteTo_Esam(uchar8 data);
extern void InF_DeadESAM_SPI_Initial( void );



#endif
