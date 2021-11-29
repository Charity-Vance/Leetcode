/**
  ******************************************************************************
  * @file    fm32l0xx_spi.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    20-JEN-2017
  * @brief   This file contains all the functions prototypes for the SPI firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_SPI_H
#define __FM32L0xx_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants
  * @{
  */
	 


/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  HSPI Init Structure definition  
  */ 

typedef struct
{
	uint32_t DELAY_CFG;							/* SETTING SENING AHESD */
  uint32_t FLTEN;            			/* SET PAD(SSN/SCK/MOSI) FILTER ENABLE AT SLAVE  */	
  uint32_t LSBF;          				/* SETTING 1 FOR LSB */	
  uint32_t CPHOL;            			/* SETTING 1 FOR CLK STOP AT HIGH */	
  uint32_t CPHA;             			/* SETTING 1 FOR START AT SECOND CLK EDGE AND 0 FOR FIRST */	
} HSPI_SLAVE_InitType;

typedef struct
{
	uint32_t DELAY_CFG;							/* SETTING SAMPLE DELAY */
  uint32_t WAIT;          				/* WAIT CYCLE BETWEEN TWO BYTE SENDING */	
  uint32_t BAUD_RATE;           	/* SETTING BAUD_RATE */	
  uint32_t LSBF;             			/* SETTING 1 FOR LSB */		
  uint32_t CPHOL;									/* SETTING 1 FOR CLK STOP AT HIGH*/	
	uint32_t CPHA;									/* SETTING 1 FOR START AT SECOND CLK EDGE AND 0 FOR FIRST */
	uint32_t SSNM;									/* SETTING SSN AFTER SENDING */	
	uint32_t SSNSEN;								/* SETTING 1 FOR CONTROL SSN BY SOFTWARE */
} HSPI_MASTER_InitType;

/** 
  * @brief  SPI Init Structure definition  
  */ 

typedef struct
{
	uint32_t SSPA;									/* SETTING SENING AHESD HALF CYCLE */
  uint32_t FLTEN;            			/* SET PAD(SSN/SCK/MOSI) FILTER ENABLE AT SLAVE  */	
  uint32_t LSBF;          				/* SETTING 1 FOR LSB */	
  uint32_t CPHOL;            			/* SETTING 1 FOR CLK STOP AT HIGH */	
  uint32_t CPHA;             			/* SETTING 1 FOR START AT SECOND CLK EDGE AND 0 FOR FIRST */	
} SPI_SLAVE_InitType;

typedef struct
{
	uint32_t MSPA;									/* SETTING SAMPLE DELAY HALF CYCLE */
  uint32_t WAIT;          				/* WAIT CYCLE BETWEEN TWO BYTE SENDING */	
  uint32_t BAUD_RATE;           	/* SETTING BAUD_RATE */	
  uint32_t LSBF;             			/* SETTING 1 FOR LSB */		
  uint32_t CPHOL;									/* SETTING 1 FOR CLK STOP AT HIGH*/	
	uint32_t CPHA;									/* SETTING 1 FOR START AT SECOND CLK EDGE AND 0 FOR FIRST */
	uint32_t SSNM;									/* SETTING SSN AFTER SENDING */	
	uint32_t SSNSEN;								/* SETTING 1 FOR CONTROL SSN BY SOFTWARE */
} SPI_MASTER_InitType;


/**
* @} SPI_SPICR1
*/ 
  
/** @defgroup SPI_SPICR1_CPHA
  * @{
  */
#define SPI_SPICR1_CPHA_Pos               								0                                            
#define SPI_SPICR1_CPHA_Msk              									(0x01UL << SPI_SPICR1_CPHA_Pos) 
#define SPI_SPICR1_CPHA_FIRST           									((uint32_t)0x00000000)
#define SPI_SPICR1_CPHA_SECOND            								((uint32_t)0x00000001)

/** @defgroup SPI_SPICR1_CPHOL
  * @{
  */
#define SPI_SPICR1_CPHOL_Pos               								1                                            
#define SPI_SPICR1_CPHOL_Msk              								(0x01UL << SPI_SPICR1_CPHOL_Pos) 
#define SPI_SPICR1_CPHOL_LOW           										((uint32_t)0x00000000)
#define SPI_SPICR1_CPHOL_HIGH            									((uint32_t)0x00000002)

/** @defgroup SPI_SPICR1_LSBF
  * @{
  */
#define SPI_SPICR1_LSBF_Pos               								2                                            
#define SPI_SPICR1_LSBF_Msk              									(0x01UL << SPI_SPICR1_LSBF_Pos) 
#define SPI_SPICR1_LSBF_MSB           										((uint32_t)0x00000000)
#define SPI_SPICR1_LSBF_LSB            										((uint32_t)0x00000004)

/** @defgroup SPI_SPICR1_BAUD_RATE
  * @{
  */
#define SPI_SPICR1_BAUD_RATE_Pos               						3                                            
#define SPI_SPICR1_BAUD_RATE_Msk              						(0x07UL << SPI_SPICR1_BAUD_RATE_Pos) 
#define SPI_SPICR1_BAUD_RATE_FPCLK            						((uint32_t)0x00000000)
#define SPI_SPICR1_BAUD_RATE_FPCLK_2           						((uint32_t)0x00000008)
#define SPI_SPICR1_BAUD_RATE_FPCLK_4           						((uint32_t)0x00000010)
#define SPI_SPICR1_BAUD_RATE_FPCLK_8           						((uint32_t)0x00000018)
#define SPI_SPICR1_BAUD_RATE_FPCLK_16            					((uint32_t)0x00000020)
#define SPI_SPICR1_BAUD_RATE_FPCLK_32           					((uint32_t)0x00000028)
#define SPI_SPICR1_BAUD_RATE_FPCLK_64           					((uint32_t)0x00000030)
#define SPI_SPICR1_BAUD_RATE_FPCLK_128           					((uint32_t)0x00000038)

/** @defgroup SPI_SPICR1_WAIT
  * @{
  */
#define SPI_SPICR1_WAIT_Pos               								6                                            
#define SPI_SPICR1_WAIT_Msk              									(0x03UL << SPI_SPICR1_WAIT_Pos) 
#define SPI_SPICR1_WAIT_1            											((uint32_t)0x00000000)
#define SPI_SPICR1_WAIT_2           											((uint32_t)0x00000040)
#define SPI_SPICR1_WAIT_3           											((uint32_t)0x00000080)
#define SPI_SPICR1_WAIT_4           											((uint32_t)0x000000C0)

/** @defgroup SPI_SPICR1_MM
  * @{
  */
#define SPI_SPICR1_MM_Pos               									8                                            
#define SPI_SPICR1_MM_Msk              										(0x01UL << SPI_SPICR1_MM_Pos) 
#define SPI_SPICR1_MM_SLAVE        												((uint32_t)0x00000000)
#define SPI_SPICR1_MM_MASTER           										((uint32_t)0x00000100)

/** @defgroup SPI_SPICR1_SSPA
  * @{
  */
/** ONLY FOR SPI */
#define SPI_SPICR1_SSPA_Pos               								9                                            
#define SPI_SPICR1_SSPA_Msk              									(0x01UL << SPI_SPICR1_SSPA_Pos) 
#define SPI_SPICR1_SSPA_NORMAL       											((uint32_t)0x00000000)
#define SPI_SPICR1_SSPA_HALF_AHEAD   											((uint32_t)0x00000200)

/** @defgroup SPI_SPICR1_MSPA
  * @{
  */
/** ONLY FOR SPI */
#define SPI_SPICR1_MSPA_Pos               								10                                            
#define SPI_SPICR1_MSPA_Msk              									(0x01UL << SPI_SPICR1_MSPA_Pos) 
#define SPI_SPICR1_MSPA_NORMAL       											((uint32_t)0x00000000)
#define SPI_SPICR1_MSPA_HALF_DELAY   											((uint32_t)0x00000400)

/** @defgroup SPI_SPICR1_DELAY
  * @{
  */
/** ONLY FOR HSPI */
#define SPI_SPICR1_DELAY_Pos               								9                                            
#define SPI_SPICR1_DELAY_Msk              								(0x07UL << SPI_SPICR1_DELAY_Pos) 
#define SPI_SPICR1_DELAY_MASTER_NO_DELAY  								((uint32_t)0x00000000)
#define SPI_SPICR1_DELAY_MASTER_DELAY_10NS								((uint32_t)0x00000200)
#define SPI_SPICR1_DELAY_MASTER_DELAY_20NS  							((uint32_t)0x00000400)
#define SPI_SPICR1_DELAY_MASTER_DELAY_30NS 								((uint32_t)0x00000600)
#define SPI_SPICR1_DELAY_MASTER_DELAY_40NS  							((uint32_t)0x00000800)
#define SPI_SPICR1_DELAY_MASTER_DELAY_HALF 								((uint32_t)0x00000A00)

#define SPI_SPICR1_DELAY_SLAVE_NO_AHEAD	  								((uint32_t)0x00000000)
#define SPI_SPICR1_DELAY_SLAVE_AHEAD_HALF_20NS						((uint32_t)0x00000200)
#define SPI_SPICR1_DELAY_SLAVE_AHEAD_HALF_15NS  					((uint32_t)0x00000400)
#define SPI_SPICR1_DELAY_SLAVE_AHEAD_HALF_10NS 						((uint32_t)0x00000600)
#define SPI_SPICR1_DELAY_SLAVE_AHEAD_HALF_5NS  						((uint32_t)0x00000800)
#define SPI_SPICR1_DELAY_SLAVE_AHEAD_HALF 								((uint32_t)0x00000A00)

/**
* @} SPI_SPICR2
*/ 
  
/** @defgroup SPI_SPICR2_SPIEN
  * @{
  */
#define SPI_SPICR2_SPIEN_Pos               								0                                            
#define SPI_SPICR2_SPIEN_Msk              								(0x01UL << SPI_SPICR2_SPIEN_Pos) 
#define SPI_SPICR2_SPIEN_DISABLE         									((uint32_t)0x00000000)
#define SPI_SPICR2_SPIEN_ENABLE            								((uint32_t)0x00000001)

/** @defgroup SPI_SPICR2_SSNSEN
  * @{
  */
#define SPI_SPICR2_SSNSEN_Pos               							1                                            
#define SPI_SPICR2_SSNSEN_Msk              								(0x01UL << SPI_SPICR2_SSNSEN_Pos) 
#define SPI_SPICR2_SSNSEN_SOFT           									((uint32_t)0x00000000)
#define SPI_SPICR2_SSNSEN_HARD	           								((uint32_t)0x00000002)

/** @defgroup SPI_SPICR2_SSN
  * @{
  */
#define SPI_SPICR2_SSN_Pos               									2                                            
#define SPI_SPICR2_SSN_Msk              									(0x01UL << SPI_SPICR2_SSN_Pos) 
#define SPI_SPICR2_SSN_CLR           											((uint32_t)0x00000000)
#define SPI_SPICR2_SSN_SET	           										((uint32_t)0x00000004)

/** @defgroup SPI_SPICR2_TXO
  * @{
  */
#define SPI_SPICR2_TXO_Pos               									3                                            
#define SPI_SPICR2_TXO_Msk              									(0x01UL << SPI_SPICR2_TXO_Pos) 
#define SPI_SPICR2_TXO_DISABLE       											((uint32_t)0x00000000)
#define SPI_SPICR2_TXO_ENABLE         										((uint32_t)0x00000008)

/** @defgroup SPI_SPICR2_TXO_AC
  * @{
  */
#define SPI_SPICR2_TXO_AC_Pos               							4                                            
#define SPI_SPICR2_TXO_AC_Msk              								(0x01UL << SPI_SPICR2_TXO_AC_Pos) 
#define SPI_SPICR2_TXO_AC_CLR_AT_CLOSE       							((uint32_t)0x00000000)
#define SPI_SPICR2_TXO_AC_CLR_AT_TX		  									((uint32_t)0x00000010)

/** @defgroup SPI_SPICR2_SSNM
  * @{
  */
#define SPI_SPICR2_SSNM_Pos               								5                                            
#define SPI_SPICR2_SSNM_Msk              									(0x01UL << SPI_SPICR2_SSNM_Pos) 
#define SPI_SPICR2_SSNM_LOW						       							((uint32_t)0x00000000)
#define SPI_SPICR2_SSNM_HIGH					  									((uint32_t)0x00000020)

/** @defgroup SPI_SPICR2_FLTEN
  * @{
  */
#define SPI_SPICR2_FLTEN_Pos               								6                                            
#define SPI_SPICR2_FLTEN_Msk             									(0x01UL << SPI_SPICR2_FLTEN_Pos) 
#define SPI_SPICR2_FLTEN_DISABLE			       							((uint32_t)0x00000000)
#define SPI_SPICR2_FLTEN_ENABLE				  									((uint32_t)0x00000020)


/**
* @} SPI_SPICR3
*/ 
  
/** @defgroup SPI_SPICR3_SERRC
  * @{
  */
#define SPI_SPICR3_SERRC_Pos               								0                                            
#define SPI_SPICR3_SERRC_Msk              								(0x01UL << SPI_SPICR3_SERRC_Pos) 
#define SPI_SPICR3_SERRC_CLR            									((uint32_t)0x00000001)

/** @defgroup SPI_SPICR3_MERRC
  * @{
  */
#define SPI_SPICR3_MERRC_Pos               								1                                            
#define SPI_SPICR3_MERRC_Msk              								(0x01UL << SPI_SPICR3_MERRC_Pos) 
#define SPI_SPICR3_MERRC_CLR	           									((uint32_t)0x00000002)

/** @defgroup SPI_SPICR3_RXBFC
  * @{
  */
#define SPI_SPICR3_RXBFC_Pos               								2                                            
#define SPI_SPICR3_RXBFC_Msk              								(0x01UL << SPI_SPICR3_RXBFC_Pos) 
#define SPI_SPICR3_RXBFC_CLR	           									((uint32_t)0x00000004)

/** @defgroup SPI_SPICR3_TXBFC
  * @{
  */
#define SPI_SPICR3_TXBFC_Pos               								3                                            
#define SPI_SPICR3_TXBFC_Msk              								(0x01UL << SPI_SPICR3_TXBFC_Pos) 
#define SPI_SPICR3_TXBFC_FULL         									((uint32_t)0x00000008)

/**
* @} SPI_SPIIE
*/ 
  
/** @defgroup SPI_SPIIE_RXIE
  * @{
  */
#define SPI_SPIIE_RXIE_Pos               								0                                            
#define SPI_SPIIE_RXIE_Msk              								(0x01UL << SPI_SPICR2_SPIEN_Pos) 
#define SPI_SPIIE_RXIE_DISABLE           								((uint32_t)0x00000000)
#define SPI_SPIIE_RXIE_ENABLE            								((uint32_t)0x00000001)

/** @defgroup SPI_SPIIE_TXIE
  * @{
  */
#define SPI_SPIIE_TXIE_Pos               								1                                            
#define SPI_SPIIE_TXIE_Msk              								(0x01UL << SPI_SPIIE_TXIE_Pos) 
#define SPI_SPIIE_TXIE_DISABLE        									((uint32_t)0x00000000)
#define SPI_SPIIE_TXIE_ENABLE          									((uint32_t)0x00000002)

/** @defgroup SPI_SPIIE_ERRIE
  * @{
  */
#define SPI_SPIIE_ERRIE_Pos               							2                                            
#define SPI_SPIIE_ERRIE_Msk              								(0x01UL << SPI_SPIIE_ERRIE_Pos) 
#define SPI_SPIIE_ERRIE_DISABLE      										((uint32_t)0x00000000)
#define SPI_SPIIE_ERRIE_ENABLE         									((uint32_t)0x00000004)

/**
* @} SPI_SPIIF
*/ 
  
/** @defgroup SPI_SPIIF_RXBF
  * @{
  */
#define SPI_SPIIF_RXBF_Pos               								0                                            
#define SPI_SPIIF_RXBF_Msk              								(0x01UL << SPI_SPIIF_RXBF_Pos) 
#define SPI_SPIIF_RXBF_EMPTY	           								((uint32_t)0x00000000)
#define SPI_SPIIF_RXBF_FULL	            								((uint32_t)0x00000001)

/** @defgroup SPI_SPIIF_TXBE
  * @{
  */
#define SPI_SPIIF_TXBE_Pos               								1                                            
#define SPI_SPIIF_TXBE_Msk              								(0x01UL << SPI_SPIIF_TXBE_Pos) 
#define SPI_SPIIF_TXBE_FULL    		    									((uint32_t)0x00000000)
#define SPI_SPIIF_TXBE_EMPTY          									((uint32_t)0x00000002)

/** @defgroup SPI_SPIIF_BUSY
  * @{
  */
#define SPI_SPIIF_BUSY_Pos               								2                                            
#define SPI_SPIIF_BUSY_Msk              								(0x01UL << SPI_SPIIF_BUSY_Pos) 
#define SPI_SPIIF_BUSY_IDLE      												((uint32_t)0x00000000)
#define SPI_SPIIF_BUSY_BUSY         										((uint32_t)0x00000004)

/** @defgroup SPI_SPIIF_TXCOL
  * @{
  */
#define SPI_SPIIF_TXCOL_Pos               							3                                            
#define SPI_SPIIF_TXCOL_Msk              								(0x01UL << SPI_SPIIF_TXCOL_Pos) 
#define SPI_SPIIF_TXCOL_OK       												((uint32_t)0x00000000)
#define SPI_SPIIF_TXCOL_OV         											((uint32_t)0x00000008)

/** @defgroup SPI_SPIIF_RXCOL
  * @{
  */
#define SPI_SPIIF_RXCOL_Pos               							4                                            
#define SPI_SPIIF_RXCOL_Msk              								(0x01UL << SPI_SPIIF_RXCOL_Pos) 
#define SPI_SPIIF_RXCOL_OK      												((uint32_t)0x00000000)
#define SPI_SPIIF_RXCOL_OV         											((uint32_t)0x00000010)

/** @defgroup SPI_SPIIF_SERR
  * @{
  */
#define SPI_SPIIF_SERR_Pos               								5                                            
#define SPI_SPIIF_SERR_Msk              								(0x01UL << SPI_SPIIF_SERR_Pos) 
#define SPI_SPIIF_SERR_RESET     												((uint32_t)0x00000000)
#define SPI_SPIIF_SERR_SET         											((uint32_t)0x00000020)

/** @defgroup SPI_SPIIF_MERR
  * @{
  */
#define SPI_SPIIF_MERR_Pos               								6                                            
#define SPI_SPIIF_MERR_Msk              								(0x01UL << SPI_SPIIF_MERR_Pos) 
#define SPI_SPIIF_MERR_RESET      											((uint32_t)0x00000000)
#define SPI_SPIIF_MERR_SET         											((uint32_t)0x00000040)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
extern void HSPI_MASTER_Init(HSPI_MASTER_InitType* HSPI_MASTER_InitStruct);
extern void HSPI_SLAVE_Init(HSPI_SLAVE_InitType* HSPI_SLAVE_InitStruct);
extern void SPI_MASTER_Init(SPI_Type* SPIx,SPI_MASTER_InitType* SPI_MASTER_InitStruct);
extern void SPI_SLAVE_Init(SPI_Type* SPIx,SPI_SLAVE_InitType* SPI_SLAVE_InitStruct);
extern ITStatus SPI_GetFlagSta(SPI_Type* SPIx,uint32_t FlagBit);
extern uint32_t SPI_ReceiveData(SPI_Type* SPIx);
extern void SPI_SendData(SPI_Type* SPIx, uint32_t Data);


#ifdef __cplusplus
}
#endif

#endif /* __FM385_SPI_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/




