/**
  ******************************************************************************
  * @file    fm32l0xx_rcc.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    20-SETP-2016
  * @brief   This file contains all the functions prototypes for the RCC firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_RCC_H
#define __FM32L0xx_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM33A0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants
  * @{
  */

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t SYSCLK_Frequency; /*!<  SYSCLK clock frequency expressed in Hz */
  uint32_t AHBCLK_Frequency;  /*!<  AHB clock frequency expressed in Hz  */
  uint32_t APBCLK_Frequency;  /*!<  APB clock frequency expressed in Hz  */
  uint32_t RCHF_Frequency;   /*!<  RCHF clock frequency expressed in Hz   */
  uint32_t PLL_Frequency;   /*!<  PLL clock frequency expressed in Hz   */
}RCC_ClocksType;


/**
* @}
*/ 
#define HXVAR(object, addr)   (*((object *) (addr)))
#define const_rchf_Trim8 	HXVAR( uint32_t, 0x1FFFFD40 )	//RC8M 常温校准�?
#define const_rchf_Trim16 	HXVAR( uint32_t, 0x1FFFFD3C )	//RC16M 常温校准�?
#define const_rchf_Trim24 	HXVAR( uint32_t, 0x1FFFFD38 )	//RC24M 常温校准�?
#define const_rchf_Trim32 	HXVAR( uint32_t, 0x1FFFFD34 )	//RC32M 常温校准�?  
/** @defgroup RCC_SYSRCCSEL_SYSRCCSEL 
  * @{
  */
#define RCC_SYSRCCSEL_SYSRCCSEL_Pos               					0                                             
#define RCC_SYSRCCSEL_SYSRCCSEL_Msk               					(0x03UL << RCC_SYSRCCSEL_SYSRCCSEL_Pos)  
#define RCC_SYSRCCSEL	               										((uint32_t)0x00000003)
#define RCC_SYSRCCSEL_RCHF                									((uint32_t)0x00000000)
#define RCC_SYSRCCSEL_RCLP                									((uint32_t)0x00000001)
#define RCC_SYSRCCSEL_LSRCC                									((uint32_t)0x00000002)
#define RCC_SYSRCCSEL_PLL                										((uint32_t)0x00000003)


/** @defgroup RCC_SYSRCCSEL_AHBPRES
  * @{
  */
#define RCC_SYSRCCSEL_AHBPRES_Pos               						8                                            
#define RCC_SYSRCCSEL_AHBPRES_Msk               						(0x07UL << RCC_SYSRCCSEL_AHBPRES_Pos)
#define RCC_SYSRCCSEL_AHBPRES_NONE                					((uint32_t)0x00000000)
#define RCC_SYSRCCSEL_AHBPRES_2                							((uint32_t)0x00000400)
#define RCC_SYSRCCSEL_AHBPRES_4               							((uint32_t)0x00000500)
#define RCC_SYSRCCSEL_AHBPRES_8                							((uint32_t)0x00000600)
#define RCC_SYSRCCSEL_AHBPRES_16                						((uint32_t)0x00000700)

/** @defgroup RCC_SYSRCCSEL_APBPRES
  * @{
  */  
#define RCC_SYSRCCSEL_APBPRES_Pos               						16                                            
#define RCC_SYSRCCSEL_APBPRES_Msk               						(0x07UL << RCC_SYSRCCSEL_APBPRES_Pos) 
#define RCC_SYSRCCSEL_APBPRES_NONE                					((uint32_t)0x00000000)
#define RCC_SYSRCCSEL_APBPRES_2                							((uint32_t)0x00040000)
#define RCC_SYSRCCSEL_APBPRES_4               							((uint32_t)0x00050000)
#define RCC_SYSRCCSEL_APBPRES_8                							((uint32_t)0x00060000)
#define RCC_SYSRCCSEL_APBPRES_16                						((uint32_t)0x00070000)

/** @defgroup RCC_SYSRCCSEL_EXTICKSEL
  * @{
  */  
#define RCC_SYSRCCSEL_EXTICKSEL_Pos               					24                                            
#define RCC_SYSRCCSEL_EXTICKSEL_Msk               					(0x01UL << RCC_SYSRCCSEL_EXTICKSEL_Pos) 
#define RCC_SYSRCCSEL_EXTICKSEL_AHBRCC                			((uint32_t)0x00000000)
#define RCC_SYSRCCSEL_EXTICKSEL_LSRCC                				((uint32_t)0x01000000)

/** @defgroup RCC_SYSRCCSEL_SLP_ENEXTI
  * @{
  */
#define RCC_SYSRCCSEL_SLP_ENEXTI_Pos               					25                                            
#define RCC_SYSRCCSEL_SLP_ENEXTI_Msk               					(0x01UL << RCC_SYSRCCSEL_SLP_ENEXTI_Pos)  
#define RCC_SYSRCCSEL_SLP_ENEXTI_NONE                				((uint32_t)0x00000000)
#define RCC_SYSRCCSEL_SLP_ENEXTI_LSRCC                			((uint32_t)0x02000000)

/** @defgroup RCC_SYSRCCSEL_WKUPRCC
  * @{
  */ 
#define RCC_SYSRCCSEL_WKUPRCC_Pos               						26                                            
#define RCC_SYSRCCSEL_WKUPRCC_Msk               						(0x01UL << RCC_SYSRCCSEL_WKUPRCC_Pos) 
#define RCC_SYSRCCSEL_WKUPRCC_RCHF                					((uint32_t)0x00000000)/*8MH*/
#define RCC_SYSRCCSEL_WKUPRCC_RCLP                					((uint32_t)0x04000000)/*512k*/

/** @defgroup RCC_SYSRCCSEL_LPM_RCLP_OFF
  * @{
  */ 
#define RCC_SYSRCCSEL_LPM_RCLP_OFF_Pos               				31                                            
#define RCC_SYSRCCSEL_LPM_RCLP_OFF_Msk              				(0x01UL << RCC_SYSRCCSEL_LPM_RCLP_OFF_Pos) 
#define RCC_SYSRCCSEL_LPM_RCLP_ON               						((uint32_t)0x00000000)
#define RCC_SYSRCCSEL_LPM_RCLP_OFF               						((uint32_t)0x80000000)

/**
  * @}
  */ 

/** @defgroup RCC_RCHFCON_RCHFEN
  * @{
  */  
#define RCC_RCHFCON_RCHFEN_Pos               								0                                            
#define RCC_RCHFCON_RCHFEN_Msk              								(0x01UL << RCC_RCHFCON_RCHFEN_Pos) 
#define RCC_RCHFCON_RCHFEN_OFF               								((uint32_t)0x00000000)
#define RCC_RCHFCON_RCHFEN_ON               								((uint32_t)0x00000001)

/** @defgroup RCC_RCHFCON_FSEL
  * @{
  */  
#define RCC_RCHFCON_FSEL_Pos               									16                                            
#define RCC_RCHFCON_FSEL_Msk              									(0x03UL << RCC_RCHFCON_FSEL_Pos) 
#define RCC_RCHFCON_FSEL_8M               									((uint32_t)0x00000000)
#define RCC_RCHFCON_FSEL_16M               									((uint32_t)0x00010000)
#define RCC_RCHFCON_FSEL_24M               									((uint32_t)0x00020000)
#define RCC_RCHFCON_FSEL_32M               									((uint32_t)0x00030000)


/**
  * @}
  */ 

/** @defgroup RCC_RCHFTRIM_RCHFTRIM
  * @{
  */
#define RCC_RCHFTRIM_RCHFTRIM_Pos               						0                                            
#define RCC_RCHFTRIM_RCHFTRIM_Msk   												((uint32_t)0x0000007F)
#define IS_RCC_RCHFTRIM(RCHFTRIM) 													((RCHFTRIM) <= 0x7FUL) 

/**
  * @}
  */ 

/** @defgroup RCC_PLLCON_PLLEN
  * @{
  */ 
#define RCC_PLLCON_PLLEN_Pos               									0                                            
#define RCC_PLLCON_PLLEN_Msk              									(0x01UL << RCC_PLLCON_PLLEN_Pos)
#define RCC_PLLCON_PLLEN_OFF               									((uint32_t)0x00000000)
#define RCC_PLLCON_PLLEN_ON               									((uint32_t)0x00000001)

/** @defgroup RCC_PLLCON_PLLINSEL
  * @{
  */
	
#define RCC_PLLCON_PLLINSEL_Pos               							1                                            
#define RCC_PLLCON_PLLINSEL_Msk              								(0x03UL << RCC_PLLCON_PLLINSEL_Pos) 
#define RCC_PLLCON_PLLDB32768											(0x01F30000)
#define RCC_PLLCON_PLLDB3125											(0x027F0000)
#define RCC_PLLCON_PLLOSEL0	               								((uint32_t)0x00000000)
#define RCC_PLLCON_PLLINSEL_XTLF               								((uint32_t)0x00000000)
#define RCC_PLLCON_PLLINSEL_RCLP               								((uint32_t)0x00000002)
#define RCC_PLLCON_PLLINSEL_RCHF_256               							((uint32_t)0x00000004)
//#define RCC_PLLINSEL_XTLF               									((uint32_t)0x00000006)

/** @defgroup RCC_PLLCON_LOCKED
  * @{
  */                                    
#define RCC_PLLCON_LOCKED_Pos               								7                                            
#define RCC_PLLCON_LOCKED_Msk              									(0x01UL << RCC_PLLCON_LOCKED_Pos) 
#define RCC_PLLCON_LOCKED_NONE               								((uint32_t)0x00000000)
#define RCC_PLLCON_LOCKED_RDY               								((uint32_t)0x00000080)


/** @defgroup RCC_PLLCON_PLLDB
  * @{
  */                                           
#define RCC_PLLCON_PLLDB_Pos               									16                                            
#define RCC_PLLCON_PLLDB_Msk              									(0x3FFUL << RCC_PLLCON_PLLDB_Pos)   
#define IS_PLL_PLLDB(VALUE)		((VALUE) <= 0x3FFUL)

/**
  * @}
  */ 
	
/** @defgroup RCC_RCLPCON_LOCKED
  * @{
  */                                    
#define RCC_RCLPCON_RCLP_HFEN_B_Pos               						16                                            
#define RCC_RCLPCON_RCLP_HFEN_B_Msk              							(0x01UL << RCC_PLLCON_LOCKED_Pos) 
#define RCC_RCLPCON_RCLP_HFEN_B_512K               						((uint32_t)0x00000000)
#define RCC_RCLPCON_RCLP_HFEN_B_32K               						((uint32_t)0x00010000)

/** @defgroup RCC_RCLPCON_LOCKED
  * @{
  */                                    
#define RCC_RCLPCON_RCLP_EN_B_Pos               							0                                            
#define RCC_RCLPCON_RCLP			               							((uint32_t)0x00000001)                                            
#define RCC_RCLPCON_RCLP_EN_B_Msk              								(0x01UL << RCC_PLLCON_LOCKED_Pos) 
#define RCC_RCLPCON_RCLP_EN_B_ON               								((uint32_t)0x00000000)
#define RCC_RCLPCON_RCLP_EN_B_OFF               							((uint32_t)0x00000001)


/**
  * @}
  */ 

/** @defgroup RCC_RCLPTRIM_RCLPTRIM
  * @{
  */
#define RCC_RCLPTRIM_RCLPTRIM_Pos               							0                                            
#define RCC_RCLPTRIM_RCLPTRIM_Msk              								(0x0FUL << RCC_RCLPTRIM_RCLPTRIM_Pos)   
#define IS_PLL_RCLPTRIM(VALUE)		((VALUE) <= 0x0FUL)

/**
  * @}
  */ 

/** @defgroup RCC_XTLFIPW_XTLFIPW
  * @{
  */
#define RCC_XTLFIPW_XTLFIPW_Pos               								0                                            
#define RCC_XTLFIPW_XTLFIPW_Msk              									(0x07UL << RCC_XTLFIPW_XTLFIPW_Pos)   
#define RCC_XTLFIPW_450NA																			((uint32_t)0x00000000)
#define RCC_XTLFIPW_400NA																			((uint32_t)0x00000001)
#define RCC_XTLFIPW_350NA																			((uint32_t)0x00000002)
#define RCC_XTLFIPW_300NA																			((uint32_t)0x00000003)
#define RCC_XTLFIPW_250NA																			((uint32_t)0x00000004)
#define RCC_XTLFIPW_200NA																			((uint32_t)0x00000005)
#define RCC_XTLFIPW_150NA																			((uint32_t)0x00000006)
#define RCC_XTLFIPW_100NA																			((uint32_t)0x00000007)




/**
  * @}
  */ 

/** @defgroup RCC_PERRCCCON1_Selection
  * @{
  */
#define RCC_PERRCCCON1_LPTRCCEN_Pos               	0                                            
#define RCC_PERRCCCON1_LPTRCCEN_Msk              		(0x01UL << RCC_PERRCCCON1_LPTRCCEN_Pos) 
#define RCC_PERRCCCON1_LPTRCCEN_ON									((uint32_t)0x00000001)
#define RCC_PERRCCCON1_LPTRCCEN_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON1_LPTFCCEN_Pos               	1                                           
#define RCC_PERRCCCON1_LPTFCCEN_Msk              		(0x01UL << RCC_PERRCCCON1_LPTRCCEN_Pos) 
#define RCC_PERRCCCON1_LPTFCCEN_ON									((uint32_t)0x00000002)
#define RCC_PERRCCCON1_LPTFCCEN_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON1_RTCRCCEN_Pos               	2                                            
#define RCC_PERRCCCON1_RTCRCCEN_Msk              		(0x01UL << RCC_PERRCCCON1_RTCRCCEN_Pos) 
#define RCC_PERRCCCON1_RTCRCCEN_ON									((uint32_t)0x00000004)
#define RCC_PERRCCCON1_RTCRCCEN_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON1_PMURCCEN_Pos               	3                                            
#define RCC_PERRCCCON1_PMURCCEN_Msk              		(0x01UL << RCC_PERRCCCON1_PMURCCEN_Pos)  
#define RCC_PERRCCCON1_PMURCCEN_ON									((uint32_t)0x00000008)
#define RCC_PERRCCCON1_PMURCCEN_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON1_SCUCKEN_Pos               		4                                            
#define RCC_PERRCCCON1_SCUCKEN_Msk              		(0x01UL << RCC_PERRCCCON1_SCUCKEN_Pos) 
#define RCC_PERRCCCON1_SCUCKEN_ON               		((uint32_t)0x00000010)                                            
#define RCC_PERRCCCON1_SCUCKEN_OFF              		((uint32_t)0x00000000)

#define RCC_PERRCCCON1_IWDTCKEN_Pos               	5                                            
#define RCC_PERRCCCON1_IWDTCKEN_Msk              		(0x01UL << RCC_PERRCCCON1_PMURCCEN_Pos) 
#define RCC_PERRCCCON1_IWDTCKEN_ON               		((uint32_t)0x00000020)                                            
#define RCC_PERRCCCON1_IWDTCKEN_OFF              		((uint32_t)0x00000000)

#define RCC_PERRCCCON1_ANACKEN_Pos               		6                                            
#define RCC_PERRCCCON1_ANACKEN_Msk              		(0x01UL << RCC_PERRCCCON1_PMURCCEN_Pos) 
#define RCC_PERRCCCON1_ANACKEN_ON               		((uint32_t)0x00000040)                                            
#define RCC_PERRCCCON1_ANACKEN_OFF              		((uint32_t)0x00000000)

#define RCC_PERRCCCON1_PDCCKEN_Pos               		7                                            
#define RCC_PERRCCCON1_PDCCKEN_Msk              		(0x01UL << RCC_PERRCCCON1_PMURCCEN_Pos) 
#define RCC_PERRCCCON1_PDCCKEN_ON               		((uint32_t)0x00000080)                                            
#define RCC_PERRCCCON1_PDCCKEN_OFF              		((uint32_t)0x00000000)

#define RCC_PERRCCCON1_EXTICKEN0_Pos               	8                                            
#define RCC_PERRCCCON1_EXTICKEN0_Msk              	(0x01UL << RCC_PERRCCCON1_EXTICKEN0_Pos) 
#define RCC_PERRCCCON1_EXTICKEN0_ON               	((uint32_t)0x00000100)                                            
#define RCC_PERRCCCON1_EXTICKEN0_OFF              	((uint32_t)0x00000000)

#define RCC_PERRCCCON1_EXTICKEN1_Pos               	9                                            
#define RCC_PERRCCCON1_EXTICKEN1_Msk              	(0x01UL << RCC_PERRCCCON1_EXTICKEN1_Pos) 
#define RCC_PERRCCCON1_EXTICKEN1_ON               	((uint32_t)0x00000200)                                            
#define RCC_PERRCCCON1_EXTICKEN1_OFF              	((uint32_t)0x00000000)

#define RCC_PERRCCCON1_EXTICKEN2_Pos               	10                                            
#define RCC_PERRCCCON1_EXTICKEN2_Msk              	(0x01UL << RCC_PERRCCCON1_EXTICKEN2_Pos) 
#define RCC_PERRCCCON1_EXTICKEN2_ON               	((uint32_t)0x00000400)                                            
#define RCC_PERRCCCON1_EXTICKEN2_OFF              	((uint32_t)0x00000000)

#define RCC_PERRCCCON1_DCUCKEN_Pos               		31                                            
#define RCC_PERRCCCON1_DCUCKEN_Msk              		(0x01UL << RCC_PERRCCCON1_DCUCKEN_Pos) 
#define RCC_PERRCCCON1_DCUCKEN_ON               		((uint32_t)0x80000000)                                            
#define RCC_PERRCCCON1_DCUCKEN_OFF              		((uint32_t)0x00000000)

/**
  * @}
  */ 

/** @defgroup RCC_PERRCCCON2_Selection
  * @{
  */
#define RCC_PERRCCCON2_CRCCKE_Pos               		0                                            
#define RCC_PERRCCCON2_CRCCKE_Msk              			(0x01UL << RCC_PERRCCCON2_CRCCKE_Pos)  
#define RCC_PERRCCCON2_CRCCKE_ON										((uint32_t)0x00000001)
#define RCC_PERRCCCON2_CRCCKE_OFF										((uint32_t)0x00000000)

#define RCC_PERRCCCON2_RNGCKE_Pos               		1                                            
#define RCC_PERRCCCON2_RNGCKE_Msk              			(0x01UL << RCC_PERRCCCON2_RNGCKE_Pos)  
#define RCC_PERRCCCON2_RNGCKE_ON										((uint32_t)0x00000002)
#define RCC_PERRCCCON2_RNGCKE_OFF										((uint32_t)0x00000000)

#define RCC_PERRCCCON2_AESCKE_Pos               		2                                            
#define RCC_PERRCCCON2_AESCKE_Msk              			(0x01UL << RCC_PERRCCCON2_AESCKE_Pos) 
#define RCC_PERRCCCON2_AESCKE_ON										((uint32_t)0x00000004)
#define RCC_PERRCCCON2_AESCKE_OFF										((uint32_t)0x00000000)

#define RCC_PERRCCCON2_LCDCKE_Pos               		3                                            
#define RCC_PERRCCCON2_LCDCKE_Msk              			(0x01UL << RCC_PERRCCCON2_LCDCKE_Pos)  
#define RCC_PERRCCCON2_LCDCKE_ON										((uint32_t)0x00000008)
#define RCC_PERRCCCON2_LCDCKE_OFF										((uint32_t)0x00000000)

#define RCC_PERRCCCON2_DMACKE_Pos               		4                                            
#define RCC_PERRCCCON2_DMACKE_Msk              			(0x01UL << RCC_PERRCCCON2_DMACKE_Pos)  
#define RCC_PERRCCCON2_DMACKE_ON										((uint32_t)0x00000010)
#define RCC_PERRCCCON2_DMACKE_OFF										((uint32_t)0x00000000)

#define RCC_PERRCCCON2_FLSCKE_Pos               		5                                            
#define RCC_PERRCCCON2_FLSCKE_Msk              			(0x01UL << RCC_PERRCCCON2_FLSCKE_Pos) 
#define RCC_PERRCCCON2_FLSCKE_ON										((uint32_t)0x00000020)
#define RCC_PERRCCCON2_FLSCKE_OFF										((uint32_t)0x00000000)

#define RCC_PERRCCCON2_RAMBISTCKE_Pos             	6                                            
#define RCC_PERRCCCON2_RAMBISTCKE_Msk              	(0x01UL << RCC_PERRCCCON2_RAMBISTCKE_Pos)  
#define RCC_PERRCCCON2_RAMBISTCKE_ON								((uint32_t)0x00000040)
#define RCC_PERRCCCON2_RAMBISTCKE_OFF								((uint32_t)0x00000000)

#define RCC_PERRCCCON2_WWDTCKE_Pos               		7                                            
#define RCC_PERRCCCON2_WWDTCKE_Msk              		(0x01UL << RCC_PERRCCCON2_WWDTCKE_Pos) 
#define RCC_PERRCCCON2_WWDTCKE_ON										((uint32_t)0x00000080)
#define RCC_PERRCCCON2_WWDTCKE_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON2_ADCCKE_Pos               		8                                            
#define RCC_PERRCCCON2_ADCCKE_Msk              			(0x01UL << RCC_PERRCCCON2_ADCCKE_Pos)  
#define RCC_PERRCCCON2_ADCCKE_ON										((uint32_t)0x00000100)
#define RCC_PERRCCCON2_ADCCKE_OFF										((uint32_t)0x00000000)

#define RCC_PERRCCCON2_ADCCKSEL_Pos               	16                                            
#define RCC_PERRCCCON2_ADCCKSEL_Msk              		(0x07UL << RCC_PERRCCCON2_ADCCKSEL_Pos)   
#define RCC_PERRCCCON2_ADCCKSEL_RCHF								((uint32_t)0x00000000)
#define RCC_PERRCCCON2_ADCCKSEL_RCHFDIV2						((uint32_t)0x00010000)
#define RCC_PERRCCCON2_ADCCKSEL_RCHFDIV4						((uint32_t)0x00020000)
#define RCC_PERRCCCON2_ADCCKSEL_RCHFDIV8						((uint32_t)0x00030000)
#define RCC_PERRCCCON2_ADCCKSEL_RCHFDIV16						((uint32_t)0x00040000)
#define RCC_PERRCCCON2_ADCCKSEL_RCHFDIV32						((uint32_t)0x00050000)
#define RCC_PERRCCCON2_ADCCKSEL_RCHFDIV64						((uint32_t)0x00060000)
#define RCC_PERRCCCON2_ADCCKSEL_RCLP								((uint32_t)0x00070000)


/**
  * @}
  */ 

/** @defgroup RCC_PERRCCCON3_Selection
  * @{
  */
#define RCC_PERRCCCON3_SPI1CKE_Pos               		0                                            
#define RCC_PERRCCCON3_SPI1CKE_Msk              		(0x01UL << RCC_PERRCCCON3_SPI1CKE_Pos)  
#define RCC_PERRCCCON3_SPI1CKE_ON										((uint32_t)0x00000001)
#define RCC_PERRCCCON3_SPI1CKE_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON3_SPI2CKE_Pos               		1                                            
#define RCC_PERRCCCON3_SPI2CKE_Msk              		(0x01UL << RCC_PERRCCCON3_SPI2CKE_Pos) 
#define RCC_PERRCCCON3_SPI2CKE_ON										((uint32_t)0x00000002)
#define RCC_PERRCCCON3_SPI2CKE_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON3_HSPICKE_Pos               		2                                            
#define RCC_PERRCCCON3_HSPICKE_Msk              		(0x01UL << RCC_PERRCCCON3_HSPICKE_Pos) 
#define RCC_PERRCCCON3_HSPICKE_ON                               ((uint32_t)0x00000004)
#define RCC_PERRCCCON3_HSPICKE_OFF									((uint32_t)0x00000000)


#define RCC_PERRCCCON3_UART0CKE_Pos               	8                                            
#define RCC_PERRCCCON3_UART0CKE_Msk              		(0x01UL << RCC_PERRCCCON3_UART0CKE_Pos) 
#define RCC_PERRCCCON3_UART0CKE_ON									((uint32_t)0x00000100)
#define RCC_PERRCCCON3_UART0CKE_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON3_UART1CKE_Pos               	9                                            
#define RCC_PERRCCCON3_UART1CKE_Msk              		(0x01UL << RCC_PERRCCCON3_UART1CKE_Pos)  
#define RCC_PERRCCCON3_UART1CKE_ON									((uint32_t)0x00000200)
#define RCC_PERRCCCON3_UART1CKE_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON3_UART2CKE_Pos               	10                                            
#define RCC_PERRCCCON3_UART2CKE_Msk              		(0x01UL << RCC_PERRCCCON3_UART2CKE_Pos) 
#define RCC_PERRCCCON3_UART2CKE_ON									((uint32_t)0x00000400)
#define RCC_PERRCCCON3_UART2CKE_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON3_UART3CKE_Pos               	11                                            
#define RCC_PERRCCCON3_UART3CKE_Msk              		(0x01UL << RCC_PERRCCCON3_UART3CKE_Pos) 
#define RCC_PERRCCCON3_UART3CKE_ON									((uint32_t)0x00000800)
#define RCC_PERRCCCON3_UART3CKE_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON3_UART4CKE_Pos               	12                                            
#define RCC_PERRCCCON3_UART4CKE_Msk              		(0x01UL << RCC_PERRCCCON3_UART4CKE_Pos) 
#define RCC_PERRCCCON3_UART4CKE_ON									((uint32_t)0x00001000)
#define RCC_PERRCCCON3_UART4CKE_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON3_UART5CKE_Pos               	13                                            
#define RCC_PERRCCCON3_UART5CKE_Msk              		(0x01UL << RCC_PERRCCCON3_UART5CKE_Pos)
#define RCC_PERRCCCON3_UART5CKE_ON									((uint32_t)0x00002000)
#define RCC_PERRCCCON3_UART5CKE_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON3_UARTCCKE_Pos               	14                                            
#define RCC_PERRCCCON3_UARTCCKE_Msk              		(0x01UL << RCC_PERRCCCON3_UARTCCKE_Pos)
#define RCC_PERRCCCON3_UARTCCKE_ON									((uint32_t)0x00004000)
#define RCC_PERRCCCON3_UARTCCKE_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON3_USART0CKE_Pos               	16                                            
#define RCC_PERRCCCON3_USART0CKE_Msk              	(0x01UL << RCC_PERRCCCON3_USART0CKE_Pos) 
#define RCC_PERRCCCON3_USART0CKE_ON									((uint32_t)0x00010000)
#define RCC_PERRCCCON3_USART0CKE_OFF								((uint32_t)0x00000000)

#define RCC_PERRCCCON3_USART1CKE_Pos               	17                                            
#define RCC_PERRCCCON3_USART1CKE_Msk              	(0x01UL << RCC_PERRCCCON3_USART1CKE_Pos)  
#define RCC_PERRCCCON3_USART1CKE_ON									((uint32_t)0x00020000)
#define RCC_PERRCCCON3_USART1CKE_OFF								((uint32_t)0x00000000)


#define RCC_PERRCCCON3_I2CCKE_Pos               		24                                            
#define RCC_PERRCCCON3_I2CCKE_Msk              			(0x01UL << RCC_PERRCCCON3_I2CCKE_Pos) 
#define RCC_PERRCCCON3_I2CCKE_ON										((uint32_t)0x01000000)
#define RCC_PERRCCCON3_I2CCKE_OFF										((uint32_t)0x00000000)


/**
  * @}
  */ 

/** @defgroup RCC_PERRCCCON4_Selection
  * @{
  */
#define RCC_PERRCCCON4_BT12CKE_Pos               		0                                            
#define RCC_PERRCCCON4_BT12CKE_Msk              		(0x01UL << RCC_PERRCCCON4_BT12CKE_Pos)  
#define RCC_PERRCCCON4_BT12CKE_ON										((uint32_t)0x00000001)
#define RCC_PERRCCCON4_BT12CKE_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON4_BT34CKE_Pos               		1                                            
#define RCC_PERRCCCON4_BT34CKE_Msk              		(0x01UL << RCC_PERRCCCON4_BT34CKE_Pos)  
#define RCC_PERRCCCON4_BT34CKE_ON										((uint32_t)0x00000002)
#define RCC_PERRCCCON4_BT34CKE_OFF									((uint32_t)0x00000000)

#define RCC_PERRCCCON4_ET1CKE_Pos               		2                                            
#define RCC_PERRCCCON4_ET1CKE_Msk              			(0x01UL << RCC_PERRCCCON4_ET1CKE_Pos)
#define RCC_PERRCCCON4_ET1CKE_ON										((uint32_t)0x00000004)
#define RCC_PERRCCCON4_ET1CKE_OFF										((uint32_t)0x00000000)

#define RCC_PERRCCCON4_ET2CKE_Pos               		3                                            
#define RCC_PERRCCCON4_ET2CKE_Msk              			(0x01UL << RCC_PERRCCCON4_ET2CKE_Pos) 
#define RCC_PERRCCCON4_ET2CKE_ON										((uint32_t)0x00000008)
#define RCC_PERRCCCON4_ET2CKE_OFF										((uint32_t)0x00000000)

#define RCC_PERRCCCON4_ET3CKE_Pos               		4                                            
#define RCC_PERRCCCON4_ET3CKE_Msk              			(0x01UL << RCC_PERRCCCON4_ET3CKE_Pos) 
#define RCC_PERRCCCON4_ET3CKE_ON										((uint32_t)0x00000010)
#define RCC_PERRCCCON4_ET3CKE_OFF										((uint32_t)0x00000000)

#define RCC_PERRCCCON4_ET4CKE_Pos               		5                                            
#define RCC_PERRCCCON4_ET4CKE_Msk              			(0x01UL << RCC_PERRCCCON4_ET4CKE_Pos) 
#define RCC_PERRCCCON4_ET4CKE_ON										((uint32_t)0x00000020)
#define RCC_PERRCCCON4_ET4CKE_OFF										((uint32_t)0x00000000)




/**
  * @}
  */ 

/** @defgroup RCC_MPRIL_Selection
  * @{
  */
#define RCC_MPRIL_MPRIL_Pos               				0                                            
#define RCC_MPRIL_MPRIL_Msk              					(0x01UL << RCC_PERRCCCON5_PACKE_Pos)  
#define RCC_MPRIL_MPRIL_DMA												((uint32_t)0x00000000)
#define RCC_MPRIL_MPRIL_CPU 											((uint32_t)0x00000001)



/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/ 

extern void RCC_DeInit(void);															/*initial state,8M rchf*/

extern void RCC_RCHF_FSEL_Config(uint32_t fsel_set); 			/*change the center freq 8/16/24/32M*/
extern void RCC_RCHFTRIM_Config(uint32_t rchftrim_data);	/*change the RCHFtrim data*/
extern void RCC_RCHF_enable(void);												/*enable RCHF freq*/
extern void RCC_RCHF_disable(void);												/*disable RCHF freq*/

extern void RCC_init(void);																/*general initial setting*/
extern void RCC_PERIPH_clk_enable(Periph_Type periph_num);		/*set the periph clock*/
extern void RCC_PERIPH_clk_disable(Periph_Type periph_num);	/*close the periph clock*/
extern void RCC_PERIPH_clk_set(Periph_Type periph_num,FunctionalState NewState);/*set the periph clock,according to the newstate*/
#ifdef __cplusplus
}
#endif

#endif /* __FM385_RCC_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/



