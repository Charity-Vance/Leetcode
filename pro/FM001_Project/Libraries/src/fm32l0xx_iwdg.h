/**
  ******************************************************************************
  * @file    fm32l0xx_iwdg.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    20-SETP-2016
  * @brief   This file contains all the functions prototypes for the RCC firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_IWDG_H
#define __FM32L0xx_IWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM33A0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup IWDG
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/

/** @defgroup IWDG_Exported_Constants
  * @{
  */

/* Exported types ------------------------------------------------------------*/

#define WDTSERV_key	((uint32_t)0x12345A5A)
/**
* @}
*/ 
  
/** @defgroup IWDT_IWDTSERV 
  * @{
  */
#define IWDT_IWDTOVP_Pos               								0                                             
#define IWDT_IWDTOVP               								((uint32_t)0x00000007) 
#define IWDT_IWDTOVP_Msk               								(0x07UL << IWDT_IWDTOVP_Pos)  
#define IWDT_IWDTOVP_125ms                						 ((uint32_t)0x00000000)
#define IWDT_IWDTOVP_500ms               							((uint32_t)0x00000001)
#define IWDT_IWDTOVP_2s                								((uint32_t)0x00000002)
#define IWDT_IWDTOVP_8s                								((uint32_t)0x00000003)

#define IWDT_IWDTOVP_4096s                						((uint32_t)0x00000004)



/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

extern void IWDT_Clr(void);					/*clr iwdt*/
extern void IWDT_Set(uint32_t period);			/*set iwdt overflow period*/
extern uint32_t IWDT_Read_Counter(void);		/*return the value of the counter*/

#ifdef __cplusplus
}
#endif

#endif /* __FM385_IWDT_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/



