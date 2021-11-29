/**
  ******************************************************************************
  * @file    fm32l0xx_anac.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    6-MAR-2017
  * @brief   This file contains all the functions prototypes for the ANAC firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_ANAC_H
#define __FM32L0xx_ANAC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup ANAC
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/

/** @defgroup ANAC_Exported_Constants
  * @{
  */
typedef enum {
	CMP1_num = 0,	CMP2_num	=	1,		
}CMP_Type;
  
	 
/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  LPTIM Init Structure definition  
  */ 
  
typedef struct
{
  uint16_t MODE;            		/* SLELECT SVD WORK MODE */
  uint16_t Interval;          	/* SLELECT SVD Interval TIME */
  uint16_t DFEN;            	  /* ENABLE DIGITAL FILTERING */
  uint16_t LEVEL;             	/* SET DETECT VOLTAGE LEVEL*/										   	

} SVD_InitType;

/**
* @}ANAC_PDRCFG
*/ 
  
/** @defgroup ANAC_PDRCFG_PDREN
  * @{
  */
#define ANAC_PDRCFG_PDREN_Pos		               					0                                             
#define ANAC_PDRCFG_PDREN_Msk               						(0x01UL << ANAC_PDRCFG_PDREN_Pos)  
#define ANAC_PDRCFG_PDREN_DISABLE     									((uint32_t)0x00000000)
#define ANAC_PDRCFG_PDREN_ENABLE     									  ((uint32_t)0x00000001)

/** @defgroup ANAC_PDRCFG_PDRCFG
  * @{
  */
#define ANAC_PDRCFG_PDRCFG_Pos		               				1                                             
#define ANAC_PDRCFG_PDRCFG_Msk               						(0x03UL << ANAC_PDRCFG_PDRCFG_Pos)  
#define ANAC_PDRCFG_PDRCFG_1_5v                         ((uint32_t)0x00000000)
#define ANAC_PDRCFG_PDRCFG_1_25v                        ((uint32_t)0x00000002)
#define ANAC_PDRCFG_PDRCFG_1_35v                        ((uint32_t)0x00000004)
#define ANAC_PDRCFG_PDRCFG_1_4v                         ((uint32_t)0x00000006)


/**
* @}ANAC_BORCFG
*/ 

/** @defgroup ANAC_BORCFG_OFF_BOR
  * @{
  */
#define ANAC_BORCFG_OFF_BOR_Pos		               				0                                             
#define ANAC_BORCFG_OFF_BOR_Msk               					(0x01UL << ANAC_BORCFG_OFF_BOR_Pos)  
#define ANAC_BORCFG_OFF_BOR_DISABLE     								((uint32_t)0x00000000)
#define ANAC_BORCFG_OFF_BOR_ENABLE     									((uint32_t)0x00000001)

/** @defgroup ANAC_BORCFG_BOR_PDRCFG
  * @{
  */
#define ANAC_BORCFG_BOR_PDRCFG_Pos		               		1                                             
#define ANAC_BORCFG_BOR_PDRCFG_Msk               				(0x03UL << ANAC_BORCFG_BOR_PDRCFG_Pos)  
#define ANAC_BORCFG_BOR_PDRCFG_1_7v                     ((uint32_t)0x00000000)
#define ANAC_BORCFG_BOR_PDRCFG_1_6v                     ((uint32_t)0x00000002)
#define ANAC_BORCFG_BOR_PDRCFG_1_65v                    ((uint32_t)0x00000004)
#define ANAC_BORCFG_BOR_PDRCFG_1_75v                    ((uint32_t)0x00000006)


/**
* @}ANAC_SVDCFG
*/ 

/** @defgroup ANAC_SVDCFG_SVDITVL
  * @{
  */
#define ANAC_SVDCFG_SVDITVL_Pos		               				0                                             
#define ANAC_SVDCFG_SVDITVL_Msk               					(0x03L << ANAC_SVDCFG_SVDITVL_Pos)  
#define ANAC_SVDCFG_SVDITVL_15_625ms                    ((uint32_t)0x00000000) 
#define ANAC_SVDCFG_SVDITVL_62_5ms                      ((uint32_t)0x00000001) 
#define ANAC_SVDCFG_SVDITVL_256ms                       ((uint32_t)0x00000002) 
#define ANAC_SVDCFG_SVDITVL_1s                          ((uint32_t)0x00000003) 

/** @defgroup ANAC_SVDCFG_SVDMOD
  * @{
  */
#define ANAC_SVDCFG_SVDMOD_Pos		               				2                                             
#define ANAC_SVDCFG_SVDMOD_Msk               						(0x01L << ANAC_SVDCFG_SVDMOD_Pos)  
#define ANAC_SVDCFG_SVDMOD_ALWAYS_ON										((uint32_t)0x00000000)
#define ANAC_SVDCFG_SVDMOD_INTERVAL     								((uint32_t)0x00000004) 

/** @defgroup ANAC_SVDCFG_DFEN
  * @{
  */
#define ANAC_SVDCFG_DFEN_Pos		               				  3                                             
#define ANAC_SVDCFG_DFEN_Msk               						  (0x01L << ANAC_SVDCFG_DFEN_Pos)  
#define ANAC_SVDCFG_DFEN_DISABLE     									  ((uint32_t)0x00000000)
#define ANAC_SVDCFG_DFEN_ENABLE     									  ((uint32_t)0x00000008) 

/** @defgroup ANAC_SVDCFG_SVDLVL
  * @{
  */
#define ANAC_SVDCFG_SVDLVL_Pos		               				4                                             
#define ANAC_SVDCFG_SVDLVL_Msk               						(0x0FL << ANAC_SVDCFG_SVDLVL_Pos)  
#define ANAC_SVDCFG_SVDLVL_1_800v   									  ((uint32_t)0x00000000)
#define ANAC_SVDCFG_SVDLVL_2_014v                       ((uint32_t)0x00000010)
#define ANAC_SVDCFG_SVDLVL_2_229v    									  ((uint32_t)0x00000020)  
#define ANAC_SVDCFG_SVDLVL_2_443v 											((uint32_t)0x00000030)
#define ANAC_SVDCFG_SVDLVL_2_657v    									  ((uint32_t)0x00000040)     
#define ANAC_SVDCFG_SVDLVL_2_871v 											((uint32_t)0x00000050)
#define ANAC_SVDCFG_SVDLVL_3_086v    									  ((uint32_t)0x00000060)     
#define ANAC_SVDCFG_SVDLVL_3_300v 											((uint32_t)0x00000070)
#define ANAC_SVDCFG_SVDLVL_3_514v    									  ((uint32_t)0x00000080)     
#define ANAC_SVDCFG_SVDLVL_3_729v 											((uint32_t)0x00000090)
#define ANAC_SVDCFG_SVDLVL_3_943v    										((uint32_t)0x000000A0)						        
#define ANAC_SVDCFG_SVDLVL_4_157v 											((uint32_t)0x000000B0)
#define ANAC_SVDCFG_SVDLVL_4_371v 											((uint32_t)0x000000C0)
#define ANAC_SVDCFG_SVDLVL_4_586v 											((uint32_t)0x000000D0)
#define ANAC_SVDCFG_SVDLVL_4_800v												((uint32_t)0x000000E0)
#define ANAC_SVDCFG_SVDLVL_SVS 													((uint32_t)0x000000F0)

/** @defgroup ANAC_SVDCFG_PRIE
  * @{
  */
#define ANAC_SVDCFG_PRIE_Pos		               				  8                                             
#define ANAC_SVDCFG_PRIE_Msk               						  (0x01L << ANAC_SVDCFG_PRIE_Pos)  
#define ANAC_SVDCFG_PRIE_DISABLE     									  ((uint32_t)0x00000000)
#define ANAC_SVDCFG_PRIE_ENABLE     									  ((uint32_t)0x00000100) 

/** @defgroup ANAC_SVDCFG_PFIE
  * @{
  */
#define ANAC_SVDCFG_PFIE_Pos		               				  9                                             
#define ANAC_SVDCFG_PFIE_Msk               						  (0x01L << ANAC_SVDCFG_PFIE_Pos)  
#define ANAC_SVDCFG_PFIE_DISABLE     									  ((uint32_t)0x00000000)
#define ANAC_SVDCFG_PFIE_ENABLE     									  ((uint32_t)0x00000200) 


/**
* @}ANAC_SVDCON
*/ 

/** @defgroup ANAC_SVDCON_SVDEN
  * @{
  */
#define ANAC_SVDCON_SVDEN_Pos		               				  0                                             
#define ANAC_SVDCON_SVDEN_Msk               						(0x01L << ANAC_SVDCON_SVDEN_Pos)  
#define ANAC_SVDCON_SVDEN_DISABLE     									((uint32_t)0x00000000)
#define ANAC_SVDCON_SVDEN_ENABLE     									  ((uint32_t)0x00000001)

/** @defgroup ANAC_SVDCON_SVDTE
  * @{
  */
#define ANAC_SVDCON_SVDTE_Pos		               				  8                                             
#define ANAC_SVDCON_SVDTE_Msk               						(0x01L << ANAC_SVDCON_SVDTE_Pos)  
#define ANAC_SVDCON_SVDTE_DISABLE     									((uint32_t)0x00000000)
#define ANAC_SVDCON_SVDTE_ENABLE     									  ((uint32_t)0x00000100)


/**
* @}ANAC_SVDSIF
*/ 

/** @defgroup ANAC_SVDSIF_PRF
  * @{
  */
#define ANAC_SVDSIF_PRF_Pos		               				    0                                             
#define ANAC_SVDSIF_PRF_Msk               						  (0x01L << ANAC_SVDSIF_PRF_Pos)  
#define ANAC_SVDSIF_PRF_DISABLE     									  ((uint32_t)0x00000000)
#define ANAC_SVDSIF_PRF_ENABLE     									    ((uint32_t)0x00000001)

/** @defgroup ANAC_SVDSIF_PFF
  * @{
  */
#define ANAC_SVDSIF_PFF_Pos		               				    1                                             
#define ANAC_SVDSIF_PFF_Msk               						  (0x01L << ANAC_SVDSIF_PFF_Pos)  
#define ANAC_SVDSIF_PFF_DISABLE     									  ((uint32_t)0x00000000)
#define ANAC_SVDSIF_PFF_ENABLE     									    ((uint32_t)0x00000002)

/** @defgroup ANAC_SVDSIF_SVDO
  * @{
  */
#define ANAC_SVDSIF_SVDO_Pos		               				  8                                             
#define ANAC_SVDSIF_SVDO_Msk               						  (0x01L << ANAC_SVDSIF_SVDO_Pos)  
#define ANAC_SVDSIF_SVDO_LOWER_THAN_SVD								  ((uint32_t)0x00000000)
#define ANAC_SVDSIF_SVDO_HIGHER_THAN_SVD							  ((uint32_t)0x00000100)


/**
* @}ANAC_FDETIE
*/ 

/** @defgroup ANAC_FDETIE_LFDET_IE
  * @{
  */
#define ANAC_FDETIE_LFDET_IE_Pos		               			0                                             
#define ANAC_FDETIE_LFDET_IE_Msk               					(0x01L << ANAC_FDETIE_LFDET_IE_Pos)  
#define ANAC_FDETIE_LFDET_IE_DISABLE     								((uint32_t)0x00000000)
#define ANAC_FDETIE_LFDET_IE_ENABLE     								((uint32_t)0x00000001)


/**
* @}ANAC_FDETIF
*/ 

/** @defgroup ANAC_FDETIF_LFDET_IF
  * @{
  */
#define ANAC_FDETIF_LFDET_IF_Pos		               			0                                             
#define ANAC_FDETIF_LFDET_IF_Msk               					(0x01L << ANAC_FDETIF_LFDET_IF_Pos)  
#define ANAC_FDETIF_LFDET_IF_DISABLE     								((uint32_t)0x00000000)
#define ANAC_FDETIF_LFDET_IF_ENABLE     								((uint32_t)0x00000001)

/** @defgroup ANAC_FDETIF_LFDET_OUT_B
  * @{
  */
#define ANAC_FDETIF_LFDET_OUT_B_Pos		               		6                                             
#define ANAC_FDETIF_LFDET_OUT_B_Msk               			(0x01L << ANAC_FDETIF_LFDET_OUT_B_Pos)  
#define ANAC_FDETIF_LFDET_OUT_B_STOP     					    	((uint32_t)0x00000000)
#define ANAC_FDETIF_LFDET_OUT_B_NORMAL     							((uint32_t)0x00000040)


/**
* @}ANAC_ANATESTSEL
*/ 

/** @defgroup ANAC_ANATESTSEL_BUF4TST_SEL
  * @{
  */
#define ANAC_ANATESTSEL_BUF4TST_SEL_Pos		              0                                             
#define ANAC_ANATESTSEL_BUF4TST_SEL_Msk               	(0x0FL << ANAC_ANATESTSEL_BUF4TST_SEL_Pos)  
#define ANAC_ANATESTSEL_BUF4TST_SEL_vbe1_adc            ((uint32_t)0x00000000)
#define ANAC_ANATESTSEL_BUF4TST_SEL_vbe2_adc            ((uint32_t)0x00000001)
#define ANAC_ANATESTSEL_BUF4TST_SEL_vbe3_adc            ((uint32_t)0x00000002)
#define ANAC_ANATESTSEL_BUF4TST_SEL_vcmbuf_adc          ((uint32_t)0x00000003)
#define ANAC_ANATESTSEL_BUF4TST_SEL_vddx                ((uint32_t)0x00000004)
#define ANAC_ANATESTSEL_BUF4TST_SEL_lfdet_out_b         ((uint32_t)0x00000005)
#define ANAC_ANATESTSEL_BUF4TST_SEL_VDD50               ((uint32_t)0x00000006)
#define ANAC_ANATESTSEL_BUF4TST_SEL_VREF08              ((uint32_t)0x00000007)
#define ANAC_ANATESTSEL_BUF4TST_SEL_AN1                 ((uint32_t)0x00000008)
#define ANAC_ANATESTSEL_BUF4TST_SEL_AN2                 ((uint32_t)0x00000009)
#define ANAC_ANATESTSEL_BUF4TST_SEL_AN3                 ((uint32_t)0x0000000A)
#define ANAC_ANATESTSEL_BUF4TST_SEL_AN4                 ((uint32_t)0x0000000B)
#define ANAC_ANATESTSEL_BUF4TST_SEL_AN5                 ((uint32_t)0x0000000C)
#define ANAC_ANATESTSEL_BUF4TST_SEL_AN6                 ((uint32_t)0x0000000D)
#define ANAC_ANATESTSEL_BUF4TST_SEL_AN7                 ((uint32_t)0x0000000E)
#define ANAC_ANATESTSEL_BUF4TST_SEL_AN8                 ((uint32_t)0x0000000F)

/** @defgroup ANAC_ANATESTSEL_BUF4TST_BYPASS
  * @{
  */
#define ANAC_ANATESTSEL_BUF4TST_BYPASS_Pos		          4                                             
#define ANAC_ANATESTSEL_BUF4TST_BYPASS_Msk              (0x01L << ANAC_ANATESTSEL_BUF4TST_BYPASS_Pos) 
#define ANAC_ANATESTSEL_BUF4TST_BYPASS_DISABLE     			((uint32_t)0x00000000)
#define ANAC_ANATESTSEL_BUF4TST_BYPASS_ENABLE     			((uint32_t)0x00000010)

/** @defgroup ANAC_ANATESTSEL_BUF4TST_EN
  * @{
  */
#define ANAC_ANATESTSEL_BUF4TST_EN_Pos		              5                                             
#define ANAC_ANATESTSEL_BUF4TST_EN_Msk                  (0x01L << ANAC_ANATESTSEL_BUF4TST_EN_Pos) 
#define ANAC_ANATESTSEL_BUF4TST_EN_DISABLE     			    ((uint32_t)0x00000000)
#define ANAC_ANATESTSEL_BUF4TST_EN_ENABLE     				  ((uint32_t)0x00000020)


/**
* @}ANAC_ADCCON
*/ 

/** @defgroup ANAC_ADCCON_ADC_EN
  * @{
  */
#define ANAC_ADCCON_ADC_EN_Pos		               				0                                             
#define ANAC_ADCCON_ADC_EN_Msk               					  (0x01L << ANAC_ADCCON_ADC_EN_Pos)  
#define ANAC_ADCCON_ADC_EN_DISABLE     								  ((uint32_t)0x00000000)
#define ANAC_ADCCON_ADC_EN_ENABLE     									((uint32_t)0x00000001)

/** @defgroup ANAC_ADCCON_ADC_VANA_EN
  * @{
  */
#define ANAC_ADCCON_ADC_VANA_EN_Pos		               		1                                             
#define ANAC_ADCCON_ADC_VANA_EN_Msk               			(0x01L << ANAC_ADCCON_ADC_VANA_EN_Pos)  
#define ANAC_ADCCON_ADC_VANA_EN_Temp     								((uint32_t)0x00000000)
#define ANAC_ADCCON_ADC_VANA_EN_Voltage 								((uint32_t)0x00000002)

/** @defgroup ANAC_ADCCON_ADC_IE
  * @{
  */
#define ANAC_ADCCON_ADC_IE_Pos		               		  	7                                             
#define ANAC_ADCCON_ADC_IE_Msk               						(0x01L << ANAC_ADCCON_ADC_IE_Pos)  
#define ANAC_ADCCON_ADC_IE_DISABLE     						  		((uint32_t)0x00000000)
#define ANAC_ADCCON_ADC_IE_ENABLE     							  	((uint32_t)0x00000080)


/**
* @}ANAC_ADCIF
*/ 

/** @defgroup ANAC_ADCIF_ADC_IF
  * @{
  */
#define ANAC_ADCIF_ADC_IF_Pos		               				  0                                             
#define ANAC_ADCIF_ADC_IF_Msk               					  (0x01L << ANAC_ADCIF_ADC_IF_Pos)  
#define ANAC_ADCIF_ADC_IF_CLR     								  ((uint32_t)0x00000000)
#define ANAC_ADCIF_ADC_IF_SET     									  ((uint32_t)0x00000001)


/**
* @}ANAC_TRNGEN
*/ 

/** @defgroup ANAC_TRNGEN_trng_en
  * @{
  */
#define ANAC_TRNGEN_trng_en_Pos		               				0                                             
#define ANAC_TRNGEN_trng_en_Msk               					(0x01L << ANAC_TRNGEN_trng_en_Pos)  
#define ANAC_TRNGEN_trng_en_DISABLE     								((uint32_t)0x00000000)
#define ANAC_TRNGEN_trng_en_ENABLE     									((uint32_t)0x00000001)


/**
* @}ANAC_COMP1CR
*/ 

/** @defgroup ANAC_COMP1CR_CMP1EN
  * @{
  */
#define ANAC_COMP1CR_CMP1EN_Pos		               				0                                             
#define ANAC_COMP1CR_CMP1EN_Msk               					(0x01L << ANAC_COMP1CR_CMP1EN_Pos)  
#define ANAC_COMP1CR_CMP1EN_DISABLE     								((uint32_t)0x00000000)
#define ANAC_COMP1CR_CMP1EN_ENABLE     									((uint32_t)0x00000001)

/** @defgroup ANAC_COMP1CR_V1NSEL
  * @{
  */
#define ANAC_COMP1CR_V1NSEL_Pos		               				1                                             
#define ANAC_COMP1CR_V1NSEL_Msk               					(0x03L << ANAC_COMP1CR_V1NSEL_Pos)  
#define ANAC_COMP1CR_V1NSEL_PF5     								    ((uint32_t)0x00000000)
#define ANAC_COMP1CR_V1NSEL_PF1    									    ((uint32_t)0x00000002)
#define ANAC_COMP1CR_V1NSEL_Vref0_8v     						  ((uint32_t)0x00000004)
#define ANAC_COMP1CR_V1NSEL_VrefDIV2_0_4v  							((uint32_t)0x00000006)

/** @defgroup ANAC_COMP1CR_V1PSEL
  * @{
  */
#define ANAC_COMP1CR_V1PSEL_Pos		               				3                                             
#define ANAC_COMP1CR_V1PSEL_Msk               					(0x03L << ANAC_COMP1CR_V1PSEL_Pos)  
#define ANAC_COMP1CR_V1PSEL_PF6    								      ((uint32_t)0x00000000)
#define ANAC_COMP1CR_V1PSEL_PF2    									    ((uint32_t)0x00000008)
#define ANAC_COMP1CR_V1PSEL_PG2    								 			((uint32_t)0x00000010)
#define ANAC_COMP1CR_V1PSEL_PG3            							((uint32_t)0x00000018)

/** @defgroup ANAC_COMP1CR_CMP1O
  * @{
  */
#define ANAC_COMP1CR_CMP1O_Pos		               				8                                             
#define ANAC_COMP1CR_CMP1O_Msk               					  (0x01L << ANAC_COMP1CR_CMP1O_Pos) 
#define ANAC_COMP1CR_CMP1O_DISABLE     								  ((uint32_t)0x00000000)
#define ANAC_COMP1CR_CMP1O_ENABLE     								  ((uint32_t)0x00000100)


/**
* @}ANAC_COMP2CR
*/ 

/** @defgroup ANAC_COMP2CR_CMP2EN
  * @{
  */
#define ANAC_COMP2CR_CMP2EN_Pos		               				0                                             
#define ANAC_COMP2CR_CMP2EN_Msk               					(0x01L << ANAC_COMP2CR_CMP2EN_Pos)  
#define ANAC_COMP2CR_CMP2EN_DISABLE     								((uint32_t)0x00000000)
#define ANAC_COMP2CR_CMP2EN_ENABLE     									((uint32_t)0x00000001)

/** @defgroup ANAC_COMP2CR_V2NSEL
  * @{
  */
#define ANAC_COMP2CR_V2NSEL_Pos		               				1                                             
#define ANAC_COMP2CR_V2NSEL_Msk               					(0x03L << ANAC_COMP2CR_V2NSEL_Pos)  
#define ANAC_COMP2CR_V2NSEL_PC14    								    ((uint32_t)0x00000000)
#define ANAC_COMP2CR_V2NSEL_PE3    									    ((uint32_t)0x00000002)
#define ANAC_COMP2CR_V2NSEL_Vref0_8v     							((uint32_t)0x00000004)
#define ANAC_COMP2CR_V2NSEL_VrefDIV2_0_4v   						((uint32_t)0x00000006)

/** @defgroup ANAC_COMP2CR_V2PSEL
  * @{
  */
#define ANAC_COMP2CR_V2PSEL_Pos		               				3                                             
#define ANAC_COMP2CR_V2PSEL_Msk               					(0x01L << ANAC_COMP2CR_V2PSEL_Pos)  
#define ANAC_COMP2CR_V2PSEL_PC15   								      ((uint32_t)0x00000000)
#define ANAC_COMP2CR_V2PSEL_PE4    									    ((uint32_t)0x00000008)


/** @defgroup ANAC_COMP2CR_CMP2O
  * @{
  */
#define ANAC_COMP2CR_CMP2O_Pos		               				8                                             
#define ANAC_COMP2CR_CMP2O_Msk               					  (0x01L << ANAC_COMP2CR_CMP2O_Pos) 
#define ANAC_COMP2CR_CMP2O_DISABLE     								  ((uint32_t)0x00000000)
#define ANAC_COMP2CR_CMP2O_ENABLE     									((uint32_t)0x00000100)


/**
* @}ANAC_COMPICR
*/ 

/** @defgroup ANAC_COMPICR_CMP1IE
  * @{
  */
#define ANAC_COMPICR_CMP1IE_Pos		               				0                                             
#define ANAC_COMPICR_CMP1IE_Msk               					(0x01L << ANAC_COMPICR_CMP1IE_Pos)  
#define ANAC_COMPICR_CMP1IE_DISABLE     								((uint32_t)0x00000000)
#define ANAC_COMPICR_CMP1IE_ENABLE     									((uint32_t)0x00000001)

/** @defgroup ANAC_COMPICR_CMP2IE
  * @{
  */
#define ANAC_COMPICR_CMP2IE_Pos		               				1                                             
#define ANAC_COMPICR_CMP2IE_Msk               					(0x01L << ANAC_COMPICR_CMP2IE_Pos)  
#define ANAC_COMPICR_CMP2IE_DISABLE     								((uint32_t)0x00000000)
#define ANAC_COMPICR_CMP2IE_ENABLE     									((uint32_t)0x00000002)

/** @defgroup ANAC_COMPICR_CMP1SEL
  * @{
  */
#define ANAC_COMPICR_CMP1SEL_Pos		               			2                                             
#define ANAC_COMPICR_CMP1SEL_Msk               					(0x03L << ANAC_COMPICR_CMP1SEL_Pos)  
#define ANAC_COMPICR_CMP1SEL_RISE_FALL     							((uint32_t)0x00000000)
#define ANAC_COMPICR_CMP1SEL_RISING     								((uint32_t)0x00000004)
#define ANAC_COMPICR_CMP1SEL_FALLING     								((uint32_t)0x00000008)

/** @defgroup ANAC_COMPICR_CMP2SEL
  * @{
  */
#define ANAC_COMPICR_CMP2SEL_Pos		               			4                                             
#define ANAC_COMPICR_CMP2SEL_Msk               					(0x03L << ANAC_COMPICR_CMP2SEL_Pos)  
#define ANAC_COMPICR_CMP2SEL_RISE_FALL     							((uint32_t)0x00000000)
#define ANAC_COMPICR_CMP2SEL_RISING     								((uint32_t)0x00000010)
#define ANAC_COMPICR_CMP2SEL_FALLING     								((uint32_t)0x00000020)


/**
* @}ANAC_COMPIF
*/ 

/** @defgroup ANAC_COMPIF_CMP1IF
  * @{
  */
#define ANAC_COMPIF_CMP1IF_Pos		               				0                                             
#define ANAC_COMPIF_CMP1IF_Msk               					  (0x01L << ANAC_COMPIF_CMP1IF_Pos)  
#define ANAC_COMPIF_CMP1IF_CLR     								  ((uint32_t)0x00000000)
#define ANAC_COMPIF_CMP1IF_SET     									((uint32_t)0x00000001)

/** @defgroup ANAC_COMPIF_CMP2IF
  * @{
  */
#define ANAC_COMPIF_CMP2IF_Pos		               				1                                             
#define ANAC_COMPIF_CMP2IF_Msk               					  (0x01L << ANAC_COMPIF_CMP2IF_Pos)  
#define ANAC_COMPIF_CMP2IF_CLR     								  ((uint32_t)0x00000000)
#define ANAC_COMPIF_CMP2IF_SET     									((uint32_t)0x00000002)


/**
* @}ANAC_TROSCCR
*/ 

/** @defgroup ANAC_TROSCCR_TROSCEN
  * @{
  */
#define ANAC_TROSCCR_TROSCEN_Pos		               			0                                             
#define ANAC_TROSCCR_TROSCEN_Msk               					(0x01L << ANAC_TROSCCR_TROSCEN_Pos)  
#define ANAC_TROSCCR_TROSCEN_DISABLE     								((uint32_t)0x00000000)
#define ANAC_TROSCCR_TROSCEN_ENABLE     								((uint32_t)0x00000001)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

extern void PDR_Enable(void);
extern void PDR_Disable(void);
extern void PDR_Config(uint32_t cfg_data);
extern uint32_t PDR_GetConfig(void);

extern void BOR_Enable(void);
extern void BOR_Disable(void);
extern void BOR_PDRConfig(uint32_t cfg_data);
extern uint32_t BOR_GetConfig(void);

extern uint32_t LDO15_GetTrimData(void);

extern uint32_t VREF_GetTrimdata(void);

extern void SVD_Init(SVD_InitType* SVD_InitStruct);
extern void SVD_Enable(void);
extern void SVD_Disable(void);
extern void SVD_ITEnable(uint16_t EnableBit);
extern void SVD_ITDisable(uint16_t DisableBit);
extern ITStatus SVD_GetFlagSta(uint16_t FlagBit);
extern void SVD_ClrITStatus(uint16_t FlagBit);

extern void FDET_ITEnable(void);
extern void FDET_ITDisable(void);
extern ITStatus FDET_GetFlagSta(void);
extern void FDET_ClrITStatus(void);

extern void BUF4TST_Enable(void);
extern void BUF4TST_Disable(void);
extern void BUF4TST_BypassEn(void);
extern void BUF4TST_BypassDisable(void);
extern void BUF4TST_ChannelSel(uint32_t ChannelNUM);

extern void ADC_Enable(void);
extern void ADC_Disable(void);
extern void ADC_ITEnable(void);
extern void ADC_ITDisable(void);
extern ITStatus ADC_GetFlagSta(void);
extern void ADC_ClrITStatus(void);
extern void ADC_SetTrim(uint32_t TrimData);
extern uint32_t ADC_GetData(void);
extern void ADC_ChannelSel(uint32_t channelsel);

extern void TNG_Enable(void);
extern void TNG_Disable(void);

extern void CMP_Enable(uint32_t CmpNum);
extern void CMP_Disable(uint32_t CmpNum);
extern void CMP_Init(uint32_t CmpNum,uint32_t PSELNum,uint32_t NSELNum);
extern void CMP_ITEnable(uint32_t CmpNum);
extern void CMP_ITDisable(uint32_t CmpNum);
extern ITStatus CMP_GetFlagSta(uint32_t CmpNum);
extern void CMP_ClrITStatus(uint32_t CmpNum);
extern ITStatus CMP_GetOutSta(uint32_t CmpNum);
extern void CMP_ISSel(uint32_t CmpNum,uint32_t SelNum);


#ifdef __cplusplus
}
#endif

#endif /* __FM385_ANAC_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/



