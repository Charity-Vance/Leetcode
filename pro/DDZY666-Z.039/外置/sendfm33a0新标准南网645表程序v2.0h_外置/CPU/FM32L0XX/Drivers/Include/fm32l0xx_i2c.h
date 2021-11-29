/**
  ******************************************************************************
  * @file    fm32l0xx_i2c.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    2-MAR-2017
  * @brief   This file contains all the functions prototypes for the I2C firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_I2C_H
#define __FM32L0xx_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/

/** @defgroup I2C_Exported_Constants
  * @{
  */
  
	 
/* Exported types ------------------------------------------------------------*/


/**
* @}I2C_I2CCON
*/ 
  
/** @defgroup I2C_I2CCON_I2CEN 
  * @{
  */
#define I2C_I2CCON_I2CEN_Pos		               					0                                             
#define I2C_I2CCON_I2CEN_Msk               							(0x01UL << I2C_I2CCON_I2CEN_Pos)  
#define I2C_I2CCON_I2CEN_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CCON_I2CEN_ENABLE     									  ((uint32_t)0x00000001)

/** @defgroup I2C_I2CCON_SEN 
  * @{
  */
#define I2C_I2CCON_SEN_Pos                              8                                             
#define I2C_I2CCON_SEN_Msk               							  (0x01UL << I2C_I2CCON_SEN_Pos) 
#define I2C_I2CCON_SEN_DISABLE     									    ((uint32_t)0x00000000)
#define I2C_I2CCON_SEN_ENABLE     									    ((uint32_t)0x00000100)

/** @defgroup I2C_I2CCON_RSEN 
  * @{
  */
#define I2C_I2CCON_RSEN_Pos		               				    9                                             
#define I2C_I2CCON_RSEN_Msk               						  (0x01UL << I2C_I2CCON_RSEN_Pos) 
#define I2C_I2CCON_RSEN_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CCON_RSEN_ENABLE     									    ((uint32_t)0x00000200)

/** @defgroup I2C_I2CCON_PEN 
  * @{
  */
#define I2C_I2CCON_PEN_Pos		               					  10                                             
#define I2C_I2CCON_PEN_Msk               							  (0x01UL << I2C_I2CCON_PEN_Pos)  
#define I2C_I2CCON_PEN_DISABLE     									    ((uint32_t)0x00000000)
#define I2C_I2CCON_PEN_ENABLE     									    ((uint32_t)0x00000400)

/** @defgroup I2C_I2CCON_RCEN
  * @{
  */
#define I2C_I2CCON_RCEN_Pos		               					  11                                             
#define I2C_I2CCON_RCEN_Msk               							(0x01UL << I2C_I2CCON_RCEN_Pos)  
#define I2C_I2CCON_RCEN_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CCON_RCEN_ENABLE     									    ((uint32_t)0x00000800)

/** @defgroup I2C_I2CCON_ACKEN
  * @{
  */
#define I2C_I2CCON_ACKEN_Pos		               				  12                                             
#define I2C_I2CCON_ACKEN_Msk               							(0x01UL << I2C_I2CCON_ACKEN_Pos) 
#define I2C_I2CCON_ACKEN_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CCON_ACKEN_ENABLE     									  ((uint32_t)0x00001000)

/** @defgroup I2C_I2CCON_SDAHL 
  * @{
  */
#define I2C_I2CCON_SDAHL_Pos		               					13                                             
#define I2C_I2CCON_SDAHL_Msk               							(0x01UL << I2C_I2CCON_SDAHL_Pos) 
#define I2C_I2CCON_SDAHL_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CCON_SDAHL_ENABLE     									  ((uint32_t)0x00002000)

/** @defgroup I2C_I2CCON_SCLHL 
  * @{
  */
#define I2C_I2CCON_SCLHL_Pos		               					14                                             
#define I2C_I2CCON_SCLHL_Msk               							(0x01UL << I2C_I2CCON_SCLHL_Pos) 
#define I2C_I2CCON_SCLHL_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CCON_SCLHL_ENABLE     									  ((uint32_t)0x00004000)


/**
* @}I2C_I2CSTA
*/ 
  
/** @defgroup I2C_I2CSTA_ACKDT
  * @{
  */
#define I2C_I2CSTA_ACKDT_Pos		               					0                                             
#define I2C_I2CSTA_ACKDT_Msk               							(0x01UL << I2C_I2CSTA_ACKDT_Pos)  
#define I2C_I2CSTA_ACKDT_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CSTA_ACKDT_ENABLE     									  ((uint32_t)0x00000001)

/** @defgroup I2C_I2CSTA_ACKSTAT
  * @{
  */
#define I2C_I2CSTA_ACKSTAT_Pos		               				1                                             
#define I2C_I2CSTA_ACKSTAT_Msk               						(0x01UL << I2C_I2CSTA_ACKSTAT_Pos)  
#define I2C_I2CSTA_ACKSTAT_DISABLE     									((uint32_t)0x00000000)
#define I2C_I2CSTA_ACKSTAT_ENABLE     									((uint32_t)0x00000002)

/** @defgroup I2C_I2CSTA_BF
  * @{
  */
#define I2C_I2CSTA_BF_Pos		               				      2                                             
#define I2C_I2CSTA_BF_Msk               						    (0x01UL << I2C_I2CSTA_BF_Pos)  
#define I2C_I2CSTA_BF_DISABLE     									    ((uint32_t)0x00000000)
#define I2C_I2CSTA_BF_ENABLE     									      ((uint32_t)0x00000004)

/** @defgroup I2C_I2CSTA_S
  * @{
  */
#define I2C_I2CSTA_S_Pos		               				      3                                             
#define I2C_I2CSTA_S_Msk               						      (0x01UL << I2C_I2CSTA_S_Pos)  
#define I2C_I2CSTA_S_DISABLE     									      ((uint32_t)0x00000000)
#define I2C_I2CSTA_S_ENABLE     									      ((uint32_t)0x00000008)

/** @defgroup I2C_I2CSTA_STOP
  * @{
  */
#define I2C_I2CSTA_STOP_Pos		               				    4                                             
#define I2C_I2CSTA_STOP_Msk               						  (0x01UL << I2C_I2CSTA_STOP_Pos)  
#define I2C_I2CSTA_STOP_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CSTA_STOP_ENABLE     									    ((uint32_t)0x00000010)

/** @defgroup I2C_I2CSTA_RW
  * @{
  */
#define I2C_I2CSTA_RW_Pos		               				      5                                             
#define I2C_I2CSTA_RW_Msk               						    (0x01UL << I2C_I2CSTA_RW_Pos)  
#define I2C_I2CSTA_RW_DISABLE     									    ((uint32_t)0x00000000)
#define I2C_I2CSTA_RW_ENABLE     									      ((uint32_t)0x00000020)

/** @defgroup I2C_I2CSTA_WCOL
  * @{
  */
#define I2C_I2CSTA_WCOL_Pos		               				    6                                             
#define I2C_I2CSTA_WCOL_Msk               						  (0x01UL << I2C_I2CSTA_WCOL_Pos)  
#define I2C_I2CSTA_WCOL_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CSTA_WCOL_ENABLE     									    ((uint32_t)0x00000040)


/**
* @}I2C_I2CIR
*/ 

/** @defgroup I2C_I2CIR_I2CIF
  * @{
  */
#define I2C_I2CIR_I2CIF_Pos		               					  0                                            
#define I2C_I2CIR_I2CIF_Msk               						  (0x01UL << I2C_I2CIR_I2CIF_Pos) 
#define I2C_I2CIR_I2CIF_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CIR_I2CIF_ENABLE     									    ((uint32_t)0x00000001)

/** @defgroup I2C_I2CIR_I2CIE
  * @{
  */
#define I2C_I2CIR_I2CIE_Pos		               					  1                                            
#define I2C_I2CIR_I2CIE_Msk               						  (0x01UL << I2C_I2CIR_I2CIE_Pos) 
#define I2C_I2CIR_I2CIE_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CIR_I2CIE_ENABLE     									    ((uint32_t)0x00000002)


/**
* @}I2C_I2CFSM
*/ 

/** @defgroup I2C_I2CFSM_I2CFSM
  * @{
  */
#define I2C_I2CFSM_I2CFSM_Pos		               					0                                            
#define I2C_I2CFSM_I2CFSM_Msk               						(0x0FUL << I2C_I2CFSM_I2CFSM_Pos) 
#define I2CIR_I2CFSM_IDLE																((uint32_t)0x00000000)
#define I2CIR_I2CFSM_START1															((uint32_t)0x00000001)
#define I2CIR_I2CFSM_START2															((uint32_t)0x00000010)
#define I2CIR_I2CFSM_START_DONE													((uint32_t)0x00000011)
#define I2CIR_I2CFSM_TX_STATE												    ((uint32_t)0x00000100)
#define I2CIR_I2CFSM_RCACK												      ((uint32_t)0x00000101)
#define I2CIR_I2CFSM_OP_IDLE  													((uint32_t)0x00000110)
#define I2CIR_I2CFSM_STOP1    											    ((uint32_t)0x00000111)
#define I2CIR_I2CFSM_STOP2    											    ((uint32_t)0x00001000)
#define I2CIR_I2CFSM_STOP_DONE												  ((uint32_t)0x00001001)
#define I2CIR_I2CFSM_RTP_START													((uint32_t)0x00001010)
#define I2CIR_I2CFSM_RX_STATE											      ((uint32_t)0x00001011)
#define I2CIR_I2CFSM_ACT_STATE												  ((uint32_t)0x00001100)
#define I2CIR_I2CFSM_STOP0										          ((uint32_t)0x00001101)


/**
* @}I2C_I2CERR
*/ 

/** @defgroup I2C_I2CERR_IERR
  * @{
  */
#define I2C_I2CERR_IERR_Pos		               					  0                                            
#define I2C_I2CERR_IERR_Msk               						  (0x01UL << I2C_I2CERR_IERR_Pos) 
#define I2C_I2CERR_IERR_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CERR_IERR_ENABLE     									    ((uint32_t)0x00000001)

/** @defgroup I2C_I2CERR_SDERR
  * @{
  */
#define I2C_I2CERR_SDERR_Pos		               					1                                            
#define I2C_I2CERR_SDERR_Msk               						  (0x01UL << I2C_I2CERR_SDERR_Pos) 
#define I2C_I2CERR_SDERR_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CERR_SDERR_ENABLE     									  ((uint32_t)0x00000002)

/** @defgroup I2C_I2CERR_OIERR
  * @{
  */
#define I2C_I2CERR_OIERR_Pos		               					2                                            
#define I2C_I2CERR_OIERR_Msk               						  (0x01UL << I2C_I2CERR_OIERR_Pos) 
#define I2C_I2CERR_OIERR_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CERR_OIERR_ENABLE     									  ((uint32_t)0x00000004)

/** @defgroup I2C_I2CERR_ERRIE
  * @{
  */
#define I2C_I2CERR_ERRIE_Pos		               					8                                            
#define I2C_I2CERR_ERRIE_Msk               						  (0x01UL << I2C_I2CERR_ERRIE_Pos) 
#define I2C_I2CERR_ERRIE_DISABLE     									  ((uint32_t)0x00000000)
#define I2C_I2CERR_ERRIE_ENABLE     									  ((uint32_t)0x00000100)




#ifdef __cplusplus
}
#endif

#endif /* __FM385_I2C_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/

