/**
  ******************************************************************************
  * @file    fm32l0xx_etimer.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    20-SETP-2016
  * @brief   This file contains all the functions prototypes for the RCC firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_ETIMER_H
#define __FM32L0xx_ETIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup ETIMER
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/

/** @defgroup ETIMER_Exported_Constants
  * @{
  */


/* Exported types ------------------------------------------------------------*/


/**
* @}
*/ 
  
/** @defgroup NVMIF_FLSRDCON_WAIT 
  * @{
  */
#define NVMIF_FLSRDCON_WAIT_Pos		               						0                                             
#define NVMIF_FLSRDCON_WAIT_Msk               							(0x01UL << NVMIF_FLSRDCON_WAIT_Pos)  
#define NVMIF_FLSRDCON_WAIT_0                							((uint32_t)0x00000000)
#define NVMIF_FLSRDCON_WAIT_1                							((uint32_t)0x00000001)
#define NVMIF_FLSRDCON_WAIT_2                							((uint32_t)0x00000002)


/** @defgroup NVMIF_FLSRDCON_READM0
  * @{
  */
#define NVMIF_FLSRDCON_READM0_Pos               						8                                            
#define NVMIF_FLSRDCON_READM0_Msk               						(0x03UL << NVMIF_FLSRDCON_READM0_Pos)
#define NVMIF_FLSRDCON_READM0_DISABLE                					((uint32_t)0x00000100)
#define NVMIF_FLSRDCON_READM0_ENABLE                					((uint32_t)0x00000200)



/** @defgroup NVMIF_FLSRDCON_READM1
  * @{
  */
#define NVMIF_FLSRDCON_READM1_Pos               						10                                            
#define NVMIF_FLSRDCON_READM1_Msk               						(0x03UL << NVMIF_FLSRDCON_READM0_Pos)
#define NVMIF_FLSRDCON_READM1_DISABLE                					((uint32_t)0x00000400)
#define NVMIF_FLSRDCON_READM1_ENABLE                					((uint32_t)0x00000800)

/**
  * @}
  */ 

/** @defgroup NVMIF_PRFTCON_PRFTEN
  * @{
  */  
#define NVMIF_PRFTCON_PRFTEN_Pos               							0                                            
#define NVMIF_PRFTCON_PRFTEN_Msk               							(0x01UL << NVMIF_PRFTCON_PRFTEN_Pos) 
#define NVMIF_PRFTCON_PRFTEN_DISABLE                					((uint32_t)0x00000000)
#define NVMIF_PRFTCON_PRFTEN_ENABLE               						((uint32_t)0x00000001)

/**
  * @}
  */ 

/** @defgroup NVMIF_OPTBR_BOOT0
  * @{
  */  
#define NVMIF_OPTBR_BOOT0_Pos               							7                                            
#define NVMIF_OPTBR_BOOT0_Msk               							(0x01UL << NVMIF_OPTBR_BOOT0_Pos) 
#define NVMIF_OPTBR_BOOT0_RAM                							((uint32_t)0x00000000)
#define NVMIF_OPTBR_BOOT0_FLASH               							((uint32_t)0x00000001)

/** @defgroup NVMIF_OPTBR_ACLOCKEN
  * @{
  */  
#define NVMIF_OPTBR_ACLOCKEN_Pos               							2                                            
#define NVMIF_OPTBR_ACLOCKEN_Msk               							(0x03UL << NVMIF_OPTBR_ACLOCKEN_Pos) 
#define NVMIF_OPTBR_ACLOCKEN_DISABLE               						((uint32_t)0x00000004)
#define NVMIF_OPTBR_ACLOCKEN_ENABLE               						((uint32_t)0x00000008)

/** @defgroup NVMIF_OPTBR_DBRDPEN
  * @{
  */  
#define NVMIF_OPTBR_DBRDPEN_Pos               							0                                            
#define NVMIF_OPTBR_DBRDPEN_Msk               							(0x03UL << NVMIF_OPTBR_DBRDPEN_Pos) 
#define NVMIF_OPTBR_DBRDPEN_DISABLE               						((uint32_t)0x00000001)
#define NVMIF_OPTBR_DBRDPEN_ENABLE               						((uint32_t)0x00000002)


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 



#ifdef __cplusplus
}
#endif

#endif /* __FM385_RCC_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/



