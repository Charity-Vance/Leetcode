/**
  ******************************************************************************
  * @file    fm32l0xx_dma.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    20-SETP-2016
  * @brief   This file contains all the functions prototypes for the RCC firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_DMA_H
#define __FM32L0xx_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants
  * @{
  */
	 
typedef enum {DmaChannel_0 = 0, DmaChannel_1 = 1, DmaChannel_2= 2, DmaChannel_3 = 3, 
							DmaChannel_4 = 4, DmaChannel_5 = 5, DmaChannel_6 = 6, DmaChannel_7 = 7} DmaChannel;

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  DmaChannel CHANNEL_num; 				/*!<  set dma channel 0-7 */
  uint32_t Trans_Sizes;   				/*!<  trans size 1-8192   */
  uint32_t Ram_Addr;  						/*!<  ram start address */
	uint32_t Flash_Addr;  					/*!<  flash start address only for channel7 */
  uint32_t CHPriority;  	    		/*!<  CHANNEL Priority */
  uint32_t CHselect;   						/*!<  periph select only for channel0-6     */
  uint32_t ram_addrincrease;   		/*!< ram address increase or decrease  */
	uint32_t flash_addrincrease;   	/*!< flash address increase or decrease only for channel7  */
}DMA_InitType;


/**
* @}
*/ 
  
/** @defgroup DMA_GLOBALCTRL_DMAEN
  * @{
  */
#define DMA_GLOBALCTRL_DMAEN_Pos               							0                                             
#define DMA_GLOBALCTRL_DMAEN_Msk               							(0x01UL << DMA_GLOBALCTRL_DMAEN_Pos)  
#define DMA_GLOBALCTRL_DMAEN_DIABLE        									((uint32_t)0x00000000)
#define DMA_GLOBALCTRL_DMAEN_ENABLE        									((uint32_t)0x00000001)

/**
* @}
*/ 

/** @defgroup DMA_CHxCTRL_CHxTSIZE
  * @{
  */
#define DMA_CHxCTRL_CHxTSIZE_Pos               						  16                                            
#define DMA_CHxCTRL_CHxTSIZE_Msk               						 	(0xFFFUL << DMA_CHxCTRL_CHxTSIZE_Pos)

/** @defgroup DMA_CHxCTRL_CHxPRI
  * @{
  */  
#define DMA_CHxCTRL_CHxPRI_Pos               								12                                            
#define DMA_CHxCTRL_CHxPRI_Msk               								(0x03UL << DMA_CHxCTRL_CHxPRI_Pos) 
#define DMA_CHxCTRL_CHxPRI_LOW		                					((uint32_t)0x00000000)
#define DMA_CHxCTRL_CHxPRI_Medium                						((uint32_t)0x00001000)
#define DMA_CHxCTRL_CHxPRI_High               							((uint32_t)0x00002000)
#define DMA_CHxCTRL_CHxPRI_VeryHigh               					((uint32_t)0x00003000)


/** @defgroup DMA_CHxCTRL_CHxINC
  * @{
  */  
#define DMA_CHxCTRL_CHxINC_Pos               								11                                            
#define DMA_CHxCTRL_CHxINC_Msk               								(0x01UL << DMA_CHxCTRL_CHxINC_Pos) 
#define DMA_CHxCTRL_CHxINC_Dec                							((uint32_t)0x00000000)
#define DMA_CHxCTRL_CHxINC_Inc                							((uint32_t)0x00000800)

/** @defgroup DMA_CHxCTRL_CHxFTIE
  * @{
  */
#define DMA_CHxCTRL_CHxFTIE_Pos               							2                                            
#define DMA_CHxCTRL_CHxFTIE_Msk               							(0x01UL << DMA_CHxCTRL_CHxFTIE_Pos)  
#define DMA_CHxCTRL_CHxFTIE_Disable                					((uint32_t)0x00000000)
#define DMA_CHxCTRL_CHxFTIE_Enable	                				((uint32_t)0x00000003)

/** @defgroup DMA_CHxCTRL_CHxHTIE
  * @{
  */ 
#define DMA_CHxCTRL_CHxHTIE_Pos               							1                                            
#define DMA_CHxCTRL_CHxHTIE_Msk               							(0x01UL << DMA_CHxCTRL_CH0HTIE_Pos) 
#define DMA_CHxCTRL_CHxHTIE_Disable                					((uint32_t)0x00000000)
#define DMA_CHxCTRL_CHxHTIE_Enable                					((uint32_t)0x00000002)

/** @defgroup DMA_CHxCTRL_CHxEN
  * @{
  */ 
#define DMA_CHxCTRL_CHxEN_Pos               								0                                            
#define DMA_CHxCTRL_CHxEN_Msk               								(0x01UL << DMA_CHxCTRL_CHxEN_Pos) 
#define DMA_CHxCTRL_CHxEN_Disable                						((uint32_t)0x00000000)
#define DMA_CHxCTRL_CHxEN_Enable                						((uint32_t)0x00000001)

/**
  * @}
  */ 

/** @defgroup DMA_CH0CTRL_CH0SSEL
  * @{
  */  
#define DMA_CHxCTRL_CHxSSEL_Pos               							8                                            
#define DMA_CHxCTRL_CHxSSEL_Msk              								(0x07UL << DMA_CHxCTRL_CHxSSEL_Pos) 

#define DMA_CH0CTRL_CH0SSEL_ET4_CAP 												((uint32_t)0x00000000)
#define DMA_CH0CTRL_CH0SSEL_ET2_CAP 												((uint32_t)0x00000100)
#define DMA_CH0CTRL_CH0SSEL_BT34_CAP 												((uint32_t)0x00000200)
#define DMA_CH0CTRL_CH0SSEL_ET3_CAP 												((uint32_t)0x00000300)
#define DMA_CH0CTRL_CH0SSEL_BT12_CAP 												((uint32_t)0x00000400)
#define DMA_CH0CTRL_CH0SSEL_CRC_OUT 												((uint32_t)0x00000500)
#define DMA_CH0CTRL_CH0SSEL_AES_IN 													((uint32_t)0x00000600)
#define DMA_CH0CTRL_CH0SSEL_ADC_OUT 												((uint32_t)0x00000700)

#define DMA_CH1CTRL_CH1SSEL_ET1_CAP 												((uint32_t)0x00000000)
#define DMA_CH1CTRL_CH1SSEL_AES_OUT 												((uint32_t)0x00000100)
#define DMA_CH1CTRL_CH1SSEL_I2C_RX 													((uint32_t)0x00000200)
#define DMA_CH1CTRL_CH1SSEL_USART0_RX 											((uint32_t)0x00000300)
#define DMA_CH1CTRL_CH1SSEL_UART3_RX 												((uint32_t)0x00000400)
#define DMA_CH1CTRL_CH1SSEL_UART0_RX 												((uint32_t)0x00000500)
#define DMA_CH1CTRL_CH1SSEL_SPI0_RX 												((uint32_t)0x00000600)
#define DMA_CH1CTRL_CH1SSEL_ADC_OUT 												((uint32_t)0x00000700)

#define DMA_CH2CTRL_CH2SSEL_ET3_CAP 												((uint32_t)0x00000000)
#define DMA_CH2CTRL_CH2SSEL_BT12_CAP 												((uint32_t)0x00000100)
#define DMA_CH2CTRL_CH2SSEL_AES_OUT 												((uint32_t)0x00000200)
#define DMA_CH2CTRL_CH2SSEL_I2C_TX 		  										((uint32_t)0x00000300)
#define DMA_CH2CTRL_CH2SSEL_USART0_TX 											((uint32_t)0x00000400)
#define DMA_CH2CTRL_CH2SSEL_UART3_TX 												((uint32_t)0x00000500)
#define DMA_CH2CTRL_CH2SSEL_UART0_TX 												((uint32_t)0x00000600)
#define DMA_CH2CTRL_CH2SSEL_SPI0_TX 												((uint32_t)0x00000700)

#define DMA_CH3CTRL_CH3SSEL_BT34_CAP 												((uint32_t)0x00000000)
#define DMA_CH3CTRL_CH3SSEL_ET1_CAP 												((uint32_t)0x00000100)
#define DMA_CH3CTRL_CH3SSEL_I2C_TX  												((uint32_t)0x00000200)
#define DMA_CH3CTRL_CH3SSEL_USART1_RX												((uint32_t)0x00000300)
#define DMA_CH3CTRL_CH3SSEL_UART4_RX 												((uint32_t)0x00000400)
#define DMA_CH3CTRL_CH3SSEL_UART1_RX 												((uint32_t)0x00000500)
#define DMA_CH3CTRL_CH3SSEL_UART0_RX 												((uint32_t)0x00000600)
#define DMA_CH3CTRL_CH3SSEL_SPI1_RX 												((uint32_t)0x00000700)

#define DMA_CH4CTRL_CH4SSEL_ET2_CAP 												((uint32_t)0x00000000)
#define DMA_CH4CTRL_CH4SSEL_AES_IN  												((uint32_t)0x00000100)
#define DMA_CH4CTRL_CH4SSEL_I2C_RX  												((uint32_t)0x00000200)
#define DMA_CH4CTRL_CH4SSEL_USART1_TX 											((uint32_t)0x00000300)
#define DMA_CH4CTRL_CH4SSEL_UART4_TX 												((uint32_t)0x00000400)
#define DMA_CH4CTRL_CH4SSEL_UART1_TX 												((uint32_t)0x00000500)
#define DMA_CH4CTRL_CH4SSEL_UART0_TX 												((uint32_t)0x00000600)
#define DMA_CH4CTRL_CH4SSEL_SPI1_TX 												((uint32_t)0x00000700)

#define DMA_CH5CTRL_CH5SSEL_LPTIM_CAP												((uint32_t)0x00000000)
#define DMA_CH5CTRL_CH5SSEL_USART1_RX 											((uint32_t)0x00000100)
#define DMA_CH5CTRL_CH5SSEL_USART0_RX 											((uint32_t)0x00000200)
#define DMA_CH5CTRL_CH5SSEL_UART5_RX 												((uint32_t)0x00000300)
#define DMA_CH5CTRL_CH5SSEL_UART2_RX 												((uint32_t)0x00000400)
#define DMA_CH5CTRL_CH5SSEL_UART1_RX 												((uint32_t)0x00000500)
#define DMA_CH5CTRL_CH5SSEL_SPI2_RX													((uint32_t)0x00000600)
#define DMA_CH5CTRL_CH5SSEL_SPI0_RX 												((uint32_t)0x00000700)

#define DMA_CH6CTRL_CH6SSEL_LPTIM_CAP												((uint32_t)0x00000000)
#define DMA_CH6CTRL_CH6SSEL_USART1_TX												((uint32_t)0x00000100)
#define DMA_CH6CTRL_CH6SSEL_USART0_TX 											((uint32_t)0x00000200)
#define DMA_CH6CTRL_CH6SSEL_UART5_TX 												((uint32_t)0x00000300)
#define DMA_CH6CTRL_CH6SSEL_UART2_TX 												((uint32_t)0x00000400)
#define DMA_CH6CTRL_CH6SSEL_UART1_TX 												((uint32_t)0x00000500)
#define DMA_CH6CTRL_CH6SSEL_SPI2_TX 												((uint32_t)0x00000600)
#define DMA_CH6CTRL_CH6SSEL_SPI0_TX 												((uint32_t)0x00000700)


/**
* @}
*/ 

/** @defgroup DMA_CH7CTRL_CH7TSIZE
  * @{
  */
#define DMA_CH7CTRL_CH7TSIZE_Pos               						  16                                            
#define DMA_CH7CTRL_CH7TSIZE_Msk               						 	(0xFFFUL << DMA_CH7CTRL_CH7TSIZE_Pos)

/** @defgroup DMA_CH7CTRL_CH7PRI
  * @{
  */  
#define DMA_CH7CTRL_CH7PRI_Pos               								12                                            
#define DMA_CH7CTRL_CH7PRI_Msk               								(0x03UL << DMA_CH7CTRL_CH7PRI_Pos) 
#define DMA_CH7CTRL_CH7PRI_LOW		                					((uint32_t)0x00000000)
#define DMA_CH7CTRL_CH7PRI_Medium                						((uint32_t)0x00001000)
#define DMA_CH7CTRL_CH7PRI_High               							((uint32_t)0x00002000)
#define DMA_CH7CTRL_CH7PRI_VeryHigh               					((uint32_t)0x00003000)


/** @defgroup DMA_CH7CTRL_CH7DIR
  * @{
  */  
#define DMA_CH7CTRL_CH7DIR_Pos                							10                                            
#define DMA_CH7CTRL_CH7DIR_Msk               								(0x01UL << DMA_CH7CTRL_CH7DIR_Pos) 
#define DMA_CH7CTRL_CH7DIR_Ram2Flash           							((uint32_t)0x00000000)
#define DMA_CH7CTRL_CH7DIR_Flash2Ram           							((uint32_t)0x00000400)

/** @defgroup DMA_CH7CTRL_CH7RI
  * @{
  */  
#define DMA_CH7CTRL_CH7RI_Pos               								9
#define DMA_CH7CTRL_CH7RI_Msk               								(0x01UL << DMA_CH7CTRL_CH7RI_Pos) 
#define DMA_CH7CTRL_CH7RI_Dec                							  ((uint32_t)0x00000000)
#define DMA_CH7CTRL_CH7RI_Inc                							  ((uint32_t)0x00000200)

/** @defgroup DMA_CH7CTRL_CH7FI
  * @{
  */  
#define DMA_CH7CTRL_CH7FI_Pos               								8                                            
#define DMA_CH7CTRL_CH7FI_Msk               								(0x01UL << DMA_CH7CTRL_CH7FI_Pos) 
#define DMA_CH7CTRL_CH7FI_Dec                							  ((uint32_t)0x00000000)
#define DMA_CH7CTRL_CH7FI_Inc                							  ((uint32_t)0x00000100)

/** @defgroup DMA_CH7CTRL_CH7FTIE
  * @{
  */
#define DMA_CH7CTRL_CH7FTIE_Pos               							2                                            
#define DMA_CH7CTRL_CH7FTIE_Msk               							(0x01UL << DMA_CH7CTRL_CH7FTIE_Pos)  
#define DMA_CH7CTRL_CH7FTIE_Disable                					((uint32_t)0x00000000)
#define DMA_CH7CTRL_CH7FTIE_Enable	                				((uint32_t)0x00000004)

/** @defgroup DMA_CH7CTRL_CH7HTIE
  * @{
  */ 
#define DMA_CH7CTRL_CH7HTIE_Pos               							1                                            
#define DMA_CH7CTRL_CH7HTIE_Msk               							(0x01UL << DMA_CH7CTRL_CH7HTIE_Pos) 
#define DMA_CH7CTRL_CH7HTIE_Disable                					((uint32_t)0x00000000)
#define DMA_CH7CTRL_CH7HTIE_Enable                					((uint32_t)0x00000002)

/** @defgroup DMA_CH7CTRL_CH7EN
  * @{
  */ 
#define DMA_CH7CTRL_CH7EN_Pos               								0                                            
#define DMA_CH7CTRL_CH7EN_Msk               								(0x01UL << DMA_CH7CTRL_CH7EN_Pos) 
#define DMA_CH7CTRL_CH7EN_Disable                						((uint32_t)0x00000000)
#define DMA_CH7CTRL_CH7EN_Enable                						((uint32_t)0x00000001)

/**
* @}
*/ 

/** @defgroup DMA_CH7FLSAD_CH7FLSAD
  * @{
  */
#define DMA_CH7FLSAD_CH7FLSAD_Pos               						  0                                            
#define DMA_CH7FLSAD_CH7FLSAD_Msk               						 	(0x1FFFFUL << DMA_CH7FLSAD_CH7FLSAD_Pos)	

/**
* @}
*/ 

/** @defgroup DMA_CH7RAMAD_CH7RAMAD
  * @{
  */
#define DMA_CH7RAMAD_CH7RAMAD_Pos               						  0                                            
#define DMA_CH7RAMAD_CH7RAMAD_Msk               						 	(0x3FFFUL << DMA_CH7RAMAD_CH7RAMAD_Pos)	
	
/**
* @}
*/ 

/** @defgroup DMA_CHSTATUS_DMACHFT
  * @{
  */
#define DMA_CHSTATUS_DMACHFT_7               						  ((uint32_t)0x00008000)                                           
#define DMA_CHSTATUS_DMACHFT_6               						  ((uint32_t)0x00004000) 
#define DMA_CHSTATUS_DMACHFT_5               						  ((uint32_t)0x00002000) 
#define DMA_CHSTATUS_DMACHFT_4               						  ((uint32_t)0x00001000) 
#define DMA_CHSTATUS_DMACHFT_3               						  ((uint32_t)0x00000800) 
#define DMA_CHSTATUS_DMACHFT_2               						  ((uint32_t)0x00000400) 
#define DMA_CHSTATUS_DMACHFT_1               						  ((uint32_t)0x00000200) 
#define DMA_CHSTATUS_DMACHFT_0               						  ((uint32_t)0x00000100) 

/** @defgroup DMA_CHSTATUS_DMACHHT
  * @{
  */
#define DMA_CHSTATUS_DMACHHT_7               						  ((uint32_t)0x00000080)                                           
#define DMA_CHSTATUS_DMACHHT_6               						  ((uint32_t)0x00000040) 
#define DMA_CHSTATUS_DMACHHT_5               						  ((uint32_t)0x00000020) 
#define DMA_CHSTATUS_DMACHHT_4               						  ((uint32_t)0x00000010) 
#define DMA_CHSTATUS_DMACHHT_3               						  ((uint32_t)0x00000008) 
#define DMA_CHSTATUS_DMACHHT_2               						  ((uint32_t)0x00000004) 
#define DMA_CHSTATUS_DMACHHT_1               						  ((uint32_t)0x00000002) 
#define DMA_CHSTATUS_DMACHHT_0               						  ((uint32_t)0x00000001) 		

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
extern void DMA_Globle_Disable(void);
extern void DMA_Globle_Ensable(void);
extern void DMA_Init(DMA_InitType* DMA_InitStruct);
extern void DMA_Channel_Enable(DmaChannel DMA_num,uint32_t NewSet);
extern void DMA_Channel_Disable(DmaChannel DMA_num,uint32_t NewSet);
extern ITStatus DMA_GetITStatus(uint32_t DMA_IT);
extern void DMA_ClrITStatus(uint32_t DMA_IT);
extern void DMA_TRANS_FLASH_TO_RAM(uint32_t flash_addr,uint32_t ram_addr,uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* __FM385_RCC_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/




