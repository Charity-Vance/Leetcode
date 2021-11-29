/**
  ******************************************************************************
  * @file    fm32l0xx_nvmif.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    20-SETP-2016
  * @brief   This file contains all the functions prototypes for the RCC firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_NVMIF_H
#define __FM32L0xx_NVMIF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup NVMIF
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/

/** @defgroup NVMIF_Exported_Constants
  * @{
  */
#define flash_sector_erase_key0 	((uint32_t)0x96969696)
#define flash_sector_erase_key1 	((uint32_t)0xEAEAEAEA)
	 
#define flash_block_erase_key0 		((uint32_t)0x96969696)
#define flash_block_erase_key1 		((uint32_t)0x3C3C3C3C)

#define flash_chip_erase_key0 		((uint32_t)0x96969696)
#define flash_chip_erase_key1 		((uint32_t)0x7D7D7D7D)
	 
#define flash_erase_data 			((uint32_t)0x1234ABCD)

#define flash_PROG_key0 			((uint32_t)0xA5A5A5A5)
#define flash_PROG_key1 			((uint32_t)0xF1F1F1F1)

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

/**
  * @}
  */ 
  
/** @defgroup NVMIF_ACLOCK_BLOCK
  * @{
  */  
#define NVMIF_ACLOCK_BLOCK_0               						((uint32_t)0x00000001)                                            
#define NVMIF_ACLOCK_BLOCK_1               						((uint32_t)0x00000002)
#define NVMIF_ACLOCK_BLOCK_2               						((uint32_t)0x00000004)
#define NVMIF_ACLOCK_BLOCK_3               						((uint32_t)0x00000008) 
#define NVMIF_ACLOCK_BLOCK_4               						((uint32_t)0x00000010)                                            
#define NVMIF_ACLOCK_BLOCK_5               						((uint32_t)0x00000020)
#define NVMIF_ACLOCK_BLOCK_6               						((uint32_t)0x00000040)
#define NVMIF_ACLOCK_BLOCK_7               						((uint32_t)0x00000080) 
#define NVMIF_ACLOCK_BLOCK_8               						((uint32_t)0x00000100)                                            
#define NVMIF_ACLOCK_BLOCK_9               						((uint32_t)0x00000200)
#define NVMIF_ACLOCK_BLOCK_10               					((uint32_t)0x00000400)
#define NVMIF_ACLOCK_BLOCK_11               					((uint32_t)0x00000800) 
#define NVMIF_ACLOCK_BLOCK_12               					((uint32_t)0x00001000)                                            
#define NVMIF_ACLOCK_BLOCK_13               					((uint32_t)0x00002000)
#define NVMIF_ACLOCK_BLOCK_14               					((uint32_t)0x00004000)
#define NVMIF_ACLOCK_BLOCK_15               					((uint32_t)0x00008000) 
#define NVMIF_ACLOCK_BLOCK_16               					((uint32_t)0x00010000)                                            
#define NVMIF_ACLOCK_BLOCK_17               					((uint32_t)0x00020000)
#define NVMIF_ACLOCK_BLOCK_18               					((uint32_t)0x00040000)
#define NVMIF_ACLOCK_BLOCK_19               					((uint32_t)0x00080000) 
#define NVMIF_ACLOCK_BLOCK_20               					((uint32_t)0x00100000)                                            
#define NVMIF_ACLOCK_BLOCK_21               					((uint32_t)0x00200000)
#define NVMIF_ACLOCK_BLOCK_22               					((uint32_t)0x00400000)
#define NVMIF_ACLOCK_BLOCK_23               					((uint32_t)0x00800000) 
#define NVMIF_ACLOCK_BLOCK_24               					((uint32_t)0x01000000)                                            
#define NVMIF_ACLOCK_BLOCK_25               					((uint32_t)0x02000000)
#define NVMIF_ACLOCK_BLOCK_26               					((uint32_t)0x04000000)
#define NVMIF_ACLOCK_BLOCK_27               					((uint32_t)0x08000000) 
#define NVMIF_ACLOCK_BLOCK_28               					((uint32_t)0x10000000)                                            
#define NVMIF_ACLOCK_BLOCK_29               					((uint32_t)0x20000000)
#define NVMIF_ACLOCK_BLOCK_30               					((uint32_t)0x40000000)
#define NVMIF_ACLOCK_BLOCK_31               					((uint32_t)0x80000000) 


#define NVMIF_ACLOCK_BLOCK_32               					((uint32_t)0x00000001)                                            
#define NVMIF_ACLOCK_BLOCK_33               					((uint32_t)0x00000002)
#define NVMIF_ACLOCK_BLOCK_34               					((uint32_t)0x00000004)
#define NVMIF_ACLOCK_BLOCK_35               					((uint32_t)0x00000008) 
#define NVMIF_ACLOCK_BLOCK_36               					((uint32_t)0x00000010)                                            
#define NVMIF_ACLOCK_BLOCK_37               					((uint32_t)0x00000020)
#define NVMIF_ACLOCK_BLOCK_38               					((uint32_t)0x00000040)
#define NVMIF_ACLOCK_BLOCK_39               					((uint32_t)0x00000080) 
#define NVMIF_ACLOCK_BLOCK_40               					((uint32_t)0x00000100)                                            
#define NVMIF_ACLOCK_BLOCK_41               					((uint32_t)0x00000200)
#define NVMIF_ACLOCK_BLOCK_42               					((uint32_t)0x00000400)
#define NVMIF_ACLOCK_BLOCK_43               					((uint32_t)0x00000800) 
#define NVMIF_ACLOCK_BLOCK_44               					((uint32_t)0x00001000)                                            
#define NVMIF_ACLOCK_BLOCK_45               					((uint32_t)0x00002000)
#define NVMIF_ACLOCK_BLOCK_46               					((uint32_t)0x00004000)
#define NVMIF_ACLOCK_BLOCK_47               					((uint32_t)0x00008000) 
#define NVMIF_ACLOCK_BLOCK_48               					((uint32_t)0x00010000)                                            
#define NVMIF_ACLOCK_BLOCK_49               					((uint32_t)0x00020000)
#define NVMIF_ACLOCK_BLOCK_50               					((uint32_t)0x00040000)
#define NVMIF_ACLOCK_BLOCK_51               					((uint32_t)0x00080000) 
#define NVMIF_ACLOCK_BLOCK_52               					((uint32_t)0x00100000)                                            
#define NVMIF_ACLOCK_BLOCK_53               					((uint32_t)0x00200000)
#define NVMIF_ACLOCK_BLOCK_54               					((uint32_t)0x00400000)
#define NVMIF_ACLOCK_BLOCK_55               					((uint32_t)0x00800000) 
#define NVMIF_ACLOCK_BLOCK_56               					((uint32_t)0x01000000)                                            
#define NVMIF_ACLOCK_BLOCK_57               					((uint32_t)0x02000000)
#define NVMIF_ACLOCK_BLOCK_58               					((uint32_t)0x04000000)
#define NVMIF_ACLOCK_BLOCK_59               					((uint32_t)0x08000000) 
#define NVMIF_ACLOCK_BLOCK_60               					((uint32_t)0x10000000)                                            
#define NVMIF_ACLOCK_BLOCK_61               					((uint32_t)0x20000000)
#define NVMIF_ACLOCK_BLOCK_62               					((uint32_t)0x40000000)
#define NVMIF_ACLOCK_BLOCK_63               					((uint32_t)0x80000000)

/**
  * @}
  */ 
  
/** @defgroup NVMIF_EPCON_ERTYPE
  * @{
  */ 
#define NVMIF_EPCON_ERTYPE_Pos               				8                                            
#define NVMIF_EPCON_ERTYPE_Msk               				(0x03UL << NVMIF_EPCON_ERTYPE_Pos) 
#define NVMIF_EPCON_ERTYPE_SECTOR               			((uint32_t)0x00000000)
#define NVMIF_EPCON_ERTYPE_BLOCK               				((uint32_t)0x00000100)
#define NVMIF_EPCON_ERTYPE_CHIP               				((uint32_t)0x00000200)

/** @defgroup NVMIF_EPCON_PREQ
  * @{
  */ 
#define NVMIF_EPCON_PREQ_Pos               					1                                            
#define NVMIF_EPCON_PREQ_Msk               					(0x01UL << NVMIF_EPCON_PREQ_Pos)   
#define NVMIF_EPCON_PREQ_RESET               				((uint32_t)0x00000000)  
#define NVMIF_EPCON_PREQ_SET               					((uint32_t)0x00000002)

/** @defgroup NVMIF_EPCON_EREQ
  * @{
  */ 
#define NVMIF_EPCON_EREQ_Pos               					0                                            
#define NVMIF_EPCON_EREQ_Msk               					(0x01UL << NVMIF_EPCON_EREQ_Pos) 
#define NVMIF_EPCON_EREQ_RESET           					((uint32_t)0x00000000)
#define NVMIF_EPCON_EREQ_SET           						((uint32_t)0x00000001)

/**
  * @}
  */ 
  
/** @defgroup NVMIF_FLSIE_AUTHIE
  * @{
  */ 
#define NVMIF_FLSIE_AUTHIE_Pos               				10                                            
#define NVMIF_FLSIE_AUTHIE_Msk               				(0x01UL << NVMIF_FLSIE_AUTHIE_Pos) 
#define NVMIF_FLSIE_AUTHIE_DISABLE               			((uint32_t)0x00000000)
#define NVMIF_FLSIE_AUTHIE_ENABLE               			((uint32_t)0x00000400)

/** @defgroup NVMIF_FLSIE_KEYIE
  * @{
  */ 
#define NVMIF_FLSIE_KEYIE_Pos               				9                                            
#define NVMIF_FLSIE_KEYIE_Msk               				(0x01UL << NVMIF_FLSIE_KEYIE_Pos) 
#define NVMIF_FLSIE_KEYIE_DISABLE               			((uint32_t)0x00000000)
#define NVMIF_FLSIE_KEYIE_ENABLE               				((uint32_t)0x00000200)

/** @defgroup NVMIF_FLSIE_CKIE
  * @{
  */ 
#define NVMIF_FLSIE_CKIE_Pos               					8                                            
#define NVMIF_FLSIE_CKIE_Msk               					(0x01UL << NVMIF_FLSIE_CKIE_Pos) 
#define NVMIF_FLSIE_CKIE_DISABLE               				((uint32_t)0x00000000)
#define NVMIF_FLSIE_CKIE_ENABLE               				((uint32_t)0x00000100)

/** @defgroup NVMIF_PRDIE_CKIE
  * @{
  */ 
#define NVMIF_FLSIE_PRDIE_Pos               				1                                            
#define NVMIF_FLSIE_PRDIE_Msk               				(0x01UL << NVMIF_FLSIE_PRDIE_Pos) 
#define NVMIF_FLSIE_PRDIE_DISABLE               			((uint32_t)0x00000000)
#define NVMIF_FLSIE_PRDIE_ENABLE               				((uint32_t)0x00000002)

/** @defgroup NVMIF_ERDIE_CKIE
  * @{
  */ 
#define NVMIF_FLSIE_ERDIE_Pos               				0                                            
#define NVMIF_FLSIE_ERDIE_Msk               				(0x01UL << NVMIF_FLSIE_ERDIE_Pos) 
#define NVMIF_FLSIE_ERDIE_DISABLE               			((uint32_t)0x00000000)
#define NVMIF_FLSIE_ERDIE_ENABLE               				((uint32_t)0x00000001)

/**
  * @}
  */ 
  
/** @defgroup NVMIF_FLSIF_AUTHIF
  * @{
  */ 
#define NVMIF_FLSIF_AUTHIF_Pos               				10                                            
#define NVMIF_FLSIF_AUTHIF_Msk               				(0x01UL << NVMIF_FLSIF_AUTHIF_Pos) 
#define NVMIF_FLSIF_AUTHIF_DISABLE               			((uint32_t)0x00000000)
#define NVMIF_FLSIF_AUTHIF_ENABLE               			((uint32_t)0x00000400)

/** @defgroup NVMIF_FLSIF_KEYIF
  * @{
  */ 
#define NVMIF_FLSIF_KEYIF_Pos               				9                                            
#define NVMIF_FLSIF_KEYIF_Msk               				(0x01UL << NVMIF_FLSIF_KEYIF_Pos) 
#define NVMIF_FLSIF_KEYIF_DISABLE               			((uint32_t)0x00000000)
#define NVMIF_FLSIF_KEYIF_ENABLE               				((uint32_t)0x00000200)

/** @defgroup NVMIF_FLSIF_CKIF
  * @{
  */ 
#define NVMIF_FLSIF_CKIF_Pos               					8                                            
#define NVMIF_FLSIF_CKIF_Msk               					(0x01UL << NVMIF_FLSIF_CKIF_Pos) 
#define NVMIF_FLSIF_CKIF_DISABLE               				((uint32_t)0x00000000)
#define NVMIF_FLSIF_CKIF_ENABLE               				((uint32_t)0x00000100)

/** @defgroup NVMIF_PRDIF_CKIF
  * @{
  */ 
#define NVMIF_FLSIF_PRDIF_Pos               				1                                            
#define NVMIF_FLSIF_PRDIF_Msk               				(0x01UL << NVMIF_FLSIF_PRDIF_Pos) 
#define NVMIF_FLSIF_PRDIF_DISABLE               			((uint32_t)0x00000000)
#define NVMIF_FLSIF_PRDIF_ENABLE               				((uint32_t)0x00000002)

/** @defgroup NVMIF_ERDIF_CKIF
  * @{
  */ 
#define NVMIF_FLSIF_ERDIF_Pos               				0                                            
#define NVMIF_FLSIF_ERDIF_Msk               				(0x01UL << NVMIF_FLSIF_ERDIF_Pos) 
#define NVMIF_FLSIF_ERDIF_DISABLE               			((uint32_t)0x00000000)
#define NVMIF_FLSIF_ERDIF_ENABLE               				((uint32_t)0x00000001)

/**
  * @}
  */ 
  
/** @defgroup NVMIF_RAMRPRx_RPEN
  * @{
  */ 
#define NVMIF_RAMRPRx_RPEN_Pos               				31                                            
#define NVMIF_RAMRPRx_RPEN_Msk               				(0x01UL << NVMIF_FLSIE_AUTHIF_Pos) 
#define NVMIF_RAMRPRx_RPEN_DISABLE               			((uint32_t)0x00000000)
#define NVMIF_RAMRPRx_RPEN_ENABLE               			((uint32_t)0x80000000)

/** @defgroup NVMIF_RAMRPRx_RAMRPD
  * @{
  */ 
#define NVMIF_RAMRPRx_RAMRPD_Pos               				8                                            
#define NVMIF_RAMRPRx_RAMRPD_Msk               				(0xFFUL << NVMIF_RAMRPRx_RAMRPD_Pos) 


/** @defgroup NVMIF_RAMRPRx_RAMFAD
  * @{
  */ 
#define NVMIF_RAMRPRx_RAMFAD_Pos               				0                                            
#define NVMIF_RAMRPRx_RAMFAD_Msk               				(0xFFFFUL << NVMIF_RAMRPRx_RAMFAD_Pos) 


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

extern void NVMIF_INIT(void);
extern void NVMIF_DeINIT(void);
extern void NVMIF_SET_waitcycle(uint32_t cycle_num);
extern void NVMIF_PREFATCH_enable(void);
extern void NVMIF_PREFATCH_disable(void);

extern void NVMIF_ERASE_sector(uint32_t* erase_addr);
extern void NVMIF_ERASE_block(uint32_t* erase_addr);
extern void NVMIF_ERASE_chip(void);
extern void NVMIF_PROG_single_word(uint32_t* prog_addr,uint32_t prog_data);
extern void NVMIF_PROG_half_word(uint16_t* prog_addr,uint16_t prog_data);
extern void NVMIF_PROG_single_byte(uint8_t* prog_addr,uint8_t prog_data);

#ifdef __cplusplus
}
#endif

#endif /* __FM385_RCC_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/



